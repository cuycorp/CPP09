#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>

class RPN
{
public:
    explicit RPN(const std::string &expr);
    RPN(const RPN& other);
    RPN &operator=(const RPN &other);
    ~RPN();

    /* Evaluate the stored postfix expression and return the result.  Throws
       std::runtime_error on any error: malformed expression, invalid token,
       division by zero, etc.  Only a std::stack<int> is used internally. */
    int evaluate() const;

private:
    std::string _expr;

    bool isNumber(const std::string &tok) const;
    bool isOperator(const std::string &tok) const;
    int applyOperator(int lhs, int rhs, const std::string &op) const;
};

#endif