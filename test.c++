using namespace std;
#include<stdio.h>
#include<bits/stdc++.h>

typedef struct People{
    long long a;
    long long b;
}people;

typedef struct Pasta_Time{
    long long finish_time;
    long long remain_time;
}pasta_time;

bool cmp(people x, people y){
    if(x.b != y.b){
        return x.b > y.b;
    }
    else{
        return y.a > x.a;
    }
}

bool cmp2(pasta_time x, pasta_time y){
    return y.finish_time > x.finish_time;
}

void count_time(people *costomer, pasta_time *dinner_time, long long *m, int group_id){
    dinner_time[group_id].finish_time = 0;
    dinner_time[group_id].remain_time = 0;
    for(int i = 0; i < m[group_id]; i++){

        dinner_time[group_id].finish_time += costomer[i].a;

        if(costomer[i].a + costomer[i].b > dinner_time[group_id].remain_time){
            dinner_time[group_id].remain_time = costomer[i].b;
        }
        else{
            dinner_time[group_id].remain_time = dinner_time[group_id].remain_time - (costomer[i].a + costomer[i].b);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    long long *m = (long long *)malloc(sizeof(long long) * n);
    pasta_time *dinner_time = (pasta_time *)malloc(sizeof(pasta_time) * n);

    for(int i = 0; i < n; i++){
        scanf("%lld", &m[i]);
        people *costomer = (people *)malloc(sizeof(people) * m[i]);
        for(int j = 0; j < m[i]; j++){
            scanf("%lld%lld", &costomer[j].a, &costomer[j].b);
        }
        sort(costomer, costomer + m[i], cmp);
        /*for(int i = 0; i < m[0]; i++){
            printf("%d %d ", costomer[i].a, costomer[i].b);
        }*/
        count_time(costomer, dinner_time, m, i);
        /*printf("\n%d %d", dinner_time[i].finish_time, dinner_time[i].remain_time);*/
    }

    sort(dinner_time, dinner_time + n, cmp2);

    long long ans = 0;
    long long prepare_time = 0;

    for(int i = 0; i < n; i++){
        prepare_time += dinner_time[i].finish_time;
        ans += (prepare_time + dinner_time[i].remain_time) * m[i];
    }
    
    printf("%lld", ans);
    

    return 0;
}