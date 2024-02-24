#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
#include<limits>
#include<set>
using namespace std;
ifstream fin("text.in");
int n,m,source,sink,k;
vector<vector<int>> adq;
vector<vector<pair<int,int>>> capacity;
vector<int> parent;


void containerInit(const int& n){
    adq.resize(n);
    parent.resize(n);
    capacity.resize(n);
    for(auto& row:capacity){
        row.resize(n);
    }

}

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int findSmallestPrime(int num) {
    if (num <= 1) {
        return 2;
    }
    while (!isPrime(num)) {
        --num;
    }
    return num;
}

int findPathBFS(int startNode=source,int endNode=sink){
    // parintii sa fie -1 marcand un nod nevizitat
    fill(parent.begin(), parent.end(),-1);

    queue<pair<int,int>> q;
    // parintele o sa fie -2 marcand ca este vizitat dar nu are parinte
    parent[startNode]=-2;

    q.emplace(startNode,INT_MAX);

    while(!q.empty()){
        int currentFlow = q.front().second;
        int currentNode = q.front().first;

        q.pop();

        for(const auto& nextNode: adq[currentNode]){
            // testeaza daca nodul e nevizitat si daca mai poate trasnporta flux
            if(parent[nextNode]==-1 && capacity[currentNode][nextNode].second){

                // se salveaza parintele
                parent[nextNode]=currentNode;

                // calculeaza fluxul minim ce se poate transporta pana in nodul curent
                int minFlow=min(currentFlow,capacity[currentNode][nextNode].second);
                // daca nodul este sink ul se returneaza fluxul minim
                if(nextNode==endNode){
                    return minFlow;
                }
                // se da push in q la nodul curent cu fluxul minim pana in el
                q.emplace(nextNode,minFlow);
            }
        }
    }
    // daca nu se gaseste se returneaza 0 ( nu se mai poate trimite flux)
    return 0;
}

void updatePath(const int& flow,int startNode=source,int endNode=sink){

    int currentNode=endNode;

    while(currentNode!=startNode){

        // capacitatea ce se mai poate transmite scade
        capacity[parent[currentNode]][currentNode].second -= flow;
        //creste capacitatea transmisa
        capacity[parent[currentNode]][currentNode].first +=flow;
        // capacitatea care se poate intoarce creste
        capacity[currentNode][parent[currentNode]].second +=flow;
        //capacitatea transmisa = capacitatea ce se poate intoarce * (-1) pentru a stii ca nu e sens direct
        capacity[currentNode][parent[currentNode]].first -=flow;

        currentNode=parent[currentNode];

    }

}


int maxFlow(int startNode=source,int endNode=sink){

    int Flow=0;
    int currentFlow;
    // cat timp se gasesteun path pe care se poate transmite flux
    while((currentFlow = findPathBFS())){

        // se da update la path cu fluxul gasit
        updatePath(currentFlow,startNode,endNode);
    }

    // pentru a calcula flow ul o sa ne uitam pe randul sinkului
    for(int i=1;i<=n;++i)
        Flow+= abs(capacity[endNode][i].first);

    return Flow;

}


int main(){
    //citire date
    cin>>n>>m;
    containerInit(n+1);
    for(int i=1;i<=n;++i){
        int grad,j,maxFlow;

        cin>>grad;

        while(grad--){
            cin>>j>>maxFlow;


            adq[i].push_back(j);
            adq[j].push_back(i);

            //cat flux se transmite
            capacity[i][j].first = 0;
            // cat flux se mai poate transmite
            capacity[i][j].second = maxFlow;
            // cand fluxul se redirectioneaza
            capacity[j][i].second = 0;
            capacity[j][i].first = 0;
        }


    }
    cin>>source>>sink;
    int maxF = maxFlow();


    int k = findSmallestPrime(maxF);
    cout<<k<<endl;
    if(k==maxF)
        cout<<"Da";
    else cout<<"Nu";

    return 0;
}