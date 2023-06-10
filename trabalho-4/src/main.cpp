#include <iostream>
#include "../include/de.h"
#include <random>

int main(){
    srand(SEED);
    double_vec lb = {-5.12, -5.12};
    double_vec ub = {5.12, 5.12};
    DiffEvol de(100, 2, 1000, lb, ub, 0.8, 0.9);
    de.evaluate();
    return 0;
}