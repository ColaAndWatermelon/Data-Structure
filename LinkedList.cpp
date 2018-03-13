#define NULL 0
#include <stdio.h>
#include <stdlib.h>


typedef struct lnode{
     int data;
     struct lnode *next;
}lnode, *linklist;

linklist  createlistf(void)  /*��ͷ*/
  {
      int e;
      linklist  head;
      lnode  *p;
       head=NULL;
       scanf("%d",&e);
       while (e!=0){
	   p=(lnode*)malloc(sizeof(lnode));
	    p->data=e;
	    p->next=head;
            head=p;
	   scanf("%d",&e);
      } 
      return (head);
   }

void createlist_f(linklist *h)  /*��ͷ--����*/
  {
      int e;
      linklist  head;
      lnode  *p;
       head=NULL;
       scanf("%d",&e);
       while (e!=0){
	   p=(lnode*)malloc(sizeof(lnode));
	    p->data=e;
	    p->next=head;
            head=p;
	   scanf("%d",&e);
      } 
    *h=head;
 
   }

linklist createliste(void)  /*��ͷ*/
  {
      int e;
      linklist head=(linklist)malloc(sizeof(lnode));
      lnode  *p,*r;
      r=head;
      scanf("%d",&e);
      while (e!=0){
	   p=(lnode*)malloc(sizeof(lnode));
	   p->data=e;
	   r->next=p;
           r=p;
          scanf("%d",&e);
         }
       r->next=NULL;
       return (head);
   }

lnode *getnode(linklist head,int i)
   {
     int j;
     lnode *p;
     p=head;j=0;
     while(p->next && j<i){
           p=p->next;
	    j++;
          }
     if (i==j)
          return p;
      else
	 return NULL;
   }

lnode *locatenode(linklist head,int key)
  {
    lnode *p=head->next;
    while( p && p->data!=key)
        p=p->next;
    return p;
  }



void printlist(linklist head)
{
   lnode *p=head;; 
   while (p!=NULL)
   {
        printf("%d,",p->data);
        p=p->next;
    }
}

void  insertnode(linklist head,int x,int i)
    {
       lnode  *p,*q;
      p=getnode(head,i-1);
      if(p==NULL)
           {printf("��λ���޷����룡"); return;}
        q=(lnode *)malloc(sizeof(lnode));
        q->data=x;
        q->next=p->next;
        p->next=q;
      }


main()
{
     linklist headf,heade;
     lnode *p;
     int i,e;

 
     printf("\n��������1,����ֵ 0 ����:\n");
/*     headf=createlistf();   //����ֵ*/

     createlist_f(&headf);

     printlist(headf);

     printf("\n��������2,����ֵ 0 ����:\n");
     heade=createliste();
     printlist(heade->next);

     printf("\n����������2�н������²���: ");

     printf("\n�����������ֵ��λ�ã�");
     scanf("%d",&i);
     p=getnode(heade,i);
     if (p!=NULL)  printf("\n�����ҵ�ֵ��:%d\n",p->data);
	 else  printf("\n�����ҵ�ֵ�����ڣ�");


     printf("\n����������ҵ�ֵ:");
     scanf("%d",&e);
     p=locatenode(heade,e);
     if (p!=NULL)  printf("\n�����ҵ�ֵ�� :%d\n",p->data);
	 else  printf("\n�����ҵ�ֵ�����ڣ�");

     printf("\n���룺������������ֵ:");
     scanf("%d",&e);
     printf("\n���������ֵ��λ��:");
     scanf("%d",&i);
     insertnode(heade,e,i);
     printlist(heade->next);

}
