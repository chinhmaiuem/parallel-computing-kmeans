# Đồ án Lập trình Tính toán Song song

Dự án cài đặt, phân tích thiết kế theo mô hình **PCAM** và đánh giá hiệu năng song song trên **CPU (C++17)** và **GPU (NVIDIA CUDA)** cho 2 bài toán:
1. **Bài A1 (Chung):** Tính tích vô hướng của 2 vector (CPU tuần tự vs CUDA Shared Memory Reduction).
2. **Bài A2 (Riêng - Chủ đề 6):** Thuật toán phân cụm K-means song song:
   - Hỗ trợ 2 phương pháp khởi tạo tâm: **Random** và **K-means++**.
   - Cài đặt và so sánh 2 chiến lược xử lý tranh chấp (race condition) khi cập nhật tâm cụm:
     - `atomicAdd` trực tiếp trên **Global Memory**.
     - Tích lũy cục bộ trên **Shared Memory** rồi **Reduction**.
   - Đo thời gian tách bạch từng giai đoạn: `I/O`, `Init`, `Host-Device Transfer (H2D/D2H)`, và `Kernel Compute`.
   - Đánh giá cả hiệu năng (**Speedup**, **Efficiency**) lẫn chất lượng hội tụ (**SSE/Inertia**, **số vòng lặp**).

---

## 1. Cấu trúc Thư mục

```text
.
├── Makefile                    # Biên dịch C++17 & CUDA (-O3)
├── README.md                   # Hướng dẫn cài đặt & tái lập thí nghiệm
├── CONTRIBUTIONS.md            # Phân công và tỷ lệ đóng góp 3 thành viên
├── AI_USAGE.md                 # Nhật ký công khai sử dụng AI
├── include/                    # Header dùng chung (timer, CUDA_CHECK, I/O .bin)
├── src/
│   ├── a1_dot_product/         # Mã nguồn Bài A1
│   └── a2_kmeans/              # Mã nguồn Bài A2
├── scripts/                    # Script Python sinh dữ liệu, benchmark & vẽ biểu đồ
├── tests/                      # Bộ kiểm thử đối chiếu với scikit-learn
├── notebooks/                  # Notebook chạy trên Google Colab + Drive
├── results/                    # Dữ liệu CSV và biểu đồ kết quả
└── docs/                       # Sơ đồ PCAM (Draw.io), Báo cáo & Slide
```

---

## 2. Môi trường Thực nghiệm (Chỉnh sửa theo máy/Colab thực tế)

| Thành phần | Thông số cấu hình |
| :--- | :--- |
| **Nền tảng chạy** | Google Colab (kết nối Google Drive lưu dữ liệu lớn) |
| **GPU** | NVIDIA Tesla T4 (16 GB GDDR6, Compute Capability `7.5` / `sm_75`) |
| **CPU** | Intel Xeon @ 2.20 GHz (2 vCPU) *(cập nhật theo lệnh `lscpu` trên Colab)* |
| **RAM** | ~12.7 GB *(cập nhật theo lệnh `free -h`)* |
| **Hệ điều hành** | Ubuntu 22.04 LTS (Colab VM) |
| **Compiler & Cờ tối ưu** | `nvcc` (CUDA 12.x), `g++` (C++17), `-O3 -arch=sm_75` |
| **Thư viện Python** | Python 3.10+, `numpy`, `scikit-learn`, `pandas`, `matplotlib`, `seaborn` |

---

## 3. Hướng dẫn Cài đặt & Tái lập Thí nghiệm trên Google Colab

### Bước 1: Kết nối Google Drive và Clone Repository
Trong notebook Google Colab (chọn Runtime -> Change runtime type -> **T4 GPU**):

```bash
# Kiểm tra GPU và phiên bản CUDA
!nvidia-smi
!nvcc --version

# Clone repo
!git clone <URL_REPO_GITHUB_CUA_NHOM>
%cd <TEN_THU_MUC_REPO>
```

### Bước 2: Cài đặt thư viện Python cần thiết
```bash
!pip install -q numpy scikit-learn pandas matplotlib seaborn
```

### Bước 3: Biên dịch mã nguồn C++ / CUDA
```bash
!make clean && make all ARCH=sm_75
```

### Bước 4: Sinh dữ liệu tổng hợp (3 quy mô: $10^4, 10^5, 10^6$ điểm)
```bash
# Lưu dữ liệu nhị phân (.bin) vào Google Drive để tái sử dụng
!python3 scripts/generate_data.py --output-dir /content/drive/MyDrive/parallel_project/data
```

### Bước 5: Kiểm thử độ chính xác (Unit Test)
```bash
!make test
```

### Bước 6: Chạy Benchmark tự động ($\ge 5$ lần/cấu hình) và Vẽ biểu đồ
```bash
!python3 scripts/run_benchmark.py --data-dir /content/drive/MyDrive/parallel_project/data --runs 5 --out results/raw/benchmark.csv
!python3 scripts/plot_results.py --input results/raw/benchmark.csv --out-dir results/figures
```
