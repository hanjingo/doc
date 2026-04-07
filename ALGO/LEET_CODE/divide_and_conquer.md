# Divide and Conquer Algorithm

[TOC]



#### Split the array in half, sort both halves, then merge them back.

```c++
void merge_sort(std::vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    
    // merge
    std::vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
        temp.push_back((arr[i] <= arr[j]) ? arr[i++] : arr[j++]);

    while (i <= mid)
        temp.push_back(arr[i++]);

    while (j <= right)
        temp.push_back(arr[j++]);

    for (i = left; i <= right && i - left < temp.size(); i++)
        arr[i] = temp[i - left];
}
```

| Scenario                           | Time Complexity | Space Complexity |
| :--------------------------------- | :-------------- | :--------------- |
| Best Case                          | O(n log n)      | O(n)             |
| Average Case                       | Θ(n log n)      | O(n)             |
| **Early Exit Best** (small target) | O(n log n)      | O(n)             |