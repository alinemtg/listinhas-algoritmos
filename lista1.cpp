/* Mutirão
 https://iudex.io/problem/5b7d976ee588f50001a602c8/statement */

#include <bits/stdc++.h>
using namespace std;

//~~~NODE~~~
struct node {
    int id;
    int tempo;
    int empresa;
    int posicao;
    node *next;

    // CONSTRUTOR DO NODE
    node(int id, int tempo, int empresa, int posicao): id(id), tempo(tempo), empresa(empresa), posicao(posicao), next(NULL) {}
};

// ~~~ FILA ~~~

struct fila {

    node *front;
    node *rear;

    // CONSTRUTOR DA FILA
    fila (): front(NULL), rear(NULL) {}

    // ADICIONAR
    void add (int id, int tempo, int empresa, int posicao) {
        node *aux = new node (id, tempo, empresa, posicao);
        if (this->rear != NULL){
            this->rear->next = aux;
            this->rear = aux;
        }else{
            this->rear = aux;
            this->front = aux;
        }
    }

    // REMOVER
    node* remove(){
        node* aux = front;
        if (this->front != NULL){
            this->front =  this->front->next;
        }
        return aux;
    }

    // RETORNA TRUE SE A FILA TEM ELEMENTOS, FALSE SE N TEM NGM
    bool check(){
        return (this->front != NULL);
    }

};

// ~~~ PILHA ~~~

struct pilha {

    node *top;

    // CONSTRUTOR DA PILHA
    pilha (): top(NULL) {}

    // ADICIONAR
    void add (int id, int tempo, int empresa, int posicao) {
        node *aux = new node (id, tempo, empresa, posicao);
        aux->next = this->top;
        this->top = aux;
    }

    // REMOVER
    node* remove (){
        node* aux = top;
        if (this->top != NULL){
            this->top =  this->top->next;
        }
        return aux;
    }

    // RETORNA TRUE SE A PILHA TEM ELEMENTOS, FALSE SE N TEM NGM
    bool check(){
        return (this->top != NULL);
    }
};


// MAINNNNNNNNNNNNNNNNNNNNNNN

int main () {

    // ~~~ LEITURA DA ENTRADA ~~~
    int numEmpresas;
    cin >> numEmpresas;
    fila array_empresas[numEmpresas];

    for (int i = 0; i < numEmpresas; i++) {
        int numProcessos;
        cin >> numProcessos;
        for (int j = 0; j < numProcessos; j++) {
            int id, tempo;
            cin >> id >> tempo;
            array_empresas[i].add(id, tempo, i, j);
        }
    }

    int numMagistrados;
    cin >> numMagistrados;
    int horas_por_magistrado[numMagistrados];
    for (int i = 0; i < numMagistrados; i++) {
        cin >> horas_por_magistrado[i];
    }

    // ~~~ DISTRIBUIÃÃO POR MAGISTRADO ~~~
    pilha processos_por_magistrado[numMagistrados];
    int cont_m = 0;
    bool temProcesso1 = true;
    while (temProcesso1) {
        int cont_e = 0;
        for (int i = 0; i < numEmpresas && temProcesso1; i++) {
            if (array_empresas[i].check()) {
                node *aux = array_empresas[i].remove();
                processos_por_magistrado[cont_m % numMagistrados].add(aux->id, aux->tempo, aux->empresa, aux->posicao);
                cont_m++;
            } else {
                cont_e++;
                if (cont_e == numEmpresas) {
                    temProcesso1 = false;
                }
            }
        }
        cont_e = 0;
    }

    // ~~~ REVISÃO ~~~
    for (int i=0; i<numMagistrados; i++) {
        for (int j = 0; j < numMagistrados; j++) {
            if (i != j) {
                pilha pilhaAux;
                while (processos_por_magistrado[i].check()) {
                    node *aux = processos_por_magistrado[i].remove();
                    if (aux->id == j) {
                        processos_por_magistrado[j].add(aux->id, aux->tempo, aux->empresa, aux->posicao);
                    }else{
                        pilhaAux.add(aux->id, aux->tempo, aux->empresa, aux->posicao);
                    }
                }
                processos_por_magistrado[i] = pilhaAux;
            }
        }
    }


    // ~~~ FIM DO INFERNO

    bool temProcesso2 = true;
    int nTem = 0;
    while  (temProcesso2){
        for (int hora=1; hora<24 && temProcesso2; hora++){
            for (int magist = 0; magist<numMagistrados && temProcesso2; magist++){
                if (processos_por_magistrado[magist].check()){
                    if (hora<=horas_por_magistrado[magist]) {
                        processos_por_magistrado[magist].top->tempo--;
                        if (processos_por_magistrado[magist].top->tempo == 0) {
                            cout << magist << " " << processos_por_magistrado[magist].top->empresa << " "
                                 << processos_por_magistrado[magist].top->posicao << endl;
                            processos_por_magistrado[magist].remove();
                        }
                    }
                }else{
                        nTem++;
                        if (nTem == numMagistrados) {
                            temProcesso2 = false;
                        }
                }
            }
            nTem = 0;
        }
    }

    return 0;
}
