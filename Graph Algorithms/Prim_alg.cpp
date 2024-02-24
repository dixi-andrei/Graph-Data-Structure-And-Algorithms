#include<iostream>
#include<vector>
#include<fstream>
#include<climits>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

ifstream fin("text.in");
int n,m,noNodesMST;

vector<vector<pair<int,int>>> listaAdiacenta;
vector<pair<int,int>> minCostParent;
vector<int>inMst;
priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;

void Prim(int x=1){

        // se incepe cu primul nod
        minCostParent[x]= make_pair(0,0);
        //se adauga la heap
        // de forma (cost,nod)
        pq.push(make_pair(0,x));

        while(!pq.empty()){
            // se extrage nodul de pe heap
            x=pq.top().second;
            // inseamna ca e solutie deci se adauga
            inMst[x]=1;
            // se scoate
            pq.pop();
            //pentru eficienta
            noNodesMST++;

            if(noNodesMST==n)
                break;


            // parcurgem nodurile adiacente
            for(const auto& costNode : listaAdiacenta[x]){
                int node=costNode.second;
                int cost=costNode.first;

                // daca nodul nu e in APM si totodata costul este minim pentru acel nod
                if(!inMst[node]&& cost<minCostParent[node].first){

                    // se adauga costul si parintele
                    minCostParent[node]= make_pair(cost,x);
                    // se introduce in heap
                    pq.push(make_pair(cost,node));
                }
            }

        }
    
}

void containerResize(const int&x){
    minCostParent.resize(x);
    fill(minCostParent.begin(),minCostParent.end(), make_pair(INT_MAX,-1));

    inMst.resize(x);

    listaAdiacenta.resize(x);

}

int main(){
    fin>>n>>m;

    containerResize(n+1);


    // o sa fie stocate de forma (cost,nod)
    while(m--)
    {
        int x,y,cost;
        fin>>x>>y>>cost;
        listaAdiacenta[x].push_back(make_pair(cost,y));
        listaAdiacenta[y].push_back(make_pair(cost,x));
    }

    Prim(1);

    for(int i=1;i<=n;i++){
        cout<<minCostParent[i].second<<" "<<minCostParent[i].first<<endl;
    }

    return 0;
}
/*

*/