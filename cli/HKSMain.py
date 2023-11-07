
from HKSUpdateMathods import RandomUpdater, SynchronousUpdater
from GraphConstructors import DumbbellEqMvConstructor, PathEqualDistanceGraphConstructor
import HKSSimulator as sim 
import plotSimulations as simPlot
import math

from mpmath import mp
import os
import random

def load_and_scale_data(folderName, figureName):

    data = simPlot.loadData(folderName,figureName)
    scale_data(data,folderName, figureName)

def scale_data(data,folderName:str, figureName:str):   
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: 1),figureName,folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a),figureName+"DivN",folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a*a),figureName+"DivNN",folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a*a*a),figureName+"DivNNN",folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a*a*a*a),figureName+"DivNNNN",folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a*a*a*math.sqrt(a)),figureName+"DivNNNsqrtN",folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a*a*a*math.sqrt(a)*math.log(a)),figureName+"DivNNNsqrtNlogN",folderName)

def scale_data_delta_range(data,eps,folderName:str, figureName:str): 
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: a),figureName+"DivLinear",folderName)
    simPlot.boxPlot(simPlot.scaleDataHelp(data,lambda a: math.log(a)),figureName+"DivLog",folderName)



def run():

    folderName = "TestsHKS"
    os.makedirs(folderName, exist_ok=True)

    figureName = "PathVsDumbbellFirstHalf"
    testRangeN(folderName,figureName)

    figureName = "PathVsDumbbellSecondHalf"
    testRangeN2(folderName,figureName)

    testEpsilonDeltaRange(folderName)
    



def testRangeN(folderName,figureName):
    epsilon = 100.0
    delta = 1.0
    tests = 100

    minN = 4
    maxN = 43
    stepSize = 4

    randomSeed = 13451325
 

    constructors = []
    constructors.append(DumbbellEqMvConstructor(epsilon,EqMv = False))
    constructors.append(PathEqualDistanceGraphConstructor(epsilon))   

    simData = sim.simulate_range_n(constructors, range(minN,maxN,stepSize), epsilon, delta, RandomUpdater(randomSeed),tests)

    simPlot.saveData(simData,folderName,figureName+"Data")    
    simPlot.boxPlot(simData,figureName,folderName)             
    scale_data(simData,folderName, figureName+"Data")
    simPlot.data_to_comma_seperated_list(simData,folderName,figureName+"CommaSeparatedList")

def testRangeN2(folderName,figureName):
    epsilon = 100.0
    delta = 1.0
    tests = 100

    minN = 44
    maxN = 61
    stepSize = 4

    randomSeed = 13451325

    constructors = []
    constructors.append(DumbbellEqMvConstructor(epsilon,EqMv = False))
    constructors.append(PathEqualDistanceGraphConstructor(epsilon))   

    simData = sim.simulate_range_n(constructors, range(minN,maxN,stepSize), epsilon, delta, RandomUpdater(randomSeed),tests)

    simPlot.saveData(simData,folderName,figureName+"Data")    
    simPlot.boxPlot(simData,figureName,folderName)             
    scale_data(simData,folderName, figureName+"Data")
    simPlot.data_to_comma_seperated_list(simData,folderName,figureName+"CommaSeparatedList")

def testEpsilonDeltaRange(folderName):
    figureName = "testEpsilonDeltaRange10To100"
    epsilon = 100.0
    tests = 100

    n = 32

    simData = {}

    minEpsDelta = 10
    maxEpsDelta = 101
    deltaStepSize = 10

    randomSeed = 13451325

    constructors = []
    constructors.append(DumbbellEqMvConstructor(epsilon,EqMv = False))
    constructors.append(PathEqualDistanceGraphConstructor(epsilon))    

    print("starting test 2")
    
    simData = sim.simulate_range_delta(constructors, n, epsilon, range(int(minEpsDelta),int(maxEpsDelta),deltaStepSize), RandomUpdater(randomSeed),tests)
    
    simPlot.saveData(simData,folderName,figureName+"Data")    
    simPlot.boxPlot(simData,figureName,folderName)             
    scale_data_delta_range(simData,epsilon,folderName, figureName+"Data")
    simPlot.data_to_comma_seperated_list(simData,folderName,figureName+"CommaSeparatedList")

if __name__ == "__main__":
    run()    