#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <unordered_set>

typedef unsigned long long ull;
typedef long long ll;

struct sol_pair
{
    ll num;
    ull count;
};

typedef std::vector<sol_pair> stack_t;
typedef std::vector<stack_t *> stacks_t;

void fill_vector_until_newline(std::vector<ll> *sequence, std::unordered_set<ll> *elements_sequence1, bool intersection);
void solve_p1(std::vector<ll> *sequence, ull *max_length);
ull solve_p2(std::vector<ll> *sequence1,
             std::vector<ll> *sequence2);

// aux fn p1
stacks_t::iterator get_stack_to_insert_to(stacks_t *stacks, ll n);
ull get_cumv_count_from_prev_stack(stacks_t::iterator curr, ll upper);

int main()
{

    int num_problem;
    std::string dummy;
    std::vector<ll> sequence1, sequence2;

    std::cin >> num_problem;
    getline(std::cin, dummy);

    std::unordered_set<ll> elements_sequence1;

    fill_vector_until_newline(&sequence1, &elements_sequence1, false);

    if (num_problem == 1)
    {
        ull max_length[2];
        solve_p1(&sequence1, max_length);
        std::cout << max_length[0] << " " << max_length[1] << std::endl;
    }
    else if (num_problem == 2)
    {
        fill_vector_until_newline(&sequence2, &elements_sequence1, true);

        std::cout << solve_p2(&sequence1, &sequence2) << std::endl;
    }

    return 0;
}

void fill_vector_until_newline(std::vector<ll> *sequence, std::unordered_set<ll> *elements_sequence1, bool intersection)
{
    std::string input_sequence;
    getline(std::cin, input_sequence);
    std::stringstream input_stream(input_sequence);
    std::string t;
    while (getline(input_stream, t, ' '))
    {
        if (!t.empty())
        {
            ll value = std::stoll(t);
            // true - only add if it exists in seq1
            if (intersection)
            {
                if (elements_sequence1->count(value) > 0)
                {
                    sequence->push_back(value);
                }
            }
            // false - add to hashmap
            else
            {
                elements_sequence1->insert(value);
                sequence->push_back(value);
            }
        }
    }
}

void solve_p1(std::vector<ll> *sequence, ull *max_length)
{
    stacks_t stacks(0);
    if (sequence->size() == 0)
    {
        max_length[0] = 0;
        max_length[1] = 0;
        return;
    }

    for (auto it = sequence->begin(); it != sequence->end(); ++it)
    {
        auto insertion_stack = get_stack_to_insert_to(&stacks, *it);

        ull count = 1;
        if (insertion_stack != stacks.begin())
        {
            count = get_cumv_count_from_prev_stack(insertion_stack, *it);
        }
        if (insertion_stack == stacks.end())
        {
            // add new stack
            stacks.push_back(new stack_t(1, {*it, count}));
        }
        else
        {
            count += (*insertion_stack)->back().count;
            (*insertion_stack)->push_back({*it, count});
        }
    }

    max_length[0] = stacks.size();
    max_length[1] = stacks.back()->back().count;
}

stacks_t::iterator get_stack_to_insert_to(stacks_t *stacks, ll n)
{
    return std::lower_bound(stacks->begin(), stacks->end(), n,
                            [](stack_t *a, ll n)
                            { return a->back().num < n; });
}

ull get_cumv_count_from_prev_stack(stacks_t::iterator curr, ll upper)
{
    stacks_t::iterator prev_stack_it = curr - 1;
    ull max_count = (*prev_stack_it)->back().count;
    ull min_count = 0;

    auto lower = std::lower_bound((*prev_stack_it)->begin(), (*prev_stack_it)->end(), upper,
                                  [](sol_pair a, ll n)
                                  { return a.num >= n; });

    if (lower != (*prev_stack_it)->begin())
    {
        min_count = (lower - 1)->count;
    }

    return max_count - min_count;
}

ull solve_p2(std::vector<ll> *sequence1,
             std::vector<ll> *sequence2)
{

    ull *max_length_until = (ull *)calloc(sequence2->size(), sizeof(ull));
    ull max_length = 0;

    for (auto it_seq1 = sequence1->begin(); it_seq1 != sequence1->end(); ++it_seq1)
    {
        ull length_until_seq1_value = 0;
        size_t cache_index = 0;

        for (auto it_seq2 = sequence2->begin(); it_seq2 != sequence2->end(); ++it_seq2)
        {
            if (*it_seq1 > *it_seq2)
            {
                if (max_length_until[cache_index] > length_until_seq1_value)
                {
                    length_until_seq1_value = max_length_until[cache_index];
                }
            }
            if (*it_seq1 == *it_seq2)
            {
                if (length_until_seq1_value + 1 > max_length_until[cache_index])
                {
                    max_length_until[cache_index] = length_until_seq1_value + 1;
                    if (length_until_seq1_value >= max_length)
                    {
                        max_length = length_until_seq1_value + 1;
                    }
                }
            }
            ++cache_index;
        }
    }

    free(max_length_until);
    return max_length;
}
