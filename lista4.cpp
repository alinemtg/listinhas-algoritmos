/* O Hospital Universitário 
 https://iudex.io/problem/5bb8204ffcc3820001202507/statement */

#include <bits/stdc++.h>
using namespace std;


struct paciente {
    int urgencia;
    int idade;
    int ordemChegada;

    paciente (int urgencia, int idade, int ordemChegada): urgencia(urgencia), idade(idade), ordemChegada(ordemChegada) {}
};

void bubbleUp (paciente* fila[], int posicaoProblematica){
    while (posicaoProblematica>0 && (  (fila[posicaoProblematica]->urgencia > fila[(int)floor((posicaoProblematica-1)/2)]->urgencia) ||
                                       (fila[posicaoProblematica]->urgencia == fila[(int)floor((posicaoProblematica-1)/2)]->urgencia && fila[posicaoProblematica]->idade > fila[(int)floor((posicaoProblematica-1)/2)]->idade) ||
                                       (fila[posicaoProblematica]->urgencia == fila[(int)floor((posicaoProblematica-1)/2)]->urgencia && fila[posicaoProblematica]->idade == fila[(int)floor((posicaoProblematica-1)/2)]->idade
                                        && fila[posicaoProblematica]->ordemChegada < fila[(int)floor((posicaoProblematica-1)/2)]->ordemChegada) )){
        paciente* pacienteAux = fila[posicaoProblematica];
        fila[posicaoProblematica] = fila[(int)floor((posicaoProblematica-1)/2)];
        fila[(int)floor((posicaoProblematica-1)/2)] = pacienteAux;

        posicaoProblematica = (int)(floor((posicaoProblematica-1) / 2));
    }
}

void inserir (paciente* fila[], int tamFila, int capacFila, int urgencia, int idade, int ordemChegada){
    auto * pacienteAux = new paciente (urgencia, idade, ordemChegada);

    fila[tamFila] = pacienteAux;
    bubbleUp(fila, tamFila);
}

void heapify (paciente* fila[], int tamFila, int posicao){
    int l = 2*posicao+1;
    int r = 2*posicao+2;
    int m = posicao;

    if (l<tamFila && (  (fila[l]->urgencia > fila[m]->urgencia) || (fila [l]->urgencia == fila[m]->urgencia && fila[l]->idade > fila[m]->idade) ||
                        (fila[l]->urgencia == fila[m]->urgencia && fila[l]->idade == fila[m]->idade && fila[l]->ordemChegada < fila[m]->ordemChegada) ) ){
        m = l;
    }
    if (r<tamFila && (  (fila[r]->urgencia > fila[m]->urgencia) || (fila [r] ->urgencia == fila[m]->urgencia && fila[r]->idade > fila[m]->idade) ||
                        (fila[r]->urgencia == fila[m]->urgencia && fila[r]->idade == fila[m]->idade && fila[r]->ordemChegada < fila[m]->ordemChegada) ) ){
        m = r;
    }
    if (m!=posicao){
        paciente* pacienteAux = fila [posicao];
        fila[posicao] = fila[m];
        fila[m] = pacienteAux;
        heapify(fila, tamFila, m);
    }

}

paciente* retirar (paciente* fila[], int tamFila){
    paciente* pacienteAux = fila[tamFila-1];
    fila[tamFila-1] = fila[0];
    fila[0] = pacienteAux;
    tamFila -= 1;
    heapify (fila, tamFila, 0);
    return fila[tamFila];
}

int main (){
    int numServicos;
    cin >> numServicos;
    int tamFilas [numServicos];
    int capacidadeFilas[numServicos];
    paciente** filasServicos[numServicos];

    for (int i=0; i<numServicos; i++){
        tamFilas[i] = 0;
        capacidadeFilas[i] = 4;
        filasServicos[i] = new paciente* [4];
    }

    string evento;
    int ordemChegada = 0;

    while(cin >> evento && evento!= "END"){

        if (evento == "CIN"){
            int idade, urgencia, servico;
            cin >> idade >> urgencia >> servico;

            if (tamFilas[servico] == capacidadeFilas[servico]){
                auto ** filaAux = new paciente* [capacidadeFilas[servico]*2];
                for (int i=0; i<tamFilas[servico]; i++){
                    filaAux[i] = filasServicos[servico][i];
                }
                filasServicos[servico] = filaAux;
                capacidadeFilas[servico] = capacidadeFilas[servico]*2;
            }

            inserir(filasServicos[servico], tamFilas[servico], capacidadeFilas[servico], urgencia, idade, ordemChegada);
            tamFilas[servico] += 1;
            ordemChegada ++;
        }

        if (evento == "STD"){
            int servicoAtendido = -1;
            int aux = -1;
            auto * pacienteAtendido = new paciente (-1, -1, -1);
            for (int i=0; i<numServicos; i++){
                if (tamFilas[i] > 0){
                    servicoAtendido = i;
                    aux = i;
                    break;
                }
            }
            if (servicoAtendido != -1) {
                for (int i=aux+1; i<numServicos; i++){
                    if (tamFilas[i] > 0 && (
                            (filasServicos[i][0]->urgencia < filasServicos[servicoAtendido][0]->urgencia) ||
                            (filasServicos[i][0]->urgencia == filasServicos[servicoAtendido][0]->urgencia && filasServicos[i][0]->idade < filasServicos[servicoAtendido][0]->idade) ||
                            (filasServicos[i][0]->urgencia == filasServicos[servicoAtendido][0]->urgencia && filasServicos[i][0]->idade == filasServicos[servicoAtendido][0]->idade &&
                             filasServicos[i][0]->ordemChegada < filasServicos[servicoAtendido][0]->ordemChegada))) {
                        servicoAtendido = i;
                    }
                }
                pacienteAtendido = retirar(filasServicos[servicoAtendido], tamFilas[servicoAtendido]);
                tamFilas[servicoAtendido] -= 1;
            }
            cout << servicoAtendido << " " << pacienteAtendido->idade << " " << pacienteAtendido->urgencia << endl;
        }

        if (evento == "NXT"){
            int fila;
            cin >> fila;
            int servicoAtendido = -1;
            auto * pacienteAtendido = new paciente (-1, -1, -1);

            if (tamFilas[fila]>0){
                pacienteAtendido = retirar(filasServicos[fila], tamFilas[fila]);
                servicoAtendido = fila;
                tamFilas[fila] -= 1;
            }
            cout << servicoAtendido << " " << pacienteAtendido->idade << " " << pacienteAtendido->urgencia << endl;
        }


    }

    return 0;
}

