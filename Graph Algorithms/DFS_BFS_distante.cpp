#include <iostream>
#include<vector>
#include <queue>
//pentru memeset
#include<cstring>
#include<stack>
#include<fstream>
#include<set>
using namespace std;
ifstream fin("text.in");
const int NMAX=100000;
set<int> G[NMAX+1]; // lista de adiacenta
int d[NMAX+1];
bool vis[NMAX+1];

void DFS2(int x){
    stack<int> stk;
    vis[x]=1;
    cout<<x<<" ";
    stk.push(x);
    while(!stk.empty()){
        int noduriVizitate=0;
        x=stk.top();
        for(auto nod:G[x]){
            noduriVizitate+=vis[nod];
            if(!vis[nod]){
                cout<<nod<<" ";
                vis[nod]=1;
                stk.push(nod);
                break;
            }
        }
        if(noduriVizitate==int(G[x].size())){
            stk.pop();
        }
    }
}
void DFS1(int x){
    cout<<x<<" ";
    vis[x]=true;

    for(auto listNode:G[x]){
        if(!vis[listNode]){
            DFS1(listNode);
        }
    }
}

void BFS(int x){
    queue<int> q;
    q.push(x); //incepem cu primul nod
    d[x]=0;
    vis[x]=true;

    while(!q.empty()){
        x=q.front(); // luam nodul
        q.pop(); // il scoatem
        cout<<x<<" "; // se afiseaza
        for(auto listNode:G[x]){ // intram in nodurile adiacente
            if(!vis[listNode]){ // daca nu a fost vizitat se adauga
                q.push(listNode);
                d[listNode]=d[x]+1;
                vis[listNode]=true;
            }
        }
    }
}

int main() {

    memset(vis,0,NMAX+1);
    int n,m;
    fin>>n>>m; // cate noduri cate muchii
    while(m--){
        int x,y; // se citeste o legatura
        fin>>x>>y;
        G[x].insert(y); // se adauga la lista
    }
    BFS(1);
    cout<<endl;
//    for(int i=1;i<=n;i++)
//        cout<<d[i]<<" ";
//    cout<<endl;
//    memset(vis,0,NMAX+1);
//
//    DFS1(1);
//    memset(vis,0,sizeof(vis));
//    DFS2(1);
    /*
     9 12
     1 5
     1 9
     1 3
     3 2
     2 5
     3 6
     6 9
     9 7
     9 8
     7 4
     4 8
     4 9

     */
    return 0;
}
