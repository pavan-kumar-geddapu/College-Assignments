SOLVING TRAVELLING SALESMAN PROBLEM USING A* ALGORITHEM
-------------------------------------------------------

*   Initial state : Agent in the start position with not visited any other node

    Ending state : Agent has visited all the nodes and reached start position again

    h(n)    : distance to the nearest unvisited node from the current node + estimated distance to travel all the unvisited nodes (MST heuristic used here) + nearest distance from an unvisited city to the start city

*   Minimum Spanning Tree (MST) calculated using Kruskal's algorithem.