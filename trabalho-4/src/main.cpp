#include <iostream>
#include "../include/de.h"
#include "../include/utils.h"
#include "../include/config.h"
#include <fstream>
#include <random>

int main(int argc, char** argv){
    unsigned int seed = argv[1] ? atoi(argv[1]) : 122;
    
    srand(seed);

    std::ifstream file;
    std::string instance = "Falkenauer_t60_00";
    std::string instance_file = FALKENAUER_T "/" + instance + ".txt";

    std::vector<int> weights;
    
    file.open(instance_file, std::ios::in);

    if(!file.is_open()){
        std::cout << "Error opening file" << std::endl;
        return 1;
    }
    //intellisense pode acusar erro mas esse código funciona!
    auto [num_itens, capacity] = readInstance(file,weights); 
    // int num_itens = readAugmented(file,weights);
    // int capacity = 40000;
    int problem_dimension = num_itens;
    int population_size = 600;
    int epochs = 6000;
    double wf = 0.8;
    double cr = 0.9;
    double_vec lb(problem_dimension, 0);
    double_vec ub(problem_dimension, num_itens-1);

    DiffEvol de(population_size, problem_dimension, epochs, lb, ub, wf, cr, weights, capacity, num_itens);

    
    de.evaluate(seed,instance);

    std::cout << num_itens << " " << capacity << std::endl;
    std::cout << "seed: " << seed << std::endl; 

    return 0;
}