#include <bits/stdc++.h>
using namespace std;


struct paciente {
    int urgencia;
    int idade;
    int ordemChegada;

    heap (int urgencia, int idade, int ordemChegada): urgencia(urgencia), idade(idade), ordemChegada(ordemChegada) {}
}*

void inserir (paciente* fila[], int tamFila, int urgencia, int idade, int ordemChegada){
    paciente* pacienteAux = new paciente (urgencia, idade, ordemChegada);
    int capacidade = sizeof(fila)/ sizeof(fila[0])

    if (tamFila == capacidade){
        paciente* filaAux [capacidade*2];
        for (int i=0; i<tamFila; i++){
            filaAux[i] = fila[i];
        }
        fila = filaAux;
    }

    fila[tamFila] = pacienteAux;
    fila.bubbleUp(fila, tamFila-1);
}

void bubbleUp (paciente* fila, int posicaoProblematica){
    while (posicaoProblematica>0 && fila[posicaoProblematica].urgencia>fila[(posicaoProblematica-1)/2]){
        paciente* pacienteAux = fila[posicaoProblematica];
        fila[posicaoProblematica] = fila[(posicaoProblematica-1)/2];
        fila[(posicaoProblematica-1)/2] = pacienteAux;

        posicaoProblematica = (posicaoProblematica-1)/2
    }
}


int main (){
    int numServicos;
    cin >> numServicos;

    paciente* filasServico[numServicos][5];
    int tamFilas [numServicos];

    for (int i=0; i<numServicos; i++){
        string evento;
        cin >> evento;
        if (evento == "CIN"){
            int idade, urgencia, servico;
            cin >> idade >> urgencia >> servico;

        }else if (evento == "NXT"){
            int fila;
            cin >> fila;
        }else{
            //atendimento estudantes
        }
    }

    return 0;
}