import tsplib95
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.PSO as pso
import os 
import mealpy.utils.problem as Problem
from tsp import TSPProblem ,returnMatrix, returnProblem

path = 'results'
if not os.path.exists(path):
    os.makedirs(path)

RESULTS = []

BERLIN52= 'instances/tsp/berlin52.tsp'
BR17 = 'instances/atsp/br17.atsp'
CH130 = 'instances/tsp/ch130.tsp'
FTV70 = 'instances/atsp/ftv70.atsp'


problem_tsp = returnProblem(FTV70,'atsp')
distance = returnMatrix(problem_tsp)
# distance = np.triu(distance)
lb = [0, ] * problem_tsp.dimension
ub = [problem_tsp.dimension-1, ] * problem_tsp.dimension


term_dict = {
    'max_fe': 70000,
}

# algo = pso.C_PSO(4500,10)
# algo = ga.EliteSingleGA(10000,10)
algo = de.BaseDE(10000,10)

using_algo = algo.name

t = TSPProblem(lb = lb,ub = ub,minmax='min',distance_matrix= distance, n_dims = problem_tsp.dimension, obj_weights = np.ones(problem_tsp.dimension))

best_fit, best_sol = algo.solve(t,'thread', termination = term_dict,n_workers=6)

RESULTS.append(best_sol)

with open(f'results/result_{using_algo}_{problem_tsp.dimension}_{problem_tsp.name}.txt','a') as compiled:
    i = 0
    for sol in RESULTS:
        compiled.write(f'Execução {i}: {sol}\n')
        i += 1

