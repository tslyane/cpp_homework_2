#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

template <typename T, int Cap>
class Registry {
 private:
  std::vector<T> items_;

 public:
  bool add(T elem);
  std::size_t size() const;
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;
  bool remove(std::size_t index);
  int find(const std::string& id) const;
};

template <typename T, int Cap>
bool Registry<T, Cap>::add(T elem) {
  if (items_.size() >= Cap) {
    return false;
  }
  std::size_t left = 0;
  std::size_t right = items_.size();
  while (left < right) {
    std::size_t mid = left + (right - left) / 2;
    if (*items_[mid] < *elem) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  items_.insert(items_.begin() + left, std::move(elem));
  return true;
}

template <typename T, int Cap>
std::size_t Registry<T, Cap>::size() const {
  return items_.size();
}

template <typename T, int Cap>
T& Registry<T, Cap>::operator[](std::size_t index) {
  return items_[index];
}

template <typename T, int Cap>
const T& Registry<T, Cap>::operator[](std::size_t index) const {
  return items_[index];
}

template <typename T, int Cap>
bool Registry<T, Cap>::remove(std::size_t index) {
  if (items_.size() <= index) {
    return false;
  }
  items_.erase(items_.begin() + index);
  return true;
}

template <typename T, int Cap>
int Registry<T, Cap>::find(const std::string& id) const {
  int left = 0;
  int right = static_cast<int>(items_.size());
  while (left < right) {
    int mid = left + (right - left) / 2;
    if (items_[mid]->inventoryId() < id) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  if (left < static_cast<int>(items_.size()) &&
      items_[left]->inventoryId() == id) {
    return left;
  }
  return -1;
}