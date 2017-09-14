/**
 *
 * Main file
 *
 * Lluis Garrido, 2016.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "linked-list.h"
#include "red-black-tree.h"

#define MAXCHAR 150

int count = 0;

/**
 *
 * This file reads and outputs the lines of a CSV file.
 *
 */
void setCount() {
    count++;
}

int getCount() {
    return count;
}

void saveLine(char ** line, RBTree *tree)
{
  RBData *treeData;
  ListData *listData;

  int lenOri = strlen(line[2]);
  int lenDest = strlen(line[3]);
  int dia = atoi(line[0]);
  int retraso = atoi(line[1]);

  if (lenOri <= 3) {

      treeData = findNode(tree, line[2]);
      if (treeData != NULL) {
        //printf("Found node %s in the Tree.\n", line[2]);
        treeData->num++;
        if (lenDest <= 3) {

            listData = findList(treeData->lista, line[3]);
            if (listData != NULL) {
              /* We increment the number of times current item has appeared */
              listData->numTimes++;
              listData->retrasos[dia] = (listData->retrasos[dia] + retraso) / 2;
              dumpList(treeData->lista);

            } else {
              /* If the key is not in the list, allocate memory for the data and
               * insert it in the list */
              treeData->lista = (List *) malloc(sizeof(List) + 1);
              initList(treeData->lista);

              listData = malloc(sizeof(ListData));
              listData->retrasos = malloc((sizeof(int) * 7) + 7);
              listData->key = line[3];
              listData->numTimes = 1;
              listData->retrasos[dia] = retraso;

              insertList(treeData->lista, listData);
              dumpList(treeData->lista);
            }
        }
      } else {
        /* If the key is not in the tree, allocate memory for the data
         * and insert in the tree */
        treeData = malloc(sizeof(RBData));
        treeData->key = line[2];
        treeData->num = 1;

        if (lenDest <= 3) {
          /* If the key is not in the list, allocate memory for the data and
           * insert it in the list */
          treeData->lista = (List *) malloc(sizeof(List) + 1);
          initList(treeData->lista);

          listData = malloc(sizeof(ListData));
          listData->retrasos = malloc((sizeof(int) * 7) + 7);
          listData->key = line[3];
          listData->numTimes = 1;
          listData->retrasos[dia] = retraso;

          insertList(treeData->lista, listData);
          dumpList(treeData->lista);
        }
        printf("Inserting node %s in the Tree.\n", line[2]);
        insertNode(tree, treeData);
        setCount();
      }
  } else {
      printf("Ignoring node %s.\n", line[2]);
  }
}


void readCSV(char *filename, RBTree *tree)
{
  FILE *fp;
  char *line;
  char *sline;

  char **info;

  line = (char *) malloc(sizeof(char) * MAXCHAR);
  sline = (char *) malloc(sizeof(char) * MAXCHAR);

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Could not open file '%s'\n", filename);
    exit(1);
  }

  info = (char **) malloc((sizeof(char*) * 4) + 2);

  while (fgets(line, MAXCHAR, fp) != NULL) {
     //printf("%s", line);
     int j;
     int i = 0;
     int col[4] = {4, 15, 17, 18};
     char *p = strtok(line, ",");
     char *array[MAXCHAR];

     while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, ",");
     }
     for (j = 0;j<4; j++) {
        info[j] = array[col[j]-1];
    }
    saveLine(info, tree); //info[0], info[1], info[2], info[3]);
  }
  free(info);
  fclose(fp);

  free(sline);
  free(line);
}

/**
 *
 * Main function.
 *
 */

int main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: %s <fitxer.txt>\n", argv[0]);
    exit(1);
  }

  RBTree *tree;

  tree = (RBTree *) malloc(sizeof(RBTree));
  initTree(tree);

  readCSV(argv[1], tree);

  printf("GOT TO THE END!\n");
  printf("COUNT: %d\n", getCount());

  deleteTree(tree);

  return 0;
}
