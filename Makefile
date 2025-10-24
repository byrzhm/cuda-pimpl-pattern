CXX := g++-13
NVCC := nvcc
CXXFLAGS := -std=c++17 -O2
NVCCFLAGS := -std=c++17 -O2 -arch=sm_80 -ccbin $(CXX)
TARGET := pimpl_cuda

SRCS_CPP := tensor.cpp tensor_cpu.cpp main.cpp
SRCS_CU  := tensor_gpu.cu

OBJS_CPP := $(SRCS_CPP:.cpp=.o)
OBJS_CU  := $(SRCS_CU:.cu=.o)

all: $(TARGET)

$(TARGET): $(OBJS_CPP) $(OBJS_CU)
	$(NVCC) -o $@ $^ $(NVCCFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CPP) $(OBJS_CU) $(TARGET)

