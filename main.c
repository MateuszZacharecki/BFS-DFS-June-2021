#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 6

//Mateusz Zacharecki
//polecenie nr 1

typedef struct element {
  int data;
  struct element *next;
} element, *list;

void ini(list *h)
// inicjalizacja listy 1-kierunkowej
{
  *h = NULL;
}

list nowy(int a)
// tworzenie elementu listy 1-kierunkowej
{
  list u;
  u = malloc(sizeof(element));
  u->next = NULL;
  u->data = a;
  return u;
}

void dodaj(list *h, list u)
// dodawanie elementu do listy 1-kierunkowej
{
  u->next = *h;
  *h = u;
}

void druk_list(list u)
// wypisanie listy 1-kierunkowej
{
  while (u != NULL)
  {
    printf("%d ", u->data);
    u = u->next;
  }
  printf("\n");
}

void druk_graph(list G[])
{
  int i;
  printf("\n");
  for (i = 0; i < N; i++)
  {
    printf("%3d: ", i);
    druk_list(G[i]);
  }
}

list* wczytaj()
{
    FILE *f;
    int a;
    f=fopen("dane.txt", "r");
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
            dodaj(&G[i],nowy(a));
            fscanf(f, "%d", &a);
        }
    }
    fclose(f);
    return G;
}

void usun(list *w)
//usuwanie pierwszego elementu z listy 1-kierunkowej
//o ile istnieje
{
    list u;
    if (*w!=NULL)
    {
        u=*w;
        *w=(*w)->next;
        free(u);
    }
}

void sciezka (int P[], int s, int v)
{
    if (v==s) printf("%d ",s);
    else if (P[v]==-1) printf("Nie ma sciezki.");
    else
    {
        sciezka(P,s,P[v]);
        printf("%d ",v);
    }
}

void BFS(list G[], int s, int k)
{
    list q;
    ini(&q);
    list h, t, pom;
    list c;
    int P[N];
    int kolor[N];
    for (int i=0;i<N;i++)
    {
        P[i]=-1;
        kolor[i]=0;
    }
    dodaj(&q,nowy(s));
    h=q;
    t=q;
    while (h!=NULL && kolor[k]!=1)
    {
        c=G[h->data];
        while (c!=NULL)
        {
            if (kolor[c->data]==0 && k!=c->data)
            {
                dodaj(&(t->next),nowy(c->data));
                P[c->data]=h->data;
                kolor[c->data]=1;
                t=t->next;
                c=c->next;
            }
            else if (k==c->data)
            {
                P[c->data]=h->data;
                c=NULL;
                kolor[k]=1;
            }
            else c=c->next;
        }

        //kolor[h->data]=2;
        pom=h;
        h=h->next;
        usun(&pom);
    }
    printf("Najkrotsza droga: ");
    sciezka(P,s,k);
    printf("\n");
}

void DFS(list G[])
{
    list q;
    ini(&q);
    if (czy_acykliczny(G)==1)
    {
        sortowanie(G,&q);
        printf("Sortowanie topologiczne: ");
        while (q!=NULL)
        {
            printf ("%d ", q->data);
            q=q->next;
        }
    }
    else printf("Graf jest cykliczny ");
}

void sortowanie(list G[], list *u)
{
    int p;
    list k;
    int P[N], kolor[N];
    for (int i=0;i<N;i++)
    {
        P[i]=-1;
        kolor[i]=0;
    }
    for (int i=0;i<N;i++)
    {
        p=i;
        k=G[p];
        while (kolor[i]!=1)
        {
            if (k!=NULL)
            {
                if (kolor[k->data]==0)
                {
                    P[k->data]=p;
                    p=k->data;
                    k=G[p];
                }
                else k=k->next;
            }
            else
            {
                kolor[p]=1;
                dodaj(u,nowy(p));
                if (p!=i)
                {
                    k=G[P[p]];
                    p=P[p];
                }
            }
        }
    }
}

int czy_acykliczny(list G[])
{
    int p;
    int kolor[N];
    list k;
    int P[N];
    for (int i=0;i<N;i++)
    {
        P[i]=-1;
        kolor[i]=0;
    }
    for (int i=0;i<N;i++)
    {
        p=i;
        k=G[p];
        while (kolor[i]!=2)
        {
            if (k!=NULL)
            {
                if (kolor[k->data]==0)
                {
                    kolor[k->data]=1;
                    P[k->data]=p;
                    p=k->data;
                    k=G[p];
                }
                else if (kolor[k->data]==1) return 0;
                else k=k->next;
            }
            else
            {
                kolor[p]=2;
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

int main()
{
  list *G;
  G=wczytaj();
  printf("Graf:");
  druk_graph(G);
  BFS(G,3,2);
  DFS(G);

return 0;
}
