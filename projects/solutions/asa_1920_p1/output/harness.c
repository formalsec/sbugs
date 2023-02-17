#include <stdlib.h>
#include <stdio.h>
#include <wasp.h>
typedef struct LstNode
{
  int val;
  int len;
  struct LstNode *next;
} *Lst;
void freeLst(Lst lst)
{
  if (lst != ((void *) 0))
  {
    freeLst(lst->next);
    free(lst);
  }
}

int getLength(Lst lst)
{
  if (lst == ((void *) 0))
    return 0;
  return lst->len;
}

Lst createLst(int i, Lst lst)
{
  Lst new_lst = (Lst) malloc(sizeof(struct LstNode));
  new_lst->val = i;
  new_lst->next = lst;
  new_lst->len = getLength(lst) + 1;
  return new_lst;
}

Lst addToFront(int i, Lst lst)
{
  return createLst(i, lst);
}

Lst emptyLst()
{
  return (void *) 0;
}

void printList(Lst lst)
{
  while (lst != ((void *) 0))
  {
    printf("%d, ", lst->val);
    lst = lst->next;
  }

  printf("\n");
}

typedef struct NodeStruct
{
  int id;
  int price;
  Lst nghbrs;
} *Node;
void freeNode(Node node)
{
  freeLst(node->nghbrs);
  free(node);
}

Node createNode(int id, int price, Lst nghbrs)
{
  Node nd = (Node) malloc(sizeof(struct NodeStruct));
  nd->id = id;
  nd->nghbrs = nghbrs;
  nd->price = price;
  return nd;
}

void printNode(Node n)
{
  printf("Node. id: %d. price: %d\n", n->id, n->price);
}

Node copyRawNode(Node n)
{
  return createNode(n->id, n->price, emptyLst());
}

void addNghbr(Node nd, int v)
{
  Lst lst = nd->nghbrs;
  nd->nghbrs = addToFront(v, lst);
}

typedef struct GraphStruct
{
  int n;
  int m;
  Node *nodes;
} *Graph;
void freeGraph(Graph g)
{
  Node *nodes = g->nodes;
  for (int i = 1; i <= g->n; i++)
  {
    Node node = nodes[i];
    freeNode(node);
  }

  free(nodes);
  free(g);
}

Graph createGraph(int n, int m, Node *nodes)
{
  Graph g = (Graph) malloc(sizeof(struct GraphStruct));
  g->n = n;
  g->m = m;
  g->nodes = nodes;
  return g;
}

void printGraph(Graph g)
{
  int n = g->n;
  for (int i = 1; i <= n; i++)
  {
    Node u = g->nodes[i];
    Lst nghbrs = u->nghbrs;
    printf("%d: ", u->id);
    while (nghbrs != ((void *) 0))
    {
      printf("%d, ", nghbrs->val);
      nghbrs = nghbrs->next;
    }

    printf("\n");
  }

}

Graph graphTranspose(Graph g)
{
  Node *nodes = g->nodes;
  int n = g->n;
  int m = g->m;
  Node *new_nodes = (Node *) malloc((sizeof(Node)) * (n + 1));
  for (int j = 1; j <= n; j++)
  {
    Node node = nodes[j];
    Node new_node = copyRawNode(node);
    new_nodes[j] = new_node;
  }

  for (int i = 1; i <= n; i++)
  {
    Node u = nodes[i];
    Lst nghbrs = u->nghbrs;
    while (nghbrs != ((void *) 0))
    {
      int v = nghbrs->val;
      addNghbr(new_nodes[v], u->id);
      nghbrs = nghbrs->next;
    }

  }

  return createGraph(n, m, new_nodes);
}

typedef struct DFSInfoStruct
{
  Graph g;
  int next_finish_time_index;
  int *dtimes;
  int *ftimes;
  int *visited;
  int *parents;
  int *finish_times;
  Lst *dfs_trees;
  int cur_dfs_tree;
} *DFSInfo;
void freeDFSInfo(DFSInfo dfsinfo)
{
  freeGraph(dfsinfo->g);
  free(dfsinfo->dtimes);
  free(dfsinfo->ftimes);
  free(dfsinfo->visited);
  free(dfsinfo->parents);
  free(dfsinfo->finish_times);
  for (int i = 0; i <= dfsinfo->cur_dfs_tree; i++)
  {
    Lst lst = dfsinfo->dfs_trees[i];
    freeLst(lst);
  }

  free(dfsinfo->dfs_trees);
  free(dfsinfo);
}

Lst getNghbrs(Graph g, int i)
{
  return g->nodes[i]->nghbrs;
}

DFSInfo createDFSInfo(Graph g)
{
  DFSInfo dfsinfo = (DFSInfo) malloc(sizeof(struct DFSInfoStruct));
  dfsinfo->g = g;
  int size = g->n + 1;
  int *dtimes = (int *) malloc((sizeof(int)) * size);
  int *ftimes = (int *) malloc((sizeof(int)) * size);
  int *visited = (int *) calloc(size, sizeof(int));
  int *parents = (int *) malloc((sizeof(int)) * size);
  int *finish_times = (int *) malloc((sizeof(int)) * g->n);
  Lst *dfs_trees = (Lst *) malloc((sizeof(Lst)) * g->n);
  dfsinfo->dtimes = dtimes;
  dfsinfo->ftimes = ftimes;
  dfsinfo->visited = visited;
  dfsinfo->parents = parents;
  dfsinfo->finish_times = finish_times;
  dfsinfo->next_finish_time_index = 0;
  dfsinfo->dfs_trees = dfs_trees;
  dfsinfo->cur_dfs_tree = -1;
  return dfsinfo;
}

void printDFSTrees(DFSInfo dfsinfo)
{
  int n = dfsinfo->cur_dfs_tree;
  Lst *dfs_trees = dfsinfo->dfs_trees;
  for (int i = 0; i <= n; i++)
  {
    Lst lst = dfs_trees[i];
    printList(lst);
  }

}

void addDFSTree(DFSInfo dfsinfo, int i)
{
  int cur_dfs_tree = dfsinfo->cur_dfs_tree;
  cur_dfs_tree++;
  dfsinfo->cur_dfs_tree = cur_dfs_tree;
  Lst lst = createLst(i, emptyLst());
  dfsinfo->dfs_trees[cur_dfs_tree] = lst;
}

void extendCurDFSTree(DFSInfo dfsinfo, int i)
{
  int cur_dfs_tree = dfsinfo->cur_dfs_tree;
  Lst lst = dfsinfo->dfs_trees[cur_dfs_tree];
  Lst lst_new = addToFront(i, lst);
  dfsinfo->dfs_trees[cur_dfs_tree] = lst_new;
}

void updateLastFinishTime(DFSInfo dfsinfo, int i)
{
  int next_finish_time_index = dfsinfo->next_finish_time_index;
  dfsinfo->finish_times[next_finish_time_index] = i;
  dfsinfo->next_finish_time_index = next_finish_time_index + 1;
}

void printDFSInfo(DFSInfo dfsinfo)
{
  int n = dfsinfo->g->n;
  int *dtimes = dfsinfo->dtimes;
  int *ftimes = dfsinfo->ftimes;
  int *finish_times = dfsinfo->finish_times;
  for (int i = 1; i <= n; i++)
  {
    printf("%d - dtime: %d, ftime: %d\n", i, dtimes[i], ftimes[i]);
  }

  printf("Nodes Ordered by Finish Times: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d, ", finish_times[i]);
  }

  printf("\n");
}

int visit(Graph g, DFSInfo dfsinfo, int i, int count)
{
  if (dfsinfo->visited[i])
  {
    printf("visit invoked on visted node!\n");
    return -1;
  }
  dfsinfo->visited[i] = 1;
  dfsinfo->dtimes[i] = count;
  count++;
  Lst nghbr = getNghbrs(g, i);
  while (nghbr != ((void *) 0))
  {
    int j = nghbr->val;
    if (!dfsinfo->visited[j])
    {
      extendCurDFSTree(dfsinfo, j);
      dfsinfo->parents[j] = i;
      count = visit(g, dfsinfo, j, count);
    }
    nghbr = nghbr->next;
  }

  dfsinfo->ftimes[i] = count;
  updateLastFinishTime(dfsinfo, i);
  count++;
  return count;
}

DFSInfo dfs(Graph g, int *search_order)
{
  DFSInfo dfsinfo = createDFSInfo(g);
  int n = g->n;
  int count = 1;
  if (search_order == ((void *) 0))
  {
    search_order = (int *) malloc((sizeof(int)) * n);
    for (int i = 0; i < n; i++)
    {
      search_order[i] = i + 1;
    }

  }
  for (int i = 0; i < n; i++)
  {
    int k = search_order[i];
    if (!dfsinfo->visited[k])
    {
      dfsinfo->parents[k] = -1;
      addDFSTree(dfsinfo, k);
      count = visit(g, dfsinfo, k, count);
    }
  }

  return dfsinfo;
}

typedef struct ParsedInfo
{
  int n;
  int m;
  int *estimates;
  int *friends;
} *PInfo;
void freePInfo(PInfo pinfo)
{
  free(pinfo->estimates);
  free(pinfo->friends);
  free(pinfo);
}

PInfo createPInfo(int n, int m, int *estimates, int *friends)
{
  PInfo info = (PInfo) malloc(sizeof(struct ParsedInfo));
  info->n = n;
  info->m = m;
  info->estimates = estimates;
  info->friends = friends;
  return info;
}

Graph PInfo2Graph(PInfo info)
{
  int n = info->n;
  int m = info->m;
  int *estimates = info->estimates;
  int *friends = info->friends;
  Node *nodes = (Node *) malloc((sizeof(Node)) * (n + 1));
  for (int i = 1; i <= n; i++)
  {
    int price = estimates[i];
    Node nd = createNode(i, price, emptyLst());
    nodes[i] = nd;
  }

  for (int i = 0; i < (2 * m); i += 2)
  {
    int u = friends[i];
    int v = friends[i + 1];
    addNghbr(nodes[u], v);
  }

  return createGraph(n, m, nodes);
}

void readLine(char **line, size_t *len, FILE *fptr, char *msg)
{
  if (getline(line, len, fptr) == (-1))
  {
    printf("%s", msg);
    return;
  }
}

PInfo parseInput()
{
  int n;
  int m;
  n = __WASP_symb_int("n");
  m = __WASP_symb_int("m");
  int *estimates = (int *) malloc((sizeof(int)) * (n + 1));
  for (int i = 0; i < n; i++)
  {
    int j;
    j = __WASP_symb_int("j");
    estimates[i + 1] = j;
  }

  int *friends = (int *) malloc(((sizeof(int)) * m) * 2);
  for (int i = 0; i < m; i++)
  {
    int j;
    int k;
    j = __WASP_symb_int("j");
    k = __WASP_symb_int("k");
    friends[i * 2] = j;
    friends[(i * 2) + 1] = k;
  }

  return createPInfo(n, m, estimates, friends);
}

int *reverseArray(int *arr, int size)
{
  int *new_arr = (int *) malloc((sizeof(int)) * size);
  int end = size - 1;
  for (int i = 0; i < size; i++)
  {
    new_arr[i] = arr[end - i];
  }

  return new_arr;
}

DFSInfo sccs(Graph g)
{
  DFSInfo dfsinfo = dfs(g, (void *) 0);
  Graph gt = graphTranspose(g);
  int *search_order = reverseArray(dfsinfo->finish_times, g->n);
  DFSInfo dfsinfot = dfs(gt, search_order);
  return dfsinfot;
}

typedef struct SCCGraphStruct
{
  int n;
  Graph g;
  int *mapping;
} *SCCGraph;
SCCGraph createSCCGraph(Graph g, int n, int *mapping)
{
  SCCGraph scc_g = (SCCGraph) malloc(sizeof(struct SCCGraphStruct));
  scc_g->g = g;
  scc_g->n = n;
  scc_g->mapping = mapping;
  return scc_g;
}

int findMaxPriceAndSetMapping(Graph g, Lst lst, int *mapping, int u)
{
  int price = -1;
  Node *nodes = g->nodes;
  while (lst != ((void *) 0))
  {
    int v = lst->val;
    int v_price = nodes[v]->price;
    price = (price < v_price) ? (v_price) : (price);
    mapping[v] = u;
    lst = lst->next;
  }

  return price;
}

SCCGraph DFSInfo2SCCGraph(DFSInfo dfsinfo, Graph g)
{
  Lst *dfs_trees = dfsinfo->dfs_trees;
  int scc_n = dfsinfo->cur_dfs_tree;
  int scc_m = 0;
  int n = g->n;
  int *mapping = (int *) malloc((sizeof(int)) * (n + 1));
  Node *scc_nodes = (Node *) malloc((sizeof(Node)) * (scc_n + 2));
  for (int i = 0; i <= scc_n; i++)
  {
    Lst lst = dfs_trees[i];
    int max_price = findMaxPriceAndSetMapping(g, lst, mapping, i + 1);
    Node scc_node = createNode(i + 1, max_price, emptyLst());
    scc_nodes[i + 1] = scc_node;
  }

  for (int i = 1; i <= n; i++)
  {
    Node u = g->nodes[i];
    int u_scc = mapping[u->id];
    Lst nghbrs = u->nghbrs;
    while (nghbrs != ((void *) 0))
    {
      int v = nghbrs->val;
      int v_scc = mapping[v];
      if (u_scc != v_scc)
      {
        Node scc_node = scc_nodes[u_scc];
        addNghbr(scc_node, v_scc);
        scc_m++;
      }
      nghbrs = nghbrs->next;
    }

  }

  Graph g2 = createGraph(scc_n, scc_m, scc_nodes);
  SCCGraph scc_g = createSCCGraph(g2, n, mapping);
  return scc_g;
}

void recomputePrices(Graph g)
{
  int n = g->n;
  Node *nodes = g->nodes;
  for (int i = n; i > 0; i--)
  {
    Node u = nodes[i];
    Lst nghbrs = u->nghbrs;
    int max_u = u->price;
    while (nghbrs != ((void *) 0))
    {
      int v_price = nodes[nghbrs->val]->price;
      max_u = (v_price > max_u) ? (v_price) : (max_u);
      nghbrs = nghbrs->next;
    }

    u->price = max_u;
  }

}

void printNewPrices(SCCGraph scc_g)
{
  int n = scc_g->n;
  int *mapping = scc_g->mapping;
  Graph g = scc_g->g;
  Node *nodes = g->nodes;
  for (int i = 1; i <= n; i++)
  {
    int i_price = nodes[mapping[i]]->price;
    printf("%d\n", i_price);
  }

}

int main()
{
  PInfo pinfo = parseInput();
  Graph g = PInfo2Graph(pinfo);
  DFSInfo dfsinfo = dfs(g, (void *) 0);
  DFSInfo dfsinfo_scc = sccs(g);
  SCCGraph g_scc = DFSInfo2SCCGraph(dfsinfo_scc, g);
  recomputePrices(g_scc->g);
  printNewPrices(g_scc);
  return 0;
}
