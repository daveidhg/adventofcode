import networkx as nx

# Once again a python library that does all the work for you.
# Why bother doing it manually in c++ ¯\_(ツ)_/¯

graph = nx.Graph()
for line in open("2023/25/input.txt"):
    l, r = line.split(":")
    for node in r.strip().split():
        graph.add_edge(l, node)

graph.remove_edges_from(nx.minimum_edge_cut(graph))
group_a, group_b = nx.connected_components(graph)
print(f"Part one: {len(group_a) * len(group_b)}")