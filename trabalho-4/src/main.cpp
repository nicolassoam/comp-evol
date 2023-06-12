#include <iostream>
#include "../include/de.h"
#include "../include/utils.h"
#include "../include/config.h"
#include <fstream>
#include <random>

int main(){
    srand(SEED);

    std::ifstream file;
    std::string instance = FALKENAUER_U;

    std::vector<int> weights;

    file.open(instance+"/Falkenauer_u120_00.txt", std::ios::in);
    
    auto [num_itens, capacity] = readInstance(file,weights); // C++17

    int problem_dimension = 10;
    int population_size = 1000 * problem_dimension;
    int epochs = 12000;
    double wf = 0.8;
    double cr = 0.9;
    double_vec lb(problem_dimension, 1);
    double_vec ub(problem_dimension, num_itens);

   

    DiffEvol de(population_size, problem_dimension, epochs, lb, ub, wf, cr, weights, capacity, num_itens);


    de.evaluate();

    std::cout << num_itens << " " << capacity << std::endl;

    // for(int i : weights)
    //     std::cout << i << " ";

    return 0;
}