#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        BitcoinExchange convert(av[1]);
        convert.openDataBase();
        convert.repondQueries();
    }
    else 
        std::cout << "Error" << std::endl;
}