#ifndef FUNCOESTABELAS_1
#define FUNCOESTABELAS_1
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "structs.h"
#include "jogos.h"
#include "equipas.h"
HashTableJogos * IniciarHTJogos();

HashTableEquipas * IniciarHTEquipas();

void AdicionarHTEquipas(HashTableEquipas * HTE,int hash,NoSimplesEquipas * novo_no);

void AdicionarHTJogos(HashTableJogos * HTJ,int hash,NoDuploJogos * novo_no);

void ApagarHTs(HashTableEquipas * HTE,HashTableJogos * HTJ);

void ApagaTudo(HashTableEquipas * HTE,HashTableJogos * HTJ,NoSimplesEquipas * equipas,ListaDuplaJogo * jogos);

#endif
