#ifndef MODULE2_GROUPING_H
#define MODULE2_GROUPING_H


#include "Student.h"
#include <iostream>

using namespace std;

const int MAX_STUDENTS_IN_MODULE = 200;
const int MAX_GROUPS = 100;
const int MAX_GROUP_SIZE = 50;


int createGroupsGreedy(const Student students[], int n, int groupSize, int groups[][MAX_GROUP_SIZE]) {
    if (groupSize <= 0) return 0;
    int g = 0;
    int idx = 0;

    while (idx < n && g < MAX_GROUPS) {
        int j = 0;
        while (j < groupSize && idx < n) {
            groups[g][j] = idx;
            j++;
            idx++;
        }
        while (j < MAX_GROUP_SIZE) {
            groups[g][j] = -1;
            j++;
        }
        g++;
    }
    return g;
}

int combinationResults[MAX_STUDENTS_IN_MODULE][MAX_GROUP_SIZE];

void combRec(const int studentsIndices[], int n, int k, int start, int depth, int current[], int &outCount) {
    if (depth == k) {
    
        for (int i = 0; i < k; i++) {
            combinationResults[outCount][i] = current[i];
        }
        for (int i = k; i < MAX_GROUP_SIZE; i++) {
            combinationResults[outCount][i] = -1;
        }
        outCount++;
        return;
    }

    for (int i = start; i <= n - (k - depth); i++) {
        current[depth] = studentsIndices[i];
        combRec(studentsIndices, n, k, i + 1, depth + 1, current, outCount);
    }
}

int listAllCombinations(const Student students[], int n, int k) {
    if (k <= 0 || k > n)
        return 0;
    int studentsIndices[MAX_STUDENTS_IN_MODULE];
    for (int i = 0; i < n; i++) studentsIndices[i] = i;

    int current[MAX_GROUP_SIZE];
    int outCount = 0;
    combRec(studentsIndices, n, k, 0, 0, current, outCount);
    return outCount;
}

void printGroups(const Student students[], int groups[][MAX_GROUP_SIZE], int groupCount, int groupSize) {
    for (int g = 0; g < groupCount; g++) {
        cout << "Group " << (g + 1) << ": ";
        bool first = true;
        for (int j = 0; j < groupSize; j++) {
            int idx = groups[g][j];
            if (idx == -1)
                continue;
            if (!first) cout << ", ";
            cout << students[idx].getID() << "(" << students[idx].getName() << ")";
            first = false;
        }
        if (first) cout << " (empty)";
        cout << "\n";
    }
}

void printCombinationResults(const Student students[], int combCount, int k) {
    for (int r = 0; r < combCount; r++) {
        cout << "Combination " << (r + 1) << ": ";
        for (int i = 0; i < k; i++) {
            int idx = combinationResults[r][i];
            if (i > 0)
                cout << ", ";
            cout << students[idx].getID() << "(" << students[idx].getName() << ")";
        }
        cout << "\n";
    }
}

#endif 
