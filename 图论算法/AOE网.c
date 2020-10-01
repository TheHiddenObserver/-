
#include <stdlib.h>
#include <stdio.h>
#define MAXN 50
#define MAXM 100

typedef struct e_node
		{ int adjvex;   int dur;   int act;   struct e_node *next; 
		} E_NODE;

typedef struct  
		{ int count;   E_NODE *link;
		}  V_NODE;

// ����AOE �����ڽӱ� 
int creat_adj_list(V_NODE adj[], int n) 	
	{ int  i, u, v,dur,act ; 										// �ý�����ʽ��������ͼ���ڽӱ�
	  int E[MAXN][4]={													//  AOE ���ı�
					{1,2,4,1},    {1,3,7,2},    {2,4,8,3},			//***** 
					{2,5,3,4},    {3,5,9,5},    {4,5,3,6},			//*****
					{4,6,2,7},    {5,6,6,8},    {3,6,5,9},			//*****
					{0}   			  								// �߽��� ****
				  };

	  E_NODE *p;
      for (i=1;i<=n;i++) 
		  {adj[i].count=0; adj[i].link=NULL;}
      for (i=1; i<MAXM; i++)
		  { printf("�����%d����(���,�յ�,Ȩֵ,�):", i);
            // scanf("%d,%d,%d,%d", &u, &v, &dur, &act);

	        u=E[i-1][0]; v=E[i-1][1];dur=E[i-1][2]; act=E[i-1][3];	//   ****		    		
		    printf("%d,%d,%d,%d\n",u,v,dur,act);					//   ****
		   
		    if (u<=0||v<=0) break;									// �����յ�Ϊ 0 �������� 
            p=(E_NODE *) malloc(sizeof(E_NODE));
            p->adjvex=v;
		    p->dur=dur; p->act=act;
		    p->next=adj[u].link;   
            adj[u].link=p;
		    (adj[v].count)++;
		  }
	  return(i-1); 													// ���ر���
	}

// ��� AOE �����ڽӱ� 
void prn_adj_list(V_NODE head[ ], int n)
	{ int i,w;
	  E_NODE *p;
	  printf("\n AOE ���ı�Ϊ��\n  ");
	  for (i=1; i<=n; i++)											// ����ÿ��������
		  { p=head[i].link;
       
			while (p!=NULL)
				  { w=p->adjvex; 
					printf("(v%d,v%d,a%d=%d), ",i,p->adjvex,p->act,p->dur);
					p=p->next;
				  }
			printf("\n  ");		  
	  }
	}


// �����¼������緢��ʱ�� ee 
int calculate_ee(V_NODE adj[], int tpv[], int ee[], int n) 
	{ E_NODE * t;       
	  int  i, j, k, top ;
      for (i=1; i<=n; i++)  ee[i]=0;
      
	  top=0;     
	  for (i=1; i<=n; i++)
          if (adj[i].count==0)
             { adj[i].count=top; 
               top=i; 
             }
	  i=0;
	  while (top!=0)
			{ j=top;  top=adj[top].count;
              tpv[++i]=j;  t=adj[j].link;
              while (t!=NULL)
					{ k=t->adjvex;									// ������ ee(k) ����� 
                      if (ee[k]<ee[j]+t->dur)  ee[k]=ee[j]+t->dur; 
                      if (--(adj[k].count)==0)
						 { adj[k].count=top; top=k;}
                      t=t->next;
					}
			}
	  return (i);
	}


// ���� le
void calculate_le(adj, tpv, le, path_len, n)	
	V_NODE adj[];
	int le[], tpv[], n, path_len;
	{ int  i, j, k;        E_NODE *t;
      for (i=1;i<=n;i ++) le[i]=path_len;							// le[i] ����ֵΪee[n] 
      for (i=n-1; i>0; i--)											// ����������������д���
          { k=tpv[i];  t=adj[k].link;								// ȡ�ߵĿ�ʼ����
            while (t!=NULL)
                  { j=t->adjvex; 									// ȡ�ߵĽ������� 
                    if (le[k]>le[j]-(t->dur)) 
					   le[k]=le[j]-(t->dur); 
                    t=t->next;
                  }
          }
	}


// ���������翪ʼʱ�� e
void calculate_e(adj, ee, e, n)	
    V_NODE adj[];
    int n, ee[], e[];
	{ int i, j;
      E_NODE *t;
      for (j=1;j<n;j++)
          { t=adj[j].link;
            while (t!=NULL)
                  { i=t->act;
					e[i]=ee[j];
					t=t->next;
				  }
          }
	}


// ��������ٿ�ʼʱ�� l
void calculate_l(adj, le, l, n) 	 
	V_NODE adj[];
    int n, le[], l[];
	{ int i, j, k;
      E_NODE *t;      
	  for ( k=1; k<=n; k++)
          { t=adj[k].link;
            while (t!=NULL)
                  { j=t->adjvex; i=t->act;							// ȡ�ߵ��յ㡢����
                    l[i]=le[j]-(t->dur); 							// ����ʽ���� l[i]
                    t=t->next;
                  }
           }
   }




 int main()
	{ V_NODE  head[MAXN];
	  int n=6, count, m, l[MAXM], e[MAXM], 
		  ee[MAXN], le[MAXN], tpv[MAXN], i;    						//nΪ������ 
	  m=creat_adj_list(head, n);									// �����ڽӱ�,��������ı���
      prn_adj_list(head, n);

      count=calculate_ee(head, tpv, ee, n);
      if (count<n)  
	     printf("AOE���д��ڻ�·!\n");
      else { printf("\n �¼������緢��ʱ�� ee Ϊ��");
             for (i=1;i<=n;i++)  printf("%d,", ee[i]);
             
			 calculate_le(head,tpv, le, ee[n], n);
             printf("\n\n �¼�����ٷ���ʱ�� le Ϊ��");
             for (i=1; i<=n; i++)   printf("%d,", le[i]);          

             calculate_e(head, ee, e, n);
             printf("\n\n ������翪ʼʱ��  e Ϊ��");
             for (i=1; i<=m; i++)  printf("%d,", e[i]);
             
			 calculate_l(head, le, l, n);
             printf("\n\n �����ٿ�ʼʱ��  l Ϊ��");
             for (i=1; i<=m; i++)   printf("%d,", l[i]);
             
			 printf("\n\n �������  l[i]-e[i] Ϊ��");
             for (i=1; i<=m; i++)  printf("%d,", l[i]-e[i]);
            
			 printf("\n\n �ؼ��Ϊ��");
             for (i=1;i<=m;i++) if (e[i]==l[i]) printf("a%d,",i);
             printf("\n\n ");
		  }
	}
