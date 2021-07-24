#include <iostream>
#include <stack>
#include <vector>
#include <limits.h>
#include "grafo.h"
#include <stack>
#include <queue>
using namespace std;

int main(){

    vector<int> vec = {1,2,3,4,0};
    
    queue<int> q1;

    for(auto &it:vec){
        if(it == 1) continue;
        q1.push(it);
    }


    int niveles = vec.size()-1;
    int niv = 2;


  
    stack<int> s;

    for(int j=0; j<niveles; ++j){
        auto top = q1.front();
        q1.pop();
    //7 cout << top << endl;
        s.push(top);
    }

    while(niv-1<=niveles){
        cout << "Nivel: " << niv << endl;
        auto aux = s;
        for(int j=0; j<niveles; ++j){
            auto top = aux.top();
            aux.pop();
            cout << top << " ";
            
        }cout << endl;

        for(int i = niv; i>=2; i--){
            cout << "subnivel "<< i << endl;

            for(int j=0; j<i; ++j){
                auto t = s.top();
                s.pop();
                q1.push(t);
                
            }

            for(int j=0; j<i; ++j){
                auto top = q1.front();
                q1.pop();
                //cout << top << endl;
                s.push(top);
            }
            
            auto au = s;
            for(int j=0; j<niveles; ++j){
                auto top = au.top();
                au.pop();
                cout << top << " ";
               
            }cout << endl;


        }

        niv++;

        cout << endl;
    }


    return 0;
}