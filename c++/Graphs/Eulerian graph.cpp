> Algoritmo para encontrar un camino euleriano en un grafo, el cual es un camino que use todas las aristas del grafo una y sola una vez.

> La versión no dirigida existe si: 
* El grado de todos los nodos es par (Esto forma un ciclo euleriano)
* Solo existen dos nodos con grado impar

vector<int> euler_path(const vector<vector<pair<int, int>>> &G, int s = 0){
	int n = G.size(), odd = 0, m = 0;
	for (int i = 0; i < n; ++i){
		odd += G[i].size() & 1;
		m += G[i].size();
	}
	vector<int> path;
	if (odd == 0 || (odd == 2 && (G[s].size() & 1) == 1)){
		vector<int> pos(n);
		vector<bool> mark(m / 2);
		function<void(int)> visit = [&](int u){
			for (int v, id; pos[u] < G[u].size(); ){
				tie(v, id) = G[u][pos[u]++];
				if (!mark[id]){
					mark[id] = true;
					visit(v);
				}
			}
			path.push_back(u);
		};
		visit(s);
		reverse(path.begin(), path.end());
		if (path.size() != m / 2 + 1) path.clear();
	}
	return path;
}

> La versión no dirigida existe si: 
* El in-degree - out-degree == 0 para todos los nodos (Esto forma un ciclo euleriano)
* Solo existen dos nodos con |in-degree - out-degree| == 1

vector<int> euler_path(vector<vector<int>> G, int s = 0){
	int n = G.size(), m = 0;
	vector<int> deg(n);
	for (int u = 0; u < n; ++u){
		m += G[u].size();
		for (auto v : G[u])
			--deg[v];           //  in-deg
		deg[u] += G[u].size();  // out-deg
	}

	vector<int> path;
	int k = n - count(deg.begin(), deg.end(), 0);
	if (k == 0 || (k == 2 && deg[s] == 1)){
		function<void(int)> visit = [&](int u){
			while (!G[u].empty()){
				int v = G[u].back();
				G[u].pop_back();
				visit(v);
			}
			path.push_back(u);
		};
		visit(s);
		reverse(path.begin(), path.end());
		if (path.size() != m + 1) path.clear();
	}
	return path;
}