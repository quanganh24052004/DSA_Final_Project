#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../core/StudentManager.h"
#include "../models/Student.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>

class FileHandler {
public:
    // Load student records from CSV. Returns true if successfully loaded, false otherwise.
    static bool loadData(const std::string& filePath, StudentManager& manager) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file de doc: " << filePath << std::endl;
            return false;
        }

        std::string line;
        // Read header line
        if (!std::getline(file, line)) {
            std::cerr << "Loi: File rong!" << std::endl;
            file.close();
            return false;
        }

        // Check if it's a valid CSV header (contains "MSSV" or similar)
        if (line.find("MSSV") == std::string::npos) {
            // Not a header or incorrect format, let's reset to beginning
            file.seekg(0);
        }

        size_t loadedCount = 0;
        size_t errorCount = 0;
        size_t duplicateCount = 0;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string fields[18];
            std::string temp;
            int idx = 0;

            // Split by comma
            while (std::getline(ss, temp, ',') && idx < 18) {
                fields[idx++] = temp;
            }

            // If we don't have exactly 18 fields, skip and log error
            if (idx < 18) {
                std::cerr << "Canh bao: Dong khong du 18 truong du lieu. Bo qua. Noi dung: " << line.substr(0, 50) << "..." << std::endl;
                errorCount++;
                continue;
            }

            try {
                std::string mssv = fields[0];
                std::string fullName = fields[1];
                std::string classCode = fields[2];
                std::string dob = fields[3];
                std::string hometown = fields[4];
                std::string gender = fields[5];
                std::string admMethod = fields[6];
                double admScore = std::stod(fields[7]);
                std::string email = fields[8];
                std::string phone = fields[9];
                std::string address = fields[10];
                std::string major = fields[11];
                std::string department = fields[12];
                std::string status = fields[13];
                int enrollYear = std::stoi(fields[14]);
                double gpa = std::stod(fields[15]);
                int credits = std::stoi(fields[16]);
                std::string advisor = fields[17];

                Student* s = new Student(mssv, fullName, classCode, dob, hometown, gender, 
                                         admMethod, admScore, email, phone, address, 
                                         major, department, status, enrollYear, gpa, 
                                         credits, advisor);

                if (!manager.addStudent(s)) {
                    // Duplicate MSSV
                    delete s; // Free memory immediately
                    duplicateCount++;
                } else {
                    loadedCount++;
                }

            } catch (const std::exception& e) {
                std::cerr << "Loi phan tich o dong: " << line.substr(0, 50) << "... - Chi tiet: " << e.what() << std::endl;
                errorCount++;
            }
        }

        file.close();
        std::cout << "Ket qua tai du lieu:" << std::endl;
        std::cout << " - Thanh cong: " << loadedCount << " sinh vien." << std::endl;
        if (duplicateCount > 0) std::cout << " - Trung MSSV (Bo qua): " << duplicateCount << " sinh vien." << std::endl;
        if (errorCount > 0) std::cout << " - Loi dinh dang (Bo qua): " << errorCount << " dong." << std::endl;
        
        return true;
    }

    // Save student records to CSV. Returns true if successfully saved, false otherwise.
    static bool saveData(const std::string& filePath, const StudentManager& manager) {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file de ghi: " << filePath << std::endl;
            return false;
        }

        // Write header
        file << "MSSV,FullName,ClassCode,DateOfBirth,Hometown,Gender,AdmissionMethod,AdmissionScore,Email,PhoneNumber,Address,Major,Department,AcademicStatus,EnrollmentYear,GPA,AccumulatedCredits,Advisor\n";

        size_t savedCount = 0;
        Node<Student*>* current = manager.getAllClasses().getHead();
        while (current != nullptr) {
            file << current->data->toCSV() << "\n";
            savedCount++;
            current = current->next;
        }

        file.close();
        std::cout << "Ghi thanh cong " << savedCount << " sinh vien vao file: " << filePath << std::endl;
        return true;
    }
};

#endif // FILEHANDLER_H
