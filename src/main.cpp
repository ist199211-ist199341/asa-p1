#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long ull;
typedef long long ll;

struct sol_pair
{
    ll num;
    ull count;
};

typedef std::vector<sol_pair> stack_t;
typedef std::vector<stack_t *> stacks_t;

void fill_vector_until_newline(std::vector<ll> *sequence);
void solve_p1(std::vector<ll> *sequence, ull *result);
size_t solve_p2(std::vector<ll> *sequence1,
                std::vector<ll> *sequence2);

// aux fn p1
stacks_t::iterator get_stack_to_insert_to(stacks_t *stacks, ll n);
ull get_cumv_count_from_prev_stack(stacks_t::iterator curr, ll upper);

int main()
{
    int num_problem;
    std::vector<ll> sequence1, sequence2;

    std::cin >> num_problem;

    fill_vector_until_newline(&sequence1);
    if (num_problem == 1)
    {
        ull result[2];
        solve_p1(&sequence1, result);
        std::cout << result[0] << " " << result[1] << std::endl;
    }
    else if (num_problem == 2)
    {
        fill_vector_until_newline(&sequence2);

        ull result = solve_p2(&sequence1, &sequence2);
        std::cout << result << std::endl;
    }

    return 0;
}

void fill_vector_until_newline(std::vector<ll> *sequence)
{
    long long c = getchar();
    long long value;
    while (c == ' ' || c == '\n')
    {
        c = getchar();
    }

    while (true)
    {
        value = 0;
        bool changed = false;
        bool negative = false;
        while (c != ' ')
        {
            if (c == '\n' || c == EOF)
            {
                if (changed)
                {
                    if (negative)
                    {
                        value = -value;
                    }
                    sequence->push_back(value);
                }
                return;
            }
            if (c == '-')
            {
                value = value;
                negative = true;
                changed = true;
            }
            else if (c != ' ')
            {
                value = value * 10 + c - '0';
                changed = true;
            }
            c = getchar();
        }
        if (changed)
        {
            if (negative)
                value = -value;
            sequence->push_back(value);
        }
        c = getchar();
    }
}

void solve_p1(std::vector<ll> *sequence, ull *result)
{
    stacks_t stacks(0);

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

size_t solve_p2(std::vector<ll> *sequence1,
                std::vector<ll> *sequence2)
{
    size_t len1 = sequence1->size();
    size_t len2 = sequence2->size();

    ull *dp = (ull *)malloc(len2 * sizeof(ull));

    for (size_t i = 0; i < len2; i++)
    {
        dp[i] = 0;
    }

    for (size_t i = 0; i < len1; i++)
    {

        ull current = 0;

        for (size_t j = 0; j < len2; j++)
        {

            if (sequence1->at(i) == sequence2->at(j))
                if (current + 1 > dp[j])
                    dp[j] = current + 1;

            if (sequence1->at(i) > sequence2->at(j))
                if (dp[j] > current)
                    current = dp[j];
        }
    }

    ull result = 0;
    for (size_t i = 0; i < len2; i++)
        if (dp[i] > result)
            result = dp[i];

    return result;
}