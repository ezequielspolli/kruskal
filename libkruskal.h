#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERTICES 5

typedef int tipo_nombre;
typedef int tipo_elemento;
typedef int vertice;

typedef struct _ARISTA{
    vertice u;
    vertice v;
    int costo;
}arista;

typedef struct _RAMA{
    struct _ARISTA a;
    struct _RAMA *Sig;
}rama;

typedef struct _ENCABEZADO{
    int cuenta;
    int primer_elemento;
}encabezado;

typedef struct _NOMBRE{
    tipo_nombre nombre_conjunto;
    int siguiente_elemento;
}nombre;

typedef struct _CONJUNTO_CE{
    nombre nombres [VERTICES];
    encabezado encabezamientos_conjunto[VERTICES];
}conjunto_CE;

void inserta (int i, int j, int M_Costos, rama **arbol);
rama *obtieneRama (int i, int j, int M_Costos);
rama *suprimeRama (rama *anterior_aux);
void muestraRama (rama *arbol);
void kruskal (rama*);
void inicial (tipo_nombre, tipo_elemento, conjunto_CE*);
void combina (tipo_nombre, tipo_nombre, conjunto_CE*);
tipo_nombre encuentra (int, conjunto_CE*);
void muestraCe (conjunto_CE *cce);
void liberaArbol(rama *arbol);





