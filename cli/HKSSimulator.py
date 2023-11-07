from typing import List
from HkClass import HKS
import os

import plotSimulations as simPlot

from HKSUpdateMathods import UpdateStrategy
from GraphConstructors import GrpahConstructor

import copy

import multiprocessing


def simulate_delta_stability(system: HKS, updateMethod: UpdateStrategy,delta):
    count = 0
    sysCopy = copy.deepcopy(system)
    while sysCopy.exist_delta_edge(delta):
        count = updateMethod.update_hks(sysCopy, count)
    resultString = "{}, {}, {}, {}".format(system.get_number_of_nodes(),count,system.get_name(),updateMethod.getName())    
    print(resultString)   
    return count    


def simulate_several_runs(system: HKS, updateMethod: UpdateStrategy, delta, runs: int):
    updateMethod.reset()

    pool = multiprocessing.Pool()
    result_list = [pool.apply_async(simulate_delta_stability, args=(system, updateMethod, delta)) for _ in range(0,runs)]
    
    pool.close()
    pool.join()
    
    return [res.get() for res in result_list]   

def simulate_systems(constructors: List[GrpahConstructor],n:int, eps, delta, updateMethod: UpdateStrategy, runs: int):
    simulationResults = {}

    for constructor in constructors:
        system = HKS(constructor.construct_graph(n),eps,constructor.get_name())
        updateList = simulate_several_runs(system,updateMethod,delta,runs)
        simulationResults[constructor.get_name()] = updateList

    return simulationResults

def simulate_range_n(constructors: List[GrpahConstructor],range_n, eps, delta, update_method: UpdateStrategy, runs: int):
    data = {}   
    for n in range_n:    
        label = "n = {}".format(n)       
        data[label] = simulate_systems(constructors,n, eps, delta, update_method, runs)
        #simPlot.saveData(data,"Test","tempSimulateRangeN")
    return data    

def simulate_range_delta(constructors: List[GrpahConstructor],n, eps, range_delta, update_method: UpdateStrategy, runs: int):
    data = {}   
    for eps_delta in range_delta:
        delta = float(eps)/eps_delta
        label = "eps/delta = {}".format(eps_delta)
        print(label)
        data[label] = simulate_systems(constructors,n, eps, delta, update_method, runs)
        print(data)
        #simPlot.saveData(data,"Test","tempSimulateRangeDelta")
    return data 

def data_to_comma_seperated_list(data, folder_name,document_name):
    os.makedirs(folder_name, exist_ok=True)
    saveName = folder_name + '/' + document_name  + '.txt'
    print(saveName)

    for label, localData in data.items():
        splitLabel = [s for s in str.split(label)]
        n = float(splitLabel[2])
        for label2, localList in localData.items():
            for entry in localList:
                line = str(int(n)) +"," +str(entry) +"," +str(label2)+"\n"
                with open(saveName, 'a+') as file:
                    file.write(line)