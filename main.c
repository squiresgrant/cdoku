#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
  int valid; //make this 0 when you wanna forgor it
} matrix;
void matrixinit(matrix *m,size_t init){
  m->at = malloc(init*sizeof(array));
  m->used = 0;
  m->size = init;
  m->valid = 0;
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
int isvalid(array a){
  for(int i = 0;i!=a.used;i++){
    for(int z = 0;z!=a.used;z++){
      if(a.at[i]==a.at[z]&&i!=z&&a.at[i]!=0){
        return 0;
      }
    }
  }
  return 1;
}
void matrixlist(matrix m){
  //printf("\n~ |  0  1  2  3  4  5  6  7  8  ...\n===============================\n");
  printf("\n~ | ");
  for(int i = 0; i!= m.used;i++){
    printf(" %i ",i);
  }
  printf("\n=-|-");
  for(int i = 0; i!= m.used;i++){
    printf("=-=");
  }
  printf("\n");
  for(int x = 0; x!= m.used;x++){
    printf("%i | ",x);
    for(int y =0; y!= m.at[x].used;y++){
      printf(" %i ",m.at[x].at[y]);
    }
    printf("\n");
  }
}
void arraylist(array a){
  printf("\n~ | ");
  for(int x = 0; x!=a.used;x++){
    printf(" %i ", a.at[x]);
  }
}
array array_shuffle_left(array*a){
  //array an =  a;
  int temp = a->at[0];
  array an;
  arrayinit(&an,1);
  for(int x = 0; x!=a->used; x++){
    arrayins(&an,a->at[x+1]);
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
    matrixins(&perm,t);
  }
  return perm;
}
array rowtocol(matrix m,int col){
  array a;
  arrayinit(&a,1);
  for(int x = 0; x!= m.used; x++){
    arrayins(&a,m.at[x].at[col]);
  }
  return a;
}

array getsquare(matrix q, int n){//only works with 9x9 probably
  array sq;
  arrayinit(&sq,1);
  int i = 0;
  int i2 = 0;
  switch(n){
    case 1:
      i = 3;
    break;
    case 2:
      i =6;
    break;
    case 3:
      i2 = 3;
    case 4:
      i2 = 3;
      i = 3;
    break;
    case 5:
      i2 = 3;
      i = 6;
    break;
    case 6:
      i2 =6;
    break;
    case 7:
      i2 =6;
      i = 3;
    break;
    case 8:
      i2=6;
      i=6;
    break;
  }
  //arrayins(&sq)
  int a1 = i + 0;
  int a2 = i2 + 0;

  int b1 = i + 1;
  int b2 = i2 + 0;

  int c1 = i + 2;
  int c2 = i2 + 1;

  int d1 = i + 0;
  int d2 = i2 + 1;

  int e1 = i + 1;
  int e2 = i2 + 1;

  int f1 = i + 2;
  int f2 = i2 + 1;

  int g1 = i + 0;
  int g2 = i2 + 2;

  int h1 = i + 1;
  int h2 = i2 + 2;

  int j1 = i + 2;
  int j2 = i2 + 2;
  arrayins(&sq,q.at[a2].at[a1]);
  arrayins(&sq,q.at[b2].at[b1]);
  arrayins(&sq,q.at[c2].at[c1]);
  arrayins(&sq,q.at[d2].at[d1]);
  arrayins(&sq,q.at[e2].at[e1]);
  arrayins(&sq,q.at[f2].at[f1]);
  arrayins(&sq,q.at[g2].at[g1]);
  arrayins(&sq,q.at[h2].at[h1]);
  arrayins(&sq,q.at[j2].at[j1]);
  return sq;
}
matrix getposible(array a){
  array a2;
  arrayinit(&a2,1);
  for(int i = 0; i!=a.used;i++){
    arrayins(&a2,a.at[i]);
  }
  array empty,temp,needs;
  matrix sol;
  arrayinit(&empty,9);
  arrayinit(&needs,9);
  temp = a2;
  for(int i = 0; i != a2.used; i++){
    if(a2.at[i]==0){
      arrayins(&empty,i);
      for(int z = 1;z!=10;z++){
        temp.at[i]=z;
        if(isvalid(temp)){
          arrayins(&needs,a2.at[i]);
          break;  
        }
        }    
    }
  }
  sol = array_permutations(needs);
  
  //printf("\nvalid? :%s",isvalid(&temp)?"true":"false");
  return sol;
}
int isMvalid(matrix q){
  array temp;
  arrayinit(&temp, 1);
  for(int x = 0; x!= q.used;x++){
    array t1 = rowtocol(q,x);
    array t2 = getsquare(q,x);
    //arraylist(t2);
    if(0==isvalid(q.at[x])||0==isvalid(t1)||0==isvalid(t2)){
      return 1;
    }
  }
  return 0;
}
matrix bruteforce(matrix q){
  array temp = {q.at[0].at,5,5};
  //matrixcopy(&temp,q);
  //memcpy(&temp, &q, sizeof(q));
  q.at[0].at[0]=5;
  arraylist(temp);
  
  return q;
}
int main(){
  matrix sudoku;
  matrixinit(&sudoku,9);
  int puzzle[9][9] = {
    {1,2,3, 4,0,0, 5,6,0},
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
  /*
    *everything before this is only 
    *to initialize the 'matrix' object as a sudoku puzzle
    *that the program can read
  */
  clock_t t;
  t = clock();
  //printf("\n%i\n",isMvalid(sudoku));
  bruteforce(sudoku);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  printf("took %f seconds",time_taken);
  return 0;
}

