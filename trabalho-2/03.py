from cec2017.functions import f9 as func
import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.BeesA as ba
import os 

# from ctypes import CDLL, POINTER, c_int, c_double
# import pathlib

# def cec17_test_func(x, f, nx, mx, func_num,
#                     ):
#     libname = f"{pathlib.Path().absolute()}\cec17_test_func.so"
#     print(libname)
#     dll_path=CDLL(libname)
#     functions = dll_path
#     x_pointer_type = POINTER(c_double * nx)
#     f_pointer_type = POINTER(c_double * mx)
#     nx_type = c_int
#     mx_type = c_int
#     func_num_type = c_int
#     functions.cec17_test_func.argtypes = [x_pointer_type, f_pointer_type,
#                                           nx_type, mx_type, func_num_type] 
#     functions.cec17_test_func.restype = None
#     x_ctype = (c_double * nx)()
#     for i, value in enumerate(x):
#         x_ctype[i] = value
#     f_ctype = (c_double * mx)()
#     for i in range(mx):
#         f_ctype[i] = 0
#     functions.cec17_test_func(x_pointer_type(x_ctype), f_pointer_type(f_ctype),
#                               nx, mx, func_num)
#     for i in range(len(f)):
#         f[i] = f_ctype[i]

path = 'results'
if not os.path.exists(path):
    os.makedirs(path)

n_times = 51
alg = func.__name__

dim = int(input("Dimensão: "))
executions = 1000

results = []

def fit(solution):
        # x = np.random.uniform(-100, 100, size=(executions, dim))
        solution = np.reshape(solution, (1, dim))
        # print(solution)
        # resp = POINTER(c_double * dim)
        # val =cec17_test_func(solution, resp, dim, executions, 2);
        val  = func(solution)

        return val

    
term_dict = {
    'max_fe': 10000 * dim,
}

# ga1 = ga.EliteSingleGA(3500,50,pc = 0.85,pm =0.025,selection='tournament')
# ga1 = de.SHADE(epoch = 3500,pop_size = 50, miu_f=0.5, miu_cr=0.5)
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
    
    # file = open(f"results/result_{i}_{using_alg}_{dim}_{alg}.txt", "w")
    
    best_fit, best_sol = ga1.solve(problem,'thread', termination = term_dict,n_workers=6)
    
    results.append(best_sol)
    
with open(f'results/result_{using_alg}_{dim}_{alg}.txt','w') as compiled:
    i = 0
    for sol in results:
        compiled.write(f'Execução {i}: {sol}\n')
        i += 1

    