using System;
using System.Collections.Generic;
class Graph
{
    public Dictionary<string, List<Tuple<string, int>>> baglantilidugumler;
    public Dictionary<string, List<string>> bitisikdugumler;
    public Graph()
    {
        baglantilidugumler = new Dictionary<string, List<Tuple<string, int>>>();
        bitisikdugumler = new Dictionary<string, List<string>>();
    }

    public void kenarEkle(string from, string to, int weight)
    {
        if (!baglantilidugumler.ContainsKey(from))
        {
            baglantilidugumler[from] = new List<Tuple<string, int>>();
        }
        baglantilidugumler[from].Add(new Tuple<string, int>(to, weight));

        if (!baglantilidugumler.ContainsKey(to))
        {
            baglantilidugumler[to] = new List<Tuple<string, int>>();
        }

        if (!bitisikdugumler.ContainsKey(from))
        {
            bitisikdugumler[from] = new List<string>();
        }
        bitisikdugumler[from].Add(to);

        if (!bitisikdugumler.ContainsKey(to))
        {
            bitisikdugumler[to] = new List<string>();
        }
    }
}
class MinHeap
{
    private List<Tuple<string, int>> heap;

    public MinHeap()
    {
        heap = new List<Tuple<string, int>>();
    }

    public void Add(string node, int distance)
    {
        heap.Add(new Tuple<string, int>(node, distance));
        int currentIndex = heap.Count - 1;
        while (currentIndex > 0)
        {
            int parentIndex = (currentIndex - 1) / 2;
            if (heap[currentIndex].Item2 >= heap[parentIndex].Item2)
                break;

            var temp = heap[currentIndex];
            heap[currentIndex] = heap[parentIndex];
            heap[parentIndex] = temp;

            currentIndex = parentIndex;
        }
    }
    public Tuple<string, int> ExtractMin()
    {
        
        var min = heap[0];
        heap[0] = heap[heap.Count - 1];
        heap.RemoveAt(heap.Count - 1);
        int currentIndex = 0;
        while (true)
        {
            int leftChild = 2 * currentIndex + 1;
            int rightChild = 2 * currentIndex + 2;
            int smallest = currentIndex;

            if (leftChild < heap.Count && heap[leftChild].Item2 < heap[smallest].Item2)
                smallest = leftChild;
            if (rightChild < heap.Count && heap[rightChild].Item2 < heap[smallest].Item2)
                smallest = rightChild;
            if (smallest == currentIndex)
                break;
            var temp = heap[currentIndex];
            heap[currentIndex] = heap[smallest];
            heap[smallest] = temp;

            currentIndex = smallest;
        }
        return min;
    }
    public bool IsEmpty()
    {
        return heap.Count == 0;
    }
}
class Program
{
    static void Main(string[] args)
    {
        Graph graph = new Graph();
        kenarEklesToGraph(graph);

        Console.WriteLine("agirliklarla en kisa yol:");
        var shortestPathDijkstra = Dijkstra(graph, "s", "t");
        PrintPath(shortestPathDijkstra);

        Console.WriteLine("\nkenar agirliklari 1 olan en kısa yol:");
        var shortestPathBFS = BFS(graph, "s", "t");
        PrintPath(shortestPathBFS);
    }
    static void kenarEklesToGraph(Graph graph)
    {
        graph.kenarEkle("s", "A", 1);
        graph.kenarEkle("s", "D", 4);
        graph.kenarEkle("s", "G", 4);
        graph.kenarEkle("A", "B", 2);
        graph.kenarEkle("A", "D", 2);
        graph.kenarEkle("B", "C", 2);
        graph.kenarEkle("C", "t", 4);
        graph.kenarEkle("D", "E", 3);
        graph.kenarEkle("E", "C", 1);
        graph.kenarEkle("E", "F", 3);
        graph.kenarEkle("E", "I", 6);
        graph.kenarEkle("F", "t", 3);
        graph.kenarEkle("F", "I", 1);
        graph.kenarEkle("G", "H", 6);
        graph.kenarEkle("H", "I", 6);
        graph.kenarEkle("I", "t", 4);
    }
    static Dictionary<string, int> Dijkstra(Graph graph, string start, string end)
    {
        var distances = new Dictionary<string, int>();
        var previousNodes = new Dictionary<string, string>();
        var visited = new HashSet<string>();
        var minHeap = new MinHeap();

        foreach (var node in graph.baglantilidugumler.Keys)
        {
            distances[node] = int.MaxValue;
        }
        distances[start] = 0;
        minHeap.Add(start, 0);
        while (!minHeap.IsEmpty())
        {
            var current = minHeap.ExtractMin();
            var currentNode = current.Item1;
            var currentDistance = current.Item2;
            if (currentNode == end)
                break;

            if (visited.Contains(currentNode))
                continue;
            visited.Add(currentNode);

            foreach (var neighbor in graph.baglantilidugumler[currentNode])
            {
                var neighborNode = neighbor.Item1;
                var edgeWeight = neighbor.Item2;
                var newDistance = currentDistance + edgeWeight;

                if (newDistance < distances[neighborNode])
                {
                    distances[neighborNode] = newDistance;
                    previousNodes[neighborNode] = currentNode;
                    minHeap.Add(neighborNode, newDistance);
                }
            }
        }
        return distances;
    }
    static List<string> BFS(Graph graph, string start, string end)
    {
        var queue = new Queue<string>();
        var distances = new Dictionary<string, int>();
        var oncekiNode = new Dictionary<string, string>();
        var visited = new HashSet<string>(); //hash olarak

        queue.Enqueue(start);
        distances[start] = 0;
        visited.Add(start);

        while (queue.Count > 0)
        {
            var currentNode = queue.Dequeue();

            foreach (var komsu in graph.bitisikdugumler[currentNode])
            {
                if (!visited.Contains(komsu))
                {
                    queue.Enqueue(komsu);
                    visited.Add(komsu);
                    distances[komsu] = distances[currentNode] + 1;
                    oncekiNode[komsu] = currentNode;

                    if (komsu == end)
                    {
                        var path = new List<string>();
                        var pathNode = end;

                        while (pathNode != null)
                        {
                            path.Add(pathNode);
                            pathNode = oncekiNode.ContainsKey(pathNode) ? oncekiNode[pathNode] : null;
                        }

                        path.Reverse();
                        return path;
                    }
                }
            }
        }
        return null;
    }
    static void PrintPath(Dictionary<string, int> distances)
    {
        foreach (var kvp in distances)
        {
            Console.WriteLine($"dugum {kvp.Key}, mesafea: {kvp.Value}");
        }
    }
    static void PrintPath(List<string> path)
    {
        if (path != null)
        {
            foreach (var node in path)
            {
                Console.Write(node + " ");
            }
            Console.WriteLine();
        }
        else
        {
            Console.WriteLine("Yol bulunamadı.");
        }
    }
}