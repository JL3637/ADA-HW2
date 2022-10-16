using namespace std;
#include<stdio.h>
#include<bits/stdc++.h>

long long find_maximum_subarray(int *arr, int l, int r){
    long long max = arr[l];
    long long sum = 0;
    for(int i = l; i <= r; i++){
        sum += arr[i];
        if(sum > max){
            max = sum;
        }
        if(sum < 0){
            sum = 0;
        }
    }
    return max * (r - l + 1);
}

long long find_min_sleep(long long **m, int *a, int k_id, int n_id, long long **table){
    long long min = m[k_id-1][n_id-1] + a[n_id];
    for(int i = n_id; i >= k_id; i--){
        long long x = m[k_id-1][i-1] + table[i][n_id];
        if(min > x){
            min = x;
        }
    }
    return min;
}

void modify_table(long long **table, int *a, int n){
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            table[i][j] = find_maximum_subarray(a, i, j);
        }
    }
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    int *a = (int *)malloc(sizeof(int) * (n+1));
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    long long **m = (long long **)malloc(sizeof(long long*) * (k+1));
    for(int i = 1; i <= k; i++){
        m[i] = (long long *)malloc(sizeof(long long) * (n+1));
    }
    long long **table = (long long **)malloc(sizeof(long long*) * (n + 1));
    for(int i = 1; i <= n; i++){
        table[i] = (long long *)malloc(sizeof(long long) * (n + 1));
    }
    modify_table(table, a, n);

    for(int i = 1; i <= n; i++){
        m[1][i] = table[1][i];
    }
    for(int i = 2; i <= k; i++){
        for(int j = i; j <= n; j++){
            m[i][j] = find_min_sleep(m, a, i, j, table);
        }
    }
    /*for(int i = 1; i <= k; i++){
        for(int j = i; j <= n; j++){
            printf("%lld ", m[i][j]);
        }
        printf("\n");
    }*/

    printf("%lld", m[k][n]);


    return 0;
}
