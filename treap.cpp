#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;
 
#define F first
#define S second

mt19937 rng;// XXX
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

const int MAXN = 1e6 + 10;// XXX
// Set to the maximum number of treap nodes.

struct node {
	node *left, *right, *par;
	int weight, size;
	
	// Add custom node data here.
	int val;
	
	node() : left(NULL), right(NULL), par(NULL), weight(rng()), size(1) {}
};

typedef node * nodep;
node pool[MAXN];

// Use this function as a constructor.
nodep new_node(/* Node data */) {
	static int nt = 0;
	assert(nt < MAXN);
	return &pool[nt++];
}

int size(nodep treap) {
	return treap == NULL ? 0 : treap->size;
}

void set_par(nodep treap, nodep par) {
	if(treap == NULL) 
		return;
	treap->par = par;
}

// Do any lazy propogation here.
// Must be called whenever you 'touch' a treap node.
void prop(nodep treap) {
	if(treap == NULL)
		return;
	
}

// Recalculate stored information about this treap node.
// Must be called whenever a child of 'treap' changes.
void recalc(nodep treap) {
	if(treap == NULL)
		return;
	
	prop(treap);
	treap->size = 1 + size(treap->left) + size(treap->right);
}

// Split 'treap' into 2 treaps, 'left' and 'right'.
// Returns and array of 2 treaps, ret[0] is the left treap, ret[1] is the right treap.
// size(ret[0]) == onLeft
// size(ret[1]) == size(treap) - onLeft 
array<nodep,2> split(nodep treap, int onLeft) {
	if(treap == NULL) {
		assert(onLeft == 0);
		return {NULL, NULL};
	} else {
		prop(treap);
		if(size(treap->left) >= onLeft) {
			auto ret = split(treap->left, onLeft);
			treap->left = ret[1];
			set_par(ret[1], treap);
			recalc(treap);
			return {ret[0], treap};
		} else {
			auto ret = split(treap->right, onLeft - size(treap->left) - 1);
			treap->right = ret[0];
			set_par(ret[0], treap);
			recalc(treap);
			return {treap, ret[1]};
		}
	}
}

// Merge 'left' and 'right' into a new treap.
// All elements of 'left' to the left of all elements of 'right' in preorder.
// Preserves ordering of nodes in 'left' and 'right'.
// Returns the root to the new treap. 'left' and 'right' ARE NO LONGER VALID.
nodep merge(nodep left, nodep right) {
	if(left == NULL) return right;
	if(right == NULL) return left;
	
	prop(left); prop(right);
	if(left->weight < right->weight) {
		nodep r = merge(left->right, right);
		set_par(r, left);
		left->right = r;
		recalc(left);
		return left;
	} else {
		nodep l = merge(left, right->left);
		set_par(l, right);
		right->left = l;
		recalc(right);
		return right;
	}
}

// Returns the root of the treap which contains 'v', or NULL if 'v' is NULL.
nodep get_root(nodep v) {
	if(v == NULL)
		return NULL;
	while(v->par != NULL)
		v = v->par;
	return v;
}

void solve() {
	
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//cout << fixed << setprecision(6);
	
	int te = 1;	
	//cin >> te;
	for (int w = 1; w <= te; w++){
		//cout << "Case #" << w << ": ";
		solve();
	}
	return 0;
}

/*	Usage:
 * 
 * 		// Creating a new treap node.
 * 		nodep treap = new_node(node_data);
 * 		
 * 		// Create a treap from an array.
 * 		nodep treap = NULL;
 * 		for (int i = 0; i < n; i++) {
 * 			treap = merge(treap, new_node(a[i]));
 * 		}
 * 	
 * 		// Splitting a treap into 2 treaps. 
 * 		auto [left, right] = split(treap, onLeft);
 * 
 * 	Gotchas:
 * 		- 'merge' returns a new treap from 2 other treaps, the input treaps are no longer valid.
 * 			- Similar for 'split', but it returns 2 new treaps
 * 
 * 		- Use new_node(...) to creat a new node (modify parameters to initialize node data).
 * 		- Make sure to call 'prop(treap)' and 'recalc(treap)' whenever you touch/modify a treap node.
 * 		- Make 'MAXN' big enough.
 * 
 */
