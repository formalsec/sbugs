#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "funcoestabelas.h"


HashTableJogos *IniciarHTJogos()
{
  HashTableJogos *HTJ;
  HTJ = malloc(sizeof(HashTableJogos));
  HTJ->capacidade = 2039;
  HTJ->listasjog = calloc(2039, sizeof(HashNoJogos *));
  return HTJ;
}

HashTableEquipas *IniciarHTEquipas()
{
  HashTableEquipas *HTE;
  HTE = malloc(sizeof(HashTableEquipas));
  HTE->capacidade = 2039;
  HTE->listasequi = calloc(HTE->capacidade, sizeof(HashNoEquipas *));
  return HTE;
}

void AdicionarHTEquipas(HashTableEquipas *HTE, int hash, NoSimplesEquipas *novo_no)
{
  HashNoEquipas *aux = malloc(sizeof(HashNoEquipas));
  aux->dadosequipa = novo_no;
  aux->proxequipah = HTE->listasequi[hash];
  HTE->listasequi[hash] = aux;
}

void AdicionarHTJogos(HashTableJogos *HTJ, int hash, NoDuploJogos *novo_no)
{
  HashNoJogos *aux = malloc(sizeof(HashNoJogos));
  aux->dadosjogo = novo_no;
  aux->proxjogoh = HTJ->listasjog[hash];
  HTJ->listasjog[hash] = aux;
}

void ApagarHTs(HashTableEquipas *HTE, HashTableJogos *HTJ)
{
  HashNoJogos *auxjog;
  HashNoEquipas *auxequi;
  int lime = HTE->capacidade;
  int limj = HTJ->capacidade;
  int counte;
  int countj;
  for (counte = 0; counte < lime; counte++)
  {
    while (HTE->listasequi[counte])
    {
      auxequi = HTE->listasequi[counte];
      HTE->listasequi[counte] = HTE->listasequi[counte]->proxequipah;
      free(auxequi);
    }

  }

  free(HTE->listasequi);
  free(HTE);
  for (countj = 0; countj < limj; countj++)
  {
    while (HTJ->listasjog[countj])
    {
      auxjog = HTJ->listasjog[countj];
      HTJ->listasjog[countj] = HTJ->listasjog[countj]->proxjogoh;
      free(auxjog);
    }

  }

  free(HTJ->listasjog);
  free(HTJ);
}

void ApagaTudo(HashTableEquipas *HTE, HashTableJogos *HTJ, NoSimplesEquipas *equipas, ListaDuplaJogo *jogos)
{
  ApagarJogos(jogos);
  ApagarEquipas(equipas);
  ApagarHTs(HTE, HTJ);
}

