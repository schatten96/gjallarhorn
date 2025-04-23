#pragma once

#include "client/IClient.hpp"
#include "client/Enums.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace gh {

class BoostTcpClient : public IClient {
public:
    explicit BoostTcpClient();
    ~BoostTcpClient() override;

    void connect(const std::string& url) override;
    void disconnect() override;
    bool isConnected() const override;
    void send(const std::string& data) override;

private:
    void asyncRead();

private:
    ConnectionStatus mStatus;
    boost::asio::io_context mIoContext;
    boost::asio::ip::tcp::socket mSocket;
    boost::asio::streambuf mMessageBuffer;
    std::thread mIoThread;
};

} // namespace gh