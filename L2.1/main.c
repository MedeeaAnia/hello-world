#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char*name;
    float price;
    int amount;
    int manData;
    int expData;
    struct node *left, *right;
} NodeT;

NodeT *pRoot;

NodeT *createNode(NodeT *pRoot,char name[30],float price, int amount, int manData, int expData)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    p->name=(char*)calloc(30,sizeof(char));
    strcpy(p->name,name);
    p->price=price;
    p->amount=amount;
    p->manData=manData;
    p->expData=expData;
    p->left=p->right=NULL;
    return p;
}
void insert(NodeT *r, NodeT *p)
{
    if(strcmp(r->name,p->name)>0)
    {
        if(r->left==NULL)
            r->left=p;
        else
            insert(r->left,p);
    }
    else
    {
        if(r->right==NULL)
            r->right=p;
        else
            insert(p->right,p);
    }
}
NodeT *findMin(NodeT* pRoot, NodeT* r)
{
    if(r->left)
        findMin(pRoot,r->left);
    else
        return r;
}
NodeT *deleteNode(NodeT *pRoot, NodeT *p, char* name)
{
    if(p==NULL)
    {
        printf("Nu exista");
    }
    else
    {
        if(strcmp(p->name,name)>0)
            deleteNode(pRoot,p->left,name);
        else
        {
            if(strcmp(p->name,name)<0)
               deleteNode(pRoot,p->right,name);
            else
            {
                if(p->left&&p->right)
                {
                    NodeT *aux=findMin(pRoot,p->right);
                    strcpy(p->name,aux->name);
                    p->price=aux->price;
                    p->amount=aux->amount;
                    p->manData=aux->manData;
                    p->expData=aux->expData;
                    p->right=deleteNode(pRoot,p->right,aux->name);
                }
                else
                {

                    NodeT *aux=p;
                    if(p->left)
                        p=p->left;
                    else
                        p=p->right;
                    free(aux);
                }
            }
        }
    }
     return p;
}

void findNode(NodeT *pRoot, NodeT *p, char name[30],char NewName[30],float price, int amount, int manData, int expData)
{
    if(strcmp(p->name,name)>0)
    {

        if(p->left)
            findNode(pRoot,p->left,name,NewName,price,amount,manData,expData);
        else
            printf("NU EXISTA");
    }
    else
    {
        if(strcmp(p->name,name)<0)
        {
            if(p->right)
                findNode(pRoot,p->right,name,NewName,price,amount,manData,expData);
            else
                printf("NU EXISTA");
        }
        else
        {
            if(NewName[0]!='*')
        {
            if(price!=-1)
                    p->price=price;
                if(amount!=-1)
                    p->amount=amount;
                if(manData!=-1)
                    p->manData=manData;
                if(expData!=-1)
                    p->expData=expData;
                NodeT *q=createNode(pRoot,NewName,p->price,p->amount,p->manData,p->expData);
                insert(pRoot,q);
                pRoot=deleteNode(pRoot,pRoot,name);
                //insert(pRoot,q);
            }
            else
            {

                if(price!=-1)
                    p->price=price;
                if(amount!=-1)
                    p->amount=amount;
                if(manData!=-1)
                    p->manData=manData;
                if(expData!=-1)
                    p->expData=expData;



            }
        }
    }

}

void preorder(NodeT *p)
{
    if(p)
    {
        printf("%s ",p->name);
        preorder(p->left);
        preorder(p->right);
    }
}
int main()
{
    NodeT *pRoot=(NodeT*)malloc(sizeof(NodeT));
    pRoot=NULL;
    char* s,*nume,*numeNou;
    s=(char*)calloc(100,sizeof(char));
    nume=(char*)calloc(30,sizeof(char));
    numeNou=(char*)calloc(30,sizeof(char));
    float pret;
    int cant,d1,d2;
    FILE* fp;
    char* tok;
    fp=fopen("data.in","r");
    while(fgets(s,100,fp))
    {
        switch(s[0])
        {
        case 'i':
            tok=strtok(s+1,",");
            strcpy(nume,tok);
            tok=strtok(NULL,",");
            pret=atof(tok);
            tok=strtok(NULL,",");
            cant=atoi(tok);
            tok=strtok(NULL,",");
            d1=atoi(tok);
            tok=strtok(NULL,",");
            d2=atoi(tok);
            if(pRoot==NULL)
            {
                pRoot=createNode(pRoot,nume,pret,cant,d1,d2);
            }
            else
            {
                NodeT *q=createNode(pRoot,nume,pret,cant,d1,d2);
                insert(pRoot,q);
            }
            break;
        case 'd':
            tok=strtok(s+1,",");
            strcpy(nume,tok);
            pRoot=deleteNode(pRoot,pRoot,nume);
            break;
        case 'u':
            tok=strtok(s+1,",");
            strcpy(nume,tok);
            tok=strtok(NULL,",");
            if(tok=='~')
                strcpy(numeNou,"*");
            else
                strcpy(numeNou,tok);
            tok=strtok(NULL,",");
            if(tok=='~')
                pret=-1;
            else
                pret=atof(tok);
            tok=strtok(NULL,",");
            if(tok=='~')
                cant=-1;
            else
                cant=atoi(tok);
            tok=strtok(NULL,",");
            if(tok=='~')
                d1=-1;
            else
                d1=atoi(tok);
            tok=strtok(NULL,",");
            if(tok=='~')
                d2=-1;
            else
                d2=atoi(tok);
            findNode(pRoot,pRoot,nume,numeNou,pret,cant,d1,d2);
            break;
        default:
            exit(1);
        }

    }
    printf("\n");
    preorder(pRoot);



    return 0;
}
