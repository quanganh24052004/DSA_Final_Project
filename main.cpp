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

void printMenuHeader() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     CHUONG TRINH QUAN LY SINH VIEN (4-TABLE 3NF)      " << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 1. Tu dong sinh Mock Data (CSV)" << std::endl;
    std::cout << " 2. Tai du lieu (NganhHoc, HocPhan, SinhVien, Diem)" << std::endl;
    std::cout << " 3. Tim kiem sinh vien bang MSSV (Kem Bang Diem/Hoc Phi)" << std::endl;
    std::cout << " 4. Hien thi danh sach toan bo sinh vien" << std::endl;
    std::cout << " 0. Thoat chuong trinh" << std::endl;
    std::cout << "=======================================================" << std::endl;
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
        printMenuHeader();
        std::cout << "Nhap lua chon cua ban (0-4): ";
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
            case 1: { // Generate Data
                std::cout << "Dang tao mock data (1000 sinh vien)..." << std::endl;
                DataGenerator::generateMockData(1000);
                break;
            }
            case 2: { // Load CSV
                int subChoice = -1;
                std::cout << "\n--- CHON CHE DO TAI DU LIEU ---" << std::endl;
                std::cout << "1. Tai toan bo du lieu mac dinh (Xoa du lieu cu)" << std::endl;
                std::cout << "2. Tai them tu file cu the (Giu nguyen du lieu hien tai)" << std::endl;
                std::cout << "Nhap lua chon: ";
                if (!(std::cin >> subChoice)) {
                    std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                if (subChoice == 1) {
                    std::cout << "Dang tai du lieu mac dinh..." << std::endl;
                    manager.cleanUp(); // Reset truoc khi tai
                    FileHandler::loadNganhHoc("../NganhHoc.csv", manager);
                    FileHandler::loadHocPhan("../HocPhan.csv", manager);
                    FileHandler::loadSinhVien("../DanhSachSinhVien.csv", manager);
                    FileHandler::loadDiem("../Diem_DaiSo.csv", manager, "MI1141");
                    FileHandler::loadDiem("../Diem_GT1.csv", manager, "MI1111");
                    FileHandler::loadDiem("../Diem_TinHoc.csv", manager, "IT1110");
                    FileHandler::loadDiem("../Diem_Triet.csv", manager, "LL1111");
                } else if (subChoice == 2) {
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
                        break;
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
                break;
            }
            case 3: { // Search by MSSV
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
                break;
            }
            case 4: { // Display All
                std::cout << "Danh sach toan bo sinh vien (" << manager.getStudentCount() << " records):" << std::endl;
                manager.printAll();
                break;
            }
            default:
                std::cout << "Loi: Lua chon khong hop le!" << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
