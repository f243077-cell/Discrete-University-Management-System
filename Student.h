#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string id;
    string name;

    string completed[50];
    int completedCount;

    string taking[50];
    int takingCount;

public:
    Student() {
        id = "";
        name = "";
        completedCount = 0;
        takingCount = 0;
    }

    Student(string i, string n) {
        id = i;
        name = n;
        completedCount = 0;
        takingCount = 0;
    }

    // Getters - make sure these are const
    string getID() const {
        return id;
    }
    
    string getName() const {
        return name;
    }

    void addCompleted(string courseCode) {
        if (completedCount < 50)
            completed[completedCount++] = courseCode;
    }

    void addTaking(string courseCode) {
        if (takingCount < 50)
            taking[takingCount++] = courseCode;
    }

    bool hasCompleted(string courseCode) const {
        for (int i = 0; i < completedCount; i++)
            if (completed[i] == courseCode)
                return true;
        return false;
    }

    void display() const {
        cout << "\n--- Student Info ---\n";
        cout << "ID: " << id << "\nName: " << name << "\n";

        cout << "Completed: ";
        if (completedCount == 0) cout << "None";
        else {
            for (int i = 0; i < completedCount; i++) {
                cout << completed[i];
                if (i < completedCount - 1) cout << ", ";
            }
        }
        cout << "\n";

        cout << "Taking: ";
        if (takingCount == 0) cout << "None";
        else {
            for (int i = 0; i < takingCount; i++) {
                cout << taking[i];
                if (i < takingCount - 1) cout << ", ";
            }
        }
        cout << "\n";
    }
};

#endif
