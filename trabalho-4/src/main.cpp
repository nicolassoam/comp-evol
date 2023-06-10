#include <iostream>
#include "../include/de.h"
#include <random>

int main(){
    srand(SEED);
    double_vec lb(10, 0);
    double_vec ub(10, 100);
    DiffEvol de(2000, 10, 2000, lb, ub, 0.8, 0.9);
    de.evaluate();
    return 0;
}