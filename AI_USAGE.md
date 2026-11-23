# Nhật ký Công khai Sử dụng AI (AI_USAGE)

Tài liệu này ghi nhận trung thực việc sử dụng các công cụ Trí tuệ Nhân tạo (AI) trong quá trình thực hiện đồ án môn **Lập trình tính toán song song**.

> **Quy ước ghi nhận khi làm việc song song (tránh xung đột Git):**  
> Trong quá trình phát triển trên các nhánh riêng, từng thành viên ghi nhận lần sử dụng AI vào tệp riêng của mình trong `docs/ai_logs/` (`tv1.md`, `tv2.md`, `tv3.md`) theo đúng 10 mục bắt buộc dưới đây. Trước mỗi đợt chốt mốc / nộp bài, Thành viên 3 tổng hợp toàn bộ vào tệp `AI_USAGE.md` chính thức này.

## Lịch sử

### 1
- **Thời gian:** 2026-11-15 – 2026-11-16
- **Người sử dụng:** Nguyễn Đình Chính (`chinhmaiuem`) — Thành viên 1
- **Công cụ/mô hình:** Antigravity (Google DeepMind) / Gemini
- **Mục đích:** Lập kế hoạch triển khai dự án, thiết kế cấu trúc thư mục GitHub, tạo các tệp khung nền tảng (`Makefile`, `README.md`, `CONTRIBUTIONS.md`, `AI_USAGE.md`, `.gitignore`), hệ thống log AI tách theo thành viên (`docs/ai_logs/`) và 3 tệp header giao ước (`include/common.hpp`, `include/timer.hpp`, `src/a2_kmeans/kmeans.hpp`).
- **Prompt hoặc tóm tắt prompt:** Yêu cầu lập Implementation Plan chi tiết cho Bài A1 (tích vô hướng 2 vector) và Bài A2 (K-means song song CUDA với `atomicAdd` và `Shared Memory` theo chủ đề Phân khúc khách hàng), phân công công việc 3 thành viên tránh xung đột Git và khởi tạo khung dự án + giao ước header.
- **Kết quả:** Tạo được kế hoạch triển khai, bộ tệp khung ban đầu và 3 tệp header định nghĩa cấu trúc tệp nhị phân `.bin`, bộ đo thời gian 4 pha và chữ ký hàm K-means.
- **Phần đã sử dụng:** Cấu trúc thư mục, `Makefile`, khung `README.md`, `CONTRIBUTIONS.md`, `AI_USAGE.md`, `.gitignore`, `docs/ai_logs/tv1..3.md` và 3 tệp header giao ước.
- **Chỉnh sửa của nhóm:** Bổ sung tên, MSSV, tài khoản GitHub của Thành viên 1; chốt chủ đề Phân khúc hành vi khách hàng; bỏ cột tỷ lệ đóng góp; bổ sung hướng dẫn tạo nhánh & quy trình Git trực tiếp vào `README.md`.
- **Kiểm chứng:** Kiểm tra cú pháp Tab của `Makefile`, kiểm tra cú pháp C++17 bằng `g++ -std=c++17 -Wall -Wextra -fsyntax-only` trên 3 tệp header (pass 0 lỗi), đối chiếu đầy đủ các mục bắt buộc trong đề bài `Chu de NHOM 2026-1 v1s (1).docx`.
- **Commit/issue liên quan:** Nhánh `dev` (các commit khởi tạo khung dự án & header giao ước).

<!--
### 2 (Mẫu chuẩn 10 mục cho các lần sử dụng tiếp theo - copy vào docs/ai_logs/tvX.md rồi tổng hợp về đây)
- **Thời gian:** YYYY-MM-DD
- **Người sử dụng:** [Họ tên (GitHub handle)]
- **Công cụ/mô hình:** [Tên công cụ/mô hình]
- **Mục đích:** [Tra cứu khái niệm / Gợi ý test / Giải thích lỗi / Tối ưu hóa...]
- **Prompt hoặc tóm tắt prompt:** [Nội dung tóm tắt]
- **Kết quả:** [Mô tả ngắn kết quả AI trả về]
- **Phần đã sử dụng:** [Đoạn mã / ý tưởng được giữ lại]
- **Chỉnh sửa của nhóm:** [Những chỗ nhóm đã sửa, tối ưu hoặc viết lại]
- **Kiểm chứng:** [Cách test, đo đạc, kiểm tra race condition / deadlock / sai số / rò rỉ tài nguyên]
- **Commit/issue liên quan:** [Mã commit hoặc số PR/issue]
-->

## Tuyên bố
Nhóm chịu trách nhiệm về tính đúng đắn, bản quyền, số liệu thực nghiệm và mọi nội dung đã nộp.
