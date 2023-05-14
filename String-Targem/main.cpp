#include <iostream>
#include <vector>
#include <algorithm>

#include "MyString.h"

int main()
{
    auto strings = std::vector<MyString>();

    std::cout << "String count:";
    size_t count;
    std::cin >> count;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (count-- > 0)
    {
        MyString line;
        std::cin >> line;

        strings.push_back(std::move(line));
    }

    std::cout << std::endl;

    std::sort(std::begin(strings), std::end(strings));
    std::reverse(std::begin(strings), std::end(strings));

    for (auto& item : strings)
    {
        std::cout << item << '\n';
    }
}