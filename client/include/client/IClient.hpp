#pragma once

#include <string>
#include <functional>

namespace gh {

class IClient {
public:
    virtual ~IClient() = default;

    using MessageHandler = std::function<void(const std::string&)>;
    using ConnectionHandler =
        std::function<void(bool connected, const std::string& error)>;

    /**
     * @brief Performs connection to server
     * @param url - formatted string, connection endpoint
     * @example "wss://example.com/chat", "tcp://127.0.0.1:8080"
     */
    virtual void connect(const std::string& url) = 0;

    /**
     * @brief Disconnects client from server
     */
    virtual void disconnect() = 0;

    /**
     * @brief Returns true if client is connected
     */
    virtual bool isConnected() const = 0;

    /**
     * @brief Sends message to server
     * @param data - message converted to binary
     */
    virtual void send(const std::string& data) = 0;

    /**
     * @brief Sets message handler callback
     */
    inline void
    setMessageHandler(MessageHandler handler) {
        mMessageHandler = std::move(handler);
    }

    /**
     * @brief Sets connection handler callback
     */
    inline void
    setConnectionHandler(ConnectionHandler handler) {
        mConnectionHandler = std::move(handler);
    }

protected:
    MessageHandler mMessageHandler;
    ConnectionHandler mConnectionHandler;
};

} // namespace gh