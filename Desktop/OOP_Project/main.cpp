
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    float marks;

public:
    // Add Student
    void addStudent()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cout << "Enter Name (one word): ";
        cin >> name;

        cout << "Enter Marks (0-100): ";
        cin >> marks;

        if (marks < 0 || marks > 100)
        {
            cout << "Invalid marks!\n";
            return;
        }

        // Check for duplicate roll number
        ifstream check("students.txt");
        int r;
        string n;
        float m;

        while (check >> r >> n >> m)
        {
            if (r == rollNo)
            {
                check.close();
                cout << "Roll Number already exists!\n";
                return;
            }
        }
        check.close();

        ofstream file("students.txt", ios::app);

        if (file.is_open())
        {
            file << rollNo << " "
                 << name << " "
                 << marks << endl;

            file.close();
            cout << "Student added successfully!\n";
        }
        else
        {
            cout << "Error opening file!\n";
        }
    }

    // Display All Students
    void displayStudents()
    {
        ifstream file("students.txt");

        int r;
        string n;
        float m;
        bool found = false;

        if (!file.is_open())
        {
            cout << "\nNo student records found.\n";
            return;
        }

        cout << "\n===== STUDENT RECORDS =====\n";

        while (file >> r >> n >> m)
        {
            cout << "\nRoll Number: " << r;
            cout << "\nName: " << n;
            cout << "\nMarks: " << m;
            cout << "\nGrade: ";

            if (m >= 75)
                cout << "Distinction";
            else if (m >= 60)
                cout << "First Class";
            else if (m >= 40)
                cout << "Pass";
            else
                cout << "Fail";

            cout << "\n--------------------------\n";
            found = true;
        }

        if (!found)
            cout << "No student records found.\n";

        file.close();
    }

    // Search Student
    void searchStudent()
    {
        ifstream file("students.txt");

        int r, searchRoll;
        string n;
        float m;
        bool found = false;

        cout << "\nEnter Roll Number to search: ";
        cin >> searchRoll;

        while (file >> r >> n >> m)
        {
            if (r == searchRoll)
            {
                cout << "\nStudent Found!\n";
                cout << "Roll Number: " << r;
                cout << "\nName: " << n;
                cout << "\nMarks: " << m << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Student not found.\n";

        file.close();
    }

    // Update Student
    void updateStudent()
    {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        if (!temp.is_open())
        {
            cout << "Unable to create temporary file!\n";
            file.close();
            return;
        }

        int r, searchRoll, newRoll;
        string n, newName;
        float m, newMarks;
        bool found = false;

        cout << "\nEnter Roll Number to update: ";
        cin >> searchRoll;

        while (file >> r >> n >> m)
        {
            if (r == searchRoll)
            {
                cout << "Enter New Roll Number: ";
                cin >> newRoll;

                cout << "Enter New Name (one word): ";
                cin >> newName;

                cout << "Enter New Marks (0-100): ";
                cin >> newMarks;

                if (newMarks < 0 || newMarks > 100)
                {
                    cout << "Invalid marks! Update cancelled.\n";
                    file.close();
                    temp.close();
                    remove("temp.txt");
                    return;
                }

                // Check if the new roll number is already used
                bool duplicate = false;
                ifstream check("students.txt");
                int cr;
                string cn;
                float cm;

                while (check >> cr >> cn >> cm)
                {
                    if (cr == newRoll && cr != searchRoll)
                        duplicate = true;
                }
                check.close();

                if (duplicate)
                {
                    cout << "New Roll Number already exists!\n";
                    file.close();
                    temp.close();
                    remove("temp.txt");
                    return;
                }

                temp << newRoll << " "
                     << newName << " "
                     << newMarks << endl;

                found = true;
            }
            else
            {
                temp << r << " " << n
                     << " " << m << endl;
            }
        }

        file.close();
        temp.close();

        if (found)
        {
            remove("students.txt");

            if (rename("temp.txt", "students.txt") == 0)
                cout << "Student updated successfully!\n";
            else
                cout << "Error saving updated records!\n";
        }
        else
        {
            remove("temp.txt");
            cout << "Student not found!\n";
        }
    }

    // Delete Student
    void deleteStudent()
    {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        if (!temp.is_open())
        {
            cout << "Unable to create temporary file!\n";
            file.close();
            return;
        }

        int r, searchRoll;
        string n;
        float m;
        bool found = false;

        cout << "\nEnter Roll Number to delete: ";
        cin >> searchRoll;

        while (file >> r >> n >> m)
        {
            if (r == searchRoll)
            {
                found = true;
            }
            else
            {
                temp << r << " " << n
                     << " " << m << endl;
            }
        }

        file.close();
        temp.close();

        if (found)
        {
            remove("students.txt");

            if (rename("temp.txt", "students.txt") == 0)
                cout << "Student deleted successfully!\n";
            else
                cout << "Error saving records!\n";
        }
        else
        {
            remove("temp.txt");
            cout << "Student not found!\n";
        }
    }

    // Calculate Grade
    void calculateGrade()
    {
        float m;

        cout << "\nEnter Marks (0-100): ";
        cin >> m;

        if (m < 0 || m > 100)
            cout << "Invalid marks!\n";
        else if (m >= 75)
            cout << "Grade: Distinction\n";
        else if (m >= 60)
            cout << "Grade: First Class\n";
        else if (m >= 40)
            cout << "Grade: Pass\n";
        else
            cout << "Grade: Fail\n";
    }
};

int main()
{
    Student s;
    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "   STUDENT MANAGEMENT SYSTEM\n";
        cout << "================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Calculate Grade\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s.addStudent();
            break;

        case 2:
            s.displayStudents();
            break;

        case 3:
            s.searchStudent();
            break;

        case 4:
            s.updateStudent();
            break;

        case 5:
            s.deleteStudent();
            break;

        case 6:
            s.calculateGrade();
            break;

        case 7:
            cout << "Thank you for using the system!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
// g++ main.cpp -o student
// .\student.exe