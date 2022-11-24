#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "funcoes.h"

/*funcao que adiciona uma equipa ao sistema*/
void adiciona_equipa(link* heads,int n_linha)
{
    /*declaracao e leitura das variaveis*/
    char buffer[MAX_LETRAS];
    char *nome;
    scanf(" %[^:\n]",buffer);

    /*reserva de memoria para o nome da equipa e atribuicao*/
    nome=(char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(nome,buffer);

    /*nome da equipa nao pode ja existir*/
    if (existe_el(heads,nome)==TRUE)
    {
        printf("%d Equipa existente.\n",n_linha);
       
        
    }
    else
    {
        /*insere a equipa na hashtable*/
        insere_na_lista(heads,nome);
        
    }
    
    free(nome);
    
}

/*funcao que procura uma certa equipa e devolve o seu nome e jogos ganhos*/
void devolve_equipa(link*heads,int n_linha)
{
    /*declaracao e leitura das variaveis*/
    char buffer[MAX_LETRAS];
    Equipa* equipa;
    scanf(" %[^:\n]",buffer);

    /*guarda-se a equipa*/
    equipa=procura_equipa(heads,buffer);
    
    /*equipa tem que existir*/
    if(equipa!=NULL)
    {
        /*sao imprimidos os seus dados*/
        
        printf("%d %s %d\n",n_linha,equipa->nome,equipa->jogos_ganhos);
    }
    else
        printf("%d Equipa inexistente.\n",n_linha);
   
    
}

/*funcao que adiciona um novo jogo ao sistema*/
void adiciona_jogo(limites_lista* lista,link_jogo* heads_jogos,link*heads,int n_linha)
{
    /*declaracao e leitura das variaveis*/
    int score1,score2;
    char buffer[MAX_LETRAS];
    char *nome,*equipa1,*equipa2;
    scanf(" %[^:\n]:",buffer);
    
    
    nome=(char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    
    /*vai lendo, reservando memoria e copiando cada string*/
    strcpy(nome,buffer);

    scanf("%[^:\n]:",buffer);
    
    equipa1=(char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(equipa1,buffer);
    

    scanf("%[^:\n]:",buffer);
    
    equipa2=(char*) can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(equipa2,buffer);
    
    /*leitura do score*/
    scanf("%d:%d",&score1,&score2);
    

    
    /*nome do jogo tem que ser novo*/
    if (existe_jogo(heads_jogos,nome)==TRUE)
    {
        printf("%d Jogo existente.\n",n_linha);
       
        
    }
    /*amabas as equipas tem que existir*/
    else if(existe_el(heads,equipa1)==FALSE || existe_el(heads,equipa2)==FALSE)
    {
        printf("%d Equipa inexistente.\n",n_linha);
        
        
        
    }
    else
    {
        /*cria o jogo e insere-o na hashtable*/
       insere_jogo_hash(lista,heads,heads_jogos,nome,equipa1,equipa2,score1,score2);
        
        
    }
    /*liberta os nomes*/
    free(nome);
    free(equipa1);
    free(equipa2);
    
   
}

/*funcao que imprime os jogos por ordem de introducao no sistema*/
void print_jogos(limites_lista* lista,int n_linha)
{
    link_lista aux;
    /*percorre toda a lista e vai imprimindo os seus dados*/
    for(aux=lista->head;aux!=NULL;aux=aux->next)
        printf("%d %s %s %s %d %d\n",n_linha,
                    aux->jogo->nome,aux->jogo->equipa1->nome,aux->jogo->equipa2->nome,
                            aux->jogo->score1,aux->jogo->score2);
   }

/*funcao que procura um certo jogo pelo seu nome e devolve os seus dados*/
void devolve_jogo(link_jogo* heads_jogos,int n_linha)
{
    /*declaracao e leitura das variaveis*/
    char buffer[MAX_LETRAS];
    Jogo* jogo;
    scanf(" %[^:\n]",buffer);
    
    /*guarda-se o jogo*/

    jogo=procura_jogo(heads_jogos,buffer);
    /*jogo tem que existir*/
    if(jogo!=NULL)
    {
        /* imprime-se os seus dados*/
        
        printf("%d %s %s %s %d %d\n",n_linha,jogo->nome,
            jogo->equipa1->nome,jogo->equipa2->nome,jogo->score1,jogo->score2);
    }
    else
        printf("%d Jogo inexistente.\n",n_linha);
    
    
}

/*funcao que altera o score de um jogo*/
void altera_score(link_jogo* heads_jogos,int n_linha)
{
    /*declaracao e leitura das variaveis*/
    int score1,score2,empate=0,derrota=0,vitoria=0;
    char buffer[MAX_LETRAS];
    Jogo* jogo;
    scanf(" %[^:\n]:%d:%d",buffer,&score1,&score2);

    /*jogo tem que existir*/
    if(existe_jogo(heads_jogos,buffer)==1)
    {
        /*procura o jogo*/
        jogo=procura_jogo(heads_jogos,buffer);

        /*determina quem ganhou ou se houve empate no jogo anterior
        -->vitoria: ganhou equipa1
        -->derrota: ganhou equipa2 */

        if(jogo->score1==jogo->score2)
            empate=1;
        else if(jogo->score1>jogo->score2)
            vitoria=1;
        else    
            derrota=1;

        /*atualiza o score*/
        jogo->score1=score1;
        jogo->score2=score2;

        /*se no novo score ganhou a equipa1*/
        if(score1>score2)
        {
            /*e elas tinham antes empatado a equipa1 ganha mais um jogo*/
            if(empate==1)
                jogo->equipa1->jogos_ganhos+=1;
            /*se tinha antes ganho a equipa2 esta perde um jogo e a equipa 1 ganha*/
            else if(derrota==1)
            {
                jogo->equipa1->jogos_ganhos+=1;
                jogo->equipa2->jogos_ganhos-=1;
            }
        }
        /*mesma situacao so que para a equipa 2*/
        else if(score2>score1)
        {
            
            if(empate==1)
                jogo->equipa2->jogos_ganhos+=1;
            else if(vitoria==1)
            {
                jogo->equipa2->jogos_ganhos+=1;
                jogo->equipa1->jogos_ganhos-=1;
            }
        }
        /*se ambas empataram anteriormente e alguma 
        das duas agora ganhou ganha mais um jogo*/
        else
        {
            if(vitoria==1)
                jogo->equipa1->jogos_ganhos-=1;
            else if(derrota==1)
                jogo->equipa2->jogos_ganhos-=1;
        }

    }
    else
        printf("%d Jogo inexistente.\n",n_linha);
    

}

/*funcao que apaga um jogo do sistema*/
void apaga_jogo(link_jogo* head_jogos,limites_lista* lista,int n_linha)
{
    /*declaracao e leitura das varaiveis*/
    char buffer[MAX_LETRAS];
    char *nome;
    Jogo *jogo;
    scanf(" %[^:\n]",buffer);
    
    nome=(char*)can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(nome,buffer);
    
    /*jogo tem que existir*/
    if(existe_jogo(head_jogos,nome)==TRUE)
    {
        /*guarda o jogo*/
        jogo=procura_jogo(head_jogos,nome);


        /*apaga-se o no do jogo na hashtable e na lista duplamente ligada*/
        apaga_jogo_hash(head_jogos,nome);
        apaga_jogo_lista(lista,nome);
        
        /*se alguem ganhou esse jogo e' lhe retirado essa vitoria*/
        if(jogo->score1>jogo->score2)
        {
            jogo->equipa1->jogos_ganhos-=1;
        }
        else if(jogo->score2>jogo->score1)
        {
            jogo->equipa2->jogos_ganhos-=1;
        }

        /*liberta-se o nome do jogo e a estrutura*/
        free(jogo->nome);
        free(jogo);
        
        
    }
    else    
        printf("%d Jogo inexistente.\n",n_linha);
    free(nome);
    
    

}

/*funcao que imprime os dados das equipas com mais vitorias e esse numero*/
void equipas_mais_vitorias(link*heads,int M,int n_linha)
{
    /*vetor para guardar os nomes das equipas*/
    char**nomes;
    int max=0,n_el=0,i;
    link head,aux;
    /*lista para guardar as equipas com mais vitorias*/
    link lista=NULL;

    /*ciclo que percorre todas as listas da hashtable*/
    for(i=0;i<M;i++)
    {
        head=heads[i];
        /*percorre todos os elementos de cada lista*/
        while(head!=NULL)
        {
            /*se o numero de jogos de uma equipa superar o maximo ja existente*/
            if(head->equipa->jogos_ganhos>max)
            {
                /*o maximo e' substituido*/
                max=head->equipa->jogos_ganhos;
                /*a lista e' destruida e e' adicionada a equipa analisada apenas*/
                lista=destroi(lista);
                lista=insere_el_char(lista,head->equipa);
                n_el=1;
                
            }
            /*se o numero de jogos for igual ao maximo*/
            else if(head->equipa->jogos_ganhos==max)
            {
                /*a equipa e' adicionada a lista e o n de elementos da lista aumenta*/
                lista=insere_el_char(lista,head->equipa);
                n_el++;
            }
            head=head->next;
        }
    }
    /*reserva-se memorias para os n. de strings*/
    nomes=(char**)can_fail_malloc(n_el*sizeof(char*));

    /*percorre-se todos os elementos da lista e sao copiados para o vetor*/
    for(i=0,aux=lista;i<n_el;i++)
    {
        nomes[i]=(char*)can_fail_malloc(sizeof(char)*(strlen(aux->equipa->nome)+1));
        strcpy(nomes[i],aux->equipa->nome);
        aux=aux->next;
    }

    /*sao organizadas as equipas pela ordem lexicografica dos seus nome*/
    qsort(nomes,n_el,sizeof(char*),comparar_nome);
    
    /*se houver elementos*/
    if(n_el>0)
    {
        /*sao imprimidas as equipas uma a uma*/
        printf("%d Melhores %d\n",n_linha,max);
        for(i=0;i<n_el;i++)
            printf("%d * %s\n",n_linha,nomes[i]);
    }
    /*liberta-se a memoria do vetor*/
    for(i=0;i<n_el;i++)
    {
        free(nomes[i]);
    }
    free(nomes);
    /*destroi-se a lista*/
    lista=destroi(lista);
    
}

/*funcao que destroi as estruturas usadas*/
void destroi_tudo(link_jogo* head_jogos,limites_lista* lista, link*heads,int M,int n)
{
    /*primeiro destroi as equipas e a sua hashtable*/
    destroi_hash_equipa(heads,n);
    /*depois o nome dos jogos, as estruturas dos jogos e a sua hashtable*/
    destroi_lista_jogos(lista);
    /*por fim apenas falta destruir os nos da lista dos jogos*/
    destroi_hash_jogos(head_jogos,M);
}