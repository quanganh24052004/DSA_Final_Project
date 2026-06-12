# Phân tích Thuật toán và Mã giả

## 1. Module Thao Tác Dữ Liệu Gốc
### 1.1. Chức năng Quản lý Sinh Viên

#### a. Thêm sinh viên mới (`addSinhVien`)

**1. Mục đích:**
Thêm một đối tượng sinh viên mới vào hệ thống thông qua Bảng băm `danhSachSinhVien`. Đảm bảo tính duy nhất của Mã số sinh viên (MSSV).

**2. Đầu vào (Input):**
- `sv`: Con trỏ tới đối tượng `SinhVien` cần thêm.

**3. Đầu ra (Output):**
- Trả về `true` nếu thêm thành công.
- Trả về `false` nếu con trỏ `sv` bị `NULL` hoặc MSSV đã tồn tại trong hệ thống.

**4. Mã giả (Pseudocode):**
```cpp
    bool addSinhVien(SinhVien* sv) {
        if sv == NULL then return false;
        
        // Kiểm tra xem MSSV đã tồn tại trong Bảng băm chưa
        if danhSachSinhVien.get(sv->getMSSV()) != NULL then 
            return false;
            
        // Thêm vào Bảng băm
        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(1)$ trung bình. Bảng băm tra cứu và chèn phần tử với thời gian hằng số.
- **Độ phức tạp không gian:** $O(1)$. Chỉ tốn thêm chi phí lưu trữ một con trỏ vào Bảng băm.

---

#### b. Cập nhật thông tin sinh viên (`updateSinhVien`)

**1. Mục đích:**
Cập nhật dữ liệu của một sinh viên đã tồn tại trong hệ thống thông qua việc ghi đè lên Bảng băm.

**2. Đầu vào (Input):**
- `sv`: Con trỏ tới đối tượng `SinhVien` chứa thông tin mới.

**3. Đầu ra (Output):**
- Trả về `true` nếu cập nhật thành công.
- Trả về `false` nếu `sv` bị `NULL` hoặc MSSV chưa tồn tại trong hệ thống.

**4. Mã giả (Pseudocode):**
```cpp
    bool updateSinhVien(SinhVien* sv) {
        if sv == NULL then return false;
        
        // Kiểm tra sinh viên có tồn tại không
        if danhSachSinhVien.get(sv->getMSSV()) == NULL then 
            return false;

        // Cập nhật bằng cách ghi đè trong Bảng băm
        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(1)$ trung bình. Tra cứu và ghi đè trên Bảng băm.
- **Độ phức tạp không gian:** $O(1)$.

---

#### c. Xóa thông tin sinh viên (`removeSinhVien`)

**1. Mục đích:**
Xoá bỏ hoàn toàn thông tin của một sinh viên khỏi hệ thống, đồng thời giải phóng bộ nhớ đã cấp phát.

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên (chuỗi) cần xoá.

**3. Đầu ra (Output):**
- Trả về `true` nếu xoá và giải phóng bộ nhớ thành công.
- Trả về `false` nếu không tìm thấy MSSV.

**4. Mã giả (Pseudocode):**
```cpp
    bool removeSinhVien(string mssv) {
        SinhVien* sv = danhSachSinhVien.get(mssv);
        
        if sv != NULL then {
            // Ngắt kết nối trong Bảng băm
            if danhSachSinhVien.remove(mssv) == true then {
                delete sv; // Giải phóng bộ nhớ trên Heap
                return true;
            }
        }
        return false;
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(1)$ trung bình. Tra cứu và loại bỏ node trong chuỗi Separate Chaining của Bảng băm.
- **Độ phức tạp không gian:** $O(1)$.

---

#### d. Tra cứu sinh viên theo MSSV (`findSinhVienByMSSV`)

**1. Mục đích:**
Tìm kiếm và trả về địa chỉ đối tượng sinh viên khi biết MSSV.

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên (chuỗi).

**3. Đầu ra (Output):**
- Con trỏ `SinhVien*` tới đối tượng tìm thấy, hoặc `NULL` nếu không tồn tại.

**4. Mã giả (Pseudocode):**
```cpp
    SinhVien* findSinhVienByMSSV(string mssv) {
        return danhSachSinhVien.get(mssv);
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(1)$ trung bình.
- **Độ phức tạp không gian:** $O(1)$.

---

### 1.2. Chức năng Quản lý Ngành Học

*(Cấu trúc các hàm `addNganhHoc`, `updateNganhHoc`, `removeNganhHoc`, `findNganhHocByMa` hoạt động hoàn toàn tương tự module Quản lý Sinh viên, áp dụng trên bảng băm `danhSachNganhHoc` bằng khoá là `Mã Ngành`).*

**Độ phức tạp chung:**
- **Thời gian:** $O(1)$ trung bình cho mọi thao tác CRUD do ứng dụng Bảng băm.
- **Không gian:** $O(1)$.

---

### 1.3. Chức năng Quản lý Học Phần

*(Cấu trúc các hàm `addHocPhan`, `updateHocPhan`, `removeHocPhan`, `findHocPhanByMa` hoạt động hoàn toàn tương tự module Quản lý Sinh viên, áp dụng trên bảng băm `danhSachHocPhan` bằng khoá là `Mã Học phần`).*

**Độ phức tạp chung:**
- **Thời gian:** $O(1)$ trung bình cho mọi thao tác CRUD do ứng dụng Bảng băm.
- **Không gian:** $O(1)$.

---

### 1.4. Chức năng Quản lý Lớp Học Phần

#### a. Đăng ký sinh viên vào lớp học phần (`registerSinhVienToLop`)

**1. Mục đích:**
Đăng ký một sinh viên vào danh sách của một lớp học phần cụ thể.

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên (chuỗi).
- `maLop`: Mã lớp học phần (chuỗi).

**3. Đầu ra (Output):**
- Trả về `true` nếu đăng ký thành công.
- Trả về `false` nếu không tìm thấy sinh viên, không tìm thấy lớp, hoặc sinh viên đã có trong danh sách của lớp đó.

**4. Mã giả (Pseudocode):**
```cpp
    bool registerSinhVienToLop(string mssv, string maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        
        if sv != NULL and lhp != NULL then {
            return lhp->addSinhVien(sv);
        }
        return false;
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(K)$ trung bình. Với $K$ là số lượng sinh viên đang đăng ký trong lớp học phần đó. Việc tra cứu `sv` và `lhp` thông qua Bảng băm mất $O(1)$. Tuy nhiên, phương thức `addSinhVien` của `LopHocPhan` cần duyệt qua danh sách liên kết $K$ phần tử để kiểm tra sự trùng lặp (chống đăng ký 2 lần) trước khi chèn vào cuối.
- **Độ phức tạp không gian:** $O(1)$.

---

#### b. Hủy đăng ký sinh viên khỏi lớp học phần (`unregisterSinhVienFromLop`)

**1. Mục đích:**
Loại bỏ hoàn toàn một sinh viên khỏi danh sách của lớp học phần.

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên (chuỗi).
- `maLop`: Mã lớp học phần (chuỗi).

**3. Đầu ra (Output):**
- Trả về `true` nếu loại bỏ thành công.
- Trả về `false` nếu thao tác thất bại.

**4. Mã giả (Pseudocode):**
```cpp
    bool unregisterSinhVienFromLop(string mssv, string maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        
        if sv != NULL and lhp != NULL then {
            return lhp->removeSinhVien(sv);
        }
        return false;
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(K)$ trung bình. Với $K$ là số sinh viên trong lớp học phần. Thao tác `removeSinhVien` của đối tượng lớp học phần cần duyệt dọc theo danh sách liên kết để tìm chính xác nút sinh viên và loại bỏ nó.
- **Độ phức tạp không gian:** $O(1)$.

---

### 1.5. Chức năng Quản lý Kết quả học tập

#### a. Thêm kết quả học tập (`addDiem`)

**1. Mục đích:**
Ghi nhận kết quả học tập (điểm quá trình, điểm cuối kỳ) của một sinh viên vào hệ thống. Tự động tính toán điểm hệ chữ và hệ 4.

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên.
- `maLop`: Mã lớp học phần.
- `maHP`: Mã học phần.
- `diemQTr`, `diemCK`: Điểm quá trình và điểm cuối kỳ.
- `trongSoQTr`: Trọng số điểm quá trình (mặc định là 0.3).

**3. Đầu ra (Output):**
- Trả về `true` nếu ghi nhận thành công.

**4. Mã giả (Pseudocode):**
```cpp
    bool addDiem(string mssv, string maLop, string maHP, float diemQTr, float diemCK, float trongSoQTr) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return false;
    
        // Tính toán các hệ số điểm
        float diemHP = diemQTr * trongSoQTr + diemCK * (1.0 - trongSoQTr);
        KetQuaHocTap* kq = new KetQuaHocTap(maLop, maHP, diemQTr, diemCK, diemHP, xepLoaiDiemChu(diemHP), quyDoiHe4(diemHP));
    
        // Thêm vào danh sách điểm lưu trữ tại thực thể SinhVien
        if sv->themKetQuaHocTap(kq) == true then {
            return true;
        } else {
            // Giải phóng bộ nhớ nếu mã lớp học phần đã có sẵn (trùng)
            delete kq;  
            return false;
        }
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(M)$. Với $M$ là tổng số học phần mà sinh viên đó đã tích lũy. Hàm `themKetQuaHocTap` phải duyệt dọc qua chuỗi $M$ kết quả học tập cũ để bảo đảm rằng `maLop` này chưa từng tồn tại, chống hiện tượng ghi đè dữ liệu sai trái.
- **Độ phức tạp không gian:** $O(1)$. Hệ thống chỉ tiêu tốn thêm lượng không gian hằng số để cấp phát một đối tượng `KetQuaHocTap` mới trên Heap.

---

#### b. Cập nhật & Xóa thông tin điểm số (`updateDiem` & `removeDiem`)

**1. Mục đích:**
Điều chỉnh hoặc xoá bỏ một kết quả học tập khi phát hiện sai sót trong quá trình nhập liệu.

**2. Đầu vào (Input):**
- Khóa định danh: `mssv` (để xác định sinh viên) và `maLop` (để xác định kết quả của lớp học phần cụ thể).
- Các tham số mới (đối với hành động Cập nhật).

**3. Đầu ra (Output):**
- Trả về `true` nếu tìm thấy và sửa/xoá thành công.
- Trả về `false` nếu không tìm thấy.

**4. Mã giả (Ví dụ cho Cập nhật điểm):**
```cpp
    bool updateDiem(string mssv, string maLop, float diemQTrMoi, float diemCKMoi, float trongSoQTr) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return false;
        
        // Duyệt danh sách điểm để tìm nút tương ứng với mã lớp
        Node* current = sv->getDanhSachDiem().getHead();
        while current != NULL do {
            if current->data->getMaLop() == maLop then {
                float diemHP = diemQTrMoi * trongSoQTr + diemCKMoi * (1.0 - trongSoQTr);
                current->data->setDiemQTr(diemQTrMoi);
                current->data->setDiemCK(diemCKMoi);
                // Cập nhật lại các thuộc tính phụ trợ (điểm chữ, hệ 4)...
                return true;
            }
            current = current->next;
        }
        return false;
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(M)$. Quá trình tìm kiếm `maLop` trong danh sách liên kết có kích thước $M$ của sinh viên là bắt buộc.
- **Độ phức tạp không gian:** $O(1)$.

---

## 2. Module Chiết Xuất & Hiển Thị Thông Tin

### 2.1. Tra cứu Bảng điểm cá nhân (`displayBangDiemCaNhan`)

**1. Mục đích:**
Kết xuất toàn bộ lịch sử học tập của một cá nhân dưới dạng giao diện bảng biểu, bao gồm các điểm thành phần, điểm tổng kết hệ số 10, hệ số 4 và điểm chữ.

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên.

**3. Đầu ra (Output):**
- In bảng điểm chi tiết ra Console. Hàm không có giá trị trả về (`void`).

**4. Mã giả (Pseudocode):**
```cpp
    void displayBangDiemCaNhan(string mssv) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return;

        // In phần mở đầu (Tiêu đề bảng, MSSV, Họ Tên)
        
        Node* current = sv->getDanhSachDiem().getHead();
        while current != NULL do {
            KetQuaHocTap* kq = current->data;
            // Giải tham chiếu để lấy tên học phần, số tín chỉ
            HocPhan* hp = findHocPhanByMa(kq->getMaHP()); 
            
            // In định dạng cho 1 dòng dữ liệu (Mã lớp, Mã HP, Tên HP, Các cột điểm...)
            
            current = current->next;
        }
        
        // In phần kết thúc (Đóng bảng)
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(M)$. Hàm thực thi một vòng lặp duyệt liên tục qua $M$ kết quả học tập của cá nhân. Ở mỗi bước, việc truy xuất tên học phần `findHocPhanByMa` trực tiếp từ Bảng băm tốn chi phí hằng số $O(1)$.
- **Độ phức tạp không gian:** $O(1)$. Quá trình xử lý chuỗi và in được đẩy thẳng ra bộ đệm stdout.

---

### 2.2. Hiển thị Bảng điểm Lớp Học Phần (`displayBangDiemLopHP`)

**1. Mục đích:**
In báo cáo danh sách điểm của toàn bộ sinh viên trực thuộc một Lớp Học Phần.

**2. Đầu vào (Input):**
- `maLop`: Mã lớp học phần.

**3. Đầu ra (Output):**
- Bảng danh sách điểm xuất ra Console. (`void`).

**4. Mã giả (Pseudocode):**
```cpp
    void displayBangDiemLopHP(string maLop) {
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        if lhp == NULL then return;

        // Lấy danh sách SV nằm trong sự quản lý của lớp học phần
        Node* currentSV = lhp->getDanhSachSinhVien().getHead();
        
        while currentSV != NULL do {
            SinhVien* sv = currentSV->data;
            
            // Tìm điểm của sinh viên trong học phần này
            KetQuaHocTap* kqTarget = NULL;
            Node* kqNode = sv->getDanhSachDiem().getHead();
            
            while kqNode != NULL do {
                if kqNode->data->getMaLop() == maLop then {
                    kqTarget = kqNode->data;
                    break;
                }
                kqNode = kqNode->next;
            }

            // In thông tin 1 sinh viên (MSSV, Họ tên, Điểm QTr, Điểm CK, ...)
            
            currentSV = currentSV->next;
        }
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(K \times M)$. Với $K$ là số lượng sinh viên trong lớp học phần, vòng lặp ngoài cùng chạy $K$ lần. Đối với mỗi sinh viên được xét, thuật toán bắt buộc phải quét dọc theo danh sách điểm cá nhân của họ gồm $M$ bản ghi (số học phần trung bình một sinh viên đã học) để lấy được đúng kết quả ứng với lớp này.
- **Độ phức tạp không gian:** $O(1)$. Xử lý trích xuất tại chỗ trên các danh sách liên kết.

---

## 3. Module Thống Kê & Đánh Giá Học Lực

### 3.1. Tính GPA & CPA (`calculateGPAAndCPA`)

**1. Mục đích:**
Tính toán Điểm trung bình học kỳ (GPA) chỉ áp dụng cho một học kỳ duy nhất, và Điểm trung bình tích lũy toàn khoá (CPA). Chức năng này bao gồm cơ chế lọc và loại bỏ điểm của những môn học lại (chỉ tính điểm cao nhất).

**2. Đầu vào (Input):**
- `mssv`: Mã số sinh viên.
- `hocKy`: Học kỳ truy vấn (Ví dụ: `2023.1`).

**3. Đầu ra (Output):**
- Giá trị bộ đôi (tuple/pair) `(gpa, cpa)`.

**4. Mã giả (Pseudocode):**
```cpp
    GPA_CPA calculateGPAAndCPA(string mssv, string hocKy) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return (0.0, 0.0);

        float sumGPA = 0.0, sumCPA = 0.0;
        int creditsGPA = 0, creditsCPA = 0;

        // Danh sách liên kết phụ trợ dùng để lọc bỏ môn học lại
        LinkedList listCPA;     
        Node* current = sv->getDanhSachDiem().getHead();

        // [Giai đoạn 1]: Tính GPA & Gom nhóm học phần cho CPA
        while current != NULL do {
            KetQuaHocTap* kq = current->data;
            HocPhan* hp = findHocPhanByMa(kq->getMaHP());
            LopHocPhan* lhp = findLopHocPhanByMa(kq->getMaLop());

            if hp != NULL AND lhp != NULL then {
                int stc = hp->getSoTinChi();
                float diem4 = kq->getThang4();

                // a. Xử lý GPA (Cộng dồn nếu khớp với học kỳ truy vấn)
                if lhp->getHocKy() == hocKy then {
                    sumGPA = sumGPA + (diem4 * stc);
                    creditsGPA = creditsGPA + stc;
                }

                // b. Xử lý CPA (Lọc học phần học lại, lấy điểm cao nhất)
                bool foundInCPA = false;
                Node* cpaNode = listCPA.getHead();
                
                while cpaNode != NULL do {
                    if cpaNode->data->getMaHP() == kq->getMaHP() then {
                        foundInCPA = true;
                        // Ghi đè con trỏ nếu điểm vòng ngoài cao hơn
                        if diem4 > cpaNode->data->getThang4() then {
                            cpaNode->data = kq;     
                        }
                        break;  
                    }
                    cpaNode = cpaNode->next;
                }

                // Nếu là học phần hoàn toàn mới, đẩy vào danh sách
                if foundInCPA == false then {
                    listCPA.insertAtHead(kq);   
                }
            }
            current = current->next;
        }

        // [Giai đoạn 2]: Tính tổng CPA thông qua danh sách đã lọc sạch
        Node* cpaNode = listCPA.getHead();
        while cpaNode != NULL do {
            KetQuaHocTap* kqCPA = cpaNode->data;
            HocPhan* hpCPA = findHocPhanByMa(kqCPA->getMaHP());
            
            int stc = hpCPA->getSoTinChi();
            sumCPA = sumCPA + (kqCPA->getThang4() * stc);
            creditsCPA = creditsCPA + stc;

            cpaNode = cpaNode->next;
        }

        // [Giai đoạn 3]: Đóng gói kết quả (Chống lỗi Division by Zero)
        float gpa = (creditsGPA > 0) ? (sumGPA / creditsGPA) : 0.0;
        float cpa = (creditsCPA > 0) ? (sumCPA / creditsCPA) : 0.0;

        // Giải phóng danh sách phụ trợ
        listCPA.clear();

        return (gpa, cpa);
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(M^2)$. 
  - *Giải thích:* [Giai đoạn 1] duyệt qua $M$ kết quả học tập gốc. Tại mỗi kết quả, thuật toán lội qua danh sách phụ trợ `listCPA` (kích thước tối đa là $M$) để kiểm tra sự trùng lặp mã học phần $\rightarrow$ Hai vòng lặp lồng nhau tiêu thụ $O(M^2)$. [Giai đoạn 2] duyệt một lần qua danh sách đã lọc, tốn $O(M)$. Tổng thể chi phí chi phối là $O(M^2)$.
- **Độ phức tạp không gian:** $O(M)$.
  - *Giải thích:* Khởi tạo danh sách liên kết phụ trợ `listCPA` lưu trữ tối đa $M$ con trỏ để giải quyết triệt để vấn đề sinh viên học lại.

---

### 3.2. Đánh giá xếp loại học lực (`evaluateHocLuc` & `displayThongKeHocLuc`)

**1. Mục đích:**
Dựa trên điểm CPA đã tính toán, ánh xạ sang mức xếp loại học lực chuẩn (Xuất sắc, Giỏi, Khá...) và hiển thị tổng hợp ra màn hình.

**2. Đầu vào (Input):**
- `mssv` và `hocKy`.

**3. Đầu ra (Output):**
- In kết quả thống kê.

**4. Mã giả (Pseudocode):**
```cpp
    string evaluateHocLuc(float cpa) {
        if cpa >= 3.6 then return "Xuat sac";
        if cpa >= 3.2 then return "Gioi";
        if cpa >= 2.5 then return "Kha";
        if cpa >= 2.0 then return "Trung binh";
        return "Yeu";
    }

    void displayThongKeHocLuc(string mssv, string hocKy) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return;

        // Trích xuất CPA
        GPA_CPA result = calculateGPAAndCPA(mssv, hocKy);
        
        // Nhận nhãn học lực
        string hocLuc = evaluateHocLuc(result.cpa);

        // Xuất kết quả
        print("GPA: ", result.gpa);
        print("CPA: ", result.cpa);
        print("Hoc luc: ", hocLuc);
    }
```

**5. Phân tích độ phức tạp:**
- **Độ phức tạp thời gian:** $O(M^2)$. Khâu xử lý `if/else` để đánh giá học lực chỉ tốn $O(1)$. Tuy nhiên toàn hàm phụ thuộc hoàn toàn vào quá trình tính toán nặng nề `calculateGPAAndCPA` gọi ở bên trong.
- **Độ phức tạp không gian:** $O(M)$. Phụ thuộc vào quá trình cấp phát danh sách phụ trợ của `calculateGPAAndCPA`.