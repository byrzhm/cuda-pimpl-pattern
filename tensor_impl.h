#pragma once

#include <memory>

struct TensorImplBase {
  virtual ~TensorImplBase() = default;

  virtual void fill(float value) = 0;
  virtual void add(const TensorImplBase &other) = 0;
  virtual void print() const = 0;
};

// Declare factory functions (implemented in .cpp/.cu)
std::unique_ptr<TensorImplBase> make_cpu_tensor(int size);
std::unique_ptr<TensorImplBase> make_gpu_tensor(int size);

