> Este algoritmo responde de manera offline queries de rango sobre un arreglo en n * sqrt(n)
WARNING Usar como estructura de datos global una que trabaje en O(1), sino es muy probable que de TLE

// Suele usar una estructura de datos global

void remove(int idx) {}  // IMPLEMENTAR: Eliminar el valor en la posicion idx de la estructura
void add(int idx) {}     // IMPLEMENTAR: Agregar el valor en la posicion idx a la estructura
int get_answer();  // IMPLEMENTAR: Obtener la respuesta actual para la estructura

// Asignar el tamaño deseado, suele rondar el valor de sqrt(n), se recomienda dejarlo const para acelerarlo
const int block_size;  

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    // IMPLEMENTAR: Inicializar la estructura de datos global que vamos a utilizar

    int cur_l = 0;
    int cur_r = -1;
    // INVARIANTE: La estructura de datos siempre reflejara el rango [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

// Comparador especial para mejorar el rendimiento, pero no suele ser necesario

bool cmp(pair<int, int> p, pair<int, int> q) {
    if (p.first / BLOCK_SIZE != q.first / BLOCK_SIZE)
        return p < q;
    return (p.first / BLOCK_SIZE & 1) ? (p.second < q.second) : (p.second > q.second);
}