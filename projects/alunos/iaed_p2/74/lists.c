#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "lists.h"


char *stringdup(char *org)
{
    long int org_size;
    static char *dup;
    char *dup_offset;

    /*Aloca memoria para duplicar */
    org_size = strlen(org);
    dup = (char *)can_fail_malloc(sizeof(char)*org_size+1);
  
    /*Copia a string*/
    dup_offset = dup;
    while(*org)
    {
        *dup_offset = *org;
        dup_offset++;
        org++;
    }
    *dup_offset = '\0';
    return(dup);
}

list *create(char *txt){
    list *temp;
    temp=(list*)can_fail_malloc(sizeof(list));
    temp->str=stringdup(txt);
    temp->next=NULL;
    temp->ant=NULL;
    return temp;
}

list *list_insert(char *txt,list *lis){
    lis->next=create(txt);
    lis->next->ant=lis;
    return lis->next;
}

int list_size(list *lis){
    int i=0;
    list *temp;
    temp = lis;
    while(temp!=NULL){
        i++;
        temp=temp->next;
    }
    return i;
}

list *list_remove(char *txt, list *lis){
    list *temp, *t1, *t2;
    temp = lis;
    while(temp!=NULL){
        t1=temp->next;
        t2=temp->ant;
        if(strcmp(temp->str,txt)==0)
            if(t2!=NULL)
                if(t1!=NULL){ /*se o elemento a remover for no meio da lista*/
                    t2->next=t1;
                    t1->ant=t2;
                    free(temp->str);
                    free(temp);
                    return lis;
                }
                else{
                    t2->next=NULL; /*se o elemento a remover for o ultimo da lista*/
                    free(temp->str);
                    free(temp);
                    return lis;
                }
            else
                if(t1!=NULL){ /*se elemento a remover e o primeiro*/
                    t1->ant=NULL;
                    free(temp->str);
                    free(temp);
                    lis=t1;
                    return lis;
                }
                else{ /*se a lista so tiver um elemento*/
                    lis=NULL;
                    free(temp->str);
                    free(temp);
                    return lis;
                }
        else{
            temp=temp->next;
        }
    }
    return NULL;
}

list *list_search(char *txt,list *lis){
    list *temp=lis;
    while(temp!=NULL){
        if(strcmp(temp->str,txt)==0){
            return temp;
        }
        else{
            temp=temp->next;
        }
    }
    return NULL;
}

void free_list(list *lis){
    list *temp = lis;
    while(temp!=NULL){
        lis=lis->next;
        free(temp->str);
        free(temp);
        temp=lis;
    }
    free(temp);
    
}
