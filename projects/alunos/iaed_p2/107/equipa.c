#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "equipa.h"

/*Recebe um nome e calcula a sua posicao numa tabela de dispersao retornando-a*/
int hash(char nome[]){
    int h, a = 31415, b = 27183;
for (h = 0; *nome != '\0'; nome++, a = a*b % (MAX_TABELA-1))
    h = (a*h + *nome) % MAX_TABELA;
return h;
}

/*Recebe um nome e cria a equipa correspondente. Retorna um ponteiro
para a equipa criada*/
no_equipa *cria_equipa(char nome[]){
    no_equipa *novo = can_fail_malloc(sizeof(no_equipa));
    novo->proximo = NULL;
    novo->equipa_do_no.nome = can_fail_malloc((strlen(nome)+1)*sizeof(char));
    strcpy(novo->equipa_do_no.nome,nome);
    novo->equipa_do_no.vitorias = 0;
    return novo;
}

/*Recebe um nome e adiciona a equipa correspondente
ao input a lista de equipas*/
void adiciona_equipa(no_equipa *tabela_equipas[],char nome[],int *numero_equipas){
    no_equipa *novo = cria_equipa(nome);
    int pos = hash(nome);
    if(!tabela_equipas[pos]){
        tabela_equipas[pos] = novo;
    }
    else
    {
        novo->proximo = tabela_equipas[pos];
        tabela_equipas[pos] = novo;
    }
    (*numero_equipas)++;
}

/*Recebe o nome de uma equipa e procura-o na lista de equipas, retornando um ponteiro
para esta caso exista. Retorna um ponteiro nullo caso contrario*/
equipa *procura_equipa_lista(no_equipa *tabela_equipas[],char nome[]){
    no_equipa *i;
    equipa *res = NULL;
    int pos = hash(nome);
    /*acesso a table e procura na lista ligada*/
    for(i = tabela_equipas[pos];i;i=i->proximo){
        if(!strcmp(i->equipa_do_no.nome,nome)){
            res = &(i->equipa_do_no);
            return res;
        }
    }
    return res;
}

/*Recebe um nome de uma equipa e uma chave e altera o numero de vitorias 
da equipa recebida consoante a chave. Nao retorna nada*/
void altera_vitoria_equipa(no_equipa *tabela_equipas[],char nome[],int chave){
    equipa *alvo = procura_equipa_lista(tabela_equipas,nome);
    if (chave == ADICIONA && alvo)
        (alvo->vitorias)++;
    else
    {
        (alvo->vitorias)--;
    }
}

/*Recebe dois pointeiros e compara os seus conteudos de acordo com a 
ordem lexicografica. Retorna um inteiro resultante da comparacao*/
int compara(const void *a,const void *b){
   const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
   
} 

/*Recebe o numero de equipas e a tabela de equipas. Procura na tabela de equipas
o maior numero de vitorias e quantas equipas tem o maior numero de vitorias. Retorna
um ponteiro para o vetor que contem na primeira posicao o numero de vitorias maximo
e na segunda o numero de equipas com essas vitorias*/
int *procura_mais_vitorias(int numero_equipas,no_equipa *tabela_equipas[]){
    no_equipa *aux;
    int max = 0,i,*res,cont = 0;
    int controlo; /*controla o numero de equipas verificadas, para otimizacao*/
    res = (int*) can_fail_malloc(sizeof(int)*2);
     for(i = 0,controlo = 0;i<MAX_TABELA && controlo<numero_equipas ;i++){
            if(!tabela_equipas[i])
                continue;
            for(aux = tabela_equipas[i];aux;aux = aux->proximo,controlo++)
                /*o numero de vitorias e maior que max?*/
                if(aux->equipa_do_no.vitorias > max){
                    /*sim, logo faz reset do contador*/ 
                    max = aux->equipa_do_no.vitorias;
                    cont = 1;
                }
                /*o numero de vitorias e igual que max?*/
                else if(aux->equipa_do_no.vitorias == max) 
                    /*sim, logo encontramos mais uma equipa*/
                    cont++;
    }
    res[0] = max;
    res[1] = cont;
    return res;
}


/*Recebe a tabela de equipas e o numero destas.Lista as equipas que tiveram mais vitorias. 
Nao retorna nada*/
void lista_mais_vitorias(no_equipa *tabela_equipas[],int linha, int numero_equipas){
    int tamanho,max,*res,i;
    int controlo; /*controla o numero de equipas verificadas, para otimizacao*/
    no_equipa *aux;
    char **mais_vitorias;
    if(!numero_equipas) return; /*se nao existirem equipas, nao imprime nada*/
    res = procura_mais_vitorias(numero_equipas,tabela_equipas);
    tamanho = res[1];
    max = res[0];
    mais_vitorias = (char**) can_fail_malloc(tamanho*sizeof(char*));
    /*retira os nomes das equipas com mais vitorias*/
    for(i=0,controlo = 0;i<MAX_TABELA && controlo<tamanho;i++){
        if(!tabela_equipas[i]) continue;
        for(aux = tabela_equipas[i];aux && controlo<tamanho;aux=aux->proximo){
            if(aux->equipa_do_no.vitorias == max){
                mais_vitorias[controlo] = aux->equipa_do_no.nome;
                controlo++;
            }
        }
    }
    /*ordena as equipas encontradas*/
    qsort(mais_vitorias,tamanho,sizeof(char*),compara);
    /*imprime as equipas*/
    printf("%d Melhores %d\n",linha,max);
    for(i=0;i<tamanho;i++){
        printf("%d * %s\n",linha,mais_vitorias[i]);
    }
    /*liberta memoria alocada*/
    free(res);
    free(mais_vitorias);
}


