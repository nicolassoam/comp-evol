#include <boost/graph/adjacency_matrix.hpp>
#include <fstream>
#include <iostream>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;

typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef adjacency_matrix<undirectedS,no_property,EdgeWeightProperty> Graph;
typedef Graph::edge_descriptor Edge;
typedef Graph::vertex_descriptor Vertex;

void readGraphATSP(string file_location){
    ifstream infile;
    infile.open(file_location,ios::in);
    int i =4;

    string line;
      
    while(i>0){
        
        getline(infile, line,'\n');
        i--;
        
    }

    stringstream ss(line);  
    string aux;
    getline(ss,aux,' ');
    getline(ss,aux,' ');
 
    int n;
    n = stoi(aux);
    i = 3;

    while(i > 0){
        getline(infile, line,'\n');
        i--;
    }

    i = 0;
    int j = 0;

    Graph g(n);

    while(!infile.eof()){
        while(infile >> line){
             stringstream ss(line);
             string aux;
             while(getline(ss,aux,' ')){
                if(aux == "100000000" || aux == "EOF" || aux == "\n")
                    continue;
                else
                    add_edge(i, j,stoi(aux),g);

                j++;
             };
          
            // dynamic_properties dp;
            // dp.property("node_id", get(vertex_index, g));
            // dp.property("weight", get(edge_weight, g));
            // write_graphviz_dp(std::cout, g, dp);
            cout << i << endl;
            i++;
        };
       
    }
    

    // cout << n << endl;

    

    // while (getline(infile, line)){
    //     int a, b;
    //     istringstream iss(line);
    //     if (!(iss >> a >> b)) { break; } // error
    //     add_edge(a, b, 3,g);
    // }
    // return g;
}
