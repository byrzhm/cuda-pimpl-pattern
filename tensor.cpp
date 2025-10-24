#include "tensor.h"
#include "tensor_impl.h"

struct Tensor::Impl {
  std::unique_ptr<TensorImplBase> impl;
  Impl(int size, DeviceType device);
};

Tensor::Impl::Impl(int size, DeviceType device) {
  if (device == DeviceType::CPU)
    impl = make_cpu_tensor(size);
  else
    impl = make_gpu_tensor(size);
}

Tensor::Tensor(int size, DeviceType device)
    : pimpl(std::make_unique<Impl>(size, device)) {}

Tensor::~Tensor() = default;

void Tensor::fill(float value) { pimpl->impl->fill(value); }
void Tensor::add(const Tensor &other) { pimpl->impl->add(*other.pimpl->impl); }
void Tensor::print() const { pimpl->impl->print(); }

