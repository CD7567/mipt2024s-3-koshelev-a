#include "stackarrtexception.hpp"

StackArrTException::StackArrTException(const char* msg) : message_(msg) {}

const char* StackArrTException::what() const noexcept { return message_; }
