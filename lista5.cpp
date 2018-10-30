/* aMAZEing!
 https://iudex.io/problem/5bcc95305cd44b0001fdbf74/statement */

#include <bits/stdc++.h>
using namespace std;

struct celula {
    int numeracao;
    int altura;

    celula (int numeracao): numeracao(numeracao), altura (0) {}
};

celula* find (int indice, celula* celulas[]){
    if (indice == celulas[indice]->numeracao)
        return celulas[indice];
    else{
        celulas[indice] = find(celulas[indice]->numeracao, celulas);
        return celulas[indice];
    }
}

celula* unionn (int indiceA, int indiceB, celula* celulas []){
    celula* root1 = find (indiceA, celulas);
    celula* root2 = find (indiceB, celulas);

    if (root1->altura == root2->altura){
        celulas[root2->numeracao] = root1;
        root1->altura = root1->altura + 1;
        return root1;
    }else if (root1->altura > root2->altura){
        celulas[root2->numeracao] = root1;
        return root1;
    }else{
        celulas[root1->numeracao] = root2;
        return root2;
    }
}

int main() {
    int quantLabirintos;
    cin >> quantLabirintos;

    for (int l=0; l<quantLabirintos; l++){
        int tamLabirinto, quantParedesRemovidas, quantParesConsultados;
        cin >> tamLabirinto >> quantParedesRemovidas >> quantParesConsultados;
        int aux = (2*tamLabirinto) - 1;
        celula* celulas [tamLabirinto*tamLabirinto];

        for (int n=0; n<tamLabirinto*tamLabirinto; n++){
            celulas[n] = new celula (n);
        }

        for (int p=0; p<quantParedesRemovidas; p++){
            int parede;
            cin >> parede;
            int celula1, celula2;

            if (parede%aux < tamLabirinto-1){
                celula1 = tamLabirinto*(parede/aux) + parede%aux;
                celula2 = celula1 + 1;
            }else{
                celula1 = tamLabirinto*(parede/aux) + parede%aux + 1;
                celula2 = celula1 - tamLabirinto;
            }
            unionn (celula1, celula2, celulas);
            celulas[celula1] = find (celula1, celulas);
            celulas[celula2] = find (celula2, celulas);
        }

        for (int d=0; d<quantParesConsultados; d++) {
            int celula1, celula2;
            cin >> celula1 >> celula2;

            if (find (celula1, celulas) == find(celula2, celulas)) {
                cout << l << "." << d << " " << 1 << endl;
            } else {
                cout << l << "." << d << " " << 0 << endl;
            }
        }
        
        cout << "\n";
    }
}