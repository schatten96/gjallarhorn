#pragma once

#include "common/protocol/IMessage.hpp"

#include <string>

namespace gh::core {

class TextMessage : public IMessage {
public:
    static constexpr Type MessageType = Type::Text;

    explicit TextMessage(const std::string& text);
    ~TextMessage() override = default;

    Type type() const noexcept override;
    const std::string& text() const;

private:
    std::string mText;
};

} // namespace gh::core
