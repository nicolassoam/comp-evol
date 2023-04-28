from cec2017.functions import f3 as func
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.ALO as alo

alg = 'f3'
dim = 10
executions = 1000
files = []

def fit(solution):
        x = np.random.uniform(-100, 100, size=(executions, dim))
        val = func(x);
        
        # val = np.sum(solution**2);
        return val.min()


    
term_dict = {
    'max_fe': 10000 * dim,
}

# ga1 = ga.EliteMultiGA(51,1000,0.85,0.01)
ga1 = de.SHADE(1000,1000)
# ga1 = alo.BaseALO(1000,1000)
using_alg = ga1.name


for i in range(0,3):

    problem = {
        "fit_func": fit,
        "lb": [-100, ] * dim,
        "ub": [100, ] * dim,
        "minmax":"min",
        "n_dims":dim,
        # 'obj_weights':np.ones(3)
        "obj_weights":np.ones(executions),
        "log_to":"file",
        "log_file":f"results/result_{i}_{using_alg}_{dim}_{alg}.txt"
    }
    
    
    # file = open(f"results/result_{i}_{using_alg}_{dim}_{alg}.txt", "w")
    
    # file.write(f"Execucao {i}: \n")
    ga1.solve(problem, 'thread', termination = term_dict)
    
    files.append(f"results/result_{i}_{using_alg}_{dim}_{alg}.txt")
    
    # file.close()
    
with open(f'results/result_{using_alg}_{dim}_{alg}','w') as compiled:
    for fname in files:
        with open(fname) as infile:
            for line in infile:
                compiled.write(line)

    