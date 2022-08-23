#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum color{branco, cinza, preto};
enum tipoDeVertice{entrada, saida, casa, superMercado, fonte, ralo, inexistente};

typedef struct Vertice
{
    enum color cor;

    int oX;
    int oY;

    enum tipoDeVertice tipo;

    struct Aresta **arestas;

    struct Vertice *predecessor;

    int arestaPredecessor;

    struct Aresta *ligacaoEspecial;
} vertice;

typedef struct Queue
{
    struct Vertice **filaDeVertices;
    int totalDeVerticesNafila;
    int posicaoNaFila;
} queue;

typedef struct Aresta
{
    int fluxo;
    struct Vertice *atual;
    struct Vertice *proximo;

} aresta;

vertice *criarVerticeFalso()
{
    vertice *falso = (vertice*)malloc(sizeof(vertice));
    falso->tipo = inexistente;

    return falso;
}

vertice** criarGrafo(int numDeAvenidas, int numDeRuas, vertice *falso)
{
    int i, j, k;
    vertice **grafo = (vertice **)malloc(numDeAvenidas * sizeof(vertice *));
    for(i = 0; i < numDeAvenidas; i++)
    {
        grafo[i] = (vertice *)malloc(numDeRuas*2 * sizeof(vertice));
        for(j=0; j<numDeRuas*2; j++)
        {
            if(j%2==0)
            {
                grafo[i][j].tipo = entrada;
            } else {
                grafo[i][j].tipo = saida;
            }
            grafo[i][j].oY = i;
            grafo[i][j].oX = j;
            grafo[i][j].arestas = (aresta**)malloc(5*sizeof(aresta));
            for(k = 0; k<5; k++)
            {
                grafo[i][j].arestas[k] = (aresta*)malloc(sizeof(aresta));
                grafo[i][j].arestas[k]->atual = &grafo[i][j];
                grafo[i][j].arestas[k]->proximo = falso;
                grafo[i][j].arestas[k]->fluxo = 0;
            }
        }
    }
    return grafo;
}

vertice* criarSink()
{
    vertice *sink = (vertice*)malloc(sizeof(vertice));

    sink->arestas = (aresta**)malloc(sizeof(aresta));
    sink->tipo = ralo;
    sink->oX = -2;
    sink->oY = -2;
    return sink;
}

vertice* criarSource(int numDePessoas, vertice *falso)
{
    int i;

    vertice *source = (vertice*)malloc(sizeof(vertice));
    source->arestas = (aresta**)malloc(numDePessoas*sizeof(aresta));
    for(i = 0; i<numDePessoas*2; i++)
    {
        source->arestas[i] = (aresta*)malloc(sizeof(aresta));
        source->arestas[i]->atual = source;
        source->arestas[i]->proximo = falso;
        source->arestas[i]->fluxo = 0;
    }
    source->oX = -1;
    source->oY = -1;
    source->tipo = fonte;

    return source;
}

int getMercados(int numDeMercados, vertice **manhatan, vertice* sink)
{
    int i;
    int avenida, rua;
    int contadorDeRepetidos = 0;

    for(i = 0; i < numDeMercados; i++)
    {
        if(scanf("%d %d", &avenida, &rua) != EOF)
        {
            if(manhatan[avenida-1][2*rua-1].tipo != superMercado)
            {
                manhatan[avenida-1][2*rua - 1].tipo = superMercado;
                manhatan[avenida-1][2*rua - 1].ligacaoEspecial = (aresta*)malloc(sizeof(aresta));
                manhatan[avenida-1][2*rua - 1].ligacaoEspecial->atual = &manhatan[avenida-1][2*rua - 1];
                manhatan[avenida-1][2*rua - 1].ligacaoEspecial->proximo = sink;
                manhatan[avenida-1][2*rua - 1].ligacaoEspecial->fluxo = 0;

            } else {
                contadorDeRepetidos++;
            }
        }
    }
    return contadorDeRepetidos;
}

int getPessoas(int numDePessoas, vertice **manhatan, vertice *source)
{
    int i;
    int avenida, rua;
    int contadorDeRepetidos = 0;

    for(i = 0; i < numDePessoas; i++)
    {
        if(scanf("%d %d", &avenida, &rua) != EOF)
        {
            if(manhatan[avenida-1][2*(rua-1)].tipo != casa)
            {
                manhatan[avenida-1][2*(rua-1)].tipo = casa;
                source->arestas[i-contadorDeRepetidos]->proximo = &manhatan[avenida-1][2*(rua-1)];
                source->arestas[i-contadorDeRepetidos]->proximo->arestaPredecessor = i-contadorDeRepetidos;

            } else {
                contadorDeRepetidos++;
            }
        }
    }
    return contadorDeRepetidos;
}

void conectarVertices(vertice **manhatan, int numDeAvenidas, int numDeRuas)
{
    int i, j;
    /*aresta[0] -> direita
      aresta[1] -> esquerda
      aresta[2] -> cima
      aresta[3] -> baixo
      aresta[4] -> auxiliar pra origem ou origem para auxiliar
      */
    for(i = 0; i<numDeAvenidas; i++)
    {
        for(j = 0; j<numDeRuas*2; j++)
        {

            if(j%2 != 0){
                if(j<numDeRuas*2-1)
                {
                    manhatan[i][j].arestas[0]->proximo = &manhatan[i][j+1];
                }
                if(j>1)
                {
                    manhatan[i][j].arestas[1]->proximo = &manhatan[i][j-3];
                }
                if(i>0)
                {
                    manhatan[i][j].arestas[2]->proximo = &manhatan[i-1][j-1];
                }
                if(i<numDeAvenidas-1)
                {
                    manhatan[i][j].arestas[3]->proximo = &manhatan[i+1][j-1];
                }
                if(j>0)
                {
                     manhatan[i][j].arestas[4]->proximo = &manhatan[i][j-1];
                }
            } else {
                if(j<numDeRuas*2-2)
                {
                    manhatan[i][j].arestas[0]->proximo = &manhatan[i][j+3];
                }
                if(j>1)
                {
                    manhatan[i][j].arestas[1]->proximo = &manhatan[i][j-1];
                }
                if(i>0)
                {
                    manhatan[i][j].arestas[2]->proximo = &manhatan[i-1][j+1];
                }
                if(i<numDeAvenidas-1)
                {
                    manhatan[i][j].arestas[3]->proximo = &manhatan[i+1][j+1];
                }
                if(j<numDeRuas*2 -1)
                {
                    manhatan[i][j].arestas[4]->proximo = &manhatan[i][j+1];
                }
            }
        }
    }
}

void displayVertex(int numDeAvenidas, int numDeRuas, vertice **manhatan, vertice *source, vertice *sink, int numDePessoas)
{
    int i, j, k;
    int aux1;
    for(i= 0; i<numDeAvenidas; i++)
    {
        for(j= 0; j<numDeRuas*2; j++)
        {
            aux1 = 0;

            for(k=0; k<5; k++)
            {
                if(manhatan[i][j].arestas[k]->proximo->tipo != inexistente)
                {
                    aux1++;
                }
            }
                printf("vertice: %d %d --- conectado com: %d\n", i, j, aux1);
        }
    }
}

int bfs(vertice *no, vertice *sink, queue *fila, int numDePessoas)
{
    int i;
    switch(no->tipo)
    {
        case inexistente:
            return 0;
            break;
        case ralo:
            return 1;
            break;

        case fonte:
            for(i=0; i<numDePessoas; i++)
            {
                if(no->arestas[i]->fluxo == 0)
                {
                    no->arestas[i]->proximo->arestaPredecessor = i;
                    no->arestas[i]->proximo->predecessor = no;
                    no->arestas[i]->proximo->cor = cinza;
                    fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                    fila->totalDeVerticesNafila++;
                }
            }
            break;

        case casa:
        case entrada:
            /*0 -> vai para direita
            1 -> esquerda
            2 -> cima
            3 -> baixo
            4 -> direita auxiliar*/
            for(i = 0; i<5; i++)
            {
                if(no->arestas[i]->proximo->tipo != inexistente)
                {
                    if(no->arestas[i]->proximo->cor == branco)
                    {
                        if(i<4)
                        {
                            if(no->arestas[i]->fluxo == -1)
                            {
                                no->arestas[i]->proximo->predecessor = no;
                                no->arestas[i]->proximo->cor = cinza;
                                no->arestas[i]->proximo->arestaPredecessor = i;
                                fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                                fila->totalDeVerticesNafila++;
                            }
                        } else {
                            if(no->arestas[i]->fluxo == 0)
                            {
                                /*printf("abobora\n");*/
                                no->arestas[i]->proximo->predecessor = no;
                                no->arestas[i]->proximo->cor = cinza;
                                no->arestas[i]->proximo->arestaPredecessor = i;
                                fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                                fila->totalDeVerticesNafila++;
                            }
                        }
                    }
                }
            }
            break;

        case saida:
            /*0 -> vai para direita(direita)
            1 -> esquerda sem ser a sua origem
            2 -> cima
            3 -> baixo
            4 -> esquerda origem*/
            for(i = 0; i<5; i++)
            {
                if(no->arestas[i]->proximo->tipo != inexistente)
                {
                    if(no->arestas[i]->proximo->cor == branco)
                    {
                        if(i<4)
                        {
                            if(no->arestas[i]->fluxo == 0)
                            {
                                no->arestas[i]->proximo->predecessor = no;
                                no->arestas[i]->proximo->cor = cinza;
                                no->arestas[i]->proximo->arestaPredecessor = i;
                                fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                                fila->totalDeVerticesNafila++;
                            }
                        } else {
                            if(no->arestas[i]->fluxo == -1)
                            {
                                no->arestas[i]->proximo->predecessor = no;
                                no->arestas[i]->proximo->cor = cinza;
                                no->arestas[i]->proximo->arestaPredecessor = i;
                                fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                                fila->totalDeVerticesNafila++;
                            }
                        }
                    }
                }
            }
            break;

        case superMercado:
            if(no->ligacaoEspecial->fluxo == 0)
            {
                /*printf("entrei no mercado %d %d\n\n", no->oY, no->oX);*/
                no->ligacaoEspecial->fluxo = 1;
                no->ligacaoEspecial->proximo->predecessor = no;
                return 1;
                /*o que fazer ao atingir sink*/
                break;
            } else {
                for(i=0; i<5; i++)
                {
                    if(no->arestas[i]->proximo->tipo == inexistente)
                    {
                        if(no->arestas[i]->proximo->cor == branco)
                        {
                            if(i<4)
                            {
                                if(no->arestas[i]->fluxo == 0)
                                {
                                    no->arestas[i]->proximo->predecessor = no;
                                    no->arestas[i]->proximo->cor = cinza;
                                    no->arestas[i]->proximo->arestaPredecessor = i;
                                    fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                                    fila->totalDeVerticesNafila++;
                                }
                            } else {
                                if(no->arestas[i]->fluxo == -1)
                                {
                                    no->arestas[i]->proximo->predecessor = no;
                                    no->arestas[i]->proximo->cor = cinza;
                                    no->arestas[i]->proximo->arestaPredecessor = i;
                                    fila->filaDeVertices[fila->totalDeVerticesNafila] = no->arestas[i]->proximo;
                                    fila->totalDeVerticesNafila++;
                                }
                            }
                        }
                    }
                }
                break;
            }
        default:
            break;
    }

    if(fila->posicaoNaFila < fila->totalDeVerticesNafila)
    {
        fila->posicaoNaFila++;
        return bfs(fila->filaDeVertices[fila->posicaoNaFila], sink, fila, numDePessoas);
    } else {
        return 0;
    }
}

void limparTudo(int numDeRuas, int numDeAvenidas, vertice **manhatan, queue *fila, vertice *falso)
{
    int i, j;

    for(i=0; i<numDeAvenidas; i++)
    {
        for(j = 0; j<numDeRuas*2; j++)
        {
            manhatan[i][j].cor = branco;
            manhatan[i][j].predecessor = NULL;
            manhatan[i][j].arestaPredecessor = -1;
        }
    }

    for(i=0; i<numDeAvenidas*numDeRuas*2; i++)
    {
        fila->filaDeVertices[i] = falso;
    }

    fila->posicaoNaFila = 0;
    fila->totalDeVerticesNafila = 1;
}

int edmondsKarp(vertice *source, vertice *sink, int numDePessoas, int totalDeVertices, int numDeRuas, int numDeAvenidas, vertice **manhatan, int numDeMercados, vertice *falso)
{

    int i;
    int flow = 0;
    int new_flow;
    vertice *aux;
    vertice *aux2;
    queue *fila = (queue*)malloc(sizeof(queue));
    fila->filaDeVertices = (vertice**)malloc(totalDeVertices*sizeof(vertice));
    for(i = 0; i<totalDeVertices; i++)
    {
        fila->filaDeVertices[i] = falso;
    }
    fila->posicaoNaFila = 0;
    fila->totalDeVerticesNafila = 1;
    while ((new_flow = bfs(source, sink, fila, numDePessoas)))
    {
        flow += new_flow;
        if(new_flow != numDePessoas && new_flow != numDeMercados)
        {
            aux = sink->predecessor;
            while (aux->tipo != source->tipo)
            {
                if(aux->tipo != casa)
                {
                    aux2 = aux->predecessor;
                    aux2->arestas[aux->arestaPredecessor]->fluxo += 1;
                    for(i = 0; i<5; i++)
                    {
                        if(aux->arestas[i]->proximo->tipo != inexistente)
                        {
                            if(aux->arestas[i]->proximo->oX == aux2->oX && aux->arestas[i]->proximo->oY == aux2->oY)
                            {
                                aux->arestas[i]->fluxo += -1;
                            }
                        }
                    }
                    aux = aux2;
                } else {
                    if(aux->predecessor->tipo == fonte)
                    {
                        source->arestas[aux->arestaPredecessor]->fluxo = 1;
                        aux = source;
                    } else {
                        aux2 = aux->predecessor;
                        aux2->arestas[aux->arestaPredecessor]->fluxo += 1;
                        for(i = 0; i<5; i++)
                        {
                            if(aux->arestas[i]->proximo->tipo != inexistente)
                            {
                                if(aux->arestas[i]->proximo->oX == aux2->oX && aux->arestas[i]->proximo->oY == aux2->oY)
                                {
                                    aux->arestas[i]->fluxo += -1;
                                }
                            }
                        }
                        aux = aux2;
                    }
                }
            }
        } else {
            return new_flow;
        }
        limparTudo(numDeRuas, numDeAvenidas, manhatan, fila, falso);
    }

    free(fila->filaDeVertices);
    free(fila);

    return flow;
}

void liberarTudo(vertice *falso, vertice **manhatan, vertice *sink, vertice *source, int numDeRuas, int numDeAvenidas, int numDePessoas)
{

    int i, j, k;

    free(falso);


    for(i = 0; i < numDeAvenidas; i++)
    {
        for(j=0; j<numDeRuas*2; j++)
        {
            for(k = 0; k<5; k++)
            {
                free(manhatan[i][j].arestas[k]);
            }
            free(manhatan[i][j].arestas);
            if(manhatan[i][j].tipo == superMercado)
            {
                free(manhatan[i][j].ligacaoEspecial);
            }
        }
        free(manhatan[i]);
    }

    free(manhatan);
    free(sink->arestas);
    free(sink);

    for(i = 0; i<numDePessoas*2; i++)
    {
        free(source->arestas[i]);
    }

    free(source->arestas);
    free(source);

}

void displayMatrix(vertice **manhatan, int numDeRuas, int numDeAvenidas)
{
    int i, j;
    for(i = 0; i<numDeAvenidas; i++)
    {
        for(j = 0; j<numDeRuas*2; j++)
        {
            if(j==numDeRuas*2-1)
            {
                printf("%d", manhatan[i][j].tipo);
            }else{
                printf("%d - ", manhatan[i][j].tipo);
            }
        }
        if(i!=numDeAvenidas-1){
                printf("\n");
            for(j = 0; j<numDeRuas*2; j++)
            {
                printf("|   ");
            }
        }
                printf("\n");
    }
    printf("\n\n");
}

int main(void) {

    int numDeAvenidas, numDeRuas, numDeMercados, numDePessoas;

    if(scanf("%d %d", &numDeAvenidas, &numDeRuas) != EOF)
    {
        if(scanf("%d %d", &numDeMercados, &numDePessoas) != EOF)
        {
            vertice *falso = criarVerticeFalso();
            vertice **manhatan = criarGrafo(numDeAvenidas, numDeRuas, falso);
            vertice *sink = criarSink();
            vertice *source = criarSource(numDePessoas, falso);
            numDeMercados -= getMercados(numDeMercados, manhatan, sink);
            numDePessoas -= getPessoas(numDePessoas, manhatan, source);
            conectarVertices(manhatan, numDeAvenidas, numDeRuas);
            printf("%d\n", edmondsKarp(source, sink, numDePessoas, numDeAvenidas*numDeRuas*2, numDeRuas, numDeAvenidas, manhatan, numDeMercados, falso));
            liberarTudo(falso, manhatan, sink, source, numDeRuas, numDeAvenidas, numDePessoas);
        }
    }

    return 0;
}
