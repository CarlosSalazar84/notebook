Algoritmo para hallar componentes fuertemente conexas(SCC) en grafos dirigidos.
SE DEBEN LIMPIAR LAS ESTRUCTURAS DE DATOS ANTES DE UTILIZARSE

int v, e; 
const int MAX = 5000; // Máxima cantidad de nodos
int dfs_low[MAX];
int dfs_num[MAX];
bool marked[MAX];
vector<int> s;
int dfsCont, cantSCC;
vector<int> ady[];
	
void tarjanSCC( int u ){
	dfs_low[u] = dfs_num[u] = dfsCont;
	dfsCont++;
	s.push_back(u);
	marked[u] = true;
		
	int j, v;
		
	for( j = 0; j < ady[u].size(); j++ ){
		v = ady[u][j] );
			
		if( dfs_num[v] == -1 ){
			tarjanSCC( v );
		}
			
		if( marked[v] ){
			dfs_low[u] = min( dfs_low[u], dfs_low[v] );
		}
	}
		
	if( dfs_low[u] == dfs_num[u] ){
		cantSCC++;
        /* ********************************************************* */
        /* Esta seccion se usa para imprimir las componentes conexas */
		cout << "COMPONENTE CONEXA #" << cantSCC << "\n";
		while( true ){
			v = s.back();
			s.pop_back();
			marked[v] = false;
			cout << v << "\n";
			if( u == v ) break;
		}
        /* ********************************************************** */
	}	
}

int main (){
    for( int i = 0; i < v; i++ ){ //Por si el grafo no es conexo
        if( dfs_num[i] == -1 ){
            dfsCont = 0;
            s.clear();
            tarjanSCC(i);
        }
    }
}
	



