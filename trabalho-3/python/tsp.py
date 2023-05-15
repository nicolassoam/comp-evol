import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.BeesA as ba
import os
from mealpy import Problem 
import tsplib95
import networkx


path_atsp = 'instances/atsp'
path_tsp = 'instances/tsp'

problem = tsplib95.load(f'{path_atsp}/br17.atsp')

g = problem.get_graph()

distance = networkx.to_numpy_matrix(g)


class TSP(Problem):
    def __init__(self, lb, ub,minmax,distance_matrix = None,**kwargs):
        super().__init__(lb, ub, minmax,**kwargs)
        self.distance_matrix = distance_matrix
        
    def generate_position(self, lb=None, ub=None):
        return np.random.permutation(len(self.distance_matrix))
    
    def amend_position(self, solution, lb=None, ub=None):
        np.clip(solution, lb,ub)
        
        
    
    def fit_func(self, solution):
        dist = self.distance_matrix[solution]
        sum =0.
        for i in range(len(dist)-1):
            sum += dist[i,i+1]
        sum += dist[-1,0]
        return sum
            
    