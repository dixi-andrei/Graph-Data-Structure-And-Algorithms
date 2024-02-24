#include<iostream>
#include<vector>
#include<fstream>
#include<limits>
#include<climits>
#include<algorithm>
using namespace std;
ifstream fin("text.in");
int n,m;

vector<vector<pair<int,int>>> adq;


vector<int> parent;
vector<long long> distances;

void BellmanFord(const int& start){


    distances[start]=0;


    for(int i=1;i<=n-1;++i){

        for(int current=1;current<=n;current++){

            for(const auto& next: adq[current]){
                int nextNode=next.first;
                int cost=next.second;

                if(distances[nextNode]>cost+distances[current]){
                    distances[nextNode]=cost+distances[current];
                    parent[nextNode]=current;
                }

            }
        }
    }

    for(int current=1;current<=n;current++){

        for(const auto& next: adq[current]){
            int nextNode=next.first;
            int cost=next.second;

            if(distances[nextNode]>cost+distances[current]){
                distances[nextNode]=cost+distances[current];
                parent[nextNode]=current;

                cout<<"Circuit de cost negativ"<<endl;

                current=n;
                break;
            }

        }
    }

}


void containerInit(const int &n){
    adq.resize(n);
    parent.resize(n);
    distances.resize(n);

    fill(distances.begin(), distances.end(),INT_MAX);
}

int main(){

    fin>>n>>m;
    containerInit(n+1);
    while(m--){
        int x,y,cost;
        fin>>x>>y>>cost;

        adq[x].push_back(make_pair(y,cost));
        //adq[y].push_back(make_pair(x,cost));

    }

    BellmanFord(1   );

    for(int i=1;i<=n;++i){
        cout<<distances[i]<<" ";
    }

    return 0;
}
//5 6
//1 3 7
//1 2 5
//3 2 -3
//2 4 1
//4 3 3
//4 5 -1