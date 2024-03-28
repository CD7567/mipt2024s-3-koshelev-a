#ifndef MIPT2024S_3_KOSHELEV_A_STACKARRTEXCEPTION_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKARRTEXCEPTION_HPP

#include <exception>

class StackArrTException final : public std::exception {
  private:
    const char* message_;

  public:
    explicit StackArrTException(const char* msg);

    [[nodiscard]] const char* what() const noexcept override;
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKARRTEXCEPTION_HPP
