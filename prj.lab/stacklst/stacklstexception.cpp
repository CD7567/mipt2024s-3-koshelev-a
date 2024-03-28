#include "stacklstexception.hpp"

StackLstException::StackLstException(const char* msg) : message_(msg) {}

const char* StackLstException::what() const noexcept { return message_; }
