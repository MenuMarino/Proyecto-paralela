/*
    Version 1: (Branch and bound)
    Sin paralelizacion y recursivo
*/

#include <iostream>
#include <stack>
#include <vector>
#include <limits.h>
#include <sys/time.h>
#include "grafo.h"

using namespace std;

int ciudades[N] = {LIMA_CENTRO, LINCE, MIRAFLORES, BARRANCO, RIMAC, LOS_OLIVOS, LA_MOLINA, LA_VICTORIA, MAGDALENA_DEL_MAR, SAN_BORJA};
bool visitados[N] = {true, false, false, false, false, false, false, false, false, false};

stack<int> camino;
float camino_distancia = 0;
stack<int> mejor_camino;
float mejor_camino_distancia = INT_MAX;
int c = 0;

void BranchAndBound(stack<int> path, float cur_dist, float gasolina) {
    if (path.size() == N ) {
        float camino = GRAFITO[LIMA_CENTRO][path.top()];
        float dist = cur_dist + camino;
        if (gasolina < camino) {
            dist += (camino - gasolina) * 2;
        }
        if (dist < mejor_camino_distancia) {
            mejor_camino = path;
            mejor_camino.push(LIMA_CENTRO);
            mejor_camino_distancia = dist;
        }
    } else {
        int ultima_ciudad = path.top();

        for (const auto& ciudad : ciudades) {
            if (visitados[ciudad] || ultima_ciudad == ciudad) continue;

            int cur_gasolina = gasolina;
            float camino = GRAFITO[ciudad][ultima_ciudad];
            float dist = cur_dist + camino;

            if (cur_gasolina < camino) {
                dist += (camino - cur_gasolina) * 2;
                cur_gasolina = G;
            } else {
                cur_gasolina -= camino;
            }

            if (dist < mejor_camino_distancia) {
                visitados[ciudad] = true;
                path.push(ciudad);
                BranchAndBound(path, dist, cur_gasolina);
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

    printf("\nCosto = %.4f\n", mejor_camino_distancia);
}

int main(int argc, char* argv[]) {
    bool debug = false;
    if (argc >= 2) debug = true;
    cout << "\n================ Secuential ================\n";
    struct timeval start, end;
    gettimeofday(&start, NULL);

    camino.push(0);
    BranchAndBound(camino, 0.0, G);

    gettimeofday(&end, NULL);
    auto delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec) / 1.e6;

    print_mejor_camino(debug);
    cout << "Tiempo: " << delta << " s.\n";
    cout << "============================================\n";
    return 0;
}
