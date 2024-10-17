> Guarda el estado del segment tree después de cada actualización para permitir hacer consultas sobre estados pasados.
> Consultas y actualizaciones en O(logn), ocupa O(nlogn) en memoria.

typedef int T; 
const T neutro = 1e9;

T merge(T &a, T &b) {
    return min(a, b);
}

struct node {
    T value; node *l, *r;  
    
    node() : value(neutro), l(nullptr), r(nullptr) {}
    
    node(T val) : value(val), l(nullptr), r(nullptr) {} 
    
    void unite() {
        T lf = (l != nullptr) ? l->value : neutro;
        T rg = (r != nullptr) ? r->value : neutro;  
        value = merge(lf, rg);
    }
};

struct segtree {
    vector<node*> roots;
    int n;

    segtree(const vector<int> &v) {
        n = v.size();
        roots.push_back(build(0, n - 1, v));
    }

    node* build(int L, int R, const vector<int> &v) {
        if (L == R) return new node(v[L]);
        int m = (L + R) / 2;
        node *p = new node();
        p->l = build(L, m, v);
        p->r = build(m + 1, R, v);
        p->unite();
        return p;
    }
    
    T query(int i, int j, int tm) { return query(roots[tm], 0, n - 1, i, j); }
    void upd(int i, int j, T val) { roots.push_back(upd(roots.back(), 0, n - 1, i, j, val)); }
    
    T query(node *p, int L, int R, int i, int j) {
        if (i > R || j < L) return neutro;
        if (i <= L && j >= R) return p->value;
        int m = (L + R) / 2;
        T lf = query(p->l, L, m, i, j);
        T rg = query(p->r, m + 1, R, i, j);
        return merge(lf, rg);
    }

    node* upd(node *p, int L, int R, int i, int j, T val) {
        if (i > R || j < L) return p;
        if (i <= L && j >= R) return new node(val); 
        int m = (L + R) / 2;
        node *new_p = new node();
        new_p->l = upd(p->l, L, m, i, j, val);
        new_p->r = upd(p->r, m + 1, R, i, j, val);
        new_p->unite();
        return new_p;
    }
};

> Versión con lazy creation

struct node {
    node *left, *right;
    int val;

    node() : left(this), right(this), val(0) {}
    node(node *left, node *right, int val) :
        left(left), right(right), val(val) {}

    node* update(int l, int r, int i, int x) {
        if (l == r) return new node(nullptr, nullptr, val + x);
        int m = (l + r) / 2;
        if (i <= m)
            return new node(left->update(l, m, i, x), right, val + x);
        return new node(left, right->update(m + 1, r, i, x), val + x);
    }

    int query(int l, int r, int i, int j) {
        if (i > r || l > j) return 0;
        if (i <= l && r <= j) return this->val;
        int m = (l + r) / 2;
        int lf = left->query(l, m, i, j);
        int rg = right->query(m + 1, r, i, j);
        return lf + rg;
    }
};

vector<node*> roots = {new node()};
roots.pb(roots.back()->update(0, n-1, i, x));
roots[i]->query(0, n-1, l, r);
