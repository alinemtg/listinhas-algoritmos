/* O Detetive
 https://iudex.io/problem/5c0295e25cd44b0001fdc280/statement */

#include <bits/stdc++.h>
using namespace std;

int d[3000][50000];
void quinapisaqui (int v[], int w[], int k, int n){

    for (int i=0; i<n+1; i++){
        for (int j=0; j<k+1; j++){
            d[i][j] = 0;
        }
    }

    for (int m=1; m<=n ; m++) {
        for (int j=1; j<=k; j++){
            if (w[m-1] <= j){
                d[m][j] = max(d[m-1][j], v[m-1] + d[m-1][j-w[m-1]]);
            }else{
                d[m][j] = d[m-1][j];
            }
        }
    }

    // FAZENDO A SAIDA
    string saidaa = "";
    int i = n;
    int j = k;
    while (i!=0 && j!=0){
        if (d[i][j] != d[i-1][j]){
            saidaa = to_string(i-1) + " " + saidaa;
            j = j-w[i-1];
        }i--;
    }
    cout << d[n][k] << endl;
    cout << saidaa.substr(0, saidaa.length()-1) << endl;
};


int main (){
    int quantItens, capacidade;
    cin >> quantItens >> capacidade;

    int valoretes [quantItens];
    int pesotes [quantItens];

    for (int i=0; i<quantItens; i++){
        cin >> valoretes [i];
        cin >> pesotes[i];

    }

    quinapisaqui(valoretes, pesotes, capacidade, quantItens);

    return 0;
}
