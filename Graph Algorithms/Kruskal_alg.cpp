#include<iostream>
#include<vector>
#include<set>
#include<utility>
#include<fstream>
#include<algorithm>
using namespace std;

struct Edge{
    int node1;
    int node2;
    int cost;

    bool operator<(const Edge& e){
        return (cost<e.cost)||(cost==e.cost&&node1<e.node1)||(cost==e.cost&&node1==e.node1&&node2<e.node2);
    }
};

ifstream fin("text.in");
vector<Edge> muchii;
vector<Edge> MSP;
vector<int> parent;
vector<int> height;
int n,m;


int Find(const int&x){
    if(parent[x]==0)
        return x;
    parent[x]=Find(parent[x]);
    return parent[x];
}

void Union(const int&x,const int&y){
    int v,u;
    v=Find(x);
    u=Find(y);

    if(v!=u){
        if(height[v]>height[u])
            parent[u]=v;
        else{
            parent[v]=u;
            if(height[v]==height[u])
                ++height[u];
        }
    }

}

void Kruskal(){

    sort(muchii.begin(),muchii.end());

    for(const auto& muchie:muchii){
        int v,u;
        v=Find(muchie.node1);
        u=Find(muchie.node2);
        if(v!=u){
            MSP.push_back(muchie);
            Union(u,v);
        }
    }

}

int main(){

    fin>>n>>m;
    parent.resize(n+1);
    height.resize(n+1);
    while(m--){

        Edge muchie;
        fin>>muchie.node1>>muchie.node2>>muchie.cost;
        muchii.push_back(muchie);
    }
    Kruskal();

    for(const auto& muchie:MSP){
        cout<<muchie.node1<<" "<<muchie.node2<<" "<<muchie.cost<<endl;
    }


    return 0;
}