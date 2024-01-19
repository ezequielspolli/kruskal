#include "libkruskal.c"

int main (){
    int M_Costos [VERTICES] [VERTICES];
    rama *arbol= NULL;
    char continuar= 'S';
    char espacio;

    printf ("\n                   ÁRBOLES ABARCADORES DE COSTO MÍNIMO\n");
    while (continuar =='S'){
        printf ("\nPara encontrar el árbol abarcador de costo mínimo de un grafo de %d vertices:\n", VERTICES);
        printf ("\nIngrese el COSTO DE LA ARISTA entre:\n");
        for (int i = 0; i < VERTICES; i++){
            for (int j = i+1; j < VERTICES; j++){
            printf ("\n   - Los vertices %d y %d:  ", i,j);
            scanf ("%d", &M_Costos [i] [j]);
            scanf ("%c",&espacio);
            }
        }
        for (int i = 0; i <= VERTICES-1; i++){                          //La mitad inf. de diagonal de matriz
            for (int j = i+1; j < VERTICES; j++){
                if (M_Costos [i] [j] != 0){
                    inserta (i, j, M_Costos [i] [j], &arbol);             //Inserto en cola prioridad
                }
            }
        }
        kruskal (arbol);
        printf ("\n¿Desea ingresar un nuevo grafo? ('S'/'N')\n\n");
        scanf ("%c",&continuar);
        while (continuar !='S' && continuar !='N'){
            printf ("\n\nERROR al ingresar la OPCIÓN\n\n");
            printf ("¿Desea ingresar un nuevo grafo? ('S'/'N')\n\n");
            scanf ("%c",&espacio);
            scanf ("%c",&continuar);
        }
        scanf ("%c",&espacio);
    }
    printf ("\nFIN de la operación\n\n");
    return EXIT_SUCCESS;
}
