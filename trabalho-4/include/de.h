#ifndef DE_H
#define DE_H

#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <utility>
#include <limits>

#define SEED 12

std::mt19937 gen(SEED);

typedef std::vector<double> double_vec;
typedef struct individual{
    double_vec vec;
    double fitness;
    individual(): fitness(0.0) {};
} individual;

typedef std::vector<individual> pop_mat;

class DiffEvol {
    private:
        long pop_size;
        long problem_dim;
        int max_iter;
        pop_mat population; 
        double_vec fitness;
        double_vec lb;
        double_vec ub;
        double wf;
        double cr;
        void init_population();
        void select_parents(pop_mat&pop, int current, int&p1, int&p2, int&p3);
        pop_mat create_children(pop_mat &pop, int wf, int cr);
        pop_mat select_population(pop_mat parents, pop_mat children);
        double_vec de_rand_1_bin(double_vec pop, double_vec parent1, double_vec parent2, double_vec parent3, int wf, int cr);
        individual search();
        double objective_function(double_vec &vec);
    public:
        DiffEvol(long pop_size, long problem_dim, int max_iter, double_vec lb, double_vec ub, double wf, double cr);
        void evaluate();
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
DiffEvol::DiffEvol(long pop_size, long problem_dim, int max_iter, double_vec lb, double_vec ub, double wf, double cr){
    this->pop_size = pop_size;
    this->problem_dim = problem_dim;
    this->lb = lb;
    this->ub = ub;
    this->wf = wf;
    this->cr = cr;
    this->max_iter = max_iter;
    
}

void DiffEvol::init_population(){
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    for (int i = 0; i < pop_size; i++){
        individual temp;
        for (int j = 0; j < problem_dim; j++){
            temp.vec.push_back(lb[j] + (ub[j] - lb[j]) * dis(gen));
            
        }
        temp.fitness = std::numeric_limits<double>::max();
        
        population.push_back(temp);
    }
}

void DiffEvol::select_parents(pop_mat&pop, int current, int&p1, int&p2, int&p3){
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
    
    for(auto i = 0;i < pop.size(); i++){
        int p1, p2, p3;
        select_parents(pop, i, p1, p2, p3);
        individual child;
        child.vec = de_rand_1_bin(pop[i].vec, pop[p1].vec, pop[p2].vec, pop[p3].vec, wf, cr);
        children.push_back(child);
    }

    return children;
}

pop_mat DiffEvol::select_population(pop_mat children, pop_mat parents){
    pop_mat new_population;
    for(individual child : children){
        for(individual parent: parents){
            new_population.push_back(child.fitness <= parent.fitness ? child : parent);
        }
    }
    return new_population;
}

double_vec DiffEvol::de_rand_1_bin(double_vec pop, double_vec parent1, double_vec parent2, double_vec parent3, int wf, int cr){
   
   double_vec sample(pop.size());
//    std::uniform_int_distribution<int> dis(0, pop_size - 1);
   int cut = gen() % (pop.size() - 1) + 1;
   
   for (int i = 0; i < sample.size(); i++) {
        sample[i] = pop[i];
        if (i == cut || (double)gen() / RAND_MAX < cr) {
            double v = parent3[i] + wf * (parent1[i] - parent2[i]);
            v = std::max(v, this->lb[i]);
            v = std::min(v, this->ub[i]);
            sample[i] = v;
        }
    }
    return sample;
}

double DiffEvol::objective_function(double_vec& vec){
    double sum = 0;
    for(double element : vec)
        sum += element * element;   
    return sum;
}

individual DiffEvol::search(){
    init_population();

    for(individual i: this->population)
        i.fitness = objective_function(i.vec);

    individual best = *std::min_element(population.begin(), population.end(), [](const individual& a, const individual& b) { return a.fitness < b.fitness; });
    for (int gen = 0; gen < this->max_iter; gen++) {
       pop_mat children = create_children(this->population, this->wf, cr);
       for (int i = 0; i < children.size(); i++) {
           children[i].fitness = objective_function(children[i].vec);
       }
       
       this->population.insert(this->population.end(), children.begin(), children.end());

       std::sort(this->population.begin(), this->population.end(), [](const individual& a, const individual& b) { return a.fitness < b.fitness; });

       this->population.erase(this->population.begin() + pop_size, this->population.end());

       if(this->population[0].fitness < best.fitness){
              best = this->population[0];
       }

       std::cout << " > gen " << gen+1 << ", fitness=" << best.fitness << std::endl;
   }

    return best;
}


void DiffEvol::evaluate(){
    
    std::cout << "Population size: " << this->pop_size << std::endl;
    std::cout << "Problem dimension: " << this->problem_dim << std::endl;
    std::cout << "Lower bound: " << std::endl;
    for(double i : this->lb)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "Upper bound: " << std::endl;
    for(double i : this->ub)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "Weight factor: " << this->wf << std::endl;
    std::cout << "Crossover rate: " << this->cr << std::endl;
    std::cout << "Max iteration: " << this->max_iter << std::endl;
    std::cout << "Best solution: " << std::endl;
    individual best = search();
    for(double i : best.vec)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "Best fitness: " << best.fitness << std::endl;

}
#endif