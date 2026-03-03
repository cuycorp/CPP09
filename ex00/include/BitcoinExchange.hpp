#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map> 
#include <string>

class BitcoinExchange
{
    public:
        //attributes
        std::string _fileName;
        std::map<std::string, double> _queries;
        std::map<std::string, double> _database;
        //OCF
        BitcoinExchange(std::string fileName);
        //BitcoinExchange(const BitcoinExchange& other);
        //BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        //main methods
        //void parseQueries();
        void openQueries(void);
        void openDataBase(void);
        void searchDate(std::string date);
    private:
        bool validateDate(const std::string &date);
        double getRate(const std::string &date);
};

#endif

