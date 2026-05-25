#include "models/HocPhan.h"
#include "models/KetQuaHocTap.h"
#include "models/SinhVien.h"

int main() {
    HocPhan hp("MI1141", "Dai so", 3, 3, 400.0);
    KetQuaHocTap kq("143211", "MI1141", 8.0, 9.0, 8.7, "A", 4.0);
    SinhVien sv("20250001", "Nguyen Van A", "IT", "KHMT", "IT1", "CNTT", "K68", 2023, "01/01/2005", "Nam", "HN", "Kinh", "0123", "a@sis", "a@gmail", "Dang hoc", "THPT", "HN");
    sv.themKetQuaHocTap(&kq);
    
    // Test the dynamic calculation
    float hocPhi = kq.tinhTongHocPhi(&hp);
    
    return 0;
}
