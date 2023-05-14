#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

struct TSP {
    int n;
    vector<vector<int>> dist;
};

void readGraphATSP(string file_location){
    ifstream infile;
    try{
        infile.open(file_location,ios::in);
        cout << "Arquivo aberto" << endl;
    } catch(string e) {
        cout << "Erro ao abrir o arquivo" << endl;
    };
        
    int i =4;

    string line;
      
    while(i>0){
        
        getline(infile, line,'\n');
        i--;
        
    }

    stringstream ss(line);  
    string aux;
    getline(ss,aux,' ');
   
    getline(ss,aux);
   

    int n;
    n = stoi(aux);
    i = 3;
    

    while(i > 0){
        getline(infile, line,'\n');
        i--;
        
    }

    i = 0;
    int j = 0;
    TSP tsp;
    tsp.n = n;
    vector<vector<int>> dist(n,vector<int>(n));
    tsp.dist = dist;

    while(!infile.eof()){
        while(infile >> line){
             stringstream cc(line);
             string aux;
             while(getline(cc,aux,' ')){
                if(aux == "100000000" || aux == "9999" || aux == "EOF" || aux == "\n")
                    continue;
                else
                    tsp.dist[i][j] = stoi(aux);

                j++;
                
             };
          
            // cout << i << endl;
            
            j = 0;
        };
       i++;
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
