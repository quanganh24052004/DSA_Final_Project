#include "datastructures/LinkedList.h"
#include "datastructures/HashMap.h"
#include "models/SinhVien.h"
#include "models/HocPhan.h"
#include "models/NganhHoc.h"
#include "models/KetQuaHocTap.h"
#include "core/StudentManager.h"
#include "utils/FileHandler.h"
#include "utils/DataGenerator.h"

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMainMenu() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     HE THONG QUAN LY DAO TAO TIN CHI                  " << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 1. Quan Ly Danh Muc" << std::endl;
    std::cout << " 2. Quan Ly Diem & Ket Qua" << std::endl;
    std::cout << " 3. Logic Nghiep Vu" << std::endl;
    std::cout << " 4. Bao Cao & Tim Kiem" << std::endl;
    std::cout << " 5. Du Lieu & He Thong (Yeu cau DSA)" << std::endl;
    std::cout << " 0. Thoat Chuong Trinh" << std::endl;
    std::cout << "=======================================================" << std::endl;
}

void printSubMenu1() {
    std::cout << "\n--- 1. Quan Ly Danh Muc ---" << std::endl;
    std::cout << "1. Quan ly Mon hoc" << std::endl;
    std::cout << "2. Quan ly Lop hoc phan" << std::endl;
    std::cout << "3. Quan ly Sinh vien (Hien thi danh sach toan bo SV)" << std::endl;
    std::cout << "0. Quay lai" << std::endl;
}

void printSubMenu2() {
    std::cout << "\n--- 2. Quan Ly Diem & Ket Qua ---" << std::endl;
    std::cout << "1. Nhap diem (Theo Ma SV + Ma mon hoc)" << std::endl;
    std::cout << "2. Cap nhat / Sua diem" << std::endl;
    std::cout << "0. Quay lai" << std::endl;
}

void printSubMenu3() {
    std::cout << "\n--- 3. Logic Nghiep Vu ---" << std::endl;
    std::cout << "1. Tinh DTB hoc ky & Tich luy (He 10 & He 4)" << std::endl;
    std::cout << "2. Xep loai hoc luc (Xuat sac, Gioi, Kha...)" << std::endl;
    std::cout << "0. Quay lai" << std::endl;
}

void printSubMenu4() {
    std::cout << "\n--- 4. Bao Cao & Tim Kiem ---" << std::endl;
    std::cout << "1. Tra cuu & hien thi bang diem ca nhan cua 1 SV" << std::endl;
    std::cout << "2. Hien thi bang diem tong hop cua Lop hoc phan" << std::endl;
    std::cout << "0. Quay lai" << std::endl;
}

void printSubMenu5() {
    std::cout << "\n--- 5. Du Lieu & He Thong (Yeu cau DSA) ---" << std::endl;
    std::cout << "1. Luu / Tai du lieu tu File" << std::endl;
    std::cout << "2. Sinh du lieu mau (Mock 10.000+ data)" << std::endl;
    std::cout << "3. Danh gia hieu nang tim kiem" << std::endl;
    std::cout << "0. Quay lai" << std::endl;
}

void hienThiChiTietSinhVien(SinhVien* sv, StudentManager& manager) {
    if (sv == nullptr) return;
    
    NganhHoc* nganhCuaSV = manager.findNganhHocByMa(sv->getMaNganh());
    std::string tenNganh = (nganhCuaSV != nullptr) ? nganhCuaSV->getTenNganh() : "Khong xac dinh";

    std::cout << "\n--- THONG TIN SINH VIEN ---" << std::endl;
    std::cout << "MSSV: " << sv->getMSSV() << " | Ho ten: " << sv->getHoTen() << std::endl;
    std::cout << "Lop: " << sv->getLop() << " | Nganh: " << tenNganh << " (" << sv->getMaNganh() << ")" << std::endl;
    
    std::cout << "\n--- KET QUA HOC TAP VA HOC PHI ---" << std::endl;
    LinkedList<KetQuaHocTap*>& dsDiem = sv->getDanhSachDiem();
    if (dsDiem.isEmpty()) {
        std::cout << "Chua co du lieu diem." << std::endl;
        return;
    }

    std::cout << std::left << std::setw(10) << "MaHP" 
              << std::setw(25) << "Ten HP"
              << std::setw(10) << "Diem QTr"
              << std::setw(10) << "Diem CK"
              << std::setw(10) << "Diem HP"
              << std::setw(10) << "Diem Chu"
              << std::setw(15) << "Hoc Phi (VND)" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    Node<KetQuaHocTap*>* current = dsDiem.getHead();
    float tongHocPhiCaKy = 0;
    while (current != nullptr) {
        KetQuaHocTap* kq = current->data;
        HocPhan* thongTinMon = manager.findHocPhanByMa(kq->getMaHP());
        
        std::string tenHP = (thongTinMon != nullptr) ? thongTinMon->getTenHP() : "Unknown";
        float hocPhi = kq->tinhTongHocPhi(thongTinMon, nganhCuaSV);
        tongHocPhiCaKy += hocPhi;

        std::cout << std::left << std::setw(10) << kq->getMaHP()
                  << std::setw(25) << tenHP.substr(0, 24)
                  << std::setw(10) << kq->getDiemQTr()
                  << std::setw(10) << kq->getDiemCK()
                  << std::setw(10) << kq->getDiemHP()
                  << std::setw(10) << kq->getDiemChu()
                  << std::setw(15) << hocPhi << std::endl;
        current = current->next;
    }
    std::cout << std::string(90, '-') << std::endl;
    std::cout << "Tong hoc phi phai nop: " << tongHocPhiCaKy << " nghin VND\n" << std::endl;
}

int main(int argc, const char * argv[]) {
    StudentManager manager;
    int choice = -1;

    while (true) {
        printMainMenu();
        std::cout << "Nhap lua chon cua ban (0-5): ";
        if (!(std::cin >> choice)) {
            std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 0) {
            std::cout << "Cam on ban da su dung chuong trinh. Tam biet!" << std::endl;
            break;
        }

        switch (choice) {
            case 1: { // Quan Ly Danh Muc
                int subChoice = -1;
                while (true) {
                    printSubMenu1();
                    std::cout << "Nhap lua chon (0-3): ";
                    if (!(std::cin >> subChoice)) {
                        std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    clearInputBuffer();

                    if (subChoice == 0) break;

                    if (subChoice == 1) {
                        std::cout << "Chuc nang quan ly Mon hoc dang duoc cap nhat..." << std::endl;
                    } else if (subChoice == 2) {
                        std::cout << "Chuc nang quan ly Lop hoc phan dang duoc cap nhat..." << std::endl;
                    } else if (subChoice == 3) {
                        std::cout << "\nDanh sach toan bo sinh vien (" << manager.getStudentCount() << " records):" << std::endl;
                        manager.printAll();
                    } else {
                        std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                    }
                }
                break;
            }
            case 2: { // Quan Ly Diem & Ket Qua
                int subChoice = -1;
                while (true) {
                    printSubMenu2();
                    std::cout << "Nhap lua chon (0-2): ";
                    if (!(std::cin >> subChoice)) {
                        std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    clearInputBuffer();

                    if (subChoice == 0) break;

                    if (subChoice == 1) {
                        std::cout << "Chuc nang Nhap diem dang duoc cap nhat..." << std::endl;
                    } else if (subChoice == 2) {
                        std::cout << "Chuc nang Cap nhat / Sua diem dang duoc cap nhat..." << std::endl;
                    } else {
                        std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                    }
                }
                break;
            }
            case 3: { // Logic Nghiep Vu
                int subChoice = -1;
                while (true) {
                    printSubMenu3();
                    std::cout << "Nhap lua chon (0-2): ";
                    if (!(std::cin >> subChoice)) {
                        std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    clearInputBuffer();

                    if (subChoice == 0) break;

                    if (subChoice == 1) {
                        std::cout << "Chuc nang Tinh DTB hoc ky & Tich luy dang duoc cap nhat..." << std::endl;
                    } else if (subChoice == 2) {
                        std::cout << "Chuc nang Xep loai hoc luc dang duoc cap nhat..." << std::endl;
                    } else {
                        std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                    }
                }
                break;
            }
            case 4: { // Bao Cao & Tim Kiem
                int subChoice = -1;
                while (true) {
                    printSubMenu4();
                    std::cout << "Nhap lua chon (0-2): ";
                    if (!(std::cin >> subChoice)) {
                        std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    clearInputBuffer();

                    if (subChoice == 0) break;

                    if (subChoice == 1) {
                        std::string mssv;
                        std::cout << "Nhap MSSV can tim: ";
                        std::getline(std::cin, mssv);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        SinhVien* sv = manager.findSinhVienByMSSV(mssv);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::nano> duration = end - start;

                        if (sv != nullptr) {
                            hienThiChiTietSinhVien(sv, manager);
                            std::cout << "[Thong ke] Thoi gian tim kiem bang Hash Map: " 
                                      << std::fixed << std::setprecision(2) << duration.count() 
                                      << " ns (O(1))" << std::endl;
                        } else {
                            std::cout << "Khong tim thay sinh vien co MSSV: " << mssv << std::endl;
                        }
                    } else if (subChoice == 2) {
                        std::cout << "Chuc nang Hien thi bang diem tong hop cua Lop hoc phan dang duoc cap nhat..." << std::endl;
                    } else {
                        std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                    }
                }
                break;
            }
            case 5: { // Du Lieu & He Thong (Yeu cau DSA)
                int subChoice = -1;
                while (true) {
                    printSubMenu5();
                    std::cout << "Nhap lua chon (0-3): ";
                    if (!(std::cin >> subChoice)) {
                        std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    clearInputBuffer();

                    if (subChoice == 0) break;

                    if (subChoice == 1) {
                        int loadChoice = -1;
                        std::cout << "\n--- CHON CHE DO TAI DU LIEU ---" << std::endl;
                        std::cout << "1. Tai toan bo du lieu mac dinh (Xoa du lieu cu)" << std::endl;
                        std::cout << "2. Tai them tu file cu the (Giu nguyen du lieu hien tai)" << std::endl;
                        std::cout << "Nhap lua chon: ";
                        if (!(std::cin >> loadChoice)) {
                            std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                            clearInputBuffer();
                            continue;
                        }
                        clearInputBuffer();

                        if (loadChoice == 1) {
                            std::cout << "Dang tai du lieu mac dinh..." << std::endl;
                            manager.cleanUp(); // Reset truoc khi tai
                            FileHandler::loadNganhHoc("../NganhHoc.csv", manager);
                            FileHandler::loadHocPhan("../HocPhan.csv", manager);
                            FileHandler::loadSinhVien("../DanhSachSinhVien.csv", manager);
                            FileHandler::loadDiem("../Diem_DaiSo.csv", manager, "MI1141");
                            FileHandler::loadDiem("../Diem_GT1.csv", manager, "MI1111");
                            FileHandler::loadDiem("../Diem_TinHoc.csv", manager, "IT1110");
                            FileHandler::loadDiem("../Diem_Triet.csv", manager, "LL1111");
                        } else if (loadChoice == 2) {
                            int fileType = -1;
                            std::cout << "\n--- CHON LOAI DU LIEU MUON TAI ---" << std::endl;
                            std::cout << "1. Nganh hoc" << std::endl;
                            std::cout << "2. Hoc phan" << std::endl;
                            std::cout << "3. Sinh vien" << std::endl;
                            std::cout << "4. Diem" << std::endl;
                            std::cout << "Nhap lua chon: ";
                            
                            if (!(std::cin >> fileType)) {
                                std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                                clearInputBuffer();
                                continue;
                            }
                            clearInputBuffer();

                            std::string filePath;
                            std::cout << "Nhap duong dan file (.csv)\n";
                            std::cout << "(Meo: Neu ban dang chay tu thu muc build, ban can dung ../ truoc ten file, VD: ../NganhHoc.csv): ";
                            std::getline(std::cin, filePath);

                            switch (fileType) {
                                case 1:
                                    FileHandler::loadNganhHoc(filePath, manager);
                                    break;
                                case 2:
                                    FileHandler::loadHocPhan(filePath, manager);
                                    break;
                                case 3:
                                    FileHandler::loadSinhVien(filePath, manager);
                                    break;
                                case 4: {
                                    std::string maHP;
                                    std::cout << "Nhap ma hoc phan mac dinh (VD: MI1141 - De trong neu file da co san ma HP): ";
                                    std::getline(std::cin, maHP);
                                    FileHandler::loadDiem(filePath, manager, maHP);
                                    break;
                                }
                                default:
                                    std::cout << "Loi: Lua chon loai du lieu khong hop le!" << std::endl;
                                    break;
                            }
                        } else {
                            std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                        }
                    } else if (subChoice == 2) {
                        std::cout << "Dang tao mock data (10000 sinh vien)..." << std::endl;
                        // Thay đổi số lượng từ 1000 lên 10000 để phù hợp với menu mới
                        DataGenerator::generateMockData(10000); 
                    } else if (subChoice == 3) {
                        std::cout << "Chuc nang Danh gia hieu nang tim kiem dang duoc cap nhat..." << std::endl;
                    } else {
                        std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                    }
                }
                break;
            }
            default:
                std::cout << "Loi: Lua chon khong hop le! Vui long nhap tu 0 den 5." << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

