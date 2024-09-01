#include <bits/stdc++.h>
using namespace std;

template<class T> struct LazySegmentTree {
    vector<T> st;
    vector<T> lazy;
    int n;
    T identity_element;
    T identity_update;
    LazySegmentTree(int n, T identity_element, T identity_update) {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4*n, identity_element);
        lazy.assign(4*n, identity_update);
    }
    T combine(T l, T r) { // adjust for query type
        return l+r;
        // return max(l, r);
        // return min(l, r);
    }
    T apply(T curr, T upd, int tl, int tr) { // adjust for update/query type
        T ans = curr + (tr-tl+1)*upd; // range increment, range sum
        // T ans = curr + upd; // range increment, range max/min
        // T ans = (tr-tl+1)*upd; // range set, range sum
        // T ans = upd; // range set, range max/min
        return ans;
    }
    T combineUpdate(T old_upd, T new_upd, int tl, int tr) { // adjust for update
        T ans = old_upd;
        ans+=new_upd; // range increment
        // ans=new_upd; // range set
        return ans;
    }
    void buildUtil(int v, int tl, int tr, vector<T>&a) {
        if(tl == tr) {
            st[v] = a[tl];
            return;
        }
        int tm = (tl + tr)>>1;
        buildUtil(2*v + 1, tl, tm,a);
        buildUtil(2*v + 2,tm+1,tr,a);
        st[v] = combine(st[2*v + 1], st[2*v + 2]);
    }
    void push_down(int v, int tl, int tr) {
        if(lazy[v] == identity_update)return;
        st[v] = apply(st[v], lazy[v], tl, tr);
        if(2*v + 2 < 4*n) {
            int tm = (tl + tr)>>1;
            lazy[2*v + 1] = combineUpdate(lazy[2*v+1], lazy[v], tl, tm);
            lazy[2*v + 2] = combineUpdate(lazy[2*v+2], lazy[v], tm+1,tr);            
        }
        lazy[v] = identity_update;
    }
    T queryUtil(int v, int tl, int tr, int l, int r) {
        push_down(v,tl,tr);
        if(l > r)return identity_element;
        if(tr < l or tl > r) {
            return identity_element;
        }
        if(l <= tl and r >= tr) {
            return st[v];
        }
        int tm = (tl + tr)>>1;
        return combine(queryUtil(2*v+1,tl,tm,l,r), queryUtil(2*v+2,tm+1,tr,l,r));
    }
    void updateUtil(int v, int tl, int tr, int l, int r, T upd) {
        push_down(v,tl,tr); 
        if(tr < l or tl > r)return;
        if(tl >=l and tr <=r) {
            lazy[v] = combineUpdate(lazy[v],upd,tl,tr);
            push_down(v,tl,tr);
        }
        else {
            int tm = (tl + tr)>>1;
            updateUtil(2*v+1,tl,tm,l,r,upd);
            updateUtil(2*v+2,tm+1,tr,l,r,upd);
            st[v] = combine(st[2*v + 1], st[2*v+2]);
        }
    }
    void build(vector<T>& a) {
        assert(a.size() == n);
        buildUtil(0,0,n-1,a);
    }
    T query(int l, int r) {
        return queryUtil(0,0,n-1,l,r);
    }
    void update(int l,int r, T upd) {
        updateUtil(0,0,n-1,l,r,upd);
    }
};

int main() {
	int tc; cin >> tc;
	while(tc--) {
		int n, q;
		cin >> n >> q;
	    LazySegmentTree<long long> segtree(n, 0, 0);
	    while(q--) {
	        int x; cin >> x;
	        if(x==0) {
	            int a, b, u;
	            cin >> a >> b >> u;
                a--, b--;
	            segtree.update(a, b, u);
	        }
	        else {
	            int a, b;
	            cin >> a >> b;
                a--, b--;
	            cout << segtree.query(a, b) << "\n";
	        }
	    }
	}
}
