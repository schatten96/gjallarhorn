#pragma once

#include "server/IServer.hpp"
#include <memory>
#include <boost/asio.hpp>

namespace gh {

class ISession;

class BoostTcpServer : public IServer {
public:
    explicit BoostTcpServer(std::uint16_t port);
    ~BoostTcpServer() override;
    void start() override;
    void stop() override;

private:
    void accept();
    std::shared_ptr<ISession>
    createSession(boost::asio::ip::tcp::socket socket) const;

private:
    boost::asio::io_context mIoContext;
    boost::asio::ip::tcp::acceptor mAcceptor;
};

} // namespace gh