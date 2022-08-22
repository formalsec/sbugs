#include <stdio.h>
#include <stdlib.h>

typedef struct{/*Estrutura que define uma ligação*/
	int u;
	int v;
}liga;

typedef struct{/*Estrutura de um router*/
	int *l;/*ligações diretas de um router*/
	int cod;/*Código de visita 0-white 1-grey 2-black*/
	int subrede;/*Número da subrede correspondente ao router*/
}router;

router *r;/*Vetor com registo das ligações diretas em cada router (Os routers a que liga e não as ligações em si)*/

int *s, *a, *b;/*s - Vetor com o número de ligações de cada rede*/

int N, M, m, w, x, y, z;

void visit(int z){
	int y;
	r[z].cod=1;
	if (z+1>m)
		m=z+1;
	for(y=0;y<s[z];y++){
		if(r[r[z].l[y]-1].cod==0 && a[r[z].l[y]-1]==0 && r[z].l[y]-1!=x)
			visit(r[z].l[y]-1);
	}
	r[z].cod=2;
}

void update(){
	int z,y;
	for(z=0;z<N;z++)/*Reset da marcação dos números das subredes dos routers*/
		r[z].subrede=0;
	for(z=0;z<N;z++){
		if(r[z].cod==0 && a[z]==0 && z!=x){
			m=z+1;
			visit(z);
			for(y=0;y<N;y++){
				if(r[y].cod==2){
					r[y].subrede=m;
					r[y].cod=3;
				}
			}
		}
	}
}

int main(){
	scanf("%d",&N);
	scanf("%d",&M);
	x=N+1;
	liga l[M];
	for(z=0;z<M;z++)
		scanf("%d %d",&l[z].u,&l[z].v);
	r=(router*)malloc(sizeof(router)*N);
	s=(int*)malloc(sizeof(int)*N);
	a=(int*)malloc(sizeof(int)*N);
	b=(int*)malloc(sizeof(int)*N);
	for(z=0;z<N;z++)
		s[z]=a[z]=b[z]=0;
	for(y=1;y<N+1;y++){
		int* p=(int*)malloc(sizeof(int)*M);/*Vetor com as ligações diretas do router para depois inserir em r*/
		w=0;
		for(z=0;z<M;z++){
			if(l[z].u==y){/*Verifica se o router em questão pertence à ligação*/
				p[w]=l[z].v;
				w+=1;
			}
			if(l[z].v==y){
				p[w]=l[z].u;
				w+=1;
			}
		}
		s[y-1]=w;
		r[y-1].l=p;
	}
	for(z=0;z<N;z++)/*Reset dos códigos de visita dos routers*/
		r[z].cod=0;
	update();

	int n=0,g[N];/*Determinar o número de sub-redes (g - Contem as sub-redes registadas)*/
	for(z=0;z<N;z++)
		g[z]=0;
	for(y=0;y<N;y++){
		if(g[r[y].subrede-1]==0){/*Determinar se o número da subrede já foi registado*/
			g[r[y].subrede-1]=r[y].subrede;
			n+=1;
		}
	}
	printf("%d\n",n);
	int O=0;
	for(z=0;z<N;z++){
		if(g[z]!=0){
			if(O!=0)
				printf(" %d",g[z]);
			else{
				printf("%d",g[z]);
				O=1;
			}
		}
	}
	printf("\n");
	int C=0;
	for(x=0;x<N;x++){
		for(z=0;z<N;z++){
			r[z].cod=0;
		}
		r[x].cod=3;

		update();
		
		int W=0,g[N];
		for(z=0;z<N;z++)
			g[z]=0;
		for(y=0;y<N;y++){
			if(y!=x){
				if(g[r[y].subrede-1]==0){
					g[r[y].subrede-1]=r[y].subrede;
					W+=1;
				}
			}
		}	
		if(W>n){
			C+=1;
			b[x]=x+1;
		}
	}
	for(z=0;z<N;z++){
		a[z]=b[z];
	}

	printf("%d\n",C);
	x=N+1;
	for(z=0;z<N;z++)
		r[z].cod=0;
	update();

	int b[N+1],m=0;/*b[] -Contagem dos routers de cada subrede | m - Número de routers da maior subrede*/
	for(z=0;z<N+1;z++){
		b[z]=0;
	}
	for(z=0;z<N;z++){
		if(a[z]==0){
			b[r[z].subrede]+=1;
		}
	}
	for(x=1;x<N+1;x++){
		if (b[x]>m)
			m=b[x];
	 }
	printf("%d\n",m);
	free(r);
	free(s);
	return 0;
}