Algoritmo de eliminación Gauss-Jordan O(N ^ 3)
Soluciona un sistema de ecuaciones de la forma:
a11 x1 + a12 x2 + ... + a1m xm = b1
a21 x1 + a22 x2 + ... + a2m xm = b2
an x1 + an2 x2 + ... + anm xm = bn

El vector a contiene los valores de la matriz, cada fila es una ecuación, la última columna contiene los valores b.

const double EPS = 1e-9;
const int INF = -1; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

Gauss jordan para operaciones de xor

const int N = 100;

int gauss (vector<bitset<N>> &a, vector<bool> &b, int n, int m, vector<bool> &ans) {
  vector<int> pivot(m, -1);
  for(int col = 0, row = 0; col < m && row < n; ++col) {
    for(int i = row; i < n; ++i){
      if(a[i][col]){
        swap(a[i], a[row]);
        swap(b[i], b[row]);
        break;
      }
    }
    if(!a[row][col])continue;
    pivot[col] = row;
    for(int i = 0; i < n; ++i)
      if(i != row && a[i][col]) {
        a[i] ^= a[row];
        b[i] = b[i] ^ b[row];
      }
    ++row;
  }
  
  ans.assign(m, 0);
  for(int i = 0; i < m; ++i)
    if(pivot[i] != -1) ans[i] = b[pivot[i]];
  for(int i = 0; i < n; ++i) {
    bool xr = 0;
    for(int j = 0; j < m; ++j) {
        xr ^= ans[j] & a[i][j];
    }
    if(xr != b[i]) return 0;
  }
  for(int i = 0; i < m; ++i)
    if(pivot[i] == -1) return -1; /// infinite solutions
  return 1;
}
