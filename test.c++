using namespace std;
#include<stdio.h>
#include<bits/stdc++.h>

int main(){
    long long n, k, m;
    scanf("%lld%lld%lld", &n, &k, &m);

    long long ans = (1 + (n + 1) * n / 2) % m;
    printf("%lld", ans);

    return 0;
}