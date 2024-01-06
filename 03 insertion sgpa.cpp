#include <iostream>
#include <string>

using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

void insertionSort(Student students[], int n) {
    for (int i = 1; i < n; ++i) {
        Student key = students[i];
        int j = i - 1;

        while (j >= 0 && students[j].name > key.name) {
            students[j + 1] = students[j];
            --j;
        }
        students[j + 1] = key;
    }
}

void printStudents(Student students[], int n) {
    cout << "Roll No\t Name\t SGPA\n";
    for (int i = 0; i < n; ++i) {
        cout << students[i].rollNo << "\t " << students[i].name << "\t " << students[i].sgpa << "\n";
    }
}

void searchBySGPA(Student students[], int n, float searchSGPA) {
    bool found = false;
    cout << "Students with SGPA " << searchSGPA << ":\n";
    for (int i = 0; i < n; ++i) {
        if (students[i].sgpa == searchSGPA) {
            found = true;
            cout << students[i].name << "\n";
        }
    }
    if (!found) {
        cout << "No student found with SGPA " << searchSGPA << "\n";
    }
}

int main() {
    const int maxSize = 15;
    Student students[maxSize];

    int numStudents;
    cout << "Enter the number of students (max 15): ";
    cin >> numStudents;
    cin.ignore(); // Clear newline from buffer

    if (numStudents > maxSize) {
        cout << "Exceeded maximum limit of students.\n";
        return 1;
    }

    for (int i = 0; i < numStudents; ++i) {
        cout << "Enter details for student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> students[i].rollNo;
        cin.ignore(); // Clear newline from buffer

        cout << "Name: ";
        getline(cin, students[i].name);

        cout << "SGPA: ";
        cin >> students[i].sgpa;
        cin.ignore(); // Clear newline from buffer
    }

    cout << "\nBefore sorting:\n";
    printStudents(students, numStudents);

    insertionSort(students, numStudents);

    cout << "\nAfter sorting alphabetically:\n";
    printStudents(students, numStudents);

    float searchSGPA;
    cout << "\nEnter SGPA to search for: ";
    cin >> searchSGPA;
    searchBySGPA(students, numStudents, searchSGPA);
    return 0;
}
