#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include <cstdlib>
#include <algorithm>

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    bool _sorted_vec;
    bool _sorted_deq;

    void parseArgs(char **av);
    double getTime() const;
    void fordJohnsonVector();
    void fordJohnsonDeque();

public:
    PmergeMe(char **av);
    ~PmergeMe();
    void printBefore() const;
    void printAfter() const;
    void sortAndPrintVector();
    void sortAndPrintDeque();
};

#endif

