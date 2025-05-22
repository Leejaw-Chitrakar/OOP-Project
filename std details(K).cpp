/*Student ID (integer, unique identifier)
    Name (string)
    Class/Grade (string/integer)
    Section (character/string, optional)
    */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct stStudent{
    string name;
    int roll;
    float mark;
};

void ShowMenu(){
    cout << "\n === Student Management System ===\n";
    cout << "1. Add student\n";
    cout << "2. Edit Student\n";
    cout << "3. Delete Student\n";
    cout << "4. Search Student\n";
    cout << "5. Display All Student\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

void addStudent(vector<stStudent> & student){
    stStudent newStudent;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin,newStudent.name);

    cout << "Enter Student Roll no.: ";
    cin >> newStudent.roll;

    cout << "Enter Student mark: ";
    cin >> newStudent.mark;

    student.push_back(newStudent);
    cout << "student added successfully.\n";
}

int findStudentByRoll(const vector<stStudent> &students,int roll){
    for(size_t i=0; i < students.size(); ++i){
        if(students[i].roll == roll){
            return i;
        }
    }
    return -1;
}

void editStudent(vector<stStudent>& students){
    int roll;
	cout<<"Enter the Roll no. of the student to edit:";
	cin>>roll;
	int index=findStudentByRoll(students,roll);
	if(index != -1){
		cout<<"Editing Student:" << students[index].name <<endl;
		cout<<"Enter new name:";
		cin.ignore();
		getline(cin,students[index].name);

		cout<<"Enter new mark:";
		cin>>students[index].mark;

		cout<<"student update successfully"<<endl;

	}
	else{
		cout<<"Student not found."<<endl;
	}
}

void deleteStudent(vector<stStudent>& students){
	int roll;
	cout<<"Enter the ID of the student to delete:";
	cin>>roll;

	int index= findStudentByRoll(students,roll);

	if(index !=-1){
		cout<< "Deleting student:" <<students[index].name<<endl;
		students.erase(students.begin()+index);
		cout<<"Student deleted successfully."<<endl;
	}
	else{
		cout<<"Student not found."<<endl;
	}
}

void searchStudent(const vector<stStudent> & students){
	int roll;
	cout<<"Enter student ID to search:";
	cin>>roll;
	int index=findStudentByRoll(students,roll);
	if(index != -1){
		cout<<"Student Found:"<<endl;
		cout<<"Name"<<students[index].name <<endl;
		cout<<"ID:"<<students[index].roll <<endl;
		cout<<"Mark:" <<students[index].mark<<endl;
	}
	else{
		cout<<"Student not found."<<endl;
	}
}

void DisplayAllStudents(const vector<stStudent>& students){
	if(students.empty()){
		cout<<"No students available."<<endl;
		return ;
	}

	cout<<endl<<"All Students:"<<endl;
	for(const stStudent& s :students){
		cout<<"Name:"<<s.name<<"| ID:"<<s.roll<<" | Mark:"<<s.mark<<endl;
	}
}

int main ()
{
	vector<stStudent> students;
	int choice;
	do
	{
		ShowMenu();
		cin>>choice;
		switch (choice){
			case 1:
				addStudent(students);
            break;

            case 2:
                editStudent(students);
            break;

            case 3:
                deleteStudent(students);
            break;

            case 4:
                searchStudent(students);
            break;

            case 5:
                DisplayAllStudents(students);
            break;

            case 6:
                cout<<"Exiting the program!"<<endl;
            break;

            default:
                cout<<"Invalid option. PLease try again."<<endl;
            break;

        }
    }while (choice !=6);
	return 0;
}
