#ifndef DE_H
#define DE_H

#include <random>
#include <vector>

#define SEED 5
typedef std::vector<std::vector<double>> pop_mat;
typedef std::vector<double> double_vec;
std::mt19937 gen(SEED);

class DiffEvol {
    private:
        long pop_size;
        long problem_dim;
        pop_mat population; 
        double_vec fitness;
        double_vec lb;
        double_vec ub;
        double wf;
        double cr;
        void init_population();
        pop_mat select_parents(pop_mat&pop, int current);
        pop_mat create_children(pop_mat &pop, int wf, int cr);
        pop_mat select_population(pop_mat parents, pop_mat children);
        pop_mat de_rand_1_bin(pop_mat &initial, double_vec parent1, double_vec parent2, double_vec parent3, int wf, int cr);
    public:
        DiffEvol(long pop_size, long problem_dim, double_vec lb, double_vec ub, double wf, double cr);
        void evaluate();
        void run();
        double_vec get_best();
        double_vec get_best_fitness();
        pop_mat get_population();
        double_vec get_fitness();
};

DiffEvol::DiffEvol(long pop_size, long problem_dim, double_vec lb, double_vec ub, double wf, double cr){
    this->pop_size = pop_size;
    this->problem_dim = problem_dim;
    this->lb = lb;
    this->ub = ub;
    this->wf = wf;
    this->cr = cr;
    init_population();
}

void DiffEvol::init_population(){
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    for (int i = 0; i < pop_size; i++){
        double_vec temp;
        for (int j = 0; j < problem_dim; j++){
            temp.push_back(lb[j] + (ub[j] - lb[j]) * dis(gen));
        }
        population.push_back(temp);
    }
}

pop_mat DiffEvol::select_parents(pop_mat&pop, int current){
    std::uniform_int_distribution<int> dis(0, pop_size - 1);

    int r1 = dis(gen);
    int r2 = dis(gen);
    int r3 = dis(gen);

    while (r1 == current || r2 == current || r3 == current || r1 == r2 || r1 == r3 || r2 == r3){
        r1 = dis(gen);
        r2 = dis(gen);
        r3 = dis(gen);
    }

    pop_mat parents(3);
    parents[0] = pop[r1];
    parents[1] = pop[r2];
    parents[2] = pop[r3];
    

    return parents;
}


pop_mat DiffEvol::create_children(pop_mat &pop, int wf, int cr){
    
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    pop_mat children;
    
    double_vec lb = this->lb;
    double_vec ub = this->ub;

    for(auto i = 0;i < pop.size(); i++){
        pop_mat parents = select_parents(pop, i);
        double_vec child;
        double_vec aux = pop[i];
    }

    return children;
}

pop_mat DiffEvol::select_population(pop_mat children, pop_mat parents){
    pop_mat new_population;
    for(auto child : children){
        for(auto parent: parents){
            new_population.push_back(child <= parent ? child : parent);
        }
    }
    return new_population;
}

/*
    Ruby function:
    def de_rand_1_bin(p0, p1, p2, p3, f, cr, search_space)
        sample = {:vector=>Array.new(p0[:vector].size)}
        cut = rand(sample[:vector].size-1) + 1
        sample[:vector].each_index do |i|
        sample[:vector][i] = p0[:vector][i]
        if (i==cut or rand() < cr)
        v = p3[:vector][i] + f * (p1[:vector][i] - p2[:vector][i])
        v = search_space[i][0] if v < search_space[i][0]
        v = search_space[i][1] if v > search_space[i][1]
        sample[:vector][i] = v
        end
    end

*/

pop_mat DiffEvol::de_rand_1_bin(pop_mat &pop, double_vec parent1, double_vec parent2, double_vec parent3, int wf, int cr){
   
   double_vec sample(pop[0].size());
   std::uniform_int_distribution<int> dis(0, pop_size - 1);
   int cut= dis(gen) +1;

   for (int i = 0; i < sample.size(); i++) {
        sample[i] = p0.vector[i];
        if (i == cut || (double)rand() / RAND_MAX < cr) {
            double v = p3.vector[i] + wf * (p1.vector[i] - p2.vector[i]);
            v = std::max(v, search_space[i].first);
            v = std::min(v, search_space[i].second);
            sample.vector[i] = v;
        }
    }
}
#endif