#include <ISession.hpp>
#include <boost/asio.hpp>

class TcpSession : public ISession {
public:
    explicit TcpSession(boost::asio::ip::tcp::socket socket);
    void start() override;
    void read() override;
    void write(const std::string& data) override;

private:
    boost::asio::ip::tcp::socket mSocket;
    enum { max_length = 1024 };
    char mData[max_length];
};
