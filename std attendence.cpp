#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Student {
    int id;
    string name;
};

class AttendanceSystem {
private:
    vector<Student> students;
    // Map of date -> map of studentId -> present(true/false)
    map<string, map<int, bool>> attendanceRecords;
    int nextStudentId;

public:
    AttendanceSystem() : nextStudentId(1) {}

    void addStudent() {
        cout << "Enter student name: ";
        string name;
        getline(cin, name);
        if (name.empty()) {
            cout << "Name cannot be empty.\n";
            return;
        }
        Student s;
        s.id = nextStudentId++;
        s.name = name;
        students.push_back(s);
        cout << "Student added with ID " << s.id << ".\n";
    }

    void markAttendance() {
        if (students.empty()) {
            cout << "No students found. Add students first.\n";
            return;
        }

        cout << "Enter date (YYYY-MM-DD): ";
        string date;
        getline(cin, date);
        if (date.empty()) {
            cout << "Date cannot be empty.\n";
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
                    cout << "Please enter 'y' or 'n'.\n";
                }
            }
        }
        cout << "Attendance recorded for " << date << ".\n";
    }

    void viewAttendance() {
        if (attendanceRecords.empty()) {
            cout << "No attendance records found.\n";
            return;
        }

        cout << "Enter date (YYYY-MM-DD) to view attendance: ";
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

    void saveToFile() {
        ofstream file("attendance_data.txt");
        if (!file) {
            cout << "Error opening file for writing.\n";
            return;
        }
        // Save students
        file << "STUDENTS\n";
        for (const auto& student : students) {
            file << student.id << "," << student.name << "\n";
        }
        file << "END_STUDENTS\n";

        // Save attendance records
        file << "ATTENDANCE\n";
        for (const auto& dateEntry : attendanceRecords) {
            file << dateEntry.first << "\n";
            for (const auto& record : dateEntry.second) {
                file << record.first << "," << (record.second ? 1 : 0) << "\n";
            }
            file << "END_DATE\n";
        }
        file << "END_ATTENDANCE\n";

        cout << "Data saved to attendance_data.txt.\n";
    }

    void loadFromFile() {
        ifstream file("attendance_data.txt");
        if (!file) {
            cout << "No data file found, starting with empty records.\n";
            return;
        }

        students.clear();
        attendanceRecords.clear();
        nextStudentId = 1;

        string line;
        enum Section { NONE, STUDENTS, ATTENDANCE } section = NONE;
        string currentDate;

        while (getline(file, line)) {
            if (line == "STUDENTS") {
                section = STUDENTS;
                continue;
            } else if (line == "END_STUDENTS") {
                section = NONE;
                continue;
            } else if (line == "ATTENDANCE") {
                section = ATTENDANCE;
                continue;
            } else if (line == "END_ATTENDANCE") {
                section = NONE;
                continue;
            }

            if (section == STUDENTS) {
                int commaPos = line.find(',');
                if (commaPos != string::npos) {
                    int id = stoi(line.substr(0, commaPos));
                    string name = line.substr(commaPos + 1);
                    students.push_back({id, name});
                    if (id >= nextStudentId)
                        nextStudentId = id + 1;
                }
            } else if (section == ATTENDANCE) {
                if (line == "END_DATE") {
                    currentDate.clear();
                } else if (currentDate.empty()) {
                    currentDate = line;
                } else {
                    int commaPos = line.find(',');
                    if (commaPos != string::npos) {
                        int sid = stoi(line.substr(0, commaPos));
                        bool present = line.substr(commaPos + 1) == "1";
                        attendanceRecords[currentDate][sid] = present;
                    }
                }
            }
        }
        cout << "Data loaded from attendance_data.txt.\n";
    }

    void listStudents() {
        if (students.empty()) {
            cout << "No students added yet.\n";
            return;
        }
        cout << left << setw(10) << "ID" << "Name\n";
        cout << string(30, '-') << "\n";
        for (const auto& student : students) {
            cout << left << setw(10) << student.id << student.name << "\n";
        }
    }
};

void showMenu() {
    cout << "\n===== Student Attendance System =====\n";
    cout << "1. Add Student\n";
    cout << "2. List Students\n";
    cout << "3. Mark Attendance\n";
    cout << "4. View Attendance\n";
    cout << "5. Save Data\n";
    cout << "6. Load Data\n";
    cout << "7. Exit\n";
    cout << "Select an option: ";
}

int main() {
    AttendanceSystem system;
    system.loadFromFile();

    while (true) {
        showMenu();
        string choiceStr;
        getline(cin, choiceStr);
        if (choiceStr.empty()) continue;
        int choice = stoi(choiceStr);

        switch (choice) {
            case 1:
                system.addStudent();
                break;
            case 2:
                system.listStudents();
                break;
            case 3:
                system.markAttendance();
                break;
            case 4:
                system.viewAttendance();
                break;
            case 5:
                system.saveToFile();
                break;
            case 6:
                system.loadFromFile();
                break;
            case 7:
                cout << "Exiting. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
    return 0;
}

