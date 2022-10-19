//using namespace std;
#include<stdio.h>
#include<stdlib.h>
//#include<bits/stdc++.h>

long long plus123(long long a, long long b, long long m){
    return (a + b >= m ? a + b - m : a + b);
}

long long num_difarr(int k, long long table[k][k], int a, int b, long long m){
    long long sum = -table[a][b];
    for(int i = a; i >= 0; i--){
        sum = plus123(sum, table[i][b], m);
    }
    for(int i = b; i >= 0; i--){
        sum = plus123(sum, table[a][i], m);
    }
    return sum;
}

void modify_table(int n, int k, long long pre_table[k][k], long long cur_table[k][k], int *mod, long long m){
    for(int i = 0; i < n; i++){
        if(*mod == 0){
            for(int j = 0; j < k; j++){
                for(int x = j; x < k; x++){
                    cur_table[j][x] = num_difarr(k, pre_table, j, x, m);
                }
            }
            *mod = 1;
        }
        else if(*mod == 1){
            for(int j = 0; j < k; j++){
                for(int x = j; x < k; x++){
                    pre_table[j][x] = num_difarr(k, cur_table, j, x, m);
                }
            }
            *mod = 0;
        }
    }
}

void print_ans(int k, long long table[k][k], long long m){
    long long sum = 0;
    for(int i = 0; i < k; i++){
        sum = plus123(sum, table[i][k-1], m);
    }
    printf("%lld", sum);
}

int main(){
    int n, k;
    long long m;
    scanf("%d%d%lld", &n, &k, &m);

    long long pre_table[k+1][k+1];
    long long cur_table[k+1][k+1];
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
    modify_table(n, k+1, pre_table, cur_table, &mod, m);
    if(n % 2 == 1){
        print_ans(k+1, pre_table, m);
    }
    else{
        print_ans(k+1, cur_table, m);
    }

    return 0;
}