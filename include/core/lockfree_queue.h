#pragma once
#include <atomic>
#include <optional>
#include <vector>

// Single Producer / Single Consumer ring buffer

template <typename T, size_t N>
class SPSCQueue {
 public:
  bool push(const T& item) {
    auto next = (head_ + 1) % N;
    if (next == tail_.load(std::memory_order_acquire)) return false;  // full
    buffer_[head_] = item;
    head_ = next;
    return true;
  }

  std::optional<T> pop() {
    auto tail = tail_.load(std::memory_order_relaxed);
    if (tail == head_) return std::nullopt;  // empty

    T item = buffer_[tail];
    tail_.store((tail + 1) % N, std::memory_order_release);
    return item;
  }

 private:
  std::vector<T> buffer_{N};
  size_t head_{0};
  std::atomic<size_t> tail_{0};
};
