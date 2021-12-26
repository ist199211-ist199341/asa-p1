#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <unordered_map>

typedef unsigned long long ull;
typedef long long ll;

struct sol_pair
{
    ll num;
    ull count;
};

typedef std::vector<sol_pair> stack_t;
typedef std::vector<stack_t *> stacks_t;

void fill_vector_until_newline(std::vector<ll> *sequence, std::unordered_map<ll, int> *elements_sequence1, bool intersection);
void solve_p1(std::vector<ll> *sequence, ull *result);
int solve_p2(std::vector<ll> *sequence1,
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

    std::unordered_map<ll, int> elements_sequence1;

    fill_vector_until_newline(&sequence1, &elements_sequence1, false);
    if (num_problem == 1)
    {
        ull result[2];
        solve_p1(&sequence1, result);
        std::cout << result[0] << " " << result[1] << std::endl;
    }
    else if (num_problem == 2)
    {
        fill_vector_until_newline(&sequence2, &elements_sequence1, true);

        std::cout << solve_p2(&sequence1, &sequence2) << std::endl;
    }

    return 0;
}

std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;

    while (getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }

    return internal;
}

void fill_vector_until_newline(std::vector<ll> *sequence, std::unordered_map<ll, int> *elements_sequence1, bool intersection)
{
    std::string input_sequence;
    getline(std::cin, input_sequence);
    input_sequence.append(" ");
    std::vector<std::string> out;
    out = split(input_sequence, ' ');
    for (std::string t : out)
    {
        if (!t.empty())
        {
            // true - only add if it exists in seq1
            if (intersection)
            {
                if (elements_sequence1->count(std::stoll(t)) > 0)
                {
                    sequence->push_back(std::stoll(t));
                    elements_sequence1->at(std::stoll(t))--;
                }
            }
            // false - add to hashmap
            else
            {
                if (elements_sequence1->count(std::stoll(t)) == 0)
                    elements_sequence1->insert({std::stoll(t), 1});

                else
                {
                    elements_sequence1->at(std::stoll(t))++;
                }
                sequence->push_back(std::stoll(t));
            }
        }
    }
}

void solve_p1(std::vector<ll> *sequence, ull *result)
{
    stacks_t stacks(0);
    if (sequence->size() == 0)
    {
        result[0] = 0;
        result[1] = 0;
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

    result[0] = stacks.size();
    result[1] = stacks.back()->back().count;
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

int solve_p2(std::vector<ll> *sequence1,
             std::vector<ll> *sequence2)
{

    int *dp = (int *)calloc(sequence2->size() * sizeof(int), sizeof(int));

    for (size_t i = 0; i < sequence1->size(); i++)
    {

        int current = 0;

        for (size_t j = 0; j < sequence2->size(); j++)
        {

            if (sequence1->at(i) == sequence2->at(j))
                if (current + 1 > dp[j])
                    dp[j] = current + 1;

            if (sequence1->at(i) > sequence2->at(j))
                if (dp[j] > current)
                    current = dp[j];
        }
    }

    int result = 0;
    for (size_t i = 0; i < sequence2->size(); i++)
        if (dp[i] > result)
            result = dp[i];

    return result;
}