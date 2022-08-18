#include "List.h"

/* Creates and returns a new List, initializing all it's values as NULL.*/
List InitList(){
    List l;
    l = (List) malloc(sizeof(struct list));
    SetHead(l, NULL);
    SetEnd(l, NULL);
    return l;
}

/* Receives a List and a Node, sets that Node as the List's head.*/
void SetHead(List l, Node node){
    l->head = node;
}

/* Receives a List and a Node, sets that Node as the List's end.*/
void SetEnd(List l, Node node){
    l->end = node;
}

/* Receives a List ans returns it's head.*/
Node Head(List l){
    return l->head;
}

/* Receives a List and returns it's end.*/
Node End(List l){
    return l->end;
}

/* Receives a List and a Game, and inserts the Game at the end of List.*/
void InsertEnd(List l, Game g){
    /* Node "new" is the new node inserted at the end of List "l".*/
    Node new = InitNode();
    
    SetGame(new, g);
    /* If the head is not NULL, the previous Node from the new Node is the one in the end.*/
    if (Head(l) != NULL){
        SetPrev(new, End(l));
        SetNext(End(l), new);
    }
    /* If the head is NULL, then there is no previous Node to the new Node.*/
    else { 
        SetHead(l, new);
        SetPrev(new, NULL);
    }
    /* Updates the end of the List "l".*/
    SetEnd(l, new);
}

/* Receives a Node and a List, removing the Node from the List.*/
void RemoveGame(Node node, List l){
    Team winner;

    /* If either the previous Node and the next Node are not NULL, then the Node is fully surrounded.*/
    if ((Prev(node) != NULL) && (Next(node) != NULL)){
        SetNext(Prev(node), Next(node));
        SetPrev(Next(node), Prev(node));
    }
    /* If only the previous Node is not NULL, the Node is at the end of the List.*/
    else if (Prev(node) != NULL){
        SetNext(Prev(node), NULL);
        SetEnd(l, Prev(node));
    }
    /* If only the next node is not NULL, the Node is at the beggining of the List.*/
    else if (Next(node) != NULL){
        SetPrev(Next(node), NULL);
        SetHead(l, Next(node));
    }
    /* If everything fails, the Node is the only one at the List.*/
    else{
        SetEnd(l, NULL);
        SetHead(l, NULL);
    }

    /* If there is a winner to the removed Game, it must be decremented from the winner team.*/
    winner = Winner(NodeGame(node));
    if (winner != NULL)
        DecWins(winner);
    
    /* Destroys all the memory associated to the Node and the Game in it.*/
    DestroyGame(NodeGame(node));
    DestroyNode(node);
}

/* Receives a List and destroys it, cleaning the memory.*/
void DestroyList(List l){
    Node aux;
    Node head = Head(l);

    /* If the head is not NULL, there are Nodes to destroy.*/
    if (head != NULL){
        /* For each "aux" Node not NULL, the Game inside it and the Node are destroyed.*/
        for (aux = Next(head); aux != NULL; head = aux, aux = Next(aux)){
            DestroyGame(NodeGame(head));
            DestroyNode(head);
        }
        /* In the end, the last remaining Game and Node are destroyed.*/
        DestroyGame(NodeGame(head));
        DestroyNode(head);
    }
    /* The List "l" is also destroyed.*/
    free(l);
}