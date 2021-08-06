#include <iostream>

template <typename T>
class seg_tree {
private:
	T* tree, * arr;
	int size, cap;
	T(*oper)(T, T);

public:
	seg_tree() {/* cout << "init1\n";*/ }
	seg_tree(int s, T(*fun)(T, T)) : size(s), cap(s * 4), tree(new T[s * 4 + 1]), arr(new T[s + 1]), oper(fun) { /*cout << "init2\n";*/ }
	~seg_tree() {
		/*cout << "delete\n";*/
		//delete[] tree;
		//delete[] arr;
	}

	void init(int now, int l, int r) {
		if (l == r) {
			tree[now] = arr[l];
			return;
		}
		int mid = (l + r) / 2;
		init(now * 2, l, mid);
		init(now * 2 + 1, mid + 1, r);
		tree[now] = oper(tree[now * 2], tree[now * 2 + 1]);
	}

	void init() {
		memset(arr, 0, sizeof(T) * (size + 1));
		memset(tree, 0, sizeof(T) * (cap + 1));
	}

	void get_init() {
		for (int i = 1; i <= size; i++)
			std::cin >> arr[i];
		init(1, 1, size);
	}

	void init(T* s, T* e) {
		for (int i = 0; s + i != e; i++)
			arr[i + 1] = s[i];
		init(1, 1, size);
	}

	/*void init(vector<T>::iterator s, vector<T>::iterator e) {
		for (int i = 0; s != e; s++, i++)
			arr[i] = *s;
		init(1, 1, size);
	}*/

	void update(int now, int l, int r, int idx, T v) {
		if (idx < l or r < idx)
			return;
		if (l == r) {
			tree[now] = v;
			return;
		}
		int mid = (l + r) / 2;
		update(now * 2, l, mid, idx, v);
		update(now * 2 + 1, mid + 1, r, idx, v);
		tree[now] = oper(tree[now * 2], tree[now * 2 + 1]);
	}

	void update(int idx, T v) {
		update(1, 1, size, idx, v);
	}

	void update(long long idx, T v) {
		update(1, 1, size, (int)idx, v);
	}

	T quary(int now, int nowl, int nowr, int l, int r) {
		if (l <= nowl and nowr <= r)
			return tree[now];
		int mid = (nowl + nowr) / 2;
		if (mid < l)
			return quary(now * 2 + 1, mid + 1, nowr, l, r);
		if (r < mid + 1)
			return quary(now * 2, nowl, mid, l, r);
		T ret = oper(quary(now * 2, nowl, mid, l, r), quary(now * 2 + 1, mid + 1, nowr, l, r));
		return ret;
	}

	T quary(int l, int r) {
		return quary(1, 1, size, l, r);
	}

	T quary(long long l, long long r) {
		return quary(1, 1, size, (int)l, (int)r);
	}
};