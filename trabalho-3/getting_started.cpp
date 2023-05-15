#include <iostream>


#include <pagmo/algorithm.hpp>

#include <pagmo/algorithms/sade.hpp>

#include <pagmo/algorithms/pso.hpp>

#include <pagmo/archipelago.hpp>

#include <pagmo/problem.hpp>

#include <pagmo/problems/schwefel.hpp>

#include "tsp/tsp.cpp"

#include "config.h"

using namespace pagmo;


int main()

{
    string f_location = ATSP;
    TSPProblem tsp = readGraphATSP(f_location+"br17.atsp");
    

    problem prob{tsp};
    cout << prob.get_lb()[0] << endl;

    // 2 - Instantiate a pagmo algorithm (self-adaptive differential

    // evolution, 100 generations).

    algorithm algo{pso(1000)};
    algo.set_seed(42u);


    // 3 - Instantiate an archipelago with 16 islands having each 20 individuals.

    archipelago archi{16u, algo, prob, 20u};
    

    // 4 - Run the evolution in parallel on the 16 separate islands 10 times.

    archi.evolve(10);

    // 5 - Wait for the evolutions to finish.

    archi.wait_check();


    // 6 - Print the fitness of the best solution in each island.
    
    for (const auto &isl : archi) {

        std::cout << isl.get_population().champion_f()[0] << '\n';

    }
    cout << prob << endl;
}