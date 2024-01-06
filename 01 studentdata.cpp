#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string division;
    string address;
};

const string filename = "student_database.txt";

void addStudent() {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening the file." << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    file << student.rollNo << " " << student.name << " " << student.division << " " << student.address << endl;
    file.close();

    cout << "Student record added successfully." << endl;
}

void displayStudent(int rollNumber) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening the file." << endl;
        return;
    }

    bool found = false;
    Student student;
    while (file >> student.rollNo >> student.name >> student.division >> ws && getline(file, student.address)) {
        if (student.rollNo == rollNumber) {
            found = true;
            cout << "Roll Number: " << student.rollNo << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found." << endl;
    }

    file.close();
}

void deleteStudent(int rollNumber) {
    ifstream fileIn(filename);
    ofstream fileOut("temp.txt");

    if (!fileIn || !fileOut) {
        cout << "Error opening the file." << endl;
        return;
    }

    bool found = false;
    Student student;
    while (fileIn >> student.rollNo >> student.name >> student.division >> ws && getline(fileIn, student.address)) {
        if (student.rollNo == rollNumber) {
            found = true;
            cout << "Student with Roll Number " << student.rollNo << " deleted." << endl;
            continue;
        }
        fileOut << student.rollNo << " " << student.name << " " << student.division << " " << student.address << endl;
    }

    if (!found) {
        cout << "Student record not found." << endl;
    }

    fileIn.close();
    fileOut.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

int main() {
    int choice, rollNo;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to display: ";
                cin >> rollNo;
                displayStudent(rollNo);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid choice." << endl;
        }
    } while (choice != 4);

    return 0;
}
