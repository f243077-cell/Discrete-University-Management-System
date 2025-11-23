#ifndef MODULE7_RELATIONS_H
#define MODULE7_RELATIONS_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_REL = 50;

class RelationModule {
private:
    string elements[MAX_REL];
    int elementCount;

    int matrix[MAX_REL][MAX_REL];


public:
    RelationModule() {
        elementCount = 0;
        for (int i = 0; i < MAX_REL; i++)
            for (int j = 0; j < MAX_REL; j++)
                matrix[i][j] = 0;
    }

    
    void addElement(const string& e) {
        if (elementCount < MAX_REL)
            elements[elementCount++] = e;
    }


    void addPair(const string& a, const string& b) {
        int i = findIndex(a);
        int j = findIndex(b);
        if (i != -1 && j != -1)
            matrix[i][j] = 1;
    }

    int findIndex(const string& x) {
        for (int i = 0; i < elementCount; i++)
            if (elements[i] == x)
                return i;
        return -1;
    }


    void printRelation() {
        cout << "R = { ";
        bool first = true;

        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                if (matrix[i][j] == 1) {
                    if (!first) cout << ", ";
                    cout << "(" << elements[i] << ", " << elements[j] << ")";
                    first = false;
                }
            }
        }

        cout << " }\n";
    }


    void printMatrix() {
        cout << "\nRelation Matrix:\n  ";
        for (int i = 0; i < elementCount; i++)
            cout << elements[i] << " ";
        cout << "\n";

        for (int i = 0; i < elementCount; i++) {
            cout << elements[i] << " ";
            for (int j = 0; j < elementCount; j++)
                cout << matrix[i][j] << " ";
            cout << "\n";
        }
    }

    bool isReflexive() {
        for (int i = 0; i < elementCount; i++)
            if (matrix[i][i] == 0)
                return false;
        return true;
    }

    bool isSymmetric() {
        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                if (matrix[i][j] != matrix[j][i])
                    return false;
            }
        }
        return true;
    }

    bool isAntiSymmetric() {
        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                if (i != j && matrix[i][j] == 1 && matrix[j][i] == 1)
                    return false;
            }
        }
        return true;
    }

    bool isTransitive() {
        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                if (matrix[i][j] == 1) {
                    for (int k = 0; k < elementCount; k++) {
                        if (matrix[j][k] == 1 && matrix[i][k] == 0)
                            return false;
                    }
                }
            }
        }
        return true;
    }

    bool isEquivalence() {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    bool isPartialOrder() {
        return isReflexive() && isAntiSymmetric() && isTransitive();
    }


    void relationComposition(int result[MAX_REL][MAX_REL],
                             int A[MAX_REL][MAX_REL],
                             int B[MAX_REL][MAX_REL]) {

        for (int i = 0; i < elementCount; i++)
            for (int j = 0; j < elementCount; j++)
                result[i][j] = 0;

        for (int i = 0; i < elementCount; i++) {
            for (int j = 0; j < elementCount; j++) {
                for (int k = 0; k < elementCount; k++) {
                    if (A[i][k] == 1 && B[k][j] == 1)
                        result[i][j] = 1;
                }
            }
        }
    }
};

#endif


