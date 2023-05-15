import numpy as np
import mealpy.evolutionary_based.GA as ga
import mealpy.evolutionary_based.DE as de
import mealpy.swarm_based.BeesA as ba
import os 
import tsplib95

path_atsp = 'instances/atsp'
path_tsp = 'instances/tsp'

problem = tsplib95.load(f'{path_atsp}/br17.atsp')