template <class T> class SegmentTree {
  	private:
	T comb(T a, T b) {
		return a + b;
	}
	const T DEFAULT = 0;
	vector<T> segtree;
	int len;

  	public:
	SegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}
	void set(int ind, T val) { // 0 indexed
		assert(0 <= ind && ind < len);
		ind += len;
		segtree[ind] = val;
		for (; ind > 1; ind /= 2) {
			segtree[ind >> 1] = comb(segtree[ind], segtree[ind ^ 1]);
		}
	}
	T range_query(int start, int end) { // [start, end)
		assert(0 <= start && start < len && 0 < end && end <= len);
		T sum = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if ((start & 1) != 0) { sum = comb(sum, segtree[start++]); }
			if ((end & 1) != 0) { sum = comb(sum, segtree[--end]); }
		}
		return sum;
	}
};

int main() {
	int arr_len;
	int query_num;
	cin >> arr_len >> query_num;
	SegmentTree<long long> segtree(arr_len);
	for (int i = 0; i < arr_len; i++) {
		int n;
		cin >> n;
		segtree.set(i, n);
	}
	for (int q = 0; q < query_num; q++) {
		int type;
		cin >> type;
		if (type == 1) {
			int ind;
			int val;
			cin >> ind >> val;
			segtree.set(ind - 1, val);
		} else if (type == 2) {
			int start;
			int end;
			cin >> start >> end;
			cout << segtree.range_query(start - 1, end) << '\n';
		}
	}
}
