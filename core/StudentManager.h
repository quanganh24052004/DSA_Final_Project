#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "../datastructures/LinkedList.h"
#include "../datastructures/HashMap.h"
#include "../models/SinhVien.h"
#include "../models/HocPhan.h"
#include "../models/NganhHoc.h"
#include <iostream>
#include <iomanip>

class StudentManager {
private:
    HashMap<std::string, SinhVien*> danhSachSinhVien; // Key: MSSV
    HashMap<std::string, HocPhan*> danhSachHocPhan;   // Key: MaHP
    HashMap<std::string, NganhHoc*> danhSachNganhHoc; // Key: MaNganh

public:
    StudentManager() {}

    ~StudentManager() {
        cleanUp();
    }

    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;

    void cleanUp() {
        // Free SinhVien objects
        LinkedList<SinhVien*>* svList = danhSachSinhVien.values();
        if (svList) {
            Node<SinhVien*>* current = svList->getHead();
            while (current != nullptr) {
                delete current->data; 
                current = current->next;
            }
            delete svList;
        }
        danhSachSinhVien.clear();

        // Free HocPhan objects
        LinkedList<HocPhan*>* hpList = danhSachHocPhan.values();
        if (hpList) {
            Node<HocPhan*>* current = hpList->getHead();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete hpList;
        }
        danhSachHocPhan.clear();

        // Free NganhHoc objects
        LinkedList<NganhHoc*>* nganhList = danhSachNganhHoc.values();
        if (nganhList) {
            Node<NganhHoc*>* current = nganhList->getHead();
            while (current != nullptr) {
                delete current->data;
                current = current->next;
            }
            delete nganhList;
        }
        danhSachNganhHoc.clear();
    }

    // Nganh Hoc Management
    bool addNganhHoc(NganhHoc* nh) {
        if (nh == nullptr) return false;
        if (danhSachNganhHoc.get(nh->getMaNganh()) != nullptr) return false;
        danhSachNganhHoc.put(nh->getMaNganh(), nh);
        return true;
    }

    NganhHoc* findNganhHocByMa(const std::string& maNganh) const {
        return danhSachNganhHoc.get(maNganh);
    }

    // Học Phần Management
    bool addHocPhan(HocPhan* hp) {
        if (hp == nullptr) return false;
        if (danhSachHocPhan.get(hp->getMaHP()) != nullptr) return false;
        danhSachHocPhan.put(hp->getMaHP(), hp);
        return true;
    }

    HocPhan* findHocPhanByMa(const std::string& maHP) const {
        return danhSachHocPhan.get(maHP);
    }
    
    // Sinh Viên Management
    bool addSinhVien(SinhVien* sv) {
        if (sv == nullptr) return false;
        if (danhSachSinhVien.get(sv->getMSSV()) != nullptr) return false;
        danhSachSinhVien.put(sv->getMSSV(), sv);
        return true;
    }

    SinhVien* findSinhVienByMSSV(const std::string& mssv) const {
        return danhSachSinhVien.get(mssv);
    }

    size_t getStudentCount() const {
        return danhSachSinhVien.getSize();
    }

    // Helpers for printing
    void printAll() const {
        LinkedList<SinhVien*>* list = danhSachSinhVien.values();
        if (list == nullptr || list->isEmpty()) {
            std::cout << "He thong chua co sinh vien nao!" << std::endl;
            if (list) delete list;
            return;
        }
        
        printTableHeader();
        Node<SinhVien*>* current = list->getHead();
        while (current != nullptr) {
            SinhVien* sv = current->data;
            std::cout << "| " << std::left << std::setw(10) << sv->getMSSV()
                      << " | " << std::setw(20) << sv->getHoTen().substr(0, 20)
                      << " | " << std::setw(10) << sv->getLop()
                      << " | " << std::setw(10) << sv->getNgaySinh()
                      << " | " << std::setw(12) << sv->getQueQuan().substr(0, 12)
                      << " |" << std::endl;
            current = current->next;
        }
        printTableFooter();
        delete list;
    }

    static void printTableHeader() {
        std::cout << "+" << std::string(73, '-') << "+" << std::endl;
        std::cout << "| " << std::left << std::setw(10) << "MSSV"
                  << " | " << std::setw(20) << "Ho va ten"
                  << " | " << std::setw(10) << "Lop"
                  << " | " << std::setw(10) << "Ngay sinh"
                  << " | " << std::setw(12) << "Que quan"
                  << " |" << std::endl;
        std::cout << "+" << std::string(73, '-') << "+" << std::endl;
    }

    static void printTableFooter() {
        std::cout << "+" << std::string(73, '-') << "+" << std::endl;
    }
};

#endif // STUDENTMANAGER_H
