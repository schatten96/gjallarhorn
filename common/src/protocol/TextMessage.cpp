#include "common/protocol/TextMessage.hpp"

namespace gh::core {

TextMessage::TextMessage(const std::string& text)
    : mText(text) {
}

IMessage::Type
TextMessage::type() const noexcept {
    return TextMessage::MessageType;
}

const std::string&
TextMessage::text() const {
    return mText;
}

} // namespace gh::core