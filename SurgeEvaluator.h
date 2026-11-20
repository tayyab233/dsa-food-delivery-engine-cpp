#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <stdexcept>
using namespace std;

class SurgeEvaluator {
private:
    // Operator stack (array-based)
    static const int OPS_CAP = 200;
    char opStack[OPS_CAP];
    int  top;

    // Operand stack for evaluation (linked-list style via vector is also valid)
    vector<double> valStack;

    int  precedence(char op) const;
    bool isOperator(char c) const;
    void pushOp(char c);
    char popOp();
    char peekOp() const;

public:
    SurgeEvaluator();

    string infixToPostfix(const string& infix);
    double evaluatePostfix(const string& postfix);
    double evaluateInfix(const string& infix);  // convenience
};