import matplotlib.pyplot as plt
import os
import pickle
from copy import deepcopy


def boxPlot(boxData,figureName,folderName,addHor = False,line = 0,title = ""):
    #print(box)
    #plt.title(title)
    saveName = folderName + '/' + figureName  + '.png'
    os.makedirs(folderName, exist_ok=True)

    figureWidth = 2.5* float(len(boxData))
    figureHeight = 10.0
    fig, ax = plt.subplots()
    fig.set_size_inches(figureWidth, figureHeight)
    # ax.set_title(figureName)
    dataBox = []
    xLabels =[] 
    #print('given data:')
    #print(boxData)
    for label in boxData:
        data = boxData[label]
        x =float(len(data))-0.5
        for key in data:
            dataBox.append(list(data[key])) 
            xLabels.append(key)
        xLinePosition =  float(len(xLabels))  
        ax.axvline(xLinePosition +0.5, color = 'black', linestyle='--')
        yPositionLabel = min(min(dataBox,key = min))
        plt.text(xLinePosition - x + 0.5, yPositionLabel, label)   
        plt.gcf().text(xLinePosition - x + 0.5, 0, label)
    #print('plot data:')
    #print(dataBox)    
    plt.boxplot(dataBox)
    plt.ylabel('steps to equilibrium')

    
    # Add a horizontal grid to the plot, but make it very light in color
    # so we can use it for reading data values but not be distracting
    ax.yaxis.grid(True, linestyle='-', which='major', color='lightgrey', alpha=0.5)   
    xtickNames = plt.setp(ax, xticklabels=xLabels)
    #plt.setp(xtickNames, rotation=45, fontsize=8)

    if addHor:
        plt.axhline(y=line, color='grey', linestyle='-')

    plt.setp(xtickNames, rotation=45)
    plt.savefig(saveName)
    plt.clf
    plt.close()
    print("saved figure" + saveName)


def saveData(data,folderName,dataName):
    os.makedirs(folderName, exist_ok=True)
    saveName = folderName + '/' + dataName  + '.txt'
    with open(saveName, 'wb') as handle:
        pickle.dump(data, handle)

def loadData(folderName,dataName):
    os.makedirs(folderName, exist_ok=True)
    saveName = folderName + '/' + dataName  + '.txt'
    with open(saveName, 'rb') as handle:
        data = pickle.loads(handle.read())      
    return data       


def scaleDataHelp(data,scaleFun):
    
    
    data1 = deepcopy(data)

    for label, localData in data1.items():
        print("label: {}".format(label))
        numbers = [s for s in str.split(label)]
        print(numbers)
        n = float(numbers[2])
        
        print("n = {}".format(n))

        div = scaleFun(n)
        for (key,array) in localData.items():
            array[:] = [x/(div) for x in array]
            localData[key] = array
    return data1	

def remove_instance_from_data(data, name:str):

    dataNew = {}

    for label, localData in data.items():
        localDataNew = {}
        for label2, localList in localData.items():
            if not label2 == name:
                localDataNew[label2] = localList
        dataNew[label] = localDataNew  

    return dataNew

def merge_data(data1,data2):
    
    dataNew = deepcopy(data1)

    for label, localData in data2.items():
        if not label in dataNew:
            dataNew[label] = localData
        else:
            localDataNew = dataNew[label]
            for label2, localList in localData.items():
                if not label2 in localDataNew:
                    localDataNew[label2] = localList
                else:   
                    localDataNew[label2].extend(localList) 
    return dataNew               



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

    # with open(saveName, 'a+') as handle:
    #     pickle.dump(data, handle)


