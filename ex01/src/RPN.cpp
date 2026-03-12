#include "RPN.hpp"

#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <cstdlib>

/*
   RPN.cpp
   -------
   Implements evaluation of a reverse-Polish (postfix) expression.  The only
   STL container used is a stack, which holds integer operands as tokens are
   consumed directly from the input string.  Errors (malformed expression,
   invalid token, division by zero, etc.) are signaled by throwing
   std::runtime_error.
*/

// Constructors / destructor

RPN::RPN(const std::string &expr): _expr(expr) {}

RPN::RPN(const RPN& other): _expr(other._expr) {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _expr = other._expr;
    return *this;
}

RPN::~RPN() {}

// Helpers

bool RPN::isNumber(const std::string &tok) const
{
    if (tok.empty())
        return false;
    for (size_t i = 0; i < tok.length(); i++) {
        char c = tok[i];
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

bool RPN::isOperator(const std::string &tok) const
{
    return tok == "+" || tok == "-" || tok == "*" || tok == "/";
}

int RPN::applyOperator(int lhs, int rhs, const std::string &op) const
{
    if (op == "+")
        return lhs + rhs;
    if (op == "-")
        return lhs - rhs;
    if (op == "*")
        return lhs * rhs;
    if (op == "/") {
        if (rhs == 0)
            throw std::runtime_error("division by zero");
        return lhs / rhs;
    }
    throw std::runtime_error("unknown operator");
}


int RPN::evaluate() const
{
    std::istringstream iss(_expr);
    std::string tok;
    std::stack<int> operandStack;

    while (iss >> tok) {
        if (isNumber(tok)) {
            operandStack.push(std::atoi(tok.c_str()));
        } else if (isOperator(tok)) {
            if (operandStack.size() < 2)
                throw std::runtime_error("not enough operands");
            int rhs = operandStack.top(); operandStack.pop();
            int lhs = operandStack.top(); operandStack.pop();
            int res = applyOperator(lhs, rhs, tok);
            operandStack.push(res);
        } else {
            throw std::runtime_error("invalid token");
        }
    }
    if (operandStack.size() != 1)
        throw std::runtime_error("malformed expression");
    return operandStack.top();
}
