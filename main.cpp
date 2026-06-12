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
#include <vector>
#include <cstdlib>
#include <ctime>

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
    std::cout << "1. Quan ly Hoc phan" << std::endl;
    std::cout << "2. Quan ly Lop hoc phan" << std::endl;
    std::cout << "3. Quan ly Sinh vien" << std::endl;
    std::cout << "4. Quan ly Nganh hoc" << std::endl;
    std::cout << "0. Quay lai" << std::endl;
}

void printSubMenu2() {
    std::cout << "\n--- 2. Quan Ly Diem & Ket Qua ---" << std::endl;
    std::cout << "1. Nhap diem (Theo Ma SV + Ma hoc phan)" << std::endl;
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

// Old hienThiChiTietSinhVien function removed, using manager.displayBangDiemCaNhan instead.

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
                    std::cout << "Nhap lua chon (0-4): ";
                    if (!(std::cin >> subChoice)) {
                        std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    clearInputBuffer();

                    if (subChoice == 0) break;

                    if (subChoice == 1) {
                        int hpChoice = -1;
                        while (true) {
                            std::cout << "\n--- Quan Ly Hoc Phan ---\n1. Them hoc phan\n2. Cap nhat hoc phan\n3. Xoa hoc phan\n4. Danh sach hoc phan\n0. Quay lai\nNhap lua chon: ";
                            if (!(std::cin >> hpChoice)) {
                                std::cout << "Loi nhap lieu!\n";
                                clearInputBuffer(); continue;
                            }
                            clearInputBuffer();
                            if (hpChoice == 0) break;
                            if (hpChoice == 1) {
                                std::string ma, ten; int stc;
                                std::cout << "Ma HP: "; std::getline(std::cin, ma);
                                std::cout << "Ten HP: "; std::getline(std::cin, ten);
                                std::cout << "So TC: "; std::cin >> stc; clearInputBuffer();
                                HocPhan* hp = new HocPhan(ma, ten, stc, stc);
                                if (manager.addHocPhan(hp)) std::cout << "Them thanh cong!\n";
                                else { std::cout << "Ma HP da ton tai!\n"; delete hp; }
                            } else if (hpChoice == 2) {
                                std::string ma, ten; int stc;
                                std::cout << "Ma HP can sua: "; std::getline(std::cin, ma);
                                HocPhan* oldHp = manager.findHocPhanByMa(ma);
                                if (oldHp) {
                                    std::cout << "Ten HP moi: "; std::getline(std::cin, ten);
                                    std::cout << "So TC moi: "; std::cin >> stc; clearInputBuffer();
                                    oldHp->setTenHP(ten); oldHp->setSoTinChi(stc);
                                    std::cout << "Cap nhat thanh cong!\n";
                                } else std::cout << "Khong tim thay Ma HP!\n";
                            } else if (hpChoice == 3) {
                                std::string ma;
                                std::cout << "Ma HP can xoa: "; std::getline(std::cin, ma);
                                if (manager.removeHocPhan(ma)) std::cout << "Xoa thanh cong!\n";
                                else std::cout << "Khong tim thay Ma HP!\n";
                            } else if (hpChoice == 4) {
                                LinkedList<HocPhan*>* list = manager.getAllHocPhan();
                                if (!list || list->isEmpty()) std::cout << "Danh sach trong.\n";
                                else {
                                    Node<HocPhan*>* curr = list->getHead();
                                    while(curr) {
                                        std::cout << curr->data->getMaHP() << " - " << curr->data->getTenHP() << " (" << curr->data->getSoTinChi() << " TC)\n";
                                        curr = curr->next;
                                    }
                                }
                                if (list) delete list;
                            }
                        }
                    } else if (subChoice == 2) {
                        int lhpChoice = -1;
                        while (true) {
                            std::cout << "\n--- Quan Ly Lop Hoc Phan ---\n1. Mo lop\n2. Xoa lop\n3. Dang ky SV\n4. Huy dang ky SV\n5. Danh sach LHP\n0. Quay lai\nNhap lua chon: ";
                            if (!(std::cin >> lhpChoice)) {
                                std::cout << "Loi nhap lieu!\n"; clearInputBuffer(); continue;
                            }
                            clearInputBuffer();
                            if (lhpChoice == 0) break;
                            if (lhpChoice == 1) {
                                std::string malop, mahp, hocky;
                                std::cout << "Ma Lop: "; std::getline(std::cin, malop);
                                std::cout << "Ma HP: "; std::getline(std::cin, mahp);
                                std::cout << "Hoc ky: "; std::getline(std::cin, hocky);
                                LopHocPhan* lhp = new LopHocPhan(malop, mahp, hocky);
                                if (manager.addLopHocPhan(lhp)) std::cout << "Mo lop thanh cong!\n";
                                else { std::cout << "Ma Lop da ton tai!\n"; delete lhp; }
                            } else if (lhpChoice == 2) {
                                std::string malop;
                                std::cout << "Ma Lop can xoa: "; std::getline(std::cin, malop);
                                if (manager.removeLopHocPhan(malop)) std::cout << "Xoa thanh cong!\n";
                                else std::cout << "Khong tim thay Ma Lop!\n";
                            } else if (lhpChoice == 3) {
                                std::string malop, mssv;
                                std::cout << "Ma Lop: "; std::getline(std::cin, malop);
                                std::cout << "MSSV: "; std::getline(std::cin, mssv);
                                if (manager.registerSinhVienToLop(mssv, malop)) std::cout << "Dang ky thanh cong!\n";
                                else std::cout << "Dang ky that bai (Loi MSSV/MaLop hoac da dang ky)!\n";
                            } else if (lhpChoice == 4) {
                                std::string malop, mssv;
                                std::cout << "Ma Lop: "; std::getline(std::cin, malop);
                                std::cout << "MSSV: "; std::getline(std::cin, mssv);
                                if (manager.unregisterSinhVienFromLop(mssv, malop)) std::cout << "Huy dang ky thanh cong!\n";
                                else std::cout << "Huy that bai!\n";
                            } else if (lhpChoice == 5) {
                                LinkedList<LopHocPhan*>* list = manager.getAllLopHocPhan();
                                if (!list || list->isEmpty()) std::cout << "Danh sach trong.\n";
                                else {
                                    Node<LopHocPhan*>* curr = list->getHead();
                                    while(curr) {
                                        std::cout << "Lop: " << curr->data->getMaLop() << " | HP: " << curr->data->getMaHP() << " | HK: " << curr->data->getHocKy() << "\n";
                                        curr = curr->next;
                                    }
                                }
                                if (list) delete list;
                            }
                        }
                    } else if (subChoice == 3) {
                        int svChoice = -1;
                        while (true) {
                            std::cout << "\n--- Quan Ly Sinh Vien ---\n1. Them sinh vien\n2. Cap nhat thong tin\n3. Xoa sinh vien\n4. Hien thi tat ca\n0. Quay lai\nNhap lua chon: ";
                            if (!(std::cin >> svChoice)) {
                                std::cout << "Loi nhap lieu!\n"; clearInputBuffer(); continue;
                            }
                            clearInputBuffer();
                            if (svChoice == 0) break;
                            if (svChoice == 1) {
                                std::string mssv, ten, malop, manganh;
                                std::cout << "MSSV: "; std::getline(std::cin, mssv);
                                std::cout << "Ho va Ten: "; std::getline(std::cin, ten);
                                std::cout << "Ma Lop (vd MI1.01): "; std::getline(std::cin, malop);
                                std::cout << "Ma Nganh (vd MI1): "; std::getline(std::cin, manganh);
                                SinhVien* sv = new SinhVien();
                                sv->setMSSV(mssv);
                                sv->setHoTen(ten);
                                sv->setLop(malop);
                                sv->setMaNganh(manganh);
                                if (manager.addSinhVien(sv)) std::cout << "Them thanh cong!\n";
                                else { std::cout << "MSSV da ton tai!\n"; delete sv; }
                            } else if (svChoice == 2) {
                                std::string mssv, ten, malop, manganh;
                                std::cout << "MSSV can sua: "; std::getline(std::cin, mssv);
                                SinhVien* oldSv = manager.findSinhVienByMSSV(mssv);
                                if (oldSv) {
                                    std::cout << "Ho ten moi: "; std::getline(std::cin, ten);
                                    std::cout << "Ma Lop moi: "; std::getline(std::cin, malop);
                                    std::cout << "Ma Nganh moi: "; std::getline(std::cin, manganh);
                                    oldSv->setHoTen(ten); oldSv->setLop(malop); oldSv->setMaNganh(manganh);
                                    std::cout << "Cap nhat thanh cong!\n";
                                } else std::cout << "Khong tim thay MSSV!\n";
                            } else if (svChoice == 3) {
                                std::string mssv;
                                std::cout << "MSSV can xoa: "; std::getline(std::cin, mssv);
                                if (manager.removeSinhVien(mssv)) std::cout << "Xoa thanh cong!\n";
                                else std::cout << "Khong tim thay MSSV!\n";
                            } else if (svChoice == 4) {
                                std::cout << "\nDanh sach toan bo sinh vien (" << manager.getStudentCount() << " records):" << std::endl;
                                manager.printAll();
                            }
                        }
                    } else if (subChoice == 4) {
                        int nghChoice = -1;
                        while (true) {
                            std::cout << "\n--- Quan Ly Nganh Hoc ---\n1. Them nganh hoc\n2. Cap nhat nganh hoc\n3. Xoa nganh hoc\n4. Hien thi tat ca\n0. Quay lai\nNhap lua chon: ";
                            if (!(std::cin >> nghChoice)) {
                                std::cout << "Loi nhap lieu!\n"; clearInputBuffer(); continue;
                            }
                            clearInputBuffer();
                            if (nghChoice == 0) break;
                            if (nghChoice == 1) {
                                std::string ma, ten; float hocPhi;
                                std::cout << "Ma Nganh: "; std::getline(std::cin, ma);
                                std::cout << "Ten Nganh: "; std::getline(std::cin, ten);
                                std::cout << "Hoc Phi 1 Tin: "; std::cin >> hocPhi; clearInputBuffer();
                                NganhHoc* nganh = new NganhHoc(ma, ten, hocPhi);
                                if (manager.addNganhHoc(nganh)) std::cout << "Them thanh cong!\n";
                                else { std::cout << "Ma Nganh da ton tai!\n"; delete nganh; }
                            } else if (nghChoice == 2) {
                                std::string ma, ten; float hocPhi;
                                std::cout << "Ma Nganh can sua: "; std::getline(std::cin, ma);
                                NganhHoc* oldNganh = manager.findNganhHocByMa(ma);
                                if (oldNganh) {
                                    std::cout << "Ten Nganh moi: "; std::getline(std::cin, ten);
                                    std::cout << "Hoc Phi 1 Tin moi: "; std::cin >> hocPhi; clearInputBuffer();
                                    oldNganh->setTenNganh(ten); oldNganh->setHocPhiMotTin(hocPhi);
                                    std::cout << "Cap nhat thanh cong!\n";
                                } else std::cout << "Khong tim thay Ma Nganh!\n";
                            } else if (nghChoice == 3) {
                                std::string ma;
                                std::cout << "Ma Nganh can xoa: "; std::getline(std::cin, ma);
                                if (manager.removeNganhHoc(ma)) std::cout << "Xoa thanh cong!\n";
                                else std::cout << "Khong tim thay Ma Nganh!\n";
                            } else if (nghChoice == 4) {
                                LinkedList<NganhHoc*>* list = manager.getAllNganhHoc();
                                if (!list || list->isEmpty()) std::cout << "Danh sach trong.\n";
                                else {
                                    Node<NganhHoc*>* curr = list->getHead();
                                    while(curr) {
                                        std::cout << curr->data->getMaNganh() << " - " << curr->data->getTenNganh() << " (Hoc phi: " << curr->data->getHocPhiMotTin() << ")\n";
                                        curr = curr->next;
                                    }
                                }
                                if (list) delete list;
                            }
                        }
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
                        std::string mssv, malop, mahp; float qtr, ck, trongso;
                        std::cout << "MSSV: "; std::getline(std::cin, mssv);
                        std::cout << "Ma Lop: "; std::getline(std::cin, malop);
                        std::cout << "Ma HP: "; std::getline(std::cin, mahp);
                        std::cout << "Diem QTr: "; std::cin >> qtr;
                        std::cout << "Diem CK: "; std::cin >> ck;
                        std::cout << "Trong so QTr (vd 0.3): "; std::cin >> trongso;
                        clearInputBuffer();
                        if (manager.addDiem(mssv, malop, mahp, qtr, ck, trongso)) std::cout << "Nhap diem thanh cong!\n";
                        else std::cout << "Nhap diem that bai (Sai MSSV, hoac da co diem)!\n";
                    } else if (subChoice == 2) {
                        std::string mssv, malop; float qtr, ck, trongso;
                        std::cout << "MSSV: "; std::getline(std::cin, mssv);
                        std::cout << "Ma Lop can sua diem: "; std::getline(std::cin, malop);
                        std::cout << "Diem QTr moi: "; std::cin >> qtr;
                        std::cout << "Diem CK moi: "; std::cin >> ck;
                        std::cout << "Trong so QTr (vd 0.3): "; std::cin >> trongso;
                        clearInputBuffer();
                        if (manager.updateDiem(mssv, malop, qtr, ck, trongso)) std::cout << "Cap nhat diem thanh cong!\n";
                        else std::cout << "Cap nhat that bai!\n";
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
                        std::string mssv, hocKy;
                        std::cout << "Nhap MSSV can thong ke: ";
                        std::getline(std::cin, mssv);
                        std::cout << "Nhap Hoc Ky (vd: 2023.1): ";
                        std::getline(std::cin, hocKy);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        manager.displayThongKeHocLuc(mssv, hocKy);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> duration = end - start;
                        
                        std::cout << "\n[Thong ke] Thoi gian tinh toan GPA/CPA: " 
                                  << std::fixed << std::setprecision(3) << duration.count() 
                                  << " ms" << std::endl;
                    } else if (subChoice == 2) {
                        std::string mssv;
                        std::cout << "Nhap MSSV can xep loai: ";
                        std::getline(std::cin, mssv);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        std::pair<float, float> result = manager.calculateGPAAndCPA(mssv, "");
                        float cpa = result.second;
                        std::string hocLuc = manager.evaluateHocLuc(cpa);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> duration = end - start;

                        std::cout << "\nSinh vien " << mssv << " co CPA = " << std::fixed << std::setprecision(2) << cpa 
                                  << " -> Xep loai: " << hocLuc << std::endl;
                                  
                        std::cout << "[Thong ke] Thoi gian tinh toan: " 
                                  << std::fixed << std::setprecision(3) << duration.count() 
                                  << " ms" << std::endl;
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
                        manager.displayBangDiemCaNhan(mssv);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> duration = end - start;
                        
                        std::cout << "\n[Thong ke] Thoi gian hien thi: " 
                                  << std::fixed << std::setprecision(3) << duration.count() 
                                  << " ms" << std::endl;
                    } else if (subChoice == 2) {
                        std::string maLop;
                        std::cout << "Nhap Ma Lop HP can xem bang diem: ";
                        std::getline(std::cin, maLop);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        manager.displayBangDiemLopHP(maLop);
                        auto end = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> duration = end - start;
                        
                        std::cout << "\n[Thong ke] Thoi gian hien thi: " 
                                  << std::fixed << std::setprecision(3) << duration.count() 
                                  << " ms" << std::endl;
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
                        int loadSaveChoice = -1;
                        std::cout << "\n--- CHON CHE DO TAI/LUU DU LIEU ---" << std::endl;
                        std::cout << "1. Tai toan bo du lieu mac dinh (Xoa du lieu cu)" << std::endl;
                        std::cout << "2. Tai them tu file cu the (Giu nguyen du lieu hien tai)" << std::endl;
                        std::cout << "3. Luu toan bo du lieu hien tai ra file CSV" << std::endl;
                        std::cout << "Nhap lua chon: ";
                        if (!(std::cin >> loadSaveChoice)) {
                            std::cout << "Loi: Vui long nhap so nguyen hop le!" << std::endl;
                            clearInputBuffer();
                            continue;
                        }
                        clearInputBuffer();

                        if (loadSaveChoice == 1) {
                            std::cout << "Dang tai du lieu mac dinh..." << std::endl;
                            manager.cleanUp(); // Reset truoc khi tai
                            FileHandler::loadNganhHoc("../NganhHoc.csv", manager);
                            FileHandler::loadHocPhan("../HocPhan.csv", manager);
                            FileHandler::loadSinhVien("../DanhSachSinhVien.csv", manager);
                            FileHandler::loadDiem("../Diem_DaiSo.csv", manager, "MI1141");
                            FileHandler::loadDiem("../Diem_GT1.csv", manager, "MI1111");
                            FileHandler::loadDiem("../Diem_TinHoc.csv", manager, "IT1110");
                            FileHandler::loadDiem("../Diem_Triet.csv", manager, "LL1111");
                        } else if (loadSaveChoice == 2) {
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
                        } else if (loadSaveChoice == 3) {
                            std::cout << "Dang luu toan bo du lieu ra file..." << std::endl;
                            FileHandler::saveNganhHoc("../NganhHoc_Export.csv", manager);
                            FileHandler::saveHocPhan("../HocPhan_Export.csv", manager);
                            FileHandler::saveSinhVien("../DanhSachSinhVien_Export.csv", manager);
                            FileHandler::saveDiem("../Diem_Export.csv", manager);
                        } else {
                            std::cout << "Loi: Lua chon khong hop le!" << std::endl;
                        }
                    } else if (subChoice == 2) {
                        std::cout << "Dang tao mock data (10000 sinh vien)..." << std::endl;
                        // Thay đổi số lượng từ 1000 lên 10000 để phù hợp với menu mới
                        DataGenerator::generateMockData(10000); 
                    } else if (subChoice == 3) {
                        LinkedList<SinhVien*>* listSV = manager.getAllSinhVien();
                        if (!listSV || listSV->isEmpty()) {
                            std::cout << "Loi: Chua co du lieu Sinh Vien de danh gia hieu nang!" << std::endl;
                            if (listSV) delete listSV;
                            continue;
                        }
                        
                        std::vector<std::string> randomMSSVs;
                        std::vector<SinhVien*> svArray;
                        Node<SinhVien*>* current = listSV->getHead();
                        while (current != nullptr) {
                            svArray.push_back(current->data);
                            current = current->next;
                        }
                        
                        std::srand(static_cast<unsigned int>(std::time(nullptr)));
                        int testCount = 1000;
                        if (svArray.size() < 1000) testCount = svArray.size();
                        
                        for (int i = 0; i < testCount; ++i) {
                            randomMSSVs.push_back(svArray[std::rand() % svArray.size()]->getMSSV());
                        }
                        
                        std::cout << "\n=== DANH GIA HIEU NANG TIM KIEM (" << testCount << " Sinh vien) ===" << std::endl;
                        
                        // 1. O(N) LinkedList Search
                        auto startLinear = std::chrono::high_resolution_clock::now();
                        int foundLinear = 0;
                        for (const std::string& target : randomMSSVs) {
                            Node<SinhVien*>* curr = listSV->getHead();
                            while (curr != nullptr) {
                                if (curr->data->getMSSV() == target) {
                                    foundLinear++;
                                    break;
                                }
                                curr = curr->next;
                            }
                        }
                        auto endLinear = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> durationLinear = endLinear - startLinear;
                        
                        // 2. O(1) HashMap Search
                        auto startHash = std::chrono::high_resolution_clock::now();
                        int foundHash = 0;
                        for (const std::string& target : randomMSSVs) {
                            if (manager.findSinhVienByMSSV(target) != nullptr) {
                                foundHash++;
                            }
                        }
                        auto endHash = std::chrono::high_resolution_clock::now();
                        std::chrono::duration<double, std::milli> durationHash = endHash - startHash;
                        
                        std::cout << "1. Tim kiem tuyen tinh tren Linked List O(N):" << std::endl;
                        std::cout << "   - Thoi gian chay: " << std::fixed << std::setprecision(3) << durationLinear.count() << " ms" << std::endl;
                        
                        std::cout << "2. Tim kiem tren Hash Map O(1):" << std::endl;
                        std::cout << "   - Thoi gian chay: " << std::fixed << std::setprecision(3) << durationHash.count() << " ms" << std::endl;
                        
                        if (durationHash.count() > 0) {
                            std::cout << "=> Hieu suat: Hash Map nhanh hon khoang " 
                                      << std::fixed << std::setprecision(1) << (durationLinear.count() / durationHash.count()) 
                                      << " lan." << std::endl;
                        }
                        
                        delete listSV;
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

