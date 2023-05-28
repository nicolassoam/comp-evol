import tsplib95
import networkx
import numpy as np
import os

if(os.path.exists('matrices')):
    pass
else:
    os.mkdir('matrices')

BERLIN52= 'instances/tsp/berlin52.tsp'
BR17 = 'instances/atsp/br17.atsp'
CH130 = 'instances/tsp/ch130.tsp'
FTV70 = 'instances/atsp/ftv70.atsp'

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

problem = returnProblem(BERLIN52,'tsp')
distance = returnMatrix(problem)

with open(f'matrices/{problem.name}.txt','w') as f:
    for i in range(len(distance)):
        for j in range(len(distance)):
            f.write(f'{distance[i,j].astype(np.int64)} ')
        f.write('\n ')