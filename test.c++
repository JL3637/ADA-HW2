#include <bits/stdc++.h>
using namespace std;

string min_by_k_Swaps(string s, long long k){
    int n = s.size();
    string res;
    res.reserve(n);
    vector<int> q(62, n);
    for(int i = 0; i < n; i++){
        int d;
        if(s[i] <= '9'){
            d = s[i] - '0';
        }
        else if(s[i] <= 'Z'){
            d = s[i] - 'A' + 10;
        }
        else if(s[i] <= 'z'){
            d = s[i] - 'a' + 36;
        }
        if(q[d] == n){
            q[d] = i;
        }
    }
    vector<bool> used(n);
    vector<int> q_used(62);
    for(int i = 0; i < n; i++){
        for(int d = 0; d < 62; d++){
            if(q[d] == n){
                continue;
            }
            int c = q[d] - q_used[d];
            if(c <= k){
                k -= c;
                if(d <= 9){
                    res.push_back('0' + d);
                }
                else if(d <= 35){
                    res.push_back('A' + d - 10);
                }
                else if(d <= 61){
                    res.push_back('a' + d - 36);
                }
                used[q[d]] = true;
                for(int d1 = 0; d1 < 62; d1++){
                    if(q[d1] > q[d]){
                        q_used[d1]++;
                    }
                }
                while(q[d] < n){
                    if(used[q[d]]){
                        ++q_used[d];
                    }
                    if(d <= 9){
                        if(s[++q[d]] == '0' + d){
                            break;
                        }
                    }
                    else if(d <= 35){
                        if(s[++q[d]] == 'A' + d - 10){
                            break;
                        }
                    }
                    else if(d <= 61){
                        if(s[++q[d]] == 'a' + d - 36){
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    return res;
}

int main(){
    string s;
    long long k;
    cin >> s >> k;
    cout << min_by_k_Swaps(s, k) << endl;

    return 0;
}