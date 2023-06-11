#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <vector>

void readInstance(std::fstream &file){
    int num_items, capacity;
    std::vector<int> weights(num_items);
    file >> num_items >> capacity;
    
    while(!file.eof()){
        for(int i = 0; i < num_items; i++){
            file >> weights[i];
        }
    }
    return;
}

#endif