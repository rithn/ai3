#include "Variable.h"
#include <iostream>
#include <map>
#include <vector>
#include<string>
#include<set>

using namespace std;

int numVertices, numEdges, numAgencies;
vector< set<int> > graph;
vector< vector<Variable> > clauses;

map<int,string> Variable::idToVariable;
map<string,int> Variable::variableToId;
int Variable::counter=0;


int main(){
   
    cin>>numVertices>>numEdges>>numAgencies;
    graph.resize(numVertices+1);
    int a,b;
    for(int i=0;i<numEdges;i++){
        cin>>a>>b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    //Clauses for checking if each agency has at least one member
    for(int agency=1;agency<=numAgencies;agency++){
        vector<Variable> clause;
        for(int vertex=1;vertex<=numVertices;vertex++){
            clause.push_back(NodeAgency(vertex,agency,true));
        }
        clauses.push_back(clause);
    }

    //Clauses for checking if edge between n1 & n2 implies at least one common agency
    for(int n1=1;n1<=numVertices;n1++){
        for(auto n2: graph[n1]){
            if(n1<n2) break;
            vector<Variable> c0;
            for(int agency=1;agency<=numAgencies;agency++){
                vector<Variable> c1;
                c1.push_back(NodeAgency(n1,agency,true));
                c1.push_back(NodePairAgency(n1,n2,agency,false));
            
                vector<Variable> c2;
                c2.push_back(NodeAgency(n1,agency,false));
                c2.push_back(NodePairAgency(n1,n2,agency,false));
                c2.push_back(NodeAgency(n2,agency,true));

                vector<Variable> c3;
                c3.push_back(NodeAgency(n1,agency,false));
                c3.push_back(NodePairAgency(n1,n2,agency,true));
                c3.push_back(NodeAgency(n2,agency,false));

                clauses.push_back(c1);
                clauses.push_back(c2);
                clauses.push_back(c3);

                c0.push_back(NodePairAgency(n1,n2,agency,true));
            }
            clauses.push_back(c0);
        }
    }

    //Clauses for checking if 'no edge' implies 'no common agency'
    for(int n2=1;n2<=numVertices;n2++){
        for(int n1=n2+1;n1<=numVertices;n1++){
            if(graph[n1].find(n2)!=graph[n1].end()) continue;

            for(int agency=1;agency<=numAgencies;agency++){
                vector<Variable> c0;
                c0.push_back(NodePairAgency(n1,n2,agency,false));
                clauses.push_back(c0);
            }

        }
    }

    //Clauses for ensuring no agency is a subset of another
    for(int a1=1;a1<=numAgencies;a1++){
        for(int a2=1;a2<=numAgencies;a2++){
            if(a1==a2) continue;
            vector<Variable> c0;
            for(int node=1;node<=numVertices;node++){
                vector<Variable> c1;
                c1.push_back(NodeAgency(node,a1,true));
                c1.push_back(AgencyPairNode(a1,a2,node,false));
            
                vector<Variable> c2;
                c2.push_back(NodeAgency(node,a1,false));
                c2.push_back(AgencyPairNode(a1,a2,node,false));
                c2.push_back(NodeAgency(node,a1,false));
                

                vector<Variable> c3;
                c3.push_back(NodeAgency(node,a1,false));
                c3.push_back(AgencyPairNode(a1,a2,node,true));
                c3.push_back(NodeAgency(node,a1,true));

                clauses.push_back(c1);
                clauses.push_back(c2);
                clauses.push_back(c3);

                c0.push_back(AgencyPairNode(a1,a2,node,true));

            }
            clauses.push_back(c0);
            
        }
    }

    /*Print clauses to file*/

    /*Print id to variable mapping in a separate file (which will be used 
    * later to construct subgraphs) */


    


    return 0;
}