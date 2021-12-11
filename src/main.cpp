#include <iostream>
#include <vector>

#define max(a, b) (a > b ? a : b)

std::vector<int> f1(std::vector<int> sequence);

int main()
{
    int c = 0;
    int num_problem;
    std::vector<int> sequence1;
    std::cin >> num_problem;

    if (num_problem == 2)
    {
        while (c != '\n')
        {
            std::vector<int> sequence2;
            std::cin >> c;
            sequence2.push_back(c);
            c = getchar();
        }
    }
    else
    { // Unknown Input (kinda cursed)
        if (num_problem != 1)
            return -1;
    }

    while (c != EOF)
    {
        std::cin >> c;
        sequence1.push_back(c);
        c = getchar();
    }

    std::vector<int> result = f1(sequence1);
    std::cout << result[0] << " " << result[1] << std::endl;

    return 0;
}

std::vector<int> f1(std::vector<int> sequence)
{
    std::vector<int> result;
    result.push_back(69);
    result.push_back(420);
    return result;
}