#include <iostream>
#include <vector>
#include <limits>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

void fill_vector_until_newline(std::vector<std::int64_t> *sequence);
void solve_p1(std::vector<std::int64_t> *sequence, std::int64_t *result);
void solve_p1_aux(std::vector<std::int64_t> *sequence, std::int64_t *result, int index, int len, int curr_num);

int64_t solve_p2(std::vector<std::int64_t> *sequence1,
                 std::vector<std::int64_t> *sequence2);

int lcs(std::vector<std::int64_t> *sequence1, std::vector<std::int64_t> *sequence2, int *common_sequence);
void remove_element_vector(std::vector<std::int64_t> *sequence, int *array, int index);

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
    int common_sequence[20];
    for (int i = 0; i < 20; i++)
        common_sequence[i] = 0;
    lcs(sequence1, sequence2, common_sequence);
    remove_element_vector(sequence1, common_sequence, 0);
    remove_element_vector(sequence2, common_sequence, 1);

    std::vector<std::int64_t> new_sequence1;
    std::vector<std::int64_t> new_sequence2;

    for (int i = 0; i < (int)sequence1->size(); i++)
    {
        if (sequence1->at(i) != -1)
            new_sequence1.push_back(sequence1->at(i));
    }
    for (int i = 0; i < (int)sequence2->size(); i++)
    {
        if (sequence2->at(i) != -1)
            new_sequence2.push_back(sequence2->at(i));
    }
    std::int64_t array1[2];
    std::int64_t array2[2];
    solve_p1(&new_sequence1, array1);
    solve_p1(&new_sequence2, array2);
    return min(array1[0], array2[0]);
}

int lcs(std::vector<std::int64_t> *sequence1, std::vector<std::int64_t> *sequence2, int *common_sequence)
{
    std::vector<std::vector<int>> lengths =
        std::vector<std::vector<int>>(
            sequence1->size() + 1,
            std::vector<int>(sequence2->size() + 1, 0));

    int lenX = sequence1->size();
    int lenY = sequence2->size();

    for (int i = 0; i <= lenX; i++)
    {
        for (int j = 0; j <= lenY; j++)
        {
            if (i == 0 || j == 0)
            {
                lengths[i][j] = 0;
            }
            else if (sequence1->at(i - 1) == sequence2->at(j - 1))
            {
                lengths[i][j] = lengths[i - 1][j - 1] + 1;
                common_sequence[sequence1->at(i - 1)]++;
                common_sequence[sequence1->at(i - 1) + 10]++;
            }
            else
            {
                lengths[i][j] = max(lengths[i - 1][j], lengths[i][j - 1]);
            }
        }
    }
    return lengths[lenX][lenY];
}

void remove_element_vector(std::vector<std::int64_t> *sequence, int *array, int index)
{
    for (int i = 0; i < sequence->size(); i++)
    {
        if (array[sequence->at(i) + index * 10])
        {
            array[sequence->at(i) + index * 10]--;
        }
        else
        {
            sequence->at(i) = -1;
        }
    }
}