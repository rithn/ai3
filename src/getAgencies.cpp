#include <iostream>
#include <map>
#include <vector>
#include<string>

#include <fstream>

using namespace std;

//  Command: ./main $1.meta $1.satoutput > $1.subgraphs  

int main(int argc, char** argv){
    ios_base::sync_with_stdio(0);
    ifstream metafile,sat;
 
    metafile.open(argv[1]); //metadata on graph
    int numVertices,numAgencies,x;
    metafile>>numVertices>>numAgencies;
    x=max(numVertices,numAgencies);
    metafile.close();

    sat.open(argv[2]);
    int v,agency,node;
    string s;
    vector< vector<int> > agencies;
    agencies.resize(numAgencies+1);
 
    sat>>s;
    if(s=="UNSAT"){
        cout<<0<<'\n';
        return 0;
    }
 
    for(int i=0;i<x*x + x + 1;i++){
        sat>>v;
        if(v>0 && abs(v)%x<=numAgencies){
            // cout<<v<<endl;
            agency=v%x;
            node=(v-agency)/x;
            agencies[agency].push_back(node);
        }
    }
 
    sat.close();

    for(int a=1;a<=numAgencies;a++){
        cout<<"#"<<a<<" "<<agencies[a].size()<<'\n';
        for(auto n: agencies[a]){
            cout<<n<<" ";

        }
        cout<<'\n';
    }


    
}