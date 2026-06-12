## **NOTE: CHƯA RÀ SOÁT HẾT**

## **I. Kịch bản vận hành cấu trúc dữ liệu dưới RAM:**

Để tối ưu hóa tốc độ hệ thống, toàn bộ thực thể nghiệp vụ dữ liệu gốc khi nạp từ file CSV sẽ được cấp phát động bằng toán tử new trên vùng nhớ **Heap**. Hệ thống triển khai kiến trúc lưu trữ kết hợp giữa hai cấu trúc dữ liệu cốt lõi:

**Về Bảng băm (HashMap):** Sử dụng cấu trúc mảng các danh sách liên kết LinkedList\<HashEntry\<K,V\>\>\* buckets để quản lý va chạm.

* Khóa định danh (Key) và con trỏ dữ liệu (Value) được đóng gói trong HashEntry\<K, V\>. Toán tử so sánh bằng operator== dựa trên khóa.  
* Hàm băm sử dụng thuật toán **DJB2** (băm chuỗi string thành chỉ số mảng thông qua phép toán modulo với capacity).  
* Hệ số tải $\\lambda \= \\frac{\\text{size}}{\\text{capacity}}$. Khi $\\lambda \\ge 0.75$, hàm rehash() tự động nhân đôi kích thước mảng bucket lên một **số nguyên tố lớn hơn** tiếp theo.  
  **Về Danh sách liên kết đơn (LinkedList):**  
* Sử dụng cấu trúc LinkedList\<T\> tổng quát, quản lý thông qua hai con trỏ head và tail cùng biến size. Các phần tử kết nối qua con trỏ next của Node\<T\>.  
* Quản lý danh sách kết quả học tập (danhSachDiem kiểu LinkedList\<KetQuaHocTap\*\>) lồng trong từng thực thể sinh viên.  
* Mỗi lớp học phần (LopHocPhan) chứa một LinkedList\<SinhVien\*\> để lưu trữ các con trỏ sinh viên đăng ký vào lớp. Thao tác thêm sinh viên vào lớp hoặc thêm điểm vào sinh viên sử dụng hàm insertAtTail() với độ phức tạp $O(1)$.

## **II. Hệ thống ca kiểm thử (Test cases)**

Dưới đây là bảng đặc tả các ca kiểm thử (Test Cases) cốt lõi nhằm kiểm tra toàn diện từ các luồng thao tác dữ liệu gốc (CRUD), xử lý va chạm, tính toán tích lũy cho đến kiểm thử hiệu năng dữ liệu lớn của hệ thống. 

| Mã TC | Tên / Mục đích kiểm thử | Dữ liệu đầu vào (Input) | Kết quả mong đợi (Expected Output) | Độ phức tạp |
| :---- | :---- | :---- | :---- | :---- |
| **TC\_1.1** | Nạp dữ liệu từ file CSV (loadData) | Đường dẫn các file .csv chuẩn (Sinh viên, Ngành, Học phần, Lớp HP). | Thư viện fstream đọc file, parse bằng delimiter; cấp phát new đối tượng lên Heap và nạp tự động vào HashMap/LinkedList tương ứng. | $O(N)$ |
| **TC\_1.2** | Kiểm thử biên: Xử lý file CSV trống hoặc lỗi | Tệp dữ liệu có dung lượng bằng 0 KB hoặc không tồn tại. | Hệ thống thông báo khởi tạo danh sách rỗng thành công, không bị sập (crash) chương trình. | $O(1)$ |
| **TC\_1.3** | Đồng bộ ghi file dữ liệu (saveData) | Gọi hàm lưu dữ liệu khi có biến động trên RAM. | Duyệt qua các cấu trúc lưu trữ, trích xuất thông tin thành chuỗi cách nhau bằng dấu phẩy và ghi tuần tự lại vào file CSV. | $O(N \+ B)$ |
| **TC\_2.1** | Thêm mới thực thể thành công (addSinhVien, addNganhHoc, addHocPhan, addLopHocPhan) | Con trỏ thực thể hợp lệ (đã cấp phát trên Heap), mã số định danh chưa tồn tại trong hệ thống. | Hàm .get() trả về nullptr. Hệ thống gọi .put() nạp thành công mã số và con trỏ thực thể vào Bảng băm tương ứng, trả về true. | $O(1)$ trung bình |
| **TC\_2.2** | Kiểm thử biên: Thêm thực thể trùng mã định danh | Nhập thực thể mới có mã số (MSSV, Mã ngành, Mã HP, Mã lớp) trùng với thực thể đã tồn tại. | Hàm .get() nhận diện mã đã tồn tại (khác nullptr), hệ thống lập tức từ chối nạp, trả về false và phát cảnh báo lỗi. | $O(1)$ trung bình |
| **TC\_2.3** | Xóa thực thể gốc khỏi hệ thống (removeSinhVien, removeNganhHoc, removeHocPhan, removeLopHocPhan) | Mã định danh của một thực thể hiện có trên RAM. | Gọi .remove(key) ngắt liên kết khỏi Bảng băm. Kích hoạt lệnh delete thu hồi triệt để vùng nhớ Heap của đối tượng, trả về true. | $O(1)$ trung bình |
| **TC\_3.1** | Đăng ký sinh viên vào lớp HP (registerSinhVienToLop) | Cặp chuỗi định danh mssv và maLop hợp lệ. | Tìm kiếm thực thể qua hàm phụ trợ. Kích hoạt hàm thành viên lhp-\>addSinhVien(sv), gọi insertAtTail() để nối con trỏ SinhVien\* vào cuối LinkedList nội bộ của lớp, trả về true. | $O(1)$ |
| **TC\_3.2** | Xóa sinh viên khỏi lớp HP (unregisterSinhVienFromLop) | Cặp chuỗi định danh mssv và maLop hiện có. | Kích hoạt lhp-\>removeSinhVien(sv), chỉnh sửa liên kết các con trỏ next xung quanh nút, giải phóng ô nhớ của nút, chuỗi không bị đứt gãy, trả về true. | $O(N)$ (Duyệt tuyến tính) |
| **TC\_4.1** | Tra cứu & Xử lý xung đột băm (HashMap::get) | Hai mã định danh khác nhau nhưng trùng chỉ số băm (Index) qua thuật toán băm chuỗi DJB2. | Cơ chế Separate Chaining kích hoạt, các nút kết nối chung mảng qua con trỏ next của LinkedList tại buckets\[index\]. Tra cứu duyệt tuyến tính trên chuỗi va chạm vẫn chính xác. | $O(1)$ trung bình, cực hạn $O(K)$ |
| **TC\_4.2** | Nhập điểm mới & Khử nhiễu học lại (addDiem) | Các chuỗi mssv, maLop, maHP, điểm diemQTr, diemCK. Sinh viên học lại môn cũ với mức điểm cao hơn ở kỳ mới. | findSinhVienByMSSV định vị sinh viên. Duyệt LinkedList điểm cá nhân check trùng mã lớp. Ánh xạ điểm chữ (xepLoaiDiemChu), thang 4 (quyDoiHe4). Cấp phát KetQuaHocTap trên Heap, chèn cuối danh sách điểm qua themKetQuaHocTap. | Tra cứu SV: $O(1)$, Duyệt danh sách điểm: $O(M)$ |
| **TC\_4.3** | Tính điểm tích lũy & Xếp loại học lực (calculateGPAAndCPA, displayThongKeHocLuc) | Chuỗi mssv và hocKy cần tra cứu. | Khởi tạo danh sách phụ trợ listCPA để lọc trùng, nếu điểm môn cũ thấp hơn thì trỏ lại nút dữ liệu sang nút mới cao hơn. Cộng dồn nhân số tín chỉ, tính chính xác GPA (học kỳ) và CPA (tích lũy). Hàm evaluateHocLuc rẽ nhánh điều kiện logic in đúng chuỗi xếp loại. | Duyệt danh sách điểm gốc và phụ trợ: $O(M)$ |
| **TC\_4.4** | In bảng điểm lớp học phần lồng nhau (displayBangDiemLopHP) | Chuỗi mã lớp học phần maLop cần kết xuất. | Vòng lặp ngoài duyệt LinkedList sinh viên của lớp. Vòng lặp trong duyệt tuần tự LinkedList điểm cá nhân để tìm maLop tương ứng. Trích xuất chi tiết điểm số, nếu không tìm thấy điểm in giá trị "N/A". | Vòng lặp lồng nhau: $O(P \\times M)$ |
| **TC\_5.1** | Tự động kích hoạt Rehash khi tải nặng (rehash) | Hàm sinh dữ liệu mẫu chạy vòng lặp liên tiếp, đẩy số lượng phần tử tăng cao khiến hệ số tải $\\lambda \= \\frac{\\text{size}}{\\text{capacity}} \\ge 0.75$. | Hệ thống tự động cấp phát mảng buckets mới có kích thước lớn hơn (số nguyên tố tiếp theo), duyệt mảng cũ, tính toán lại vị trí băm và di dời toàn bộ các Node dữ liệu sang mảng mới, giải phóng bộ nhớ cũ. | $O(N \+ B)$ tại thời điểm rehash |
| **TC\_5.2** | Đánh giá so sánh hiệu năng thực tế giải thuật | Gọi chức năng đo đạc, hệ thống lấy ngẫu nhiên các khóa để tra cứu trên HashMap và một LinkedList tuần tự. | Thư viện \<chrono\> ghi lại thời gian thực thi (milli-giây). Xuất bảng đối chiếu trực quan minh chứng tốc độ vượt trội của Bảng băm $T\_{\\text{HashMap}} \\approx 0 \- 1 \\text{ ms}$ ($O(1)$) so với $T\_{\\text{LinkedList}} \\gg 1 \\text{ ms}$ ($O(N)$). | Đối chiếu trực quan cấu trúc dữ liệu |
| **TC\_5.3** | Dọn dẹp hệ thống & Thoát chương trình (cleanUp) | Chọn chức năng thoát chương trình. | Hàm cleanUp() duyệt qua toàn bộ các cấu trúc dữ liệu (HashMap, mảng buckets, chuỗi các LinkedList), gọi lệnh delete giải phóng triệt để tất cả các con trỏ thực thể gốc đang neo giữ trên bộ nhớ Heap. RAM thu hồi hoàn toàn, chống rò rỉ bộ nhớ (Memory Leak). | $O(N \+ B)$ |

