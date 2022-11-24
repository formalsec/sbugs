#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*4 variaveis globais com uso para varias funcoes, exceptuando o controlador que apenas serve para o main()*/

int Controlador;

int contador_equipas;

int contador_jogos;

/*este numero_linha serve para guardar o NL indicado no iniciado, e ira ser incrementado cada vez que damos uma ordem ao sistema, com excecao do 'x' */

int numero_linha;

/*estrutura contendo todas as equipas adicionadas juntamente com o seu numero de vitorias*/
typedef struct {
    
    char equipa[1024];
    int vitorias;

} equipas; 

equipas lista_equipas[4000];

/*estrutura contendo todos os jogos juntamente com as equipas participantes e o numero de golos que a equipa 1 e a equipas 2 marcaram, tal como com o vencedor dessa partida (0 se nenhum) e se existe para
ajudar no print dos jogos e evitar alguns erros*/

typedef struct {

    char jogo[512];
    char equipa1[512];
    char equipa2[512];
    int score1;
    int score2;
    int vencedor;
    int existe;

    /* talvez adicionar um com o vencedor*/
} jogos;

jogos lista_jogos[4000];

void adiciona_equipa(char * texto);

void adiciona_jogo(char * texto);

void lista_de_jogos();

void procura_jogo(char * texto);

void procura_equipa(char * texto);

void apaga_jogo(char * texto);

void altera_pontuacao(char * texto);

void encontra_mais_vitorias();

int main()
{
    /*declaracao do valor das variaveis globais*/

    Controlador = 0;

    contador_equipas = 0;

    contador_jogos = 0;

    numero_linha = 0;

    while (Controlador == 0)
    {
        /*declaracao do texto, onde vamos guardar inicialmente toda a informacao que quereremos passar ao programa*/

        char texto[5000];
        scanf(" %[^\n]", texto);

        /*switch case com todas as opcoes de ordem para o programa executar, analisando o primeiro algarismo e de acordo com qual for, executa uma funcao especifica*/

        switch(texto[0])
        {
            case 'A':
            adiciona_equipa(texto);
            break;

            case 'a':
            adiciona_jogo(texto);
            break;

            case 'l':
            lista_de_jogos();
            break;
            
            case 'p':
            procura_jogo(texto);
            break;

            case 'P':
            procura_equipa(texto);
            break;

            case 'r':
            apaga_jogo(texto);
            break;

            case 's':
            altera_pontuacao(texto);
            break;

            case 'g':
            encontra_mais_vitorias();
            break; 

            /*se for 'x', entao o controlador vai se tornar 1 quebrando o ciclo while e acabando a funcao*/ 

            case 'x':
            Controlador = 1;
            break;

        }
    }
    return 0;
}

/*tal como o nome indica, esta funcao adiciona uma equipa a base de dados, dando store no struct criado para armazenar equipas e as suas vitorias*/

void adiciona_equipa(char * texto)
{
    /* declaracao das variaveis necessarias, de notar que o i fica como 2 para indicar a terceira posicao
    do texto de modo a saltar a letra que indica a ordem e o espaco entre a letra e o resto da ordem*/

    int i = 2;

    char str[512];

    int contador;

    int controlador = 0;

    numero_linha++;

    contador = contador_equipas - 1;

    /*passagem de o nome da equipa para um array*/

    while (texto[i] != 0)
    {
        str[i-2] = texto[i];
        i++;

    }

    /*while que verifica se a equipa ja existe na base de dados, enviando um erro e retornando se tal for o caso*/
    
    while (contador >= 0)
    {
        if (strcmp(lista_equipas[contador].equipa, str) == 0)
        {
            printf("%d Equipa existente.\n", numero_linha);  

            controlador = 1;
        }
        contador--;
    }

    if (controlador == 0)
    {
        /*passagem da palavra contida na variavel temporaria para o struct que ira guardar o nome da equipa*/
        strcpy(lista_equipas[contador_equipas].equipa, str);

        /*como adicionamos uma equipa, o contador de equipas ira incrementar*/
        contador_equipas++;
    }

    /*em todas as funcoes que uso arrays como variaveis temporarias dou reset no fim para evitar bugs no programa havendo com estar a dar overwrite na mesma variavel*/
    
    memset(str, 0, sizeof(str));
}

void adiciona_jogo(char * texto)
{
    /* declaracao de todas as variaveis necessarias para a funcao, em todas as funcoes os contadores irao ser usados para correr ciclos while e os str como variaveis 
    temporarias para palavras enquanto que as outras variaveis tem outros propositos normalmente percebe se o uso de cada de acordo com o seu nome*/

    int i = 2;

    int contador;
    int contador2;
    int index_equipa1 = 0;
    int index_equipa2 = 0;

    int controlador_equipas = 0;

    /* de notar que como os str1, 2 e 3 tem que guardar palavras com ate 1024 letras enquanto que os
    4 e 5 que apenas vao guardar o score do jogo, dai a diferenca de comprimento nos arrays*/

    char str1[512];
    char str2[512];
    char str3[512];
    char str4[10];
    char str5[10];

    numero_linha++;

    contador = 0;

    /*primeira parte da funcao que copia o nome do jogo para uma variavel e examina se esse jogo ja existe*/

    while (texto[i] != ':')
    {
        str1[contador] = texto[i];
        i++;
        contador++;
    }

    contador = 0;
    i++;

    contador2 = contador_jogos - 1;

    while (contador2 >= 0)
    {
        /*corre um ciclo while que avalia se o jogo ja existe no sistema, se sim da reset nos arrays e corre o erro, retornando no final*/

        if (strcmp(lista_jogos[contador2].jogo, str1) == 0)
        {
            memset(str1, 0, sizeof(str1));
            memset(str2, 0, sizeof(str2));
            memset(str3, 0, sizeof(str3));
            memset(str4, 0, sizeof(str4));
            memset(str5, 0, sizeof(str5));
            printf("%d Jogo existente.\n", numero_linha);
            return;
        }
        contador2--;
    }

    /*segunda parte da funcao que copia o nome das equipas e analisa se as equipas sao validas e existem*/

    /*para a primeira equipa*/

    while (texto[i] != ':')
    {
        str2[contador] = texto[i];
        i++;
        contador++;
    }

    contador = 0;
    i++;

    contador2 = contador_equipas - 1;

    /*analisa se a equipa existe no sistema, se sim ativa a variavel controlador_equipa que ira deixar a funcao continuar sem erro,
    caso contrario ira dar o erro que a equipa nao existe*/

    while (contador2 >= 0)
    {
        if (strcmp(lista_equipas[contador2].equipa, str2) == 0)
        {
            controlador_equipas = 1;
            index_equipa1 = contador2;
        }
        contador2--;
    }

    if (controlador_equipas != 1)
    {
        /*tal como com o nome jogo, se houver erro primeiro os arrays levam reset*/

        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
        memset(str3, 0, sizeof(str3));
        memset(str4, 0, sizeof(str4));
        memset(str5, 0, sizeof(str5));
        printf("%d Equipa inexistente.\n", numero_linha);
        return;

    }

    /*para a segunda equipa aplica se exatamente o mesmo que com a primeira*/

    while (texto[i] != ':')
    {
        str3[contador] = texto[i];
        i++;
        contador++;
    }

    contador = 0;
    i++;

    contador2 = contador_equipas - 1;

    controlador_equipas = 0;

    while (contador2 >= 0)
    {
        if (strcmp(lista_equipas[contador2].equipa, str3) == 0)
        {
            controlador_equipas = 1;
            index_equipa2 = contador2;
        }
        contador2--;
    }

    if (controlador_equipas != 1)
    {
        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
        memset(str3, 0, sizeof(str3));
        memset(str4, 0, sizeof(str4));
        memset(str5, 0, sizeof(str5));
        printf("%d Equipa inexistente.\n", numero_linha);
        return;
    }

    /*terceira parte onde nao ha possiblidade de erros e apenas se passa o score para a respetiva variavel*/

    while (texto[i] != ':')
    {
        str4[contador] = texto[i];
        i++;
        contador++;
    }

    contador = 0;
    i++;

    while (texto[i] != 0)
    {
        str5[contador] = texto[i];
        i++;
        contador++;
    }

    /*no final, se nao houver erros que causam o return da funcao, entao entramos na parte em que todas 
    as variaveis temporarias sao incorporadas na respetiva variavel na estrutura que da store nos jogos*/

    strcpy(lista_jogos[contador_jogos].jogo, str1);
    strcpy(lista_jogos[contador_jogos].equipa1, str2);
    strcpy(lista_jogos[contador_jogos].equipa2, str3);
    sscanf(str4, "%d", &lista_jogos[contador_jogos].score1);
    sscanf(str5, "%d", &lista_jogos[contador_jogos].score2);
    lista_jogos[contador_jogos].existe = 1;

    /*apos o store vemos que equipa e a vencedora, se empatarem ninguem vence*/

    if (lista_jogos[contador_jogos].score1 > lista_jogos[contador_jogos].score2)
    {
        lista_equipas[index_equipa1].vitorias++;
        lista_jogos[contador_jogos].vencedor = 1;
    }

    if (lista_jogos[contador_jogos].score2 > lista_jogos[contador_jogos].score1)
    {
        lista_equipas[index_equipa2].vitorias++;
        lista_jogos[contador_jogos].vencedor = 2;
    }

    /*incremento do contador de jogos, visto que adicionamos um novo ao sistema*/

    contador_jogos++;

    /*reset dos arrays no final tal como feito na ultima funcao*/

    memset(str1, 0, sizeof(str1));
    memset(str2, 0, sizeof(str2));
    memset(str3, 0, sizeof(str3));
    memset(str4, 0, sizeof(str4));
    memset(str5, 0, sizeof(str5));
}


void lista_de_jogos()
{
    int contador;

    numero_linha++;

    contador = 0;

    /*bastante facil de perceber, apenas corremos um ciclo onde vamos incrementando o contador enquanto o limite nao e atingido, 
    em que se o jogo existir, iremos dar lhe print criando uma lista de todos os jogos adicionados ao sistema ate ao momento, indicando o nome do jogo, as duas equipas e o seu score*/

    while (contador < contador_jogos)
    {
        if (lista_jogos[contador].existe == 1)
        {
            printf("%d %s %s %s %d %d\n", numero_linha, lista_jogos[contador].jogo, lista_jogos[contador].equipa1, lista_jogos[contador].equipa2, lista_jogos[contador].score1, lista_jogos[contador].score2);
            contador++;
        }
    }
}

void procura_jogo(char * texto)
{
    /* declaracao das variaveis e um ciclo para detetar se o jogo existe, bastante parecido com a forma como vimos se as equipas existiam no adiciona_jogo()*/

    int i = 2;

    char str[1024];

    int contador;

    int controlador = 0;

    int index_jogo;

    numero_linha++;

    contador = contador_jogos - 1;

    while (texto[i] != 0)
    {
        str[i-2] = texto[i];
        i++;
    }

    while (contador >= 0)
    {
        if (strcmp(lista_jogos[contador].jogo, str) == 0)
        {
            controlador = 1;
            index_jogo = contador;

        }
        contador--;
    }

    if (controlador != 1)
    {
        /* se nao existir da se o tal erro com o reset e o return*/

        memset(str, 0, sizeof(str));
        printf("%d Jogo inexistente.\n", numero_linha);
        return;
    }

    /*se existir da se o print de acordo com os elementos necessarios de acordo com o enunciado e por ultimo o reset do array usado como variavel temporaria*/

    printf("%d %s %s %s %d %d\n", numero_linha, lista_jogos[index_jogo].jogo, lista_jogos[index_jogo].equipa1, lista_jogos[index_jogo].equipa2, lista_jogos[index_jogo].score1, lista_jogos[index_jogo].score2);
    memset(str, 0, sizeof(str));
}

void procura_equipa(char * texto)
{
    /*tem exatamente a mesma logica e a mesma estrutura que a funcao procura jogo, apenas alterando o print que damos*/

    int i = 2;

    char str[512];

    int contador;

    int controlador = 0;

    int index_equipa;

    numero_linha++;

    contador = contador_equipas - 1;

    while (texto[i] != 0)
    {
        str[i-2] = texto[i];
        i++;
    }

    while (contador >= 0)
    {
        if (strcmp(lista_equipas[contador].equipa, str) == 0)
        {
            controlador = 1;
            index_equipa = contador;

        }
        contador--;
    }

    if (controlador != 1)
    {
        memset(str, 0, sizeof(str));
        printf("%d Equipa inexistente.\n", numero_linha);
        return;
    }

    printf("%d %s %d\n", numero_linha, lista_equipas[index_equipa].equipa, lista_equipas[index_equipa].vitorias);
    memset(str, 0, sizeof(str));
}

void apaga_jogo(char * texto)
{
    /*declaracao de varias variveis, e a funcao que usa mais devido ao alto numero de whiles que usa comparando com as outras*/

    int i = 2;

    char str[512];

    int contador;

    int contador2;

    int contador3;

    int contador4;

    int contador5;

    int controlador = 0;

    int index_jogo;

    numero_linha++;

    contador = contador_jogos - 1;

    /*o primeiro passo nesta funcao e passar o nome do jogo para uma variavel e verificar se e um jogo valido, tal como fizemos no procura_jogo()*/

    while (texto[i] != 0)
    {
        str[i-2] = texto[i];
        i++;
    }

    while (contador >= 0)
    {
        if (strcmp(lista_jogos[contador].jogo, str) == 0)
        {
            controlador = 1;
            index_jogo = contador;

        }
        contador--;
    }

    if (controlador != 1)
    {
        memset(str, 0, sizeof(str));
        printf("%d Jogo inexistente.\n", numero_linha);
        return;
    }

    contador2 = contador_jogos - 1;

    contador3 = index_jogo;

    contador4 = index_jogo + 1;

    contador5 = contador_equipas - 1;

    /*apos por mos com valor varias variaveis que sao uteis para correr os ciclos while e indicar equipas e jogos, vamos analisar se ha algum vencedor no jogo que vamos apagar e se houver
    corremos um ciclo destinado a encontrar onde esta essa equipa na estrutura que contem as equipas e tirar lhe a vitoria do jogo a remover*/

    if (lista_jogos[contador3].vencedor == 1)
    {
        while (contador5 >= 0)
        {
            if (strcmp(lista_equipas[contador5].equipa, lista_jogos[contador3].equipa1) == 0)
            {
                lista_equipas[contador5].vitorias--;
            }
            contador5--;
        }
    }

    if (lista_jogos[contador3].vencedor == 2)
    {
        while (contador5 >= 0)
        {
            if (strcmp(lista_equipas[contador5].equipa, lista_jogos[contador3].equipa2) == 0)
            {
                lista_equipas[contador5].vitorias--;
            }
            contador5--;
        }
    }

    /*por ultimo vmamos correr um ciclo que passa todos os jogos que estao na posicao apos esse jogo para a posicao atras, 
    de modo a nao haver uma posicao na lista_jogos sem ser usada para tentar nao desperdicar memoria*/
    
    while (contador2 > index_jogo)
    {
        memset(lista_jogos[contador3].jogo, 0, sizeof(lista_jogos[contador3].jogo));
        memset(lista_jogos[contador3].equipa1, 0, sizeof(lista_jogos[contador3].equipa1));
        memset(lista_jogos[contador3].equipa2, 0, sizeof(lista_jogos[contador3].equipa2));

        strcpy(lista_jogos[contador3].jogo, lista_jogos[contador4].jogo);
        strcpy(lista_jogos[contador3].equipa1, lista_jogos[contador4].equipa1);
        strcpy(lista_jogos[contador3].equipa2, lista_jogos[contador4].equipa2);

        lista_jogos[contador3].score1 = lista_jogos[contador4].score1;
        lista_jogos[contador3].score2 = lista_jogos[contador4].score2;
        lista_jogos[contador3].vencedor = lista_jogos[contador4].vencedor;

        contador3++;
        contador4++;
        contador2--;
    }

    /* se o jogo estiver na ultima posicao, entao apenas o removemos com o reset dos arrays e o set dos ints para 0, nomeadamente
    o exite que ira permitir que este jogo nao seja dado print se for corrido a ordem para listar todos os jogos*/


    if (contador2 == index_jogo)
    {
        memset(lista_jogos[contador3].jogo, 0, sizeof(lista_jogos[contador3].jogo));
        memset(lista_jogos[contador3].equipa1, 0, sizeof(lista_jogos[contador3].equipa1));
        memset(lista_jogos[contador3].equipa2, 0, sizeof(lista_jogos[contador3].equipa2));
        lista_jogos[contador3].score1 = 0;
        lista_jogos[contador3].score2 = 0;
        lista_jogos[contador3].vencedor = 0;
        lista_jogos[contador4].existe = 0;
    }

    /* no final apamos a ultima posicao da estrutura que contem os jogos, visto que de momento ela se encontra duplicada no penultimo e no ultimo lugar*/

    memset(lista_jogos[contador4].jogo, 0, sizeof(lista_jogos[contador4].jogo));
    memset(lista_jogos[contador4].equipa1, 0, sizeof(lista_jogos[contador4].equipa1));
    memset(lista_jogos[contador4].equipa2, 0, sizeof(lista_jogos[contador4].equipa2));
    lista_jogos[contador4].score1 = 0;
    lista_jogos[contador4].score2 = 0;
    lista_jogos[contador4].vencedor = 0;
    lista_jogos[contador4].existe = 0;

    memset(str, 0, sizeof(str));
}

void altera_pontuacao(char * texto)
{
    /*inicio semelhante as outras funcoes, com a declaracao das variaveis necessarias e a passagem da palavra jogo com para uma variavel, juntamente com os scores a alterar*/

    int i = 2;

    int contador;

    int contador2;

    int index_jogo;

    int controlador_jogo;

    int vencedor;

    int index_equipa1;

    int index_equipa2;

    char str1[512];
    char str2[10];
    char str3[10];

    numero_linha++;

    contador = 0;

    while (texto[i] != ':')
    {
        str1[contador] = texto[i];
        i++;
        contador++;
    }

    contador = 0;
    i++;

    while (texto[i] != ':')
    {
        str2[contador] = texto[i];
        i++;
        contador++;
    }

    contador = 0;
    i++;

    while (texto[i] != 0)
    {
        str3[contador] = texto[i];
        i++;
        contador++;
    }

    contador2 = contador_jogos - 1;

    /*apos a passagem corremos um ciclo while para identificar o index do jogo na struct e correr o erro se o jogo nao existir*/

    while (contador2 >= 0)
    {
        if (strcmp(lista_jogos[contador2].jogo, str1) == 0)
        {
            controlador_jogo = 1;
            index_jogo = contador2;
        }
        contador2--;
    }

    if (controlador_jogo != 1)
    {
        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
        memset(str3, 0, sizeof(str3));
        printf("%d Jogo inexistente.\n", numero_linha);
        return;
    }

    /* passagem dos scores para a struct como int*/

    sscanf(str2, "%d", &lista_jogos[index_jogo].score1);
    sscanf(str3, "%d", &lista_jogos[index_jogo].score2);

    /*na ultima parte vem a lista de ifs que em primeiro lugar ve quem e o vencedor no novo score ou se empataram*/

    if (lista_jogos[index_jogo].score1 > lista_jogos[index_jogo].score2)
    {
        vencedor = 1;
    }

    if (lista_jogos[index_jogo].score2 > lista_jogos[index_jogo].score1)
    {
        vencedor = 2;
    }

    if (lista_jogos[index_jogo].score2 == lista_jogos[index_jogo].score1)
    {
        vencedor = 0;
    }

    /*e em segundo lugar de acordo com o vencedor antigo e com o novo vencedor ira alterar a contagem de vitorias*/

    if (lista_jogos[index_jogo].vencedor != vencedor)
    {
        contador = contador_equipas - 1;

        /*primeiro ve quem sao as equipas e o index delas no struct das equipas*/

        while (contador >= 0)
        {
            if (strcmp(lista_equipas[contador].equipa, lista_jogos[index_jogo].equipa1) == 0)
            {
                index_equipa1 = contador;
            }
            contador--;
        }

        contador = contador_equipas - 1;

        while (contador >= 0)
        {
            if (strcmp(lista_equipas[contador].equipa, lista_jogos[index_jogo].equipa2) == 0)
            {
                index_equipa2 = contador;
            }
            contador--;
        }

        /*depois de acordo com a situacao altera a contagem de vitorias*/

        if (vencedor == 0)
        {
            if (lista_jogos[index_jogo].vencedor == 1)
            {
                lista_equipas[index_equipa1].vitorias--;
            }

            if (lista_jogos[index_jogo].vencedor == 2)
            {
                lista_equipas[index_equipa2].vitorias--;
            }
        }

        if (lista_jogos[index_jogo].vencedor == 0)
        {
            if (vencedor == 1)
            {
                lista_equipas[index_equipa1].vitorias++;
            }

            if (vencedor == 2)
            {
                lista_equipas[index_equipa2].vitorias++;
            }
        }

        if (vencedor == 1)
        {
            if (lista_jogos[index_jogo].vencedor == 2)
            {
                lista_equipas[index_equipa1].vitorias++;
                lista_equipas[index_equipa2].vitorias--;
            }
        }

        if (vencedor == 2)
        {
            if (lista_jogos[index_jogo].vencedor == 1)
            {
                lista_equipas[index_equipa1].vitorias--;
                lista_equipas[index_equipa2].vitorias++;
            }
        }

        lista_jogos[index_jogo].vencedor = vencedor;
    }
}

void encontra_mais_vitorias()
{

    /*para a ultima funcao apos as variaveis serem declaradas, ha um while simples que e corrido para determinar a numero maximo de vitorias que uma ou mais equipas tem*/

    int contador;
    
    int numero_vitorias;

    numero_linha++;

    numero_vitorias = 0;

    contador = contador_equipas - 1;

    while (contador >= 0)
    {
        if (lista_equipas[contador].vitorias > numero_vitorias)
        {
            numero_vitorias = lista_equipas[contador].vitorias;
        }
        contador--;
    }

    contador = 0;

    /*depois se existirem equipas e corrido um while que determina que se a uma equipa possui a contagem de vitorias 
    equivalente a maxima, entao essa equipa ira levar print e ira pertencer a lista de equipas com mais vitorias*/

    /*se houverem mais do que uma equipa entao o print e a lista vai da ordem da primeira a ser adicionada no sistema para a ultima*/

    if (contador_equipas > 0)
    {
        printf("%d Melhores %d\n", numero_linha, numero_vitorias);
        while (contador < contador_equipas)
        {
            if (lista_equipas[contador].vitorias == numero_vitorias)
            {
                printf("%d * %s\n", numero_linha, lista_equipas[contador].equipa);
            }
            contador++;
        }
    }
}
