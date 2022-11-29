#ifndef JOGOS_1
#define JOGOS_1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "hash.h"
#include "equipas.h"
#include "funcoestabelas.h"
int JogoJaAdicionado(HashTableJogos * HTJ,int hash,char * nome);

void AdicionarJogo(int * contacomandos,ListaDuplaJogo * listajogos,HashTableJogos * HTJ,HashTableEquipas * HTE);

void RemoverJogo(int * contacomandos,HashTableJogos * HTJ,ListaDuplaJogo * listajogos,HashTableEquipas * HTE);

void ProcuraJogo(int * contacomandos,HashTableJogos * HTJ);

void AlteraPontuacao(int * contacomandos,HashTableEquipas * HTE,HashTableJogos * HTJ);

void ListarJogos(int * contacomandos,ListaDuplaJogo * jogos);

void ApagarJogos(ListaDuplaJogo * jogos);
#endif
