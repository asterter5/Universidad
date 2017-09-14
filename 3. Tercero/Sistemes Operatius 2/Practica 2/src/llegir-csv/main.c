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
#define HASH_SIZE  100
#define N 100

int count = 0;

void setCount() {
    count++;
}

int getCount() {
    return count;
}


/*
 *
 * 3rd Block function. Saves the extracted info from the hash table to the tree.
 *
 */
void save_to_tree(RBTree *tree, List **hash)
{
  RBData *treeData;
  ListData *hashData;
  ListData *listData;
  ListItem *listItem;

  int * retrasos = malloc((sizeof(int) * 7));
  char * origen = malloc(sizeof(char) * 4);
  char * destino = malloc(sizeof(char) * 4);

  for (int i = 0; i < HASH_SIZE; i++) {
      /* We iterate over the hash table to get the info for the tree */
      listItem = hash[i]->first;
      while (listItem != NULL) {
          //printf("%d >>> KEY %s, KEY_SEC %s\n", i, listItem->data->key, listItem->data->key_sec);
          hashData = findHash(hash[i], listItem->data->key, listItem->data->key_sec);
          memcpy(origen, hashData->key_sec, sizeof(char) * 4);
          memcpy(destino, hashData->key, sizeof(char) * 4);
          memcpy(retrasos, hashData->retrasos, sizeof(int) * 7);

          //printf("%s, %s\n", origen, destino);

          if (strlen(origen) <= 3) {
              treeData = findNode(tree, origen);
              if (treeData != NULL) {
                printf("Found node %s in the Tree.\n\n", treeData->key);
                treeData->num++;
                if (strlen(destino) <= 3) {
                    listData = findList(treeData->lista, destino);
                    if (listData != NULL) {
                      /* We increment the number of times current item has appeared */
                      listData->numTimes++;
                      memcpy(listData->retrasos, retrasos, sizeof(int) * 7);

                    } else {
                      /* If the key is not in the list, allocate memory for the data and
                       * insert it in the list */
                      treeData->lista = (List *) malloc(sizeof(List) + 1);
                      initList(treeData->lista);

                      listData = malloc(sizeof(ListData));
                      listData->retrasos = malloc(sizeof(int) * 7);
                      listData->key =  destino;
                      listData->numTimes = 1;
                      memcpy(listData->retrasos, retrasos, sizeof(int) * 7);

                      insertList(treeData->lista, listData);
                    }
                }
              } else {
                /* If the key is not in the tree, allocate memory for the data
                 * and insert in the tree */
                treeData = (RBData *) malloc(sizeof(RBData));
                treeData->key = origen;
                treeData->num = 1;

                if (strlen(destino) <= 3) {
                  /* If the key is not in the list, allocate memory for the data and
                   * insert it in the list */
                  treeData->lista = (List *) malloc(sizeof(List) + 1);
                  initList(treeData->lista);

                  listData = malloc(sizeof(ListData));
                  listData->retrasos = malloc(sizeof(int) * 7);
                  listData->key = destino;
                  listData->numTimes = 1;
                  memcpy(listData->retrasos, retrasos, sizeof(int) * 7);

                  insertList(treeData->lista, listData);
                }
                printf("Inserting node %s in the Tree.\n", treeData->key);
                insertNode(tree, treeData);
                setCount();
              }
          } else {
              printf("Ignoring node %s.\n", hashData->key_sec);
          }
          listItem = listItem->next;
      }
  }
  free(origen);
  free(destino);
  free(retrasos);
}

/*
 *
 * Function that reads a char array and transforms it into a numeric hash for indexing.
 *
 */
int get_hash(char * string)
{
    int j, len, seed, sum, h;
    char origen[4];
    strcpy(origen, string);

    len = strlen(origen);
    sum = 0;
    seed = 131;
    for(j = 0; j < len; j++)
      sum = sum * seed + (int)origen[j];

    h = sum % HASH_SIZE;
    return h;
}

/*
 *
 * 2nd Block function. Processes the linex extracted from the 'csv' file and puts the wanted info into the hash table.
 *
 */
void save_to_hash(char ** lines, List ** hash)
{
    ListData * hashData; //NOT OVERWRITE THIS VARIABLE, OR THE DATA WILL BE SMASHED
    char **info = (char **) malloc((sizeof(char*) * 4) + 2);
    int h;

    for (int idx = 0; idx <= N; idx++) {
        int col[4] = {4, 15, 17, 18}, i = 0;
        char *array[MAXCHAR];
        char *tok = lines[idx], *end = lines[idx];

        while (tok != NULL) {
            strsep(&end, ",");
            array[i++] = tok;
            tok = end;
        }

        for (int j = 0;j<4; j++) {
            info[j] = array[col[j]-1];
        }
        printf("%d, %d, %s, %s\n", atoi(info[0]), atoi(info[1]), info[2], info[3]);
        h = get_hash(info[2]);
        hashData = findHash(hash[h], info[3], info[2]);
        if (hashData != NULL) {
          /* We increment the number of times current item has appeared */
          hashData->numTimes++;
          hashData->retrasos[(atoi(info[0]) - 1)] += atoi(info[1]);

        } else {
          /* If the key is not in the list, allocate memory for the data and
           * insert it in the list */
          ListData * hashData = (ListData *) malloc(sizeof(ListData));
          hashData->retrasos = malloc(sizeof(int) * 7);
          hashData->key = info[3];
          hashData->key_sec = info[2];
          hashData->numTimes = 1;
          hashData->retrasos[(atoi(info[0]) - 1)] = atoi(info[1]);

          insertList(hash[h], hashData);
      }
    }

    free(info);
    free(hashData);

}

/*
 *
 * 1st Block function. Reads and saves 'N' lines from the 'csv' file.
 *
 */
void read_lines(char *filename, char** lines)
{
  FILE *fp;
  char *line;

  line = (char *) malloc(sizeof(char) * MAXCHAR);

  fp = fopen(filename, "r");
  if (!fp) {
    printf("Could not open file '%s'\n", filename);
    exit(1);
  }

  int n = 0;
  while (fgets(line, MAXCHAR, fp) != NULL && (n <= N)) {
    //printf("%s", line);
    lines[n] = (char *) malloc(sizeof(char) * MAXCHAR);
    memcpy(lines[n], line, sizeof(char) * MAXCHAR);
    n = n + 1;
  }
  fclose(fp);
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
  List ** hash;
  char **lines;

  tree = (RBTree *) malloc(sizeof(RBTree));
  initTree(tree);

  lines = (char **) malloc((sizeof(char *) * MAXCHAR) * N);
  read_lines(argv[1], lines);

  printf("%s\n", lines[0]);

  hash = (List **) malloc(sizeof(List *) * HASH_SIZE);
  for (int i = 0; i < HASH_SIZE; i++) {
      hash[i] = (List *) malloc(sizeof(List));
      initList(hash[i]);
  }
  save_to_hash(lines, hash);
  save_to_tree(tree, hash);

  printf("GOT TO THE END!\n");
  printf("COUNT: %d\n", getCount());

  for (int i = 0; i <= N; i++) {
      free(lines[i]);
  } free(lines);
  for (int j = 0; j < HASH_SIZE; j++) {
      deleteList(hash[j]);
      free(hash[j]);
  } free(hash);
  deleteTree(tree);

  return 0;
}
