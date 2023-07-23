# Non-Coding Problems
## N1
First, note that the algorithm only picks the $k$ th classroom if the $1$ st until the $k - 1$ st classroom is unavailable. When the algorithm picks the $k$ th classroom, we know that the depth must be at least $k$ (i.e., $d \ge k$).

Suppose that $n > d$. Then that means that there is some point at which the first $n$ classrooms are occupied. In other words, $d \ge n$. However, this implies that $d > d$, which is a contradiction. Therefore, the assumption that $n > d$ is wrong, and so $d \ge n$ $\blacksquare$.

## N2
![N2 Counterexample](assets/n2.png)

## N3a
$\frac{11}{28}$

The greedy algorithm outputs $\frac{1}{3} + \frac{1}{17} + \frac{1}{1428}$, but the correct answer is $\frac{1}{4} + \frac{1}{7}$

## N4a
Suppose $C'$ is some multiset of coins representing a solution. Let $C$ be the greedy solution.

From the problem statement, since $c_{i + 1} > c_{i}$, and $c_{i + 1} = kc_{i}$ for some positive integer $k$, $k = 2$. Thus, $c_{i + 1} \ge 2c_{i}$

Note that we can exchange $\frac{c_{i + 1}}{c_{i}}$ instances of $c_{i}$ to one instance of $c_{i + 1}$ in $C$ and get a more optimal solution $C'$.

After doing this, let the new number of $c_{i}$ coins be $a_{i}$. Due to the way $C'$ was constructed, $a_{i} < \frac{c_{i + 1}}{c_{i}}$. To show this, suppose $a_{i} \ge \frac{c_{i + 1}}{c_{i}}$. If this is the case, then some of the $c_i$ coins could still have been further exchanged, which contradicts the way we constructed $C'$.

If $a_{i} < \frac{c_{i + 1}}{c_{i}}$, then $a_i c_i < c_{i + 1}$. Clearly, $a_1 c_1 < c_2$, so we cannot exchange any of the coins smaller than $c_2$ into more instances of $c_2$. Suppose we have $\sum_{i = 1}^{k - 1} a_i c_i < c_k$, let us show that $\sum_{i = 1}^{k} a_i c_i < c_{k + 1}$.

$\sum_{i = 1}^{k} a_i c_i = a_k c_k + \sum_{i = 1}^{k - 1} a_i c_i\\ 
< a_k c_k + c_k = (a_k + 1) c_k \le \frac{c_{k + 1}}{c_k} \cdot c_k < c_{k + 1}$.

Thus, we have $\sum_{i = 1}^{k} a_i c_i < c_{k + 1}$ for all $1 \le k \le n - 1$. This implies that, in $C'$, as many instances of $c_n$ were taken, and then as many instances of $c_{n - 1}$ were taken, and so on. However, this is simply how we constructed our greedy solution, so our greedy solution must therefore be optimal.

## N4b
The denominations $c = 1, 2, 3$ work.

Let $f(n)$ be the minimum number of coins needed to form a sum of $n$, with $f(0) = 0$ and $f(1) = f(2) = 1$.

We know that $f(n) = \min(f(n - 3), f(n - 2), f(n - 1)) + 1$. Thus, $f(n) = \left\lfloor \frac{n - 1}{3} \right\rfloor + 1$.

The greedy algorithm would take $\left\lfloor \frac{n - 1}{3} \right\rfloor$ coins of value $3$, and then take a $1$, $2$, or another $3$ depending on the left-over. Thus, the greedy algorithm would take a total of $\left\lfloor \frac{n - 1}{3} \right\rfloor + 1 = f(n)$ coins, thus proving its optimality.