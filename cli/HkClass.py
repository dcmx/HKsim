from mpmath import mp
from typing import List

from networkx.classes.function import neighbors
from GraphClass import Graph, Node, NodeMissingError
    
class HKS:

    __graph : Graph
    __eps : mp.mpf
    name : str
    __medium_edge : [Node,Node]

    def __init__(self, graph: Graph, eps=mp.mpf(1),name ='_', edge = 0):
        self.__graph = graph
        self.__eps = eps
        self.name = name
        self.__medium_edge = edge
        if edge == 0:
            self.__medium_edge = [self.__graph.get_nodes()[0],self.__graph.get_nodes()[0]]
    
    def get_name(self):
        return self.name

    def get_epsilon(self):
        return self.__eps

    def get_number_of_nodes(self) -> int:
        return self.__graph.get_number_of_nodes()   

    def get_nodes(self) -> int:
        return self.__graph.get_nodes()    

    def get_communication_neighbors(self, node:Node) -> List[Node]: 
        socialNeighbors = self.__graph.get_neighbors(node)
        CommunicationNeighbors = list(filter(lambda neighbor: Node.node_distance(node,neighbor) <= self.__eps, socialNeighbors))
        return CommunicationNeighbors     

    def exist_delta_edge(self,delta):
        dist = Node.node_distance(self.__medium_edge[0], self.__medium_edge[1])
        if dist <= self.__eps and dist >= delta:
            return True

        for node1 in self.get_nodes():
            for node2 in self.__graph.get_neighbors(node1):
                dist = Node.node_distance(node1, node2)
                if dist <= self.__eps and dist >= delta:
                    self.__medium_edge[0] = node1
                    self.__medium_edge[1] = node2
                    return True
        return False     

    def get_update_position(self,node:Node): 
        if not self.__graph.is_updateable(node):
            raise NodeMissingError(node,self) 
        i = 0.0
        w = node.get_position() - node.get_position()
        for neighbour in self.get_communication_neighbors(node): 
            i = i + 1.0
            w = w + neighbour.get_position()
        return w/i

    def move_distance(self,node:Node):
        if not self.__graph.is_updateable(node):
            raise NodeMissingError(node,self) 
        currPos = node.get_position()
        newPos = self.get_update_position(node)
        return Node.position_distance(newPos,currPos)   

    def get_max_moving_node(self) -> Node:
        nodes = self.get_nodes()
        return max(nodes, key=lambda node: self.move_distance(node))    

    def potential_function_impact(self,node: Node):
        move = self.move_distance(node)
        neighbors = self.get_communication_neighbors(node)
        num_neighbors = len(neighbors)
        return move * move * (num_neighbors+1)     

    def get_max_potential_impacting_node(self) -> Node:
        nodes = self.get_nodes()
        return max(nodes, key=lambda node: self.potential_function_impact(node))      

    def update_node(self,node:Node):
        '''updates position of the node according to the updateFunktion of the HK system'''
        if not self.__graph.is_updateable(node):
            raise NodeMissingError(node,self)            
        pos = self.get_update_position(node)
        node.set_position(pos)

    def synchronously_update_nodes(self):
        new_positions = {}
        for node in self.get_nodes():
            newPos = self.get_update_position(node)
            new_positions[node] = newPos

        for node, newPos  in new_positions.items():
            node.set_position(newPos)    