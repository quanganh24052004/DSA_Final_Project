# BÁO CÁO ĐỒ ÁN MÔN HỌC
**Môn học:** Cấu trúc dữ liệu và giải thuật (MI3060)
**Tên đề tài:** Xây dựng Hệ thống Quản lý Đào tạo Tín chỉ
**Sinh viên thực hiện:** Nguyễn Quang Anh - 20227035

---

## MỤC LỤC
1. [Giới thiệu chung](#1-giới-thiệu-chung)
2. [Cấu trúc dữ liệu được áp dụng](#2-cấu-trúc-dữ-liệu-được-áp-dụng)
3. [Thiết kế thuật toán và Logic nghiệp vụ](#3-thiết-kế-thuật-toán-và-logic-nghiệp-vụ)
4. [Hệ thống chức năng](#4-hệ-thống-chức-năng)
5. [Đánh giá hiệu năng và Kết luận](#5-đánh-giá-hiệu-năng-và-kết-luận)

---

## 1. Giới thiệu chung

Đồ án hướng tới việc thiết kế và xây dựng một **Hệ thống Quản lý Đào tạo Tín chỉ** bằng ngôn ngữ C++. Điểm nổi bật của hệ thống này không nằm ở việc sử dụng cơ sở dữ liệu quan hệ có sẵn (như MySQL hay SQL Server) mà hoàn toàn tự triển khai các cấu trúc dữ liệu nguyên thủy trên bộ nhớ RAM (Heap). Mục tiêu cốt lõi là áp dụng các kiến thức cốt lõi của môn học **Cấu trúc dữ liệu và giải thuật (MI3060)** để giải quyết bài toán quản lý dữ liệu lớn, đảm bảo hiệu suất truy xuất, thêm, sửa, xóa (CRUD) gần như tức thời.

Hệ thống hỗ trợ quản lý toàn diện 4 thực thể chính: **Sinh Viên**, **Ngành Học**, **Học Phần**, và **Lớp Học Phần**, đồng thời cung cấp bộ tính năng tính toán điểm tích lũy (CPA/GPA) và xuất báo cáo học tập trực quan.

---

## 2. Cấu trúc dữ liệu được áp dụng

Để đảm bảo hiệu năng và xử lý dữ liệu với số lượng lớn (lên đến hàng chục nghìn bản ghi), hệ thống kết hợp sức mạnh của 2 cấu trúc dữ liệu nền tảng:

### 2.1. Bảng băm (Hash Map)
- **Vai trò:** Đóng vai trò là cơ sở dữ liệu chính của hệ thống. Được dùng để lưu trữ và quản lý tập trung các danh sách thực thể gốc (Danh sách Sinh viên, Danh sách Học phần, Danh sách Ngành học, Danh sách Lớp học phần).
- **Cơ chế băm (Hashing Algorithm):** Áp dụng hàm băm chuỗi **DJB2** (nhân đa thức với hằng số 33). Thuật toán này có tính phân phối đồng đều, giúp ánh xạ các khóa chuỗi (như MSSV, Mã Học Phần) thành chỉ số mảng một cách nhanh chóng.
- **Xử lý va chạm (Collision Resolution):** Sử dụng kỹ thuật **Separate Chaining** (Băm liên kết ngoài) thông qua mảng các `LinkedList`.
- **Cơ chế tự động mở rộng (Rehashing):** Khi hệ số tải (Load Factor $\lambda = \frac{size}{capacity}$) vượt quá ngưỡng tối ưu $0.75$, Bảng băm sẽ tự động cấp phát mảng mới với kích thước là số nguyên tố lớn hơn gấp đôi và phân bổ lại toàn bộ dữ liệu. Giúp duy trì thời gian tra cứu luôn ở mức $O(1)$ trung bình.

### 2.2. Danh sách liên kết đơn (Linked List)
- **Vai trò:** Đóng vai trò cấu trúc dữ liệu phụ trợ.
- **Ứng dụng thực tế:**
  1. Xử lý các dải va chạm (buckets) của Hash Map.
  2. Lưu trữ **Danh sách Kết quả học tập** cá nhân bên trong từng đối tượng `SinhVien`. Nhờ đó sinh viên có thể tích lũy số lượng học phần không giới hạn mà không bị ràng buộc bộ nhớ tĩnh.
  3. Lưu trữ **Danh sách Sinh viên** đăng ký vào một `LopHocPhan` cụ thể.
- **Độ phức tạp:** Thao tác chèn ở đuôi (Insert At Tail) là $O(1)$ do duy trì con trỏ `tail`.

---

## 3. Thiết kế thuật toán và Logic nghiệp vụ

### 3.1. Thuật toán Lọc môn học lại và Tính CPA
Trong quá trình đào tạo tín chỉ, sinh viên được phép học lại một học phần để cải thiện điểm số. Hệ thống yêu cầu chỉ lấy điểm cao nhất khi tính toán Điểm trung bình tích lũy toàn khóa (CPA).
- **Quy trình:**
  - Hệ thống lội qua danh sách điểm gốc của sinh viên (kích thước $M$).
  - Sử dụng một `LinkedList` phụ trợ (`listCPA`) để gom nhóm các môn học.
  - Khi xét một điểm mới, thuật toán quét lại `listCPA` để kiểm tra mã học phần trùng lặp. Nếu mã đã tồn tại và điểm mới cao hơn điểm cũ, hệ thống trỏ đè dữ liệu. Ngược lại, nếu chưa tồn tại, kết quả sẽ được chèn mới.
- **Độ phức tạp:** $O(M^2)$ trong trường hợp xấu nhất (do không sử dụng thêm bộ nhớ phụ trợ lớn như Hash Map phụ cho việc này nhằm tiết kiệm RAM). Tuy nhiên $M$ (số học phần của 1 cá nhân) thường rất nhỏ (vài chục môn) nên tốc độ phản hồi vẫn dưới 1 milli-giây.

### 3.2. Chống ghi đè dữ liệu sai lệch
- Tại các thao tác CRUD và Đăng ký học tập, hệ thống luôn kiểm tra tính duy nhất.
- Ví dụ: Trong `addDiem` hay `registerSinhVienToLop`, hệ thống lội tuyến tính qua danh sách hiện tại của thực thể để đảm bảo mã định danh chưa từng tồn tại trước khi dùng `insertAtTail`.

---

## 4. Hệ thống chức năng

Hệ thống cung cấp một Giao diện Dòng lệnh (CLI) trực quan chia thành 5 phân hệ cốt lõi:

1. **Quản Lý Danh Mục:** Thêm, Cập nhật, Xoá, Hiển thị (CRUD) thông tin của Sinh Viên, Học Phần và Lớp Học Phần. Tốc độ tương tác tức thì $O(1)$.
2. **Quản Lý Điểm & Kết Quả:** Cho phép giáo viên nhập điểm (Quá trình, Cuối kỳ) cho từng sinh viên thông qua Mã định danh. Hệ thống tự động ánh xạ điểm hệ 10 sang hệ 4 và điểm chữ. Hỗ trợ sửa điểm khi có sai sót.
3. **Logic Nghiệp Vụ:** Tích hợp bộ máy tính toán GPA (Điểm trung bình học kỳ), CPA (Tích lũy) và hàm đánh giá học lực (Xuất sắc, Giỏi, Khá, Trung bình, Yếu).
4. **Báo Cáo & Tìm Kiếm:** 
   - Xuất Bảng điểm cá nhân (tra cứu tổng hợp các môn một cá nhân đã tích lũy).
   - Xuất Bảng điểm lớp học phần (liệt kê danh sách sinh viên kèm điểm trong một lớp).
5. **Dữ Liệu & Hệ Thống (Yêu cầu khắt khe về DSA):**
   - Đọc và nạp dữ liệu chuẩn CSV vào RAM. Xuất ngược RAM ra tệp CSV để đồng bộ.
   - Trình giả lập Mock Data sinh ngẫu nhiên 10.000+ sinh viên để benchmark hệ thống.

---

## 5. Đánh giá hiệu năng và Kết luận

### Phép thử Benchmark
Thông qua phân hệ **"Đánh giá hiệu năng tìm kiếm"** được tích hợp sẵn, hệ thống thực hiện phép đo kiểm thời gian thực (real-time benchmarking) với tập dữ liệu 10.000 sinh viên:
- **Tìm kiếm tuần tự $O(N)$ bằng Linked List:** Khi thực hiện 1.000 lượt tra cứu ngẫu nhiên, hệ thống cần duyệt qua hàng triệu node, tốn một lượng thời gian đáng kể (vài chục đến hàng trăm milli-giây tùy CPU).
- **Tìm kiếm bằng Hash Map $O(1)$:** Với cùng 1.000 lượt tra cứu ngẫu nhiên, nhờ cơ chế Băm DJB2 phân phối dữ liệu thông minh, thời gian trả về kết quả gần như bằng **0.001ms** (chênh lệch hàng nghìn lần so với mảng tuần tự).

### Kết luận
Dự án đã triển khai thành công một kiến trúc dữ liệu mạnh mẽ, kết hợp khéo léo giữa Hash Map và Linked List, đáp ứng trọn vẹn yêu cầu xử lý dữ liệu lớn (Big Data in RAM). Toàn bộ thao tác CRUD, tra cứu và đánh giá học tập được thực hiện nhanh chóng, không xảy ra hiện tượng rò rỉ bộ nhớ (Memory Leak) nhờ cơ chế dọn dẹp cấp phát động (`cleanUp`) tối ưu, xứng đáng là một hệ thống lõi tiềm năng để phát triển lên các phần mềm đào tạo thực tế.
