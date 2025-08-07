#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits> // Required for numeric_limits

#include "display.cpp"
using namespace std;

struct Student {
    int id;
    string name;
    string className;
    char section;
};

class StudentManagementSystem {
private:
    vector<Student> students;
    map<string, map<int, bool>> attendanceRecords;
    // Removed nextStudentId as IDs are now user-provided
    // int nextStudentId; 

public:
    // Removed nextStudentId initialization from constructor
    StudentManagementSystem() {} 

    Student* findStudentById(int id) {
        for (auto& student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    void addStudent() {
        Student newStudent;
        int inputId;

        cout << "\n--- Add New Student ---\n";
        cout << "Enter Student ID: "; // Prompt user for ID
        // Input validation for ID
        while (!(cin >> inputId) || inputId <= 0) {
            cout << "Invalid input. Please enter a positive number for Student ID: ";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        newStudent.id = inputId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer for subsequent getline

        // Check if ID already exists
        if (findStudentById(newStudent.id)) {
            cout << "Error: Student with ID " << newStudent.id << " already exists. Student not added.\n";
            return; // Exit function if ID is a duplicate
        }

        cout << "Enter Student Name: ";
        getline(cin, newStudent.name);
        if (newStudent.name.empty()) {
            cout << "Name cannot be empty. Student not added.\n";
            return;
        }

        cout << "Enter Student Class (e.g., 10, 12): ";
        getline(cin, newStudent.className);

        cout << "Enter Student Section (e.g., A, B, or leave empty if none): ";
        string sectionInput;
        getline(cin, sectionInput);
        if (!sectionInput.empty()) {
            newStudent.section = toupper(sectionInput[0]);
        } else {
            newStudent.section = ' ';
        }

        students.push_back(newStudent);
        cout << "Student '" << newStudent.name << "' added successfully with ID " << newStudent.id << ".\n";
    }

    void editStudent() {
        int id;
        cout << "Enter the ID of the student to edit: ";
        cin >> id;

        Student* studentToEdit = findStudentById(id);

        if (studentToEdit) {
            cout << "Editing Student: " << studentToEdit->name << " (ID: " << studentToEdit->id << ")\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter new name (current: " << studentToEdit->name << "): ";
            getline(cin, studentToEdit->name);

            cout << "Enter new Class (current: " << studentToEdit->className << "): ";
            getline(cin, studentToEdit->className);

            cout << "Enter new Section (current: " << studentToEdit->section << "): ";
            string sectionInput;
            getline(cin, sectionInput);
            if (!sectionInput.empty()) {
                studentToEdit->section = toupper(sectionInput[0]);
            } else {
                studentToEdit->section = ' ';
            }

            cout << "Student updated successfully!\n";
        } else {
            cout << "Student with ID " << id << " not found.\n";
        }
    }

    void deleteStudent() {
        int id;
        cout << "Enter the ID of the student to delete: ";
        cin >> id;

        int index = -1;
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].id == id) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            cout << "Deleting student: " << students[index].name << " (ID: " << students[index].id << ")\n";
            students.erase(students.begin() + index);
            cout << "Student deleted successfully.\n";

            for (auto& dateRecord : attendanceRecords) {
                dateRecord.second.erase(id);
            }
        } else {
            cout << "Student with ID " << id << " not found.\n";
        }
    }

    void searchStudent() const {
        int id;
        cout << "Enter student ID to search: ";
        cin >> id;

        const Student* foundStudent = nullptr;
        for (const auto& s : students) {
            if (s.id == id) {
                foundStudent = &s;
                break;
            }
        }

        if (foundStudent) {
            cout << "\nStudent Found:\n";
            cout << "  Name: " << foundStudent->name << "\n";
            cout << "  ID: " << foundStudent->id << "\n";
            cout << "  Class: " << foundStudent->className << "\n";
            if (foundStudent->section != ' ') {
                cout << "  Section: " << foundStudent->section;
            }
            cout << "\n";
        } else {
            cout << "Student with ID " << id << " not found.\n";
        }
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        cout << "\n--- All Students ---\n";
        cout << left << setw(10) << "ID" << setw(25) << "Name"
             << setw(10) << "Class" << "Section\n";
        cout << string(60, '-') << "\n";

        for (const auto& s : students) {
            cout << left << setw(10) << s.id << setw(25) << s.name
                 << setw(10) << s.className << (s.section != ' ' ? s.section : '-') << "\n";
        }
    }

    void markAttendance() {
        if (students.empty()) {
            cout << "No students found. Add students first.\n";
            return;
        }

        cout << "\nEnter date (YYYY-MM-DD): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string date;
        getline(cin, date);
        if (date.empty()) {
            cout << "Date cannot be empty. Attendance not marked.\n";
            return;
        }

        cout << "Mark attendance for date: " << date << "\n";
        for (const auto& student : students) {
            string input;
            while (true) {
                cout << "Is " << student.name << " (ID: " << student.id << ") present? (y/n): ";
                getline(cin, input);
                if (input == "y" || input == "Y") {
                    attendanceRecords[date][student.id] = true;
                    break;
                } else if (input == "n" || input == "N") {
                    attendanceRecords[date][student.id] = false;
                    break;
                } else {
                    cout << "Invalid input. Please enter 'y' or 'n'.\n";
                }
            }
        }
        cout << "Attendance recorded for " << date << ".\n";
    }

    void viewAttendance() const {
        if (attendanceRecords.empty()) {
            cout << "No attendance records found.\n";
            return;
        }

        cout << "\nEnter date (YYYY-MM-DD) to view attendance: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string date;
        getline(cin, date);
        if (date.empty()) {
            cout << "Date cannot be empty.\n";
            return;
        }

        auto it = attendanceRecords.find(date);
        if (it == attendanceRecords.end()) {
            cout << "No attendance records for this date.\n";
            return;
        }

        cout << "Attendance for " << date << ":\n";
        cout << left << setw(10) << "ID" << setw(30) << "Name" << "Present\n";
        cout << string(50, '-') << "\n";

        for (const auto& student : students) {
            bool present = false;
            auto pIt = it->second.find(student.id);
            if (pIt != it->second.end()) {
                present = pIt->second;
            }
            cout << left << setw(10) << student.id << setw(30) << student.name << (present ? "Yes" : "No") << "\n";
        }
    }

    void saveToFile(const string& filename = "system_data.txt") {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file for writing: " << filename << "\n";
            return;
        }

        file << "STUDENTS\n";
        // Removed nextStudentId from saving since it's user-provided now
        // file << nextStudentId << "\n"; 
        for (const auto& student : students) {
            file << student.id << "," << student.name << ","
                 << student.className << "," << student.section << "\n";
        }
        file << "END_STUDENTS\n";

        file << "ATTENDANCE\n";
        for (const auto& dateEntry : attendanceRecords) {
            file << dateEntry.first << "\n";
            for (const auto& record : dateEntry.second) {
                file << record.first << "," << (record.second ? 1 : 0) << "\n";
            }
            file << "END_DATE\n";
        }
        file << "END_ATTENDANCE\n";

        file.close();
        cout << "All data saved to " << filename << ".\n";
    }

    void loadFromFile(const string& filename = "system_data.txt") {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No data file '" << filename << "' found. Starting with empty records.\n";
            return;
        }

        students.clear();
        attendanceRecords.clear();
        // Removed nextStudentId reset as it's not auto-generated
        // nextStudentId = 1; 

        string line;
        enum Section { NONE, STUDENTS, ATTENDANCE } currentSection = NONE;
        string currentDate;

        while (getline(file, line)) {
            if (line == "STUDENTS") {
                currentSection = STUDENTS;
                // Removed reading nextStudentId as it's not auto-generated
                // if (getline(file, line)) { nextStudentId = stoi(line); } 
                continue;
            } else if (line == "END_STUDENTS") {
                currentSection = NONE;
                continue;
            } else if (line == "ATTENDANCE") {
                currentSection = ATTENDANCE;
                continue;
            } else if (line == "END_ATTENDANCE") {
                currentSection = NONE;
                continue;
            }

            if (currentSection == STUDENTS) {
                stringstream ss(line);
                string segment;
                Student s;
                getline(ss, segment, ','); s.id = stoi(segment);
                getline(ss, s.name, ',');
                getline(ss, s.className, ',');
                getline(ss, segment);
                s.section = segment.empty() ? ' ' : segment[0];

                students.push_back(s);

            } else if (currentSection == ATTENDANCE) {
                if (line == "END_DATE") {
                    currentDate.clear();
                } else if (currentDate.empty()) {
                    currentDate = line;
                } else {
                    stringstream ss(line);
                    string sid_str, present_str;
                    getline(ss, sid_str, ',');
                    getline(ss, present_str);
                    int sid = stoi(sid_str);
                    bool present = (present_str == "1");
                    attendanceRecords[currentDate][sid] = present;
                }
            }
        }
        file.close();
        cout << "Data loaded from " << filename << ".\n";
    }
};

void ShowMenu() {
    cout << "\n===== Student Management & Attendance System =====\n";
    cout << "1. Add Student\n";
    cout << "2. Edit Student Details\n";
    cout << "3. Delete Student\n";
    cout << "4. Search Student\n";
    cout << "5. Display All Students\n";
    cout << "6. Mark Attendance\n";
    cout << "7. View Attendance\n";
    cout << "8. Save All Data\n";
    cout << "9. Load All Data\n";
    cout << "10. Exit\n";
    cout << "Select an option: ";
}

int main() {
    showTitle();
    StudentManagementSystem system;
    system.loadFromFile();

    int choice;
    do {
        ShowMenu();
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                system.addStudent();
                break;
            case 2:
                system.editStudent();
                break;
            case 3:
                system.deleteStudent();
                break;
            case 4:
                system.searchStudent();
                break;
            case 5:
                system.displayAllStudents();
                break;
            case 6:
                system.markAttendance();
                break;
            case 7:
                system.viewAttendance();
                break;
            case 8:
                system.saveToFile();
                break;
            case 9:
                system.loadFromFile();
                break;
            case 10:
                cout << "Exiting the program! Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (choice != 10);

    return 0;
}