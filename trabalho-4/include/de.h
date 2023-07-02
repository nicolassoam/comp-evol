#ifndef DE_H
#define DE_H

#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <queue>
#include "config.h"
#include "utils.h"
#include <fstream>
#include <unordered_set>
#include <list>
#include <iostream>
#include <cmath>
#include <omp.h>
#include <utility>
#include <limits>

// #define SEED 122

// inline std::mt19937 gen;

// typedef struct bin{
//     int capacity;
// }bin;

typedef std::vector<double> double_vec;
typedef struct individual{
    double_vec cromo;
    double fitness;
    individual(): fitness(0.0) {};
} individual;

typedef std::vector<int> weights;

typedef std::vector<individual> pop_mat;


/*
    Class for Differential Evolution
*/
class DiffEvol {
    private:
        std::mt19937 gen;
        long pop_size;
        long problem_dim;
        int max_iter;
        pop_mat population; 
        double_vec fitness;
        double_vec lb;
        double_vec ub;
        weights w;
        int capacity;
        int n_itens;
        double wf;
        double cr;
        void init_population();
        void select_parents(int current, int&p1, int&p2, int&p3);
        pop_mat create_children(pop_mat &pop, int wf, int cr);
        pop_mat select_population(pop_mat parents, pop_mat children);
        double_vec de_rand_1_bin(double_vec pop, double_vec parent1, double_vec parent2, double_vec parent3, int wf, int cr);
        individual search();
        double objective_function(double_vec &cromo);
    public:
        DiffEvol(long pop_size, long problem_dim, int max_iter, double_vec lb, double_vec ub, double wf, double cr, weights w, int capacity, int n_itens);
        void evaluate(unsigned int seed, std::string file_name = " ");
        double_vec get_best();
        double_vec get_best_fitness();
        pop_mat get_population();
        double_vec get_fitness();
};

/*
    \param long pop_size: population size
    \param long problem_dim: problem dimension
    \param int max_iter: maximum number of iterations
    \param double_vec lb: lower bound
    \param double_vec ub: upper bound
    \param double wf: weight factor
    \param double cr: crossover rate
*/
DiffEvol::DiffEvol(long pop_size, long problem_dim, int max_iter, double_vec lb, double_vec ub, double wf, double cr, weights w, int capacity, int n_itens){
    this->pop_size = pop_size;
    this->problem_dim = problem_dim;
    this->lb = lb;
    this->ub = ub;
    this->wf = wf;
    this->cr = cr;
    this->max_iter = max_iter;
    this->w = w;
    this->capacity = capacity;
    this->n_itens = n_itens;
}

void DiffEvol::init_population(){
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    
    for (int i = 0; i < pop_size; i++){
        individual temp;
        
        // for (int j = 0; j < problem_dim; j++){
        //     temp.cromo.push_back(lb[j] + (ub[j] - lb[j]) * dis(gen));
        // }

        std::vector <int> itens(this->n_itens);
        std::iota(itens.begin(), itens.end(), 0);
        std::shuffle(itens.begin(), itens.end(),gen);

        for(int item : itens)
            temp.cromo.push_back(item);

        temp.fitness = this->n_itens-1;
        
        population.push_back(temp);
    }
}

void DiffEvol::select_parents(int current, int&p1, int&p2, int&p3){
    std::uniform_int_distribution<int> dis(0, pop_size - 1);

    int r1 = dis(gen);
    int r2 = dis(gen);
    int r3 = dis(gen);
    
    while (r1 == current || r2 == current || r3 == current || r1 == r2 || r1 == r3 || r2 == r3){
        r1 = dis(gen);
        r2 = dis(gen);
        r3 = dis(gen);
    }    
    p1 = r1;
    p2 = r2;
    p3 = r3;

}


pop_mat DiffEvol::create_children(pop_mat &pop, int wf, int cr){
    
    pop_mat children;
  
    for(int i = 0;i < pop.size(); i++){
        int p1, p2, p3;
        select_parents(i, p1, p2, p3);
        individual child;
        child.cromo = de_rand_1_bin(pop[i].cromo, pop[p1].cromo, pop[p2].cromo, pop[p3].cromo, wf, cr);
        children.push_back(child);
    }

    return children;
}

pop_mat DiffEvol::select_population(pop_mat children, pop_mat parents){
    pop_mat new_population;
    
    for(int i = 0; i < children.size(); i++){
        new_population.push_back(children[i].fitness <= parents[i].fitness ? children[i] : parents[i]);
    }

    return new_population;
}

double_vec DiffEvol::de_rand_1_bin(double_vec pop, double_vec parent1, double_vec parent2, double_vec parent3, int wf, int cr){
   
   double_vec sample(pop.size());
//    std::uniform_int_distribution<int> dis(0, pop_size - 1);

   int cut = gen() % (pop.size() - 1) + 1;

   for (double_vec::size_type i = 0; i < sample.size(); i++) {
        sample[i] = pop[i];
        if (i == cut || (double)gen() < cr) {
            double v = parent3[i] + wf * (parent1[i] - parent2[i]);
            v = std::max(v, this->lb[i]);
            v = std::min(v, this->ub[i]);
            sample[i] = v;
        }
    }
    return sample;
}


double DiffEvol::objective_function(double_vec& cromo){
    std::vector<double> bins;
    int aux_weight = 0;

    std::unordered_set<double> unique_values;
    int penalty = 0;
 
    for(double value : cromo){
        if(unique_values.count(value) == 0){
            unique_values.insert(value);
        }else{
            penalty++;
        }
    }
    
    for(auto i : cromo){
        if(aux_weight + this->w[i] <= this->capacity){
            aux_weight += this->w[i];
        }else{
            bins.push_back(aux_weight);
            aux_weight = 0;
        }
    }

    double sum_b = 0;
    #pragma omp parallel for reduction(+:sum_b)
    for (int i = 0; i < bins.size(); i++){
        sum_b += pow(bins[i]/this->capacity,2);
    }

    double fitness = bins.size() - sum_b;
    fitness += penalty;

    return fitness;
}

individual DiffEvol::search(){
    init_population();

    for(individual &i: this->population)
        i.fitness = objective_function(i.cromo);

    individual best = *std::min_element(population.begin(), population.end(), [](const individual& a, const individual& b) { return a.fitness < b.fitness; });
    
    for (int gen = 0; gen < this->max_iter; gen++) {
       pop_mat children = create_children(this->population, this->wf, cr);

       #pragma omp parallel for num_threads(8)
       for(individual &child: children)
            child.fitness = objective_function(child.cromo);
           
       this->population = select_population(children, this->population);

       std::sort(this->population.begin(), this->population.end(), [](const individual& a, const individual& b) { return a.fitness < b.fitness; });

    //    this->population.erase(this->population.begin() + pop_size, this->population.end());
       if(this->population[0].fitness < best.fitness){
              best = this->population[0];
       }
      
       std::cout << " > gen " << gen+1 << ", fitness = " << best.fitness << std::endl;
   }

    return best;
}


void DiffEvol::evaluate(unsigned int seed, std::string file_name){
    this->gen.seed(seed);

    auto start = Clock::now();

    individual best = search();

    auto end = Clock::now();

    std::ofstream file;
    file.open(OUTPUT_DIR+ file_name + "_results.txt", std::ios::app);

    file << "Population size: " << this->pop_size << std::endl;
    file << "Problem dimension: " << this->problem_dim << std::endl;
    file << "Lower bound: " << std::endl;

    for(double i : this->lb)
        file << i << " ";

    file << std::endl;
    file << "Upper bound: " << std::endl;

    for(double i : this->ub)
        file << i << " ";

    file << std::endl;
    file << "Weight factor: " << this->wf << std::endl;
    file << "Crossover rate: " << this->cr << std::endl;
    file << "Max iteration: " << this->max_iter << std::endl;
    file << "Best solution: " << std::endl;
    file << "[" ;
    
    for(double i : best.cromo)
        file << i << ", ";

    file << "]" << std::endl;

    file << "Best fitness: " << best.fitness << std::endl;

    file << "SEED: " << seed << std::endl << std::endl;

    file << "Solution Bins: " << std::endl;
    
    std::vector<double> bins;
    int aux_weight = 0;

    for(auto i : best.cromo){
        if(aux_weight + this->w[i] <= this->capacity){
            aux_weight += this->w[i];
        }else{
            bins.push_back(aux_weight);
            aux_weight = 0;
        }
    }
    file << "Bin Number: " << bins.size() << std::endl;
    for(auto i : bins){
        file << i << " ";
    }

    file << std::endl << "Elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " s";

    file << std::endl <<"----------------------------------------" << std::endl << std::endl;

    file.close();

    return;   
}
#endif