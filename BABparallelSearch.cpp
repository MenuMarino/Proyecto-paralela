/*
    Version 3: (Branch and bound)
    Paralelizado e iterativo
*/

#include <iostream>
#include <stack>
#include <iomanip>
#include <vector>
#include <limits.h>
#include <float.h>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <omp.h>
#include "grafo.h"
#include <chrono>

using namespace std;
struct nodo {
    nodo* padre;

    int id;
    int ciudad;

    unordered_map<double, bool> nodos_visitados;

    double **mat;

    nodo() = default;

    double coste = 0;

    nodo(nodo* p, double **m, double c, int ciu){
        mat = m;
        padre = p;
        ciudad = ciu;
        coste = c;
    };

    nodo(nodo* p, double **m, double c, int ciu, unordered_map<double, bool> vn){
        mat = m;
        padre = p;
        ciudad = ciu;
        coste = c;      
        nodos_visitados = vn;
    };

    ~nodo() {
        for (int i = 0; i < N; i++) {
            delete [] mat[i];
        }
        delete [] mat;
    }

    void set_matrix(double **_m){
        mat = _m;
    }

};

double **GRAFO;
double upper = DBL_MAX;
vector<nodo> nodes;
nodo* mejor_camino = nullptr;
int t = 2;

pair<double**, double> reducir(double **mati, int from, int to){

    double **mat = new double *[N];
    for (int i = 0; i < N; i++) {
        mat[i] = new double[N];
    }

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            mat[i][j] = mati[i][j];
        }
    }
        
        for(int i=0; i<N; ++i){
            mat[i][i] = DBL_MAX;

            if(from != to) mat[i][to] = DBL_MAX;
            if(from != to) mat[from][i] = DBL_MAX;
        }
   

    mat[to][from] = DBL_MAX;

    double acumulado_reduccion = 0;
  
    
        for(int i=0; i<N; ++i){

            double min_fila = DBL_MAX;
            for(int j=0; j<N; ++j){
                
                if(mat[i][j] < min_fila) min_fila = mat[i][j];
            }

            if(min_fila > 0 && min_fila != DBL_MAX ) {
                for(int j=0; j<N; ++j) {
                    if(mat[i][j] != DBL_MAX) mat[i][j] -= min_fila; 
                }
                if(min_fila != DBL_MAX) acumulado_reduccion += min_fila; 
            }
        }
    

        for(int j=0; j<N; ++j) {
            double min_columna = DBL_MAX;
            for(int i=0; i<N; ++i) {
                if(mat[i][j] < min_columna) {
                    
                    min_columna = mat[i][j];
                }
            }
            if(min_columna > 0 && min_columna != DBL_MAX ) {
                for(int i=0; i<N; ++i) {
                    if(mat[i][j] != DBL_MAX) mat[i][j] -= min_columna; 
                }
                if(min_columna != DBL_MAX) acumulado_reduccion += min_columna;
            }
        }
    
    return {mat, acumulado_reduccion};
}


template <typename PQ>
void recorrer(PQ& pq, double** GRAFO, bool firstime, int to){
    //cout << "pq size: " << pq.size() << endl;
    
    while(pq.empty() == false) {
        auto temp = pq.top();
        pq.pop();

       // cout << temp->nodos_visitados.size() << endl;

      
        if (temp->coste <= upper) {
            
            
            vector<nodo*> nodos_a_los_que_llegas;
            bool parada = false;

            if(firstime){
                nodo* nodo_nuevo = new nodo(temp, nullptr, DBL_MAX, to, temp->nodos_visitados);
                nodos_a_los_que_llegas.push_back(nodo_nuevo);
                parada = true; 
                firstime = false; 
            }else{
                for (int i = 0; i < N; i++) {
                    
                
                if (GRAFO[temp->ciudad][i] != DBL_MAX && temp->nodos_visitados[i] == false) {
                    //cout << "aqui" << endl;
                    nodo* nodo_nuevo = new nodo(temp, nullptr, DBL_MAX, i, temp->nodos_visitados);
                    nodos_a_los_que_llegas.push_back(nodo_nuevo);
                    parada = true;
                   // cout << "aqui" << endl;
                }
                }
            }

           
            if (parada == false) {
                upper = temp->coste;
                if (mejor_camino == nullptr) { mejor_camino = temp; }
                else {
                    mejor_camino = temp->coste < mejor_camino->coste ? mejor_camino = temp : mejor_camino = mejor_camino;
                }
            }
            else {
                for (auto n : nodos_a_los_que_llegas) {
                    auto data = reducir(temp->mat, temp->ciudad, n->ciudad);
                    n->set_matrix(data.first);
                    n->coste = temp->mat[temp->ciudad][n->ciudad] + temp->coste + data.second;
                    n->nodos_visitados[n->ciudad] = true;
                    pq.push(n);
                }
            }
        }
    }
}

int main(){

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();

    cout << "\n================ Parallel ==================\n";

    double **GRAFO = new double *[N];
    for (int i = 0; i < N; i++) {
        GRAFO[i] = new double[N];
    }
    
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            GRAFO[i][j] = GRAFITO[i][j];
        }
    }

    
    auto cmp = [](nodo* left, nodo* right) { return (left->coste) > (right->coste); };

    
    auto dat = reducir(GRAFO, 0, 0);
    nodo* root = new nodo(nullptr, dat.first, dat.second, 0);
    priority_queue<nodo*, vector<nodo*>, decltype(cmp)> pq(cmp);
    root->nodos_visitados[0] = true;
    pq.push(root);

    vector<priority_queue<nodo*, vector<nodo*>, decltype(cmp)>> pqs;

    for(int i=0; i<N+1; ++i){
        pqs.push_back(pq);
    }

    #pragma omp parallel 
    {
        #pragma omp single nowait 
        {
            for(int i=1; i<N; ++i){
                #pragma omp task
                recorrer(pqs[i], GRAFO, true,i);
            }
        
        }
        #pragma omp taskwait
        
    }
    
    
    
    

    
    
   // recorrer(pq, GRAFO, true, 1);
   // recorrer(pq1, GRAFO, true, 2);
  //  recorrer(pq2, GRAFO, true, 3);
    //recorrer(pq3, GRAFO, true, 4);
    


    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

    auto temp = mejor_camino;
    cout << "0 - ";
    while (temp != nullptr) {
        cout << temp->ciudad << " - ";
        temp = temp->padre;
    }
    cout << endl;
    cout << "Costo = " << mejor_camino->coste << endl;
    
    cout << "Tiempo: " << ms_double.count() /1000  << " s.\n";
    cout << "============================================\n\n";

    for (int i = 0; i < N; i++) {
        delete [] GRAFO[i];
    }
    delete [] GRAFO;

    delete root;

    return 0;
}