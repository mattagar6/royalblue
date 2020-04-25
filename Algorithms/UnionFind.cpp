/**
	Union find algorithm
	Complexity O(log n) for Join or Find.
*/

int pai[MAXN], sz[MAXN];

void init(int n){
	for(int i = 0; i <= n; i++){
		pai[i] = i;
		sz[i] = 1;
	}
}

int find(int i){
	if(pai[i] == i) return i;
	return pai[i] = find(pai[i]);
}

int join(int a, int b){
	a = find(a);
	b = find(b);
	if(a != b){
		sz[b] += sz[a];
		pai[a]=pai[b];
	}
}
