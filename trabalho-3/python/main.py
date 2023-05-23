import tsplib95
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.PSO as pso
import os 
from tsp import TSPProblem as TSP, returnMatrix, returnProblem

path = 'results'
if not os.path.exists(path):
    os.makedirs(path)

RESULTS = []

BERLIN52= 'instances/tsp/berlin52.tsp'
BR17 = 'instances/atsp/br17.atsp'
CH130 = 'instances/tsp/ch130.tsp'
FTV70 = 'instances/atsp/ftv70.atsp'


problem_tsp = returnProblem(BERLIN52,'tsp')
distance = returnMatrix(problem_tsp)

def fit_func(solution):
    # solution = np.random.permutation(problem_tsp.dimension)
    solution = np.clip(solution, [0,]*problem_tsp.dimension,[problem_tsp.dimension-1,]*problem_tsp.dimension)
   
    # dist = distance[solution.astype(np.int64)]
    # print(dist)
    sum =0.
    for i in range(len(distance)-1):
        sum += distance[solution[i],solution[i+1]]
    sum += distance[solution[-1],solution[0]]
    return sum

def generate_position(lb=None, ub=None):
    return np.random.permutation(len(lb))
    
def amend_position(solution,lb=None, ub=None):
    solution = np.random.permutation(len(lb))
    solution = np.clip(solution, lb,ub)
    
    solution_int = solution.astype(np.uint64)
    
    return solution_int

# lb = [0, ] * len(distance)
# ub = [len(distance)-1, ] * len(distance)

problem = {
    "fit_func": fit_func,
    "lb": [0, ] * problem_tsp.dimension,
    "ub": [problem_tsp.dimension-1, ] * problem_tsp.dimension,
    "minmax":"min",
    "n_dims":problem_tsp.dimension,
    "obj_weights":np.ones(len(distance)),
    "generate_position": generate_position,
    "amend_position": amend_position,
}

term_dict = {
    'max_fe': 70000,
}

algo = pso.C_PSO(4500,20)

using_algo = algo.name
# t = TSP(lb = lb,ub = ub,minmax='min',distance_matrix= distance, n_dims = problem.dimension, obj_weights = np.ones(problem.dimension))

best_fit, best_sol = algo.solve(problem,'thread', termination = term_dict,n_workers=6)

RESULTS.append(best_sol)

with open(f'results/result_{using_algo}_{problem_tsp.dimension}_{problem_tsp.name}.txt','w') as compiled:
    i = 0
    for sol in RESULTS:
        compiled.write(f'Execução {i}: {sol}\n')
        i += 1

