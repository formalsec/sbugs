#include "funcoes.h"

/*
  a: (unsigned int, Jogos, Equipas) -> unsigned int
  Comando a: adiciona um novo jogo a estruturas de jogos com equipas ja existentes
*/
unsigned int a(unsigned int NL, Jogos jogos, Equipas equipas){
    Jogo novo;
    Equipa eq1, eq2;
    char nome[MAX_STR], nome_eq1[MAX_STR], nome_eq2[MAX_STR];
    int size_nome, score1, score2;

    /*obtem nomes e pontuacoes*/
    size_nome = get_string(nome);
    get_string(nome_eq1);
    get_string(nome_eq2);

    scanf("%d:%d",&score1,&score2);

    /*verifica se o jogo ja existe*/
    if(procura_jogo(jogos, nome) != NULL){
        printf("%u Jogo existente.\n",NL);
        return ++NL;
    }

    /*procura as equipas e verifica se ja existem*/
    else if((eq1 = procura_equipa(equipas, nome_eq1)) == NULL || (eq2 = procura_equipa(equipas, nome_eq2)) == NULL){
        printf("%u Equipa inexistente.\n",NL);
        return ++NL;
    }

    /*cria um novo jogo e insere o jogo na estrutura jogos*/
    novo = cria_jogo(nome, size_nome, eq1, eq2, score1, score2);
    insere_jogo(jogos, novo);

    /*incrementa o contador de linhas*/
    return ++NL;
}

/*
  l: (unsigned int, Jogos) -> unsigned int
  Comando l: Lista todos os jogos pela ordem que sao introduzidos
*/
unsigned int l(unsigned int NL, Jogos jogos){
    print_todos_jogos(jogos, NL);
    return ++NL;
}

/*
  p: (unsigned int, Jogos) -> unsigned int
  Comando p: Procura um jogo dado um nome
*/
unsigned int p(unsigned int NL, Jogos jogos){
    Jogo atual;
    char nome[MAX_STR];

    /*obtem nome do jogo a ser procurado*/
    get_string(nome);

    /*procura o jogo e verifica se ele existe*/
    if((atual = procura_jogo(jogos, nome)) == NULL)
        printf("%u Jogo inexistente.\n",NL);

    else
        printf("%u %s %s %s %d %d\n",NL,nome_jogo(atual),nome_equipa(obtem_equipa1(atual)),
            nome_equipa(obtem_equipa2(atual)),obtem_score1(atual),obtem_score2(atual));

    return ++NL;
}

/*
  A: (unsigned int, Equipas) -> unsigned int
  Comando A: Adiciona uma nova equipa
*/
unsigned int A(unsigned int NL, Equipas equipas){
    char nome[MAX_STR];
    int size;
    Equipa nova;

    /*obtem o nome da equipa*/
    size = get_string(nome);

    /*verifica se existe uma equipa com esse nome*/
    if(procura_equipa(equipas, nome) != NULL){
        printf("%u Equipa existente.\n",NL);
        return ++NL;
    }

    /*cria equipa e insere a equipa criada na estrutura equipas*/
    nova = cria_equipa(nome,size); 
    insere_equipa(equipas, nova);   

    return ++NL;
} 

/*
  P: (unsigned int, Equipas) -> unsigned int
  Comando P: Procura uma equipa dado um nome
*/
unsigned int P(unsigned int NL, Equipas equipas){
    Equipa atual;
    char nome[MAX_STR];

    /*obtem o nome da equipa*/
    get_string(nome);

    /*procura e verifica se existe uma equipa com esse nome*/
    if((atual = procura_equipa(equipas, nome)) == NULL){
        printf("%u Equipa inexistente.\n",NL);
        return ++NL;
    }

    else
        printf("%u %s %d\n",NL,nome_equipa(atual),vitorias_equipa(atual));

    return ++NL;
}

/*
  r: (unsigned int, Jogos) -> unsigned int
  Comando r: Apaga um jogo dado um nome
*/
unsigned int r(unsigned int NL, Jogos jogos){
    char nome[MAX_STR];
    Jogo jogo;

    /*obtem nome do jogo*/
    get_string(nome);

    /*procura o jogo e remove da estrutura jogos*/
    if((jogo = remove_jogos(jogos, nome)) == NULL)
        printf("%u Jogo inexistente.\n",NL);

    else
        /*se o jogo existir apaga o proprio jogo*/
        remove_jogo(jogo);

    return ++NL;
}

/*
  s: (unsigned int, Jogos) -> unsigned int
  Comando s: Altera as pontuacoes de um jogo dado o nome
*/
unsigned int s(unsigned int NL, Jogos jogos){
    char nome[MAX_STR];
    int score1,score2;
    Jogo jg;

    /*obtem nome do jogo e as novas pontuacoes*/
    get_string(nome);
    scanf("%d:%d",&score1,&score2);

    /*procura o jogo e verifica se ele existe*/
    if((jg = procura_jogo(jogos, nome)) == NULL){
        printf("%u Jogo inexistente.\n",NL);
        return ++NL;
    }

    /*altera as pontuacoes para as novas pontuacoes*/
    altera_score(jg, score1, score2);
    
    return ++NL;
}

/*
  g: (unsigned int, Equipas) -> unsigned int
  Comando g: Imprime as equipas que ganharam mais jogos por ordem lexicografica 
  (do nome da equipa)
*/
unsigned int g(unsigned int NL, Equipas equipas){
    print_vencedores(equipas, NL);
    return ++NL;
}
