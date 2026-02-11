# CPP07

* Excercices by level
    * ex00: Bitcoin Exchange
        1. Use a date of input file to search for date in the database, if not found, take next largest one.
        2. once data is found, use the accompaning exchange rate, to get the value --> storing values by pairs, date is a key.
            --> find out if there are duplicated dates
        * Class: BitcoinExchange
        attributes:
            <set> exchangeRateBase
            <set> queries
        methods
            OCF -> upload exchangeRateBase an queries
            Display result 
                grab & validate line from input (date and value)-> throw error 
                search for date in database

    * ex01: Reverse Polish Notation
        1. learn Reverse polish Notation
        2. Parsing 
            Rules
            * numbers less than 10
            * operations:" + - / *
        3. Include exceptions

        <stack>

    * ex02
        * merge insert algorithm: Ford-Johnson algorithm
        <vector >
        <deque>

////
Ongoing task: opening files
next task: storing files in map


/*
//attributes
set queries
set database
std::string fileName

//methods

void openQuery()
void openDataBase()
void searchDate()
///////////***main** 
displayConversion()
*/