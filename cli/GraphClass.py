
from dataclasses import dataclass
import numpy as np
from mpmath import mp

class Node:
    __label : str
    __position : np.array

    def __init__(self,label, position):
        self.__label = label
        self.__position = position

    def set_position(self, position):
        self.__position = position  

    def get_label(self):
        return   self.__label

    def get_position(self):
        return self.__position

    def node_distance(self,v2):
        return self.position_distance(self.get_position(),v2.get_position())

    @staticmethod
    def position_distance(p1,p2):
        distVec = p1-p2
        dist = mp.sqrt(np.dot(distVec,distVec))
        return dist     




class Graph:
    __nodeList : list
    __neighbors : dict

    def __init__(self):
        self.__nodeList = []
        self.__neighbors = {}

    def get_nodes(self) -> list:   
        return self.__nodeList

    def get_number_of_nodes(self) -> int:   
        return len(self.__nodeList)

    def get_neighbors(self,node) -> list:
        return  self.__neighbors[node]     

    def is_contained(self, node) -> bool:
        return self.__nodeList.__contains__(node)

    def is_updateable(self, node) -> bool:
        if self.is_contained(node):
            return True
        print(f"node1 {node} is unknown")
        return False    

    def is_addable(self, node) -> bool:
        if self.is_contained(node):
            print("node already contained")
            return False
        return True   

    def is_neighbor(self, node1:Node, node2:Node) -> bool:
        if not (self.is_updateable(node1) and self.is_updateable(node2)):
            return False
        if self.__neighbors[node1].__contains__(node2):
            return True  
        return False       
            
    def exists_edge(self, node1: Node, node2: Node) -> bool:  
        a = self.__neighbors[node1].__contains__(node2)
        b = self.__neighbors[node2].__contains__(node1)
        if not (a and b):
             return False
        if a:
            print("beware, node1 already has neighbor node2")
        if b:
            print("beware, node2 already has neighbor node1")
        
        return True
           
    ########### manipulateGraph ###############

    def add_node(self, node: Node) -> None:    
        if not self.is_addable(node):
            raise NodeAddingError(node,self)
        self.__nodeList.append(node)
        self.__neighbors[node] = []

    def add_edge(self, node1: Node, node2: Node) -> None:
        if not self.is_updateable(node1):
            raise NodeMissingError(node1,self)
        if not self.is_updateable(node2):
            raise NodeMissingError(node2,self)
        self.exists_edge(node1, node2)

        self.__neighbors[node1].append(node2)
        self.__neighbors[node2].append(node1) 

    def add_self_loop(self, node: Node) -> None:
        if not self.is_updateable(node):
            raise NodeMissingError(node,self)
        self.exists_edge(node, node)   
        self.__neighbors[node].append(node)

    '''Removes ALL the selfloops from one node'''
    def remove_self_loops(self, node: Node) -> None:   
        if not self.is_updateable(node):
            raise NodeMissingError(node,self) 
        while self.is_neighbor(node, node):
            self.__neighbors[node].remove(node)

    ''' adds 1 selfloop to all the nodes'''
    def add_all_self_loops(self) -> None:
        for node in self.__nodeList:
            self.add_self_loop(node)

    def remove_all_self_loops(self) -> None:
        ''' removes all the selsloops from all the nodes'''
        for node in self.__nodeList:
            self.remove_self_loops(node)      

    def add_node_and_all_connecting_edges(self, node: Node) -> None:
        '''adds a new node and connects it to all the existing nodes'''
        if not self.is_addable(node):
            return False
        
        self.add_node(node)

        for neighbor in self.__neighbors:
            if not neighbor == node:
                self.add_edge(node, neighbor)
        return True    

    def add_Graph(self, graph):
        self.__nodeList.extend(graph.get_nodes())
        self.__neighbors.update(graph.__neighbors)

    def __str__(self):
        res = "nodes: \n"
        for k in self.get_nodes():
            res += "(" + str(k.get_label()) +", "+ str(k.get_position()) +")" + "\n"
        res += "\nnighbours: \n"
        for node, nighbours in self.__neighbors.items():
            res += node.get_label() + ": " 
            res += str([nighbour.get_label() for nighbour in nighbours]) + "\n"
        return res      

            

@dataclass
class NodeMissingError(Exception):
    node : Node
    graph: Graph
    message: str = "This node is not contained in the graph."

@dataclass
class NodeAddingError(Exception):
    node : Node
    graph: Graph
    message: str = "This node already contained in the graph and cannot be added."   