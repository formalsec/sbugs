#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum color {WHITE, BLACK} Color;

typedef struct amigo {
    int amigo;
    struct amigo *next;
} Amigo;

typedef struct scc {
    int low;
    int nota;
} SCComponents;

typedef struct aluno {
    Color color;
    int _nota;
    int d;
    int low;
    Amigo *lista;
    SCComponents *scc;
} Aluno;

typedef struct stack {
    int i;
    struct stack *next;
} Stack;

typedef struct node {
    SCComponents *scc;
    struct node *next;
} Node;

/* Esta funcao e' responsavrel por inserir b na lista de amigos de a */
void amigo(Aluno *alunos, int a, int b) {
    Amigo *plista = alunos[a-1].lista;
    Amigo *new = NULL;
    if (plista->amigo == 0) {
        plista->amigo = b;
        return;
    }
    new = (Amigo*)can_fail_malloc(sizeof(Amigo));
    new->amigo = b;
    new->next = plista;
    alunos[a-1].lista = new;
}

/*-------------------------------------------------------------------
Esta funcao deve percorrer recursivamente os vertices que ainda nao
foram visitados e atualizar a sua nota caso um dos vertices vizinhos
tenha uma nota mais alta que o vertice atual
------------------------------------------------------------------*/
void dfs_visit(Aluno *alunos, int i) {
    Amigo *plista = alunos[i].lista;
    alunos[i].color = BLACK;
    while (plista != NULL && plista->amigo != 0) {
        if (alunos[plista->amigo-1].color == WHITE) {
            dfs_visit(alunos, plista->amigo-1);
        }
        if (alunos[plista->amigo-1]._nota > alunos[i]._nota) {
            alunos[i]._nota = alunos[plista->amigo-1]._nota;
        }
        plista = plista->next;
    }
    return;
}

/*------------------------------------------------------------------
Esta funcao e' responsavel por marcar todos os vertices do grafos
a branco, ou seja, como unvisited e chamar a funcao dfs_visit
------------------------------------------------------------------*/
void dfs(Aluno *alunos, int n) {
    int i;
    for (i = 0; i < n; i++) {
        alunos[i].color = WHITE;
    }
    for (i = 0; i < n; i++) {
        if (alunos[i].color == WHITE)
            dfs_visit(alunos, i);
    }
}

/* Esta funcao devolve o conteudo no topo da stack */
int top(Stack *stack) {
    return stack->i;
} 

/* Esta funcoa deve remover o item no topo da stack */
Stack *pop(Stack *stack) {
    Stack *top = stack->next;
    free(stack);
    return top;
}

/* Esta funcao deve adicionar o vertice de indice i ao topo da stack */
Stack *push(Stack *stack, int i) {
    Stack *top = (Stack*)can_fail_malloc(sizeof(Stack));
    top->i = i;
    top->next = stack;
    return top;
}

/*----------------------------------------------------------------
Funcao responsavel por criar uma nova scc e adiciona-la 
a lista de sccs
------------------------------------------------------------------*/
void addSCC(Node *sccs, SCComponents *newSCC) {
    Node *new = NULL;
    if (sccs->scc == NULL){
        sccs->scc = newSCC;
        return;
    }
    new = (Node*)can_fail_malloc(sizeof(Node));
    sccs->next = new;
    new->scc = newSCC;
    new->next = NULL;
}

/*------------------------------------------------------------------
Funcao responsavel por encontrar as SCCs de um grafo, segundo o
algoritmo de Tarjan
------------------------------------------------------------------*/
Stack *SCCUtil(int i, Aluno *alunos, Stack *stack, int *stackMember, Node *sccs) {
    static int time = 0;
    int w;

    Amigo *plista = alunos[i].lista;
    alunos[i].d = ++time;
    alunos[i].low = time;
    stack = push(stack, i);
    stackMember[i] = 1;

    while (plista != NULL && plista->amigo != 0) {
        if (alunos[plista->amigo-1].d == 0) {
            stack = SCCUtil(plista->amigo-1, alunos, stack, stackMember, sccs);
            alunos[i].low = alunos[i].low < alunos[plista->amigo-1].low ? alunos[i].low : alunos[plista->amigo-1].low;
        }
        else if (stackMember[plista->amigo-1] == 1) {
            alunos[i].low = alunos[i].low < alunos[plista->amigo-1].d ? alunos[i].low : alunos[plista->amigo-1].d;
        }
        plista = plista->next;
    }

    w = 0;
    if (alunos[i].low == alunos[i].d) {
        SCComponents *newSCC = (SCComponents*)can_fail_malloc(sizeof(SCComponents));
        newSCC->low = alunos[i].low;
        newSCC->nota = 0;
        addSCC(sccs, newSCC);
        while (top(stack) != i) {
            w = top(stack);
            alunos[w].scc = newSCC;
            stackMember[w] = 0;
            stack = pop(stack);
        }
        w = top(stack);
        alunos[w].scc = newSCC;
        stackMember[w] = 0;
        stack = pop(stack);
    }
    return stack;
    
}

/*------------------------------------------------------------------
Funcao responsavel por inicializar a stack e os valores de 
descoberta e de low de cada vertice
------------------------------------------------------------------*/
void SCC(Aluno *alunos, int N, Node *sccs) {
    int i;
    int *stackMember = (int*)can_fail_malloc(sizeof(int)*N);
    Stack *stack = (Stack*)can_fail_malloc(sizeof(Stack));
    stack->next = NULL;
    stack->i = -1;

    for (i = 0; i < N; i++) {
        alunos[i].d = 0;
        alunos[i].low = 0;
        stackMember[i] = 0;
    }

    for (i = 0; i < N; i++) {
        if (alunos[i].d == 0) {
            stack = SCCUtil(i, alunos, stack, stackMember, sccs);
        }
    }

    free (stack);
    free(stackMember);
}

/*------------------------------------------------------------------
Funcao responsavel por libertar a memoria alocada pelos 
alunos e sccs 
------------------------------------------------------------------*/
void delete(Aluno *alunos, int n, Node *sccs) {
    int i;
    Node *aux = NULL;
    for (i = 0; i < n; i++) {
        Amigo *plista = alunos[i].lista;
        while (plista != NULL) {
            alunos[i].lista = plista->next;
            free(plista);
            plista = alunos[i].lista;
        }
    }
    while (sccs != NULL) {
        aux = sccs->next;
        free(sccs->scc);
        free(sccs);
        sccs = aux;
    }
    free(alunos);
}

int main() {
    int N, M, nota, i = 0, a, b;
    Aluno *alunos;
    Node *sccs = (Node*)can_fail_malloc(sizeof(Node));
    sccs->scc = NULL;
    sccs->next = NULL;

    scanf("%d", &N);
    getchar(); /* eats the comma */
    scanf("%d", &M);
    alunos = (Aluno*)can_fail_malloc(sizeof(Aluno)*N);

    /* Atribui uma nota a cada aluno e inicializa a lista de amigos */
    while (i < N) {
        scanf("%d", &nota);
        alunos[i]._nota = nota;
        alunos[i].lista = (Amigo*)can_fail_malloc(sizeof(Amigo));
        alunos[i].lista->amigo = 0;
        alunos[i].lista->next = NULL;
        i++;
    }

    /* Preenche as listas de amigos */
    for (i = 0; i < M; i++) {
        scanf("%d", &a);
        scanf("%d", &b);
        amigo(alunos, a, b);
    }

    SCC(alunos, N, sccs);
    dfs(alunos, N);

    /* Atribui uma nota maxima a cada scc */
    for (i = 0; i < N; i++) {
        if (alunos[i].scc->nota < alunos[i]._nota) {
            alunos[i].scc->nota = alunos[i]._nota;
        }
    }

    /* Atualiza a nota dos alunos consoante a scc a que pertencem */
    for (i = 0; i < N; i++) {
        if (alunos[i]._nota < alunos[i].scc->nota) {
            alunos[i]._nota = alunos[i].scc->nota;
        }
    }

    /* Imprime o output */
    for (i = 0; i < N; i++) {
        printf("%d\n", alunos[i]._nota);
    }

    delete(alunos, N, sccs);
    return 0;
}