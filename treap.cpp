mt19937 rng;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define data send_help

struct data {
	
	data() {}
};

struct node {
	
	node *left, *right;
	int weight, size;
	
	data me, sub;
	
	node() : left(NULL), right(NULL), weight(rng()), size(1) {}
	
} pool[MAXN];

int size(node *tr) {
	if (tr)
		return tr->size;
	return 0;
}

node *new_node(data d) {
	static int nt = 0;
	assert(nt < MAXN);
	pool[nt].me = pool[nt].sub = d;
	return &pool[nt++];
}

void recalc(node *tr) {
	if (!tr)
		return;
	
	
}

pair<node *, node *> split(node *tr, int k) {
	if (!tr) {
		assert(k == 0);
		return {NULL, NULL};
	}
	if (size(tr->left) >= k) {
		auto [l, r] = split(tr->left, k);
		tr->left = r;
		recalc(tr);
		return {l, tr};
	} else {
		auto [l, r] = split(tr->right, k - size(tr->left) - 1);
		tr->right = l;
		recalc(tr);
		return {tr, r};
	}
}

node *merge(node *l, node *r) {
	if (!l) return r;
	if (!r) return l;
	
	if (l->weight < r->weight) {
		l->right = merge(l->right, r);
		recalc(l);
		return l;
	} else {
		r->left = merge(l, r->left);
		recalc(r);
		return r;
	}
}
