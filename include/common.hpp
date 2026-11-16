#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(__CUDACC__) || __has_include(<cuda_runtime.h>)
#include <cuda_runtime.h>
#define CUDA_CHECK(call)                                                       \
    do {                                                                       \
        cudaError_t err__ = (call);                                            \
        if (err__ != cudaSuccess) {                                            \
            std::fprintf(stderr, "CUDA Error at %s:%d -> %s (%d)\n",           \
                         __FILE__, __LINE__, cudaGetErrorString(err__),        \
                         static_cast<int>(err__));                             \
            std::exit(EXIT_FAILURE);                                           \
        }                                                                      \
    } while (0)
#endif

/**
 * @brief Tập dữ liệu đa chiều N điểm x D chiều (row-major).
 *
 * Giao ước định dạng tệp nhị phân (.bin):
 *   - 4 byte đầu: int32_t N (số điểm / số khách hàng)
 *   - 4 byte tiếp: int32_t D (số chiều đặc trưng)
 *   - N * D * 4 byte tiếp theo: mảng float (32-bit, little-endian, row-major)
 */
struct Dataset {
    int N = 0;
    int D = 0;
    std::vector<float> data;

    inline const float* point(int idx) const {
        return &data[static_cast<std::size_t>(idx) * D];
    }

    inline float* point(int idx) {
        return &data[static_cast<std::size_t>(idx) * D];
    }
};

/**
 * @brief Đọc dữ liệu nhị phân .bin theo giao ước chung giữa Python và C++/CUDA.
 */
inline Dataset load_dataset_bin(const std::string& filepath) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Khong the mo tep du lieu: " + filepath);
    }

    int32_t n = 0;
    int32_t d = 0;
    in.read(reinterpret_cast<char*>(&n), sizeof(int32_t));
    in.read(reinterpret_cast<char*>(&d), sizeof(int32_t));
    if (!in || n <= 0 || d <= 0) {
        throw std::runtime_error("Header tep .bin khong hop le: " + filepath);
    }

    Dataset ds;
    ds.N = static_cast<int>(n);
    ds.D = static_cast<int>(d);
    const std::size_t total = static_cast<std::size_t>(ds.N) * ds.D;
    ds.data.resize(total);

    in.read(reinterpret_cast<char*>(ds.data.data()),
            static_cast<std::streamsize>(total * sizeof(float)));
    if (!in) {
        throw std::runtime_error("Du lieu trong tep .bin bi thieu: " + filepath);
    }
    return ds;
}

/**
 * @brief Ghi tập dữ liệu ra tệp nhị phân .bin.
 */
inline void save_dataset_bin(const std::string& filepath, const Dataset& ds) {
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Khong the tao tep du lieu: " + filepath);
    }
    const int32_t n = static_cast<int32_t>(ds.N);
    const int32_t d = static_cast<int32_t>(ds.D);
    out.write(reinterpret_cast<const char*>(&n), sizeof(int32_t));
    out.write(reinterpret_cast<const char*>(&d), sizeof(int32_t));
    out.write(reinterpret_cast<const char*>(ds.data.data()),
              static_cast<std::streamsize>(ds.data.size() * sizeof(float)));
}

/**
 * @brief Tính tổng bình phương sai số nội cụm (SSE / Inertia) trên CPU để kiểm chứng.
 */
inline double compute_sse_cpu(const std::vector<float>& data,
                              const std::vector<float>& centroids,
                              const std::vector<int>& labels,
                              int N, int D, int K) {
    double sse = 0.0;
    for (int i = 0; i < N; ++i) {
        const int c = labels[i];
        if (c < 0 || c >= K) {
            continue;
        }
        const float* p = &data[static_cast<std::size_t>(i) * D];
        const float* mu = &centroids[static_cast<std::size_t>(c) * D];
        double dist_sq = 0.0;
        for (int j = 0; j < D; ++j) {
            const double diff = static_cast<double>(p[j]) - static_cast<double>(mu[j]);
            dist_sq += diff * diff;
        }
        sse += dist_sq;
    }
    return sse;
}
