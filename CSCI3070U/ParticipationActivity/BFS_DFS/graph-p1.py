# Graph search 

class Graph: 
    def __init__(self):
        self.color = {}
        self.d = {}
        self.f = {}
        self.pi = {}
        self.adj = {}
      
    def addEdge(self,x,y):
        if x not in self.adj.keys():
            l = list()
        else:
            l = self.adj[x]
        l.append(y)
        self.adj[x] = l
 
    def setColorWhite(self):
        for v in self.adj:
            self.color[v] ='white'
            self.d[v] = -1
            self.f[v] = -1
            self.pi[v] = None
  
time = 0

#implement dfs_visit here
def dfs_visit(G, u):
    global time
    time += 1
    G.d[u] = time
    G.color[u] = 'gray'
    for v in G.adj[u]:
        if G.color[v] == 'white':
            G.pi[v] = u
            dfs_visit(G, v)
    G.color[u] = 'black'
    time += 1
    G.f[u] = time
    
    
def dfs(G):
    for u in G.adj:
        if G.color[u] == 'white':
            dfs_visit(G, u)

             
def main():
    
    g = Graph()
       
    g.addEdge('a','c')
    g.addEdge('a','e')
    g.addEdge('b','a')
    g.addEdge('b','d')
    g.addEdge('b','e')
    g.addEdge('c','b')
    g.addEdge('d','e')
    g.addEdge('d','f')
    g.addEdge('e','c')
    g.addEdge('f','e')
    g.addEdge('g','d')
    g.addEdge('g','f')
    g.addEdge('g','h')
    g.addEdge('h','e')
    
    g.setColorWhite()
    
    
    dfs_visit(g, 'g')

    
    print (g.d)
    print (g.f)

if __name__ == "__main__":
    main()
    