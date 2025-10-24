#include "tensor_impl.h"
#include <iostream>
#include <vector>

struct TensorCPUImpl : TensorImplBase {
  std::vector<float> data;

  TensorCPUImpl(int size) : data(size) {}

  void fill(float value) override {
    std::fill(data.begin(), data.end(), value);
  }

  void add(const TensorImplBase &other) override {
    const auto &rhs = dynamic_cast<const TensorCPUImpl &>(other);
    for (size_t i = 0; i < data.size(); ++i)
      data[i] += rhs.data[i];
  }

  void print() const override {
    for (auto v : data)
      std::cout << v << " ";
    std::cout << "\n";
  }
};

std::unique_ptr<TensorImplBase> make_cpu_tensor(int size) {
  return std::make_unique<TensorCPUImpl>(size);
}

