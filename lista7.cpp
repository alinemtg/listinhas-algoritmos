/* Lemmings
 https://iudex.io/problem/5bf2af8f5cd44b0001fdc0db/statement */

#include <bits/stdc++.h>
#define pob pop_back
using namespace std;

stack<int> pilha;
int* seqEntrada = nullptr;
int* seqSaida = nullptr;
string saida;

void resolve (string &operacoes, int i, int s, int maxL, int &maxG, int numLemmings){
    if (operacoes.size() == 2*numLemmings){
        if (saida.empty()){
            saida = operacoes;
            maxG = maxL;
        }else{
            if (maxL < maxG){
                maxG = maxL;
                saida = operacoes;
            }else if (maxL == maxG){
                if (!lexicographical_compare(saida.begin(), saida.end(), operacoes.begin(), operacoes.end())) {
                    saida = operacoes;
                }
            }
        }
    }else{
        if (pilha.size() > maxL) {
            maxL = pilha.size();
        }if (maxL > maxG){
            return;
        }
        if (i<numLemmings){
            pilha.push(seqEntrada[i]);
            operacoes.push_back('O');
            resolve(operacoes, i+1, s, maxL, maxG, numLemmings);
            operacoes.pop_back();
            pilha.pop();
        }
        if (!pilha.empty()){
            int n = pilha.top();
            if (n == seqSaida[s]){
                pilha.pop();
                operacoes.push_back('Y');
                resolve(operacoes, i, s+1, maxL, maxG, numLemmings);
                pilha.push(n);
                operacoes.pop_back();
            }
            else{
                return;
            }
        }
    }
}

int main() {
    int numFases;
    cin >> numFases;

    for (int i=0; i<numFases; i++){
        int numLemmings;
        cin >> numLemmings;
        seqEntrada = new int [numLemmings];
        seqSaida = new int [numLemmings];

        for (int ii=0; ii<numLemmings; ii++){
            cin >> seqEntrada[ii];
        }
        for (int ii=0; ii<numLemmings; ii++){
            cin >> seqSaida[ii];
        }

        string operacoes = "";
        int maxG = INT_MAX;
        saida = "";
        resolve(operacoes, 0, 0, 0, maxG, numLemmings);
        cout << saida  << " " <<  maxG << endl;

    }

    return 0;
}
