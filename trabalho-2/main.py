from cec2017.functions import f3 as func
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.BeesA as ba
import os 

path = 'results'
if not os.path.exists(path):
    os.makedirs(path)

n_times = 51
alg = func.__name__

dim = int(input("Dimensão: "))
executions = 1000

results = []

def fit(solution):
        solution = np.reshape(solution, (1, dim))
        val  = func(solution)

        return val

    
term_dict = {
    'max_fe': 10000 * dim,
}

ga1 = ba.CleverBookBeesA(3500,50)
using_alg = ga1.name


for i in range(0,n_times):

    problem = {
        "fit_func": fit,
        "lb": [-100, ] * dim,
        "ub": [100, ] * dim,
        "minmax":"min",
        "n_dims":dim,
        "obj_weights":np.ones(executions),
    }
    
    best_fit, best_sol = ga1.solve(problem,'thread', termination = term_dict,n_workers=6)
    
    results.append(best_sol)
    
with open(f'results/result_{using_alg}_{dim}_{alg}.txt','w') as compiled:
    i = 0
    for sol in results:
        compiled.write(f'Execução {i}: {sol}\n')
        i += 1

    