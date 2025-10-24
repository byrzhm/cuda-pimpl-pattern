#pragma once

#include <memory>

enum class DeviceType { CPU, GPU };

class Tensor {
public:
  Tensor(int size, DeviceType device);
  ~Tensor();

  void fill(float value);
  void add(const Tensor &other);
  void print() const;

private:
  struct Impl;
  std::unique_ptr<Impl> pimpl;
};

