# Viết giả mã cho các thuật toán
## 1. Module Thao Tác Dữ Liệu Gốc
### 1.1. Chức năng Quản lý Sinh Viên
#### a. Thêm sinh viên mới (`addSinhVien`)
```
    bool addSinhVien(SinhVien* sv) {
        if sv == NULL then return false;
        if danhSachSinhVien.get(sv->getMSSV()) != NULL then return false;   // Sinh viên đã tồn tại, không thể thêm

        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }
```
- Chú thích:
    + Các đối tượng:
        + `SinhVien`.
        + `danhSachSinhVien` (là bảng băm).
    + Các hàm được gọi:
        + `sv->getMSSV()`: Hàm của đối tượng `SinhVien`, trả về MSSV.
        + `danhSachSinhVien.get`: Hàm của bảng băm `danhSachSinhVien`, trả về con trỏ của đối tượng sinh viên thông qua MSSV.
        + `danhSachSinhVien.put`: Hàm của bảng băm `danhSachSinhVien`, trả về `true` nếu thành công nạp sinh viên vào bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### b. Cập nhật thông tin sinh viên (`updateSinhVien`)
```
    bool updateSinhVien(SinhVien* sv) {
        if sv == NULL then return false;
        if danhSachSinhVien.get(sv->getMSSV()) == NULL then return false;    // Sinh viên chưa tồn tại để update

        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `danhSachSinhVien` (là bảng băm).
    + Các hàm được gọi: `sv->getMSSV()`, `danhSachSinhVien.get`, `danhSachSinhVien.put`(xem 1.1.a).
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### c. Xóa thông tin sinh viên (removeSinhVien)
```
    bool removeSinhVien(string mssv) {
        SinhVien* sv = danhSachSinhVien.get(mssv);
        if sv != NULL then {
            if danhSachSinhVien.remove(mssv) == true then {
                delete sv;
                return true;
            }
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `danhSachSinhVien` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachSinhVien.get` (xem 1.1.a.).
        + `danhSachSinhVien.remove`: Hàm của bảng băm `danhSachSinhVien`, trả về `true` nếu thành công xoá sinh viên khỏi bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### d. Một số hàm phụ trợ
```
    SinhVien* findSinhVienByMSSV(string mssv) {
        return danhSachSinhVien.get(mssv);
    }

    size_t getStudentCount() {
        return danhSachSinhVien.getSize();
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `danhSachSinhVien` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachSinhVien.get` (xem 1.1.a.).
        + `danhSachSinhVien.getSize()`: Hàm của bảng băm `danhSachSinhVien`, trả về số nút có trong bảng băm.
- Độ phức tạp (cho cả hai hàm):
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

### 1.2. Chức năng Quản lý Ngành học
#### a. Thêm ngành học mới (`addNganhHoc`)
```
    bool addNganhHoc(NganhHoc* nh) {
        if nh == NULL then return false;
        if danhSachNganhHoc.get(nh->getMaNganh()) != NULL then return false;    // Ngành học đã tồn tại để thêm

        danhSachNganhHoc.put(nh->getMaNganh(), nh);
        return true;
    }
```
- Chú thích:
    + Các đối tượng:
        + `NganhHoc`.
        + `danhSachNganhHoc` (là bảng băm).
    + Các hàm được gọi:
        + `nh->getMaNganh()`: Hàm của đối tượng `NganhHoc`, trả về mã ngành học.
        + `danhSachNganhHoc.get`: Hàm của bảng băm `danhSachNganhHoc`, trả về con trỏ của đối tượng ngành học thông qua mã ngành.
        + `danhSachNganhHoc.put`: Hàm của bảng băm `danhSachNganhHoc`, trả về `true` nếu thành công nạp ngành học vào bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### b. Cập nhật thông tin ngành học (`updateNganhHoc`)
```
    bool updateNganhHoc(NganhHoc* nh) {
        if nh == NULL then return false;
        if danhSachNganhHoc.get(nh->getMaNganh()) == NULL then return false;    // Ngành học chưa tồn tại để update

        danhSachNganhHoc.put(nh->getMaNganh(), nh);
        return true;
    }
```
- Chú thích:
    + Các đối tượng: `NganhHoc`, `danhSachNganhHoc` (là bảng băm).
    + Các hàm được gọi: `nh->getMaNganh()`, `danhSachNganhHoc.get`, `danhSachNganhHoc.put` (xem 1.2.a.).
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### c. Xóa thông tin ngành học (`removeNganhHoc`)
```
    bool removeNganhHoc(string maNganh) {
        NganhHoc* nh = danhSachNganhHoc.get(maNganh);
        if nh != NULL then {
            if danhSachNganhHoc.remove(maNganh) == true then {
                delete nh;
                return true;
            }
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `NganhHoc`, `danhSachNganhHoc` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachNganhHoc.get` (xem 1.2.a.).
        + `danhSachNganhHoc.remove`: Hàm của bảng băm danh sách ngành học.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### d. Một số hàm phụ trợ
```
    NganhHoc* findNganhHocByMa(string maNganh) {
        return danhSachNganhHoc.get(maNganh);
    }
```
- Chú thích:
    + Các đối tượng: `NganhHoc`, `danhSachNganhHoc` (là bảng băm).
    + Các hàm được gọi: `danhSachNganhHoc.get` (xem 1.2.a.).
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

### 1.3. Chức năng Quản lý Học Phần
#### a. Thêm học phần mới (`addHocPhan`)
```
    bool addHocPhan(HocPhan* hp) {
        if hp == NULL then return false;
        if danhSachHocPhan.get(hp->getMaHP()) != NULL then return false;   // Học phần đã tồn tại, không thể thêm

        danhSachHocPhan.put(hp->getMaHP(), hp);
        return true;
    }
```
- Chú thích:
    + Các đối tượng:
        + `HocPhan`.
        + `danhSachHocPhan` (là bảng băm).
    + Các hàm được gọi:
        + `hp->getMaHP()`: Hàm của đối tượng `HocPhan`, trả về mã học phần.
        + `danhSachHocPhan.get`: Hàm của bảng băm `danhSachHocPhan`, trả về con trỏ của đối tượng học phần thông qua mã học phần.
        + `danhSachHocPhan.put`: Hàm của bảng băm `danhSachHocPhan`, trả về `true` nếu thành công nạp học phần vào bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### b. Cập nhật thông tin học phần (`updateHocPhan`)
```
    bool updateHocPhan(HocPhan* hp) {
        if hp == NULL then return false;
        if danhSachHocPhan.get(hp->getMaHP()) == NULL then return false;    // Học phần chưa tồn tại để update

        danhSachHocPhan.put(hp->getMaHP(), hp);
        return true;
    }
```
- Chú thích:
    + Các đối tượng: `HocPhan`, `danhSachHocPhan` (là bảng băm).
    + Các hàm được gọi: `hp->getMaHP()`, `danhSachHocPhan.get`, `danhSachHocPhan.put` (xem 1.3.a).
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### c. Xóa thông tin học phần (`removeHocPhan`)
```
    bool removeHocPhan(string maHP) {
        HocPhan* hp = danhSachHocPhan.get(maHP);
        if hp != NULL then {
            if danhSachHocPhan.remove(maHP) == true then {
                delete hp;
                return true;
            }
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `HocPhan`, `danhSachHocPhan` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachHocPhan.get` (xem 1.3.a.).
        + `danhSachHocPhan.remove`: Hàm của bảng băm `danhSachHocPhan`, trả về `true` nếu thành công xoá học phần khỏi bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### d. Một số hàm phụ trợ
```
    HocPhan* findHocPhanByMa(string maHP) {
        return danhSachHocPhan.get(maHP);
    }
```
- Chú thích:
    + Các đối tượng: `HocPhan`, `danhSachHocPhan` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachHocPhan.get` (xem 1.3.a.).
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

### 1.4. Chức năng Quản lý Lớp Học Phần
#### a. Thêm lớp học phần mới (`addLopHocPhan`)
```
    bool addLopHocPhan(LopHocPhan* lhp) {
        if lhp == NULL then return false;
        if danhSachLopHocPhan.get(lhp->getMaLop()) != NULL then return false;   // Lớp học phần đã tồn tại

        danhSachLopHocPhan.put(lhp->getMaLop(), lhp);
        return true;
    }
```
- Chú thích:
    + Các đối tượng:
        + `LopHocPhan`.
        + `danhSachLopHocPhan` (là bảng băm).
    + Các hàm được gọi:
        + `lhp->getMaLop()`: Hàm của đối tượng `LopHocPhan`, trả về mã lớp học phần.
        + `danhSachLopHocPhan.get`: Hàm của bảng băm `danhSachLopHocPhan`, trả về con trỏ của đối tượng lớp học phần thông qua mã lớp.
        + `danhSachLopHocPhan.put`: Hàm của bảng băm `danhSachLopHocPhan`, trả về `true` nếu thành công nạp lớp học phần vào bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### b. Xóa thông tin lớp học phần (`removeLopHocPhan`)
```
    bool removeLopHocPhan(string maLop) {
        LopHocPhan* lhp = danhSachLopHocPhan.get(maLop);
        if lhp != NULL then {
            if danhSachLopHocPhan.remove(maLop) == true then {
                delete lhp;
                return true;
            }
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `LopHocPhan`, `danhSachLopHocPhan` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachLopHocPhan.get` (xem 1.4.a.).
        + `danhSachLopHocPhan.remove`: Hàm của bảng băm `danhSachLopHocPhan`, trả về `true` nếu thành công xoá lớp học phần khỏi bảng băm.
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

#### c. Đăng ký sinh viên vào lớp học phần (`registerSinhVienToLop`)
```
    bool registerSinhVienToLop(string mssv, string maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        
        if sv != NULL and lhp != NULL then {
            return lhp->addSinhVien(sv);
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `LopHocPhan`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV`: Hàm phụ trợ trả về con trỏ đối tượng sinh viên qua MSSV.
        + `findLopHocPhanByMa`: Hàm phụ trợ trả về con trỏ đối tượng lớp học phần qua mã lớp.
        + `lhp->addSinhVien`: Hàm của đối tượng `LopHocPhan` để thêm sinh viên vào danh sách lớp đó, trả về `true` nếu thêm thành công.
- Độ phức tạp:
        + Thời gian: Trung bình $O(K)$. (Với $K$ là số sinh viên trong lớp. Tra cứu sinh viên/lớp mất $O(1)$, hàm `addSinhVien` của lớp học phần phải duyệt qua $K$ sinh viên hiện tại để kiểm tra trùng lặp trước khi thêm).
        + Không gian: $O(1)$.

#### d. Hủy đăng ký sinh viên khỏi lớp học phần (`unregisterSinhVienFromLop`)
```
    bool unregisterSinhVienFromLop(string mssv, string maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        
        if sv != NULL and lhp != NULL then {
            return lhp->removeSinhVien(sv);
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `LopHocPhan`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV`, `findLopHocPhanByMa` (xem 1.4.c).
        + `lhp->removeSinhVien`: Hàm của đối tượng `LopHocPhan`, dùng để xoá sinh viên khỏi danh sách của lớp đó.
- Độ phức tạp:
        + Thời gian: Trung bình $O(K)$. (Với $K$ là số sinh viên trong lớp. Tra cứu sinh viên/lớp mất $O(1)$, thao tác `remove` phải duyệt qua danh sách trong lớp học phần kích thước $K$ để tìm nút cần xóa).
        + Không gian: $O(1)$.

#### e. Một số hàm phụ trợ
```
    LopHocPhan* findLopHocPhanByMa(string maLop) {
        return danhSachLopHocPhan.get(maLop);
    }
```
- Chú thích:
    + Các đối tượng: `LopHocPhan`, `danhSachLopHocPhan` (là bảng băm).
    + Các hàm được gọi:
        + `danhSachLopHocPhan.get` (xem 1.4.a.).
- Độ phức tạp:
        + Thời gian: $O(1)$ trung bình với bảng băm.
        + Không gian: $O(1)$.

### 1.5. Chức năng Quản lý Kết quả học tập
#### a. Thêm kết quả học tập (`addDiem`)
```
    bool addDiem(string mssv, string maLop, string maHP, float diemQTr, float diemCK, float trongSoQTr) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return false;
    
        // Tính toán điểm số, gán đối tượng kết quả
        float diemHP = diemQTr * trongSoQTr + diemCK * (1.0 - trongSoQTr);
        KetQuaHocTap* kq = new KetQuaHocTap(maLop, maHP, diemQTr, diemCK, diemHP, xepLoaiDiemChu(diemHP), quyDoiHe4(diemHP));
    
        // Kiểm tra mã lớp đã tồn tại chưa ngay trong thực thể SinhVien
        if sv->themKetQuaHocTap(kq) == true then {
            return true;
        } else {
            delete kq;  // Nếu SinhVien báo trùng (false), huỷ vùng nhớ vừa cấp phát
            return false;
        }
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `KetQuaHocTap`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV`: Hàm phụ trợ trả về con trỏ của đối tượng sinh viên qua MSSV (xem 1.1.d.).
        + `xepLoaiDiemChu`, `quyDoiHe4`: Các hàm phụ trợ quy đổi điểm (xem 1.5.d.).
        + `sv->themKetQuaHocTap`: Hàm của đối tượng `SinhVien`, dùng để nạp đối tượng điểm mới vào danh sách điểm của sinh viên; trả về `true` nếu thêm thành công, hoặc `false` nếu mã lớp học phần (`maLop`) đã tồn tại.
- Độ phức tạp:
        + Thời gian: Trung bình $O(M)$. (Với $M$ là số học phần một sinh viên đã học. Phải duyệt qua danh sách điểm có kích thước $M$ của sinh viên đó để kiểm tra trùng mã lớp khi thêm).
        + Không gian: $O(1)$.

#### b. Cập nhật thông tin điểm số (`updateDiem`)
```
    bool updateDiem(string mssv, string maLop, float diemQTrMoi, float diemCKMoi, float trongSoQTr) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return false;
        
        // Duyệt danh sách điểm để tìm điểm cần cập nhật (theo mã lớp)
        Node* current = sv->getDanhSachDiem().getHead();
        while current != NULL do {
            if current->data->getMaLop() == maLop then {
                float diemHP = diemQTrMoi * trongSoQTr + diemCKMoi * (1.0 - trongSoQTr);
                current->data->setDiemQTr(diemQTrMoi);
                current->data->setDiemCK(diemCKMoi);
                current->data->setDiemHP(diemHP);
                current->data->setDiemChu(xepLoaiDiemChu(diemHP));
                current->data->setThang4(quyDoiHe4(diemHP));
                return true;
            }
            current = current->next;
        }
        return false;
    }
```

- Chú thích:
    + Các đối tượng: `SinhVien`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV`, `xepLoaiDiemChu`, `quyDoiHe4`.
        + `sv->getDanhSachDiem().getHead()`: Truy xuất nút đầu tiên của danh sách điểm.
        + `current->data->getMaLop()`: Lấy mã lớp từ đối tượng điểm để so sánh.
        + Các hàm `set...`: Cập nhật lại các trường dữ liệu điểm bên trong đối tượng `KetQuaHocTap`.
- Độ phức tạp:
        + Thời gian: Trung bình $O(M)$. (Với $M$ là số học phần một sinh viên đã học. Phải tìm kiếm mã lớp trong danh sách điểm có kích thước $M$ của sinh viên đó để cập nhật).
        + Không gian: $O(1)$.

#### c. Xóa thông tin điểm số (`removeDiem`)
```
    bool removeDiem(string mssv, string maLop) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return false;
        
        // Duyệt danh sách điểm để tìm điểm cần xoá (theo mã lớp)
        Node* current = sv->getDanhSachDiem().getHead();
        while current != NULL do {
            if current->data->getMaLop() == maLop then {
                KetQuaHocTap* kq = current->data;
                sv->getDanhSachDiem().remove(kq);
                delete kq;
                return true;
            }
            current = current->next;
        }
        return false;
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `KetQuaHocTap`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV`, `sv->getDanhSachDiem().getHead()`, `current->data->getMaLop()`.
        + `sv->getDanhSachDiem().remove(kq)`: Hàm của danh sách liên kết điểm, dùng để ngắt kết nối nút chứa điểm cần xóa.
- Độ phức tạp:
        + Thời gian: Trung bình $O(M)$. (Với $M$ là số học phần một sinh viên đã học. Phải tìm kiếm mã lớp trong danh sách điểm có kích thước $M$ của sinh viên đó để xoá).
        + Không gian: $O(1)$.

#### d. Một số hàm phụ trợ
```
    string xepLoaiDiemChu(float diemHP) {
        if diemHP >= 8.5 then return "A";
        if diemHP >= 8.0 then return "B+";
        if diemHP >= 7.0 then return "B";
        if diemHP >= 6.5 then return "C+";
        if diemHP >= 5.5 then return "C";
        if diemHP >= 5.0 then return "D+";
        if diemHP >= 4.0 then return "D";
        return "F";
    }

    float quyDoiHe4(float diemHP) {
        if diemHP >= 8.5 then return 4.0;
        if diemHP >= 8.0 then return 3.5;
        if diemHP >= 7.0 then return 3.0;
        if diemHP >= 6.5 then return 2.5;
        if diemHP >= 5.5 then return 2.0;
        if diemHP >= 5.0 then return 1.5;
        if diemHP >= 4.0 then return 1.0;
        return 0.0;
    }
```
- Độ phức tạp:
        + Thời gian: $O(1)$.
        + Không gian: $O(1)$.

## 2. Module Chiết Xuất & Hiển Thị Thông Tin
### 2.1. Chức năng tra cứu & hiển thị bảng điểm cá nhân (`displayBangDiemCaNhan`)
```
    void displayBangDiemCaNhan(string mssv) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then {
            // Thông báo không tìm thấy sinh viên
            return;
        }

        // 1. In tiêu đề và thông tin sinh viên

        // 2. Lấy danh sách điểm của sinh viên
        Node* current = sv->getDanhSachDiem().getHead();
        if current == NULL then {
            // Thông báo chưa có dữ liệu điểm
        }

        // 3. Duyệt từng nút điểm để in thông tin chi tiết
        while current != NULL do {
            KetQuaHocTap* kq = current->data;
            HocPhan* hp = findHocPhanByMa(kq->getMaHP());
            
            string tenHP = "N/A";
            int stc = 0;
            if hp != NULL then {
                tenHP = hp->getTenHP();
                stc = hp->getSoTinChi();
            }

            // In thông tin (một dòng) điểm chi tiết của sinh viên
            
            current = current->next;
        }
        // 4. In đường viền đóng bảng điểm
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `Node<KetQuaHocTap*>`, `KetQuaHocTap`, `HocPhan`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV` (xem 1.1.d.).
        + `findHocPhanByMa` (xem 1.3.d.).
        + `sv->getDanhSachDiem().getHead()`: Truy xuất nút đầu tiên trong Linked List danh sách điểm của sinh viên.
- Độ phức tạp:
        + Thời gian: Trung bình $O(M)$. (Hàm thực hiện một vòng lặp duyệt qua đúng $M$ môn học của sinh viên. Bên trong vòng lặp gọi các hàm với chi phí $O(1)$ trung bình).
        + Không gian: $O(1)$ (In trực tiếp ra màn hình, không dùng cấu trúc dữ liệu lưu trữ phụ).

### 2.2. Chức năng hiển thị bảng điểm của Lớp HP (`displayBangDiemLopHP`)
```
    void displayBangDiemLopHP(string maLop) {
        LopHocPhan* lhp = findLopHocPhanByMa(maLop);
        if lhp == NULL then {
            // Thông báo không tìm thấy lớp học phần
            return;
        }

        HocPhan* hp = findHocPhanByMa(lhp->getMaHP());
        string tenHP = "N/A";
        if hp != NULL then {
            tenHP = hp->getTenHP();
        }

        // 1. In tiêu đề của lớp học phần

        // 2. Duyệt qua danh sách sinh viên đăng ký trong lớp học phần
        Node* currentSV = lhp->getDanhSachSinhVien().getHead();     // Node sinh viên trong lớp
        if currentSV == NULL then {
            // Thông báo chưa có sinh viên
        }

        while currentSV != NULL do {
            SinhVien* sv = currentSV->data;
            
            // Vòng lặp trong: Tra cứu KetQuaHocTap của lớp học phần này trong danh sách điểm của sinh viên
            KetQuaHocTap* kqTarget = NULL;
            Node* kqNode = sv->getDanhSachDiem().getHead();     // Node kết quả học tập của sinh viên
            while kqNode != NULL do {
                if kqNode->data->getMaLop() == maLop then {
                    kqTarget = kqNode->data;
                    break;  // Đã tìm thấy điểm
                }
                kqNode = kqNode->next;
            }

            string hoTen = sv->getHoTen();

            // 3. In kết quả nếu tìm thấy điểm
            if kqTarget != NULL then {
                // In kết quả cho một dòng
            }

            currentSV = currentSV->next;
        }
        // 4. In đường viền đóng bảng điểm
    }
```
- Chú thích:
    + Các đối tượng: `LopHocPhan`, `Node<SinhVien*>`, `SinhVien`, `Node<KetQuaHocTap*>`, `KetQuaHocTap`, `HocPhan`.
    + Các hàm được gọi:
        + `findLopHocPhanByMa` (xem 1.4.e.).
        + `findHocPhanByMa` (xem 1.3.d.).
        + `lhp->getDanhSachSinhVien().getHead()`: Truy xuất danh sách sinh viên đăng ký học lớp học phần này.
        + `sv->getDanhSachDiem().getHead()`: Truy xuất danh sách điểm của sinh viên hiện tại.
- Độ phức tạp:
        + Thời gian: $O(KM)$. (Có $K$ sinh viên trong lớp, ứng với mỗi sinh viên, vòng lặp trong phải duyệt qua danh sách $M$ (số học phần trung bình một sinh viên đã học) học phần của sinh viên đó để tìm đúng điểm của lớp này).
        + Không gian: $O(1)$ (In trực tiếp ra màn hình, không dùng cấu trúc dữ liệu lưu trữ phụ).

## 3. Module Thống Kê & Đánh Giá Học Lực
### 3.1. Chức năng tính GPA & CPA (calculateGPAAndCPA)
*(Lưu ý: Dùng danh sách phụ trợ `listCPA` để lọc môn học lại và lấy điểm cao nhất để cộng dồn cho CPA).*
```
    ADT GPA_CPA {
        float gpa;
        float cpa;

        GPA_CPA(float g, float c) {
            gpa = g;
            cpa = c;
        }
    }

    GPA_CPA calculateGPAAndCPA(string mssv, string hocKy) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then return GPA_CPA(0.0,0.0);

        float sumGPA = 0.0, sumCPA = 0.0;
        int creditsGPA = 0, creditsCPA = 0;

        // Khởi tạo danh sách phụ trợ để lọc môn học lại cho CPA
        LinkedList listCPA;     // Khởi tạo trên Stack, với Node chứa kết quả học tập 
        Node* current = sv->getDanhSachDiem().getHead();

        // Vòng lặp 1: Tính GPA và lọc dữ liệu cho CPA
        while current != NULL do {
            KetQuaHocTap* kq = current->data;
            HocPhan* hp = findHocPhanByMa(kq->getMaHP());
            LopHocPhan* lhp = findLopHocPhanByMa(kq->getMaLop());

            if hp != NULL AND lhp != NULL then {    // Cần tra cứu và giải tham chiếu với hp và lhp
                int stc = hp->getSoTinChi();
                float diem4 = kq->getThang4();

                // 1. Xử lý GPA (Chỉ cộng dồn nếu khớp học kỳ)
                if lhp->getHocKy() == hocKy then {
                    sumGPA = sumGPA + (diem4 * stc);
                    creditsGPA = creditsGPA + stc;
                }

                // 2. Xử lý CPA (Lọc trùng lặp, chỉ lấy điểm cao nhất)
                bool foundInCPA = false;
                Node* cpaNode = listCPA.getHead();  // Node chứa kết quả học tập
                while cpaNode != NULL do {
                    if cpaNode->data->getMaHP() == kq->getMaHP() then {
                        foundInCPA = true;

                        // Nếu môn này đã có trong listCPA nhưng điểm đang xét ở vòng ngoài cao hơn thì cập nhật
                        if diem4 > cpaNode->data->getThang4() then {
                            cpaNode->data = kq;     // Đưa con trỏ trỏ sang nơi khác (điểm cao hơn)
                        }
                        break;  // Thoát vòng lặp con
                    }
                    cpaNode = cpaNode->next;
                }

                // Nếu duyệt hết listCPA mà chưa có môn này thì thêm mới vào
                if foundInCPA == false then {
                    listCPA.insertAtHead(kq);   // Ở đây chọn head hay tail cũng không sai
                }
            }
            current = current->next;
        }

        // Vòng lặp 2: Tính tổng CPA từ danh sách đã lọc
        Node* cpaNode = listCPA.getHead();  // Node chứa KetQuaHocTap
        while cpaNode != NULL do {
            KetQuaHocTap* kqCPA = cpaNode->data;
            HocPhan* hpCPA = findHocPhanByMa(kqCPA->getMaHP());
            
            // kqCPA và hpCPA đã được đảm bảo khác NULL vì biến `current` và `hp` được thiết lập
            int stc = hpCPA->getSoTinChi();
            sumCPA = sumCPA + (kqCPA->getThang4() * stc);
            creditsCPA = creditsCPA + stc;

            cpaNode = cpaNode->next;
        }

        // Tính toán kết quả cuối cùng (tránh lỗi chia cho 0)
        float gpa = 0.0;
        if creditsGPA > 0 then gpa = sumGPA / creditsGPA;

        float cpa = 0.0;
        if creditsCPA > 0 then cpa = sumCPA / creditsCPA;

        // Giải phóng danh sách phụ trợ
        listCPA.clear();    // Hàm clear để xoá các Node trên Heap

        GPA_CPA result = GPA_CPA(gpa, cpa);
        return result;
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`, `KetQuaHocTap`, `HocPhan`, `LopHocPhan`, `LinkedList<KetQuaHocTap*>` (Danh sách phụ trợ).
    + Các hàm được gọi:
        + `findSinhVienByMSSV`, `findHocPhanByMa`, `findLopHocPhanByMa`: Các hàm tra cứu phụ trợ.
        + `sv->getDanhSachDiem().getHead()`: Lấy danh sách điểm gốc của sinh viên.
        + `listCPA.insertAtHead(kq)`: Thêm con trỏ điểm vào danh sách phụ trợ.
- Độ phức tạp:
        + Thời gian: $O(M^2)$.
        Giải thích: Vòng lặp 1 duyệt qua $M$ điểm gốc. Tại mỗi bước, vòng lặp nhỏ bên trong phải lội qua danh sách phụ trợ listCPA (kích thước $O(M)$) để tìm môn học lại; cho ra tác vụ với chi phí $O(M^2)$. Vòng lặp 2 duyệt lại listCPA với chi phí $O(M)$. Phép toán chi phối toàn hàm là $O(M^2)$.
        + Không gian: $O(M)$.
        Giải thích: Khởi tạo danh sách phụ trợ listCPA trên Stack và Heap. Trong trường hợp sinh viên không học lại môn nào, danh sách này chứa đúng $M$ nút kết quả học tập.

### 3.2. Chức năng Đánh giá học lực
#### a. Hiển thị Thống kê Học lực (`displayThongKeHocLuc`)
```
    // Dùng đến ADT GPA_CPA
    void displayThongKeHocLuc(string mssv, string hocKy) {
        SinhVien* sv = findSinhVienByMSSV(mssv);
        if sv == NULL then {
            // Thông báo không tìm thấy sinh viên
            return;
        }

        // Gọi hàm tính toán
        GPA_CPA result = calculateGPAAndCPA(mssv, hocKy);
        float gpa = result.gpa;
        float cpa = result.cpa;
        
        // Gọi hàm xếp loại
        string hocLuc = evaluateHocLuc(cpa);

        // In các kết quả ra màn hình
    }
```
- Chú thích:
    + Các đối tượng: `SinhVien`.
    + Các hàm được gọi:
        + `findSinhVienByMSSV`: Hàm tra cứu sinh viên.
        + `calculateGPAAndCPA`: Hàm tính toán điểm ở mục 3.a.
        + `evaluateHocLuc`: Hàm phụ trợ xếp loại học lực.
- Độ phức tạp:
        + Thời gian: $O(M^2)$ (Phụ thuộc hoàn toàn vào hàm `calculateGPAAndCPA` được gọi bên trong, hàm xếp loại `evaluateHocLuc` chỉ có chi phí $O(1)$).
        + Không gian: $O(M)$ (Độ phức tạp không gian kế thừa từ hàm tính điểm do phải tạo list phụ trợ).

#### b. Hàm hỗ trợ lấy chuỗi xếp loại từ CPA (evaluateHocLuc) 
```
    string evaluateHocLuc(float cpa) {
        if cpa >= 3.6 then return "Xuat sac";
        if cpa >= 3.2 then return "Gioi";
        if cpa >= 2.5 then return "Kha";
        if cpa >= 2.0 then return "Trung binh";
        return "Yeu";
    }
```
- Độ phức tạp:
        + Thời gian: $O(1)$.
        + Không gian: $O(1)$.