#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n; // array size
    vector<int> arr(n);
    vector<int> pre(n);
    //input and precompute
    cin >> arr[0];
    pre[0] = arr[0];
    for(int i=1; i<n;i++){
        cin >> arr[i];
        pre[i] = pre[i-1]+arr[i];
    }

    //answer queries
    int l,r;
    cin >> l >> r;
    // convert to 0 based idx
    l--;
    r--;
    if(l==0){
        cout << pre[l];
    } else {
        cout << pre[r] - pre[l-1];
    }
    
}