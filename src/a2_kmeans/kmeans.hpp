#pragma once

#include <string>
#include <vector>

#include "common.hpp"
#include "timer.hpp"

/**
 * @brief Phương pháp khởi tạo tâm cụm ban đầu.
 */
enum class InitMethod {
    RANDOM,
    KMEANS_PP
};

/**
 * @brief Phương án thực thi thuật toán K-means.
 */
enum class KMeansBackend {
    CPU,          // Tuần tự CPU (Thành viên 1)
    CUDA_ATOMIC,  // GPU CUDA cập nhật tâm bằng Global Memory atomicAdd (Thành viên 2)
    CUDA_SHMEM    // GPU CUDA cập nhật tâm bằng Shared Memory + Reduction (Thành viên 2)
};

/**
 * @brief Cấu hình chạy K-means.
 */
struct KMeansConfig {
    int K = 8;                                   // Số cụm (phân khúc khách hàng)
    int max_iters = 100;                         // Số vòng lặp tối đa
    float tol = 1e-4f;                           // Ngưỡng dịch chuyển tâm để dừng hội tụ
    int block_size = 256;                        // Kích thước CUDA block (128, 256, 512)
    unsigned int seed = 42;                      // Seed tái lập ngẫu nhiên
    InitMethod init_method = InitMethod::RANDOM; // Random hoặc K-means++
    KMeansBackend backend = KMeansBackend::CPU;  // CPU, CUDA_ATOMIC hoặc CUDA_SHMEM
};

/**
 * @brief Kết quả đầu ra chuẩn của thuật toán K-means.
 */
struct KMeansResult {
    std::vector<float> centroids; // Kích thước K * D (row-major)
    std::vector<int> labels;      // Kích thước N (chỉ số cụm 0..K-1 cho từng điểm)
    int iters = 0;                // Số vòng lặp thực tế đến khi hội tụ
    double sse = 0.0;             // Tổng bình phương sai số nội cụm (Inertia)
    TimingBreakdown timing;       // Thời gian chi tiết từng pha (ms)
};

inline std::string to_string(InitMethod m) {
    return (m == InitMethod::RANDOM) ? "random" : "kmeans++";
}

inline std::string to_string(KMeansBackend b) {
    switch (b) {
        case KMeansBackend::CPU:         return "cpu";
        case KMeansBackend::CUDA_ATOMIC: return "cuda_atomic";
        case KMeansBackend::CUDA_SHMEM:  return "cuda_shmem";
    }
    return "unknown";
}

// ============================================================================
// Giao ước hàm (Thành viên 1 & Thành viên 2 cài đặt tương ứng ở các file .cpp/.cu)
// ============================================================================

/**
 * @brief Khởi tạo K tâm cụm ngẫu nhiên (Thành viên 2 cài đặt trong kmeans_init.cu).
 * @param centroids Vector đầu ra kích thước K * ds.D.
 */
void init_centroids_random(const Dataset& ds, int K, unsigned int seed,
                           std::vector<float>& centroids);

/**
 * @brief Khởi tạo K tâm cụm theo thuật toán K-means++ (Thành viên 2 cài đặt trong kmeans_init.cu).
 * @param centroids Vector đầu ra kích thước K * ds.D.
 */
void init_centroids_kmeans_pp(const Dataset& ds, int K, unsigned int seed,
                              std::vector<float>& centroids);

/**
 * @brief Chạy K-means tuần tự trên CPU (Thành viên 1 cài đặt trong kmeans_cpu.cpp).
 */
KMeansResult run_kmeans_cpu(const Dataset& ds, const KMeansConfig& cfg);

/**
 * @brief Chạy K-means song song CUDA dùng Global Memory atomicAdd
 *        (Thành viên 2 cài đặt trong kmeans_cuda_atomic.cu).
 */
KMeansResult run_kmeans_cuda_atomic(const Dataset& ds, const KMeansConfig& cfg);

/**
 * @brief Chạy K-means song song CUDA dùng Shared Memory cục bộ + Reduction
 *        (Thành viên 2 cài đặt trong kmeans_cuda_shmem.cu).
 */
KMeansResult run_kmeans_cuda_shmem(const Dataset& ds, const KMeansConfig& cfg);

/**
 * @brief Giao ước dòng CSV chuẩn in ra stdout để script run_benchmark.py thu thập:
 * Header:
 *   algo,init,N,D,K,block_size,io_ms,init_ms,h2d_ms,compute_ms,d2h_ms,total_ms,iters,sse
 */
inline void print_kmeans_csv_header() {
    std::cout << "algo,init,N,D,K,block_size,io_ms,init_ms,h2d_ms,compute_ms,d2h_ms,total_ms,iters,sse\n";
}

inline void print_kmeans_csv_row(const Dataset& ds, const KMeansConfig& cfg,
                                 const KMeansResult& res) {
    std::cout << to_string(cfg.backend) << ","
              << to_string(cfg.init_method) << ","
              << ds.N << ","
              << ds.D << ","
              << cfg.K << ","
              << cfg.block_size << ","
              << std::fixed << std::setprecision(4)
              << res.timing.io_ms << ","
              << res.timing.init_ms << ","
              << res.timing.h2d_ms << ","
              << res.timing.compute_ms << ","
              << res.timing.d2h_ms << ","
              << res.timing.total_ms() << ","
              << res.iters << ","
              << std::setprecision(6) << res.sse << "\n";
}
