typedef pair<int,int> pii;

struct dsu_rollback {
	vector<int> par;
	vector<int> sz;
	vector<pii> stk;
	
	dsu_rollback() {}
	
	dsu_rollback(int n) {
		par.resize(n);
		iota(par.begin(), par.end(), 0);
		sz.resize(n, 1);
	}
	
	int getPar(int v) {
		while(v != par[v])
			v = par[v];
		return v;
	}
	
	bool unite(int u, int v) {
		v = getPar(v); u = getPar(u);
		if(u == v)
			return false;
		if(sz[v] < sz[u])	
			swap(u, v);
		sz[v] += sz[u];
		par[u] = v;
		stk.emplace_back(v, u);
		return true;
	}
	
	void undo() {
		assert(!stk.empty());
		auto [v, u] = stk.back(); stk.pop_back();
		sz[v] -= sz[u];
		par[u] = u;
	}
	
};
