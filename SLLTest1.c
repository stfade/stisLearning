#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int num;                        
    struct node *nextptr;           
}*stnode;

void createNodeList(int n); 
void displayList();         
struct node *search(int);
void degistir(struct node *);
void displayList2();
void ekle(int,int);
void displayList3();
int main()
{
    int n,a,x,y;
    
		printf("\n\n Linked List : To create and display Singly Linked List :\n");
		printf("-------------------------------------------------------------\n");
		
    printf(" Input the number of nodes : ");
    scanf("%d", &n);
    createNodeList(n);
    printf("\n Data entered in the list : \n");
    displayList();
    printf("\n aramak istediginiz sayiyi giriniz :\n");
    scanf("%d",&a);
    struct node *temp=search(a);
    degistir(temp);
    displayList2();
    printf("\n eklemek istediginiz sayiyi giriniz :\n");
    scanf("%d",&x);
    printf("\n hangi sayidan sonra eklenecek :\n");
    scanf("%d",&y);
    ekle(x,y);
    displayList3();
    return 0;
}
void createNodeList(int n)
{
    struct node *fnNode, *tmp;
    int num, i;
    stnode = (struct node *)malloc(sizeof(struct node));

    if(stnode == NULL) 
    {
        printf(" Memory can not be allocated.");
    }
    else
    {


        printf(" Input data for node 1 : ");
        scanf("%d", &num);
        stnode->num = num;      
        stnode->nextptr = NULL; 
        tmp = stnode;

        for(i=2; i<=n; i++)
        {
            fnNode = (struct node *)malloc(sizeof(struct node));
            if(fnNode == NULL)
            {
                printf(" Memory can not be allocated.");
                break;
            }
            else
            {
                printf(" Input data for node %d : ", i);
                scanf(" %d", &num);
 
                fnNode->num = num;      
                fnNode->nextptr = NULL; 
 
                tmp->nextptr = fnNode; 
                tmp = tmp->nextptr; 
            }
        }
    }
}
void displayList()
{
    struct node *tmp;
    if(stnode == NULL)
    {
        printf(" List is empty.");
    }
    else
    {
        tmp = stnode;
        while(tmp != NULL)
        {
            printf(" Data = %d\n", tmp->num); 
            tmp = tmp->nextptr;                     
        }
    }
}
struct node *search(int a)
{	
	struct node *temp=NULL; 
	temp = stnode;		
	while (temp != NULL)   
	{
	
		if (a == temp->num) 	
		{
			return temp;
		}
		temp = temp->nextptr; 
	}
return NULL;
}
void degistir(struct node *temp)
{
	int x=0;
	printf("yeni sayiyi yazin\n");
	scanf("%d",&x);
	temp->num =x;
	printf("\nyeni sayi:%d\n",temp->num);
}
void displayList2()
{
    struct node *tmp;
    if(stnode == NULL)
    {
        printf(" List is empty.");
    }
    else
    {
        tmp = stnode;
        while(tmp != NULL)
        {
            printf(" Data = %d\n", tmp->num); 
            tmp = tmp->nextptr;                     
        }
    }
}
void ekle(int t,int s)
{
	int i;
	struct node *tutucu=NULL,*tmp=NULL;
	tmp=stnode;
	while (tmp != NULL)
	{
		if (s == tmp->num) 	
		{
			tutucu=tmp;
			tutucu = (struct node *)malloc(sizeof(struct node));
			if(tutucu == NULL) 
    			{
        			printf(" Memory can not be allocated.");
    			}
			tutucu->num =t;
			tutucu->nextptr =tmp->nextptr;
			tmp->nextptr =tutucu;
			
				
		}
		tmp = tmp->nextptr;  
	}

}
void displayList3()
{
    struct node *tmp;
    if(stnode == NULL)
    {
        printf(" List is empty.");
    }
    else
    {
        tmp = stnode;
        while(tmp != NULL)
        {
            printf(" Data = %d\n", tmp->num); 
            tmp = tmp->nextptr;                     
        }
    }
}
