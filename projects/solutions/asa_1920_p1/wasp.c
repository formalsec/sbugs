#include <stdlib.h>
#include <stdio.h>
#include <wasp.h>

typedef struct LstNode { 
   int val; 
   int len; 
   struct LstNode* next; 
} *Lst; 

void freeLst(Lst lst) { 
   if (lst != NULL) {
      freeLst (lst->next);
      free (lst);
   }
}

int getLength (Lst lst) { 
   if(lst == NULL) return 0; 
   return lst->len; 
}

Lst createLst (int i, Lst lst) { 
   Lst new_lst = (Lst)malloc(sizeof(struct LstNode)); 
   new_lst->val = i; 
   new_lst->next = lst;
   new_lst->len = getLength(lst)+1;  
   return new_lst; 
}

Lst addToFront (int i, Lst lst) { 
  return createLst(i, lst); 
}

Lst emptyLst() { 
   return NULL; 
}

void printList(Lst lst) {
   while(lst != NULL) {
      printf("%d, ", lst->val); 
      lst = lst->next; 
   }
   printf("\n"); 
}


typedef struct NodeStruct { 
   int id; 
   int price; 
   Lst nghbrs; 
} *Node; 

void freeNode(Node node) {
   freeLst(node->nghbrs); 
   free (node);
}

Node createNode (int id, int price, Lst nghbrs) { 
   Node nd = (Node)malloc(sizeof(struct NodeStruct));
   nd->id = id;
   nd->nghbrs = nghbrs; 
   nd->price = price; 
   return nd; 
}

void  printNode(Node n) {
   printf("Node. id: %d. price: %d\n", n->id, n->price); 
}

Node copyRawNode (Node n) {
   return createNode (n->id, n->price, emptyLst());  
}

void addNghbr(Node nd, int v) {
   Lst lst = nd->nghbrs; 
   nd->nghbrs = addToFront(v, lst);
}

typedef struct GraphStruct {
   int n; 
   int m; 
   Node* nodes; 
} *Graph; 

void freeGraph(Graph g) {
   Node* nodes = g->nodes; 
   for (int i=1; i<=(g->n); i++) {  
      Node node = nodes[i]; 
      freeNode(node); 
   }
   free(nodes); 
   free(g);
}

Graph createGraph(int n, int m, Node* nodes) {
   Graph g = (Graph)malloc(sizeof(struct GraphStruct)); 
   g->n = n;
   g->m = m; 
   g->nodes = nodes; 
   return g;  
}

void printGraph(Graph g) { 
   int n = g->n; 
   for (int i=1; i<= n; i++) { 
      Node u = g->nodes[i];
      Lst nghbrs = u->nghbrs; 
      printf("%d: ", u->id);
      while (nghbrs != NULL) { 
         printf("%d, ", nghbrs->val); 
         nghbrs = nghbrs->next; 
      } 
      printf("\n"); 
   }
}

Graph graphTranspose(Graph g) { 
   Node* nodes = g->nodes; 
   int n = g->n; 
   int m = g->m; 
   Node* new_nodes = (Node*)malloc(sizeof(Node)*(n+1)); 
   for (int j=1; j<=n; j++) { 
      Node node = nodes[j]; 
      Node new_node = copyRawNode(node);
      //printNode(node); 
      new_nodes[j] = new_node; 
     
   }
   
   for (int i=1; i<=n; i++) { 
      Node u = nodes[i]; 
      Lst nghbrs = u->nghbrs; 
      while (nghbrs != NULL) { 
         int v = nghbrs->val; 
         addNghbr(new_nodes[v], u->id); 
         nghbrs = nghbrs->next; 
      }      
   }
   
   return createGraph(n, m, new_nodes); 
}

typedef struct DFSInfoStruct { 
   Graph g; 
   int next_finish_time_index; 
   int* dtimes; 
   int* ftimes; 
   int* visited; 
   int* parents; 
   int* finish_times; // a vector with the nodes ordered by finish time - very bad name 
   Lst* dfs_trees;    // an array with lists of nodes - each list contains the nodes in one DFS tree 
   int cur_dfs_tree;  // index of the last added dfs_tree  
} *DFSInfo; 

void freeDFSInfo(DFSInfo dfsinfo) { 
   freeGraph(dfsinfo->g);
   free (dfsinfo->dtimes);
   free (dfsinfo->ftimes); 
   free (dfsinfo->visited); 
   free (dfsinfo->parents); 
   free (dfsinfo->finish_times); 
   for (int i=0; i<=dfsinfo->cur_dfs_tree; i++) { 
      Lst lst = dfsinfo->dfs_trees[i];
      freeLst(lst);     
   }
   free (dfsinfo->dfs_trees); 
   free (dfsinfo); 
}

Lst getNghbrs(Graph g, int i) { 
   return (g->nodes[i])->nghbrs; 
}

DFSInfo createDFSInfo (Graph g) { 
   DFSInfo dfsinfo   = (DFSInfo) malloc(sizeof (struct DFSInfoStruct)); 
   dfsinfo->g        = g; 
   int size          = (g->n)+1; 
   int* dtimes       = (int*)malloc(sizeof(int)*size); 
   int* ftimes       = (int*)malloc(sizeof(int)*size); 
   int* visited      = (int*)calloc(size, sizeof(int)); 
   int* parents      = (int*)malloc(sizeof(int)*size); 
   int* finish_times = (int*)malloc(sizeof(int)*(g->n));
   Lst* dfs_trees    = (Lst*)malloc(sizeof(Lst)*(g->n));
   dfsinfo->dtimes   = dtimes; 
   dfsinfo->ftimes   = ftimes; 
   dfsinfo->visited  = visited; 
   dfsinfo->parents  = parents; 
   //
   dfsinfo->finish_times           = finish_times; 
   dfsinfo->next_finish_time_index = 0;
   dfsinfo->dfs_trees              = dfs_trees; 
   dfsinfo->cur_dfs_tree           = -1; 
   return dfsinfo; 
}

void printDFSTrees(DFSInfo dfsinfo) {
   int n = dfsinfo->cur_dfs_tree;
   Lst* dfs_trees = dfsinfo->dfs_trees; 
   for (int i=0; i<=n; i++) {
      Lst lst = dfs_trees[i]; 
      printList(lst); 
   }
}

void addDFSTree (DFSInfo dfsinfo, int i) { 
   int cur_dfs_tree = dfsinfo->cur_dfs_tree; 
   cur_dfs_tree++; 
   dfsinfo->cur_dfs_tree = cur_dfs_tree; 
   Lst lst = createLst (i, emptyLst());
   dfsinfo->dfs_trees[cur_dfs_tree] = lst; 
}

void extendCurDFSTree(DFSInfo dfsinfo, int i) { 
   int cur_dfs_tree = dfsinfo->cur_dfs_tree; 
   Lst lst = dfsinfo->dfs_trees[cur_dfs_tree]; 
   Lst lst_new = addToFront(i, lst); 
   dfsinfo->dfs_trees[cur_dfs_tree] = lst_new; 
}

void updateLastFinishTime (DFSInfo dfsinfo, int i) {
   int next_finish_time_index = dfsinfo->next_finish_time_index; 
   dfsinfo->finish_times[next_finish_time_index] = i;
   dfsinfo->next_finish_time_index = next_finish_time_index+1; 
}

void printDFSInfo(DFSInfo dfsinfo) {
   int n = (dfsinfo->g)->n; 
   int* dtimes = (dfsinfo->dtimes); 
   int* ftimes = (dfsinfo->ftimes); 
   int* finish_times = (dfsinfo->finish_times); 
   //printf("DFSInfo\n"); 
   for(int i=1; i<=n; i++) { 
      printf("%d - dtime: %d, ftime: %d\n", i, dtimes[i], ftimes[i]);
   }
   printf("Nodes Ordered by Finish Times: "); 
   for (int i=0; i<n; i++) { 
      printf ("%d, ", finish_times[i]); 
   }
   printf("\n");
}

int visit(Graph g, DFSInfo dfsinfo, int i, int count) {
   if (dfsinfo->visited[i]) {
      printf("visit invoked on visted node!\n");
      return -1;
   } 
   dfsinfo->visited[i] = 1; 
   dfsinfo->dtimes[i] = count; 
   count++; 
   
   Lst nghbr = getNghbrs(g, i);
   //printf("visiting %d\n", i); 
   while(nghbr != NULL) {
      int j = nghbr->val; 
      //printf("visiting %d - %d\n", i, j); 
      if (!dfsinfo->visited[j]) {
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

DFSInfo dfs(Graph g, int* search_order) { 
   DFSInfo dfsinfo = createDFSInfo(g);
   int n = g->n; 
   int count = 1; 
   
   if (search_order == NULL) {
     search_order = (int*)malloc(sizeof(int)*n); 
     for(int i=0; i<n; i++) {
        search_order[i] = i+1; 
     }
   }

   for (int i = 0; i<n; i++) { 
      int k = search_order[i]; 
      //printf("visiting %d\n", k); 
      if (!dfsinfo->visited[k]) {
         dfsinfo->parents[k] = -1;
         addDFSTree(dfsinfo, k); 
         count = visit(g, dfsinfo, k, count); 
      }
   }
   return dfsinfo; 
}


typedef struct ParsedInfo {
   int n;
   int m;
   int* estimates; 
   int* friends;
} *PInfo;

void freePInfo(PInfo pinfo) { 
   free (pinfo->estimates);
   free (pinfo->friends); 
   free (pinfo); 
}

PInfo createPInfo (int n, int m, int* estimates, int* friends) { 
   PInfo info = (PInfo)malloc(sizeof(struct ParsedInfo)); 
   info->n = n; 
   info->m = m; 
   info->estimates = estimates; 
   info->friends = friends; 
   return info; 
}

Graph PInfo2Graph (PInfo info) { 
   int n = info->n; 
   int m = info->m; 
   int* estimates = info->estimates; 
   int* friends = info->friends; 
   
   Node* nodes = (Node*)malloc(sizeof(Node)*(n+1)); 
   for (int i=1; i<=n; i++) {
      int price = estimates[i];
      Node nd = createNode (i, price, emptyLst()); 
      nodes[i] = nd; 
   }
   
   //printf("created the nodes. n: %d. m:%d\n", n, m); 
   
   for (int i=0; i<2*m; i+=2) { 
      //printf("%d: (%d, %d)\n", i, friends[i], friends[i+1]);
      int u = friends[i]; 
      int v = friends[i+1]; 
      addNghbr(nodes[u], v); 
   }

   return createGraph(n, m, nodes);  
}

void readLine (char** line, size_t* len, FILE* fptr, char* msg) { 
   if (getline(line, len, fptr) == -1) { 
      printf("%s", msg); 
      return;
   }
}

PInfo parseInput () { 
   /*FILE *fptr;
   char* msg = "Illegal File Format\n"; 
   if ((fptr = fopen(fname, "r")) == NULL) {
      printf("Error! opening file");
      exit(1);
   }*/

   // Read lines using POSIX function getline
   // This code won't work on Windows
   //char *line = NULL;
   //size_t len = 0;
   
   // Read first line 
   int n, m;    
   //readLine(&line, &len, fptr, msg); 
   //scanf(line, "%d,%d\n", &n, &m); 
   n = __WASP_symb_int("n");
   m = __WASP_symb_int("m");

   // Read the estimate of each student 
   int* estimates = (int*)malloc(sizeof(int)*(n+1)); 
   for (int i = 0; i<n; i++) {
     int j; 
     //readLine(&line, &len, fptr, msg); 
     //sscanf(line, "%d\n", &j);
     j = __WASP_symb_int("j");
     estimates[i+1] = j; 
     //printf("Li: %d\n", j); 
   }

   // Read the friendship relationships 
   int* friends = (int*)malloc(sizeof(int)*m*2); 
   for (int i = 0; i < m; i++) {
     int j, k; 
     //readLine(&line, &len, fptr, msg); 
     //sscanf(line, "%d %d\n", &j, &k);
     j = __WASP_symb_int("j");
     k = __WASP_symb_int("k");
     friends[i*2] = j; 
     friends[i*2+1] = k;
     //printf("Li %d, %d: %d, %d\n", i*2, i*2+1, j, k); 
   }
  
   //fclose(fptr);
   //free(line);  
   return createPInfo(n, m, estimates, friends); 
}


int* reverseArray(int* arr, int size) { 
   int* new_arr = (int*)malloc(sizeof(int)*size);
   int end = size-1; 
   for(int i=0; i<size; i++) {
      new_arr[i] = arr[end-i]; 
   }
   return new_arr;
}

DFSInfo sccs(Graph g) { 
   DFSInfo dfsinfo = dfs(g, NULL);
   //printf("first DFS done!\n");
   //printGraph(g); 
   Graph gt = graphTranspose(g);
   //printf("transpose done!\n"); 
   //printGraph(gt); 
   int* search_order = reverseArray(dfsinfo->finish_times, g->n); 
   //printf("reverse of finish times done!\n"); 
   DFSInfo dfsinfot = dfs(gt, search_order); 
   //printf("second dfs done!\n"); 
   return dfsinfot; 
}

typedef struct SCCGraphStruct {
   int n;
   Graph g;  
   int* mapping; 
} *SCCGraph;

SCCGraph createSCCGraph(Graph g, int n, int* mapping) {
   SCCGraph scc_g = (SCCGraph)malloc(sizeof(struct SCCGraphStruct)); 
   scc_g->g = g; 
   scc_g->n = n; 
   scc_g->mapping = mapping; 
   return scc_g; 
}

int findMaxPriceAndSetMapping(Graph g, Lst lst, int* mapping, int u) {
   int price = -1; 
   Node* nodes = g->nodes; 
   while (lst != NULL) { 
      int v = lst->val; 
      int v_price = nodes[v]->price; 
      price = (price < v_price) ? v_price : price; 
      mapping[v] = u; 
      lst = lst->next; 
   }
   return price; 
}

SCCGraph DFSInfo2SCCGraph(DFSInfo dfsinfo, Graph g) {
   //
   Lst* dfs_trees  = dfsinfo->dfs_trees;
   int scc_n       = dfsinfo->cur_dfs_tree; 
   int scc_m       = 0; 
   int n           = g->n; 
   int* mapping    = (int*)malloc(sizeof(int)*(n+1)); 
   Node* scc_nodes = (Node*)malloc(sizeof(Node)*(scc_n+2));

   //printf("Going to create the nodes of the scc graph. scc_n: %d\n", scc_n); 
   for (int i=0; i<=scc_n; i++) {
      Lst lst = dfs_trees[i]; 
      int max_price = findMaxPriceAndSetMapping(g, lst, mapping, (i+1)); 
      Node scc_node = createNode ((i+1), max_price, emptyLst()); 
      scc_nodes[i+1] = scc_node; 
   }

   //printf("Going to create the edges of the scc graph\n"); 
   for (int i=1; i<= n; i++) { 
      Node u     = g->nodes[i]; 
      int u_scc  = mapping[u->id]; 
      Lst nghbrs = u->nghbrs; 
      while (nghbrs != NULL) { 
         int v     = nghbrs->val;
         int v_scc = mapping[v];
         //printf("i: %d, u: %d, v: %d, u_scc: %d, v_cc: %d\n", i, u->id, v, u_scc, v_scc);
         if (u_scc != v_scc) {
            Node scc_node = scc_nodes[u_scc]; 
            //printNode(scc_node); 
            addNghbr(scc_node, v_scc);
            scc_m++;
         }
         nghbrs = nghbrs->next; 
      }
   }

   //printf("Created the edges of the scc graph\n"); 
   Graph g2 = createGraph(scc_n, scc_m, scc_nodes);
   SCCGraph scc_g = createSCCGraph(g2, n, mapping); 
   return scc_g; 
}

void recomputePrices (Graph g) {
   int n = g->n;
   Node* nodes = g->nodes;  
   for (int i=n; i>0; i--) { 
      Node u = nodes[i]; 
      Lst nghbrs = u->nghbrs;
      int max_u = u->price;  
      while (nghbrs != NULL) { 
         int v_price = nodes[nghbrs->val]->price;
         max_u = (v_price > max_u) ? v_price : max_u; 
         nghbrs = nghbrs->next; 
      }
      u->price = max_u; 
   }
}

void printNewPrices(SCCGraph scc_g) { 
   int n        = scc_g->n; 
   int* mapping = scc_g->mapping; 
   Graph g      = scc_g->g;
   Node* nodes  = g->nodes; 
   for (int i=1; i<=n; i++) { 
      int i_price = nodes[mapping[i]]->price; 
      printf("%d\n", i_price); 
   }
}

int main() {
   /*if (argc < 2) { 
     printf ("Wrong Number of Arguments!\n");
     exit(1);  
   }*/

   //PInfo pinfo = parseInput(argv[1]);   
  PInfo pinfo = parseInput();    
   Graph g = PInfo2Graph(pinfo); 
   DFSInfo dfsinfo = dfs(g, NULL); 
   //printDFSInfo(dfsinfo); 
   DFSInfo dfsinfo_scc = sccs(g); 
   //printDFSTrees(dfsinfo_scc); 
   SCCGraph g_scc = DFSInfo2SCCGraph(dfsinfo_scc, g); 
   //printf("printing the scc graph!\n");
   //printGraph(g_scc->g); 
   recomputePrices(g_scc->g); 
   printNewPrices(g_scc); 
   return 0;
}
