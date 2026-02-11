#include "BitcoinExchange.hpp"
/* file(), is_open()*/
#include <fstream>

// Default constructor
BitcoinExchange::BitcoinExchange(std::string fileName): _fileName(fileName)
{
}

// Copy constructor
//BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
//{
//    std::cout << "Copy constructor called" << std::endl;
//    (void) other;
//    return ;
//}
//
//// Assignment operator overload
//BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
//{
//    std::cout << "Assignment operator called" << std::endl;
//    (void) other;
//    return (*this);
//}

// Destructor
BitcoinExchange::~BitcoinExchange(void) {}

/***********************Other methods ***************************/
void BitcoinExchange::openQueries(void)
{
    std::ifstream file(_fileName.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error opening file");
    if (file.peek() == std::ifstream::traits_type::eof())
        throw std::runtime_error("Empty file");
}
void openDataBase(){
    std::ifstream file("../data.csv");
    if (!file.is_open())
        throw std::runtime_error("Error opening file");
    if (file.peek() == std::ifstream::traits_type::eof())
        throw std::runtime_error("Empty file");
}
//void searchDate(){}
