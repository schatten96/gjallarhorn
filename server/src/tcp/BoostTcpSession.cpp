#include "BoostTcpSession.hpp"

namespace gh {

BoostTcpSession::BoostTcpSession(boost::asio::ip::tcp::socket socket)
    : mSocket(std::move(socket))
    , mMessageBuffer(1024) {
}

BoostTcpSession::~BoostTcpSession() {
    boost::system::error_code ec;
    mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    mSocket.close(ec);
}

void
BoostTcpSession::start() {
    read();
}

void
BoostTcpSession::read() {
    auto self = shared_from_this();
    boost::asio::async_read_until(
        mSocket, mMessageBuffer, '\n',
        [this, self](const boost::system::error_code& ec, std::size_t length) {
            if (!ec) {
                if (length > 0) {
                    std::istream is(&mMessageBuffer);
                    std::string message;
                    std::getline(is, message);
                    write(message);
                }
                read();
            }
        });
}

void
BoostTcpSession::write(const std::string& data) {
    boost::asio::async_write(
        mSocket, boost::asio::buffer(data + "\n"),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // successful sending
            }
        });
}

} // namespace gh