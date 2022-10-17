using namespace std;
#include<stdio.h>
#include<bits/stdc++.h>

typedef struct People{
    long long a;
    long long b;
}people;

typedef struct Pasta_Time{
    long long m;
    long long finish_time;
    long long remain_time;
}pasta_time;

bool cmp(people x, people y){
    return x.b > y.b;
}

bool cmp2(pasta_time x, pasta_time y){
    return  (x.m * y.finish_time) > (y.m * x.finish_time);
}

void count_time(people *costomer, pasta_time *dinner_time, int group_id){
    dinner_time[group_id].finish_time = 0;
    dinner_time[group_id].remain_time = 0;
    for(int i = 0; i < dinner_time[group_id].m; i++){

        dinner_time[group_id].finish_time += costomer[i].a;

        if(costomer[i].a + costomer[i].b > dinner_time[group_id].remain_time){
            dinner_time[group_id].remain_time = costomer[i].b;
        }
        else{
            dinner_time[group_id].remain_time = dinner_time[group_id].remain_time - costomer[i].a;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    pasta_time *dinner_time = (pasta_time *)malloc(sizeof(pasta_time) * n);

    for(int i = 0; i < n; i++){
        scanf("%lld", &dinner_time[i].m);
        people *costomer = (people *)malloc(sizeof(people) * dinner_time[i].m);
        for(int j = 0; j < dinner_time[i].m; j++){
            scanf("%lld%lld", &costomer[j].a, &costomer[j].b);
        }
        sort(costomer, costomer + dinner_time[i].m, cmp);
        count_time(costomer, dinner_time, i);
    }

    sort(dinner_time, dinner_time + n, cmp2);

    /*for(int i = 0; i < n; i++){
        printf("%lld %lld %lld\n", dinner_time[i].m, dinner_time[i].finish_time, dinner_time[i].remain_time);
    }*/

    long long ans = 0;
    long long prepare_time = 0;

    for(int i = 0; i < n; i++){
        prepare_time += dinner_time[i].finish_time;
        ans += (prepare_time + dinner_time[i].remain_time) * dinner_time[i].m;
    }
    
    printf("%lld", ans);

    return 0;
}