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
void arrayins(array *a, int e){
  if(a->used == a->size){
    a->size *= 2;
    a->at = realloc(a->at, a->size * sizeof(int));
  }
  a->at[a->used++] = e;
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
void matrixins(matrix *m,array e){
  if(m->used <=  m->size){
    m->size *= 4;
    m->at = realloc(m->at,m->size*sizeof(e));
  }
  m->at[m->used++]=e;
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
        return 1;
      }
    }
  }
  return 0;
}
matrix getsol(array*a){
  array empty,contains,temp;
  matrix sol;
  matrixinit(&sol,9);
  arrayinit(&empty,9);
  arrayinit(&temp,9);
  arrayinit(&contains,9);
  for(int i = 0; i!=9;i++){
    if(a->at[i]!=0){
      arrayins(&contains,a->at[i]);
    }else{
      arrayins(&empty,i);
    }
    
    arrayins(&temp,a->at[i]);
  }
  for(int i = 0;i!=empty.used;i++){
    printf("%i",empty.at[i]);
  }
  printf("\n%i\n",(int)empty.used);
  for(int it = 0; it != (int)empty.used; it++){
    int e = empty.at[it];
    
  }
  for(int i = 0; i != 9; i++){
    if(temp.at[i]==0){
      for(int z =1; z!= 10;z++){
        temp.at[i]=z;
        if(isvalid(&temp)==0){
          break;
        }
        temp.at[i]=0;
      }
    }
  }
  for(int ll = 0; ll!=9;ll++){
    printf("%i",temp.at[ll]);
  }

  printf("\n%i",isvalid(&temp));
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
        arrayins(&trow,puzzle[r][c]);
      }
    matrixins(&sudoku,trow);
  }
  getsol(&sudoku.at[0]);

  //arrayins(&sudoku,5);
  //printf("%d",sudoku.at[0].at[0]);
  return 0;
}

