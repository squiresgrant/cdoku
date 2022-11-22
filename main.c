#include <stdio.h>
#include <stdlib.h>
typedef struct {
  int * at;
  size_t used;
  size_t size;
} array;
void arrayinit(array *a,size_t init){
  a->at = malloc(init*sizeof(int));
  a->used = 0;
  a->size = init;
}
void arrayins(array *a, int *e){
  if(a->used == a->size){
    a->size *= 2;
    a->at = realloc(a->at, a->size * sizeof(int));
  }
  a->at[a->used++] = *e;
}
void arraykill(array *a){
    free(a->at);
    a->at = NULL;
    a->used = a->size = 0;
}
typedef struct {
  array* at;
  size_t used;
  size_t size;
} matrix;
void matrixinit(matrix *m,size_t init){
  m->at = malloc(init*sizeof(array));
  m->used = 0;
  m->size = init;
}
void matrixins(matrix *m,array*e){
  if(m->used <=  m->size){
    m->size *= 4;
    m->at = realloc(m->at,m->size*sizeof(*e));
  }
  m->at[m->used++]=*e;
}
void matrixkill(matrix*m){
  free(m->at);
  m->at = NULL;
  m->used = m->size = 0;
}
int isvalid(array*a){
  for(int i = 0;i!=a->used;i++){
    for(int z = 0;z!=a->used;z++){
      if(a->at[i]==a->at[z]&&i!=z&&a->at[i]!=0){
        return 0;
      }
    }
  }
  return 1;
}
void matrixlist(matrix*m){
  //printf("\n~ |  0  1  2  3  4  5  6  7  8  ...\n===============================\n");
  printf("\n~ | ");
  for(int i = 0; i!= m->used;i++){
    printf(" %i ",i);
  }
  printf("\n=-|-");
  for(int i = 0; i!= m->used;i++){
    printf("=-=");
  }
  printf("\n");
  for(int x = 0; x!= m->used;x++){
    printf("%i | ",x);
    for(int y =0; y!= m->at[x].used;y++){
      printf(" %i ",m->at[x].at[y]);
    }
    printf("\n");
  }
}
array array_shuffle_left(array*a){
  //array an =  a;
  int temp = a->at[0];
  array an;
  arrayinit(&an,1);
  for(int x = 0; x!=a->used; x++){
    arrayins(&an,&a->at[x+1]);
  }
  an.at[an.used-1] = temp;
  for(int x = 0; x!=a->used; x++){
    a->at[x] = an.at[x];
  }
  return an;

}

matrix array_permutations(array a){
  matrix perm;
  matrixinit(&perm,1);
  array temp = a;
  for(int i = 0; i != a.used; i++){
    array t = array_shuffle_left(&temp);
    matrixins(&perm,&t);
  }
  return perm;
}
matrix getsol(array*a){
  array a2;
  arrayinit(&a2,1);
  for(int i = 0; i!=a->used;i++){
    arrayins(&a2,&a->at[i]);
  }
  array empty,temp,needs;
  matrix sol;
  arrayinit(&empty,9);
  arrayinit(&needs,9);
  temp = a2;
  for(int i = 0; i != a2.used; i++){
    if(a2.at[i]==0){
      arrayins(&empty,&i);
      for(int z = 1;z!=10;z++){
        temp.at[i]=z;
        if(isvalid(&temp)){
          arrayins(&needs,&a2.at[i]);
          break;  
        }
        }    
    }
  }
  sol = array_permutations(needs);
  
  //printf("\nvalid? :%s",isvalid(&temp)?"true":"false");
  return sol;
}
int main(){
  matrix sudoku;
  matrixinit(&sudoku,9);
  int puzzle[9][9] = {
    {1,2,3, 4,0,5, 6,7,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
    {0,0,0, 0,0,0, 0,0,0},
  };
  
  for(int r = 0;r!=9;r++){
    array trow;
    arrayinit(&trow,1);
    for(int c = 0;c!=9;c++){
        arrayins(&trow,&puzzle[r][c]);
      }
    matrixins(&sudoku,&trow);
  }
  matrix z = getsol(&sudoku.at[0]);
  matrixlist(&z);
  //matrixlist(&sudoku);
  matrix x;
  x = array_permutations(sudoku.at[0]);
  matrixlist(&x);
  //arrayins(&sudoku,5);
  //printf("%d",sudoku.at[0].at[0]);
  return 0;
}

