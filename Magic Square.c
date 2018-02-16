/*Author: Ioannis Gylaris
* Date: 16/02/18
* Purpose: constructing a magic square of odd order
*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE -1
#define FALSE 0

typedef struct{
      int row,col;
}cursor; //current location in the square being examined

int** init(int n){ //initializes the square
    int i,j;
    int** sq = (int**)malloc(n*sizeof(int*));
    if(!sq){ //if memory allocation failed...
        printf("Something went wrong");
        return NULL;
    }
    for(i=0;i<n;i++){
       sq[i]=(int*)malloc(n*sizeof(int)); //allocate memory for each row and its elements
       if(!sq[i]){
         printf("Something went wrong");
         free(sq);
         return NULL;
       }
    }
    for(i=0;i<n;i++){
       for(j=0;j<n;j++){
          sq[i][j]=0; //fill the square with 0s
       }
    }
    return sq;
}

void destroy(int** sq,int n){ //frees up all of the allocated space
     int i;
     for(i=0;i<n;i++){
        free(sq[i]);
     }
     free(sq);
}

void print(int** sq,int n){
     int i,j;
     for(i=0;i<n;i++){ //rows
         for(j=0;j<n;j++){ //columns
             printf("%d \t",sq[i][j]);
         }
         printf("\n"); //prepare for the new row
     }
     printf("\n");
}

cursor moveUpRight(cursor mCursor,int n){
   if(mCursor.row-1<0){ //if we move outside of the square wrap around to the last row
      mCursor.row=n-1;
   }else{
      mCursor.row--; //else move up one row
   }
   if(mCursor.col+1>n-1){ //if we move outside of the square wrap around to the first column
      mCursor.col=0;
   }else{
      mCursor.col++; //else move one column to the right
   }
   return mCursor; //return the updated location
}

cursor moveDown(cursor mCursor,int n){
     if(mCursor.row+1>n-1){ //if we passed the final row
        mCursor.row=0;     //return to the first row of the square
     }else{
        mCursor.row++;    //otherwise move down 1 row
     }
     return mCursor;     //return the updated location inside the square
}

int isEmpty (int ** sq,cursor mCursor){ //returns true if a location is empty otherwise it returns false
     if(sq[mCursor.row][mCursor.col] == 0){
        return TRUE;
     }
     return FALSE;
}

void makeMagicSquare(int** sq,int n){ //this method follows the standard algorithm for creating a magic square of odd order
     cursor mCursor;
     mCursor.row=0;
     mCursor.col=n/2;
     int counter = 1; //actual value being placed at each position of the square
     while(1){
       sq[mCursor.row][mCursor.col]=counter;
       counter++;
       cursor tmp=moveUpRight(mCursor,n);
       if(isEmpty(sq,tmp) == FALSE){ //if location is not empty
          tmp = moveDown(mCursor,n); //move down one square
          if(isEmpty(sq,tmp) == FALSE){ //if this is not empty either finish
             return;
          }else{
             mCursor=tmp;
          }
       }else{
          mCursor=tmp;
       }
     }
}

int main(){
   int n = 0; //size of square n x n
   do{
     printf("Please enter an odd number\n");
     scanf("%d",&n);
     if(n<=0){
        printf("The number cannot be zero or negative,please try again\n");
     }else if(n%2==0){
        printf("The number that you have entered is not odd, please try again\n");
     }else{
        break;
     }
   }while(1);
   int** sq=init(n);
   makeMagicSquare(sq,n);
   print(sq,n);
   destroy(sq,n);
}

