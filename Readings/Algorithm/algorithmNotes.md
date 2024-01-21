## TO LEARN

- [ ] Graph Algorithm 


## [Dynamic Programming](https://www.youtube.com/watch?v=oBt53YbR9Kk)

Dynamic programming is a problem-solving technique used in computer science and mathematics to efficiently solve complex problems by **breaking them down into overlapping sub-problems** and reusing previously computed results.

> Here, reusing overlapping results is the key.

**The key idea behind dynamic programming is to solve each subproblem only once and store its result in a table (usually an array or a matrix). This way, when the same subproblem needs to be solved again, its result can be retrieved from the table instead of recomputing it, leading to significant time savings.**

### Memoization

Fib number using recursion is a pretty straight forward problem that incurs so many overlapping sub-problems, which drastically reduce the time complexity to `O(n)`. Therefore, this is a typical dynamic programming problem. More detail can refer to [Fib in DP](https://youtu.be/oBt53YbR9Kk?t=1503)

By using **memoization**, the structure of recursion tree of Fib problem becomes much smaller.

![fib_memo](Assets/Screenshot%202023-09-05%20at%2017.58.08.png)

> The most important thing is solving dynamic programming is to try to **think about the recursive functions in terms of a Tree**.


**Recipe for solving memoization DP problems.**

![recipe_dp](Assets/Screenshot%202023-09-05%20at%2019.03.50.png)

### Tabulation

Tabulation approach to Dynamic Programming also reduces the problem into subproblem. However Unlike memoization that uses recursion, **tabulation does it iteratively by building a table**.

Since, we have to use iteration, unlike recursion that has a straightforward minding and returns the result from the base case, now we are going from the base case all the way to the end with no turning back. **Hence, we'll consider all possible outcomes the current position can affect the following positions.**

For the Fib problem, we know, the current position is the sum of the previous 2 positions. (This is backward thinking) If we rethink this in a going forward way, we'd say, the current position contributes to the next 2 positions.

`[0,1,1,2] with index 0, 1, 2, 3`

For example, we say position 3 is calculated based on position 2 + position 1, and position 2 is calculated based on position 1 + position 0. Hence, with forwarding in mind, it's the same as saying position 1 contributes to position 2 and 3.

**Recipe for solving DP using tabulation approach.**

1. Create a table based on the input. (usually bigger, so that the index aligns with meaning).
> usually, when having multiple inputs, create table based on the input that can shrink the problem. For, example, the [canSum problem](https://youtu.be/oBt53YbR9Kk?t=13079), where we have a targetSum and an array, since a smaller targetSum means a smaller problem, we'll use targetSum to build the table, not the array.
2. initialize the table with meaning.
> Usually, the initial value should be the same as the output type as required. 

3. Think about how each step can contribute to all other steps based on the question.



## Greedy Algorithm


Greedy Algorithm also reduces the problem into subproblem, we call **stage**. In each stage, we only consider the optimal solution, and use the optimal solution in each step to form the final solution. 

As Greedy Method doesn't check all the possible cases, the solution it gives is local optimal. However, for some problems, **the local optimization can lead to global optimization.**

> For the *Activity Selection Problem*, Intuition says, you should choose an activity that leaves the resource available for as many other activities as possible. Of the activities you end up choosing, one of them must be the first one to finish. Intuition says, therefore, choose the activity in S with the earliest finish time, since that leaves the resource available for as many of the activities that follow it as possible. **Hence, each stage, we choose the activity with earliest finish time, and look into the subproblem.**

![activity_selection_problem]()



We’ll arrive at the greedy algorithm by first considering a dynamic-programming approach and then showing that an optimal solution can result from always making greedy choices.


## Complexity Analysis

### Time Complexity

For Time Complexity, the main procedure is to:

1. draw the routine diagram like function calls then summaries the number of function calls without thinking about the time complexity of any detail operations.

For a [howSum Problem](https://youtu.be/oBt53YbR9Kk?t=5371), as it uses recursion, the routine diagram is a tree.

```js
const howSum = (targetSum, numbers) => {
    if (targetSum === 0) return [];
    if (targetSum < 0) return null;

    for (let num of numbers) {
        const remainder = targetSum - num;
        const remainderResult = howSum(remainder, numbers);
        if (remainderResult !== null) {
            // costly operation
            return [...remainderResult, num];
        }
    }

    return null;
}
```

![how_sum_tree](Assets/Screenshot%202023-09-07%20at%2000.29.54.png)

In the **worst case**, (remember when analyzing the time complexity we always consider the worst case), the numbers are all `1`s, which means, we have to have `targetSum / 1` numbers of recursions, which also means the height of the tree would be `targetSum`. Also, in another worst case, we find every number inside `numbers` gives us a branch (`targetSum < 0` never gives a early return). Hence, the tree would be $n^m$ nodes, with each node a single function call, the time complexity is $O(n^m)$

![how_sum_time_complexity](Assets/Screenshot%202023-09-07%20at%2000.36.04.png)

2. Consider for any costly operations in each function call.

In the above code snippet, `[...remainderResult, num]` is gonna copy the entire the `remainderResult` into a new array, which in the worst case contains, the `targetSum` numbers of element.

Hence, the overall time complexity will be $O(n^m * m )$


### Space Complexity

For space complexity, the procedure will be quite similar to Time complexity analysis. 

1. Analysis the function stacks only without looking at the detail allocations.

For simpler Fib Problem, the routine tree is similar to the howSum problem discussed above.

![fib_tree](Assets/Screenshot%202023-09-07%20at%2000.46.30.png)

It's easy to fall in the trap to think the space complexity would the $O(n^m)$ too as the time complexity. However, when the recursion reaches the longest leaf, it will return and release its function stack. Hence, the resources the function call allocates are set free before the next recursion call. Hence, in the worst case, the **space complexity depends only on the height of the tree.**, which is $O(m)$.

2. Analyze if some variable in the function stack that can possibly be larger than the above.

In some memoization optimizations, we may hold a variable that stores all the results we previously calculated, and that variable can will be a singleton among all recursive calls and it dominates the space complexity of function stack complexity analyzed in the first step. In that case, the space complexity would be the size of the memoization variable.


## [Floyd's Algorithm to find the start of a cycle](https://www.youtube.com/watch?v=wjYnzkAhcNk)

This leads to the problem of [Leetcode 287](https://leetcode.com/problems/find-the-duplicate-number/description/?envType=daily-question&envId=2023-09-19)