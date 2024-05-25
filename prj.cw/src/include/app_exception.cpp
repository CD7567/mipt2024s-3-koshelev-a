#include "app_exception.hpp"

namespace cw {

AppException::AppException(const char *message) : message(message) {}

const char *AppException::what() const noexcept { return message; }

}  // namespace cw
