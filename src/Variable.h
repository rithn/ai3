#ifndef MOVE_H
#define MOVE_H

#include<string>
#include<map> 

using namespace std;

struct Variable{
    public:
    int id;
    static int counter;
    static map<string,int> variableToId;
    static map<int,string> idToVariable;
    // Variable(){}   
    Variable(string s){
        if(variableToId.find(s)==variableToId.end()){
            counter++;
            variableToId[s]=counter;
            idToVariable[counter]=s;
        }
        id=counter;
    }
    virtual string repr(){}

};


/*Variable denoting truth value of node being 
* present in  particular agency: 
* A(node,agency)  */
struct NodeAgency: Variable{    
    int node,agency;
    bool isTrue;
    NodeAgency(int n, int a, bool t): node(n), agency(a), isTrue(t), Variable(repr(n,a)){}
    string repr(int n, int a){
        return "-"+to_string(n)+","+to_string(a);
    }
};

/* A(node1,agency)^ A(node2,agency)
*  assume node1>node2 */
struct NodePairAgency: Variable{    
    int node1,node2,agency;
    bool isTrue;
    NodePairAgency(int n1, int n2, int a, bool t): node1(n1), node2(n2), agency(a), isTrue(t), Variable(repr(n1,n2,a)){}
    string repr(int n1, int n2, int a){
        return "#"+to_string(n1)+","+to_string(n2)+","+ to_string(a);
    }

};

/* A(node,agency1)^ !A(node,agency2) */
struct AgencyPairNode: Variable{    
    int agency1,agency2,node;
    bool isTrue;
    AgencyPairNode(int a1, int a2, int n, bool t): agency1(a1), agency2(a2), node(n), isTrue(t), Variable(repr(a1,a2,n)){}
    string repr(int a1,int a2, int n){
        return "$"+to_string(a1)+","+to_string(a2)+","+ to_string(n);
    }

};



#endif