from cec2017.functions import f1 as func
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de

dim = 10
executions = 100


def fit(solution):
    x = np.tile(solution, (executions, dim))
    val = func(x);
    # val = np.sum(solution**2);
    return val

term_dict = {
    'max_fe': 10000 * dim,
}

problem = {
    "fit_func": fit,
    "lb": [-100, ] * dim,
    "ub": [100, ] * dim,
    "minmax":"min",
    "n_dims":10,
    # 'obj_weights':np.ones(3)
    "obj_weights":np.ones(executions),
}

ga1 = ga.MultiGA(51,100,0.85,0.125)
# ga1 = de.SADE(51,100)
print(ga1.solve(problem, 'thread', termination = term_dict))