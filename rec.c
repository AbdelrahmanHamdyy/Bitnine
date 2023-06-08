#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ll;

/*(1) Recursive Way
This is considered the simplest approach to this recurrence but is it the most
efficient? The recursion stops when we hit the base case which checks for the
current index of the recurrence if it has reached the initial values which are
F(0), F(1), and F(2) and simply returns their values 0, 1, 2 respectively. The
recursion is called on n-2 & n-3 and then they are summed together according to
the recurrence F(n) = F(n - 2) + F(n - 3). The recursive approach the worst
solution to this and here's why:

Time Complexity: O(2^N)- This is because the function makes two recursive calls
for each input value greater than 2. Each of these recursive calls also makes
two recursive calls, and so on. Therefore, the total number of function calls
doubles with each increase in the input value, resulting in an exponential
growth in the number of function calls.

Memory Complexity: O(N) - The amount of
memory used in the recursive call stack is proportional to the size of the input
value n.
*/
ll recursive(int n) {
  if (n <= 2) {
    return n;
  }

  return recursive(n - 2) + recursive(n - 3);
}

/* (2) Dynamic Programming (Top Down approach)
The function takes two arguments: an integer n, which represents the input
value, and an array memo, which is used to store and retrieve previously
computed values to avoid redundant computations.

The function first checks if the value for the given input n is already stored
in the memo array. If so, it simply returns the stored value without further
computation. This check is done to avoid redundant computations, which can
significantly improve the time complexity of the algorithm.

If the value for the given input n is not already stored in the memo array, the
function proceeds to compute it by recursively calling itself with n-2 and n-3
as inputs. The base case for the recursion is when n is less than or equal to 2,
in which case the function returns n.

After computing the value for the given input n, the function stores it in the
memo array for future use, so that it can be retrieved quickly if needed again
later.

By using memoization to avoid redundant computations, the time complexity of the
dynamic programming approach is significantly reduced compared to the previous
recursive approach. The time complexity of this implementation is O(n), which is
much better than the exponential time complexity of the previous recursive
implementation.

Time Complexity: O(N)
Memory Complexity: O(N)
*/
ll topDown(int n, int memo[]) {
  if (memo[n] != 0)
    return memo[n];

  int result;
  if (n <= 2) {
    result = n;
  } else {
    result = topDown(n - 2, memo) + topDown(n - 3, memo);
  }

  memo[n] = result;

  return result;
}

/* (3) Dynamic Programming (Bottom Up Approach)
We first define the dp array of size n + 1 and initialize the first 3 locations
as given in the recurrence. The value of dp[i] is computed as dp[i - 2] + dp[i -
3] which corresponds to the recurrence F(n) = F(n - 2) + F(n - 3) but in an
incremental approach. At the end, the value of dp[n] is the value F(n) and it's
simply returned as the result.

Time Complexity: O(N)
Memory Complexity: O(N)
*/
ll bottomUp(int n) {
  int *dp = (int *)malloc(sizeof(int) * (n + 1));

  dp[0] = 0, dp[1] = 1, dp[2] = 2;

  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 2] + dp[i - 3];
  }

  return dp[n];
}

/* (4) Swapping between three variables (Iterative)
In this method, we basically have 3 variables that define the initial
values from 0 to 2 for this recurrence. A 4th variable is initialized as zero
which represents the current value in the loop and then we swap between the 4
variables at the end. The main advantage of this method is how we managed to
save up memory by only using 3 variables instead of a whole array of size n.

Time Complexity: O(N)
Memory Complexity: O(1)
*/
ll threeVariables(int n) {
  if (n <= 2) {
    return n;
  }
  ll f0 = 0, f1 = 1, f2 = 2;
  ll fn = 0; // Current value

  for (int i = 3; i <= n; i++) {
    fn = f0 + f1;

    f0 = f1;
    f1 = f2;
    f2 = fn;
  }
  return fn;
}

int main() {
  int memo[500] = {};
  int n;

  printf("F(n) = F(n-3) + F(n -2)\n");
  do {
    printf("n: ");
    scanf("%d", &n);
    if (n < 0) {
      printf("The value of n must be greater than or equal to zero\n");
    }
  } while (n < 0);

  printf("----------------------------------\n");
  printf("Iterative: %llu\n", threeVariables(n));
  printf("Recursive: %llu\n", recursive(n));
  printf("(DP) Top Down: %llu\n", topDown(n, memo));
  printf("(DP) Bottom Up: %llu\n", bottomUp(n));

  return 0;
}