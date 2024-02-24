#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<algorithm>
#include<climits>
#include<set>
using namespace std;
ifstream fin("text.in");
int n,m;
vector<vector<int>> adqMatrix;
vector<vector<int>> maskMatrix;

bool testHamilton(){
    // exista lant hamiltonian de la j la j
    for(int j=0;j<n;++j)
        maskMatrix[j][(1<<j)] = 1;

    // se parcurg submultimile
    for(int i=0;i<(1<<n);++i){

        // se parcurg nodurile
        for(int j=0;j<n;++j){

            // daca nodul curent e din submultimea curenta
            if(i & (1<<j)){

                // se cauta prin noduri iarasi
                for(int k=0;k<n;++k){

                    // se verifica daca exista un nod din submultimea curenta
                    // care sa formeze un lant hamiltonian care incepe din el in multimea i / j
                    // daca exista inseamna ca si lantul ce incepe in j in submultimea i e hamiltonian
                    if( k!=j
                        && adqMatrix[j][k]
                        && i & (1<<k) &&
                        maskMatrix[k][i ^ (1<<j)]){

                        maskMatrix[j][i] = 1;
                        break;
                    }

                }

            }

        }

    }

    // se verifica la final daca exista lant de la fiecare nod la submultimea ce contine toate nodurile
    for(int j=0;j<n;++j){
        if(maskMatrix[j][(1<<n)-1])
            return true;
    }
    return false;

}

void containerInit(int n){

    adqMatrix.resize(n);
    for(auto& row : adqMatrix)
        row.resize(n);

    maskMatrix.resize(n);
    for(auto& row : maskMatrix)
        row.resize((1<<n));
}

int main(){
    fin>>n>>m;
    containerInit(n);

    while(m--){
        int x,y,cost;
        fin>>x>>y>>cost;
        adqMatrix[x][y]=cost;
        adqMatrix[y][x]=cost;
    }

    cout<<testHamilton()<<endl;

    for(int j=0;j<n;++j){
        for(int i=0; i< (1<<n);++i)
            cout<<maskMatrix[j][i]<<" ";
        cout<<endl;
    }

    cout<<endl;
    for(int j=0;j< n;++j)
        cout<<maskMatrix[j][(1<<n)-1]<<" ";
}

//5 10
//0 1 9
//0 3 8
//1 0 7
//1 2 1
//1 4 3
//2 0 5
//2 4 4
//3 2 6
//4 3 7
//4 1 1