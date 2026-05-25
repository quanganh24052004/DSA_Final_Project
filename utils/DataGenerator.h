#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

class DataGenerator {
public:
    static bool generateSampleCSV(const std::string& filePath, size_t recordCount) {
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "Khong the mo file de ghi: " << filePath << std::endl;
            return false;
        }

        // Write CSV Header matching the 18 fields
        outFile << "MSSV,FullName,ClassCode,DateOfBirth,Hometown,Gender,AdmissionMethod,AdmissionScore,Email,PhoneNumber,Address,Major,Department,AcademicStatus,EnrollmentYear,GPA,AccumulatedCredits,Advisor\n";

        // Seed random generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Predefined arrays of realistic data for randomized synthesis
        const std::string listHo[] = {"Nguyen", "Tran", "Le", "Pham", "Hoang", "Phan", "Vu", "Dang", "Bui", "Do", "Ho", "Ngo", "Duong", "Ly"};
        const std::string listDem[] = {"Van", "Thi", "Quang", "Minh", "Quoc", "Anh", "Duc", "Ngoc", "Duy", "Huu", "Tuan", "Xuan", "Hai", "Thanh"};
        const std::string listTen[] = {"Anh", "Binh", "Cuong", "Dung", "Dong", "Giang", "Hai", "Hung", "Huy", "Khoa", "Linh", "Long", "Nam", "Phong", "Phuc", "Quan", "Son", "Tuan", "Viet", "Vy", "Trang", "Phuong", "Oanh", "Mai", "Hanh", "Yen"};
        
        const std::string listLop[] = {"CNPM01-K68", "KHMT02-K68", "HTTT01-K68", "ATTT03-K68", "DTVT01-K68", "CTTT02-K68", "CNPM02-K67", "KHMT01-K67"};
        const std::string listTinh[] = {"Ha Noi", "Hai Phong", "Da Nang", "Quang Ninh", "Nghe An", "Ha Tinh", "Thanh Hoa", "Nam Dinh", "Thai Binh", "Bac Ninh", "Thai Nguyen", "Quang Nam", "Hue", "TP HCM", "Can Tho"};
        const std::string listPTXT[] = {"Hoc ba", "Diem thi THPT", "Danh gia nang luc", "Tuyen thang"};
        
        const std::string listNganh[] = {"Cong nghe thong tin", "Khoa hoc may tinh", "He thong thong tin", "An toan thong tin", "Ky thuat may tinh", "Dien tu vien thong"};
        const std::string listKhoa[] = {"Truong CNTT&TT", "Truong CNTT&TT", "Truong CNTT&TT", "Truong CNTT&TT", "Khoa Dien tu", "Khoa Vien thong"};
        const std::string listStatus[] = {"Dang hoc", "Dang hoc", "Dang hoc", "Bao luu", "Canh cao"};
        const std::string listAdvisor[] = {"Nguyen Van A", "Tran Thi B", "Le Van C", "Pham Minh D", "Hoang Duc E"};

        const size_t sizeHo = sizeof(listHo) / sizeof(listHo[0]);
        const size_t sizeDem = sizeof(listDem) / sizeof(listDem[0]);
        const size_t sizeTen = sizeof(listTen) / sizeof(listTen[0]);
        const size_t sizeLop = sizeof(listLop) / sizeof(listLop[0]);
        const size_t sizeTinh = sizeof(listTinh) / sizeof(listTinh[0]);
        const size_t sizePTXT = sizeof(listPTXT) / sizeof(listPTXT[0]);
        const size_t sizeNganh = sizeof(listNganh) / sizeof(listNganh[0]);
        const size_t sizeStatus = sizeof(listStatus) / sizeof(listStatus[0]);
        const size_t sizeAdvisor = sizeof(listAdvisor) / sizeof(listAdvisor[0]);

        long long startingMSSV = 20250001;

        for (size_t i = 0; i < recordCount; ++i) {
            std::string mssvStr = std::to_string(startingMSSV + i);
            
            // Randomize name
            std::string ho = listHo[std::rand() % sizeHo];
            std::string dem = listDem[std::rand() % sizeDem];
            std::string ten = listTen[std::rand() % sizeTen];
            std::string fullName = ho + " " + dem + " " + ten;

            // Simple gender deduction based on middle name
            std::string gender = (dem == "Thi") ? "Nu" : ((std::rand() % 2 == 0) ? "Nam" : "Nu");

            std::string classCode = listLop[std::rand() % sizeLop];
            
            // Randomize date of birth (simple generator between 2004 and 2007)
            int day = 1 + (std::rand() % 28);
            int month = 1 + (std::rand() % 12);
            int year = 2004 + (std::rand() % 4);
            std::string dob = (day < 10 ? "0" : "") + std::to_string(day) + "/" +
                              (month < 10 ? "0" : "") + std::to_string(month) + "/" +
                              std::to_string(year);

            std::string hometown = listTinh[std::rand() % sizeTinh];
            std::string admMethod = listPTXT[std::rand() % sizePTXT];
            double admScore = 20.0 + static_cast<double>(std::rand() % 100) / 10.0; // 20.0 to 30.0

            std::string email = mssvStr + "@sis.hust.edu.vn";
            std::string phone = "09" + std::to_string(10000000 + std::rand() % 90000000); // 09xxxxxxxx
            std::string address = "So " + std::to_string(1 + std::rand() % 150) + " Pho Chua Boc - " + hometown;

            size_t majorIdx = std::rand() % sizeNganh;
            std::string major = listNganh[majorIdx];
            std::string department = listKhoa[majorIdx]; // Keep aligned with major
            
            std::string status = listStatus[std::rand() % sizeStatus];
            int enrollYear = year + 18; // Entered university at 18
            double gpa = 1.0 + static_cast<double>(std::rand() % 301) / 100.0; // 1.0 to 4.0
            int credits = std::rand() % 151; // 0 to 150 credits
            std::string advisor = listAdvisor[std::rand() % sizeAdvisor];

            // Output CSV row
            outFile << mssvStr << ","
                    << fullName << ","
                    << classCode << ","
                    << dob << ","
                    << hometown << ","
                    << gender << ","
                    << admMethod << ","
                    << admScore << ","
                    << email << ","
                    << phone << ","
                    << address << ","
                    << major << ","
                    << department << ","
                    << status << ","
                    << enrollYear << ","
                    << gpa << ","
                    << credits << ","
                    << advisor << "\n";
        }

        outFile.close();
        return true;
    }
};

#endif // DATAGENERATOR_H
