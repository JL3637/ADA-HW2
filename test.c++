#include <bits/stdc++.h>
using namespace std;

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

string min_by_k_Swaps(string s, long long k){
    int n = s.size();
    vector<int> seg((2 * (int)pow(2,(int)(ceil(log2(n)))) - 1), 0);
    unordered_map<int, list<int> > m;
    for(int i = 0; i < n; i++){
        m[s[i]].push_back(i);
    }
    string result = "";
    for(int i = 0; i < n; i++){
        for(int j = '0'; j <= 'z'; j++){
            if(j == '9'+1){
                j = 'A'-1;
                continue;
            }
            if(j == 'Z'+1){
                j = 'a'-1;
                continue;
            }
            if(m[j].size() != 0){
                int original_pos= m[j].front();
                int shift = segFind(seg, original_pos, n - 1, 0, n - 1, 0);
                int new_pos = original_pos + shift - i;
 
                if (new_pos <= k){
                    k -= new_pos;
                    segAdd(seg, 0, n - 1, original_pos, 0);
                    result.push_back(j);
                    m[j].pop_front();
                    break;
                }
            }
        }
    }
    return result;
}

int main(){
    string s;
    long long k;
    cin >> s >> k;
    cout << min_by_k_Swaps(s, k) << endl;

    return 0;
}