#ifndef MODULE1_SCHEDULING_H
#define MODULE1_SCHEDULING_H

#include "Course.h"
#include <iostream>
using namespace std;

class SchedulingModule {
private:
    Course courses[50];
    int courseCount;

    string order[50];
    bool used[50];

public:
    SchedulingModule() {
        courseCount = 0;
        for (int i = 0; i < 50; i++)
            used[i] = false;
    }

    void addCourse(const Course& c) {
        if (courseCount < 50)
            courses[courseCount++] = c;
    }

    bool canTakeNow(int idx) {
        for (int i = 0; i < courses[idx].getPrereqCount(); i++) {
            string pre = courses[idx].getPrereq(i);

            bool found = false;
            for (int j = 0; j < courseCount; j++) {
                if (courses[j].getCode() == pre) {
                    if (!used[j])
                        return false;
                    found = true;
                }
            }
            if (!found)
                return false;
        }
        return true;
    }

    void generateSchedules(int depth) {
        if (depth == courseCount) {
            cout << "\nValid Schedule: ";
            for (int i = 0; i < courseCount; i++)
                cout << order[i] << " ";
            cout << "\n";
            return;
        }

        for (int i = 0; i < courseCount; i++) {
            if (!used[i] && canTakeNow(i)) {
                used[i] = true;
                order[depth] = courses[i].getCode();
                generateSchedules(depth + 1);
                used[i] = false;
            }
        }
    }

    void generateAllSchedules() {
        cout << "\n=== GENERATING ALL VALID COURSE SCHEDULES ===\n";
        generateSchedules(0);
    }
};

#endif

