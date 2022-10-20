#include <bits/stdc++.h>
using namespace std;

void encode(char *s, int *arr){
    for(int i = 0; i < strlen(s); i++){
        arr[i] = s[i];
    }
}

void decode(int len, int *arr){
    for(int i = 0; i < len; i++){
        printf("%c", arr[i]);
    }
}

void segAdd(vector<int>& seg, int start, int end, int pos, int curr){
    if(pos < start || pos > end){
        return;
    }
    if(start == end){
        seg[curr] = 1;
        return;
    }

    int mid = (start + end) / 2;
    segAdd(seg, start, mid, pos, 2 * curr + 1);
    segAdd(seg, mid + 1, end, pos, 2 * curr + 2);

    seg[curr] = seg[2 * curr + 1] + seg[2 * curr + 2];
 
    return;
}

int segFind(vector<int>& seg, int pos_start, int pos_end, int start, int end, int curr){
    if(pos_end < start || pos_start > end){
        return 0;
    }
    if(pos_start <= start && pos_end >= end){
        return seg[curr];
    }

    int mid = (start + end) / 2;
    int left = segFind(seg, pos_start, pos_end, start, mid, 2 * curr + 1);
    int right = segFind(seg, pos_start, pos_end, mid + 1, end, 2 * curr + 2);
    return left + right;
}

void min_by_k_Swaps(int *arr, int n, int k, int *result){
    vector<int> seg((2 * (int)pow(2,(int)(ceil(log2(n)))) - 1), 0);
    unordered_map<int, list<int> > m;
    for(int i = 0; i < n; i++){
        m[arr[i]].push_back(i);
    }
    int result_top = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= 122; j++){
            if(m[j].size() != 0){
                int original_pos= m[j].front();
                int shift = segFind(seg, original_pos, n - 1, 0, n - 1, 0);
                int new_pos = original_pos + shift - i;
 
                if (new_pos <= k){
                    k -= new_pos;
                    segAdd(seg, 0, n - 1, original_pos, 0);
                    result[result_top] = j;
                    result_top++;
                    m[j].pop_front();
                    break;
                }
            }
        }
    }
    return;
}

int main(){
    char s[500001];
    long long k;
    scanf("%s%lld", s, &k);
    int arr[strlen(s)];
    encode(s, arr);
    int result[strlen(s)];
    min_by_k_Swaps(arr, strlen(s), k, result);
    decode(strlen(s), result);

    return 0;
}