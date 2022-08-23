#include <string.h>

#define charl 65
#define max 10000

struct Pr{                  /*Produtos no sistema*/
  int idp;
  char desc[charl];
  int preco;
  int stock;
};
void alphasort(struct Pr Pr[max+1], int l, int r){

  int part (struct Pr Pr[max+1], int l, int r);
  int i;

  if (r <=l) return;
  i = part(Pr,l,r);
  alphasort(Pr, l, i-1);
  alphasort(Pr, i+1, r);

}

int part (struct Pr Pr[max+1], int l, int r){    /*define a parti?ao e altera a ordem dos elementos*/
  int i = l-1;
  int j = r;
  char v[charl];
  strcpy(v, Pr[r].desc);

  while(i<j){
    while (strcmp(Pr[++i].desc, v)<0);
    while (strcmp(v, Pr[--j].desc)<0)
      if (j==l)
        break;
    if(i<j){
      Pr[max] = Pr[i];
      Pr[i] = Pr[j];
      Pr[j] = Pr[max];
    }
  }
  Pr[max] = Pr[i];
  Pr[i] = Pr[r];
  Pr[r] = Pr[max];
  return i;
}
