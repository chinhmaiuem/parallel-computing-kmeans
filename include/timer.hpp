#pragma once

#include <chrono>

#if defined(__CUDACC__) || __has_include(<cuda_runtime.h>)
#include "common.hpp"
#endif

/**
 * @brief Cấu trúc lưu thời gian tách bạch từng phân đoạn (đơn vị: ms).
 */
struct TimingBreakdown {
    double io_ms = 0.0;       // Thời gian đọc/ghi file
    double init_ms = 0.0;     // Thời gian khởi tạo dữ liệu / khởi tạo tâm (Random, K-means++)
    double h2d_ms = 0.0;      // Thời gian truyền dữ liệu Host -> Device
    double compute_ms = 0.0;  // Thời gian tính toán thuần (CPU loop hoặc CUDA kernels)
    double d2h_ms = 0.0;      // Thời gian truyền dữ liệu Device -> Host

    double total_ms() const {
        return io_ms + init_ms + h2d_ms + compute_ms + d2h_ms;
    }

    double transfer_ms() const {
        return h2d_ms + d2h_ms;
    }
};

/**
 * @brief Bộ đếm thời gian trên CPU dùng std::chrono::steady_clock.
 */
class CpuTimer {
public:
    void start() {
        t_start_ = std::chrono::steady_clock::now();
    }

    void stop() {
        t_end_ = std::chrono::steady_clock::now();
    }

    double elapsed_ms() const {
        const std::chrono::duration<double, std::milli> diff = t_end_ - t_start_;
        return diff.count();
    }

private:
    std::chrono::steady_clock::time_point t_start_{};
    std::chrono::steady_clock::time_point t_end_{};
};

#if defined(__CUDACC__) || __has_include(<cuda_runtime.h>)
/**
 * @brief Bộ đếm thời gian chính xác trên GPU dùng cudaEvent_t.
 */
class GpuTimer {
public:
    GpuTimer() {
        CUDA_CHECK(cudaEventCreate(&start_event_));
        CUDA_CHECK(cudaEventCreate(&stop_event_));
    }

    ~GpuTimer() {
        if (start_event_) cudaEventDestroy(start_event_);
        if (stop_event_) cudaEventDestroy(stop_event_);
    }

    GpuTimer(const GpuTimer&) = delete;
    GpuTimer& operator=(const GpuTimer&) = delete;

    void start(cudaStream_t stream = 0) {
        CUDA_CHECK(cudaEventRecord(start_event_, stream));
    }

    void stop(cudaStream_t stream = 0) {
        CUDA_CHECK(cudaEventRecord(stop_event_, stream));
        CUDA_CHECK(cudaEventSynchronize(stop_event_));
    }

    double elapsed_ms() const {
        float ms = 0.0f;
        CUDA_CHECK(cudaEventElapsedTime(&ms, start_event_, stop_event_));
        return static_cast<double>(ms);
    }

private:
    cudaEvent_t start_event_ = nullptr;
    cudaEvent_t stop_event_ = nullptr;
};
#endif
