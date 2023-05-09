import numpy as np
import os 

f_n = [3,4,5,6,7,8,9]
array = []
#dim 10
for n in f_n:
    with open(f'results/result_CleverBookBeesA_2_f{n}.txt','r') as f:
        lines = f.readlines()
        for line in lines:
            array.append(float(line))

    with open(f'results/result_CleverBookBeesA_2_f{n}_treated.txt','w') as f:
        for item in array:
            f.write(f'{item}\n')
        f.write(f'Média: {np.mean(array)}\n')
        f.write(f'Desvio Padrão: {np.std(array)}\n')
        f.write(f'Mediana: {np.median(array)}\n')
        f.write(f'Máximo: {np.max(array)}\n')
        f.write(f'Mínimo: {np.min(array)}\n')
        f.write(f'Variância: {np.var(array)}\n')
        f.write(f'Coeficiente de Variação: {np.std(array)/np.mean(array)}\n')
        f.write(f'Coeficiente de Assimetria: {np.mean(array)/np.std(array)}\n')
        f.write(f'Coeficiente de Curtose: {np.mean(array)/np.std(array)}\n')
    array.clear()
        


