#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <stdlib.h>

typedef struct nodeT
{
    Agnode_t *node;
    int degree;

    struct nodeT *next;
} nodeT;

nodeT *alloc_node(Agnode_t *node, int degree)
{
    nodeT *new = malloc(sizeof(nodeT));
    if (!new)
    {
        printf("Alloc fault!\n");
        return NULL;
    }

    new->node = node;
    new->degree = degree;
    new->next = NULL;

    return new;
}

int agNodeDegree(Agraph_t *g, Agnode_t *node)
{
    Agedge_t *edge = agfstedge(g,node);
    if (!edge)
        return 0;
    
    int i = 1;
    while (edge = agnxtedge(g, edge, node))
        i++;
    return i;
}

int agMaxNodeDegree(Agraph_t *g, char* name)
{
    Agnode_t *node;
    int max = 0, degree;
    node = agfstnode(g);
    if (node)
    {
        max = agNodeDegree(g,node);
        strcpy(name,agnameof(node));
    }
    while (node = agnxtnode(g, node))
    {
        degree = agNodeDegree(g, node);
        if (degree > max)
        {
            max = degree;
            strcpy(name,agnameof(node));
        }
    }
    return max;
}

int maxDegreeIn(Agraph_t *g, char* name)
{
    Agnode_t *node;
    int max = 0, degree;
    node = agfstnode(g);
    if (node)
    {
        max = agdegree(g, node, 1, 0);
        strcpy(name,agnameof(node));
    }
    while (node = agnxtnode(g, node))
    {
        degree = agdegree(g, node, 1, 0);
        if (degree > max)
        {
            max = degree;
            strcpy(name,agnameof(node));
        }
    }
    return max;
}

void printNeighbours(Agraph_t *g, char*name)
{
    Agnode_t *node;
    node = agnode(g, name, 0);
    if (!node)
    { 
        printf("node doesn't exist");
        return;
    }
    Agedge_t* edge = agfstout(g, node);
    if (edge )
        printf("%s %s\n",agnameof(aghead(edge)), agnameof(agtail(edge)));
    else return;
    while(edge = agnxtout(g, edge))
        printf("%s %s\n",agnameof(aghead(edge)), agnameof(agtail(edge)));
}

void printSorted(Agraph_t *g)
{
    nodeT *L;

    Agnode_t *node = agfstnode(g);
    if (node)
    {
        L = alloc_node(node, agdegree(g, node, 1, 0));
    }
    while (node = agnxtnode(g, node))
    {
        nodeT *new = alloc_node(node, agdegree(g, node, 1, 0));

        nodeT *curr = L;
        nodeT *prev = NULL;
        while (curr)
        {
            if (new->degree < curr->degree)
                break;

            prev = curr;
            curr = curr->next;
        }

        if (!new)
        {
        }

        if (!prev)
        {
            new->next = L;
            L = new;
        }
        else
        {
            prev->next = new;
            new->next = curr;
        }
    }

    nodeT *curr = L;
    while (curr)
    {
        printf("Nume: %s, Grad: %d\n", agnameof(curr->node), curr->degree);
        curr = curr->next;
    }
}

int verifica(Agraph_t *g, char *src, char *dest)
{
    Agnode_t *src_n = agnode(g, src, 0);
    if (!src_n)
        exit(-1);
    Agnode_t *dest_n = agnode(g, dest, 0);
    if (!dest_n)
        exit(-1);

    Agedge_t *first = agfstedge(g, src_n);
    Agedge_t *second;
    while (first)
    {
        Agnode_t *nod_intermediar;
        nod_intermediar = agtail(first);
        second = agfstedge(g, nod_intermediar);
        while (second)
        {
            Agnode_t *nod_final;
            nod_final = agtail(second);
            if (nod_final == dest_n)
                return 1;
            second = agnxtedge(g, second, nod_intermediar);
        }
        first = agnxtedge(g, first, src_n);
    }

    return 0;
}
void Bonus(Agraph_t *g, Agnode_t *node)
{
    FILE *out = fopen("fisier.dot", "w");
    printf("outs\n");
    if (!node)
    {
        printf("Not here\n");
        return;
    }
    Agraph_t *new_g = agopen("new_g", Agundirected, NULL);
    if (!new_g)
    {
        printf("newg null\n");
    }

    Agnode_t *next_node = agnxtnode(g, node);

    while (next_node)
    {
        printf("outs2\n");

        if (!agedge(new_g, node, next_node, NULL, 0))
        {
            agedge(new_g, node, next_node, NULL, 1);
        }
       

        printf("outs3\n");

        node = next_node;
        printf("outs4\n");
        next_node = agnxtnode(g, next_node);
        printf("outs5\n");
    }

    agwrite(new_g, out);
}

int main(int argc, char **argv)
{
    Agraph_t *g;
    Agnode_t *srcNode, *destNode;
    Agedge_t *e;
    char buffer[100], src[40], dest[40], nameMax[40];
    int weight;

    /* Create a simple digraph */
    g = agopen("g", Agundirected, NULL);
        
    FILE *fp = fopen("graph", "rt");
    if(!fp)
    {
        printf("can't open file\n");    
        return -1;
    }
        
    while(!feof(fp))
    {
        fgets(buffer, 100, fp);
        if(buffer[0]=='\n')
            break;
        sscanf(buffer,"%s %s %d\n",src,dest,&weight);
        //printf("%s->%s(%d)\n",src,dest,weight);
        /* creates the node or returns it if it exists */        
        srcNode = agnode(g,src,1);
        destNode = agnode(g,dest,1);
        agedge(g,srcNode,destNode,NULL,1);
    }
    //printf("name:%s, max degree = %d\n", nameMax, agMaxNodeDegree(g, nameMax));
    //printNeighbours(g, "ForzaFerrari");
    printf("Nume: %s\nMax Degree: %d\n", nameMax, maxDegreeIn(g, nameMax));
    printf("Problema 2:\n");
    printSorted(g);
    printf("Problema 3: %d\n", verifica(g, "cyber", "cyberthreat"));
    Bonus(g, agnode(g, "Iran", 0));
    
    /* Just write the graph without layout */
    //agwrite(g, stdout);

    agclose(g);

    return 0;
}