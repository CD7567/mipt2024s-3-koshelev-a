#ifndef MIPT2024S_3_KOSHELEV_A_APP_EXCEPTION_HPP
#define MIPT2024S_3_KOSHELEV_A_APP_EXCEPTION_HPP

#include <exception>

class AppException : std::exception {
  private:
    const char* message;

  public:
    AppException(const char* message);

    const char* what() const noexcept override;
};

#endif  // MIPT2024S_3_KOSHELEV_A_APP_EXCEPTION_HPP
