#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <iomanip>

class Student {
private:
    std::string mssv;              // 1. Student ID (Mã số sinh viên - Unique Key)
    std::string fullName;          // 2. Họ và tên
    std::string classCode;         // 3. Lớp sinh hoạt
    std::string dateOfBirth;       // 4. Ngày sinh (DD/MM/YYYY)
    std::string hometown;          // 5. Quê quán
    std::string gender;            // 6. Giới tính
    std::string admissionMethod;   // 7. Phương thức xét tuyển
    double admissionScore;         // 8. Điểm xét tuyển
    std::string email;             // 9. Email liên hệ
    std::string phoneNumber;       // 10. Số điện thoại
    std::string address;           // 11. Địa chỉ thường trú
    std::string major;             // 12. Ngành học
    std::string department;        // 13. Khoa viện quản lý
    std::string academicStatus;    // 14. Tình trạng học tập
    int enrollmentYear;            // 15. Năm nhập học
    double gpa;                    // 16. Điểm trung bình tích lũy (GPA)
    int accumulatedCredits;        // 17. Số tín chỉ tích lũy
    std::string advisor;           // 18. Cố vấn học tập

public:
    // Default constructor
    Student() : admissionScore(0.0), enrollmentYear(0), gpa(0.0), accumulatedCredits(0) {}

    // Parameterized constructor
    Student(std::string mssv, std::string fullName, std::string classCode, std::string dob,
            std::string hometown, std::string gender, std::string admMethod, double admScore,
            std::string email, std::string phone, std::string address, std::string major,
            std::string dept, std::string status, int enrollYear, double gpaVal,
            int credits, std::string adv)
        : mssv(mssv), fullName(fullName), classCode(classCode), dateOfBirth(dob),
          hometown(hometown), gender(gender), admissionMethod(admMethod), admissionScore(admScore),
          email(email), phoneNumber(phone), address(address), major(major),
          department(dept), academicStatus(status), enrollmentYear(enrollYear), gpa(gpaVal),
          accumulatedCredits(credits), advisor(adv) {}

    // Getters
    std::string getMSSV() const { return mssv; }
    std::string getFullName() const { return fullName; }
    std::string getClassCode() const { return classCode; }
    std::string getDateOfBirth() const { return dateOfBirth; }
    std::string getHometown() const { return hometown; }
    std::string getGender() const { return gender; }
    std::string getAdmissionMethod() const { return admissionMethod; }
    double getAdmissionScore() const { return admissionScore; }
    std::string getEmail() const { return email; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getAddress() const { return address; }
    std::string getMajor() const { return major; }
    std::string getDepartment() const { return department; }
    std::string getAcademicStatus() const { return academicStatus; }
    int getEnrollmentYear() const { return enrollmentYear; }
    double getGPA() const { return gpa; }
    int getAccumulatedCredits() const { return accumulatedCredits; }
    std::string getAdvisor() const { return advisor; }

    // Setters
    void setMSSV(const std::string& val) { mssv = val; }
    void setFullName(const std::string& val) { fullName = val; }
    void setClassCode(const std::string& val) { classCode = val; }
    void setDateOfBirth(const std::string& val) { dateOfBirth = val; }
    void setHometown(const std::string& val) { hometown = val; }
    void setGender(const std::string& val) { gender = val; }
    void setAdmissionMethod(const std::string& val) { admissionMethod = val; }
    void setAdmissionScore(double val) { admissionScore = val; }
    void setEmail(const std::string& val) { email = val; }
    void setPhoneNumber(const std::string& val) { phoneNumber = val; }
    void setAddress(const std::string& val) { address = val; }
    void setMajor(const std::string& val) { major = val; }
    void setDepartment(const std::string& val) { department = val; }
    void setAcademicStatus(const std::string& val) { academicStatus = val; }
    void setEnrollmentYear(int val) { enrollmentYear = val; }
    void setGPA(double val) { gpa = val; }
    void setAccumulatedCredits(int val) { accumulatedCredits = val; }
    void setAdvisor(const std::string& val) { advisor = val; }

    // Overloaded == operator for search/matching by MSSV
    bool operator==(const Student& other) const {
        return this->mssv == other.mssv;
    }

    // Prints a nice compact row formatted for list displays
    void printRow() const {
        std::cout << "| " << std::left << std::setw(10) << mssv
                  << " | " << std::setw(20) << fullName.substr(0, 20)
                  << " | " << std::setw(10) << classCode
                  << " | " << std::setw(10) << dateOfBirth
                  << " | " << std::setw(12) << hometown.substr(0, 12)
                  << " | " << std::setw(6) << gender
                  << " | " << std::setw(6) << std::fixed << std::setprecision(2) << gpa
                  << " | " << std::setw(5) << accumulatedCredits << " |" << std::endl;
    }

    // Prints a detailed, card-like display of all 18 fields
    void printCard() const {
        std::cout << "==================================================" << std::endl;
        std::cout << "             THÔNG TIN CHI TIẾT SINH VIÊN          " << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << " 1. MSSV:                 " << mssv << std::endl;
        std::cout << " 2. Họ và tên:            " << fullName << std::endl;
        std::cout << " 3. Lớp sinh hoạt:        " << classCode << std::endl;
        std::cout << " 4. Ngày sinh:            " << dateOfBirth << std::endl;
        std::cout << " 5. Quê quán:             " << hometown << std::endl;
        std::cout << " 6. Giới tính:            " << gender << std::endl;
        std::cout << " 7. PT xét tuyển:         " << admissionMethod << std::endl;
        std::cout << " 8. Điểm xét tuyển:       " << admissionScore << std::endl;
        std::cout << " 9. Email:                " << email << std::endl;
        std::cout << "10. Số điện thoại:        " << phoneNumber << std::endl;
        std::cout << "11. Địa chỉ thường trú:   " << address << std::endl;
        std::cout << "12. Ngành học:            " << major << std::endl;
        std::cout << "13. Khoa viện:            " << department << std::endl;
        std::cout << "14. Tình trạng học tập:   " << academicStatus << std::endl;
        std::cout << "15. Năm nhập học:         " << enrollmentYear << std::endl;
        std::cout << "16. Điểm tích lũy (GPA):  " << std::fixed << std::setprecision(2) << gpa << std::endl;
        std::cout << "17. Tín chỉ tích lũy:     " << accumulatedCredits << std::endl;
        std::cout << "18. Cố vấn học tập:       " << advisor << std::endl;
        std::cout << "==================================================" << std::endl;
    }

    // Serialize to CSV row
    std::string toCSV() const {
        return mssv + "," +
               fullName + "," +
               classCode + "," +
               dateOfBirth + "," +
               hometown + "," +
               gender + "," +
               admissionMethod + "," +
               std::to_string(admissionScore) + "," +
               email + "," +
               phoneNumber + "," +
               address + "," +
               major + "," +
               department + "," +
               academicStatus + "," +
               std::to_string(enrollmentYear) + "," +
               std::to_string(gpa) + "," +
               std::to_string(accumulatedCredits) + "," +
               advisor;
    }
};

#endif // STUDENT_H
