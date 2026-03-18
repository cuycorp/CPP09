#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av) : _sorted_vec(false), _sorted_deq(false) {
    parseArgs(av);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseArgs(char **av) {
    _vec.clear();
    _deq.clear();
    for (int i = 1; av[i]; ++i) {
        std::stringstream ss(av[i]);
        int num;
        ss >> num;
        if (ss.fail() || !ss.eof() || num <= 0) {
            throw std::runtime_error("Error");
        }
        // Check duplicates discretionary - skip for now, allow
        _vec.push_back(num);
        _deq.push_back(num);
    }
    if (_vec.empty()) {
        throw std::runtime_error("Error");
    }
}

double PmergeMe::getTime() const {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

void PmergeMe::printBefore() const {
    std::cout << "Before: ";
    size_t i = 0;
    for (; i < 10 && i < _vec.size(); ++i) {
        std::cout << _vec[i];
        if (i + 1 < _vec.size()) std::cout << " ";
    }
    if (_vec.size() > 10) std::cout << " [...]" << std::endl;
    else std::cout << std::endl;
}

void PmergeMe::printAfter() const {
    std::cout << "After: ";
    size_t i = 0;
    for (; i < 10 && i < _vec.size(); ++i) {
        std::cout << _vec[i];
        if (i + 1 < _vec.size()) std::cout << " ";
    }
    if (_vec.size() > 10) std::cout << " [...]" << std::endl;
    else std::cout << std::endl;
}

void mergeInsertSortVector(std::vector<int>& arr);

void PmergeMe::fordJohnsonVector() {
    if (_sorted_vec) return;
    mergeInsertSortVector(_vec);
    _sorted_vec = true;
}

void mergeInsertSortVector(std::vector<int>& arr) {
    if (arr.size() < 2) return;
    std::vector<int> smalls;
    std::vector<int> larges;
    size_t n = arr.size();
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            if (arr[i] < arr[i + 1]) {
                smalls.push_back(arr[i]);
                larges.push_back(arr[i + 1]);
            } else {
                smalls.push_back(arr[i + 1]);
                larges.push_back(arr[i]);
            }
        } else {
            smalls.push_back(arr[i]);
        }
    }
    mergeInsertSortVector(smalls);
    arr = smalls;
    for (std::vector<int>::size_type j = 0; j < larges.size(); ++j) {
        int large = larges[j];
        std::vector<int>::iterator it = std::lower_bound(arr.begin(), arr.end(), large);
        arr.insert(it, large);
    }
}

void mergeInsertSortDeque(std::deque<int>& arr);

void PmergeMe::fordJohnsonDeque() {
    if (_sorted_deq) return;
    mergeInsertSortDeque(_deq);
    _sorted_deq = true;
}

void mergeInsertSortDeque(std::deque<int>& arr) {
    if (arr.size() < 2) return;
    std::deque<int> smalls;
    std::deque<int> larges;
    size_t n = arr.size();
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            if (arr[i] < arr[i + 1]) {
                smalls.push_back(arr[i]);
                larges.push_back(arr[i + 1]);
            } else {
                smalls.push_back(arr[i + 1]);
                larges.push_back(arr[i]);
            }
        } else {
            smalls.push_back(arr[i]);
        }
    }
    mergeInsertSortDeque(smalls);
    arr = smalls;
    for (std::deque<int>::size_type j = 0; j < larges.size(); ++j) {
        int large = larges[j];
        std::deque<int>::iterator it = std::lower_bound(arr.begin(), arr.end(), large);
        arr.insert(it, large);
    }
}

void PmergeMe::sortAndPrintVector() {
    if (_sorted_vec) return;
    double start = getTime();
    fordJohnsonVector();
    double end = getTime();
    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : "
              << std::fixed << std::setprecision(5) << (end - start) << " us" << std::endl;
}

void PmergeMe::sortAndPrintDeque() {
    if (_sorted_deq) return;
    double start = getTime();
    fordJohnsonDeque();
    double end = getTime();
    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : "
              << std::fixed << std::setprecision(5) << (end - start) << " us" << std::endl;
}

