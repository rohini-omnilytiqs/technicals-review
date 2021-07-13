import networkx as nx
import heapq

# get shortest path from a source
def dijkstra(G, source):
    nodes_heap = [] # PQ to keep track of nearest node
    distances = {} # keeps track of shortest distance to a node
    previous = {} # keeps track of previous node in shortest path
    visited = [] # workaround for not being able to update the PQ

    # for all the nodes, set distance to inf except for source, which is 0
    for node in G.nodes:
        if node == source:
            distances[node] = 0
            heapq.heappush(nodes_heap, (0, node))
            previous[node] = None
        else:
            distances[node] = 1000
            heapq.heappush(nodes_heap, (1000, node))

    updated = True

    # continue with dijkstras until we stop updating distances
    while(updated):

        # will only perform dijkstras on nodes we didn't already do - this is a workaround because we cannot update info in PQ
        in_visited = True
        while (in_visited):
            curr_dist, curr_node = heapq.heappop(nodes_heap)
            if curr_node not in visited:
                in_visited = False

        updated = False

        # going through all neighbors of node currently being explored 
        # if there exists a shorter path to the neighbor through the current node, we perform an update
        for neighbor in G.neighbors(curr_node):
            edge_weight = G[curr_node][neighbor]["weight"] 
            new_distance = edge_weight + curr_dist
            if (new_distance < distances[neighbor]):
                distances[neighbor] = new_distance
                heapq.heappush(nodes_heap, (new_distance, neighbor))
                previous[neighbor] = curr_node
                updated = True

        visited.append(curr_node) # mark the node as updated
    return previous

def topological_sort(G):
    # get all source nodes (node with no incoming edges) and add them to topo sort
    topo_sort = []
    nodes_stack = []
    visited =[]

    for node in G.nodes:
        if not G.in_edges([node]):
            nodes_stack.append(node)
            visited.append(node)
    
    if not nodes_stack:
        return None # there was no source node
    
    visited = []

    # remove incoming edges from nodes we have already seen and get the next source nodes
    while(len(nodes_stack) != 0):
        curr_node = nodes_stack.pop()
        print(curr_node)
        topo_sort.append(curr_node)

        for neighbor in G.neighbors(curr_node):
            if is_next_source_node(G, neighbor, visited):
                nodes_stack.append(neighbor)
                visited.append(neighbor)
    
    # we couldn't finish the topological sort because there was a cycle, meaning, we couldn't get a next source node
    if len(topo_sort) != len(G.nodes):
        return None

    return topo_sort

# helper function to determine if by removing edges from nodes we have already explored, do we have a source node?
def is_next_source_node(G, node, visited):
    for from_node, _ in G.in_edges([node]):
        if from_node not in visited:
            return False
    return True

# find shortest path from source to target in a faster version of BFS
# basically, do BFS from source to target and target to source
def bidirectional_search(G, source, target):
    source_visited = [source]
    target_visited = [target]

    source_queue = [source]
    target_queue = [target]

    source_parent = {}
    target_parent = {}

    source_parent[source] = -1
    target_parent[source] = -1

    shortest_path = []

    # if the queues are empty and we still haven't returned, we don't have a path
    while (source_queue and target_queue):
        curr_source = source_queue.pop(0)
        source_visited.append(curr_source)

        curr_target = target_queue.pop(0)
        target_visited.append(curr_target)

        for neighbor in G.neighbors(curr_source):
            # add to the queue if we haven't seen the nieghbor before
            if neighbor not in source_visited:
                source_queue.append(neighbor)
                source_parent[neighbor] = curr_source

            # if we came across the neighbor from searching the target, we have found the earliest intersection
            if neighbor in target_visited:
                shortest_path.append(neighbor)

                # get the parents of the neighbor to build the shortest path
                while neighbor!=source:
                    shortest_path.insert(0, source_parent[neighbor])
                    neighbor = source_parent[neighbor]
                 
                neighbor = shortest_path[-1]

                # get the children of the neighbor to finish building the shortest path
                while neighbor != target:
                    shortest_path.append(target_parent[neighbor])
                    neighbor = target_parent[neighbor]
    
                
                return shortest_path
        
        for _, out_neighbor in G.edges(curr_target): # using out_neighbor bc this is basically BFS on G.rev
            # add to the queue if we haven't seen the neighbor before
            if out_neighbor not in target_visited:
                target_queue.append(out_neighbor)
                target_parent[out_neighbor] = curr_target

            # if we came across the out_neighbor from searching the source, we found the earliest intersection
            if out_neighbor in source_visited:
                shortest_path.append(out_neighbor)

                # get the children of the neighbor to build the shortest path
                while out_neighbor!=target:
                    shortest_path.append(target_parent[out_neighbor])
                    out_neighbor = target_parent[out_neighbor]
                
                out_neighbor = shortest_path[-1]

                # get the parents of the neighbor to finish building the shortest path
                while out_neighbor != source:
                    shortest_path.insert(0, source_parent[out_neighbor])
                    out_neighbor = source_parent[out_neighbor]
                
                return shortest_path
    return None

G = nx.Graph()
G.add_nodes_from(['A', 'B', 'C', 'D', 'E'])

G.add_weighted_edges_from([('A', 'B', 6), ('A', 'D', 1), ('B', 'D', 2), ('B', 'E', 2), ('B', 'C', 5), ('C', 'E', 5), ('D', 'E', 1)])

prev = dijkstra(G, 'A')
print(prev)

G1 = nx.DiGraph()
G1.add_nodes_from([6, 1, 5, 0, 2, 3, 4])
G1.add_edges_from([
    (6, 1), 
    (1, 5),
    (6, 5),
    (0, 1),
   # (0, 2),
    (2, 0),
    (1, 2),
    (5, 4),
    (5, 3),
    (2, 3)
])

topo_sort = topological_sort(G1)
print(topo_sort)

G2 = nx.Graph()
G2.add_nodes_from([0, 12, 5, 7, 6, 8, 1, 3, 9, 4, 2, 10, 12, 11])
G2.add_edges_from([
    (0, 13),
    (13, 5),
    (5, 6),
    (5, 7),
    (7, 8),
    (0, 1),
    (1, 7),
    (1, 3),
    (3, 9),
    (3, 4),
    (0, 2),
    (2, 10),
    (2, 12),
    (0, 11)
])

path = bidirectional_search(G2, 5, 4)
print(path)