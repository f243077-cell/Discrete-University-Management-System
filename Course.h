#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
using namespace std;

class Course {
private:
    string courseCode;
    string courseName;
    int credits;

    string prerequisites[20];
    int prereqCount;

    string faculty;
    string room;

    int capacity;
    string enrolled[200];
    int enrolledCount;

public:
    Course() {
        courseCode = "";
        courseName = "";
        credits = 0;
        prereqCount = 0;
        faculty = "";
        room = "";
        capacity = 40;
        enrolledCount = 0;
    }

    Course(string code, string name, int c, int cap = 40) {
        courseCode = code;
        courseName = name;
        credits = c;
        capacity = cap;
        prereqCount = 0;
        faculty = "";
        room = "";
        enrolledCount = 0;
    }

    string getCode() const {
        return courseCode;
    }
    string getName() const {
        return courseName;
    }
    int getCredits() const {
        return credits;
    }
    int getPrereqCount() const {
        return prereqCount;
    }
    string getPrereq(int i) const {
        return prerequisites[i];
    }
    int getCapacity() const {
        return capacity;
    }
    int getEnrolledCount() const {
        return enrolledCount;
    }

    void setFaculty(const string& f) {
        faculty = f;
    }
    void setRoom(const string& r) {
        room = r;
    }

    void addPrerequisite(const string& p) {
        if (prereqCount < 20) {
            prerequisites[prereqCount++] = p;
        }
    }

    bool enroll(const string& id) {
        if (enrolledCount >= capacity)
            return false;

        enrolled[enrolledCount++] = id;
        return true;
    }

    void display() const {
        cout << "\n--- Course Info ---\n";
        cout << "Code: " << courseCode << "\n";
        cout << "Name: " << courseName << "\n";
        cout << "Credits: " << credits << "\n";
        cout << "Faculty: " << (faculty == "" ? "N/A" : faculty) << "\n";
        cout << "Room: " << (room == "" ? "N/A" : room) << "\n";

        cout << "Prerequisites: ";
        if (prereqCount == 0) cout << "None";
        else {
            for (int i = 0; i < prereqCount; i++) {
                cout << prerequisites[i];
                if (i < prereqCount - 1) cout << ", ";
            }
        }
        cout << "\n";

        cout << "Capacity: " << enrolledCount << "/" << capacity << "\n";
    }
};

#endif

