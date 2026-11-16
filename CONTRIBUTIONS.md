# Bảng Phân công Nhiệm vụ Thành viên (CONTRIBUTIONS)

## 1. Thông tin Nhóm & Đề tài
- **Môn học:** Lập trình tính toán song song
- **Chủ đề ứng dụng:** **Phân khúc hành vi khách hàng Thương mại điện tử (Customer Segmentation)** trên GPU CUDA
  - **Bài A1 (Chung):** Tính tích vô hướng của 2 vector đặc trưng kích thước lớn (CPU tuần tự vs CUDA Shared Memory Reduction).
  - **Bài A2 (Riêng - Chủ đề 6):** Phân cụm K-means song song cho dữ liệu hành vi khách hàng ($N = 10^4, 10^5, 10^6$ khách hàng, đa chiều đặc trưng $D$, số phân khúc $K$) với 2 cách khởi tạo (**Random**, **K-means++**) và 2 phương án xử lý race condition (**Global Memory `atomicAdd`** vs **Shared Memory + Reduction**).

## 2. Phân công Vai trò & Nhiệm vụ

| STT | Họ và Tên | MSSV | Tài khoản GitHub | Vai trò chính | Nhánh Git phụ trách | Nhiệm vụ & Sản phẩm phụ trách |
| :---: | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | Nguyễn Đình Chính | 20237306 | `chinhmaiuem` | **Nhóm trưởng, Kiến trúc PCAM & Bài A1** | `feat/a1-and-baseline`, `docs/pcam` | - Quản lý Repo GitHub, duyệt Pull Request vào `dev`/`main`, theo dõi tiến độ trên GitHub Projects.<br>- Viết khung header giao ước (`include/common.hpp`, `include/timer.hpp`, `src/a2_kmeans/kmeans.hpp`) và `Makefile`.<br>- Thiết kế sơ đồ 4 bước **PCAM** (Draw.io) cho Bài A1 và Bài A2.<br>- Cài đặt trọn vẹn **Bài A1** (CPU `C++17` + CUDA) và **K-means tuần tự CPU** (`kmeans_cpu.cpp`).<br>- Viết bộ Unit Test (`tests/test_correctness.py`) đối chiếu tâm cụm & SSE giữa CPU, CUDA và `scikit-learn`. |
| 2 | *[Thành viên 2]* | *[MSSV]* | `@[github_tv2]` | **Phụ trách CUDA & Tối ưu hóa (Bài A2)** | `feat/a2-cuda-kernels` | - Cài đặt 2 phương pháp khởi tạo tâm: **Random** và **K-means++** (`kmeans_init.cu`).<br>- Cài đặt K-means song song CUDA biến thể **Global Memory `atomicAdd`** (`kmeans_cuda_atomic.cu`).<br>- Cài đặt K-means song song CUDA biến thể **Shared Memory cục bộ + Reduction** (`kmeans_cuda_shmem.cu`).<br>- Tích hợp đo thời gian tách bạch 4 pha (`I/O`, `Init`, `H2D/D2H`, `Kernel Compute`) bằng `cudaEvent` & `std::chrono` trong `main_kmeans.cu`. |
| 3 | *[Thành viên 3]* | *[MSSV]* | `@[github_tv3]` | *Phụ trách Dữ liệu, Benchmark & Tài liệu** | `feat/data-benchmark`, `docs/report` | - Viết script sinh dữ liệu tổng hợp mô phỏng **hành vi khách hàng** (RFM / đa chiều) ở 3 quy mô $10^4, 10^5, 10^6$ khách hàng xuất ra `.bin` (`scripts/generate_data.py`).<br>- Viết script chạy thực nghiệm tự động $\ge 5$ lần/cấu hình trên Google Colab T4, xuất `.csv` (`scripts/run_benchmark.py`).<br>- Viết script tính thống kê (**Median, Min-Max, IQR**) và vẽ biểu đồ Speedup, Efficiency, phân rã thời gian, SSE (`scripts/plot_results.py`).<br>- Hoàn thiện Notebook Colab, `README.md`, `AI_USAGE.md`, Báo cáo LaTeX & Slide thuyết trình. |

> **Ghi chú:** Các thành viên cập nhật đầy đủ Họ tên, MSSV, tài khoản GitHub và ghi nhận lịch sử commit có ý nghĩa trên nhánh riêng trước khi tạo Pull Request vào `dev`.
