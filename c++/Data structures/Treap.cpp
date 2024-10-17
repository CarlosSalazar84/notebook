mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0, LLONG_MAX);
 
typedef struct item* pitem;
typedef ll T;
 
const T neutro = 0;
 
/* Operaciones en O(log N)
   Permite actualizaciones y querys en rangos
*/
struct item {
	pitem left, right;
	pitem father;
	ll pri;		// Prioridad random del nodo
	int cnt;	// Cantidad de nodos en el subárbol 
	T value; 	// Valor del nodo
	T sum;		// Valor de la función que se desea consultar del subárbol. Ej: sumas, max, min...
	bool rev;	// Flag para indicar si el subárbol debe ser revertido
	T lazy;		
 
	item(T _value) {
		left = right = father = 0;
		value = _value;
		sum = _value;
		pri = rnd(rng);
		cnt = 1;
		lazy = 0;
		rev = false;
	}	

};
 
int cnt(pitem t)  { return !t ? 0 : t->cnt; }
T operation(pitem t)  { return !t ? neutro : t->sum; }
T value(pitem t)  { return !t ? neutro : t->value; }

void unite(pitem t) { 
	t->sum = value(t) + operation(t->left) + operation(t->right);
}

/* Actualizar la cantidad de nodos del árbol T */
void update_cnt(pitem t) {
	if(!t) return;
	unite(t);
	t->cnt = cnt(t->left) + cnt(t->right) + 1;
}
 
/* Actualizar los valores pendientes y push al tag lazy a sus hijos */
void propagate(pitem t) {
	if(!t) return;
	if(t->rev) {
		swap(t->left, t->right);
		if(t->left) t->left->rev ^= true;
		if(t->right) t->right->rev ^= true;
		t->rev = false;
	}
	if(t->lazy) {
		if(t->left) t->left->lazy += t->lazy;
		if(t->right) t->right->lazy += t->lazy;
		t->value += t->lazy;
		t->lazy = 0;
	}
	unite(t);
}
 
 
/* En L quedan los primeros k elementos y en R los restantes */
void split(pitem t, pitem &L, pitem &R, int k, int add = 0) { 
	if(!t) {
		L = R = 0;
		return;
	}
	propagate(t);
	int cur_key = add + cnt(t->left); // Key implicita actual
	if(k <= cur_key) {
		split(t->left, L, t->left, k, add);
		R = t;
		if(L) {
			L->father = 0;
		}
		if(t->left) {
			t->left->father = t;
		}
	}
	else {
		split(t->right, t->right, R, k, add + cnt(t->left) + 1);
		L = t;
		if(R) { 
			R->father = 0;
		}
		if(t->right) {
			t->right->father = t;
		}
	}
	update_cnt(t);
}
 
/* Une el treap L y R en el treap t = LR*/
void merge(pitem &t, pitem L, pitem R) {
	propagate(L);
	propagate(R);
	if(!L) {
		t = R;
	}
	else if(!R) {
		t = L;
	}
	else if(L->pri > R->pri) {
		merge(L->right, L->right, R);
		t = L;
		L->right->father = L;
	}
	else {
		merge(R->left, L, R->left);
		t = R;
		R->left->father = R;
	}
	update_cnt(t);
}
 
void push_all(pitem t){
	if(t->father) push_all(t->father);
	propagate(t);
} 

/* Obtiene la raiz y la posición del nodo t */
pitem root(pitem t, int& pos){ 
	push_all(t);
	pos = cnt(t->left);
	while(t->father){
		pitem f = t->father;
		if(t == f->right) pos += cnt(f->left) + 1;
		t = f;
	}
	return t;
}

/* Imprime los valores del treap */
void inorder(pitem t) {
	if(!t) return;
	propagate(t);
	inorder(t -> left);
	cout <<  (t -> value) << " ";
	inorder(t -> right);
}

/* Query [l, r) indexado desde 0 */
T query(pitem t, int l, int r) {
	T ans = 0;
	pitem range = 0, prefix = 0, sufix = 0;
	split(t, range, sufix, r);
	split(range, prefix, range, l);
	ans = operation(range);
	merge(t, prefix, range);
	merge(t, t, sufix);
	return ans;
}
 
/* Update [l, r) indexado desde 0 */
void update(pitem t, int l, int r, int add) {
	pitem range = 0, prefix = 0, sufix = 0;
	split(t, range, sufix, r);
	split(range, prefix, range, l);
	range -> lazy = add;
	merge(t, prefix, range);
	merge(t, t, sufix);
}
 
/* Reverse [l, r) indexado desde 0 */
void reverse(pitem t, int l, int r) {
	pitem range = 0, prefix = 0, sufix = 0;
	split(t, range, sufix, r);
	split(range, prefix, range, l);
	range -> rev ^= true;
	merge(t, prefix, range);
	merge(t, t, sufix);
}
 
