#include "TcpSession.hpp"

TcpSession::TcpSession(boost::asio::ip::tcp::socket socket)
    : mSocket(std::move(socket)) {
}

void
TcpSession::start() {
    read();
}

void
TcpSession::read() {
    boost::asio::async_read(
        mSocket, boost::asio::buffer(mData, max_length),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec && length > 0) {
                //! TODO reading data
                read();
            }
        });
}

void
TcpSession::write(const std::string& data) {
    boost::asio::async_write(
        mSocket, boost::asio::buffer(mData),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // successful sending
            }
        });
}