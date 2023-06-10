#include <iostream>
#include "../include/de.h"
#include <random>

int main(){
    srand(SEED);
    int problem_dimension = 30;
    int population_size = 100 * problem_dimension;
    int epochs = 3000;
    double wf = 0.8;
    double cr = 0.9;
    double_vec lb(problem_dimension, 0);
    double_vec ub(problem_dimension, 100);
    DiffEvol de(population_size, problem_dimension, epochs, lb, ub, wf, cr);
    de.evaluate();
    return 0;
}