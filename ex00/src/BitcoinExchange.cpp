#include "BitcoinExchange.hpp"
/* file(), is_open()*/
// for parsing lines
#include <cstdlib> // for std::atof

/****************** Default constructor ******************/
BitcoinExchange::BitcoinExchange(std::string fileName): _fileName(fileName) {}

// Copy constructor
//BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
//{
//    std::cout << "Copy constructor called" << std::endl;
//    (void) other;
//    return ;
//}
//

//BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
//{
//    std::cout << "Assignment operator called" << std::endl;
//    (void) other;
//    return (*this);
//}

BitcoinExchange::~BitcoinExchange(void) {}



/****************** Public ******************/
/**
    @brief reads query lines, validates them and search for result if date is valid 
*/
void BitcoinExchange::repondQueries(void)
{
    std::ifstream file(_fileName.c_str());
    std::string line;

    openAndValidateFile(file);

    while (std::getline(file, line)) 
    {
        if (line.empty() || line == "date | value")
            continue;
        size_t sep = line.find('|');
        if (sep == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, sep);
        std::string value_str = line.substr(sep + 1);

        if (!validateDate(date)) 
        {
            std::cerr << "Error: bad date => " << date << std::endl;
            continue;
        }

        char *endptr;
        double value = std::strtod(value_str.c_str(), &endptr);
        if (*endptr != '\0') {
            std::cerr << "Error: not a valid number." << std::endl;
            continue;
        }
        if (value <= 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) {
            std::cerr << "Error: too large a number" << std::endl;
            continue;
        }

        double rate = getRate(date);
        double result = value * rate;
        std::cout << date << " => " << result  << std::endl;
    }
}


/**
    @brief opens data base and puts content in a map
*/

void BitcoinExchange::openDataBase(void)
{
    std::ifstream file("./data.csv");
    std::string line;

    openAndValidateFile(file);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::string date = line.substr(0, line.find(','));
        std::string value_str = line.substr(line.find(',') + 1);
        /* convert the numeric portion to a double; atof is safe in C++98 */
        double value = std::atof(value_str.c_str());
        _database[date] = value;
    }
}

// void BitcoinExchange::searchDate(std::string date)
// {}

/*********************** Private ***************************/
void BitcoinExchange::openAndValidateFile(std::ifstream &file)
{
    if (!file.is_open())
        throw std::runtime_error("Error opening file");
    if (file.peek() == std::ifstream::traits_type::eof())
        throw std::runtime_error("Empty file");
}


bool BitcoinExchange::validateDate(const std::string &date)
{
    // format YYYY-MM-DD
    if (date.length() != 11 || date[4] != '-' || date[7] != '-' || date[10] != ' ')
        return false;
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month-1])
        return false;
    return true;
}

double BitcoinExchange::getRate(const std::string &date)
{
    if (_database.empty())
        return 0.0;
    std::map<std::string,double>::iterator it = _database.lower_bound(date);
    if (it == _database.end()) {
        --it;
        return it->second;
    }
    if (it->first != date) {
        if (it == _database.begin())
            return it->second;
        --it;
    }
    return it->second;
}

