#ifndef MODULE8_PROOFS_H
#define MODULE8_PROOFS_H


#include "Course.h"
#include "Student.h"
#include "Module3_Induction.h"
#include "Module4_Logic.h"
#include <iostream>
#include <string>

using namespace std;

class ProofsModule {
public:


    bool provePrerequisiteChain(const Course courses[], int courseCount,
                                const Student& student, const string& targetCourse) {
        InductionModule im;
        string proof[500];
        int proofCount = 0;

        bool result = im.canTakeCourse_StrongInduction(courses, courseCount, student, targetCourse, proof, proofCount);

        cout << "\n=== Prerequisite Chain Proof for student " << student.getID()
             << " and course " << targetCourse << " ===\n";

        for (int i = 0; i < proofCount; i++) {
            cout << proof[i] << "\n";
        }

        cout << "=> Final result: Student " << student.getID() << " is "
             << (result ? "ELIGIBLE" : "NOT ELIGIBLE") << " to take " << targetCourse << "\n";

        return result;
    }

 
    bool proveLogicDerivation(LogicEngine& engine, const string& conclusion) {
        cout << "\n=== Logic Derivation Proof for conclusion: " << conclusion << " ===\n";

        int newFacts = engine.forwardChaining();
        cout << "Forward chaining produced " << newFacts << " new facts.\n\n";

        engine.displayInferenceLog();

        bool derived = engine.getFact(conclusion);

        cout << "\nConclusion '" << conclusion << "' was "
             << (derived ? "DERIVED (TRUE)." : "NOT derived.") << "\n";

        engine.displayFacts();

        return derived;
    }

    int checkEnrollmentPrerequisites(const Course courses[], int courseCount,
                                     const Student students[], int studentCount,
                                     const int enrollStudentIdx[], const string enrollCourseCode[],
                                     int pairCount) {
        InductionModule im;
        int problems = 0;

        cout << "\n=== Enrollment Prerequisite Consistency Check ===\n";

        for (int k = 0; k < pairCount; k++) {
            int sIdx = enrollStudentIdx[k];
            if (sIdx < 0 || sIdx >= studentCount) {
                cout << "Pair " << k << ": INVALID student index " << sIdx << "\n";
                problems++;
                continue;
            }

            const Student& st = students[sIdx];
            const string& ccode = enrollCourseCode[k];

            cout << "\nChecking: Student " << st.getID() << " (" << st.getName() << ")"
                 << " enrolled in " << ccode << "\n";

            string proof[500];
            int proofCount = 0;
            bool ok = im.canTakeCourse_StrongInduction(courses, courseCount, st, ccode, proof, proofCount);

            for (int i = 0; i < proofCount; i++) {
                cout << proof[i] << "\n";
            }

            if (!ok) {
                cout << "=> PROBLEM: Student " << st.getID() << " is NOT eligible to take " << ccode << "\n";
                problems++;
            } else {
                cout << "=> OK: Student " << st.getID() << " meets prerequisites for " << ccode << "\n";
            }
        }

        cout << "\nEnrollment check completed. Problems found: " << problems << "\n";
        return problems;
    }

 
    void proveFunctionProperties(FunctionModule& f) {
        cout << "\n=== Function Property Check ===\n";
        cout << "Is valid function? " << (f.isValidFunction() ? "YES" : "NO") << "\n";
        cout << "Is injective? " << (f.isInjective() ? "YES" : "NO") << "\n";
        cout << "Is surjective? " << (f.isSurjective() ? "YES" : "NO") << "\n";
        cout << "Is bijective? " << (f.isBijective() ? "YES" : "NO") << "\n";

        if (f.isBijective()) {
            cout << "Proof sketch: Every domain element maps to a unique codomain element (injective), "
                 << "and every codomain element is covered (surjective). Therefore bijective.\n";
        } else if (f.isInjective()) {
            cout << "Proof sketch: Mapping is injective (one-to-one) but not onto.\n";
        } else if (f.isSurjective()) {
            cout << "Proof sketch: Mapping covers all codomain elements, but not one-to-one.\n";
        } else {
            cout << "Proof sketch: Mapping fails injectivity and/or surjectivity.\n";
        }
    }

    bool proveSetDistributiveLaw(const string A[], int aSize,
                                 const string B[], int bSize,
                                 const string C[], int cSize) {
       
        string temp1[MAX_SET];
        int bAndc = setIntersection(B, bSize, C, cSize, temp1);

        string left[MAX_SET];
        int leftSize = setUnion(A, aSize, temp1, bAndc, left);

        string aUb[MAX_SET];
        int aUbSize = setUnion(A, aSize, B, bSize, aUb);

        string aUc[MAX_SET];
        int aUcSize = setUnion(A, aSize, C, cSize, aUc);

        string right[MAX_SET];
        int rightSize = setIntersection(aUb, aUbSize, aUc, aUcSize, right);

  
        leftSize = removeDuplicates(left, leftSize);
        rightSize = removeDuplicates(right, rightSize);

        bool equal = areEqualSets(left, leftSize, right, rightSize);

        cout << "\nProving distributive law A U(B ∩ C) = (A U B) ∩ (A U C):\n";
        cout << "Left: "; printSet(left, leftSize); cout << "\n";
        cout << "Right: "; printSet(right, rightSize); cout << "\n";
        cout << "Result: " << (equal ? "Holds (sets equal)" : "Does NOT hold") << "\n";

        return equal;
    }
};

#endif 

