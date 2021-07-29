/*
    Version 1: (Branch and bound)
    Sin paralelizacion y recursivo
*/

#include <iostream>
#include <stack>
#include <vector>
#include <limits.h>
#include "grafo.h"

using namespace std;

int ciudades[10] = {LIMA_CENTRO, LINCE, MIRAFLORES, BARRANCO, RIMAC, LOS_OLIVOS, LA_MOLINA, LA_VICTORIA, MAGDALENA_DEL_MAR, SAN_BORJA};
bool visitados[10] = {true, false, false, false, false, false, false, false, false, false};

stack<int> camino;
float camino_distancia = 0;
stack<int> mejor_camino;
float mejor_camino_distancia = INT_MAX;
int c = 0;

void BranchAndBound(stack<int> path, float cur_dist) {
    if (path.size() == N ) {
        if (cur_dist + GRAFITO[LIMA_CENTRO][path.top()] < mejor_camino_distancia) {
            mejor_camino = path;
            mejor_camino.push(LIMA_CENTRO);
            mejor_camino_distancia = cur_dist + GRAFITO[LIMA_CENTRO][path.top()];
        }
    } else {
        int ultima_ciudad = path.top();
        for (const auto& ciudad : ciudades) {
            if (visitados[ciudad] || ultima_ciudad == ciudad) continue;
            // branch and bound
            if (cur_dist + GRAFITO[ciudad][ultima_ciudad] < mejor_camino_distancia) {
                visitados[ciudad] = true;
                path.push(ciudad);
                BranchAndBound(path, cur_dist + GRAFITO[ciudad][ultima_ciudad]);
                path.pop();
                visitados[ciudad] = false;
            }
        }
    }
    path.pop();
}

void print_mejor_camino(bool debug = false) {
    if (debug) {
        auto cpy = mejor_camino;
        while (cpy.size() != 1) {
            int A = cpy.top();
            print_ciudad(A);
            cpy.pop();
            int B = cpy.top();
            printf("%.2f km ", GRAFITO[A][B]);
            print_ciudad(B, true);
        }
    }

    auto cpy = mejor_camino;
    while (cpy.size()) {
        cout << cpy.top() << " - ";
        cpy.pop();
    }

    printf("\nCosto = %.1f\n", mejor_camino_distancia);
}

int main(int argc, char* argv[]) {
    bool debug = false;
    if (argc >= 2) debug = true;
    camino.push(0);
    BranchAndBound(camino, 0.0);
    print_mejor_camino(debug);
    return 0;
}
