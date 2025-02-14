# Sort Algorithm Summary

[TOC]



## Overview

There is a summary of sorting algorithms:

| Sort Algorithm | Average Case | Best Case    | Worst Case  | Space Complexity | Stability |
| -------------- | ------------ | ------------ | ----------- | ---------------- | --------- |
| Insertion Sort | $O(n^2)$     | $O(n)$       | $O(n^2)$    | $O(1)$           | Stable    |
| Shell Sort     | $O(n^{1.3})$ | $O(n)$       | $O(n^2)$    | $O(1)$           | Unstable  |
| Selection Sort | $O(n^2)$     | $O(n^2)$     | $O(n^2)$    | $O(1)$           | Unstable  |
| Heap Sort      | $O(nlog n)$  | $O(nlog n)$  | $O(nlog n)$ | $O(1)$           | Unstable  |
| Bubble Sort    | $O(n^2)$     | $O(n)$       | $O(n^2)$    | $O(1)$           | Stable    |
| Quick Sort     | $O(nlog n)$  | $O(nlog n)$  | $O(n^2)$    | $O(nlog n)$      | Unstable  |
| Merge Sort     | $O(nlog n)$  | $O(nlog n)$  | $O(nlog n)$ | $O(n)$           | Stable    |
| Radix Sort     | $O(d(r+n))$  | $O(d(n+rd))$ | $O(d(r+n))$ | $O(rd+n)$        | Stable    |

---



## Insertion Sort

The insertion sort is the simplest sorting algorithms.

### Step

Example:

| Step  | 5     | 6     | 3    | 1     | 8     | 7    | 2    | 4    |
| ----- | ----- | ----- | ---- | ----- | ----- | ---- | ---- | ---- |
| one   | **3** | 5     | 6    | 1     | 8     | 7    | 2    | 4    |
| two   | **1** | 3     | 5    | 6     | 8     | 7    | 2    | 4    |
| three | 1     | 3     | 5    | 6     | **7** | 8    | 2    | 4    |
| four  | 1     | **2** | 3    | 5     | 6     | 7    | 8    | 4    |
| five  | 1     | 2     | 3    | **4** | 5     | 6    | 7    | 8    |

### Implement

(C++)

```c++
void insert_sort(int array[], unsignedint n)
{
    int i,j;
    int temp;
    for(i = 1;i < n;i++)
    {
        temp = array[i];
        for(j = i;j > 0 && array[j - 1] > temp;j--)
        {
            array[j]= array[j - 1];
        }
        array[j] = temp;
    }
}
```

(C++ STL Implementation)

```c++
template <typename Comparable>
void insertionSort(vector<Comparable>& a)
{
    int j;
    for (int p = 1; p < a.size(); p++)
    {
        Comparable tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

template <typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end)
{
    if (begin != end)
        inertionSortHelp(begin, end, *begin);
}
template <typename Iterator, typename Object>
void insertionSortHelp(const Iterator& begin, const Iterator& end, const Object& obj)
{
    insertionSort(begin, end, less<Object>());
}

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan)
{
    if (begin != end)
        insertionSort(begin, end, lessThan, *begin);
}
template<typename Iterator, typename Comparator, typename Object>
void insertionSort(const Iterator& begin, const Iterator& end, 
    Comparator lessThan, const Object& obj)
{
    Iterator j;

    for (Iterator p = begin + 1; p != end; ++p)
    {
        Object tmp = *p;
        for (j = p; j != begin && lessThan(tmp, *(j-1)); --j)
            *j = *(j - 1);
        *j = tmp;
    }
}
```

### Performance Analysis

$\sum_{i=2}^{N} i=2+3+4+...+N = O(N^2)$

- The average and worst case: $O(N^2)$

  We express the running time of INSERTION-SORT as $an^2 + bn + c$ for constants $a, b$ and $c$ that again depends on the statement costs $c_i$; it is thus a `quadratic function` of $n$.

- The best case:  $O(N)$

  we can express this running time as $an+b$ for constants $a$ and $b$ that depend on the statement costs $c_i$; it is thus a `linear function` of $n$.

---



## Shell Sort

Shellsort works by comparing elements that are distant; the distance between comparisons decreases as the algorithm runs until the last phase, in which adjacent elements are compared. For this reason, Shellsort is sometimes referred to as **diminishing increment sort**.

### Implement

(C++)

```c++
template <typename Comparable>
void shellsort(vector<Comparable>& a)
{
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
        for (int i = gap; i < a.size(); i++)
        {
            Comparable tmp = a[i];
            int j = i;

            for (; j >= gap && tmp < a[j-gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
}
```

### Performance Analysis

- The best case: $O(n)$.
- The average case: $O(n^{1.3})$
- The worst case:
  1. The worst-case running time of Shell sort using Shell's increments is $\Theta(N^2)$.
  2. The worst-case running time of Shell sort using Hibbard's increments is $\Theta(N^{3/2})$.

---



## Selection Sort

Selection sort is an easy sort algorithm.

### Step

### Implement

(C++)

```c++
void select_sort(int *a,int n)
{
    register int i,j,min,t;
    for(i = 0;i < n-1;i++)
    {
        min = i;
        for(j = i + 1;j < n;j++)
            if(a[min] > a[j])
                min = j;
        if(min != i)
        {
            t = a[min];
            a[min] = a[i];
            a[i] = t;
        }
    }
}
```

### Performance Analysis

- The best/average case: $O(n^2)$
- The worst case: $O(n^2)$

---



## Bubble Sort

### Step

### Implement

(C++)

```c++
#include <stdio.h>
#define SIZE 8void bubble_sort(int a[], int n)
{
    int i, j, temp;
    for (j = 0;j < n - 1;j++)
        for (i = 0;i < n - 1 - j;i++)
        {
            if(a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
}
 
int main()
{
    int number[SIZE] = {95, 45, 15, 78, 84, 51, 24, 12};
    int i;
    bubble_sort(number, SIZE);
    for (i = 0; i < SIZE; i++)
    {
        printf("%d", number[i]);
    }
    printf("\n");
}
```

### Performance Analysis

- The best case: $O(n)$
- The average case: $O(n^2)$
- The worst case: $O(n^2)$

---



## Merge Sort

### Step

### Implement

(C++)

```c++
#include <stdlib.h>
#include <stdio.h>
 
void Merge(int sourceArr[],int tempArr[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j=midIndex+1, k = startIndex;
    while(i != midIndex + 1 && j != endIndex + 1)
    {
        if(sourceArr[i] >= sourceArr[j])
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i = startIndex; i <= endIndex; i++)
        sourceArr[i] = tempArr[i];
}
 
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = (startIndex + endIndex) / 2;
        MergeSort(sourceArr, tempArr, startIndex, midIndex);
        MergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}
 
int main(int argc, char * argv[])
{
    int a[8] = {50, 10, 20, 30, 70, 40, 80, 60};
    int i, b[8];
    MergeSort(a, b, 0, 7);
    for(i=0; i<8; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
```

### Performance Analysis

- The best/average case: $O(N log N)$
- The worst case: $O(N log N)$

---



## Quick Sort

### Step

Here is the three-step divide-and-conquer process for quick sort:

1. Divide
2. Conquer
3. Combine

Example:

1. Choose pivot：

   | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
   | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
   | 69   | 81   | 30   | 38   | 9    | 2    | 47   | 61   | 32   | 79   |

2. Partition：

   | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
   | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
   | 2    | 61   | 30   | 38   | 9    | 61   | 47   | 69   | 81   | 79   |

3. Recursive：

   | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
   | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
   | 2    | 9    | 30   | 32   | 38   | 47   | 61   | 69   | 79   | 81   |

### Implement

```c++
void quick_sort(int a[], int low, int high)
{
    if(low >= high)
        return;

    int first = low;
    int last  = high;
    int key   = a[first];
    while(first < last)
    {
        while(first < last && a[last] >= key) { --last; }
        a[first] = a[last];
      
        while(first < last && a[first] <= key) { ++first; }
        a[last] = a[first];
    }
    a[first] = key;
    quick_sort(a, low, first-1);
    quick_sort(a, first+1, high);
}
```

### Performance Analysis

- The best/average case: $O(nlogn)$

- The worst case:  $O(n^2)$


---



## Heap Sort

### Step

Example:

1. Create a heap.

   ![heap_sort1](/usr/local/src/github.com/hanjingo/doc/ALGO/res/heap_sort1.png)

2. Exchange head and tail.

   ![heap_sort2](/usr/local/src/github.com/hanjingo/doc/ALGO/res/heap_sort2.png)

3. So on, until the heap size equals 1.

### Implement

```c++
void HeapAdjust(int array[],int i,int nLength)
{
    int nChild;
    int nTemp;
    for(; 2 * i + 1 < nLength;i = nChild)
    {
        nChild = 2 * i + 1;
        if(nChild < nLength - 1 && array[nChild + 1] > array[nChild]) ++nChild;
        if(array[i] < array[nChild])
        {
            nTemp = array[i];
            array[i] = array[nChild];
            array[nChild] = nTemp; 
        }
        else break;
    }
}

void HeapSort(int array[],int length)
{
    int i;
    for(i = length / 2 - 1;i >= 0;--i)
    HeapAdjust(array,i,length);
    for(i = length - 1;i > 0;--i)
    {
        array[i] = array[0] ^ array[i];
        array[0] = array[0] ^ array[i];
        array[i] = array[0] ^ array[i];
        HeapAdjust(array,0,i);
    }
}

int main()
{
    int i;
    int num[]={9,8,7,6,5,4,3,2,1,0};
    HeapSort(num,sizeof(num)/sizeof(int));
    for(i = 0;i < sizeof(num) / sizeof(int);i++)
    {
        printf("%d ",num[i]);
    }
    printf("\nok\n");
    return 0;
}
```

### Performance Analysis

$O(lg\ n)$.

- The worst case:  $O(nlog n)$
- The average case: $O(nlog n)$
- The worst case: $O(nlog n)$

---



## Reference

[1] Thomas H.Cormen, Charles E.Leiserson, Ronald L. Rivest, Clifford Stein. Introduction to Algorithms . 3ED

[2] Mark Allen Weiss. Data Structures and Algorithm Analysis in C++ . 4ED
