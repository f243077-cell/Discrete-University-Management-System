#include <iostream>
#include <string>

#include "Course.h"
#include "Student.h"
#include "Module1_Scheduling.h"
#include "Module2_Grouping.h"
#include "Module3_Induction.h"
#include "Module4_Logic.h"
#include "Module5_Sets.h"
#include "Module6_Relations.h"
#include "Module7_Functions.h"
#include "Module8_Proofs.h"
#include "Module9_Consistency.h"
#include "Module10_Benchmarking.h"
#include "Module12_Testing.h"

using namespace std;

void buildSampleCourses(Course courses[], int &courseCount)
{
    courseCount = 5;
    courses[0] = Course("CS101", "Intro to Programming", 3);
    courses[1] = Course("CS102", "Into to SE", 3);
    courses[2] = Course("CS201", "Data Structures", 3);
    courses[3] = Course("CS301", "Advanced CS", 3);
    courses[4] = Course("MATH101", "Discrete Math", 3);

    courses[1].addPrerequisite("CS101");
    courses[2].addPrerequisite("CS102");
    courses[3].addPrerequisite("CS201");
    courses[3].addPrerequisite("MATH101");
}

void buildSampleStudents(Student students[], int &studentCount)
{
    studentCount = 6;
    students[0] = Student("S001", "Faizan");
    students[1] = Student("S002", "Usman");
    students[2] = Student("S003", "Tanzeel");
    students[3] = Student("S004", "Aisha");
    students[4] = Student("S005", "Hassan jugnu");
    students[5] = Student("S006", "Sara");

    students[0].addCompleted("CS101");
    students[0].addCompleted("CS102");

    students[1].addCompleted("CS101");
    students[1].addCompleted("MATH101");

    students[2].addCompleted("CS101");
    students[2].addCompleted("CS102");
    students[2].addCompleted("CS201");
}

void demoScheduling()
{
    cout << "\n--- Scheduling Demo ---\n";
    Course courses[50];
    int courseCount;
    buildSampleCourses(courses, courseCount);

    SchedulingModule sched;
    for (int i = 0; i < courseCount; i++)
        sched.addCourse(courses[i]);

    sched.generateAllSchedules();
}

void demoGrouping()
{
    cout << "\n--- Grouping Demo ---\n";
    Student students[20];
    int scount;
    buildSampleStudents(students, scount);

    int groups[10][MAX_GROUP_SIZE];
    int formed = createGroupsGreedy(students, scount, 3, groups);
    cout << "Greedy groups (size 3):\n";
    printGroups(students, groups, formed, 3);

    int combCount = listAllCombinations(students, scount, 2);
    cout << "\nAll 2-person combinations (showing first 10):\n";
    printCombinationResults(students, combCount < 10 ? combCount : 10, 2);
}

void demoInduction()
{
    cout << "\n--- Induction Demo ---\n";
    Course courses[50];
    int courseCount;
    buildSampleCourses(courses, courseCount);

    Student students[10];
    int scount;
    buildSampleStudents(students, scount);

    InductionModule im;
    string proof[500];
    int proofCount = 0;

    cout << "\nCheck if Omar (S003) can take CS301 using STRONG INDUCTION:\n";
    bool ok = im.canTakeCourse_StrongInduction(courses, courseCount, students[2], "CS301", proof, proofCount);
    for (int i = 0; i < proofCount; i++)
        cout << proof[i] << "\n";
    cout << "Final: " << (ok ? "Eligible" : "Not eligible") << "\n";
}

void demoLogicEngine()
{
    cout << "\n--- Logic Engine Demo ---\n";
    LogicEngine engine;
    engine.addFASTUniversityRules();

    engine.setFact("prof_x_teaches_cs101", true);
    engine.setFact("takes_data_structures", true);
    engine.setFact("room_capacity_exceeded", false);
    engine.setFact("completed_prerequisites", false);
    engine.setFact("has_prerequisites", true);

    int newFacts = engine.forwardChaining();
    cout << "Derived " << newFacts << " new facts.\n";
    engine.displayFacts();
    engine.displayInferenceLog();
    cout << "Contradiction? " << (engine.hasContradiction() ? "YES" : "NO") << "\n";
}

void demoSets()
{
    cout << "\n--- Sets Demo ---\n";
    string A[] = {"CS101", "CS102", "CS201"};
    string B[] = {"CS102", "MATH101"};
    string C[] = {"MATH101", "PHYS101"};

    string res[MAX_SET];

    int unionSize = setUnion(A, 3, B, 2, res);
    cout << "A ∪ B = ";
    printSet(res, unionSize);
    cout << "\n";

    int interSize = setIntersection(A, 3, B, 2, res);
    cout << "A ∩ B = ";
    printSet(res, interSize);
    cout << "\n";

    int diffSize = setDifference(A, 3, B, 2, res);
    cout << "A - B = ";
    printSet(res, diffSize);
    cout << "\n";

    cout << "\nPower set of {CS101, CS102}:\n";
    string small[] = {"CS101", "CS102"};
    printPowerSet(small, 2);

    cout << "\nCartesian product A × B:\n";
    cartesianProduct(A, 3, B, 2);
}

void demoRelations()
{
    cout << "\n--- Relations Demo ---\n";
    RelationModule rm;
    rm.addElement("a");
    rm.addElement("b");
    rm.addElement("c");

    rm.addPair("a", "a");
    rm.addPair("b", "b");
    rm.addPair("c", "c");
    rm.addPair("a", "b");

    rm.printRelation();
    rm.printMatrix();
    cout << "Reflexive: " << (rm.isReflexive() ? "YES" : "NO") << "\n";
    cout << "Symmetric: " << (rm.isSymmetric() ? "YES" : "NO") << "\n";
    cout << "Transitive: " << (rm.isTransitive() ? "YES" : "NO") << "\n";
    cout << "Equivalence: " << (rm.isEquivalence() ? "YES" : "NO") << "\n";
    cout << "Partial Order: " << (rm.isPartialOrder() ? "YES" : "NO") << "\n";
}

void demoFunctions()
{
    cout << "\n--- Functions Demo ---\n";
    FunctionModule f;
    // Domain {1,2,3}
    f.addDomainElement("1");
    f.addDomainElement("2");
    f.addDomainElement("3");
    // Codomain {A,B,C}
    f.addCodomainElement("A");
    f.addCodomainElement("B");
    f.addCodomainElement("C");
    // Mapping: 1->A, 2->B, 3->C
    f.addMapping("1", "A");
    f.addMapping("2", "B");
    f.addMapping("3", "C");

    f.printFunction();
    cout << "Valid function? " << (f.isValidFunction() ? "YES" : "NO") << "\n";
    cout << "Injective? " << (f.isInjective() ? "YES" : "NO") << "\n";
    cout << "Surjective? " << (f.isSurjective() ? "YES" : "NO") << "\n";
    cout << "Bijective? " << (f.isBijective() ? "YES" : "NO") << "\n";

    FunctionModule inv;
    if (f.inverse(inv))
    {
        cout << "Inverse exists. Inverse mapping: ";
        inv.printFunction();
    }
    else
    {
        cout << "Inverse does not exist (not injective).\n";
    }
}

void demoProofs()
{
    cout << "\n--- Proofs Demo ---\n";
    Course courses[50];
    int courseCount;
    buildSampleCourses(courses, courseCount);

    Student students[20];
    int scount;
    buildSampleStudents(students, scount);

    ProofsModule pm;
    pm.provePrerequisiteChain(courses, courseCount, students[2], "CS301");

    LogicEngine eng;
    eng.addFASTUniversityRules();
    eng.setFact("prof_x_teaches_cs101", true);
    pm.proveLogicDerivation(eng, "lab_must_be_labA");
}

void demoConsistency()
{
    cout << "\n--- Consistency Demo ---\n";
    Course courses[50];
    int courseCount;
    buildSampleCourses(courses, courseCount);

    Student students[50];
    int studentCount;
    buildSampleStudents(students, studentCount);

    LogicEngine engine;
    engine.addFASTUniversityRules();
    engine.setFact("prof_x_teaches_cs101", true);

    int sIdxs[2] = {2, 1};
    string codeList[2] = {"CS301", "CS201"};

    string logicGoals[1] = {"enrollment_conflict"};

    ConsistencyChecker cc;
    cc.runFullConsistencyCheck(courses, courseCount, students, studentCount,
                               engine, sIdxs, codeList, 2,
                               logicGoals, 1);
}

void demoBenchmarking()
{
    cout << "\n--- Benchmarking & Optimization Demo ---\n";
    BenchmarkModule bm;

    bm.runFullBenchmark();

    cout << "\n--- Additional Demo: Bit Operations ---\n";
    bm.demoBitSetOperations();
}

void demoUnitTesting()
{
    cout << "\n--- Unit Testing Demo ---\n";
    UnitTestingModule utm;
    utm.runAllTestsAndBenchmarks();
}

void printMenu()
{
    cout << "\n\n-------------------------------------------------------------\n";
    cout << "   --- FAST University Discrete Mathematics Project      ---\n";
    cout << "   ---       [UNIDISC ENGINE - Complete System]        ---\n";
    cout << "------------------------------------------------------------------\n";
    cout << "\n CORE MODULES:\n";
    cout << "  1.  Scheduling (topological / all valid orders)\n";
    cout << "  2.  Grouping (greedy + combinations)\n";
    cout << "  3.  Induction (direct vs strong)\n";
    cout << "  4.  Logic Engine (forward chaining)\n";
    cout << "  5.  Set Operations\n";
    cout << "  6.  Relations (reflexive/symmetric/transitive)\n";
    cout << "  7.  Functions (injective/surjective/bijective)\n";
    cout << "  8.  Proofs (prereq chain + logic derivation)\n";
    cout << "  9.  Consistency Checker (full report)\n";
    cout << "\n PERFORMANCE & TESTING:\n";
    cout << "  10. Algorithmic Efficiency & Benchmarking \n";
    cout << "  11. Unit Testing & Validation \n";
    cout << "\n OTHER:\n";
    cout << "  12. Run ALL Demos (comprehensive showcase)\n";
    cout << "  0.  Exit\n";
    cout << "\n-----------------------------------------------\n";
    cout << "Choose option: ";
}

void runAllDemos()
{
    cout << "\n";
    cout << "--------------------------------------------------------------\n";
    cout << "---     RUNNING COMPREHENSIVE SYSTEM DEMO    ---\n";
    cout << "--------------------------------------------------------------\n";

    demoScheduling();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

    demoGrouping();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoInduction();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoLogicEngine();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoSets();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoRelations();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoFunctions();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoProofs();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoConsistency();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoBenchmarking();
    cout << "\nPress Enter to continue...";
    cin.get();

    demoUnitTesting();

    cout << "\n";
    cout << "==============================================================\n";
    cout << "======       ALL DEMOS COMPLETED SUCCESSFULLY!           =======\n";
    cout << "===============================================================\n";
}

int main()
{
    int choice = -1;

    cout << "\n";
    cout << "==============================================================\n";
    cout << " ========               UNDISC            ========" << endl;
    cout << " =================================================   \n";
    cout << "             Discrete Mathematics Engine                   \n";
    cout << "           FAST University Project - Complete               \n";
    cout << "                                                            \n";
    cout << "==============================================================\n";
    cout << "\n  12 Modules | Full OOP | Comprehensive Testing\n";
    cout << "  Developed with Love for Discrete Mathematics\n\n";

    while (true)
    {
        printMenu();
        cin >> choice;

        if (choice == 0)
        {
            cout << "\n";
            cout << "==============================================================\n";
            cout << "                Thank You for Using                        \n";
            cout << "                    UNIDISC ENGINE                         \n";
            cout << "                                                           \n";
            cout << "         \"Mastering Discrete Structures, One Module        \n";
            cout << "                    at a Time!\"                            \n";
            cout << "==============================================================\n";
            break;
        }

        switch (choice)
        {
        case 1:
            demoScheduling();
            break;
        case 2:
            demoGrouping();
            break;
        case 3:
            demoInduction();
            break;
        case 4:
            demoLogicEngine();
            break;
        case 5:
            demoSets();
            break;
        case 6:
            demoRelations();
            break;
        case 7:
            demoFunctions();
            break;
        case 8:
            demoProofs();
            break;
        case 9:
            demoConsistency();
            break;
        case 10:
            demoBenchmarking();
            break;
        case 11:
            demoUnitTesting();
            break;
        case 12:
            runAllDemos();
            break;
        default:
            cout << "\n Invalid choice. Please enter a number between 0-12.\n";
            break;
        }

        if (choice >= 1 && choice <= 11)
        {
            cout << "\n-------------------------------------------------------\n";
            cout << "Press Enter to return to main menu...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}
