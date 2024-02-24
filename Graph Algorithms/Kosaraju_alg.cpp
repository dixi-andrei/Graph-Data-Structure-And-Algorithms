#include<iostream>
#include<vector>
#include<set>
#include<stack>
#include<fstream>
#include<algorithm>
using namespace std;
ifstream fin("text.in");
vector<set<int>> listaAdiacentaG;
vector<set<int>> listaAdiacentaGT;
vector<int>vizite;
stack<int> S;
int n,m;

void KosarajuDFS_G(const int& x){

    vizite[x]=1;
    for(const auto& node:listaAdiacentaG[x]){
        if(!vizite[node]){
            KosarajuDFS_G(node);
        }
    }
    S.push(x);
}

void KosarajuDFS_GT(const int& x){
    cout<<x<<" ";
    vizite[x]=1;
    for(const auto& node:listaAdiacentaGT[x]){
        if(!vizite[node]){
            KosarajuDFS_GT(node);
        }
    }
}

void containerResize(const int&x){
    listaAdiacentaG.resize(x);
    listaAdiacentaGT.resize(x);
    vizite.resize(x);
}

int main(){
    fin>>n>>m;
    containerResize(n+1);
    while(m--){
        int x,y;
        fin>>x>>y;
        listaAdiacentaG[x].insert(y);
        listaAdiacentaGT[y].insert(x);
    }
    for(int i=1;i<=n;++i){
        if(!vizite[i]){
            KosarajuDFS_G(i);
        }
    }
    fill(vizite.begin(),vizite.end(),0);
    while(!S.empty()){
        int x=S.top();
        S.pop();
        if(!vizite[x]){
            KosarajuDFS_GT(x);
            cout<<endl;
        }
    }
    return 0;
}

/*
 Cum in DFS cunoastem ordinea parcurgerii fiecarui nod avand in vedere ca se parcurg crescator nodurile,
 in DFS ul transpusei trebuie sa incepem cu nodul final care s-a terminat in DFS grafului initial. Asa ne garanteaza
 o componenta conexa
*/