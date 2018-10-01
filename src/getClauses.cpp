#include <iostream>
#include <map>
#include <vector>
#include<string>
#include<set>

#include<ctime>
#include <fstream>

//Command: ./main $1.satoutput $1.meta < $1.graph

using namespace std;

int numVertices, numEdges, numAgencies;
vector< set<int> > graph;

vector<vector<int> > clauses;

inline int mapping(int n,int a){
    return (n-1)*numAgencies +a;
}


int main(int argc, char** argv){
    ios_base::sync_with_stdio(0);
    clock_t begin = clock(),end;
    double elapsed_secs;


    cin>>numVertices>>numEdges>>numAgencies;
    int x= max(numVertices,numAgencies);
    graph.resize(numVertices+1);
    int a,b;
    for(int i=0;i<numEdges;i++){
        cin>>a>>b;
        graph[a].insert(b);
        graph[b].insert(a);
    }



    //Clauses for checking if each node has at least one agency (extra)
    for(int vertex=1;vertex<=numVertices;vertex++){
        vector<int> clause;
        for(int agency=1;agency<=numAgencies;agency++){
            clause.push_back(mapping(vertex,agency));
        }
        clauses.push_back(clause);
    }


    //Clauses for checking if each agency has at least one member
    for(int agency=1;agency<=numAgencies;agency++){
        vector<int> clause;
        for(int vertex=1;vertex<=numVertices;vertex++){
            clause.push_back(mapping(vertex,agency));
        }
        clauses.push_back(clause);
    }

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time elapsed- "<<elapsed_secs<<endl;
 
    // int indexCounter=x*x + x + 1;
    int indexCounter=numVertices*numAgencies+1;

    //Clauses for checking if edge between n1 & n2 implies at least one common agency
    for(int n1=1;n1<=numVertices;n1++){
        for(auto n2: graph[n1]){
            if(n1<n2) break;
            // vector<Variable> c0;            
            vector<int> c0;
            for(int agency=1;agency<=numAgencies;agency++){
                vector<int> c1;
                c1.push_back(mapping(n1,agency));
                c1.push_back(-indexCounter);
            
                vector<int> c2;
                c2.push_back(-mapping(n1,agency) );
                c2.push_back(-indexCounter);
                c2.push_back(mapping(n2,agency));

                vector<int> c3;
                c3.push_back(-mapping(n1,agency) );
                c3.push_back(indexCounter);
                c3.push_back(-mapping(n2,agency));

                clauses.push_back(c1);
                clauses.push_back(c2);
                clauses.push_back(c3);

                c0.push_back(indexCounter);
                indexCounter++;
            }
            clauses.push_back(c0);
        }
    }


    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time elapsed- "<<elapsed_secs<<endl;


    //Clauses for checking if 'no edge' implies 'no common agency'
    for(int n2=1;n2<=numVertices;n2++){
        for(int n1=n2+1;n1<=numVertices;n1++){
            if(graph[n1].find(n2)!=graph[n1].end()) continue;

            for(int agency=1;agency<=numAgencies;agency++){
                vector<int> c0;

                c0.push_back(-mapping(n1,agency) );
                c0.push_back(-mapping(n2,agency));

                clauses.push_back(c0);


            }

        }
    }

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time elapsed- "<<elapsed_secs<<endl;


    //Clauses for ensuring no agency is a subset of another
    for(int a1=1;a1<=numAgencies;a1++){
        for(int a2=1;a2<=numAgencies;a2++){
            if(a1==a2) continue;
            // vector<Variable> c0;
            vector<int> c0;
            for(int node=1;node<=numVertices;node++){
                vector<int> c1;
                c1.push_back(mapping(node,a1));
                c1.push_back(-indexCounter);
            
                vector<int> c2;
                c2.push_back(-mapping(node,a1) );
                c2.push_back(-indexCounter);
                c2.push_back(-mapping(node,a2) );

                vector<int> c3;
                c3.push_back(-mapping(node,a1) );
                c3.push_back(indexCounter);
                c3.push_back(mapping(node,a2));

                clauses.push_back(c1);
                clauses.push_back(c2);
                clauses.push_back(c3);

                c0.push_back(indexCounter);
                indexCounter++;



            }
            clauses.push_back(c0);
            
        }
    }

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time elapsed- "<<elapsed_secs<<endl;


    /*Print clauses */

    ofstream f;
    f.open (argv[1]);
    f<<"p cnf "<<indexCounter<<" "<<clauses.size()<<endl;
    for(auto c:clauses){
        for(auto v: c){
            // if(v.isTrue) f<<v.id<<" ";
            // else f<<-(v.id)<<" ";
            f<<v<<" ";
        }
        f<<0<<'\n';
    }

    f.close();

    ofstream myfile;
    myfile.open (argv[2]);
    myfile<<numVertices<<" "<<numAgencies<<endl;
    myfile.close();

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Time elapsed- "<<elapsed_secs<<endl;
    
    


    return 0;
}