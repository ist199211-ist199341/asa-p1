#include <iostream>
#include <vector>

void fill_vector_until_newline(std::vector<std::int64_t> *sequence);
void solve_p1(std::vector<std::int64_t> *sequence, std::int64_t *result);
int64_t solve_p2(std::vector<std::int64_t> *sequence1,
                 std::vector<std::int64_t> *sequence2);

int main()
{
    int num_problem;
    std::vector<std::int64_t> sequence1, sequence2;

    std::cin >> num_problem;

    fill_vector_until_newline(&sequence1);
    if (num_problem == 1)
    {
        std::int64_t result[2];
        solve_p1(&sequence1, result);
        std::cout << result[0] << " " << result[1] << std::endl;
    }
    else if (num_problem == 2)
    {
        fill_vector_until_newline(&sequence2);

        std::int64_t result = solve_p2(&sequence1, &sequence2);
        std::cout << result << std::endl;
    }

    return 0;
}

void fill_vector_until_newline(std::vector<std::int64_t> *sequence)
{
    std::int64_t c = 0;
    while (c != '\n' && c != EOF)
    {
        std::cin >> c;
        sequence->push_back(c);
        c = getchar();
    }
}

void solve_p1(std::vector<std::int64_t> *sequence, std::int64_t *result)
{
    size_t input_len = sequence->size();
    std::int64_t global_max_length = 0;
    std::vector<std::int64_t> max_until(input_len, 0);
    std::vector<std::int64_t> count_until(input_len, 0);

    for (size_t i = 0; i < input_len; ++i)
    {
        std::int64_t max = 0;
        std::int64_t count = 0;
        for (size_t j = 0; j < i; ++j)
        {
            if (sequence->at(j) < sequence->at(i) && max_until.at(j) > max)
            {
                max = max_until[j];
            }
        }

        for (size_t j = 0; j < i; ++j)
        {
            if (sequence->at(j) < sequence->at(i) && max_until.at(j) == max)
            {
                count += count_until[j];
            }
        }

        ++max;

        max_until.at(i) = max;
        count_until.at(i) = count <= 0 ? 1 : count;

        if (max > global_max_length)
        {
            global_max_length = max;
        }
    }

    std::int64_t max_count = 0;
    size_t count_until_len = count_until.size();
    for (size_t i = 0; i < count_until_len; ++i)
    {
        if (max_until.at(i) == global_max_length)
        {
            max_count += count_until.at(i);
        }
    }

    result[0] = global_max_length;
    result[1] = max_count;
}

std::int64_t solve_p2(std::vector<std::int64_t> *sequence1,
                      std::vector<std::int64_t> *sequence2)
{
    // TODO
    return 69420;
}
