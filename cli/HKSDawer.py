import networkx as nx
from mpmath import mp
import matplotlib.pyplot as plt
import numpy as np

from HkClass import HKS

import math
from mpmath import mp
from random import choice
import matplotlib.pyplot as plt
import statistics
import os
import pickle
from copy import deepcopy
import json

import csv

import networkx as nx
from matplotlib import animation, rc

########## Draw HKS #################
class HKSDrawer():

    @staticmethod
    def get_edge_list(hks:HKS):
        edgeList = []
        nodes = hks.get_nodes()
        for i in range(0,len(nodes)):
            node = nodes[i]
            for neighbour in hks.get_communication_neighbors(node):
                index = nodes.index(neighbour)    
                edgeList.append([i,index])
        return edgeList

    @staticmethod
    def get_position_dict(hks:HKS):
        pos ={}
        nodes = hks.get_nodes()
        for i in range(0,len(nodes)):
            node = nodes[i]
            weight = node.get_weight()
            position = weight.astype(np.float32)
            pos[i] = position
        return pos

    @staticmethod
    def draw_graph(hks:HKS):
        G_1 = nx.Graph()
        edgelist =  HKSDrawer.get_edge_list(hks)
        G_1.add_edges_from(edgelist)

        pos = HKSDrawer.get_position_dict()
        nx.draw(G_1, pos)
        plt.show()

# class visualizeProcess(object):

#     def __init__(self):
#         fig, ax = plt.subplots(figsize=(8,8))
#         self.fig = fig
#         self.ax = ax
    

#     def update(self,param):
#         (graph,count) = param
#         self.ax.clear()
#         limits=plt.axis('on')
#         self.ax.tick_params(left=True, bottom=True, labelleft=True, labelbottom=True)
#         plt.xlabel("step = {}".format(count))
#         G_1 = nx.Graph()
#         tempedgelist =  graph.getEdgeList()
#         G_1.add_edges_from(tempedgelist)

#         pos = graph.getPositionDict()
#         nx.draw(G_1, pos)
#         limits=plt.axis('on')
#         self.ax.tick_params(left=True, bottom=True, labelleft=True, labelbottom=True)

#     def step(self,graph,delta,stepFun):
#         count = 0
#         while(graph.existDeltaEdge(delta)):
#             count = count +1
#             stepFun(graph,count)
#             yield (graph, count)    

#     def do_nothing(self):
#         # FuncAnimation requires an initialization function. We don't
#         # do any initialization, so we provide a no-op function.
#         pass

#     def simulateProcess(self,graph, stepFun, saveName,savedFrames,delta):

#         ani = animation.FuncAnimation(
#             self.fig,
#             self.update,
#             init_func=self.do_nothing,
#             frames=self.step(graph,delta,stepFun),
#             interval=500,
#             save_count=savedFrames
#         )
#         writergif = animation.PillowWriter(fps=3)
#         ani.save(saveName,writer=writergif)
#         #plt.show()
