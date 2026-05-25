//
//  main.cpp
//  Final_Project_DSA
//
//  Created by Nguyễn Quang Anh on 18/5/26.
//

#include "datastructures/LinkedList.h"
#include "datastructures/HashMap.h"
#include "models/Student.h"
#include "core/StudentManager.h"
#include "utils/FileHandler.h"
#include "utils/DataGenerator.h"

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <limits>

// Helper function to clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Linear search helper for benchmarking (direct comparison with Hash Search)
Student* linearSearchMSSV(const LinkedList<Student*>& list, const std::string& mssv) {
    Node<Student*>* current = list.getHead();
    while (current != nullptr) {
        if (current->data->getMSSV() == mssv) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

// Visual menu UI functions
void printMenuHeader() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     CHUONG TRINH QUAN LY SINH VIEN - NHOM 5 (DSA)     " << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 1. Tai du lieu tu file CSV" << std::endl;
    std::cout << " 2. Luu du lieu ra file CSV" << std::endl;
    std::cout << " 3. Tim kiem sinh vien bang MSSV (O(1) Hash Map)" << std::endl;
    std::cout << " 4. Tim kiem sinh vien theo Lop (O(N) Linear Search)" << std::endl;
    std::cout << " 5. Tim kiem sinh vien theo Que quan (O(N) Linear Search)" << std::endl;
    std::cout << " 6. Them moi mot sinh vien" << std::endl;
    std::cout << " 7. Cap nhat thong tin sinh vien" << std::endl;
    std::cout << " 8. Xoa sinh vien khoi he thong" << std::endl;
    std::cout << " 9. Hien thi toan bo danh sach sinh vien" << std::endl;
    std::cout << " 10. Chay thu nghiem Hieu nang (Hash Search vs Linear Search)" << std::endl;
    std::cout << " 11. Tu dong sinh 10.000 du lieu mau ngau nhien" << std::endl;
    std::cout << " 0. Thoat chuong trinh" << std::endl;
    std::cout << "=======================================================" << std::endl;
}

int main(int argc, const char * argv[]) {
    StudentManager manager;
    std::string defaultFile = "students.csv";
    int choice = -1;

    while (true) {
        printMenuHeader();
        std::cout << "Nhap lua chon cua ban (0-11): ";
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
            case 1: { // Load CSV
                std::string filePath;
                std::cout << "Nhap duong dan file CSV [" << defaultFile << "]: ";
                std::getline(std::cin, filePath);
                if (filePath.empty()) filePath = defaultFile;
                
                std::cout << "Dang tai du lieu tu: " << filePath << "..." << std::endl;
                FileHandler::loadData(filePath, manager);
                break;
            }
            case 2: { // Save CSV
                std::string filePath;
                std::cout << "Nhap duong dan file CSV de ghi [" << defaultFile << "]: ";
                std::getline(std::cin, filePath);
                if (filePath.empty()) filePath = defaultFile;
                
                std::cout << "Dang ghi du lieu ra: " << filePath << "..." << std::endl;
                FileHandler::saveData(filePath, manager);
                break;
            }
            case 3: { // Search by MSSV
                std::string mssv;
                std::cout << "Nhap MSSV can tim: ";
                std::getline(std::cin, mssv);
                
                // Track search duration for demonstration
                auto start = std::chrono::high_resolution_clock::now();
                Student* s = manager.findStudentByMSSV(mssv);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::nano> duration = end - start;

                if (s != nullptr) {
                    s->printCard();
                    std::cout << "[Thong ke] Thoi gian tim kiem bang Hash Map: " 
                              << std::fixed << std::setprecision(2) << duration.count() 
                              << " ns (O(1))" << std::endl;
                } else {
                    std::cout << "Khong tim thay sinh vien co MSSV: " << mssv << std::endl;
                }
                break;
            }
            case 4: { // Search by Class
                std::string classCode;
                std::cout << "Nhap ma Lop can tim (e.g. CNPM01-K68): ";
                std::getline(std::cin, classCode);
                
                auto start = std::chrono::high_resolution_clock::now();
                LinkedList<Student*>* results = manager.findStudentsByClass(classCode);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::nano> duration = end - start;

                if (results != nullptr && results->getSize() > 0) {
                    std::cout << "Tim thay " << results->getSize() << " sinh vien thuoc lop " << classCode << ":" << std::endl;
                    StudentManager::printTableHeader();
                    Node<Student*>* current = results->getHead();
                    while (current != nullptr) {
                        current->data->printRow();
                        current = current->next;
                    }
                    StudentManager::printTableFooter();
                    std::cout << "[Thong ke] Thoi gian tim kiem tuan tu (Linear Search): " 
                              << std::fixed << std::setprecision(2) << duration.count() / 1000000.0 
                              << " ms (O(N))" << std::endl;
                } else {
                    std::cout << "Khong tim thay sinh vien nao thuoc lop: " << classCode << std::endl;
                }
                delete results; // Delete the results list shell (leaves Student pointers intact)
                break;
            }
            case 5: { // Search by Hometown
                std::string hometown;
                std::cout << "Nhap que quan can tim (e.g. Ha Noi): ";
                std::getline(std::cin, hometown);
                
                auto start = std::chrono::high_resolution_clock::now();
                LinkedList<Student*>* results = manager.findStudentsByHometown(hometown);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::nano> duration = end - start;

                if (results != nullptr && results->getSize() > 0) {
                    std::cout << "Tim thay " << results->getSize() << " sinh vien que o " << hometown << ":" << std::endl;
                    StudentManager::printTableHeader();
                    Node<Student*>* current = results->getHead();
                    while (current != nullptr) {
                        current->data->printRow();
                        current = current->next;
                    }
                    StudentManager::printTableFooter();
                    std::cout << "[Thong ke] Thoi gian tim kiem tuan tu (Linear Search): " 
                              << std::fixed << std::setprecision(2) << duration.count() / 1000000.0 
                              << " ms (O(N))" << std::endl;
                } else {
                    std::cout << "Khong tim thay sinh vien nao que o: " << hometown << std::endl;
                }
                delete results;
                break;
            }
            case 6: { // Add new Student
                std::string mssv, fullName, classCode, dob, hometown, gender;
                std::string admMethod, email, phone, address, major, dept, status, advisor;
                double admScore, gpa;
                int enrollYear, credits;

                std::cout << "--- THEM SINH VIEN MOI ---" << std::endl;
                std::cout << "Nhap MSSV (Duy nhat): "; std::getline(std::cin, mssv);
                
                if (manager.findStudentByMSSV(mssv) != nullptr) {
                    std::cout << "Loi: MSSV nay da ton tai trong he thong!" << std::endl;
                    break;
                }

                std::cout << "Nhap Ho ten: "; std::getline(std::cin, fullName);
                std::cout << "Nhap Lop: "; std::getline(std::cin, classCode);
                std::cout << "Nhap Ngay sinh (DD/MM/YYYY): "; std::getline(std::cin, dob);
                std::cout << "Nhap Que quan: "; std::getline(std::cin, hometown);
                std::cout << "Nhap Gioi tinh (Nam/Nu): "; std::getline(std::cin, gender);
                std::cout << "Nhap PT xet tuyen: "; std::getline(std::cin, admMethod);
                
                std::cout << "Nhap Diem xet tuyen: ";
                while (!(std::cin >> admScore)) {
                    std::cout << "Loi: Vui long nhap so thuc: ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Nhap Email: "; std::getline(std::cin, email);
                std::cout << "Nhap So dien thoai: "; std::getline(std::cin, phone);
                std::cout << "Nhap Dia chi thuong tru: "; std::getline(std::cin, address);
                std::cout << "Nhap Nganh hoc: "; std::getline(std::cin, major);
                std::cout << "Nhap Khoa vien: "; std::getline(std::cin, dept);
                std::cout << "Nhap Tinh trang hoc tap: "; std::getline(std::cin, status);
                
                std::cout << "Nhap Nam nhap hoc: ";
                while (!(std::cin >> enrollYear)) {
                    std::cout << "Loi: Vui long nhap so nguyen: ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Nhap GPA (he 4): ";
                while (!(std::cin >> gpa)) {
                    std::cout << "Loi: Vui long nhap so thuc: ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Nhap So tin chi tich luy: ";
                while (!(std::cin >> credits)) {
                    std::cout << "Loi: Vui long nhap so nguyen: ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Nhap Co van hoc tap: "; std::getline(std::cin, advisor);

                Student* newStudent = new Student(mssv, fullName, classCode, dob, hometown, gender,
                                                  admMethod, admScore, email, phone, address,
                                                  major, dept, status, enrollYear, gpa, credits, advisor);

                if (manager.addStudent(newStudent)) {
                    std::cout << "Da them moi sinh vien thanh cong!" << std::endl;
                } else {
                    std::cout << "Loi: Khong the them sinh vien (Loi khong xac dinh)." << std::endl;
                    delete newStudent;
                }
                break;
            }
            case 7: { // Update Student
                std::string mssv;
                std::cout << "Nhap MSSV sinh vien can cap nhat: ";
                std::getline(std::cin, mssv);

                Student* s = manager.findStudentByMSSV(mssv);
                if (s == nullptr) {
                    std::cout << "Khong tim thay sinh vien co MSSV: " << mssv << std::endl;
                    break;
                }

                s->printCard();
                std::cout << "\nChon truong thong tin muon cap nhat:" << std::endl;
                std::cout << "1. Ho va ten            2. Lop sinh hoat       3. Diem xet tuyen" << std::endl;
                std::cout << "4. Diem trung binh (GPA) 5. Tin chi tich luy    6. Tinh trang hoc tap" << std::endl;
                std::cout << "7. Co van hoc tap       0. Huy bo" << std::endl;
                std::cout << "Chon (0-7): ";
                
                int subChoice;
                if (!(std::cin >> subChoice)) {
                    std::cout << "Loi: Nhap sai!" << std::endl;
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                if (subChoice == 0) break;

                switch (subChoice) {
                    case 1: {
                        std::string name;
                        std::cout << "Nhap Ho ten moi: ";
                        std::getline(std::cin, name);
                        s->setFullName(name);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    case 2: {
                        std::string lop;
                        std::cout << "Nhap Lop moi: ";
                        std::getline(std::cin, lop);
                        s->setClassCode(lop);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    case 3: {
                        double score;
                        std::cout << "Nhap Diem xet tuyen moi: ";
                        while (!(std::cin >> score)) {
                            std::cout << "Loi. Nhap lai: ";
                            clearInputBuffer();
                        }
                        s->setAdmissionScore(score);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    case 4: {
                        double gpaVal;
                        std::cout << "Nhap GPA moi: ";
                        while (!(std::cin >> gpaVal)) {
                            std::cout << "Loi. Nhap lai: ";
                            clearInputBuffer();
                        }
                        s->setGPA(gpaVal);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    case 5: {
                        int creds;
                        std::cout << "Nhap So tin chi moi: ";
                        while (!(std::cin >> creds)) {
                            std::cout << "Loi. Nhap lai: ";
                            clearInputBuffer();
                        }
                        s->setAccumulatedCredits(creds);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    case 6: {
                        std::string status;
                        std::cout << "Nhap Tinh trang hoc tap moi: ";
                        std::getline(std::cin, status);
                        s->setAcademicStatus(status);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    case 7: {
                        std::string adv;
                        std::cout << "Nhap Co van hoc tap moi: ";
                        std::getline(std::cin, adv);
                        s->setAdvisor(adv);
                        std::cout << "Cap nhat thanh cong!" << std::endl;
                        break;
                    }
                    default:
                        std::cout << "Lua chon khong hop le." << std::endl;
                }
                break;
            }
            case 8: { // Delete Student
                std::string mssv;
                std::cout << "Nhap MSSV sinh vien can xoa: ";
                std::getline(std::cin, mssv);

                Student* s = manager.findStudentByMSSV(mssv);
                if (s == nullptr) {
                    std::cout << "Khong tim thay sinh vien co MSSV: " << mssv << std::endl;
                    break;
                }

                s->printCard();
                std::cout << "Ban co chac chan muon XOA sinh vien nay? (Y/N): ";
                std::string confirm;
                std::getline(std::cin, confirm);
                if (confirm == "Y" || confirm == "y") {
                    if (manager.deleteStudent(mssv)) {
                        std::cout << "Da xoa sinh vien khoi he thong thanh cong!" << std::endl;
                    } else {
                        std::cout << "Loi: Khong the xoa sinh vien." << std::endl;
                    }
                } else {
                    std::cout << "Da huy thao tac xoa." << std::endl;
                }
                break;
            }
            case 9: { // Display All
                std::cout << "Danh sach toan bo sinh vien (" << manager.getStudentCount() << " records):" << std::endl;
                manager.printAll();
                break;
            }
            case 10: { // Performance Benchmark
                size_t n = manager.getStudentCount();
                if (n == 0) {
                    std::cout << "Canh bao: He thong chua co du lieu sinh vien. Vui long tai du lieu (so 1) hoac sinh du lieu mau (so 11) truoc." << std::endl;
                    break;
                }

                std::cout << "--- CHUONG TRINH DO LUONG HIEU NANG THUAT TOAN ---" << std::endl;
                std::cout << "Tong so ban ghi hien tai: " << n << std::endl;
                std::cout << "Nhap so luot kiem tra truy van lap lai (e.g. 5000): ";
                int iterations = 1000;
                while (!(std::cin >> iterations) || iterations <= 0) {
                    std::cout << "Loi: Nhap so nguyen duong: ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Dang chay benchmarking " << iterations << " truy van ngau nhien..." << std::endl;

                // Pick a set of search keys
                // We will query some keys that exist, and some that do not, based on random generated IDs
                std::string* testKeys = new std::string[iterations];
                for (int i = 0; i < iterations; ++i) {
                    // Generates a random MSSV in range of synthesized IDs
                    long long randomMssv = 20250001 + (std::rand() % n);
                    testKeys[i] = std::to_string(randomMssv);
                }

                // 1. Benchmarking Hash Search O(1)
                auto startHash = std::chrono::high_resolution_clock::now();
                size_t hashFound = 0;
                for (int i = 0; i < iterations; ++i) {
                    Student* s = manager.findStudentByMSSV(testKeys[i]);
                    if (s != nullptr) hashFound++;
                }
                auto endHash = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::micro> durationHash = endHash - startHash;

                // 2. Benchmarking Linear Search O(N)
                auto startLinear = std::chrono::high_resolution_clock::now();
                size_t linearFound = 0;
                for (int i = 0; i < iterations; ++i) {
                    Student* s = linearSearchMSSV(manager.getAllClasses(), testKeys[i]);
                    if (s != nullptr) linearFound++;
                }
                auto endLinear = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::micro> durationLinear = endLinear - startLinear;

                // 3. Display Results
                std::cout << "\n=======================================================" << std::endl;
                std::cout << "                KET QUA PERFORMANCE TEST               " << std::endl;
                std::cout << "=======================================================" << std::endl;
                std::cout << " Kich thuoc du lieu (N):      " << n << " sinh vien" << std::endl;
                std::cout << " So luong truy van thuc hien: " << iterations << " lan" << std::endl;
                std::cout << " So lan tim thay:            " << hashFound << "/" << iterations << std::endl;
                std::cout << "-------------------------------------------------------" << std::endl;
                std::cout << " 1. HASH SEARCH O(1) [HashMap]:" << std::endl;
                std::cout << "    - Tong thoi gian:        " << std::fixed << std::setprecision(2) << durationHash.count() << " us" << std::endl;
                std::cout << "    - Trung binh 1 truy van:  " << (durationHash.count() / iterations) << " us (" 
                          << (durationHash.count() / iterations * 1000.0) << " ns)" << std::endl;
                std::cout << " 2. LINEAR SEARCH O(N) [LinkedList]:" << std::endl;
                std::cout << "    - Tong thoi gian:        " << durationLinear.count() << " us (" 
                          << durationLinear.count() / 1000.0 << " ms)" << std::endl;
                std::cout << "    - Trung binh 1 truy van:  " << (durationLinear.count() / iterations) << " us ("
                          << (durationLinear.count() / iterations * 1000.0) << " ns)" << std::endl;
                std::cout << "-------------------------------------------------------" << std::endl;
                
                double speedup = durationLinear.count() / (durationHash.count() > 0 ? durationHash.count() : 1);
                std::cout << " ==> HIEU QUA TANG CUONG:     HashMap nhanh hon LinkedList x" 
                          << std::fixed << std::setprecision(1) << speedup << " lan!" << std::endl;
                
                // QC Statistics
                std::cout << " => Ti le xung dot HashMap:   " << std::fixed << std::setprecision(2) 
                          << manager.getCollisionRate() << "%" << std::endl;
                std::cout << "=======================================================" << std::endl;

                delete[] testKeys;
                break;
            }
            case 11: { // Generate Data
                std::cout << "--- CHUONG TRINH SINH DU LIEU TEST TU DONG ---" << std::endl;
                std::cout << "Chuan bi sinh 10.000 ban ghi sinh vien..." << std::endl;
                std::string filePath;
                std::cout << "Nhap ten file muon ghi [" << defaultFile << "]: ";
                std::getline(std::cin, filePath);
                if (filePath.empty()) filePath = defaultFile;

                auto start = std::chrono::high_resolution_clock::now();
                bool success = DataGenerator::generateSampleCSV(filePath, 10000);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration = end - start;

                if (success) {
                    std::cout << "Sinh du lieu thanh cong!" << std::endl;
                    std::cout << " - File: " << filePath << std::endl;
                    std::cout << " - Thoi gian thuc hien: " << std::fixed << std::setprecision(2) << duration.count() << " ms" << std::endl;
                    std::cout << "Goi y: Ban co the chon Menu 1 de nap 10.000 sinh vien vua sinh vao he thong." << std::endl;
                } else {
                    std::cout << "Loi: Khong the tao file du lieu mau." << std::endl;
                }
                break;
            }
            default:
                std::cout << "Loi: Lua chon khong hop le! Vui long chon tu 0 den 11." << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
