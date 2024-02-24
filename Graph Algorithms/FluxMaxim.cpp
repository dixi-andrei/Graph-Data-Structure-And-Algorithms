#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
#include<climits>
#include<set>
using namespace std;
ifstream fin("text.in");

// pentru a stoca in lista de adiacenta
struct flow{
    int node;
    int currentFlow;
    int maxCapacity;

    flow(int node,int currentFlow,int maxCapacity):node(node),currentFlow(currentFlow),maxCapacity(maxCapacity){}
};

int n,m,source,sink;

// adq.first sunt arcele externe
// adq.second sunt arcele interne
vector<pair<vector<flow>,vector<flow>>> adq;
// folosit si ca vector de vizite
vector<int> parent;

void containerInit(const int& nodes){
    adq.resize(nodes+1);
    parent.resize(nodes+1);
}

int findPathBFS(int startNode=source,int endNode=sink){

    fill(parent.begin(), parent.end(),0);
    // q.first = nodul curent
    // q. second = fluxul minim pana in acel nod ce mai poate fi transmis
    queue<pair<int,int>> q;

    q.emplace(startNode,INT_MAX);
    parent[startNode] = startNode;

    while(!q.empty()){

        int currentNode = q.front().first;
        int currentFlow = q.front().second;

        q.pop();

        // verificam a arcele externe

        for(const auto& flowData: adq[currentNode].first){
            int nextNode=flowData.node;
            int minFlow = min(currentFlow,flowData.maxCapacity-flowData.currentFlow);
            //cout<<minFlow<<" ";

            // daca nodul e nevizitat si mai poate transporta flux
            if(!parent[nextNode]&& (flowData.maxCapacity-flowData.currentFlow) > 0){

                //cout<<minFlow;
                // se modifica parintele si se da push la nod si flow ul minim modificat
                parent[nextNode] = currentNode;

                // se testeaza daca e sinkul

                if(nextNode == endNode){
                    //cout<<nextNode<<" ";
                    return minFlow;
                }

                q.emplace(nextNode,minFlow);

            }
        }

        //verificam arcele interne

        for(const auto& flowData : adq[currentNode].second){
            int nextNode=flowData.node;
            // se ia doar capacitatea
            int minFlow = min(currentFlow,flowData.currentFlow);

            // daca nodul e nevizitat si mai poate transporta flux folosind doar capacitatea ca e arc intern
            if(!parent[nextNode]&& flowData.currentFlow){

                // se modifica parintele si se da push la nod si flow ul minim modificat

                // parintele o sa fie luat cu - pentru a putea face diferenta dintre ar ce directe si indirecte
                parent[nextNode] = -currentNode;

                q.emplace(nextNode,minFlow);

            }

        }

    }

    return 0;

}

void updatePath(const int& flow,int startNode=source,int endNode=sink){

    int currentNode = endNode;

    while(currentNode != startNode){

        int parentNode= parent[currentNode];

        // arc direct
        if(parentNode > 0){

            // creste valoarea pe arc direct parinte -> copil
            for(auto& flowData : adq[parentNode].first){
                if(flowData.node==currentNode){
                    flowData.currentFlow += flow;
                    break;
                }

            }

            // creste valoarea ce se poate intoarce pe arc invers copil -> parinte
            for(auto& flowData: adq[currentNode].second){
                if(flowData.node == parentNode){
                    flowData.currentFlow += flow;
                    break;
                }
            }

        }
        //arc invers
        else{
            parentNode *=(-1);

            // scade valoarea pe arcul copil -> parinte

            for(auto& flowData: adq[currentNode].first){
                if(flowData.node == parentNode){
                    flowData.currentFlow -= flow;
                    break;
                }
            }

            // scade valoarea ce se poate intoarce pe arc invers parinte -> copil
            for(auto& flowData: adq[parentNode].second){
                if(flowData.node == currentNode){
                    flowData.currentFlow -= flow;
                    break;
                }
            }
        }

        currentNode = parentNode;

    }

}

int calculateMaxFlow(int startNode=source,int endNode=sink){

    int flow = 0;

    while((flow = findPathBFS())){
        updatePath(flow);
    }

    // cautam in arcele ce intra in sink
    for(const auto& flowData: adq[endNode].second){
        flow+= flowData.currentFlow;
    }
    return flow;
}

bool hasValueCut(int value,int startNode=source,int endNode=sink){

    // folosim panrent ca vector de vizite
    fill(parent.begin(), parent.end(),0);
    queue<int> q;


    q.push(startNode);
    parent[startNode] = 1;

    while(!q.empty()){
        // se calculeaza posibilitatile de a avea taietura
        int currentFlow = 0;
        for(int node=1;node<=endNode;++node){
            if(parent[node]){
                for(const auto& flowData : adq[node].first){
                    currentFlow+=flowData.maxCapacity;
                }
            }
        }

        if(currentFlow == value)
            return true;

        int currentNode = q.front();
        q.pop();

    }
    return false;
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

int main(){
    //citire date
    cin>>n>>m;

    containerInit(n);

    for(int node=1;node<=n;++node)
    {
        int gradI;
        cin>>gradI;

        while(gradI--){
           int nextNode;
           int maxCapacity;

           cin>>nextNode>>maxCapacity;

           adq[node].first.emplace_back(nextNode,0,maxCapacity);
           adq[nextNode].second.emplace_back(node,0,maxCapacity);
        }
    }

    cin>>source>>sink;

    int maxFlow = calculateMaxFlow();
    int prime = findSmallestPrime(maxFlow);


    cout<< prime<<endl;

    if(prime == maxFlow)
        cout<<"Da";
    else cout<<"Nu";


    return 0;
}