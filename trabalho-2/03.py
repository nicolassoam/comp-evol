from cec2017.functions import f4 as func
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.ALO as alo
import os 


path = 'results'
if not os.path.exists(path):
    os.makedirs(path)

n_times = 52
alg = func.__name__

dim = int(input("Dimensão: "))
executions = 1000

results = []

def fit(solution):
        x = np.random.uniform(-100, 100, size=(executions, dim))
        val = func(x);

        return val.min()

    
term_dict = {
    'max_fe': 10000 * dim,
}

# ga1 = ga.EliteMultiGA(1000,1000,0.85,0.01)
ga1 = de.SHADE(1000,1000)
# ga1 = alo.BaseALO(1000,1000)
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
    
    # file = open(f"results/result_{i}_{using_alg}_{dim}_{alg}.txt", "w")
    
    best_fit, best_sol = ga1.solve(problem, 'thread', termination = term_dict)
    
    results.append(best_sol)
    
with open(f'results/result_{using_alg}_{dim}_{alg}.txt','w') as compiled:
    i = 0
    for sol in results:
        compiled.write(f'Execução {i}: {sol}\n')
        i += 1

    