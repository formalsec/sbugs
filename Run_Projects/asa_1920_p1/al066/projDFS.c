/*1 Projeto de ASA*/
/*Grupo 66*/
/*Fatima Napoleao:91605	*/
/*Joana Raposo: 92485*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


 
typedef struct Vertices{
    /*represents students*/ 
    int   StudentId;
    int  previousStudentGrade;
    int actualStudentGrade;
    struct Vertices* nextStudent;
    
}vertex; 


typedef struct  Graph{

    int *visited;
    int verticesNumber;
    vertex**adjlist;

}graph;




/*Prototypes*/

graph* CreateGraph(int verticesNumber);
void  createStudentVertex(int StudentGrade, graph* G, int index);
void InsertFriendshipEdge(int student, int friend, graph* G);
void calculateNewGrades(graph * G, int * PreviousGrades);
void caculate(vertex *u);
void DFS_VISIT_STUDENT(graph * g,int studentId, int student);
int maxgrade(int x, int y);

/*Global Variables*/
graph *G;
int current_grade=0;


/*Fuctions*/

/*Graph Functions*/
graph* CreateGraph(int verticesNumber){

    int counter;
    
    graph * G = (graph*) malloc(sizeof(graph));
    if(G != NULL){

    G->verticesNumber = verticesNumber;

    G->adjlist = (vertex**)malloc(sizeof(vertex*)*(verticesNumber+1));
    G->visited = (int*) malloc(sizeof(int)*(verticesNumber+1));
    

    for(counter = 1; counter < verticesNumber; counter++){
        
        G->visited[counter] = 0;
        G->adjlist[counter] = NULL;
    }  
   
    }

    return G;
    
}

/*Students Vertices Functions*/
void  createStudentVertex(int StudentGrade, graph* G, int index){

    vertex* aux = (vertex*) malloc(sizeof(vertex)); 
    aux ->previousStudentGrade = StudentGrade;
    aux->StudentId = index;
    
    aux->nextStudent = NULL;

    G->adjlist[index] = aux;

    

}


 void InsertFriendshipEdge(int student, int friend, graph* G){

    
    vertex* aux = (vertex*)malloc(sizeof(vertex)); 
    vertex* temp_next=(vertex*)malloc(sizeof(vertex));
    temp_next=G->adjlist[student]->nextStudent;

    aux->previousStudentGrade =  G->adjlist[friend]->previousStudentGrade;
    aux->StudentId =  friend;

    aux->nextStudent=temp_next;
    G->adjlist[student]->nextStudent=aux;
}

/*DFS Functions*/
void UpdateAllGrades(graph *G){

    int counter;
    int i;

    for(counter = 1; counter <= G->verticesNumber; counter++)
    {
        int studentId=G->adjlist[counter]->StudentId;
       
        current_grade = G->adjlist[counter]->previousStudentGrade;

        DFS_VISIT_STUDENT(G,studentId,studentId);
        G->adjlist[counter]->actualStudentGrade=current_grade;
        for(i=1;i<=G->verticesNumber;i++)
        {
            G->visited[i]=0;
        }
    }
}

          

void DFS_VISIT_STUDENT(graph * g,int studentId, int student)
{
    vertex * adjList = g->adjlist[studentId];
    vertex * temp = adjList;
    g->visited[studentId] = 1;
    if(current_grade < temp->previousStudentGrade)
    {
        current_grade= temp->previousStudentGrade;
    }
    
    while(temp!=NULL) {
        int connectedVertex = temp->StudentId;
        
        if(g->visited[connectedVertex] == 0) 
        {
            DFS_VISIT_STUDENT(g,connectedVertex,student);
        }
            temp = temp->nextStudent;
    }    
}



/*Main function*/
int main(int argc, char *argv[]){

    int studentsNumber, friendshipNumber;
    int counter=1, grade,  *PreviousGrades, student, friend;
    int i;
    scanf("%d,%d",&studentsNumber, &friendshipNumber);
    
    G = CreateGraph(studentsNumber);

    PreviousGrades = (int*) malloc((sizeof(int))*(studentsNumber+1));  

    while(counter <= studentsNumber){
       
        scanf("%d",&grade);
        PreviousGrades[counter] = grade;
        createStudentVertex(grade, G, counter);
        counter++;
    }

     
    counter=1;
    while( counter <= friendshipNumber){

        scanf("%d %d",&student, &friend);
        InsertFriendshipEdge(student, friend, G);
        counter++;
     
    }
   
    UpdateAllGrades(G);

    for(i=1;i<=studentsNumber;i++)
    {
        printf("%d\n", G->adjlist[i]->actualStudentGrade );

    }

    
    return 0;
    
       
}