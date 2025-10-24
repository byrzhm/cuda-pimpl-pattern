#include "tensor.h"

int main() {
  Tensor cpu_a(5, DeviceType::CPU);
  Tensor cpu_b(5, DeviceType::CPU);

  cpu_a.fill(1.0f);
  cpu_b.fill(2.0f);
  cpu_a.add(cpu_b);
  cpu_a.print(); // CPU result

  Tensor gpu_a(5, DeviceType::GPU);
  Tensor gpu_b(5, DeviceType::GPU);

  gpu_a.fill(1.0f);
  gpu_b.fill(2.0f);
  gpu_a.add(gpu_b);
  gpu_a.print(); // GPU result (copied back)
}

