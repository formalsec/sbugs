#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "funcoestabelas.h"
#include "equipas.h"
#include "jogos.h"


int main(){
    /*Variavel "conta-comandos" em caso de output e usada para indicar a linha do input 
    que causou o input*/
    int contacomando = 1;
    char comando;
    /*Inicializacao das Hash Tables e das Listas ligadas utilizadas no programa*/
    NoSimplesEquipas *equipas = NULL;
    ListaDuplaJogo *jogos = can_fail_malloc(sizeof(ListaDuplaJogo));
    HashTableEquipas *HTEquipas = IniciarHTEquipas();
    HashTableJogos *HTJogos = IniciarHTJogos();
    jogos->cabeca = NULL;
    jogos->ultimo = NULL;

    while(1){  
        
        switch (comando = getchar()){/*Leitura dos comandos*/
            case 'a':
                AdicionarJogo(&contacomando,jogos,HTJogos,HTEquipas);
                break;
            case 'A':
                equipas = AdicionarEquipa(&contacomando,HTEquipas,equipas);
                break;
            case 'l':
                ListarJogos(&contacomando,jogos);
                break;
            case 'p':
                ProcuraJogo(&contacomando,HTJogos);
                break;
            case 'P':
                ProcuraEquipa(&contacomando,HTEquipas);
                break;
            case 'r':
                RemoverJogo(&contacomando,HTJogos,jogos,HTEquipas);
                break;
            case 's':
                AlteraPontuacao(&contacomando,HTEquipas,HTJogos);
                break;
            case 'g':
                ListaMaisVitorias(&contacomando,equipas);
                break;
            case 'x':
                ApagaTudo(HTEquipas,HTJogos,equipas,jogos);
                return 0;
        }
    }

}
