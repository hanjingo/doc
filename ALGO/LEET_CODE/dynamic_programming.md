# Dynamic Programming

[TOC]



#### Given an array and a target, how'd you use dynamic programming to find the two numbers that add up to the target?

```c++
std::vector<int> two_sum_dp(const std::vector<int>& sorted_arr, const int target)
{
    if (target < 0) 
        return {};

    // store minimum elements needed for each sum
    std::vector<int> dp(target + 1, INT_MAX);
    dp[0] = 0;

    // store the last number used to achieve each sum
    std::vector<int> last_num(target + 1, -1);
    std::vector<int> prev_sum(target + 1, -1);
    for (auto num : sorted_arr)
    {
        if (num > target)
            continue;

        // traverse backwards to avoid reusing same element
        for (int s = target; s >= num; --s)
        {
            if (dp[s - num] != INT_MAX && dp[s - num] + 1 < dp[s])
            {
                dp[s] = dp[s - num] + 1;
                last_num[s] = num;
                prev_sum[s] = s - num;
            }
        }

        // early exit if we found exactly 2 elements
        if (dp[target] == 2)
            break;
    }

    // reconstruct the pair
    if (dp[target] == 2)
        return {last_num[target], last_num[prev_sum[target]]};

    return {};
}
```

| Scenario                           | Time Complexity            | Space Complexity | Operations (approx) |
| :--------------------------------- | :------------------------- | :--------------- | :------------------ |
| **Best Case** (pair found early)   | O(target)                  | O(target)        | target operations   |
| **Average Case**                   | O(n × target)              | O(target)        | (n × target)/2      |
| **Worst Case** (no pair found)     | O(n × target)              | O(target)        | n × target          |
| **Early Exit Best** (small target) | O(n × k) where k << target | O(target)        | n × k               |
