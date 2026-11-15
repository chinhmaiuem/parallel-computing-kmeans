# ==============================================================================
# Makefile - Đồ án Lập trình Tính toán Song song
# Bài A1: Tích vô hướng 2 vector (CPU & CUDA)
# Bài A2 (Chủ đề 6): K-means song song (CPU, CUDA atomicAdd & Shared Memory)
# ==============================================================================

CXX      := g++
NVCC     := nvcc

# Kiến trúc GPU mặc định: sm_75 (NVIDIA Tesla T4 trên Google Colab)
# Có thể ghi đè khi gọi: make ARCH=sm_80
ARCH     ?= sm_75

CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Iinclude
NVCCFLAGS:= -std=c++17 -O3 -arch=$(ARCH) -Iinclude --use_fast_math

BUILD_DIR := build
BIN_DIR   := $(BUILD_DIR)/bin

# Nguồn Bài A1
A1_SRCS := src/a1_dot_product/dot_cpu.cpp \
           src/a1_dot_product/dot_cuda.cu \
           src/a1_dot_product/main_dot.cu
A1_BIN  := $(BIN_DIR)/a1_dot

# Nguồn Bài A2
A2_SRCS := src/a2_kmeans/kmeans_cpu.cpp \
           src/a2_kmeans/kmeans_init.cu \
           src/a2_kmeans/kmeans_cuda_atomic.cu \
           src/a2_kmeans/kmeans_cuda_shmem.cu \
           src/a2_kmeans/main_kmeans.cu
A2_BIN  := $(BIN_DIR)/a2_kmeans

.PHONY: all a1 a2 directories test clean help

all: directories a1 a2

directories:
	@mkdir -p $(BIN_DIR)

a1: directories $(A1_BIN)

a2: directories $(A2_BIN)

$(A1_BIN): $(A1_SRCS)
	$(NVCC) $(NVCCFLAGS) $(A1_SRCS) -o $(A1_BIN)

$(A2_BIN): $(A2_SRCS)
	$(NVCC) $(NVCCFLAGS) $(A2_SRCS) -o $(A2_BIN)

test: all
	python3 tests/test_correctness.py

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Các lệnh hỗ trợ:"
	@echo "  make all [ARCH=sm_75]  - Biên dịch cả Bài A1 và Bài A2"
	@echo "  make a1                - Biên dịch Bài A1 (Tích vô hướng)"
	@echo "  make a2                - Biên dịch Bài A2 (K-means)"
	@echo "  make test              - Chạy bộ kiểm thử độ chính xác"
	@echo "  make clean             - Xóa thư mục build/"
