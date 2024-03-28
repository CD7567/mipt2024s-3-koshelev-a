#include "stackarrexception.hpp"

StackArrException::StackArrException(const char* msg) : message_(msg) {}

const char* StackArrException::what() const noexcept { return message_; }
