
#include <stdio.h>
#include <stdlib.h>
#include "red-black-tree.h"
#include "aeroport.h"
#include "utilitats.h"

#define MAXFILENAME 15

void printMenu() {
    printf("--------------------------------------\n");
    printf("            === MENU ===\n");
    printf("--------------------------------------\n");

    printf("\n");

    printf("1. Creació de l’arbre.\n");
    printf("2. Emmagatzemament de l’arbre.\n");
    printf("3. Lectura de l’arbre.\n");
    printf("4. Gràfica del retard mig entre dos aeroports qualsevol.\n");
    printf("5. SORTIR.\n");
}

void printGraph(FILE *pipe, ListData *data) {
    float mitja;
    fprintf(pipe, "plot '-' with lines\n");

    for (int dia=0; dia<DIES_SETMANA; dia++){
        if(data->numeroRetrasos[dia]>0){
            mitja = data->totalRetrasos[dia]/data->numeroRetrasos[dia];
        }else{
            mitja = 0;
        }
        fprintf(pipe, "%d %f\n", dia, mitja);

    }
    fflush(pipe);
    fprintf(pipe, "e\n");
}

/**
 *
 * Main function.
 *
 */

int main(int argc, char **argv) {
    FILE *fp;
    RBTree *tree;
    char * fname;
    int choice, mem;

    mem = 0;
    choice = 1;
    while(choice != 0) {
        printMenu();
        printf("Enter Choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: //CREATE TREE
                /* Reservem memoria*/
                tree = (RBTree *) malloc(sizeof(RBTree));
                fname = (char *) malloc(sizeof(char) * MAXFILENAME);

                printf("Introduce filename (Para leer de archivo [MAX %d CHAR]): ", MAXFILENAME);
                scanf("%s", fname);
                fp = fopen(fname, "r");
                if (!fp) {
                    printf("Could not open file '%s'\n", fname);
                    exit(EXIT_FAILURE);
                }

                /* Inicialitzem arbre */
                initTree(tree);
                iterate(tree, fp);

                /* Alliberem la memoria */
                fclose(fp);
                free(fname);
                mem = 1;
                break;

            case 2: //SAVE TREE
                if (mem) {
                    /* Reservem memoria*/
                    fname = (char *) malloc(sizeof(char) * MAXFILENAME);

                    printf("Introduce filename (Para guardar arbol en disco): ");
                    scanf("%s", fname);
                    fp = fopen(fname, "w");
                    if (!fp) {
                        printf("Could not open file '%s'\n", fname);
                        exit(EXIT_FAILURE);
                    }

                    /* Guardem el arbre al disc */
                    saveTree(tree, fp);

                    fclose(fp);
                    free(fname);

                } else {
                    printf("No tree saved in memory, please try OP1.\n");
                }
                break;

            case 3: //READ TREE
                /* Reservem memoria*/
                fname = (char *) malloc(sizeof(char) * MAXFILENAME);

                /* Alliberem memoria */
                if (mem) {
                    printf("Deleting previously saved tree.\n");
                    deleteTree(tree);
                    free(tree);
                    mem = 0;
                }

                printf("Introduce filename (Para cargar arbol de disco): ");
                scanf("%s", fname);
                fp = fopen(fname, "r");
                if (!fp) {
                    printf("Could not open file '%s'\n", fname);
                    exit(EXIT_FAILURE);
                }

                tree = (RBTree *) malloc (sizeof(RBTree));
                initTree(tree);

                /* Carreguem l'arbre del fitxer de disc */
                loadTree(tree, fp);

                /* Alliberem la memoria */
                fclose(fp);
                free(fname);
                mem = 1;
                break;

            case 4: //MAKE DELAY GRAPHIC [gnuplot]
                if (mem) {
                    char *key_inicio, *key_destino;
                    RBData *nodeData;
                    ListData *listData;
                    FILE *fpout;

                    key_inicio = (char *) malloc(sizeof(char) * 4);
                    key_destino = (char *) malloc(sizeof(char) * 4);

                    printf("Introduce Aeropuerto de Origen [MAX 3 Chars.]: ");
                    scanf("%s", key_inicio);
                    printf("Introduce Aeropuerto de Destino [MAX 3 Chars.]: ");
                    scanf("%s", key_destino);

                    if (strlen(key_inicio) > 3 && strlen(key_destino) > 3) {
                        printf("ERROR: clave del Aeropuerto mal introducida...\n");
                        exit(EXIT_FAILURE);
                    }

                    nodeData = findNode(tree, key_inicio);
                    if (nodeData) {
                        
                        listData = findList(nodeData->aeropuertosDestino, key_destino);
                        if (listData) {

                            fpout = popen("gnuplot -persistent", "w");
                            if (!fpout) {
                              printf("ERROR: no puc crear canonada.\n");
                              exit(EXIT_FAILURE);
                            }

                            printGraph(fpout, listData);

                            if (pclose(fpout) == -1) {
                                printf("ERROR: pclose.\n");
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            printf("Aeropuerto de Destino no es bien.\n");
                        }
                    } else {
                        printf("Aeropuerto de Origen no es bien.\n");
                    }
                    free(key_inicio);
                    free(key_destino);
                } else {
                    printf("No tree saved in memory, please try OP1.\n");
                }
                break;

            case 5: //EXIT (Bye)
                printf("Bye...\n");
                choice = 0;
                break;
        }
    }

    /* Alliberem memoria */
    if (mem) {
        deleteTree(tree);
        free(tree);
    }

    return EXIT_SUCCESS;
}
