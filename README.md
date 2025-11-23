### Discrete-University-Management-System:

“A discrete structures–based academic management engine implementing sets, relations, functions, logic inference, induction verification, scheduling, and consistency checking.”

UniDisc Engine is a high–level academic simulation framework built using Discrete Mathematics concepts and implemented in C++/Java (OOP).
It models real-life university operations such as scheduling, prerequisites, logic inference, set/relations analysis, consistency checking, and computational verification.

This project is based on the FAST University scenario and integrates mathematical rigor with modular software engineering.

### Project Overview:


Universities deal with complex rules involving prerequisites, enrollment, faculty assignment, course scheduling, and logical constraints.
UniDisc Engine provides a computational framework to:

# Validate course chains using induction

# Analyze and infer rules using propositional & predicate logic

# Handle student grouping using combinations & counting

# Analyze academic data using sets, relations, and functions

# Detect academic conflicts using consistency checking

# Benchmark performance using DP, recursion, and memoization

### Features:

# Course Scheduling

Generates valid course orders based on prerequisites
Uses recursion / DP for efficiency

# Student Group Combinations

Creates project groups, lab groups
Uses subsets, combinations, permutations

# Induction & Strong Induction

Validates multi-level prerequisite chains
Ensures indirect prerequisites are satisfied

# Logic & Inference Engine

Rule-based consistency checker
Supports propositional & predicate logic

# Set Operations

Union, intersection, difference, power set
Used for course/student/faculty analysis

# Relations Module

Reflexive, symmetric, transitive checks
Equivalence relations & partial ordering

# Functions Module

Injective, surjective, bijective checks
Supports composition & inverse mapping

# Automated Proof Generator

Step-by-step formal validation of rules
Generates mathematical-style proofs

# Consistency Checker

Finds schedule conflicts
Detects missing prerequisites

# Algorithmic Benchmarking

Recursion, memoization, DP, bitsets
Performance evaluation on large datasets

# CLI Interface

Menu-based interface to run all modules


### PROJECT STRUCTURE:

/UniDisc-Engine
│── src/
│   ├── CourseScheduling.cpp
│   ├── CombinationModule.cpp
│   ├── InductionModule.cpp
│   ├── LogicEngine.cpp
│   ├── SetOperations.cpp
│   ├── Relations.cpp
│   ├── Functions.cpp
│   ├── ProofEngine.cpp
│   ├── ConsistencyChecker.cpp
│   └── Main.cpp
│
│── include/
│   ├── CourseScheduling.h
│   ├── CombinationModule.h
│   ├── InductionModule.h
│   ├── LogicEngine.h
│   ├── SetOperations.h
│   ├── Relations.h
│   ├── Functions.h
│   ├── ProofEngine.h
│   └── ConsistencyChecker.h
│
│── tests/
│── docs/
│   └── Discrete Final Project.pdf
│── README.md

