#include <stdio.h>
#include <stdlib.h>

struct cl{
	int nodenum;
	struct cl *next;
};
struct mainvalue{
	int val;
	struct cl *prop;
}mainvalue;

void update(int nodenum,int val,struct mainvalue *mainlist){
	struct cl *it;
	if (mainlist[nodenum].val < val){
		mainlist[nodenum].val = val;
		if (mainlist[nodenum].prop != NULL){
			for (it = mainlist[nodenum].prop;it != NULL;it = it->next){
				update(it->nodenum,val,mainlist);
			}
		}
	}
}

int main(){
	int nodecount,concount,readval,readval2,i;
	struct mainvalue *mainlist;
	struct cl *connect,*it,*last;

	scanf("%d,%d",&nodecount,&concount);

	mainlist = malloc(nodecount * sizeof(struct mainvalue));	
	
	for (i = 0; i < nodecount; ++i){
		scanf("%d",&readval);
		mainlist[i].val = readval;
		mainlist[i].prop = NULL;
	}

	for (i = 0; i < concount; ++i){
		scanf("%d %d",&readval,&readval2);
		readval--;
		readval2--;
		connect = malloc(sizeof(struct cl));
		connect->nodenum = readval;
		if (mainlist[readval2].prop == NULL)
			mainlist[readval2].prop = connect;
		else {
			for (last = NULL,it = mainlist[readval2].prop;it != NULL;last = it,it = it->next){}
			last->next = connect;
		}
	}

	for (i = 0; i < nodecount; ++i){
		for (it = mainlist[i].prop;it != NULL;it = it->next){
			update(it->nodenum,mainlist[i].val,mainlist);
		}
	}
	for (i = 0; i < nodecount; ++i)
		printf("%d\n",mainlist[i].val);

	for (i = 0; i < nodecount; ++i){
		if(mainlist[i].prop != NULL){
			for (last = NULL,it = mainlist[i].prop;it != NULL;last = it,it = it->next){
				free(last);
			}
		}
	}
	free(mainlist);
	exit(0);
}