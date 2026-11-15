# Bảng Phân công & Đóng góp Thành viên (CONTRIBUTIONS)

## 1. Thông tin Nhóm
- **Môn học:** Lập trình tính toán song song
- **Đề tài:**
  - **Bài A1 (Chung):** Tính tích vô hướng của 2 vector (CPU & CUDA).
  - **Bài A2 (Riêng - Chủ đề 6):** Phân cụm K-means song song trên CUDA (`atomicAdd` vs `Shared Memory`, khởi tạo Random & K-means++).

## 2. Phân công Vai trò & Nhiệm vụ

| STT | Họ và Tên | MSSV | Tài khoản GitHub | Vai trò chính | Nhánh Git phụ trách | Phạm vi công việc & File phụ trách | Tỷ lệ đóng góp (%) |
| :---: | :--- | :--- | :--- | :--- | :--- | :--- | :---: |
| 1 | *[Thành viên 1]* | *[MSSV]* | `@[github_tv1]` | **Nhóm trưởng, Kiến trúc PCAM & Bài A1** | `feat/a1-and-baseline`, `docs/pcam` | - Thiết lập Repo Git, `Makefile`, header `include/common.hpp`, `include/timer.hpp`.<br>- Thiết kế sơ đồ PCAM (Draw.io) cho A1 & A2.<br>- Cài đặt hoàn chỉnh Bài A1 (`src/a1_dot_product/*`).<br>- Cài đặt K-means tuần tự CPU (`src/a2_kmeans/kmeans_cpu.cpp`).<br>- Viết bộ Unit Test đối chiếu với `scikit-learn` (`tests/test_correctness.py`). | 33.3% |
| 2 | *[Thành viên 2]* | *[MSSV]* | `@[github_tv2]` | **Kỹ sư CUDA & Tối ưu hóa (Bài A2)** | `feat/a2-cuda-kernels` | - Cài đặt K-means CUDA biến thể `atomicAdd` (`kmeans_cuda_atomic.cu`).<br>- Cài đặt K-means CUDA biến thể `Shared Memory` + Reduction (`kmeans_cuda_shmem.cu`).<br>- Cài đặt khởi tạo tâm Random & K-means++ (`kmeans_init.cu`).<br>- Tích hợp đo thời gian chi tiết `cudaEvent`/`std::chrono` trong `main_kmeans.cu`. | 33.3% |
| 3 | *[Thành viên 3]* | *[MSSV]* | `@[github_tv3]` | **Kỹ sư Dữ liệu, Benchmark & Báo cáo** | `feat/data-benchmark`, `docs/report` | - Viết script sinh dữ liệu `.bin` 3 kích thước $10^4, 10^5, 10^6$ (`scripts/generate_data.py`).<br>- Viết script chạy benchmark $\ge 5$ lần/cấu hình xuất `.csv` (`scripts/run_benchmark.py`).<br>- Viết script tính Median/Min-Max/IQR và vẽ biểu đồ (`scripts/plot_results.py`).<br>- Quản lý `README.md`, `AI_USAGE.md`, `CONTRIBUTIONS.md`, Notebook Colab, Báo cáo & Slide. | 33.3% |

> **Ghi chú:** Tỷ lệ đóng góp cuối cùng sẽ được cập nhật lại chính xác dựa trên lịch sử commit, Pull Request và mức độ hoàn thành thực tế trước khi nộp đồ án.
