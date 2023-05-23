#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>
#include <map>
#include <initializer_list>

#include <utility>

#include <pagmo/problem.hpp>

#include <pagmo/types.hpp>

using namespace pagmo;
using namespace std;


/*
* Define o problema
* \param n número de cidades
* \param dist matriz de distâncias
* \param fitness função objetiva
* @param get_bounds retorna espaço de busca
*/
struct TSPProblem {
    int n;
    vector<vector<int>> dist;
    
    vector_double fitness(const vector_double &dv) const{
       double total_distance = 0.0;
        // for (auto i = 0; i < n; ++i)
        // {
        //     for (auto j = 0; j < n-1; ++j)
        //     {
        //         total_distance += dist[static_cast<size_t>(dv[i])][static_cast<size_t>(dv[j])];

        //     }
            
        // }
        for(auto i = 0; i < n-1; i++){
            total_distance += dist[static_cast<size_t>(dv[i])][static_cast<size_t>(dv[i+1])];
            // cout << dv[i] << " " << dv[i+1] << endl;
        }
        total_distance += dist[static_cast<size_t>(dv[n-1])][static_cast<size_t>(dv[0])];

        // total_distance += dist[static_cast<size_t>(dv.back())][static_cast<size_t>(dv.front())];
        return {total_distance};
    };
    pair<vector_double,vector_double> get_bounds() const{
        // vector<double> lower;
        // vector<double> upper;
        // for(auto i = 0; i < n/2; i++){
        //     lower.push_back(0);
        //     upper.push_back(n);
        // }
        vector_double lower(n,0.0);
        vector_double upper(n,static_cast<double>(n-1));
        
        return {lower, upper};
    };

};

ifstream read_partial(string file_location, int &number){
    ifstream infile;
    try{
        infile.open(file_location,ios::in);
        cout << "Arquivo aberto" << endl;
    } catch(string e) {
        cout << "Erro ao abrir o arquivo" << endl;
    };

    string str;
    char* line;
    char* p;
    int n = 0;

    // le até a dimensão
    while(!infile.eof()){
        getline(infile,str);
        line = strdup(str.c_str());
        p = strtok(line, " :");
        if(strcmp(p,"DIMENSION") == 0){
            getline(infile, str);
            line = strdup(str.c_str());
            p = strtok(NULL, " :");
            n = atoi(p);
        } else if(strcmp(p,"EDGE_WEIGHT_SECTION") == 0 || strcmp(p, "NODE_COORD_SECTION") == 0){
            break;
        }
    }

    (number) = n;

    return infile;
}


/*
* Lê o arquivo de entrada do problema ATSP
* \param file_location localização do arquivo
*/
TSPProblem readGraphATSP(string file_location){
    int n;
    ifstream file = read_partial(file_location,n);

    TSPProblem tsp;
    tsp.dist = vector<vector<int>>(n,vector<int>(n));
    tsp.n = n;
    for(auto i = 0; i < n; ++i){
        for(auto j = 0; j < n; ++j){
            file >> tsp.dist[i][j];
        }
    }
    return tsp;
}
int nint(double x){
    return (int)(x + 0.5);
}

double calc_euc_dist(double xi, double xj, double yi, double yj){
    double xd,yd,dij;
    xd = xi - xj;
    yd = yi - yj;
    dij = nint( sqrt( xd*xd + yd*yd) );
    return dij;
}

TSPProblem readGraphTSP(string file_location){
    int n;
    ifstream file = read_partial(file_location,n);

    TSPProblem tsp;
    tsp.dist = vector<vector<int>>(n,vector<int>(n));
    tsp.n = n;

    map<int,pair<double,double>> node;
    int nodeN;
    double x,y;
    for(auto i = 0; i < n; ++i){
        for(auto j = 0; j < n; ++j){
            file >> nodeN >> x >>y;
            node[nodeN] = {x,y};
        }
    }

    for(auto i = 0; i < n; ++i){
        for(auto j = 0; j < n; ++j){
            tsp.dist[i][j] = calc_euc_dist(node[i].first,node[i].second,node[j].first,node[j].second);
            // cout << tsp.dist[i][j] << " ";	
        }
        // cout <<endl;
    }

    return tsp;
}
