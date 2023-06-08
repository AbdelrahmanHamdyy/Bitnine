#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ll;

// Recursive Way
ll recursive(int n) {
  if (n <= 2 && n >= 0) {
    return n;
  }

  return recursive(n - 2) + recursive(n - 3);
}

// Dynamic Programming (Top Down Approach)
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

// Swapping between three variables
ll threeVariables(int n) {
  if (n <= 2 && n >= 0) {
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

// Dynamic Programming (Bottom Up Approach)
ll bottomUp(int n) {
  int *dp = (int *)malloc(sizeof(int) * (n + 1));

  dp[0] = 0, dp[1] = 1, dp[2] = 2;

  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 2] + dp[i - 3];
  }

  return dp[n];
}

int main() {
  int memo[500] = {};
  int n;

  printf("F(n) = F(n-3) + F(n -2)\n");
  printf("n: ");
  scanf("%d", &n);

  printf("----------------------------------\n");
  printf("Iterative: %llu\n", threeVariables(n));
  printf("Recursive: %llu\n", recursive(n));
  printf("(DP) Top Down: %llu\n", topDown(n, memo));
  printf("(DP) Bottom Up: %llu\n", bottomUp(n));

  return 0;
}