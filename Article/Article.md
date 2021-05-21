# Assignment 14 - Yotam Salmon

## Preface

In this project, we will examine the performance of various algorithms for counting unique values in an array.

## Metrics

We use 3 different metric values to measure the performance of each algorithm:

1. Number of comparisons conducted
2. Number of placements/copies
3. Number of "fixed-size" calculations

We use the third metric when hashtables are involved, since we wish to reflect the cost of hashing integers (which may be significant no less than comparisons and placements).

Of course, the metric values themselves tell us nothing meaningful about comparing different algorithms for the same input size, since we do not know the relation between the cost of a comparison, a placement and a hash calculation. Moreover, there are valuable metrics not counted in this exercise, such as runtime, number of dynamic allocations, memory requirements, etc.

However, the measurements from this exercise will show us the asymptotic behaviour of the metrics in different algorithms, and that should help us grasp a strong intuition about which algorithms outperform others in the task.

## Technical

TODO: Explain the method we use to measure the number of comparisons, placements, etc...

## Algorithms

### Original algorithm

**General:** This is the algorithm presented in Maman 12 Question 1(A). The algorithm arranges a subarray at the beginning of the original array, with all the unique values stored in the subarray. For every element in the array, the algorithm iterates the unique subarray to find out if the element has previously been encountered. Has it not been - it is appended to the unique subarray and a counter is incremented.

**Performance:** The algorithm contains two nested loops - one for iterating the entire array, and an inner loop that iterates the unique subarray for every element to look for it. In the worst case scenario, where every element is unique in the array, the algorithm should take $\Theta(n^2)$ steps to complete in the worst case.

> // TODO: Maybe move the next section to somewhere else
However, when we limit the range of known values, we can know the maximum size of the unique subarray. Suppose the number of possible elements in the range is $m$. Thus, every inner iteration shall repeat no more than $m$ this, making the overall *worst-case* runtime complexity $\Theta(mn)$. When the range of generated values in the array is constant, the worst case complexity then becomes $\Theta(n)$.

Since the array values are numbers in the range $[1, 100]$, we can observe in the following metrics graph that the complexity is, in practice, linear!

![](Assets/original_algorithm_large_scale_graph.png)

<center>(1.1) - Original algorithms metrics graph<br/>Orange - comparisons, grey - placements</center>

When we generate the numbers in the range $[1, 10000]$ and take array sizes of $N=[1,10000]$, we can see metrics that represent the average case where $m=\Theta(n)$. In that case, $\Theta(mn)$ is catually $\Theta(n^2)$. The following graph represents the collected data with the new ranges:

![](Assets/original_algorithm_small_scale_graph.png)

<center>(1.2) - Original algorithms metrics graph<br/>Orange - comparisons, grey - placements</center>

An interesting phenomenon we observe in this graph is that it "starts" with something 

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
        Result: 101, Comparisons: 1000, Placements: 1303, Calculations: 0
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

