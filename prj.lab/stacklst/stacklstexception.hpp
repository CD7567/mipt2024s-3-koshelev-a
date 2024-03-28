#ifndef MIPT2024S_3_KOSHELEV_A_STACKARREXCEPTION_H
#define MIPT2024S_3_KOSHELEV_A_STACKARREXCEPTION_H

#include <exception>

class StackLstException final : public std::exception {
  private:
    const char* message_;

  public:
    explicit StackLstException(const char* msg);

    [[nodiscard]] const char* what() const noexcept override;
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKARREXCEPTION_H
