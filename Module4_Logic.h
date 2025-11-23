#ifndef MODULE4_LOGIC_H
#define MODULE4_LOGIC_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_RULES = 100;
const int MAX_PREMISES = 10;
const int MAX_FACTS = 200;
const int MAX_LOG = 500;


class LogicRule {
public:
    string id;
    string premises[MAX_PREMISES];
    int premiseCount;
    string conclusion;
    string description;

    LogicRule() {
        id = "";
        conclusion = "";
        description = "";
        premiseCount = 0;
    }

    void set(const string& ruleID,
             const string pList[],
             int pCount,
             const string& concl,
             const string& desc = "")
    {
        id = ruleID;
        premiseCount = pCount;
        for (int i = 0; i < pCount; i++)
            premises[i] = pList[i];

        conclusion = concl;
        description = desc;
    }
};


class LogicEngine {
private:
    LogicRule rules[MAX_RULES];
    int ruleCount;

    string factNames[MAX_FACTS];
    bool factValues[MAX_FACTS];
    int factCount;

    string inferenceLog[MAX_LOG];
    int logCount;

    int findFactIndex(const string& name) {
        for (int i = 0; i < factCount; i++)
            if (factNames[i] == name)
                return i;
        return -1;
    }

    bool evaluatePremises(const LogicRule& r) {
        for (int i = 0; i < r.premiseCount; i++) {
            string prem = r.premises[i];

            if (prem[0] == '!') {
                string prop = prem.substr(1);
                int idx = findFactIndex(prop);
                if (idx == -1 || factValues[idx] == true)
                    return false;
            }
            else {
                int idx = findFactIndex(prem);
                if (idx == -1 || factValues[idx] == false)
                    return false;
            }
        }
        return true;
    }

    void addLog(const string& msg) {
        if (logCount < MAX_LOG)
            inferenceLog[logCount++] = msg;
    }

public:

    LogicEngine() {
        ruleCount = 0;
        factCount = 0;
        logCount = 0;
    }

   
    void addRule(const string& id, const string premises[],
                 int premCount, const string& conclusion,
                 const string& description = "")
    {
        if (ruleCount >= MAX_RULES) return;

        rules[ruleCount].set(id, premises, premCount, conclusion, description);
        ruleCount++;
    }

    void setFact(const string& name, bool value) {
        int idx = findFactIndex(name);
        if (idx == -1) {
            idx = factCount++;
            factNames[idx] = name;
        }
        factValues[idx] = value;
    }

    bool getFact(const string& name) {
        int idx = findFactIndex(name);
        return (idx != -1 && factValues[idx]);
    }

    int forwardChaining() {
        logCount = 0;
        addLog("=== Forward Chaining Started ===");

        int newFacts = 0;
        bool changed = true;

        while (changed) {
            changed = false;

            for (int r = 0; r < ruleCount; r++) {
                int conclIdx = findFactIndex(rules[r].conclusion);

                
                if (conclIdx != -1 && factValues[conclIdx] == true)
                    continue;


                if (evaluatePremises(rules[r])) {
                    setFact(rules[r].conclusion, true);
                    newFacts++;

                    string msg = "Applied Rule " + rules[r].id + ": ";

                    for (int i = 0; i < rules[r].premiseCount; i++) {
                        msg += rules[r].premises[i];
                        if (i < rules[r].premiseCount - 1) msg += " ∧ ";
                    }
                    msg += " → " + rules[r].conclusion;

                    addLog(msg);

                    changed = true;
                }
            }
        }

        addLog("Forward Chaining Finished. New facts = " + to_string(newFacts));
        return newFacts;
    }


    void displayRules() {
        cout << "\n=== Rules ===\n";
        for (int r = 0; r < ruleCount; r++) {
            cout << rules[r].id << ": ";
            for (int i = 0; i < rules[r].premiseCount; i++) {
                cout << rules[r].premises[i];
                if (i < rules[r].premiseCount - 1) cout << " ∧ ";
            }
            cout << " → " << rules[r].conclusion;
            if (rules[r].description != "") cout << " (" << rules[r].description << ")";
            cout << "\n";
        }
    }


    void displayFacts() {
        cout << "\n=== Facts ===\n";
        for (int i = 0; i < factCount; i++)
            cout << factNames[i] << " = " << (factValues[i] ? "TRUE" : "FALSE") << "\n";
    }


    void displayInferenceLog() {
        cout << "\n=== Inference Log ===\n";
        for (int i = 0; i < logCount; i++)
            cout << inferenceLog[i] << "\n";
    }


    bool hasContradiction() {
        for (int i = 0; i < factCount; i++) {
            string neg = "!" + factNames[i];
            int j = findFactIndex(neg);
            if (j != -1 && factValues[j] == true && factValues[i] == true)
                return true;
        }
        return false;
    }

    void addFASTUniversityRules() {
        string p1[1] = {"prof_x_teaches_cs101"};
        addRule("R1", p1, 1, "lab_must_be_labA", "Faculty-lab assignment");

        string p2[1] = {"takes_data_structures"};
        addRule("R2", p2, 1, "must_complete_programming", "Prerequisite rule");

        string p3[1] = {"room_capacity_exceeded"};
        addRule("R3", p3, 1, "enrollment_conflict", "Capacity violation");

        string p4[2] = {"has_prerequisites", "!completed_prerequisites"};
        addRule("R4", p4, 2, "enrollment_blocked", "Prerequisite incomplete");
    }
};

#endif


