#ifndef MIPT2024S_3_KOSHELEV_A_STACKLSTTEXCEPTION_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKLSTTEXCEPTION_HPP

#include <exception>

class StackLstTException final : public std::exception {
  private:
    const char* message_;

  public:
    explicit StackLstTException(const char* msg);

    [[nodiscard]] const char* what() const noexcept override;
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKLSTTEXCEPTION_HPP
