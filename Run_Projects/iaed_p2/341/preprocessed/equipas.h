#ifndef EQUIPAS_1
#define EQUIPAS_1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "structs.h"
#include "funcoestabelas.h"


HashNoEquipas * EquipaJaAdicionada(HashTableEquipas * HTE,int hash, char * nome);

NoSimplesEquipas * AdicionarEquipa(int * contacomandos,HashTableEquipas * HTE,NoSimplesEquipas * listaequipas );

void ProcuraEquipa(int * contacomandos,HashTableEquipas * HTE);

void ListaMaisVitorias(int * contacomandos,NoSimplesEquipas * equipas);

void ApagarEquipas(NoSimplesEquipas * equipas);

#endif
