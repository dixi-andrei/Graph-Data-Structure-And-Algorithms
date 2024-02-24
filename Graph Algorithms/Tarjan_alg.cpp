#include<iostream>
#include<vector>
#include<set>
#include<stack>
#include<fstream>
using namespace std;
ifstream fin("text.in");
vector<set<int>> listaAdiacenta;
vector<int> nodeIndex;
vector<int> lowLink;
vector<int> onStack;
int n,m,index;
stack<int> S;

void resizeContainers(const int&x){
    listaAdiacenta.resize(x);
    nodeIndex.resize(x);
    lowLink.resize(x);
    onStack.resize(x);

    fill(nodeIndex.begin(), nodeIndex.end(), 0);
    fill(lowLink.begin(), lowLink.end(), 0);
    fill(onStack.begin(), onStack.end(), 0);
}
void TarjanDFS(const int& x){
//    nodeIndex[x]=nodeIndex[parent]+1;
//    lowLink[x]=nodeIndex[x];
    nodeIndex[x]=index;
    lowLink[x]=index;

    ++index;
    S.push(x);
    onStack[x]=1;

    for(const auto& node:listaAdiacenta[x]){
        if(!nodeIndex[node]){
            TarjanDFS(node);
            lowLink[x]=min(lowLink[x],lowLink[node]);
        }else if(onStack[node]){
            lowLink[x]=min(lowLink[x],nodeIndex[node]);
        }

    }
    //cout<<x<<" "<<nodeIndex[x]<<" "<<lowLink[x]<<endl;
    if(lowLink[x]==nodeIndex[x]){
        int y;
        do{
            y=S.top();
            S.pop();
            onStack[y]=0;
            cout<<y<<" ";
        }while(y!=x);
        cout<<endl;
    }
}

int main(){
    fin>>n>>m;
    index=1;
    resizeContainers(n+1);
    while(m--){
        int x,y;
        fin>>x>>y;
        listaAdiacenta[x].insert(y);
    }

    for(int i=1;i<=n;i++){
        if(!nodeIndex[i])
            TarjanDFS(i);
    }
    return 0;
}