#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream input("input.txt");
    std::string line;
    int sum{0};
    while (std::getline(input, line))
    {
        if(line.empty())sum++;
    }
    std::cout << sum << '\n';
    return 0;
}