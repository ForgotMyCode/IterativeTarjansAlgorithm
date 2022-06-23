# Iterative Tarjan's Algorithm
My iterative variation of the Tarjan's strongly connected components algorithm implemented in **C++17**.

The algorithm returns a vector of vectors of ints (representing vertices in components).

Also, contains a sample Graph implementation. The Graph is not modified. The algorithm's state is not shared.

# Example usage:

```

Graph graph{8};

graph.AddEdge(1, 0);
graph.AddEdge(2, 1);
graph.AddEdge(2, 3);
graph.AddEdge(3, 2);
graph.AddEdge(0, 7);
graph.AddEdge(7, 1);
graph.AddEdge(6, 7);
graph.AddEdge(6, 1);
graph.AddEdge(5, 6);
graph.AddEdge(6, 5);
graph.AddEdge(4, 5);
graph.AddEdge(4, 4);
graph.AddEdge(4, 3);

auto const cycles = tarjanFindComponents(graph);

```

Interpreted output:

```
[ 1, 7, 0, ]
[ 3, 2, ]
[ 6, 5, ]
[ 4, ]
```

