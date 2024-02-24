#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<algorithm>
#include<climits>
#include<set>
using namespace std;

struct FlowData{
    int node;
    int flow;
    int maxCapacity;

    FlowData(const int& node, const int& flow, const int& maxCapacity):node(node), flow(flow) , maxCapacity(maxCapacity) {}
};

ifstream fin("text.in");
int n,m,source,sink;

vector<vector<int>> adq;
vector<vector<pair<int,int>>> capacity;
// used to easily find the nodes that enter a specific node
vector<int> parent;
set<int> nodeSet;
set<int> sinkSet;
set<int> sourceSet;

// using bfs we will find a valid path, returns the maximum flow that can be added through the found path
int findPathBFS(int startNode = source,int endNode = sink){

    //reset the containers
    // an unvisited node will have the parent -1
    fill(parent.begin(), parent.end(),-1);

    queue<pair<int,int>> q;
    // we mark it visited, but without parent
    parent[startNode]=-2;

    // the flow that can be transported will be calculated dinamically
    q.emplace(startNode,INT_MAX);

    while(!q.empty()){

        int currentNode=q.front().first;
        int currentFlow=q.front().second;
        q.pop();

        for(const auto& nextNode: adq[currentNode]){
            // test if the next node is unvisited and if more flow can be added
            if(parent[nextNode]==-1 && capacity[currentNode][nextNode].second){

                parent[nextNode]=currentNode;

                // calculate the minflow that can go into the currentNode
                int minFlow=min(currentFlow,capacity[currentNode][nextNode].second);

                if(nextNode==endNode)
                    return minFlow;
                // push the current node with the minFlow
                q.emplace(nextNode,minFlow);
            }
        }

    }

    return 0;
}

void updatePath(const int& newFlow,int startNode=source,int endNode=sink){
    int currentNode= endNode;

    while(currentNode!=source){
        // the maximum flow that can be transported shrinks
        capacity[parent[currentNode]][currentNode].second -=newFlow;
        // the transported flow grows
        capacity[parent[currentNode]][currentNode].first +=newFlow;
        // the flow that can go back updates
        capacity[currentNode][parent[currentNode]].first -= newFlow;
        // the flow that can be transported backwords grows
        capacity[currentNode][parent[currentNode]].second += newFlow;

        currentNode=parent[currentNode];
    }
}

int maxFlow(int startNode=source,int endNode=sink){
    int maxFlow=0;
    int newFlow=0;

    // calculate a newflow till the flow drains
    while((newFlow = findPathBFS())){
        // updateMaxflow
        maxFlow += newFlow;

        //update the capacity matrix by walking on the found path
        updatePath(newFlow,startNode,endNode);

    }
    return maxFlow;
}



void findCut(int startNode = source, int endNode= sink){
    // just go with the bfs again on the nodes that still can transport flow and add them to the source set
    fill(parent.begin(), parent.end(),-1);
    queue<int> q;

    q.push(startNode);
    parent[startNode] = -2;
    sourceSet.insert(startNode);

    while(!q.empty()){
        int currentNode=q.front();
        q.pop();

        for(const auto& nextNode:adq[currentNode]){
            if(parent[nextNode]==-1 && capacity[currentNode][nextNode].second){

                parent[nextNode]=currentNode;
                sourceSet.insert(nextNode);
                q.push(nextNode);
            }
        }
    }


}

void containerInit(const int&n){
    adq.resize(n);
    parent.resize(n);

    capacity.resize(n);

    for(auto& row: capacity)
        row.resize(n);

}

int main(){
    //read data
    fin>>n>>m;
    source=0;
    sink=n+1;

    for(int i=0;i<=n+1;++i)
        nodeSet.insert(i);

    containerInit(n+2);
    // adq construction
    while(m--){
        int x,y,maxCapacity;
        fin>>x>>y>>maxCapacity;

        capacity[x][y].second=maxCapacity;
        adq[x].push_back(y);
        adq[y].push_back(x);
    }


    cout<<maxFlow()<<endl;

    for(int i=0;i<=n+1;++i){
        for(int j=0;j<=n+1;++j){
            cout<<capacity[i][j].first<<"/"<<capacity[i][j].second<<" ";
        }
        cout<<endl;
    }

    findCut();
    set_difference(nodeSet.begin(),nodeSet.end(),sourceSet.begin(),sourceSet.end(), inserter(sinkSet,sinkSet.begin()));

    for(const auto& node: sourceSet)
        cout<<node<<" ";
    cout<<endl;
    for(const auto& node:sinkSet)
        cout<<node<<" ";


    return 0;
}

//6 10
//0 1 10
//0 4 3
//1 2 3
//4 6 7
//6 1 9
//2 5 2
//6 3 5
//2 3 5
//5 7 8
//3 7 4