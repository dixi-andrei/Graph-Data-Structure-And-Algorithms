#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<algorithm>
#include<climits>
#include<limits>
#include<utility>
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
int n,m;
vector<int>internalDegree;
vector<vector<pair<int,int>>> adq;
queue<int> topologicalSort;

// long long pentru distante pentru a nu avea overflow si se initilizeaza fiercare cu INT_MAX
vector<long long>distances;
vector<int>parent;


//sortare topologica cu Kahn
void TopologicalSorting(){

    queue<int>q;

    for(int i=1;i<=n;++i){
        if(!internalDegree[i]){
            q.push(i);
        }
    }

    while(!q.empty()){
        int x=q.front();
        topologicalSort.push(x);
        q.pop();

        for(const auto& next:adq[x]){
            int nextNode=next.first;

            if(!(--internalDegree[nextNode]))
                q.push(nextNode);
        }

    }

    for(int i=1;i<=n;++i){
        if(internalDegree[i]){
            cout<<"Cicle found"<<endl;
            return;
        }
    }
}

void Dag_distances(const int& start){

    distances[start]=0;

    // se pot sari peste nodurile in care nu se pot ajunge din start
    while(topologicalSort.front()!=start)
        topologicalSort.pop();

    // pentru fiecare nod pe rand din sortarea topologica se relaxeaza fiecare muchie adiacenta
    while(!topologicalSort.empty()){
        int currentNode=topologicalSort.front();
        topologicalSort.pop();

        for(const auto&next:adq[currentNode]){
            int nextNode=next.first;
            int cost=next.second;

            //operatia de relaxare
            if(distances[nextNode]>cost+distances[currentNode]){
                distances[nextNode]=cost+distances[currentNode];
                parent[nextNode]=currentNode;

            }
        }

    }
}

void containerInit(const int&n){
    adq.resize(n);
    internalDegree.resize(n);

    parent.resize(n);
    distances.resize(n);

    // se initializeaza cu ceva aproape de infinit pentru a nu se da overflow
    std::fill(distances.begin(), distances.end(),INT_MAX);
    fill(internalDegree.begin(), internalDegree.end(),0);

}

int main(){

    //citire date
    fin>>n>>m;
    containerInit(n+1);
    while(m--){
        int x,y,cost;
        fin>>x>>y>>cost;

        adq[x].emplace_back(make_pair(y,cost));
        internalDegree[y]++;

    }

    TopologicalSorting();

    Dag_distances(1);


    for(int i=1;i<=n;++i){
        cout<<distances[i]<<" ";
    }

    return 0;
}
//6 6
//1 2 7
//4 3 12
//2 3 4
//3 6 30
//2 6 4
//3 5 30
