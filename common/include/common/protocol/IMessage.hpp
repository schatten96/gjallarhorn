#pragma once

namespace gh::core {

class IMessage {
public:
    enum class Type { Text, Image };

    virtual ~IMessage() = default;
    virtual Type type() const noexcept = 0;

    template <typename T>
    T*
    as() {
        return type() == T::MessageType ? static_cast<T*>(this) : nullptr;
    }
};

} // namespace gh::core
