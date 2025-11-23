#ifndef MODULE10_BENCHMARKING_H
#define MODULE10_BENCHMARKING_H

#include <iostream>
#include <string>
#include <ctime>
#include "Course.h"
#include "Student.h"
#include "Module1_Scheduling.h"
#include "Module2_Grouping.h"
#include "Module3_Induction.h"
#include "Module5_Sets.h"

using namespace std;

class Timer
{
private:
    clock_t startTime;
    clock_t endTime;

public:
    Timer()
    {
        startTime = 0;
        endTime = 0;
    }

    void start()
    {
        startTime = clock();
    }

    void stop()
    {
        endTime = clock();
    }

    double getElapsedMs()
    {
        return ((double)(endTime - startTime) / CLOCKS_PER_SEC) * 1000.0;
    }

    void printElapsed(const string &operation)
    {
        cout << operation << " took: " << getElapsedMs() << " ms\n";
    }
};

class FibonacciMemo
{
private:
    long long memo[100];
    int callCount;

public:
    FibonacciMemo()
    {
        for (int i = 0; i < 100; i++)
            memo[i] = -1;
        callCount = 0;
    }

    long long fibRecursive(int n)
    {
        callCount++;
        if (n <= 1)
            return n;
        return fibRecursive(n - 1) + fibRecursive(n - 2);
    }

    long long fibMemo(int n)
    {
        callCount++;
        if (n <= 1)
            return n;
        if (memo[n] != -1)
            return memo[n];

        memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
        return memo[n];
    }

    long long fibIterative(int n)
    {
        if (n <= 1)
            return n;

        long long prev = 0, curr = 1;
        for (int i = 2; i <= n; i++)
        {
            long long temp = prev + curr;
            prev = curr;
            curr = temp;
        }
        return curr;
    }

    void resetCallCount() { callCount = 0; }
    int getCallCount() { return callCount; }
};

class BitSetOperations
{
public:
    static unsigned int setBit(unsigned int set, int pos)
    {
        return set | (1u << pos);
    }

    static bool checkBit(unsigned int set, int pos)
    {
        return (set & (1u << pos)) != 0;
    }

    static unsigned int unionSets(unsigned int a, unsigned int b)
    {
        return a | b;
    }

    static unsigned int intersectSets(unsigned int a, unsigned int b)
    {
        return a & b;
    }

    static unsigned int differenceSets(unsigned int a, unsigned int b)
    {
        return a & (~b);
    }

    static int countElements(unsigned int set)
    {
        int count = 0;
        while (set)
        {
            count += (set & 1);
            set >>= 1;
        }
        return count;
    }

    static void printBitSet(unsigned int set, int maxBits = 8)
    {
        cout << "{ ";
        bool first = true;
        for (int i = 0; i < maxBits; i++)
        {
            if (checkBit(set, i))
            {
                if (!first)
                    cout << ", ";
                cout << i;
                first = false;
            }
        }
        cout << " }";
    }
};

class BenchmarkModule
{
private:
    Timer timer;

    void generateLargeCourseSet(Course courses[], int &count, int size)
    {
        count = size;
        for (int i = 0; i < size; i++)
        {
            string code = "CS" + to_string(100 + i);
            string name = "Course " + to_string(i);
            courses[i] = Course(code, name, 3);

            if (i > 0)
            {
                courses[i].addPrerequisite("CS" + to_string(100 + i - 1));
            }
            if (i > 2)
            {
                courses[i].addPrerequisite("CS" + to_string(100 + i - 3));
            }
        }
    }

    void generateLargeStudentSet(Student students[], int &count, int size)
    {
        count = size;
        for (int i = 0; i < size; i++)
        {
            string id = "S" + to_string(1000 + i);
            string name = "Student" + to_string(i);
            students[i] = Student(id, name);

            for (int j = 0; j < (i % 5); j++)
            {
                students[i].addCompleted("CS" + to_string(100 + j));
            }
        }
    }

public:
    void benchmarkSetOperations()
    {
        cout << "\n=== BENCHMARK: Set Operations ===\n";

        string setA[50], setB[50], result[100];
        int sizeA = 30, sizeB = 25;

        for (int i = 0; i < sizeA; i++)
            setA[i] = "E" + to_string(i);
        for (int i = 0; i < sizeB; i++)
            setB[i] = "E" + to_string(i + 10);

        timer.start();
        for (int iter = 0; iter < 1000; iter++)
        {
            int resSize = setUnion(setA, sizeA, setB, sizeB, result);
            (void)resSize;
        }
        timer.stop();
        timer.printElapsed("Array-based Union (1000 iterations)");

        timer.start();
        for (int iter = 0; iter < 1000; iter++)
        {
            int resSize = setIntersection(setA, sizeA, setB, sizeB, result);
            (void)resSize;
        }
        timer.stop();
        timer.printElapsed("Array-based Intersection (1000 iterations)");

        unsigned int bitSetA = 0, bitSetB = 0;
        for (int i = 0; i < 15; i++)
            bitSetA = BitSetOperations::setBit(bitSetA, i);
        for (int i = 5; i < 20; i++)
            bitSetB = BitSetOperations::setBit(bitSetB, i);

        timer.start();
        for (int iter = 0; iter < 1000; iter++)
        {
            unsigned int res = BitSetOperations::unionSets(bitSetA, bitSetB);
            (void)res;
        }
        timer.stop();
        timer.printElapsed("Bit-based Union (1000 iterations)");

        cout << "Bit operations are ~100-1000x faster for small sets!\n";
    }

    void benchmarkRecursion()
    {
        cout << "\n=== BENCHMARK: Recursion vs Memoization vs Iteration ===\n";

        FibonacciMemo fib;
        int n = 30;

        cout << "\nTesting Fibonacci(" << n << "):\n";

        if (n <= 35)
        {
            timer.start();
            fib.resetCallCount();
            long long result = fib.fibRecursive(n);
            timer.stop();
            cout << "Recursive: Result = " << result << ", Calls = " << fib.getCallCount() << ", ";
            cout << "Time: " << timer.getElapsedMs() << " ms\n";
        }
        else
        {
            cout << "Skipping pure recursion (too slow for n > 35)\n";
        }

        timer.start();
        fib.resetCallCount();
        long long result2 = fib.fibMemo(n);
        timer.stop();
        cout << "Memoized:  Result = " << result2 << ", Calls = " << fib.getCallCount() << ", ";
        cout << "Time: " << timer.getElapsedMs() << " ms\n";

        timer.start();
        long long result3 = fib.fibIterative(n);
        timer.stop();
        cout << "Iterative: Result = " << result3 << ", ";
        cout << "Time: " << timer.getElapsedMs() << " ms\n";

        cout << "\nConclusion: Memoization reduces calls dramatically!\n";
    }

    void benchmarkPrerequisiteChecking()
    {
        cout << "\n=== BENCHMARK: Prerequisite Verification ===\n";

        Course courses[20];
        int courseCount;
        generateLargeCourseSet(courses, courseCount, 15);

        Student students[50];
        int studentCount;
        generateLargeStudentSet(students, studentCount, 30);

        InductionModule im;
        string proof[500];
        int proofCount;

        timer.start();
        int checksPerformed = 0;
        for (int s = 0; s < studentCount; s++)
        {
            for (int c = 0; c < courseCount; c++)
            {
                bool result = im.canTakeCourse_StrongInduction(
                    courses, courseCount, students[s], courses[c].getCode(),
                    proof, proofCount);
                (void)result;
                checksPerformed++;
            }
        }
        timer.stop();

        cout << "Checked " << checksPerformed << " student-course pairs.\n";
        timer.printElapsed("Total time");
        cout << "Average per check: " << (timer.getElapsedMs() / checksPerformed) << " ms\n";
    }

    void benchmarkCombinations()
    {
        cout << "\n=== BENCHMARK: Combination Generation ===\n";

        Student students[30];
        int studentCount;
        generateLargeStudentSet(students, studentCount, 20);

        int k = 3;

        timer.start();

        int combCount = listAllCombinations(students, studentCount, k);
        timer.stop();

        cout << "Generated C(" << studentCount << ", " << k << ") = " << combCount << " combinations.\n";
        timer.printElapsed("Time");

        long long expected = 1;
        for (int i = 0; i < k; i++)
        {
            expected *= (studentCount - i);
            expected /= (i + 1);
        }
        cout << "Expected combinations: " << expected << "\n";

        if (combCount > 0)
        {
            cout << "Average time per combination: " << (timer.getElapsedMs() / combCount) << " ms\n";
        }
    }
    /* ---------------  combination helper  --------------- */
    static void combine(Student *a, int n, int k, int start, int depth,
                        Student *out, int &cnt)
    {
        if (depth == k)
        {
            ++cnt;
            return;
        }

        for (int i = start; i <= n - k + depth; ++i)
        {
            out[depth] = a[i];
            combine(a, n, k, i + 1, depth + 1, out, cnt);
        }
    }

    /* ---------------  function that benchmark expects --------------- */
    static int listAllCombinations(Student *students, int n, int k)
    {
        if (k <= 0 || k > n)
            return 0;
        Student *buf = new Student[k];
        int counter = 0;
        combine(students, n, k, 0, 0, buf, counter);
        delete[] buf;
        return counter;
    }

    void runFullBenchmark()
    {
        cout << "\n";
        cout << "======================================================\n";
        cout << "===   MODULE 10: ALGORITHMIC EFFICIENCY BENCHMARK   ===\n";
        cout << "====================================================\n";

        benchmarkSetOperations();
        benchmarkRecursion();
        benchmarkPrerequisiteChecking();
        benchmarkCombinations();

        cout << "\n";
        cout << "====================================================\n";
        cout << "===        OPTIMIZATION RECOMMENDATIONS          ===\n";
        cout << "====================================================\n";
        cout << "1. Use bit manipulation for small sets (< 32 elements)\n";
        cout << "2. Apply memoization for recursive algorithms\n";
        cout << "3. Prefer iteration over recursion when possible\n";
        cout << "4. Cache prerequisite check results for repeated queries\n";
        cout << "5. Use dynamic programming for scheduling problems\n";
        cout << "\n";
    }

    void demoBitSetOperations()
    {
        cout << "\n=== BIT MANIPULATION DEMO ===\n";
        cout << "Using bits to represent sets efficiently:\n\n";

        unsigned int setA = 0;
        setA = BitSetOperations::setBit(setA, 1);
        setA = BitSetOperations::setBit(setA, 3);
        setA = BitSetOperations::setBit(setA, 5);

        unsigned int setB = 0;
        setB = BitSetOperations::setBit(setB, 3);
        setB = BitSetOperations::setBit(setB, 4);
        setB = BitSetOperations::setBit(setB, 5);

        cout << "Set A: ";
        BitSetOperations::printBitSet(setA);
        cout << "\n";
        cout << "Set B: ";
        BitSetOperations::printBitSet(setB);
        cout << "\n";

        unsigned int unionSet = BitSetOperations::unionSets(setA, setB);
        cout << "A U B: ";
        BitSetOperations::printBitSet(unionSet);
        cout << "\n";

        unsigned int interSet = BitSetOperations::intersectSets(setA, setB);
        cout << "A ∩ B: ";
        BitSetOperations::printBitSet(interSet);
        cout << "\n";

        unsigned int diffSet = BitSetOperations::differenceSets(setA, setB);
        cout << "A - B: ";
        BitSetOperations::printBitSet(diffSet);
        cout << "\n";

        cout << "\nBit operations: O(1) time, minimal memory!\n";
    }
};

#endif
