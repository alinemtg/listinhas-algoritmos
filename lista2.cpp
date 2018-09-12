#include <bits/stdc++.h>;
using namespace std;

// ~~~ NODE ~~~
struct node {
    string nome;
    int id;
    node *next;

    // CONSTRUTOR DO NODE
    node(string nome, int id): nome(nome), id(id), next(nullptr) {}
};

// ~~~ FILA ~~~
struct fila {
    node *front;
    node *rear;
    int tam;

    // CONSTRUTOR DA FILA
    fila (): front(nullptr), rear(nullptr), tam(0) {}

    void add (string nome, int id){
        node *aux = new node (nome, id);
        if (this->rear){
            this->rear->next = aux;
            this->rear = aux;
        }else{
            this->front = aux;
            this->rear = aux;
        }
    }

    node* remove (){
        node *aux = this->front;
        if (this->front){
            this->front = this->front->next;
        }
        tam--;
        return aux;
    }
};

// ~~~ METODOS DA QUESTAO ~~~

int buscaBinaria (int ids[], int idProcurado){
    int iniAux = 0;
    int fimAux = (sizeof(ids)/sizeof(int))-1;
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

int dispersao (int chave, int quantGavetas){
    return (chave%quantGavetas);
}

int obterChave (string nome){
    int chave = 0;
    for (int i=0; i<nome.length(); i++){
        chave+=(i*nome[i]);
    }
    return chave;
}

int main (){

    // ~~~ LEITURA DOS ARQUIVOS LA NO INICIO ~~~
    int quantArquivosInicial;
    cin >> quantArquivosInicial;

    string arquivosInicioNome [quantArquivosInicial];
    int arquivosInicioId [quantArquivosInicial];
    for (int i=0; i<quantArquivosInicial; i++){
        string nome;
        int id;
        cin >> nome >> id;
        arquivosInicioNome[i] = nome;
        arquivosInicioId[i] = id;
    }

    int quantGavetas, quantArquivosSeraoTransf;
    cin >> quantGavetas;
    cin >> quantArquivosSeraoTransf;
    fila gavetas [quantGavetas];
    for (int i=0; i<quantArquivosSeraoTransf; i++){
        int idProcurado;
        cin >> idProcurado;
        int posArqTransf = buscaBinaria(arquivosInicioId, idProcurado);
        cout << posArqTransf;
        gavetas[dispersao(obterChave(arquivosInicioNome[posArqTransf]),quantGavetas)].add(arquivosInicioNome[posArqTransf], arquivosInicioId[posArqTransf]);
    }

    // IMPRIMIR QUANTOS ARQUIVOS TEM EM CADA GAVETA
    for (int i=0; i<quantGavetas; i++){
        cout << i << ": " << gavetas[i].tam << endl;
    }

    // ANALISE DA EFICIENCIA, OU SEJE, DE CATAR OS ARQUIVOS
    int quantArquivosConsult;
    cin >> quantArquivosConsult;



    return 0;
}