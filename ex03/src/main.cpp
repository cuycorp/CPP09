#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    try {
        PmergeMe pmerge(argv);
        pmerge.printBefore();
        pmerge.sortAndPrintVector();
        pmerge.printAfter();
        pmerge.sortAndPrintDeque();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

