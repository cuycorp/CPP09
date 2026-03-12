#!/bin/sh

# script to run RPN with various test cases

BIN="./RPN"

run() {
    echo "\n$1"
    shift
    $BIN "$@"
}

# Important edge cases
run "Empty input" ""
run "Single number" "5"
run "Operator first" "+ 2 3"
run "Too many numbers" "1 2 3 +"
run "Division by zero" "3 0 /"
run "Multiple spaces" "2   3    +"
run "Invalid character" "2 3 &"

# Additional edge cases from exercise
run "Edge Case - Invalid token" "2 a +"
run "Edge Case - Parentheses" "(1 + 1)"
run "Large chained operations" "8 9 * 9 - 9 - 9 - 4 - 1 +"
