import pandas as pd
import random
import numpy as np
import operator
import matplotlib.pyplot as plt

def printRoute(cityList):       #   to print a possible route
    for i in range(len(cityList)):
        print("{} : {}".format(i+1,cityList[i]))

def plotGraph(cityList, flag):      #   to plot graph with given city coordinates
    x = []
    y = []
    for i in cityList:
        x.append(i[0])
        y.append(i[1])
    plt.scatter(x,y)
    if flag == 1:
        plt.plot(x,y)
    plt.show()

def createRoute(cityList):      #   to create a route with given city list
    route = random.sample(cityList, len(cityList))
    return route

def routeFitness(route):        #   to find fitness of given route 
    routeDistance=0
    for i in range(0,len(route)):
        fromCity = route[i]
        toCity = route[int((i+1)%len(route))]
        x = abs(fromCity[0]-toCity[0])
        y = abs(fromCity[1]-toCity[1])
        routeDistance += np.sqrt( (x ** 2) + (y ** 2) )
    return 1/float(routeDistance)       #   inverse of routeDistance is our fitness value
    
def rankRoutes(population):     #   ranking our present population with respect to fitness value
    fitnessResults={}
    for i in range(0,len(population)):
        fitnessResults[i]=routeFitness(population[i])
    return sorted(fitnessResults.items(), key = operator.itemgetter(1), reverse = True)

def createMatingPool(population, populationRanked, eliteSize):      #   creating a matingpool for breeding
    selectionResults = []
    df = pd.DataFrame(np.array(populationRanked), columns=["Index","Fitness"])      #   calculating relative fitness weight for each individual
    df['cum_sum'] = df.Fitness.cumsum()
    df['cum_perc'] = 100*df.cum_sum/df.Fitness.sum()        
    for i in range(0, eliteSize):       #   keeping the first (eliteSize) best routes in mating pool to introduce elitism
        selectionResults.append(populationRanked[i][0])
    for i in range(0, len(populationRanked) - eliteSize):       #   to get remaining individuals of matingpool
        pick = 100*random.random()                              #   by comparing randomly drawn number to these weights
        for i in range(0, len(populationRanked)):                
            if pick <= df.iat[i,3]:
                selectionResults.append(populationRanked[i][0])
                break
    matingPool = []
    for i in range(0,len(selectionResults)):
        matingPool.append(population[selectionResults[i]])
    return matingPool

def breed(parent1, parent2):        #   to breed to individuals to get a child 
    child = []
    childP1 = []
    childP2 = []    
    geneA = int(random.random() * len(parent1))
    geneB = int(random.random() * len(parent1))    
    startGene = min(geneA, geneB)
    endGene = max(geneA, geneB)     #   to get start, end indices for breeding (randomly)
    for i in range(startGene, endGene):
        childP1.append(parent1[i])        
    childP2 = [item for item in parent2 if item not in childP1]
    child = childP1 + childP2       #   to make sure no city is duplicated and no city was missed
    return child

def breedPopulation(matingPool, eliteSize):
    children = []
    length = len(matingPool) - eliteSize
    pool = random.sample(matingPool, len(matingPool))
    for i in range(0,eliteSize):        #   keeping the elite individuals to introduce elitism
        children.append(matingPool[i])    
    for i in range(0, length):      #   to get remaining children by breeding two parents
        child = breed(pool[i], pool[len(matingPool)-i-1])
        children.append(child)
    return children

def mutatePopulation(population, mutationRate):     #   to avoid local convergence by introducing novel routes 
    mutatedPopulation = []                          #   that will allow us to explore other parts of the solution space
    for individual in population:
        for swapped in range(len(individual)):
            if(random.random() < mutationRate):
                swapWith = int(random.random() * len(individual))
                individual[swapped],individual[swapWith] = individual[swapWith],individual[swapped]  
        mutatedPopulation.append(individual)        #   to make sure no city is duplicated and no city was missed
    return mutatedPopulation

def createNextGeneration(currentGeneration, eliteSize, mutationRate):       #   to create next generation from current population
    populationRanked = rankRoutes(currentGeneration)
    matingPool = createMatingPool(currentGeneration, populationRanked, eliteSize)
    children = breedPopulation(matingPool, eliteSize)
    nextGeneration = mutatePopulation(children, mutationRate)
    return nextGeneration
    

def geneticAlgorithm(cityList, populationSize, eliteSize, mutationRate, noOfGenerations):
    population=[]
    for i in range(0,populationSize):
        population.append(createRoute(cityList))
    print("Initial route distance: " + str(1 / rankRoutes(population)[0][1]))
    progressOfGA = []
    progressOfGA.append(1 / rankRoutes(population)[0][1])
    for i in range(0, noOfGenerations):     #   repeating the process for given number of iterations
        population = createNextGeneration(population, eliteSize, mutationRate)
        progressOfGA.append(1 / rankRoutes(population)[0][1])
    print("Final route distance: " + str(1 / rankRoutes(population)[0][1]))
    return population[rankRoutes(population)[0][0]] , progressOfGA      #   returning final route and progress of our genetic algorithem


if __name__ == "__main__" :
    cityList = []
    for i in range(0,20):
        cityList.append([int(random.random() * 100), int(random.random() * 100)])       #   creating cities with random coordinates
    finalRoute , progress = geneticAlgorithm(cityList,100,20,0.01,500)      #   usng genetic algorithem to get best route

    plotGraph(cityList,0)       #   ploting grphs
    print("Best route is: ")
    printRoute(finalRoute)
    plotGraph(finalRoute,1)
    plt.plot(progress)
    plt.ylabel('Distance')
    plt.xlabel('Generation')
    plt.show()  

