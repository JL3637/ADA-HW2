#include <bits/stdc++.h>
using namespace std;

int main(){
    int dp[10];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for(int i = 3; i < 10; i++){
        dp[i] = dp[i-1] + (i - 1)*dp[i-2];
    }
    for(int i = 0; i < 10; i++){
        printf("%d\n", dp[i]);
    }

    return 0;
}