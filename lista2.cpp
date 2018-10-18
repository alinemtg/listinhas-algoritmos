/* Organizando os arquivos
 https://iudex.io/problem/5b91a3b3fcc3820001202248/statement */

#include <bits/stdc++.h>
using namespace std;

// ~~~ NODE ~~~
struct node {
    string nome;
    int id;
    node *next;

    // CONSTRUTOR DO NODE
    node(string nome, int id): nome(nome), id(id), next(nullptr) {}
};

// ~~~ GAVETA ~~~
struct gaveta {
    node *front;
    node *rear;
    int tam;

    // CONSTRUTOR DA GAVETA
    gaveta (): front(nullptr), rear(nullptr), tam(0) {}

    void add (string nome, int id){
        node *aux = new node (nome, id);
        if (this->rear){
            this->rear->next = aux;
            this->rear = aux;
        }else{
            this->front = aux;
            this->rear = aux;
        }
        tam++;
    }

    int procurar (string nome){
        node *aux = this->front;
        int cont = 0;
        while (aux->next){
            if (aux->nome.compare(nome)==0){
                return cont;
            }
        }
        return -1;
    }

    int acessoTam (){
        return this->tam;
    }
};

int buscaBinaria (int ids[], int quantArquivos, int idProcurado){
    int iniAux = 0;
    int fimAux = quantArquivos-1;
    while (iniAux<=fimAux){
        int posMeio = (iniAux+fimAux)/2;
        if (idProcurado == ids[posMeio]){
            return posMeio;
        }else if (idProcurado<ids[posMeio]){
            fimAux = posMeio-1;
        }else{
            iniAux = posMeio+1;
        }
    }
    return -1;
}

int dispersao (string nome, int quantGavetas){
    int chave = 0;
    for (int i=0; i<nome.length(); i++){
        char letrinha = nome[i];
        chave+=(i*letrinha);
    }
    return (chave%quantGavetas);
}

int main (){
    int quantArquivos;
    cin >> quantArquivos;

    string arquivosIniciaisNomes [quantArquivos];
    int arquivosIniciaisIds [quantArquivos];
    for (int i=0; i<quantArquivos; i++){
        string nome;
        cin >> nome;
        arquivosIniciaisNomes[i] = nome;
        int id;
        cin >> id;
        arquivosIniciaisIds[i] = id;
    }

    int quantGavetas;
    cin >> quantGavetas;

    gaveta gavetas[quantGavetas];

    int quantArqTransf;
    cin >> quantArqTransf;
    for (int i=0; i<quantArqTransf; i++){
        int idProcurado;
        cin >> idProcurado;
        int posEncontrada = buscaBinaria(arquivosIniciaisIds, quantArquivos, idProcurado);
        int posGavetas = dispersao(arquivosIniciaisNomes[posEncontrada], quantGavetas);
        gavetas[posGavetas].add(arquivosIniciaisNomes[posEncontrada], idProcurado);
    }

    for (int i=0; i<quantGavetas; i++){
        cout << i << ": " << gavetas[i].acessoTam() << endl;

    }

    int quantArqConsult;
    cin >> quantArqConsult;
    for (int i=0; i<quantArqConsult; i++){
        string nomeProcurado;
        cin >> nomeProcurado;
        cout << i << ": " << gavetas[dispersao(nomeProcurado, quantGavetas)].procurar(nomeProcurado) << endl;
    }

    return 0;
}
