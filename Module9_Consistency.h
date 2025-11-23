#ifndef MODULE9_CONSISTENCY_H
#define MODULE9_CONSISTENCY_H

#include <iostream>
#include <string>
using namespace std;

#include "Course.h"
#include "Student.h"
#include "Module3_Induction.h"
#include "Module4_Logic.h"
#include "Module8_Proofs.h"

const int MAX_CHECK = 200;

class ConsistencyChecker {

public:

    int checkAllPrerequisites(const Course courses[], int courseCount,
                              const Student students[], int studentCount) {
        
        InductionModule im;
        int problems = 0;

        cout << "\n=== GLOBAL PREREQUISITE CONSISTENCY CHECK ===\n";

        for (int s = 0; s < studentCount; s++) {
            const Student& st = students[s];

            cout << "\nChecking student " << st.getID() << " (" << st.getName() << "):\n";

            for (int c = 0; c < courseCount; c++) {
                const Course& course = courses[c];
                const string& code = course.getCode();

                if (st.hasCompleted(code))
                    continue;

                string proof[300];
                int proofCount = 0;

                bool ok = im.canTakeCourse_StrongInduction(
                    courses, courseCount, st, code, proof, proofCount
                );

                if (!ok) {
                    problems++;
                    cout << " Student cannot take " << code << ":\n";
                } else {
                    cout << " Student eligible for " << code << "\n";
                }
            }
        }

        cout << "\nPrerequisite problems found: " << problems << "\n";
        return problems;
    }

    bool checkLogicConsistency(LogicEngine& engine, const string conclusions[], int n) {

        cout << "\n=== LOGIC ENGINE CONSISTENCY CHECK ===\n";

        bool allGood = true;

        for (int i = 0; i < n; i++) {
            const string& goal = conclusions[i];
            cout << "\nChecking logical conclusion: " << goal << "\n";

            engine.forwardChaining();
            bool result = engine.getFact(goal);

            cout << "Conclusion '" << goal << "': "
                 << (result ? "TRUE" : "FALSE") << "\n";

            if (result) allGood = false;
        }

        cout << "\nLogical consistency: "
             << (allGood ? "OK" : "PROBLEMS DETECTED") << "\n";

        return allGood;
    }


    bool detectContradictions(LogicEngine& engine) {
        cout << "\n=== CONTRADICTION CHECK ===\n";

        bool hasContradiction = engine.hasContradiction();

        if (hasContradiction)
            cout << " Contradiction detected in logic facts.\n";
        else
            cout << " No contradictions found.\n";

        return hasContradiction;
    }


    int checkEnrollments(const Course courses[], int courseCount,
                         const Student students[], int studentCount,
                         const int studentIdx[], const string courseCode[],
                         int count)
    {
        ProofsModule pm;
        int problems = pm.checkEnrollmentPrerequisites(
            courses, courseCount,
            students, studentCount,
            studentIdx, courseCode, count
        );
        return problems;
    }


    void runFullConsistencyCheck(const Course courses[], int courseCount,
                                 const Student students[], int studentCount,
                                 LogicEngine& engine,
                                 const int studentIdx[], const string courseCodes[],
                                 int enrollCount,
                                 const string logicConclusions[], int logicConclusionCount)
    {
        cout << "\n\n============================\n";
        cout << "  FINAL CONSISTENCY REPORT\n";
        cout << "============================\n";

        int p1 = checkAllPrerequisites(courses, courseCount, students, studentCount);
        int p2 = checkEnrollments(courses, courseCount, students, studentCount,
                                  studentIdx, courseCodes, enrollCount);

        bool logicOk = checkLogicConsistency(engine, logicConclusions, logicConclusionCount);
        bool contradictionFound = detectContradictions(engine);

        cout << "\n============================\n";
        cout << " SUMMARY\n";
        cout << "============================\n";

        cout << "Prerequisite issues:   " << p1 << "\n";
        cout << "Enrollment issues:     " << p2 << "\n";
        cout << "Logic contradictions:  " << (contradictionFound ? "YES" : "NO") << "\n";
        cout << "Logic consistency:     " << (logicOk ? "OK" : "PROBLEM") << "\n";

        cout << "============================\n";
        cout << " END OF CONSISTENCY REPORT\n";
        cout << "============================\n";
    }

};

#endif

