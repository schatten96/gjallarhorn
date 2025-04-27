#pragma once

#include "server/ISession.hpp"
#include <boost/asio.hpp>

namespace gh {

class BoostTcpSession : public ISession {
public:
    explicit BoostTcpSession(boost::asio::ip::tcp::socket socket);
    ~BoostTcpSession() override;
    void start() override;
    void read() override;
    void write(const std::string& data) override;

private:
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::streambuf mMessageBuffer;
};

} // namespace gh