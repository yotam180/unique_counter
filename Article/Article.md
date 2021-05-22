# Assignment 14 - Yotam Salmon

## Preface

In this project, we will examine the performance of various algorithms for counting unique values in an array.

## Measurements

We use 3 different metric values to measure the performance of each algorithm:

1. Number of comparisons conducted
2. Number of placements/copies
3. Number of "fixed-size" calculations

We use the third metric when hashtables are involved, since we wish to reflect the cost of hashing integers (which may be significant no less than comparisons and placements).

Of course, the metric values themselves tell us nothing meaningful about comparing different algorithms for the same input size, since we do not know the relation between the cost of a comparison, a placement and a hash calculation. Moreover, there are valuable metrics not counted in this exercise, such as runtime, number of dynamic allocations, memory requirements, etc.

However, the measurements from this exercise will show us the asymptotic behaviour of the metrics in different algorithms, and that should help us grasp a strong intuition about which algorithms outperform others in the task.

## Technical

TODO: Explain the method we use to measure the number of comparisons, placements, etc...

TODO: Write the operating system version, computer specs, compiler version.

TODO: Add csv files to the assets folder

## Algorithms

### 1. Original algorithm

**General:** This is the algorithm presented in Maman 12 Question 1(A). The algorithm arranges a subarray at the beginning of the original array, with all the unique values stored in the subarray. For every element in the array, the algorithm iterates the unique subarray to find out if the element has previously been encountered. Has it not been - it is appended to the unique subarray and a counter is incremented.

**Performance:** The algorithm contains two nested loops - one for iterating the entire array, and an inner loop that iterates the unique subarray for every element to look for it. In the worst case scenario, where every element is unique in the array, the algorithm should take $\Theta(n^2)$ comparisons to complete in the worst case.

Discussing the number of placements taking place, we observe that elements are getting copied when a new element is found. The line that performs element copies within the array is `*unique_end = *current;` in the C++ code, and it happens in the outer loop, outside of the nested `range_contains` function. Thus, the placement happens at most $n$ times, and the placements number is then $O(n)$, or in the worst case, $\Theta(n)$.

However, when we limit the range of known values, we know the maximum possible size of the unique subarray. Suppose the number of possible elements in the range is $m$. Thus, every inner iteration shall repeat no more than $m$ this, making the overall *worst-case* runtime complexity $\Theta(mn)$. When the range of generated values in the array is constant, the worst case complexity then becomes $\Theta(n)$.

Since the array values are numbers in the range $[1, 100]$, we can observe in the following metrics graph that the complexity is, in practice, linear!

![](Assets/original_algorithm_large_scale_graph.png)

<center>(1.1) - Original algorithms metrics graph<br/>Orange - comparisons, grey - placements</center><br/>

When we generate the numbers in the range $[1, 10000]$ and take array sizes of $N=[1,10000]$, we can see metrics that represent the average case where $m=\Theta(n)$. In that case, $\Theta(mn)$ is catually $\Theta(n^2)$. The following graph represents the collected data with the new ranges:

![](Assets/original_algorithm_small_scale_graph.png)

<center>(1.2) - Original algorithms metrics graph<br/>Orange - comparisons, grey - placements</center><br/>

An interesting phenomenon we observe in this graph is that it "starts" as we intented, but for larger values, it becomes linear. The reason is that when we reach larger array sizes, the array size $n$ comes close to the range $m$, then recreating the previous case where $m=\Theta(n)$.

The following graph really shows the intent. It represents the results of running the expreiments with $N=[1,10000]$ and element range of $[1,1000000]$ (keeping $m>>n$ at all time). Here we can see a typical $\Theta(n^2)$ graph:

![](Assets/original_algorithm_real_n2.png)

<center>(1.3) - Original algorithms metrics graph<br/>Blue - comparisons, orange - placements</center><br/>

Note that when the comparisons count really goes quadratic (rather than linear), the placements count (which is linear) is negligible.

### 2. Insertion sort

**General:** Sort the array using insertion sort, then iterate it *once* and find all unique values. Since we know all similar values reside in "groups" (i.e. between similar elements there cannot be another element), when iterating the array, every time an element changes `array[i] != array[i-1]`, we know the new element `array[i]` is a new, unique element (which is not in `array[0...i-1]`). The routine `count_unique_in_ordered_array` counts the unique elements in exactly that manner.

**Performance:** Insertion sort is known to take $\Theta(n^2)$ steps in the worst-case (and the average case, too), and `count_unique_in_ordered_array` will run in $\Theta(n)$.

Examine the `insertion_sort` subroutine more deeply, we see an outer loop that iterates exactly $n$ times. Inside the loop, a call to `first_larger`, which performs binary search on `array[0...i-1]` to look for the first value larger than `array[i]` (that is the insertion point). The binary search takes $\Theta(\log(i))$ comparisons. After the insertion point is found, the array `array[insertion_point...i]` is rotated right once (moving `array[i]`) into `array[insertion_point]`, and shifting every other element right one position. This procedure takes $\Theta(i-insertion\_point)$ placements. In the worst case, where the array is reversely-ordered, $insertion\_point$ will always be $0$ and the rotation will take $\Theta(i)$ placements.

In conclusion, as the outer loop executea $n$ times, the placements count in the worst case is then $\sum_{i=1}^ni=\Theta(n^2)$. The comparison count is $\sum_{i=1}^n\log(i)=\log(n!)=\Theta(n\log(n))$.

The following graph shows the performance metrics of the insertion sort algorithm on array sizes from $10$ to $10000$.

![](Assets/insertion_sort_graph.png)

<center>(2.1) - Insertion sort metrics graph<br/>Blue - comparisons, orange - placements</center><br/>

### 3. Optimal comparison-based sort

**General:** We used `std::sort` as an "optimal" comparison-based sort. The standard guarantees that this sort is optimal in the worst case:

```
Complexity

O(N·log(N)), where N = std::distance(first, last) comparisons. (since C++11)
```

After sorting the array, we use `count_unique_in_sorted_array` to count the unique values in a linear time.

**Performance:** Since an optimal sort should execute in no more than $O(n\log(n))$ steps, we expect the performance metrics to reflect that.

The following graph shows the comparisons and placements growth with array sizes of $10-10000$. Two additional lines are drawn: $f(x)=200x$ (yellow line) and $f(x)=73x\log(x)$ (grey line), to visually show that the comparisons&placements graph is not linear.

![](Assets/optimal_sort_graph.png)

<center>(3.1) - Optimal sort metrics graph<br/>Blue - comparisons, orange - placements, grey - nlgn, yellow - linear</center><br/>

### 4. Heapsort

**General:** in addition to using `std::sort` (for it's known to be blazingly fast), I wanted to see the results of  a known optimal sort. The library functions added in C++20, `std::make_heap` and `std::pop_heap`, made it very simple to implement a heap sort.

After sorting the array, we use `count_unique_in_sorted_array` to count the unique values in a linear time.

**Performance:** Heapsort is known to take $\Theta(n\log(n))$ in its worst case. By calling $MAX\_HEAPIFY$ on the heap, we perform up to $\log(n)$ comparisons and $\log(n)$ placements (swapping elemants). Having $MAX\_HEAPIFY$ run $n$ times during the algorithm with decreasing heap size, the total number of comparisons/placements (after crafting the heap for the first time) should be $\sum_{i=1}^n\log(i)=\Theta(n\log(n))$.

![](Assets/heap_sort_graph.png)

<center>(4.1) - Heap sort metrics graph<br/>Blue - comparisons, orange - placements</center><br/>

We observe more placements than comparisons generally because of the frequent swapping, which counts as 3 placements.

### 5. Counting sort C array

**General:** 

## Raw outputs:

```
N=100
Running with 1 Original algorithm
        Result: 62, Comparisons: 2756, Placements: 262, Calculations: 0
Running with 2 Insertion sort
        Result: 62, Comparisons: 627, Placements: 6787, Calculations: 0
Running with 3 Heap sort
        Result: 62, Comparisons: 802, Placements: 1064, Calculations: 0
Running with 4 Optimal sort
        Result: 62, Comparisons: 1109, Placements: 1230, Calculations: 0
Running with 5 Counting table
        Result: 62, Comparisons: 100, Placements: 325, Calculations: 0
Running with 6 Hash table
        Result: 62, Comparisons: 79, Placements: 224, Calculations: 170
Running with 7 Binary tree
        Result: 62, Comparisons: 1583, Placements: 162, Calculations: 0
Running with 8 Red-Black tree
        Result: 62, Comparisons: 970, Placements: 162, Calculations: 0
```

```
N=1000
Running with 1 Original algorithm
        Result: 101, Comparisons: 46909, Placements: 2101, Calculations: 0
Running with 2 Insertion sort
        Result: 101, Comparisons: 9589, Placements: 712168, Calculations: 0
Running with 3 Heap sort
        Result: 101, Comparisons: 11271, Placements: 13868, Calculations: 0
Running with 4 Optimal sort
        Result: 101, Comparisons: 11868, Placements: 11466, Calculations: 0
Running with 5 Counting table
       " Result: 101, Comparisons: 1000, Placements: 1303, Calculations: 0
Running with 6 Hash table
        Result: 101, Comparisons: 943, Placements: 1202, Calculations: 1173
Running with 7 Binary tree
        Result: 101, Comparisons: 14450, Placements: 1101, Calculations: 0
Running with 8 Red-Black tree
        Result: 101, Comparisons: 8349, Placements: 1101, Calculations: 0
```

```
N=10000
Running with 1 Original algorithm
        Result: 101, Comparisons: 509901, Placements: 20101, Calculations: 0
Running with 2 Insertion sort
        Result: 101, Comparisons: 128912, Placements: 74801431, Calculations: 0
Running with 3 Heap sort
        Result: 101, Comparisons: 146394, Placements: 172444, Calculations: 0
Running with 4 Optimal sort
        Result: 101, Comparisons: 107440, Placements: 88345, Calculations: 0
Running with 5 Counting table
        Result: 101, Comparisons: 10000, Placements: 10303, Calculations: 0
Running with 6 Hash table
        Result: 101, Comparisons: 9955, Placements: 10202, Calculations: 10173
Running with 7 Binary tree
        Result: 101, Comparisons: 125499, Placements: 10101, Calculations: 0
Running with 8 Red-Black tree
        Result: 101, Comparisons: 78488, Placements: 10101, Calculations: 0
```

```
N=100000
Running with 1 Original algorithm
        Result: 101, Comparisons: 5092129, Placements: 200101, Calculations: 0
Running with 2 Insertion sort
        Result: 101, Comparisons: 1622336, Placements: 7399179193, Calculations: 0
Running with 3 Heap sort
        Result: 101, Comparisons: 1796290, Placements: 2056625, Calculations: 0
Running with 4 Optimal sort
        Result: 101, Comparisons: 1067254, Placements: 919963, Calculations: 0
Running with 5 Counting table
        Result: 101, Comparisons: 100000, Placements: 100303, Calculations: 0
Running with 6 Hash table
        Result: 101, Comparisons: 99946, Placements: 100202, Calculations: 100173
Running with 7 Binary tree
        Result: 101, Comparisons: 1331265, Placements: 100101, Calculations: 0
Running with 8 Red-Black tree
        Result: 101, Comparisons: 792171, Placements: 100101, Calculations: 0
```

> **Note:** Insertion sort (algorithm #2) could not run with `N=1000000` in a reasonable amount of time. I had to stop the experiment, and thus the next run does not contain metrics for insertion sort.

```
N=1000000
Running with 1 Original algorithm
        Result: 101, Comparisons: 50948269, Placements: 2000101, Calculations: 0
Running with 3 Heap sort
        Result: 101, Comparisons: 21269739, Placements: 23874683, Calculations: 0
Running with 4 Optimal sort
        Result: 101, Comparisons: 10674645, Placements: 9474961, Calculations: 0
Running with 5 Counting table
        Result: 101, Comparisons: 1000000, Placements: 1000303, Calculations: 0
Running with 6 Hash table
        Result: 101, Comparisons: 999942, Placements: 1000202, Calculations: 1000173
Running with 7 Binary tree
        Result: 101, Comparisons: 13609646, Placements: 1000101, Calculations: 0
Running with 8 Red-Black tree
        Result: 101, Comparisons: 7929950, Placements: 1000101, Calculations: 0
```
