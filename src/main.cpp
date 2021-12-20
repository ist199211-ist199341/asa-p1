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
    // TODO
    result[0] = 69;
    result[1] = 420;
}

std::int64_t solve_p2(std::vector<std::int64_t> *sequence1,
                      std::vector<std::int64_t> *sequence2)
{
    size_t len1 = sequence1->size();
    size_t len2 = sequence2->size();
    std::vector<std::vector<std::int64_t>> lcs_matrix(len1 + 1, std::vector<std::int64_t>(len2 + 1));

    std::vector<size_t> equal_seq_i;
    std::vector<size_t> equal_seq_j;

    for (size_t i = 0; i < len1; ++i)
    {
        for (size_t j = 0; j < len2; ++j)
        {
            std::int64_t val1 = sequence1->at(i);
            std::int64_t val2 = sequence2->at(j);
            if (val1 == val2)
            {
                std::int64_t prev_max_length = 0;
                size_t len_equal = equal_seq_i.size();
                for (size_t k = 0; k < len_equal; ++k)
                {
                    size_t equal_pos_i = equal_seq_i.at(k);
                    size_t equal_pos_j = equal_seq_j.at(k);
                    if (equal_pos_i < i && equal_pos_j < j && sequence1->at(equal_pos_i) < val1)
                    {
                        std::int64_t max = lcs_matrix.at(equal_pos_i + 1).at(equal_pos_j + 1);
                        if (max > prev_max_length)
                        {
                            prev_max_length = max;
                        }
                    }
                }
                equal_seq_i.push_back(i);
                equal_seq_j.push_back(j);
                lcs_matrix.at(i + 1).at(j + 1) = prev_max_length + 1;
            }
            else
            {
                std::int64_t top = lcs_matrix.at(i + 1).at(j);
                std::int64_t left = lcs_matrix.at(i).at(j + 1);

                lcs_matrix.at(i + 1).at(j + 1) = top > left ? top : left;
            }
        }
    }

    return lcs_matrix.at(len1).at(len2);
}
