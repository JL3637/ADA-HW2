using namespace std;
#include<stdio.h>
#include<bits/stdc++.h>

long long pre_table[301][301];
long long cur_table[301][301];

long long plus123(long long a, long long b, long long m){
    return (a + b >= m ? a + b - m : a + b);
}

void modify_table(int n, int k, int *mod, long long m){
    for(int x = 0; x < n; x++){
        if(*mod == 0){
            for(int i = 0; i < k; i++){
                for(int j = i; j < k; j++){
                    cur_table[i][j] = 0;
                }
            }
            int sum = 0;
            for(int i = 0; i < k; i++){
                sum = 0;
                for(int j = i; j < k; j++){
                    sum = plus123(sum, pre_table[i][j], m);
                    cur_table[i][j] = plus123(sum, cur_table[i][j], m);
                }
            }
            for(int j = 0; j < k; j++){
                sum = 0;
                for(int i = 0; i <= j; i++){
                    cur_table[i][j] = plus123(sum, cur_table[i][j], m);
                    sum = plus123(sum, pre_table[i][j], m);
                }
            }
            *mod = 1;
        }
        else if(*mod == 1){
            for(int i = 0; i < k; i++){
                for(int j = i; j < k; j++){
                    pre_table[i][j] = 0;
                }
            }
            int sum = 0;
            for(int i = 0; i < k; i++){
                sum = 0;
                for(int j = i; j < k; j++){
                    sum = plus123(sum, cur_table[i][j], m);
                    pre_table[i][j] = plus123(sum, pre_table[i][j], m);
                }
            }
            for(int j = 0; j < k; j++){
                sum = 0;
                for(int i = 0; i <= j; i++){
                    pre_table[i][j] = plus123(sum, pre_table[i][j], m);
                    sum = plus123(sum, cur_table[i][j], m);
                }
            }
            *mod = 0;
        }
    }
}

void print_ans(int k, long long m, int w){
    if(w == 1){
        long long sum = 0;
        for(int i = 0; i < k; i++){
            sum = plus123(sum, pre_table[i][k-1], m);
        }
        printf("%lld", sum);
        return;
    }
    else{
        long long sum = 0;
        for(int i = 0; i < k; i++){
            sum = plus123(sum, cur_table[i][k-1], m);
        }
        printf("%lld", sum);
        return;
    }
}

int main(){
    int n, k;
    long long m;
    scanf("%d%d%lld", &n, &k, &m);

    for(int i = 0; i <= k; i++){
        for(int j = 0; j < i; j++){
            pre_table[i][j] = 0;
            cur_table[i][j] = 0;
        }
        for(int j = i; j <= k; j++){
            pre_table[i][j] = 1;
            cur_table[i][j] = 0;
        }
    }
    int mod = 0;
    modify_table(n, k+1, &mod, m);
    if(n % 2 == 1){
        print_ans(k+1, m, n % 2);
    }
    else{
        print_ans(k+1, m, n % 2);
    }

    return 0;
}