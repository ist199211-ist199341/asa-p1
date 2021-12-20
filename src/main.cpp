#include <iostream>
#include <vector>
#include <limits>

#define max(a, b) (a > b ? a : b)

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
    result[0] = 0;

    for (int index = 0; index < seq_len; index++)
    {
        solve_p1_aux(sequence, result, index, 1, sequence->at(index));
    }
}

void solve_p1_aux(std::vector<std::int64_t> *sequence, std::int64_t *result, int index, int len, int curr_num)
{
    // when it gets to final number
    if (index + 1 == (int)sequence->size())
    {
        if (len == result[0])
            result[1]++;

        if (len > result[0])
        {
            result[0] = len;
            result[1] = 1;
        }
        return;
    }
    // if the next number is bigger
    if (sequence->at(index + 1) > curr_num)
    {
        // accepts the next number
        solve_p1_aux(sequence, result, index + 1, len + 1, sequence->at(index + 1));
    }
    else
    {
        // start new
        solve_p1_aux(sequence, result, index + 1, 1, sequence->at(index + 1));
    }
    // skip
    solve_p1_aux(sequence, result, index + 1, len, curr_num);
}

std::int64_t solve_p2(std::vector<std::int64_t> *sequence1,
                      std::vector<std::int64_t> *sequence2)
{
    std::vector<std::int64_t> common_sequence;
    int index1 = 0, index2 = 0;
}
