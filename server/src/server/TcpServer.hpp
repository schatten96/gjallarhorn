#include "../session/TcpSession.hpp"
#include <IServer.hpp>

class TcpServer : public IServer {
public:
    explicit TcpServer(uint16_t port);
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
