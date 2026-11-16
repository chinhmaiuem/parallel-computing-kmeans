# Nhật ký Công khai Sử dụng AI (AI_USAGE)

Tài liệu này ghi nhận trung thực việc sử dụng các công cụ Trí tuệ Nhân tạo (AI) trong quá trình thực hiện đồ án môn **Lập trình tính toán song song**.

## Lịch sử

### 1
- **Thời gian:** 2026-11-15
- **Người sử dụng:** Nhóm thực hiện (Thành viên 1, 2, 3)
- **Công cụ/mô hình:** Antigravity (Google DeepMind)
- **Mục đích:** Lập kế hoạch triển khai dự án theo lộ trình 8 tuần, đề xuất cấu trúc thư mục GitHub và khởi tạo các tệp khung nền tảng (`Makefile`, `README.md`, `CONTRIBUTIONS.md`, `AI_USAGE.md`).
- **Prompt hoặc tóm tắt prompt:** Yêu cầu lập Implementation Plan chi tiết cho Bài A1 (tích vô hướng 2 vector) và Bài A2 (K-means song song CUDA với `atomicAdd` và `Shared Memory`), phân công công việc 3 thành viên tránh xung đột Git và tạo sẵn 4 file khung.
- **Kết quả:** Tạo được tài liệu kế hoạch `implementation_plan.md` và 4 file khung ban đầu trong thư mục dự án.
- **Phần đã sử dụng:** Toàn bộ cấu trúc thư mục đề xuất, mẫu `Makefile` biên dịch `C++17`/`nvcc`, khung `README.md`, `CONTRIBUTIONS.md` và mẫu `AI_USAGE.md`.
- **Chỉnh sửa của nhóm:** *(Nhóm cập nhật thông tin thành viên, MSSV, URL GitHub và thông số phần cứng Colab thực tế sau khi chạy thực nghiệm).*
- **Kiểm chứng:** Đã kiểm tra cú pháp `Makefile` (định dạng Tab cho các target), đối chiếu các mục bắt buộc trong file đề bài `Chu de NHOM 2026-1 v1s (1).docx`.
- **Commit/issue liên quan:** *(Cập nhật mã commit khởi tạo repo sau khi push lên GitHub).*

<!--
### 2 (Mẫu cho các lần sử dụng tiếp theo - bỏ comment khi dùng)
- **Thời gian:** YYYY-MM-DD
- **Người sử dụng:** [Tên thành viên]
- **Công cụ/mô hình:** [Tên công cụ/mô hình]
- **Mục đích:** [Tra cứu khái niệm / Gợi ý test / Giải thích lỗi / Tối ưu hóa...]
- **Prompt hoặc tóm tắt prompt:** [Nội dung tóm tắt]
- **Kết quả:** [Mô tả ngắn kết quả AI trả về]
- **Phần đã sử dụng:** [Đoạn mã / ý tưởng được giữ lại]
- **Chỉnh sửa của nhóm:** [Những chỗ nhóm đã sửa, tối ưu hoặc viết lại]
- **Kiểm chứng:** [Cách test, đo đạc, kiểm tra race condition / sai số]
- **Commit/issue liên quan:** [Mã commit hoặc số PR/issue]
-->

## Tuyên bố
Nhóm chịu trách nhiệm về tính đúng đắn, bản quyền, số liệu thực nghiệm và mọi nội dung đã nộp.
# Nhật ký Sử dụng Công cụ AI (AI Usage Log)

> **Quy tắc chung để tránh xung đột Git (Merge Conflict):** 
> Mỗi thành viên **chỉ chỉnh sửa và thêm dòng vào đúng bảng mang tên mình** bên dưới. Không chỉnh sửa phần tiêu đề chung hoặc bảng của thành viên khác.

---

## 1. Nhật ký của Thành viên 1: Nguyễn Đình Chính (`chinhmaiuem`)
* **Phạm vi phụ trách:** Kiến trúc PCAM, Khung Header & `Makefile`, Bài A1 (Tích vô hướng CPU/CUDA), K-means tuần tự CPU (`kmeans_cpu.cpp`), Unit Test kiểm thử tính đúng đắn.

| Ngày | Công cụ AI sử dụng | Tác vụ / Mục đích hỗ trợ | Phần code / File áp dụng | Cách kiểm chứng & Chỉnh sửa thủ công |
| :--- | :--- | :--- | :--- | :--- |
| 16/11/2026 | Gemini | Thiết kế cấu trúc Repo, phân chia vai trò nhóm và khung kế hoạch 8 tuần theo chuẩn PCAM | `README.md`, `CONTRIBUTIONS.md`, `AI_USAGE.md` | Rà soát lại danh sách file, chỉnh sửa thông tin thành viên và luồng nhánh Git `dev`/`main`. |
| *(Thêm dòng mới tại đây)* | | | | |

---

## 2. Nhật ký của Thành viên 2: [Họ tên Thành viên 2] (`@[github_tv2]`)
* **Phạm vi phụ trách:** Khởi tạo tâm K-means++ (`kmeans_init.cu`), các biến thể CUDA K-means (`kmeans_cuda_atomic.cu`, `kmeans_cuda_shmem.cu`), đo thời gian 4 pha (`main_kmeans.cu`).

| Ngày | Công cụ AI sử dụng | Tác vụ / Mục đích hỗ trợ | Phần code / File áp dụng | Cách kiểm chứng & Chỉnh sửa thủ công |
| :--- | :--- | :--- | :--- | :--- |
| *(Thêm dòng mới tại đây)* | | | | |

---

## 3. Nhật ký của Thành viên 3: [Họ tên Thành viên 3] (`@[github_tv3]`)
* **Phạm vi phụ trách:** Script sinh dữ liệu (`generate_data.py`), script chạy benchmark tự động trên Colab T4 (`run_benchmark.py`), vẽ biểu đồ (`plot_results.py`), Báo cáo LaTeX & Slide.

| Ngày | Công cụ AI sử dụng | Tác vụ / Mục đích hỗ trợ | Phần code / File áp dụng | Cách kiểm chứng & Chỉnh sửa thủ công |
| :--- | :--- | :--- | :--- | :--- |
| *(Thêm dòng mới tại đây)* | | | | |