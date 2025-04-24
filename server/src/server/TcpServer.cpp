#include "TcpServer.hpp"

TcpServer::TcpServer(uint16_t port)
    : mAcceptor(mIoContext, boost::asio::ip::tcp::endpoint(
                                boost::asio::ip::tcp::v4(), port)) {
}

void
TcpServer::start() {
    mAcceptor.listen();
    accept();
    //! TODO
    mIoContext.run();
}

void
TcpServer::stop() {
    mAcceptor.close();
    mIoContext.stop();
}

void
TcpServer::accept() {
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
TcpServer::createSession(boost::asio::ip::tcp::socket socket) const {
    return std::make_shared<TcpSession>(std::move(socket));
}