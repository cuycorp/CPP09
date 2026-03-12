#!/bin/sh

# script to run RPN with various test cases

BIN="./RPN"

# colors
BLUE="\033[1;34m"
RESET="\033[0m"

run() {
    printf "\n${BLUE}=== %s ===${RESET}\n" "$1"
    shift
    $BIN "$@"
}


# Subject tests cases
run "Subject Case 1" "8 9 * 9 - 9 - 9 - 4 - 1 +"
run "Subject Case 2" "7 7 * 7 -"
run "Subject Case 3" "1 2 * 2 / 2 * 2 4 - +"
run "Subject Case 4" "(1 + 1)"

# Important edge cases
run "Empty input" ""
run "Single number" "5"
run "Operator first" "+ 2 3"
run "Too many numbers" "1 2 3 +"
run "Division by zero" "3 0 /"
run "Multiple spaces" "2   3    +"
run "Invalid character" "2 3 &"
run "Edge Case - Invalid token" "2 a +"
