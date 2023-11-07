from GraphClass import Graph
from GraphClass import Node

from mpmath import mp

from abc import ABC, abstractmethod

################# Graph Constructors #################

class GrpahConstructor(ABC):
    name = '_'

    @abstractmethod
    def construct_graph(self, n: int, label_prefix = '_', start_position = 0 ,self_loops=True):
        pass

    def get_name(self):
        return self.name


class CliqueOnePositionGraphConstructor(GrpahConstructor):
    name = 'CliqueStatic'

    def construct_graph(self,n: int, label_prefix= 'c', start_position=0,self_loops=True) -> Graph:
        graph = Graph()

        for i in range(0,n):
            label = label_prefix + str(i)
            node = Node(label,start_position)
            graph.add_node_and_all_connecting_edges(node)

        if self_loops:
            graph.add_all_self_loops()   
        return graph    

class CliqueEqualDistanceGraphConstructor(GrpahConstructor):
    name = 'CliqueSpread'

    def __init__(self,nodeDistance):
        self.___nodeDistance = nodeDistance


    def construct_graph(self,n: int, label_prefix='c', start_position=0,self_loops=True) -> Graph:
        graph = Graph()
        position = start_position
        for i in range(0,n):
            label = label_prefix + str(i)
            node = Node(label,position)
            graph.add_node_and_all_connecting_edges(node)
            position += self.___nodeDistance

        if self_loops:
            graph.add_all_self_loops()     
        return graph       

class PathEqualDistanceGraphConstructor(GrpahConstructor):
    name = 'PathEqDist'

    def __init__(self,nodeDistance):
        self.___nodeDistance = nodeDistance

    def construct_graph(self,n: int, label_prefix='p', start_position=0,self_loops=True) -> Graph:    

        distanceArray = [self.___nodeDistance] * (n-1)
        constructor = PathWithDistanceConstructor(distanceArray)
        graph = constructor.construct_graph(n,label_prefix,start_position,self_loops=False)

        if self_loops:
            graph.add_all_self_loops()              
        return graph 
        
class PathWithDistanceConstructor(GrpahConstructor):
    name = 'PathSpread'

    def __init__(self,dictanceVector):
        self.__dictanceVector = dictanceVector    

    def construct_graph(self,n: int, label_prefix = 'p', start_position=0,self_loops=True) -> Graph:    
        graph = Graph()
        position = start_position

        label = label_prefix + "0"
        nodeOld = Node(label,position)

        graph.add_node(nodeOld)

        for i in range(1,n):
            position += self.__dictanceVector[i-1]
            label = label_prefix + str(i)
            node = Node(label,position)
            graph.add_node(node)
            graph.add_edge(node,nodeOld)

            nodeOld = node  

        if self_loops:
            graph.add_all_self_loops()              
        return graph     

class DumbbellEqMvConstructor(GrpahConstructor):
    name = 'DumbbellEqMv'

    def __init__(self,largest_distance,EqMv = True):
        self.largest_distance= largest_distance
        self.EqMv = EqMv
    
    def construct_graph(self,n: int, label_prefix = '_', start_position=0,self_loops=True) -> Graph:
        
        n_viertel = int(n/4)

        if self.EqMv:
            hat_m = mp.mpf(self.largest_distance)/mp.mpf(n_viertel*n_viertel + 5.0*n_viertel-1)

            distanceArray =[0]*(2*n_viertel-1)
            for i in range(1,n_viertel+1):
                distanceArray[i-1] = self.largest_distance -3*(n_viertel - i)*hat_m
            for i in range(n_viertel+1,2*n_viertel):
                distanceArray[i-1] = self.largest_distance -3*(i - n_viertel)*hat_m    

            path_start_position =  (n_viertel+1)*hat_m            
            clique_right_start_position = (2* n_viertel -1)*self.largest_distance - 3.0*(n_viertel*n_viertel - n_viertel)*hat_m + 2*hat_m* (n_viertel +1)
        else:
            self.name = 'DumbbellMaxDist'
            path_start_position = 0 #(mp.mpf(self.largest_distance)/mp.mpf(n_viertel))*0.9999
            distanceArray =[self.largest_distance]*(2*n_viertel-1) 
            clique_right_start_position = self.largest_distance*(2*n_viertel-1) #+2*path_start_position*0.999

        clique_constr = CliqueOnePositionGraphConstructor()
        PathConstructor = PathWithDistanceConstructor(distanceArray)

        clique_left = clique_constr.construct_graph(n_viertel,"cL",0,self_loops=False)
        clique_L_nodes = clique_left.get_nodes()

        path = PathConstructor.construct_graph(2*n_viertel,"p",path_start_position,self_loops=False)
        path_nodes = path.get_nodes()

        clique_right = clique_constr.construct_graph(n_viertel,"cR",clique_right_start_position,self_loops=False)
        clique_R_nodes = clique_right.get_nodes()

        graph = Graph()   
        graph.add_Graph(clique_left) 
        graph.add_Graph(path)
        graph.add_Graph(clique_right)
        
        for node in clique_L_nodes:
            graph.add_edge(node,path_nodes[0])

        for node in clique_R_nodes:
            graph.add_edge(node,path_nodes[2*n_viertel-1])    

        if self_loops:
            graph.add_all_self_loops()              
        return graph 




def main():
    constructor = CliqueOnePositionGraphConstructor()
    graph = constructor.construct_graph(5,"cl",0)
    print(graph)


    constructor = CliqueEqualDistanceGraphConstructor(2)
    graph = constructor.construct_graph(5,"c",0)
    print(graph)

    constructor = PathEqualDistanceGraphConstructor(1)
    graph = constructor.construct_graph(5,"p",0)
    print(graph)


    constructor = PathWithDistanceConstructor([1,2,2,1])
    graph = constructor.construct_graph(5,"p",0)
    print(graph)

    n = 16
    d = n*n/16  + 5*n/4-1
    constructor = DumbbellEqMvConstructor(d)
    graph = constructor.construct_graph(n,"p",0)
    print(graph)

    n = 12
    d = n*n/16  + 5*n/4-1
    constructor = DumbbellEqMvConstructor(d,False)
    graph = constructor.construct_graph(n,"p",0)
    print(graph)

if __name__ == "__main__":
    main()