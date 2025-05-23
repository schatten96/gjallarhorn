#pragma once

#include <memory>

namespace gh {

class ISession : public std::enable_shared_from_this<ISession> {
public:
    virtual ~ISession() = default;
    virtual void start() = 0;
    virtual void read() = 0;
    virtual void write(const std::string& data) = 0;
};

} // namespace gh