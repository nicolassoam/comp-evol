import tsplib95
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.PSO as pso
import os 
from tsp import TSPProblem as TSP, returnMatrix

path = 'results'
if not os.path.exists(path):
    os.makedirs(path)

RESULTS = []

path_atsp = 'instances/atsp'
path_tsp = 'instances/tsp'

problem = tsplib95.load(f'{path_tsp}/br17.atsp')
distance = returnMatrix(problem)

lb = [0, ] * len(distance)
ub = [len(distance)-1, ] * len(distance)

term_dict = {
    'max_fe': 200000,
}

algo = pso.C_PSO(3500,40)

using_algo = algo.name
t = TSP(lb = lb,ub = ub,minmax='min',distance_matrix= distance, n_dims = problem.dimension, obj_weights = np.ones(problem.dimension))

best_fit, best_sol = algo.solve(t,'thread', termination = term_dict,n_workers=6)

RESULTS.append(best_sol)

with open(f'results/result_{using_algo}_{problem.dimension}_{problem.name}.txt','w') as compiled:
    i = 0
    for sol in RESULTS:
        compiled.write(f'Execução {i}: {sol}\n')
        i += 1

