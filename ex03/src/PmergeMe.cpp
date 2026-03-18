#include "PmergeMe.hpp"

/******************* Constructors and Destructors *******************/

PmergeMe::PmergeMe(char **av) : _sorted_vec(false), _sorted_deq(false) {
    parseArgs(av);
}

PmergeMe::~PmergeMe() {}

/******************* Parsing *******************/

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


/******************* Printing *******************/

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


/******************* Sorting *******************/
//******************* Vector

int jacobsthal_vector(int k) {
    return static_cast<int>(round((pow(2.0, k + 1) + pow(-1.0, k)) / 3.0));
}

void insert_vector(std::vector<int> &main, std::vector<int> &pend, int odd, std::vector<int> &left, std::vector<int> &vec, bool is_odd, int order);

void sort_vector(std::vector<int> &vec) {
    static int order = 1;

    int unit_size = static_cast<int>(vec.size()) / order;
    if (unit_size < 2)
        return;

    bool is_odd_unit = unit_size % 2 == 1;
    std::vector<int>::iterator start = vec.begin();
    std::vector<int>::iterator end = vec.begin() + ((order * unit_size) - (is_odd_unit ? order : 0));

    // Pairwise swap if last of pair > last of next
    for (std::vector<int>::iterator it = start; it < end; it += (order * 2)) {
        if (*(it + (order - 1)) > *(it + ((order * 2) - 1))) {
            for (int i = 0; i < order; ++i) {
                std::swap(*(it + i), *(it + i + order));
            }
        }
    }

    int old_order = order;
    order *= 2;
    sort_vector(vec);
    order = old_order;

    std::vector<int> main_chain;
    std::vector<int> pend;
    int odd = 0;
    std::vector<int> left_over;

    // Generate main and pend from last elems
    main_chain.push_back(*(start + order - 1));
    main_chain.push_back(*(start + order * 2 - 1));

    for (std::vector<int>::iterator it = start + order * 2; it < end; it += order) {
        pend.push_back(*(it + order - 1));
        it += order;
        main_chain.push_back(*(it + order - 1));
    }

    if (is_odd_unit)
        odd = *(end + order - 1);

    left_over.insert(left_over.end(), end + (order * is_odd_unit), vec.end());

    // Insert
    if (is_odd_unit || !pend.empty()) {
        insert_vector(main_chain, pend, odd, left_over, vec, is_odd_unit, order);
    }
}

void insert_vector(std::vector<int> &main, std::vector<int> &pend, int odd, std::vector<int> &left, std::vector<int> &vec, bool is_odd, int order) {
    std::vector<int>::iterator end_it;

    if (pend.size() == 1) {
        end_it = std::upper_bound(main.begin(), main.end(), pend[0]);
        main.insert(end_it, pend[0]);
    } else if (!pend.empty()) {
        size_t jc = 3;
        size_t count = 0;
        size_t idx;
        size_t decrease;

        while (!pend.empty()) {
            idx = jacobsthal_vector(jc) - jacobsthal_vector(jc - 1);
            if (idx > pend.size())
                idx = pend.size();

            decrease = 0;
            while (idx) {
                end_it = main.begin();
                if (jacobsthal_vector(static_cast<int>(jc + count)) - decrease <= main.size())
                    end_it = main.begin() + (jacobsthal_vector(static_cast<int>(jc + count)) - decrease);
                else
                    end_it = main.end();
                end_it = std::upper_bound(main.begin(), end_it, pend[idx - 1]);
                main.insert(end_it, pend[idx - 1]);
                pend.erase(pend.begin() + idx - 1);

                --idx;
                ++decrease;
                ++count;
            }
            ++jc;
        }
    }

    std::vector<int> yaslam;

    if (is_odd) {
        end_it = std::upper_bound(main.begin(), main.end(), odd);
        main.insert(end_it, odd);
    }

    // Reconstruct full vec from sorted main lasts
    for (std::vector<int>::iterator i = main.begin(); i != main.end(); ++i) {
        std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), *i);
        yaslam.insert(yaslam.end(), it - (order - 1), it + 1);
    }
    yaslam.insert(yaslam.end(), left.begin(), left.end());
    vec = yaslam;
}


void PmergeMe::fordJohnsonVector() {
    if (_sorted_vec) return;
    sort_vector(_vec);
    _sorted_vec = true;
}


//******************* Deque

int jacobsthal_deque(int k) {
    return static_cast<int>(round((pow(2.0, k + 1) + pow(-1.0, k)) / 3.0));
}

void insert_deque(std::deque<int> &main, std::deque<int> &pend, int odd, std::deque<int> &left, std::deque<int> &vec, bool is_odd, int order);

void sort_deque(std::deque<int> &vec) {
    static int order = 1;

    int unit_size = static_cast<int>(vec.size()) / order;
    if (unit_size < 2)
        return;

    bool is_odd_unit = unit_size % 2 == 1;
    std::deque<int>::iterator start = vec.begin();
    std::deque<int>::iterator end = vec.begin() + ((order * unit_size) - (is_odd_unit ? order : 0));

    // Pairwise swap if last of pair > last of next
    for (std::deque<int>::iterator it = start; it < end; it += (order * 2)) {
        if (*(it + (order - 1)) > *(it + ((order * 2) - 1))) {
            for (int i = 0; i < order; ++i) {
                std::swap(*(it + i), *(it + i + order));
            }
        }
    }

    int old_order = order;
    order *= 2;
    sort_deque(vec);
    order = old_order;

    std::deque<int> main_chain;
    std::deque<int> pend;
    int odd = 0;
    std::deque<int> left_over;

    // Generate main and pend from last elems
    main_chain.push_back(*(start + order - 1));
    main_chain.push_back(*(start + order * 2 - 1));

    for (std::deque<int>::iterator it = start + order * 2; it < end; it += order) {
        pend.push_back(*(it + order - 1));
        it += order;
        main_chain.push_back(*(it + order - 1));
    }

    if (is_odd_unit)
        odd = *(end + order - 1);

    left_over.insert(left_over.end(), end + (order * is_odd_unit), vec.end());

    // Insert
    if (is_odd_unit || !pend.empty()) {
        insert_deque(main_chain, pend, odd, left_over, vec, is_odd_unit, order);
    }
}

void insert_deque(std::deque<int> &main, std::deque<int> &pend, int odd, std::deque<int> &left, std::deque<int> &vec, bool is_odd, int order) {
    std::deque<int>::iterator end_it;

    if (pend.size() == 1) {
        end_it = std::upper_bound(main.begin(), main.end(), pend[0]);
        main.insert(end_it, pend[0]);
    } else if (!pend.empty()) {
        size_t jc = 3;
        size_t count = 0;
        size_t idx;
        size_t decrease;

        while (!pend.empty()) {
            idx = jacobsthal_deque(jc) - jacobsthal_deque(jc - 1);
            if (idx > pend.size())
                idx = pend.size();

            decrease = 0;
            while (idx) {
                end_it = main.begin();
                if (jacobsthal_deque(static_cast<int>(jc + count)) - decrease <= static_cast<size_t>(main.size()))
                    end_it = main.begin() + (jacobsthal_deque(static_cast<int>(jc + count)) - decrease);
                else
                    end_it = main.end();
                end_it = std::upper_bound(main.begin(), end_it, pend[idx - 1]);
                main.insert(end_it, pend[idx - 1]);
                pend.erase(pend.begin() + idx - 1);

                --idx;
                ++decrease;
                ++count;
            }
            ++jc;
        }
    }

    std::deque<int> yaslam;

    if (is_odd) {
        end_it = std::upper_bound(main.begin(), main.end(), odd);
        main.insert(end_it, odd);
    }

    // Reconstruct full vec from sorted main lasts
    for (std::deque<int>::iterator i = main.begin(); i != main.end(); ++i) {
        std::deque<int>::iterator it = std::find(vec.begin(), vec.end(), *i);
        yaslam.insert(yaslam.end(), it - (order - 1), it + 1);
    }
    yaslam.insert(yaslam.end(), left.begin(), left.end());
    vec = yaslam;
}

void PmergeMe::fordJohnsonDeque() {
    if (_sorted_deq) return;
    sort_deque(_deq);
    _sorted_deq = true;
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

