#define max 10000
#define Charl 65

struct Pr{                  /*Produtos no sistema*/
  char desc [Charl];
  int preco;
  int stock;
};
void quicksortp(struct Pr Pr[max+1], int l, int r){

  int partition (struct Pr Pr[max+1], int l, int r);
  int i;

  if (r <=l) return;
  i = partition(Pr,l,r);
  quicksortp(Pr, l, i-1);
  quicksortp(Pr, i+1, r);

}

int partition (struct Pr Pr[max+1], int l, int r){    /*define a parti?ao e altera a ordem dos elementos*/
  int i = l-1;
  int j = r;
  int v = Pr[r].preco;

  while(i<j){
    while (Pr[++i].preco < v);
    while (v < Pr[--j].preco)
      if (j==l)
        break;
    if(i<j){
      Pr[max]=Pr[i];
      Pr[i]=Pr[j];
      Pr[j]=Pr[max];
    }
  }
  Pr[max]=Pr[i];
  Pr[i]=Pr[r];
  Pr[r]=Pr[max];
  return i;
}
