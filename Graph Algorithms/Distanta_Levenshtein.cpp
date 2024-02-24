#include<iostream>
#include<set>
#include<vector>
#include<queue>
#include<fstream>
#include<cstring>
#include<utility>
#include<string>
using namespace std;
ifstream fin("text.in");
ofstream fout("text.out");


int LevenshteinDistance(const string& str1,const string&str2,vector<vector<int>>& distanceMat){
    int cols,rows;
    //linii cat lungimea primului string
    distanceMat.resize(str1.size()+1);
    rows=str1.size()+1;
    cols=str2.size()+1;
    // coloane cat lungimea celui de-al doilea string
    for(auto& row:distanceMat){
        row.resize(str2.size()+1);
    }
    for(int i=0;i<cols;++i){
        distanceMat[0][i]=i;
    }
    for(int i=0;i<rows;++i){
        distanceMat[i][0]=i;
    }

    //se porneste de la 1
    for(int i=1;i<rows;++i){
        for(int j=1;j<cols;++j){

            // daca  sunt egale distanta nu se modifica
            if(str1[i-1]==str2[j-1])
                distanceMat[i][j]=distanceMat[i-1][j-1];
            else{
                distanceMat[i][j]=1;
                //delete
                int del=distanceMat[i-1][j];
                //swap
                int swp=distanceMat[i-1][j-1];
                //insert
                int ins=distanceMat[i][j-1];

                distanceMat[i][j]+=min(del,min(swp,ins));
            }
        }
    }

    for(int i=0;i<rows;++i){
        for(int j=0;j<cols;++j){

            cout<<distanceMat[i][j]<<" ";
            }
        cout<<endl;
        }



    return distanceMat[rows-1][cols-1];
}
string str1,str2;
vector<vector<int>> distanceMat;



int main(){

    cout<<LevenshteinDistance("manele","marire",distanceMat)<<endl;




    return 0;
}
