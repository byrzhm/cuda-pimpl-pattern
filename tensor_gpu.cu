#include "tensor_impl.h"

#include <cuda_runtime.h>

#include <iostream>
#include <vector>

__global__ void fill_kernel(float *data, int n, float value) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < n)
    data[idx] = value;
}

__global__ void add_kernel(float *a, const float *b, int n) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx < n)
    a[idx] += b[idx];
}

struct TensorGPUImpl : TensorImplBase {
  float *data;
  int size;

  TensorGPUImpl(int n) : size(n) { cudaMalloc(&data, n * sizeof(float)); }

  ~TensorGPUImpl() override { cudaFree(data); }

  void fill(float value) override {
    int threads = 128;
    int blocks = (size + threads - 1) / threads;
    fill_kernel<<<blocks, threads>>>(data, size, value);
    cudaDeviceSynchronize();
  }

  void add(const TensorImplBase &other) override {
    const auto &rhs = dynamic_cast<const TensorGPUImpl &>(other);
    int threads = 128;
    int blocks = (size + threads - 1) / threads;
    add_kernel<<<blocks, threads>>>(data, rhs.data, size);
    cudaDeviceSynchronize();
  }

  void print() const override {
    std::vector<float> host(size);
    cudaMemcpy(host.data(), data, size * sizeof(float), cudaMemcpyDeviceToHost);
    for (auto v : host)
      std::cout << v << " ";
    std::cout << "\n";
  }
};

std::unique_ptr<TensorImplBase> make_gpu_tensor(int size) {
  return std::make_unique<TensorGPUImpl>(size);
}

