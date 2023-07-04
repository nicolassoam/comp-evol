#ifndef UTILS_H
#define UTILS_H

#include <random>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "config.h"
#include <chrono>
#include <vector>

std::pair<int,int> readInstance(std::ifstream &file, std::vector<int> &weights){
    int num_items, capacity;
    int weight;
    file.seekg(0, std::ios::beg);

    file >> num_items;
    file >> capacity;

    while(!file.eof()){
        file >> weight;
        weights.push_back(weight);
        
    }


    file.close();


    return {num_items, capacity};
}

int readAugmented(std::ifstream &file, std::vector<int> &weights){
    int num_items;
    int weight;
    file.seekg(0, std::ios::beg);

    file >> num_items;

    while(!file.eof()){
        file >> weight;
        weights.push_back(weight);
        
    }


    file.close();


    return num_items;
}

typedef std::chrono::high_resolution_clock Clock;

#endif