# Search Problem

[TOC]



### Can you write a function that finds the first non-repeating character in a string?

```c++
char first_no_repeating_char(const std::string& str)
{
    int char_count[256] = {0}; // Assuming ASCII character set
    for (char ch : str)  // O(str.size())
        char_count[static_cast<unsigned char>(ch)]++;

    // Find the first non-repeating character
    for (char ch : str) // O(str.size())
        if (char_count[static_cast<unsigned char>(ch)] == 1)
            return ch;

    return '\0'; // Return null character if no non-repeating character is found
}
```

Complexity Analysis:

- Time Complexity: $O(n)$.
- Space Complexity: $O(1)$.



### Given a sorted array, find two numbers that add up to a target. Write the code using two pointers.

```c++
void find_num2(int* n1, int* n2, int arr[], const size_t size, const int sum)
{
    std::unordered_map<int, int> tmp;
    for (int i = 0; i < size; ++i)
        tmp.insert({arr[i], i});

    
    int target = 0;
    for (int i = 0; i < size; ++i)
    {
        target = sum - arr[i];
        if (tmp.count(target) < 1)
            continue;

        *n1 = arr[i];
        *n2 = arr[tmp[target]];
        return;
    }
    return;
}

```

Complexity Analysis:

- Time complexity: $O(n)$
- Space complexity: $O(n)$



### Write a function that finds the two numbers in an array that add up to a target sum by using a hash map.

```c++
std::optional<std::pair<int, int>> 
find_two_sum_indices(const std::vector<int>& nums, int target)
{
    int complement;
    std::unordered_map<int, int> num_map;
    for (int i = 0; i < nums.size(); ++i)
    {
        complement = target - nums[i];
        if (num_map.count(complement))
            return std::make_pair(num_map[complement], i);
        num_map[nums[i]] = i;
    }
    return std::nullptr;
}
```

Complexity Analysis:

- Time complexity: $O(n)$
- Space complexity: $O(n)$



### Write a function that checks if a string is a palindrome using two iterators

```c++
bool is_palindrome(const std::string& str)
{
    for(int i = 0, j = str.size() - 1; i < j; ++i, --j) 
    {
        if (str[i] != str[j])
            return false;
    }
    return true;
}
```

Complexity Analysis:

- Time complexity: $O(n)$
- Space complexity: $O(1)$



### Write a function that removes duplicates from a sorted vector using the two-pointer technique.

```c++
void remove_dumplicate(std::vector<int>& sorted_arr)
{
    for (int i = 0, j = 1; i < sorted_arr.size() && j < sorted_arr.size();)
    {
        if (sorted_arr[i] != sorted_arr[j])
        {
            ++i;
            ++j;
            continue;
        }
        
        sorted_arr.erase(sorted_arr.begin() + j);
    }
}
```

Complexity Analysis:

- Time complexity: $O(n^2)$, where $n$ is the size of the vector. Each duplicate removal with `erase` is $O(n)$ in the worst case, and in the worst case (all elements are duplicates), this can be repeated up to $n$ times.
- Space complexity: $O(1)$, as the operation is performed in-place without using extra space.



### Checks if two strings are anagrams using character frequency counting.

```c++
bool is_anagram1(const std::string& str1, const std::string& str2)
{
    if (str1.length() != str2.length())
        return false;
        
    char ct1[256] = {0};
    for (auto e : str1)
        ct1[static_cast<uint8_t>(e)]++;

    char ct2[256] = {0};
    for (auto e : str2)
        ct2[static_cast<uint8_t>(e)]++;

    for (int i = 0; i < 256; ++i)
        if(ct1[i] != ct2[i])
            return false;

    return true;
}
```

Complexity Analysis:

- Time complexity: $O(n + m)$
- Space complexity: $O(1)$



### Finds the maximum sum of any contiguous subarray using Kadane's algorithm.

```c++
int kadane(const std::vector<int>& arr)
{
    int ret = 0;
    int sum = 0;
    for (int i = 0; i < arr.size(); ++i)
    {
        sum = 0;
        for (int j = i; j < arr.size(); ++j)
        {
            sum += arr[j];
            ret = (sum > ret) ? sum : ret;
        }
    }
    return ret;
}
```

Complexity Analysis:

- Time complexity: $O(n^2)$
- Space complexity: $O(1)$  bngvnb 