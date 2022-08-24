#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>

/* Represents a vertice of the graph. */
struct vert
{
    int indeg;    /* Indegree of the vertex. */
    int p1, p2;   /* Parent 1 and parent 2 of the vertex. */
    int found[3]; /* Flag for checking if the DFS has visited the vertex. */
    int exit;     /* Flag for checking if the DFS has exited the vertex. */
};

/* Used to detect loops. */
int dfs_loop(struct vert* graph, int v)
{
    int ret = 0;

    if (graph[v].found[0] == 1)
        return graph[v].exit == 0;
    graph[v].found[0] = 1;

    if (graph[v].p1 != 0)
        ret |= dfs_loop(graph, graph[v].p1);
    if (graph[v].p2 != 0)
        ret |= dfs_loop(graph, graph[v].p2);

    graph[v].exit = 1;
    return ret;
}

/* Used to mark the vertices that are reachable from the both input vertices. */
void dfs_mark(struct vert* graph, int v, int i)
{
    if (graph[v].found[i] == 1)
        return;
    graph[v].found[i] = 1;

    if (graph[v].p1 != 0)
        dfs_mark(graph, graph[v].p1, i);
    if (graph[v].p2 != 0)
        dfs_mark(graph, graph[v].p2, i);
}

int main(int argc, char** argv)
{
    int v1, v2, n, m, i, e1, e2, count;
    struct vert* graph;

    /* Read the input. */
    if (scanf("%d %d %d %d", &v1, &v2, &n, &m) != 4)
        return 1;

    /* Allocate memory for the graph. */
    graph = (struct vert*)malloc(sizeof(struct vert) * (n + 1));
    memset(graph, 0, sizeof(struct vert) * (n + 1));

    /* Read the edges. */
    for (; m > 0; m--)
    {
        if (scanf("%d %d", &e1, &e2) != 2) {
            /* Missing edges. */
            printf("0\n");
            return 0;
        }

        graph[e1].indeg += 1;
        if (graph[e2].p1 == 0)
            graph[e2].p1 = e1;
        else if (graph[e2].p2 == 0)
            graph[e2].p2 = e1;
        else
        {
            /* The graph doesn't form a valid family tree. */
            printf("0\n");
            return 0;
        }
    }

    /* Check if the graph is acyclic. */
    for (i = 1; i <= n; i++)
        if (dfs_loop(graph, i))
        {
            /* The graph doesn't form a valid family tree. */
            printf("0\n");
            return 0;
        }

    /* Mark the vertices that are reachable from both v1 and v2. */
    dfs_mark(graph, v1, 1);
    dfs_mark(graph, v2, 2);

    /* Remove non-reachable edges. */
    for (i = 1; i <= n; i++)
        if (graph[i].found[1] == 0 || graph[i].found[2] == 0)
        {
            if (graph[i].p1 != 0)
                graph[graph[i].p1].indeg -= 1;
            if (graph[i].p2 != 0)
                graph[graph[i].p2].indeg -= 1;
        }

    /* Find vertices that are reachable from both v1 and v2 and have no
     * incoming edges. */
    count = 0;
    for (i = 1; i <= n; i++)
        if (graph[i].found[1] == 1 && graph[i].found[2] == 1 && graph[i].indeg == 0)
        {
            printf("%d ", i);
            count += 1;
        }

    if (count == 0)
        putchar('-');
    putchar('\n');

    /* Free the allocated memory. */
    free(graph);

    return 0;
}
