#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CircularNode
{
    char *data,direction;
    int slice;
    struct CircularNode *prev;
    struct CircularNode *next;
    
} CircularNode;

CircularNode *head = NULL,*tail = NULL;
CircularNode *ptr,*first,*last;
char real_direction,dir = 'R';
int drill_run = 0;

void test(CircularNode *headptr,int turn)
{
    int i=headptr->slice;
    char direction = headptr->direction;

    printf("T");

    if(i ==-1)
    {
        printf(" DRILL");
    }

    for(i=headptr->slice ; i > 0 && turn > 0 ; i--)
    {
        if (direction == 'R')
        {
            if(!strncmp(headptr->data,"DRILL",5))
            {
                printf(" %s",headptr->data);
                break;
            }
        
            else
            {
                printf(" %s",headptr->data);
                headptr = headptr->next;
                if(i ==1)
                {
                    turn--;
                    i= headptr->slice;
                    direction = headptr->direction;
                    i++;
                }
            }
        }

        else
        {
            if(!strncmp(headptr->data,"DRILL",5))
            {
                printf(" %s",headptr->data);
                break;
            
            }
        
            else
            {
                printf(" %s",headptr->data);
                headptr = headptr->prev;
            
                if(i ==1)
                {
                    turn--;
                    i= headptr->slice;
                    direction = headptr->direction;
                    i++;
                }
            }

        }
    }

    if(!strncmp(headptr->data,"DRILL",5))
        printf("\n");
    else
    {
        printf(" %s",headptr->data);
        printf(" DRILL_NOT_FOUND\n");
    }
}

CircularNode* create(char *data,char direction,int slice)

{
    CircularNode *root =  (CircularNode *) malloc(sizeof(CircularNode));
    root->data = data;
    root->slice = slice;
    root->direction = direction;
    root->prev = NULL;
    root->next = NULL;
    return root;
}

CircularNode* deleteNode (CircularNode *ptr,char direction)
{
    CircularNode *temp= (CircularNode *) malloc(sizeof(CircularNode));
    printf("D %s %s %s\n",ptr->prev->data,ptr->data,ptr->next->data);
    temp = ptr;

    if(direction== 'L')
    {  
        ptr = ptr->next;
        ptr->prev = temp->prev;
        head=ptr;
        head->prev=tail;
        tail->next = head;
    }
    else if(direction== 'R')
    {  
        ptr = ptr->prev;
        ptr->next = temp->next;
        tail=ptr;
        head->prev=tail;
        tail->next = head;
    } 
    return ptr;
}

void control(CircularNode *headptr)
{  
    CircularNode *temp_head = headptr;
    CircularNode *temp_prev = headptr->prev;
    char *head_data = headptr->data;
    char *head_prev_data = headptr->prev->data;
    int i;
    int head_prev_num = headptr->prev->slice;
    int head_num = headptr->slice;

    printf("C");

    for (i=0; i < 1  ; headptr = headptr->next)
    {
        printf(" %s",headptr->data);  

        if(!strncmp(headptr->data,head_prev_data,20) && (head_prev_num == headptr->slice) && !strncmp(headptr->next->data,temp_prev->next->data,20) && !strncmp(headptr->prev->data,temp_prev->prev->data,20))
        {
            i++;
            headptr= headptr->prev;
        }          
    } 

    for (i=0 , headptr=headptr->prev ; i < 1  ; headptr = headptr->prev)
    {
        printf(" %s",headptr->data);   

        if(!strncmp(headptr->data,head_data,20)&& (headptr->slice == head_num) && !strncmp(headptr->next->data,temp_head->next->data,20) && !strncmp(headptr->prev->data,temp_head->prev->data,20))
        {
            i++;
            headptr=headptr->next;
        }
    }
    printf("\n");
}

void  add(char *data,char direction,char position,char dir)
{   

    ptr = create(data,direction,position);
    printf("A");
    if(!strncmp(&dir,"L",1))
    {
       if (!head) 
        {        
            head = ptr;
            head->next = head;            
            head->prev = head;
            tail = head;
            printf(" %s %s %s\n",ptr->prev->data,ptr->data,ptr->next->data);
        } 
        else 
        {
            ptr->next = head;
            head->prev = ptr;
            head=ptr;
            head->prev=tail;
            tail->next = head;
            printf(" %s %s %s\n",ptr->prev->data,ptr->data,ptr->next->data);
        }
    }
    else if(!strncmp(&dir,"R",1))
    {
        if (!tail) 
        {        
            head = ptr;
            head->next = head;            
            head->prev = head;
            tail = head;
            first = head;
            printf(" %s %s %s\n",ptr->prev->data,ptr->data,ptr->next->data);
        } 
        else 
        {
            tail->next = ptr;
            ptr->prev = tail;
            tail=ptr;
            head->prev=tail;
            tail->next = head;
            printf(" %s %s %s\n",ptr->prev->data,ptr->data,ptr->next->data);
        }
    }  
}

CircularNode * runner(CircularNode *ptr,char direction)
{   
    int i=ptr->slice;
    
    
    if(!strncmp(ptr->data,"DRILL",5))
    {
        printf("R DRILL\n");
        drill_run++;

    }
    else
    {   
        dir = ptr->direction;
        printf("R");
        if(dir== 'L')
        {  
            for (ptr = ptr->prev ; i>0  ; ptr = ptr->prev,i--)
            {
                printf(" %s",ptr->data);            
            } 
        ptr = ptr->next;
        head = ptr;
        tail = ptr->prev;
        printf("\n");
    }
        else if(dir == 'R')
        {  
            for (ptr = ptr->next  ; i >0 ; ptr = ptr->next,i--)
            {
                printf(" %s",ptr->data);            
            }
        ptr = ptr->prev;
        head = ptr->next;
        tail=ptr;
        printf("\n"); 
        
        } 
    }

    return ptr;
}

int main(void)
{

    char *operation,*task,direction;
    int l_data,slice,turn;
    int finish=0;

    for ( ;!drill_run && !finish ;)
    {
        scanf("%s",operation);

    if (!strncmp(operation,"ADD",3))
    {
        scanf("%d",&l_data);
        task = (char *) malloc(sizeof(char)*l_data);
        scanf("%s",task);
        if(!strncmp(task,"DRILL",5))
        {
            add(task,'N',-1,dir);
        }
        else
        {
            scanf(" %c",&direction);
            scanf(" %d",&slice);
            add(task,direction,slice,dir);
        }
    }
    else if (!strncmp(operation,"RUN",3))
    { 
        ptr = runner(ptr,dir);
    }
    else if (!strncmp(operation,"CONTROL",7))
    {
        control(first);
    }
    else if (!strncmp(operation,"DELETE",6))
    {
        ptr = deleteNode(ptr,dir);
    }
    else if (!strncmp(operation,"TEST",4))
    {
        scanf("%d",&turn);
        test(first,turn);
        finish++;
    }

    }
    return 0;
}
