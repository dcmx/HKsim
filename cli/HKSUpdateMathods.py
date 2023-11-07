from HkClass import HKS

from abc import ABC, abstractmethod
#from random import choice
import random


############# Updtae HKS ################
class UpdateStrategy(ABC):
    name = '_'

    @abstractmethod
    def update_hks(self,hks:HKS,step:int) -> int:
        pass

    def getName(self) -> str:
        return self.name   

    def reset(self):
        pass     


class RandomUpdater(UpdateStrategy):   
    name = 'random'
    

    def __init__(self,random_seed):
        self.random_seed = random_seed
        rand = random.Random(random_seed)
        self.random_state = random.getstate()

    def reset(self):  
        random.setstate(self.random_state)


    def update_hks(self,hks:HKS,step:int) -> int:
        hks.update_node(random.choice(hks.get_nodes()))
        return step+1

class MaxMoveUpdater(UpdateStrategy):   
    name = 'maxMove'

    def update_hks(self,hks:HKS,step:int) -> int:
        hks.update_node(hks.get_max_moving_node())     
        return step+1   

class MaxPotentialImpactUpdater(UpdateStrategy):   
    name = 'optPot.'

    def update_hks(self,hks:HKS,step:int) -> int:
        hks.update_node(hks.get_max_potential_impacting_node())     
        return step+1          

class SynchronousUpdater(UpdateStrategy):   
    name = 'synchr.'

    def update_hks(self,hks:HKS,step:int) -> int:
        hks.synchronously_update_nodes()     
        return step+1 

class sequentialUpdater(UpdateStrategy):


    updateSequence : list

    def __init__(self,sequence):
          self.updateSequence = sequence
          self.name = 'seq.'

    def update_hks(self,hks:HKS,step:int) -> int:
        n = len(self.updateSequence)
        hks.update_node(self.updateSequence[(step-1)%n])     
        return step+1 

