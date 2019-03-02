/* T&TA
 https://iudex.io/problem/5be0f9165cd44b0001fdc002/statement */

#include <bits/stdc++.h>
using namespace std;

// ~~~ HEAP ~~~
vector<pair<int, float>> bubbleUp (vector<pair<int, float>> &H, int i){
    while (i>0 && H[i].second < H[(i-1)/2].second){
        swap(H[i], H[(i-1)/2]);
        i = (i-1)/2;
    }
    return H;
}

void heap_insert (vector<pair<int, float>> &H, pair<int, float> v){
    H.emplace_back(v);
    bubbleUp(H, H.size()-1);
}

vector<pair<int, float>> heapify (vector<pair<int, float>> &H, int i){
    int l = 2*i + 1;
    int r = 2*i + 2;
    int m = i;

    if (l < H.size() && H[l].second >= H[m].second){
        m = l;
    }if (r < H.size() && H[r].second >= H[m].second){
        m = r;
    }if (m != i){
        swap(H[i], H[m]);
        heapify (H, m);
    }
}

pair<int, float> heap_extract (vector<pair<int, float>> &H){
    swap(H[0], H[H.size()-1]);
    pair<int, float> removido = H[H.size()-1];
    H.pop_back();
    return removido;
}

// ~~~ DIGISTRA E ETC ~~~
void digistra (vector<pair<int, float>> links[], int s, int quantNodes, int t){
    float D [quantNodes];
    int F [quantNodes];

    for (int e=0; e<quantNodes; e++){
        D[e] = FLT_MAX;
        F[e] = -1;
    }
    D[s] = 0;
    vector <pair<int, float>> heap;
    heap_insert(heap, {s, 0});

    while (!heap.empty()){
        pair<int,float> pairR = heap_extract (heap); // pairRemovido
        for (auto &e  : links[pairR.first]){
            if (pairR.second + e.second < D[e.first]){
                D[e.first] = pairR.second + e.second;
                F[e.first] = pairR.first;
                heap_insert(heap, {e.first, D[e.first]});
            }
        }
    }

    cout << t;
    int posicaoAnalisada = t;
    while (true){
        if (posicaoAnalisada == s)
            break;
        cout << " " << F[posicaoAnalisada];
        posicaoAnalisada = F[posicaoAnalisada];
    }
    cout << endl;
}

// ~~~ MAINN ~~~
int main() {
    float prioridade;
    int quantNodes, quantLinks;
    cin >> prioridade >> quantNodes >> quantLinks;
    vector<pair<int, float>> links [quantNodes];

    for (int i=0; i<quantLinks; i++){
        int x, y, b, c;
        cin >> x >> y >> b >> c;

        float peso = (prioridade*b + (1-prioridade)*c) / (b+c);
        links[x].push_back({y, peso});
        links[y].push_back({x, peso});
    }

    int s, t;
    while (cin >> s >> t){
        digistra(links, t, quantNodes, s);
    }

    return 0;
}
