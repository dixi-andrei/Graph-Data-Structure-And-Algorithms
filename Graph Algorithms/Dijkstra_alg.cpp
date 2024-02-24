#include<iostream>
#include<vector>
#include<queue>
#include<limits>
#include<climits>
#include<utility>
#include<algorithm>
#include<fstream>
using namespace std;
ifstream fin("text.in");
int n,m;
vector<vector<pair<int,int>>> adq;
vector<long long>distances;
vector<int>parent;

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

//varianta cu priority queue
void Dijkstra(const int& start){
    // se alege un nod de start a carui distanta se initializeaza cu 0

    distances[start]=0;

    // se pune pe priority queue
    pq.push(make_pair(0,start));

    // garantat dupa n iteratii o sa avem rapunsul
    for(int i=1;i<=n;i++){
        // se extrage nodul curent
        int x=pq.top().second;
        int distance=pq.top().first;
        pq.pop();

        // se foloseste operatia de relaxare pe fiecare nod din lista de adiacenta a lui x
        for(const auto& next: adq[x]){
            int nextNode=next.first;
            int cost=next.second;

            if(distances[nextNode]>cost+distances[x]){
                distances[nextNode]=cost+distances[x];
                parent[nextNode]=x;
                // se da push la noile valori
                pq.push(make_pair(distances[nextNode],nextNode));

            }
        }
    }
}

void containerInit(const int&n){
    adq.resize(n);
    distances.resize(n);
    parent.resize(n);

    fill(distances.begin(), distances.end(),INT_MAX);
    fill(parent.begin(), parent.end(),0);
}

int main(){

    //citire date

    fin>>n>>m;
    containerInit(n+1);
    while(m--){
        int x,y,cost;
        fin>>x>>y>>cost;

        adq[x].emplace_back(make_pair(y,cost));

        //adq[y].emplace_back(make_pair(x,cost));
    }

    Dijkstra(1);

    for(int i=1;i<=n;++i){
        cout<<distances[i]<<" ";
    }

    

    return 0;
}