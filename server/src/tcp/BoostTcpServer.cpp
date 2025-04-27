#include "BoostTcpServer.hpp"

namespace gh {

BoostTcpServer::BoostTcpServer(uint16_t port)
    : mAcceptor(mIoContext, boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(), port)) {
}

BoostTcpServer::~BoostTcpServer() {
    stop();
}

void
BoostTcpServer::start() {
    mAcceptor.listen();
    accept();
    mIoContext.run();
}

void
BoostTcpServer::stop() {
    mAcceptor.close();
    mIoContext.stop();
}

void
BoostTcpServer::accept() {
    mAcceptor.async_accept([this](boost::system::error_code ec,
                                  boost::asio::ip::tcp::socket socket) {
        if (!ec) {
            auto session = createSession(std::move(socket));
            session->start();
        }
        accept();
    });
}

std::shared_ptr<ISession>
BoostTcpServer::createSession(boost::asio::ip::tcp::socket socket) const {
    return std::make_shared<BoostTcpSession>(std::move(socket));
}

} // namespace gh