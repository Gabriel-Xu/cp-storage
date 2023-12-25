#include <bits/stdc++.h>
using namespace std;

template<class T> struct LazySegmentTree {
    int len;
    vector<T> tree, lazy;
    const T TREE_DEFAULT = 0;
    const T LAZY_DEFAULT = 0;
    // for queries
    T tree_merge(T a, T b) {
        return a+b;
    }
    // for updates
    T lazy_merge(T a, T b) {
        return a+b;
    }
    void lazy_merged(T &a, T b) { a = lazy_merge(a, b); }
    LazySegmentTree(int n) {
        len = 1; while (len < n) len *= 2;
        tree.resize(2 * len, TREE_DEFAULT);
        lazy.resize(2 * len, LAZY_DEFAULT);
    }
    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1) return;
        lazy_merged(lazy[2 * x + 1], lazy[x]);
        lazy_merged(lazy[2 * x + 2], lazy[x]);
        lazy_merged(tree[2 * x + 1], lazy[x]);
        lazy_merged(tree[2 * x + 2], lazy[x]);
        lazy[x] = LAZY_DEFAULT;
    }
    void add(int l, int r, T v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            lazy_merged(lazy[x], v);
            lazy_merged(tree[x], v);
            return;
        }
        int m = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);
        tree[x] = tree_merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    T query(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return TREE_DEFAULT;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        T left = query(l, r, 2 * x + 1, lx, m);
        T right = query(l, r, 2 * x + 2, m, rx);
        return tree_merge(left, right);
    }
    void update(int l, int r, T v) { add(l, r, v, 0, 0, len); }
    T query(int l, int r) { return query(l, r, 0, 0, len); }
};

int main() {
	int n, q;
	cin >> n >> q;
    LazySegmentTree<long long> segtree(n);
    for(int i=0; i<n; i++) {
        int x; cin >> x;
        segtree.update(i,i+1,x);
    }
    while(q--) {
        int x; cin >> x;
        if(x==1) {
            int a, b, u;
            cin >> a >> b >> u;
            a--, b--;
            segtree.update(a, b+1, u);
        }
        else {
            int k;
            cin >> k;
            k--;
            cout << segtree.query(k, k+1) << "\n";
        }
    }
}
