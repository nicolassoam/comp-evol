import numpy as np
import networkx
from mealpy.utils.problem import Problem 
import tsplib95
class TSPProblem(Problem):
    def __init__(self, lb, ub,minmax, distance_matrix,name="TSPProblem",**kwargs):
        self.distance_matrix = distance_matrix
        super().__init__(lb, ub, minmax,**kwargs)
        self.name = name
        
    def generate_position(self,lb=None, ub=None):
        return np.random.permutation(len(lb))
    
    def amend_position(self,solution,lb=None, ub=None):
        solution = np.clip(solution, lb,ub)
        # solution_int = solution.astype(np.int64)
        solution_set = set(list(range(0, len(solution))))
        solution_done = np.array([-1, ] * len(solution))
        solution_int = solution.astype(np.int32)
        city_unique, city_counts = np.unique(solution_int, return_counts=True)

        for idx, city in enumerate(solution_int):
            if solution_done[idx] != -1:
                continue
            if city in city_unique:
                solution_done[idx] = city
                city_unique = np.where(city_unique == city, -1, city_unique)
            else:
                list_cities_left = list(solution_set - set(city_unique) - set(solution_done))
                solution_done[idx] = list_cities_left[0]
        # print(f"Final solution: {solution_done}")
        # solution_done = np.clip(solution_done, lb,ub)
        return solution_done
        # return solution_int
        
        
    def fit_func(self, solution):
        solution = np.clip(solution, self.lb,self.ub)
        dist = self.distance_matrix[solution]
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
        # for i in range(len(distance)):
        #     for j in range(len(distance)):
        #         if i != j:
        #             distance[i,j] = np.linalg.norm(np.array(g.nodes[i]['coord']) - np.array(g.nodes[j]['coord']))
    return distance

def returnProblem(path, type):
    if type == 'atsp':
        problem = tsplib95.load(path)
        # distance = returnMatrix(problem)
        return problem
    elif type == 'tsp':
        problem = tsplib95.load(path,special=tsplib95.distances.euclidean)
        # distance = returnMatrix(problem)
        return problem

            
    