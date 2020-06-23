import sys
import copy

class Graph: 
  
    def __init__(self,vertices): 
        self.V= vertices 
        self.graph = []         
   
    def addEdge(self,u,v,w): 
        self.graph.append([u,v,w]) 
   
    def find(self, parent, i): 
        if parent[i] == i: 
            return i 
        return self.find(parent, parent[i]) 
   
    def union(self, parent, rank, x, y): 
        xroot = self.find(parent, x) 
        yroot = self.find(parent, y)    
        if rank[xroot] < rank[yroot]: 
            parent[xroot] = yroot 
        elif rank[xroot] > rank[yroot]: 
            parent[yroot] = xroot  
        else : 
            parent[yroot] = xroot 
            rank[xroot] += 1

    def KruskalMST(self):   #kruskal's algo to find minimum spanning tree / source GeeksForGeeks.com
        result =[]   
        i = 0  
        e = 0 
        self.graph =  sorted(self.graph,key=lambda item: item[2])   
        parent = []
        rank = [] 
        for node in range(self.V): 
            parent.append(node) 
            rank.append(0) 
        while i<len(self.graph) and e < self.V -1 : 
            u,v,w =  self.graph[i] 
            i = i + 1
            x = self.find(parent, u) 
            y = self.find(parent ,v) 
            if x != y: 
                e = e + 1     
                result.append([u,v,w]) 
                self.union(parent, rank, x, y)              
        return result
    

def print_tree(tree):
    for i in range(len(tree)):
        print(tree[i])
    print("---")
    

def MSTdis(g,unvis):    #   to calculate estimated distance to travel all the unvisited nodes (MST heuristic used here)
    
    x = copy.deepcopy(unvis)    
    x.sort()
    
    G=Graph(len(x)) #   creating a graph with the nodes
    for i in range(len(x)):
        for j in range(i+1,len(x)):
            if g[x[i]][x[j]] != 0:
                G.addEdge(i , j , g[x[i]][x[j]])
                
    res=G.KruskalMST()
    
    dis=0
    if len(unvis)==len(res)+1:  #   if minimum spanning tree exists  
        for i in res:
            dis+=i[2]
    else:
        dis=1000000
        
    return dis


def h(g,current,unvis):
    
    if len(unvis) == 0:
        return g[0][current] if g[0][current]!=0 else 1000000   #   if edge is there from last node to start node else some big number
    
    a = 1000000   #   distance to the nearest unvisited node from the current node
    for i in unvis:
        if g[current][i] != 0:  #   if edge exists
            a = min(a,g[current][i])
            
    b = MSTdis(g,unvis)   #   estimated distance to travel all the unvisited nodes (MST heuristic used here)
    
    c = 1000000   #   nearest distance from an unvisited city to the start city
    for i in unvis:
        if g[0][i] != 0:
            c = min(c,g[0][i])

    return a+b+c    #   return h value

    
def Astar(g,no_of_vertices):
    
    init_unvisited = [i for i in range(1,no_of_vertices)] #initialisation of unvis nodes from start node
    init_visited = [[0,0,0]]
    init_visited[0][2] = h(g,0,init_unvisited)  #   calculating h value
    tree = [[init_visited[0][2],init_visited.copy(),init_unvisited.copy()]] #   To store all the paths from root to leaf
    
    print_tree(tree)
    
    while len(tree) > 0 and len(tree[0][2]) > 0:  #   loop until we found the solution
        
        unvis = copy.deepcopy(tree[0][2]) #   list of unvisited nodes in current path
        vis = copy.deepcopy(tree[0][1])   #   list of visited nodes in current path
        
        for i in unvis:
            
            if g[vis[-1][0]][i] != 0: #   if current node to next node distance is zero ignore as no path is available
                
                x = copy.deepcopy(unvis)
                x.remove(i) #   considering i as current node, so removing it from unvis
                
                gval = vis[-1][1] + g[vis[-1][0]][i]  #   calculating g value
                hval = h(g,i,x)   #   calculating h value
                    
                node = copy.deepcopy(tree[0])   # storing parent path
                
                node[0] = gval + hval   #   f = g + h
                node[1].append([i, gval, hval]) #  current leaf path 
                node[2] = x     # unvisited nodes list
                
                if node[0] < 1000000 :  # when a path exist append it to tree assuming all f values will be below 
                    tree.append(node)
           
        del tree[0] #   delete parent path
        
        print_tree(tree)
        
        tree =  sorted(tree,key=lambda item: item[0])   #   to get least f value for further extension 
          
    return tree[0][0]   #   return cost


def main():
    
    no_of_vertices=5    #   graph structure
    graph = [[0,1,1,2,2],
         [1,0,2,1,2],
         [1,2,0,2,1],
         [2,1,2,0,1],
         [2,2,1,1,0]]    
    
    print("minimum cost is : ", Astar(graph,no_of_vertices) )
    

if __name__ == "__main__":
    main()
