#include "libkruskal.h"

//FUNCTIONS
void inserta (int i, int j, int M_Costos, rama **arbol){
    rama *NuevaRama = obtieneRama (i, j, M_Costos);
    if (*arbol == NULL){                                                    //SI arbol = NULL
        *arbol = NuevaRama;
        return;
    }
    if ((*arbol)-> a.costo > NuevaRama->a.costo) {                          //Si se agrega una Arista al comienzo del arbol
        NuevaRama-> Sig = *arbol;
        *arbol= NuevaRama;
        return;
    }
    rama *tmp = *arbol;                                                     //Si se agrega la nueva rama en otra posicion del arbol
    rama *next = (*arbol)->Sig;
    while (tmp->Sig != NULL) {
        if (tmp->Sig-> a.costo > NuevaRama-> a.costo) {
                NuevaRama ->Sig = next;
                tmp-> Sig = NuevaRama;
                return;
        }
        tmp = next;
        next= next->Sig;
    }
    tmp->Sig = NuevaRama;                                                   // Si se agrega la nueva rama al final del arbol
    NuevaRama->Sig = NULL;
    return;
}

rama *obtieneRama (int i, int j, int M_Costos){
    rama *NuevaRama = malloc(sizeof(rama));                                 // Reserva memoria para una rama
    if (NuevaRama == NULL){
        printf("Error al reservar memoria\n\n");
        return NULL;
    }
    NuevaRama-> a.u = i;                                                    // Asigna valores a la rama creada
    NuevaRama-> a.v = j;
    NuevaRama-> a.costo = M_Costos;
    NuevaRama-> Sig = NULL;
    return NuevaRama;
}

rama *suprimeRama (rama *anterior){
    rama *actual= anterior->Sig;
    anterior->Sig = actual->Sig;
    free(actual);
    return anterior;
}

void muestraRama (rama *arbol){
    rama *tmp = arbol;
    while (tmp != NULL) {
        printf ("\n   - Los VERTICES %d y %d, de COSTO %d\n",tmp->a.u, tmp->a.v, tmp->a.costo);
        tmp= tmp->Sig;
    }
    return;
}

void kruskal (rama* arbol){
    conjunto_CE cce;                                                 //Inicializa cce
    tipo_elemento vert [VERTICES];
    tipo_nombre name [VERTICES];
    for (int i = 0; i < VERTICES; i++){
        vert [i] = i;
        name [i] = i;
        inicial (name [i], vert [i], &cce);
    }
    rama *anterior = arbol;
    rama *actual= arbol->Sig;
    int count = 0;
    tipo_nombre conjuntoU = encuentra (anterior->a.u, &cce);         //Primer arista siempre se combina porque TODOS los vertices estan grupos distintos
    tipo_nombre conjuntoV = encuentra (anterior->a.v, &cce);
    combina (conjuntoU,conjuntoV,&cce);
    count++;
    while (actual != NULL && count < VERTICES-1){                    //Recorre el arbol
        tipo_nombre conjuntoU = encuentra (actual->a.u, &cce);
        tipo_nombre conjuntoV = encuentra (actual->a.v, &cce);
        if (conjuntoU != conjuntoV) {                                //Si la arista forma parte del grafo abarcador
            combina (conjuntoU,conjuntoV,&cce);
            count++;
        } else {                                                     //Si la arista no forma parte del grafo abarcador
            actual = suprimeRama (anterior);
        }
        anterior = actual;
        actual = actual->Sig;
    }
    if (count < VERTICES-1 ){                                        //Obtenido el grafo abarcador
        printf ("\n\nEl grafo ingresado NO ES CONEXO\n");               //Si NO es conexo
    } else {
        anterior->Sig = NULL;                                           //Si es conexo
        liberaArbol(actual);                                                //Elimina y libera todas las aristas restantes
        printf ("\n\nEl grafo abarcador de MENOR COSTO esta conformado por LAS ARISTAS entre:\n");
        muestraRama (arbol);                                                //Muestra las aristas que conforman el grafo obtenido
    }
    liberaArbol(arbol);                                              //libera la memoria asignada al arbol
    return;
}

void inicial (tipo_nombre name, tipo_elemento vert, conjunto_CE *cce){
    cce-> nombres [vert]. nombre_conjunto = name;
    cce-> nombres [vert].siguiente_elemento = -1;
    cce-> encabezamientos_conjunto [name].cuenta =1;
    cce-> encabezamientos_conjunto [name].primer_elemento = vert;
}

tipo_nombre encuentra (int vert, conjunto_CE*cce){
    tipo_nombre conjunto = cce->nombres [vert].nombre_conjunto;
    return conjunto;
}

void combina (tipo_nombre u, tipo_nombre v, conjunto_CE *cce){
    int cuenta_u = cce->encabezamientos_conjunto [u].cuenta;
    int cuenta_v = cce->encabezamientos_conjunto [v].cuenta;
    int primer_elemento_u = cce->encabezamientos_conjunto [u].primer_elemento;
    int primer_elemento_v = cce->encabezamientos_conjunto [v].primer_elemento;
    if (cuenta_u > cuenta_v){                                           // u + v
        int temp_u = u;
        int final_u = cce->nombres[u].siguiente_elemento;
        while (final_u >= 0){                                               //Recorro buscando final de U
            temp_u = final_u;
            final_u = cce->nombres[temp_u].siguiente_elemento;
        }
        cce->nombres [temp_u].siguiente_elemento = v;                       //Anexo el principio de V al final de U
        cce->nombres [v].nombre_conjunto = u;
        int next_v = cce->nombres[v].siguiente_elemento;
        while (next_v >= 0){                                                //Recorro los elemntos de V modificando su nombre de conjunto
            cce->nombres [next_v].nombre_conjunto = u;
            next_v = cce->nombres[next_v].siguiente_elemento;
        }
        cuenta_u += cuenta_v;                                               //Cuenta de elementos en U+V
        cce->encabezamientos_conjunto [u].cuenta = cuenta_u;
        cce->encabezamientos_conjunto [v].cuenta = 0;                       //Conjunto V queda vacio
        cce->encabezamientos_conjunto [v].primer_elemento= -1;              //Conjunto V sin elementos
    }else{                                                              // v + u
        int temp_v = v;
        int final_v = cce->nombres[v].siguiente_elemento;
        while (final_v >= 0){                                               //Recorro buscando final de V
            temp_v = final_v;
            final_v = cce->nombres[temp_v].siguiente_elemento;
        }
        cce->nombres [temp_v].siguiente_elemento = u;                       //Anexo el principio de U al final de V
        cce->nombres [u].nombre_conjunto = v;
        int next_u = cce->nombres[u].siguiente_elemento;
        while (next_u >= 0){                                                //Recorro los elemntos de U modificando su nombre de conjunto
            cce->nombres [next_u].nombre_conjunto = v;
            next_u = cce->nombres[next_u].siguiente_elemento;
        }
        cuenta_v += cuenta_u;                                               //Cuenta de elementos en V+U
        cce->encabezamientos_conjunto [v].cuenta = cuenta_v;
        cce->encabezamientos_conjunto [u].cuenta = 0;                       //Conjunto U queda vacio
        cce->encabezamientos_conjunto [u].primer_elemento= -1;              //Conjunto U sin elementos
    }
    return;
}

void muestraCe (conjunto_CE *cce){
    printf ("ENCABEZAMIENTO\n\n");
    printf ("Cuenta\n");
    for (int i = 0; i < VERTICES; i++){
        printf ("%d  ",cce->encabezamientos_conjunto [i].cuenta);
    }
    printf ("\n\nPrimer elemento\n");
    for (int i = 0; i < VERTICES; i++){
        printf ("%d  ",cce->encabezamientos_conjunto [i].primer_elemento);
    }
    printf ("\n\nNOMBRES");
    printf ("\n\nNombre Conjunto\n");
    for (int i = 0; i < VERTICES; i++){
        printf ("%d  ",cce->nombres [i].nombre_conjunto);
    }

    printf ("\n\nSiguiente Elemento\n");
    for (int i = 0; i < VERTICES; i++){
        printf ("%d  ",cce->nombres [i].siguiente_elemento);
    }
    return;
}

void liberaArbol(rama *arbol){
    if (arbol == NULL){                                      //Si Arbol = NULL
        return;
    }
    rama *tmp = arbol;
    rama *next = arbol->Sig;
    while (next != NULL) {                                  //Recorre y Libera la memoria asignada al arbol
        free (tmp);
        tmp= next;
        next= next->Sig;
    }
    free (tmp);
    tmp= NULL;
    next= NULL;
    return;
}


