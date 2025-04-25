#include "BoostTcpClient.hpp"

namespace gh {

BoostTcpClient::BoostTcpClient()
    : mStatus(ConnectionStatus::Disconnected)
    , mIoContext()
    , mSocket(mIoContext)
    , mMessageBuffer(1024) {
}

BoostTcpClient::~BoostTcpClient() {
    disconnect();
}

void
BoostTcpClient::connect(const std::string& url) {
    try {
        size_t pos = url.find("://");
        if (pos == std::string::npos || url.substr(0, pos) != "tcp") {
            throw std::invalid_argument(
                "Invalid URL format. Use 'tcp://host:port'");
        }

        std::string hostPort = url.substr(pos + 3);
        pos = hostPort.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Port not specified");
        }

        std::string host = hostPort.substr(0, pos);
        std::string port = hostPort.substr(pos + 1);

        boost::asio::ip::tcp::resolver resolver(mIoContext);
        auto endpoints = resolver.resolve(host, port);

        boost::asio::connect(mSocket, endpoints);
        mStatus = ConnectionStatus::Connected;

        asyncRead();
        mIoThread = std::thread([this]() { mIoContext.run(); });

    } catch (const std::exception& e) {
        mStatus = ConnectionStatus::Disconnected;
        throw std::runtime_error(std::string("Connection failed: ") + e.what());
    }
}

void
BoostTcpClient::disconnect() {
    if (mStatus == ConnectionStatus::Disconnected)
        return;

    boost::system::error_code ec;
    mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    mSocket.close(ec);
    mIoContext.stop();

    if (mIoThread.joinable()) {
        mIoThread.join();
    }

    mStatus = ConnectionStatus::Disconnected;
}

bool
BoostTcpClient::isConnected() const {
    return mStatus == ConnectionStatus::Connected && mSocket.is_open();
}

void
BoostTcpClient::send(const std::string& data) {
    if (!isConnected()) {
        throw std::runtime_error("Not connected");
    }

    boost::asio::write(mSocket, boost::asio::buffer(data + "\n"));
}

void
BoostTcpClient::asyncRead() {
    boost::asio::async_read_until(
        mSocket, mMessageBuffer, '\n',
        [this](boost::system::error_code ec, std::size_t bytes) {
            if (ec) {
                if (ec != boost::asio::error::operation_aborted) {
                    disconnect();
                }
                return;
            }

            std::istream is(&mMessageBuffer);
            std::string message;
            std::getline(is, message);

            if (mMessageHandler) {
                mMessageHandler(message);
            }

            asyncRead();
        });
}

} // namespace gh
