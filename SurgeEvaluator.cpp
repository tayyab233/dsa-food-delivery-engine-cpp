#include "SurgeEvaluator.h"

SurgeEvaluator::SurgeEvaluator() : top(-1) {}

int SurgeEvaluator::precedence(char op) const {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool SurgeEvaluator::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void SurgeEvaluator::pushOp(char c) {
    if (top >= OPS_CAP - 1) throw runtime_error("Operator stack overflow");
    opStack[++top] = c;
}

char SurgeEvaluator::popOp() {
    if (top < 0) throw runtime_error("Operator stack underflow");
    return opStack[top--];
}

char SurgeEvaluator::peekOp() const {
    return (top >= 0) ? opStack[top] : '\0';
}

string SurgeEvaluator::infixToPostfix(const string& infix) {
    top = -1;
    string postfix;
    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isspace((unsigned char)c)) continue;
        if (isdigit((unsigned char)c) || c == '.') {
            while (i < infix.size() &&
                   (isdigit((unsigned char)infix[i]) || infix[i] == '.')) {
                postfix += infix[i++];
            }
            postfix += ' ';
            --i;
        } else if (c == '(') {
            pushOp(c);
        } else if (c == ')') {
            while (top >= 0 && peekOp() != '(') {
                postfix += popOp(); postfix += ' ';
            }
            if (top >= 0) popOp(); // remove '('
        } else if (isOperator(c)) {
            while (top >= 0 && peekOp() != '(' &&
                   precedence(peekOp()) >= precedence(c)) {
                postfix += popOp(); postfix += ' ';
            }
            pushOp(c);
        }
    }
    while (top >= 0) { postfix += popOp(); postfix += ' '; }
    return postfix;
}

double SurgeEvaluator::evaluatePostfix(const string& postfix) {
    valStack.clear();
    size_t i = 0;
    while (i < postfix.size()) {
        char c = postfix[i];
        if (isspace((unsigned char)c)) { ++i; continue; }
        if (isdigit((unsigned char)c) || c == '.') {
            string num;
            while (i < postfix.size() &&
                   (isdigit((unsigned char)postfix[i]) || postfix[i] == '.')) {
                num += postfix[i++];
            }
            valStack.push_back(stod(num));
        } else if (isOperator(c)) {
            if (valStack.size() < 2) throw runtime_error("Invalid postfix expr");
            double b = valStack.back(); valStack.pop_back();
            double a = valStack.back(); valStack.pop_back();
            double r = 0;
            switch (c) {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/': r = (b == 0) ? 0 : a / b; break;
            }
            valStack.push_back(r);
            ++i;
        } else {
            ++i;
        }
    }
    if (valStack.size() != 1) throw runtime_error("Malformed postfix");
    return valStack.back();
}

double SurgeEvaluator::evaluateInfix(const string& infix) {
    return evaluatePostfix(infixToPostfix(infix));
}