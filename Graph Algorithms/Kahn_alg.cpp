#include<iostream>
#include<stack>
#include<vector>
#include<set>
#include<fstream>
#include<queue>
using namespace std;
vector<set<int>>listaAdiacenta;
vector<int>gradIntern;
queue<int> sortareTopologica;
ifstream fin("text.in");
int n,m;

void resizeContainers(int x){
    listaAdiacenta.resize(x);
    gradIntern.resize(x);
}

void KahnTopologicalSorting(){
    //incepem cu o coada goala
    queue<int> q;
    // se adauga toate nodurile cu gradul intern 0
    for(int i=1;i<=n;++i){
        if(!gradIntern[i])
            q.push(i);
    }
    // cat timp coada nu este goalka
    while(!q.empty()){
        int x=q.front(); // se extrage primul element din coada
        q.pop();
        sortareTopologica.push(x); // se adauga la output
        for(const auto& node:listaAdiacenta[x]){ //se scade cu 1 gradul fiecarui nod adiacent cu nodul extras
            if(!(--gradIntern[node])){ // daca gradul nodului e 0
                q.push(node); // se adauga la coada
            }

        }
    }

    // se verifica daca exista cicluri daca mai exsiat grad intern diferit de 0
    for(int i=1;i<=n;++i){
        if(gradIntern[i]){
            cout<<"IMPOSSIBLE";return;
        }
    }
    // se afiseaza outputul daca graful este aciclic
    while(!sortareTopologica.empty()){
        cout<<sortareTopologica.front()<<" ";
        sortareTopologica.pop();
    }
}

int main(){
    cin>>n>>m;
    resizeContainers(n+1);
    while(m--){
        int x,y;
        cin>>x>>y;
        // in caz ca se repeta
        if(listaAdiacenta[x].find(y)==listaAdiacenta[x].end()){
            listaAdiacenta[x].insert(y);
            ++gradIntern[y];
        }

    }

    KahnTopologicalSorting();

    return 0;
}