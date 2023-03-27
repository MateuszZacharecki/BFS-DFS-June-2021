#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6

typedef struct element {
  int data;
  struct element *next;
} element, *list;

void ini(list *h)
// initialization of one-way list
{
  *h = NULL;
}

list newl(int a)
// creating element of one-way list
{
  list u;
  u = malloc(sizeof(element));
  u->next = NULL;
  u->data = a;
  return u;
}

void add(list *h, list u)
// adding element to one-way list
{
  u->next = *h;
  *h = u;
}

void print_list(list u)
// printing one-way list
{
  while (u != NULL)
  {
    printf("%d ", u->data);
    u = u->next;
  }
  printf("\n");
}

void print_graph(list G[])
{
  int i;
  printf("\n");
  for (i = 0; i < N; i++)
  {
    printf("%3d: ", i);
    print_list(G[i]);
  }
}

list* load()
{
    FILE *f;
    int a;
    f=fopen("data.txt", "r");
    list *G;
    G=malloc(sizeof(list)*N);
    for(int i=0; i<N; i++)
    {
        ini(&G[i]);
    }

    for(int i=0; i<N; i++)
    {
        fscanf(f, "%d", &a);
        while(a!=-1)
        {
            add(&G[i],newl(a));
            fscanf(f, "%d", &a);
        }
    }
    fclose(f);
    return G;
}

void delet(list *w)
// deleting first element of one-way list
// if exists
{
    list u;
    if (*w!=NULL)
    {
        u=*w;
        *w=(*w)->next;
        free(u);
    }
}

void path(int P[], int s, int v)
{
    if (v==s) printf("%d ",s);
    else if (P[v]==-1) printf("There is no path.");
    else
    {
        path(P,s,P[v]);
        printf("%d ",v);
    }
}

int acyclic(list G[])
{
    int p;
    int colour[N];
    list k;
    int P[N];
    for (int i=0;i<N;i++)
    {
        P[i]=-1;
        colour[i]=0;
    }
    for (int i=0;i<N;i++)
    {
        p=i;
        k=G[p];
        while (colour[i]!=2)
        {
            if (k!=NULL)
            {
                if (colour[k->data]==0)
                {
                    colour[k->data]=1;
                    P[k->data]=p;
                    p=k->data;
                    k=G[p];
                }
                else if (colour[k->data]==1) return 0;
                else k=k->next;
            }
            else
            {
                colour[p]=2;
                if (p!=i)
                {
                    k=G[P[p]];
                    p=P[p];
                }
            }
        }
    }
    return 1;
}

void sort(list G[], list *u)
{
    int p;
    list k;
    int P[N], colour[N];
    for (int i=0;i<N;i++)
    {
        P[i]=-1;
        colour[i]=0;
    }
    for (int i=0;i<N;i++)
    {
        p=i;
        k=G[p];
        while (colour[i]!=1)
        {
            if (k!=NULL)
            {
                if (colour[k->data]==0)
                {
                    P[k->data]=p;
                    p=k->data;
                    k=G[p];
                }
                else k=k->next;
            }
            else
            {
                colour[p]=1;
                add(u,newl(p));
                if (p!=i)
                {
                    k=G[P[p]];
                    p=P[p];
                }
            }
        }
    }
}

void BFS(list G[], int s, int k)
// The shortest path
{
    list q;
    ini(&q);
    list h, t, pom;
    list c;
    int P[N];
    int colour[N];
    for (int i=0;i<N;i++)
    {
        P[i]=-1;
        colour[i]=0;
    }
    add(&q,newl(s));
    h=q;
    t=q;
    while (h!=NULL && colour[k]!=1)
    {
        c=G[h->data];
        while (c!=NULL)
        {
            if (colour[c->data]==0 && k!=c->data)
            {
                add(&(t->next),newl(c->data));
                P[c->data]=h->data;
                colour[c->data]=1;
                t=t->next;
                c=c->next;
            }
            else if (k==c->data)
            {
                P[c->data]=h->data;
                c=NULL;
                colour[k]=1;
            }
            else c=c->next;
        }
        pom=h;
        h=h->next;
        delet(&pom);
    }
    printf("The shortest path: ");
    path(P,s,k);
    printf("\n");
}

void DFS(list G[])
// Topological sorting
{
    list q;
    ini(&q);
    if (acyclic(G)==1)
    {
        sort(G,&q);
        printf("Topological sorting: ");
        while (q!=NULL)
        {
            printf ("%d ", q->data);
            q=q->next;
        }
    }
    else printf("Graph is cyclic. ");
}

int main()
{
  list *G;
  G=load();
  printf("Graph:");
  print_graph(G);
  BFS(G,3,2);
  DFS(G);

return 0;
}
