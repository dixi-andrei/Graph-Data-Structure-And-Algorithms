#include<iostream>
#include<vector>
#include<set>
#include<cstring>
#include<fstream>
using namespace std;
ifstream fin("text.in");
ofstream fout("text.out");
vector<set<int>>listaAdiacenta;
vector<int> vizite;
vector<int> nivel;
vector<int> low;
vector<int> isArticulation;
int n,m,root,rootChildren;

void containerResize(const int &x) {
    listaAdiacenta.resize(x);
    vizite.resize(x);
    nivel.resize(x);
    low.resize(x);
    isArticulation.resize(x);
}

void articulationDFS(const int&x,const int&parent=0){
    nivel[x]=nivel[parent]+1; // nivelul curent e cel al parintelui plus 1
    low[x]=nivel[x]; // momentan ramane egal cu nivelul
    vizite[x]=1;
    for(const auto& node:listaAdiacenta[x]){
        rootChildren+=1*(x==root); // daca e radacina ii numaram copiii
        if(!vizite[node]){  // cand nu e vizitat
            articulationDFS(node,x);
            // dupa ce cunoasteam low al copiilor
            low[x]=min(low[x],low[node]); // dam update la low-ul nodului curent
            //daca e radacina si are mai mult de un copil e nod de articulatie
            //sau
            // daca nu e radacina si nu exista un drum de intoarcele la un nivel mai inalt de nivelul sau e nod de articulatie
            isArticulation[x]=1*(x!=root&&low[node]>=nivel[x]||x==root&&rootChildren>1);
        }
        else if(node!=parent){ // daca deja e vizitat si nu e parinte

            low[x]=min(low[x],nivel[node]); // calculcam la ce nivel poate sa se intoarca
        }
    }

}

int main(){
    fin>>n>>m;
    containerResize(n+1);
    while(m--){
        int x,y;
        fin>>x>>y;
        listaAdiacenta[x].insert(y);
        listaAdiacenta[y].insert(x);
    }
    for(int i=1;i<=n;i++){
        root=i;
        if(!vizite[i])
            articulationDFS(i,0);
        if(isArticulation[i])
            cout<<i<<" ";
    }

    return 0;
}