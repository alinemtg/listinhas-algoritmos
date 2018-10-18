/* RMQ
 https://iudex.io/problem/5ba2fa7bfcc38200012023d4/statement */

#include <bits/stdc++.h>
using namespace std;

struct arvre {
    int inicio;
    int fim;
    int menor;
    arvre *esq;
    arvre *dir;

    //arvre (int inicio, int fim, int menor): inicio(inicio), fim(fim), menor(menor), esq(nullptr), dir(nullptr) {}
    arvre(int inicio, int fim) : inicio(inicio), fim(fim), menor(-1), esq(nullptr), dir(nullptr) {}

};

arvre *criar(arvre *raiz, int inteiros[], int inicio, int fim) {
    raiz = new arvre(inicio, fim);
    if (raiz->inicio == raiz->fim) {
        raiz->menor = inteiros[raiz->inicio];
    } else {
        int m = (int) floor((raiz->inicio + raiz->fim) / 2);
        raiz->esq = criar(raiz->esq, inteiros, inicio, m);
        raiz->dir = criar(raiz->dir, inteiros, m + 1, fim);
        raiz->menor = min(raiz->esq->menor, raiz->dir->menor);
    }
    return raiz;
}

int consulta(arvre *raiz, int a, int b) {
    if (a > b || a > raiz->fim || b < raiz->inicio) {
        return INT_MAX;
    } else if (a == raiz->inicio && b == raiz->fim) {
        return raiz->menor;
    } else {
        int h = (int) floor((raiz->inicio + raiz->fim) / 2);
        return min(consulta(raiz->esq, max(a, raiz->inicio), min(b, h)),
                   consulta(raiz->dir, max(a, h + 1), min(b, raiz->fim)));
    }
}

void atualizar(arvre *raiz, int i, int novoValor) {
    if (raiz->inicio == raiz->fim) {
        raiz->menor = novoValor;
    } else {
        int h = (raiz->fim + raiz->inicio)/2;
        if (i<=h){
            atualizar(raiz->esq, i, novoValor);
        }else {
            atualizar(raiz->dir, i, novoValor);
        }
        raiz->menor = min(raiz->esq->menor, raiz->dir->menor);
    }
}

void posOrdem(arvre *raiz, int a, int b, int l, int r) {

    if (raiz) {
        if (raiz->fim < a || raiz->inicio > b) {
            return;
        } else {
            posOrdem(raiz->esq, a, b, l, r);
            posOrdem(raiz->dir, a, b, l, r);
            cout << raiz->menor;
            if (raiz->inicio != l || raiz->fim != r){
                cout << " ";
            }

        }
    }
}

int main() {
    int numSensores;
    cin >> numSensores;
    int sensores[numSensores];
    for (int i = 0; i < numSensores; i++) {
        cin >> sensores[i];
    }
    arvre *raiz = new arvre(0, 0);
    raiz = criar(raiz, sensores, 0, numSensores - 1);

    string evento;
    while (cin >> evento, evento != "END") {
        int a, b;
        cin >> a >> b;

        if (evento == "UPD") {
            atualizar(raiz, a, b);
        } else if (evento == "RMQ") {
            cout << consulta(raiz, a, b) << endl;
        } else {
            posOrdem(raiz, a, b, raiz->inicio, raiz->fim);
            cout << endl;
        }
    }
    return 0;
}


