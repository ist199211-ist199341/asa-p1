#include <iostream>
#include <vector>
#include <limits>

void fill_vector_until_newline(std::vector<std::int64_t> *sequence);
void solve_p1(std::vector<std::int64_t> *sequence, std::int64_t *result);
void solve_p1_aux(std::vector<std::int64_t> *sequence, std::int64_t *result, int index, int len, int curr_num);

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
    int seq_len = sequence->size();
    result[0] = sequence->at(0);
    int curr_num = std::numeric_limits<int>::min();

    for (int index = 0; index < seq_len; index++)
    {
        solve_p1_aux(sequence, result, index, 0, curr_num);
    }
}

void solve_p1_aux(std::vector<std::int64_t> *sequence, std::int64_t *result, int index, int len, int curr_num)
{
    if (index + 1 == (int)sequence->size())
    {
        std::cout << len << std::endl;
        return;
    }

    if (sequence->at(index + 1) > curr_num)
    {
        // accepts the next number
        solve_p1_aux(sequence, result, index + 1, len + 1, sequence->at(index + 1));
        // skips the next number
        solve_p1_aux(sequence, result, index + 1, len, curr_num);
    }
    else
    {
        if (sequence->at(index + 1) == curr_num)
        {
            solve_p1_aux(sequence, result, index + 1, len, curr_num + 1);
        }
        else
        {
            solve_p1_aux(sequence, result, index + 1, len, std::numeric_limits<int>::min());
        }
    }
}

std::int64_t solve_p2(std::vector<std::int64_t> *sequence1,
                      std::vector<std::int64_t> *sequence2)
{
    // TODO
    return 69420;
}
