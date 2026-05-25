#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "../datastructures/LinkedList.h"
#include "../datastructures/HashMap.h"
#include "../models/Student.h"
#include <iostream>

class StudentManager {
private:
    LinkedList<Student*> allClasses;   // Single source of truth: owns the Student* objects
    HashMap studentsByMSSV;            // Index: quick lookups mapping MSSV to Student*

public:
    StudentManager() {}

    const LinkedList<Student*>& getAllClasses() const {
        return allClasses;
    }

    ~StudentManager() {
        cleanUp();
    }

    // Disable copy constructor and assignment
    StudentManager(const StudentManager&) = delete;
    StudentManager& operator=(const StudentManager&) = delete;

    // Release all dynamically allocated Student objects
    void cleanUp() {
        Node<Student*>* current = allClasses.getHead();
        while (current != nullptr) {
            delete current->data; // Delete the Student instance
            current = current->next;
        }
        allClasses.clear();
        studentsByMSSV.clear();
    }

    // Add student. Takes ownership of Student* pointer.
    // Returns true if successfully added, false if MSSV is a duplicate.
    bool addStudent(Student* s) {
        if (s == nullptr) return false;

        // Ensure MSSV is unique
        if (studentsByMSSV.get(s->getMSSV()) != nullptr) {
            return false;
        }

        // Add to HashMap
        studentsByMSSV.put(s->getMSSV(), s);

        // Add to overall LinkedList
        allClasses.insertAtTail(s);
        return true;
    }

    // Find student by MSSV (O(1) expected via HashMap)
    Student* findStudentByMSSV(const std::string& mssv) const {
        return studentsByMSSV.get(mssv);
    }

    // Find students by Class (O(N) sequential search)
    // Note: Returns a newly constructed LinkedList of Student* pointers.
    // The caller is responsible for letting this returned LinkedList fall out of scope
    // (which cleans up its nodes but does not delete the Student instances).
    LinkedList<Student*>* findStudentsByClass(const std::string& classCode) const {
        LinkedList<Student*>* results = new LinkedList<Student*>();
        Node<Student*>* current = allClasses.getHead();
        
        while (current != nullptr) {
            if (current->data->getClassCode() == classCode) {
                results->insertAtTail(current->data);
            }
            current = current->next;
        }
        return results;
    }

    // Find students by Hometown (O(N) sequential search)
    LinkedList<Student*>* findStudentsByHometown(const std::string& hometown) const {
        LinkedList<Student*>* results = new LinkedList<Student*>();
        Node<Student*>* current = allClasses.getHead();
        
        while (current != nullptr) {
            // Case-insensitive or substring matches can be added, but exact match is standard.
            if (current->data->getHometown() == hometown) {
                results->insertAtTail(current->data);
            }
            current = current->next;
        }
        return results;
    }

    // Delete student by MSSV. Releases the student's dynamic memory.
    // Returns true if successfully deleted, false if student not found.
    bool deleteStudent(const std::string& mssv) {
        Student* s = studentsByMSSV.get(mssv);
        if (s == nullptr) return false;

        // Remove from HashMap
        studentsByMSSV.remove(mssv);

        // Remove from LinkedList
        allClasses.remove(s);

        // Deallocate student record
        delete s;
        return true;
    }

    size_t getStudentCount() const {
        return allClasses.getSize();
    }

    // Prints a formatted table of all students
    void printAll() const {
        if (allClasses.isEmpty()) {
            std::cout << "Danh sach sinh vien trong." << std::endl;
            return;
        }

        printTableHeader();
        Node<Student*>* current = allClasses.getHead();
        while (current != nullptr) {
            current->data->printRow();
            current = current->next;
        }
        printTableFooter();
    }

    // Static helper to print headers
    static void printTableHeader() {
        std::cout << "+" << std::string(86, '-') << "+" << std::endl;
        std::cout << "| " << std::left << std::setw(10) << "MSSV"
                  << " | " << std::setw(20) << "Ho va ten"
                  << " | " << std::setw(10) << "Lop"
                  << " | " << std::setw(10) << "Ngay sinh"
                  << " | " << std::setw(12) << "Que quan"
                  << " | " << std::setw(6) << "G.Tinh"
                  << " | " << std::setw(6) << "GPA"
                  << " | " << std::setw(5) << "T.Chi" << " |" << std::endl;
        std::cout << "+" << std::string(86, '-') << "+" << std::endl;
    }

    static void printTableFooter() {
        std::cout << "+" << std::string(86, '-') << "+" << std::endl;
    }

    // Returns collision rate of the HashMap (for quality report in Phase 6)
    double getCollisionRate() const {
        if (getStudentCount() == 0) return 0.0;
        size_t collisions = studentsByMSSV.getCollisionCount();
        return (double)collisions / studentsByMSSV.getSize() * 100.0;
    }
};

#endif // STUDENTMANAGER_H
