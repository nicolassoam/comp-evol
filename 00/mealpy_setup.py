from mealpy.evolutionary_based import GA
import numpy as np


## x² - 3x + 4
def fitness_func(solution):
    return (solution**2 - 3*solution + 4)

problem_dict = {
    "fit_func": fitness_func,
    "lb": [-10, ] ,
    "ub": [10, ] ,
    "minmax": "min",
}

## Taxa de mutação de 1% e taxa de crossover de 60%
ga_model = GA.BaseGA(epoch=50000, pop_size=10, pc=0.60, pm=0.01)
best_position, best_fitness_value = ga_model.solve(problem_dict,mode="thread")

print(best_position)
print(best_fitness_value)