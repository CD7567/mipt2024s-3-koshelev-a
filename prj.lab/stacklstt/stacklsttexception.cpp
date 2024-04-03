#include "stacklsttexception.hpp"

StackLstTException::StackLstTException(const char* msg) : message_(msg) {}

const char* StackLstTException::what() const noexcept { return message_; }
