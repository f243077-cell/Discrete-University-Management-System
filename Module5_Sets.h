#ifndef MODULE5_SETS_H
#define MODULE5_SETS_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_SET = 100;


int removeDuplicates(string arr[], int size) {
    string temp[MAX_SET];
    int count = 0;

    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < count; j++) {
            if (temp[j] == arr[i]) {
                found = true;
                break;
            }
        }
        if (!found) temp[count++] = arr[i];
    }

    for (int i = 0; i < count; i++) arr[i] = temp[i];
    return count;
}


void printSet(const string arr[], int size) {
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " }";
}


int setUnion(const string A[], int aSize, const string B[], int bSize, string result[]) {
    int k = 0;

    for (int i = 0; i < aSize; i++)
        result[k++] = A[i];

    for (int i = 0; i < bSize; i++)
        result[k++] = B[i];

    return removeDuplicates(result, k);
}


int setIntersection(const string A[], int aSize, const string B[], int bSize, string result[]) {
    int k = 0;

    for (int i = 0; i < aSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (A[i] == B[j]) {
                result[k++] = A[i];
                break;
            }
        }
    }

    return k;
}

int setDifference(const string A[], int aSize, const string B[], int bSize, string result[]) {
    int k = 0;

    for (int i = 0; i < aSize; i++) {
        bool found = false;
        for (int j = 0; j < bSize; j++) {
            if (A[i] == B[j]) {
                found = true;
                break;
            }
        }
        if (!found) result[k++] = A[i];
    }

    return k;
}


int setSymmetricDifference(const string A[], int aSize, const string B[], int bSize, string result[]) {
    string temp1[MAX_SET], temp2[MAX_SET];
    
    int d1 = setDifference(A, aSize, B, bSize, temp1);
    int d2 = setDifference(B, bSize, A, aSize, temp2);

    int k = 0;

    for (int i = 0; i < d1; i++)
        result[k++] = temp1[i];
    for (int i = 0; i < d2; i++)
        result[k++] = temp2[i];

    return k;
}


bool isSubset(const string A[], int aSize, const string B[], int bSize) {
    for (int i = 0; i < aSize; i++) {
        bool found = false;
        for (int j = 0; j < bSize; j++) {
            if (A[i] == B[j]) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}


bool areEqualSets(const string A[], int aSize, const string B[], int bSize) {
    if (aSize != bSize)
        return false;
    return isSubset(A, aSize, B, bSize);
}


void powerSetRec(const string A[], int n, int index, string current[], int currentSize) {
    if (index == n) {
        printSet(current, currentSize);
        cout << "\n";
        return;
    }

   
    powerSetRec(A, n, index + 1, current, currentSize);

    current[currentSize] = A[index];
    powerSetRec(A, n, index + 1, current, currentSize + 1);
}

void printPowerSet(const string A[], int n) {
    string current[MAX_SET];
    cout << "\nPower Set:\n";
    powerSetRec(A, n, 0, current, 0);
}


void cartesianProduct(const string A[], int aSize, const string B[], int bSize) {
    cout << "{ ";
    for (int i = 0; i < aSize; i++) {
        for (int j = 0; j < bSize; j++) {
            cout << "(" << A[i] << ", " << B[j] << ")";
            if (!(i == aSize - 1 && j == bSize - 1))
                cout << ", ";
        }
    }
    cout << " }\n";
}

#endif

