#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
ifstream fin("text.in");

int n,m;
vector<vector<long long>> distances;
vector<vector<int>> parent;


void Floyd(){

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j){
                if(distances[i][j]>distances[i][k]+distances[k][j]){
                    distances[i][j]=distances[i][k]+distances[k][j];
                    parent[i][j]=parent[k][j];
                }
            }
    }

    for(int i=1;i<=n;++i){
        if(distances[i][i]){
            cout<<"circuir negativ"<<endl;
            break;
        }
    }
}
void drum(int i,int j){
    if(i!=j){
        drum(i,parent[i][j]);
    }
    cout<<j<<" ";
}
int main(){

    fin>>n>>m;
    distances.resize(n+1);
    parent.resize(n+1);

    for(int i=1;i<=n;++i){
        distances[i].resize(n+1);
        parent[i].resize(n+1);

        fill(distances[i].begin(), distances[i].end(),INT_MAX);
        distances[i][i]=0;

    }

    while(m--){
        int x,y,cost;

        fin>>x>>y>>cost;

        distances[x][y]=cost;
        parent[x][y]=x;
        //distances[y][x]=cost;
        //parent[x][y]=y;
    }

    Floyd();

    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            cout<<distances[i][j]<<" ";
        }
        cout<<endl;
    }


    return 0;
}

//4 8
//4 3 16
//3 4 2
//2 3 3
//1 3 10
//4 2 20
//1 4 1
//4 1 3
//1 2 5