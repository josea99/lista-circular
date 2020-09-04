#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 25

typedef struct nodo{
	char nombre[MAX];
	int tiempo;
	struct nodo *sig;
}nodo;

nodo *creaNodo(char cadena[], int tiempo);
nodo *insertar(nodo *raiz, char cadena[], int tiempo);
void imprimir(nodo *raiz);
nodo *eliminarInicio(nodo *raiz);
nodo *eliminarFinal(nodo *raiz);
nodo *lectura(nodo *raiz, char nom[]);

int main(){
	nodo *lista = NULL;
	int op, tiempo;
	char nom[MAX];
	do{
		printf("\n\n[1] > Ingresar Nodo desde teclado\n");
		printf("[2] > Ingresar lista desde archivo\n");
		printf("[3] > Eliminar cabeza\n");
		printf("[4] > Eliminar final\n");
		printf("[5] > Mostrar lista\n");
		printf("[0] > Salir\n");
		scanf("%d", & op);
		switch(op){
			case 1:
				printf("Ingrese nombre\n");
				scanf("%s", nom);
				printf("Ingrese tiempo\n");
				scanf("%d", &tiempo);
				lista = insertar(lista, nom, tiempo);
				break;
			case 2:
				printf("Nombre del archivo\n");
				scanf("%s", nom);
				lista = lectura(lista, nom);
				break;
			case 3:
				lista = eliminarInicio(lista);
				break;
			case 4:
				lista = eliminarFinal(lista);
				break;
			case 5:
				imprimir(lista);
				break;
			case 0:
				printf("Adios\n");
				break;
			default:
				printf("Opcion no valida\n");
		}
	}while(op);
	return 0;
}

nodo *creaNodo(char cadena[], int t){
	nodo *nuevo = (nodo *)malloc(sizeof(nodo));
	strcpy(nuevo->nombre, cadena);
	nuevo->tiempo = t;
	return nuevo;
}

nodo *insertar(nodo *raiz, char cadena[], int tiempo){
	nodo *nuevo = creaNodo(cadena, tiempo);
	nodo *temp = raiz;
	if(raiz == NULL){
		raiz = nuevo;
		raiz->sig = raiz;
	}else{
		while(temp->sig != raiz){
			temp = temp->sig;
		}
		temp->sig = nuevo;
		nuevo->sig = raiz;
	}
	return raiz;
}

void imprimir(nodo *raiz){
	nodo *aux = raiz;
	if(raiz == NULL){
		printf("Lista Vacia\n");
	}else{
		do{
			printf("Nombre: %s , Tiempo: %d\n", aux->nombre, aux->tiempo);
			aux = aux->sig;
		}while(aux != raiz);
	}
}

nodo *eliminarInicio(nodo *raiz){
	nodo *aux1, *aux2;
	if(raiz == NULL){
		printf("Lista Vacia\n");
	}else{
		if(raiz->sig == raiz){
			free(raiz);
			raiz = NULL;
			printf("Cabeza borrada\n");
		}else{
			aux1 = raiz;
			while(aux1->sig != raiz){
				aux1 = aux1->sig;
			}
			aux2 = raiz;
			raiz = aux2->sig;
			aux1->sig = raiz;
			free(aux2);
			printf("Cabeza borrada\n");
		}
	}
	return raiz;
}

nodo *eliminarFinal(nodo *raiz){
	nodo *aux, *ant;
	if(raiz == NULL){
		printf("Lista vacia\n");
	}else{
		if(raiz->sig == raiz){
			free(raiz);
			raiz = NULL;
			printf("Nodo borrado\n");
		}else{
			aux = raiz;
			while(aux->sig != raiz){
				ant = aux;
				aux = aux->sig;
			}
			ant->sig = aux->sig;
			free(aux);
			printf("Ultimo nodo borrado\n");
		}
	}
	return raiz;
}

nodo *lectura(nodo *raiz, char nom[]){
	FILE *archivo;
	char nombre[MAX];
	int tiempo;
	strcat(nom, ".txt");
	archivo = fopen(nom, "r");
	if(archivo == NULL){
		perror("ERROR, archivo no existe\n");
	}else{
		while(!feof(archivo)){
			fscanf(archivo, "%s %d", nombre, &tiempo);
			raiz = insertar(raiz, nombre, tiempo);
		}
		fclose(archivo);
		printf("Recuperacion exitosa\n");
	}
	return raiz;
}