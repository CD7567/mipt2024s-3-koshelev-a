#include "app_exception.hpp"

AppException::AppException(const char *message) : message(message) {}

const char *AppException::what() const noexcept { return message; }