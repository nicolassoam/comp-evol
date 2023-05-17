import numpy as np
import networkx
from mealpy import Problem 

class TSPProblem(Problem):
    def __init__(self, lb, ub,minmax,name="TSP",distance_matrix = None,**kwargs):
        self.name = name
        self.distance_matrix = distance_matrix
        super().__init__(lb, ub, minmax,**kwargs)
        
        def generate_position(lb=None, ub=None):
            return np.random.permutation(len(lb))
        
        def amend_position(solution,lb=None, ub=None):
            solution = np.clip(solution, lb,ub)
            
            solution_int = solution.astype(int)
            return solution_int
        
    def fit_func(self, solution):
        solution = np.clip(solution, self.lb,self.ub)
        dist = self.distance_matrix[solution.astype(int)]
        sum =0.
        for i in range(len(dist)-1):
            sum += dist[i,i+1]
        sum += dist[-1,0]
        return sum


def returnMatrix(problem):
    if problem.edge_weight_format == "FULL_MATRIX":
        g = problem.get_graph()
        distance = networkx.to_numpy_matrix(g)
    else:
        ## euclidian distance
        g = problem.get_graph()
        distance = networkx.to_numpy_matrix(g)
        for i in range(len(distance)):
            for j in range(len(distance)):
                if i != j:
                    distance[i,j] = np.linalg.norm(np.array(g.nodes[i]['coord']) - np.array(g.nodes[j]['coord']))

    return distance

            
    