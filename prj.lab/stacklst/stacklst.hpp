#ifndef MIPT2024S_3_KOSHELEV_A_STACKLST_HPP
#define MIPT2024S_3_KOSHELEV_A_STACKLST_HPP

#include <algorithm>
#include <cstddef>

#include "stacklstexception.hpp"

class StackLst final {
  private:
    struct Node {
        float elem_;
        Node* prev_;
    };

    Node* top_ = nullptr;
    size_t size_ = 0;

  public:
    /*
     * Constructors & destructors
     */

    StackLst() = default;

    StackLst(const StackLst& other);

    StackLst(StackLst&& other) noexcept;

    ~StackLst();

    /*
     * Operators
     */

    auto& operator=(const StackLst& other);

    auto& operator=(StackLst&& other) noexcept;

    /*
     * Member functions
     */

    [[nodiscard]] bool IsEmpty() const noexcept;

    [[nodiscard]] std::size_t Size() const noexcept;

    [[nodiscard]] float& Top();

    [[nodiscard]] const float& Top() const;

    void Push(const float& elem);

    void Pop();
};

#endif  // MIPT2024S_3_KOSHELEV_A_STACKLST_HPP
