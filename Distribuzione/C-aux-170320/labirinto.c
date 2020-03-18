#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int n;
    int **matrix;
    int **marcata;
    int ** S;
} labirinto_struct ;

labirinto * labirinto_new(int n) {
   // TODO: Da completare
  labirinto_struct * l = (labirinto_struct*) malloc(sizeof(labirinto_struct));
  l->n = n;

	l->matrix = (int**) malloc(n*sizeof(int*)); 
  for(int r=0; r<n; r++)	l->matrix[r] = (int*)malloc(sizeof(int)*n);
  
  for(int x=0; x<n; x++)
		for(int y=0; y<n; y++)
			l->matrix[x][y] = LABIRINTO_VUOTA;
			
	l->marcata = (int**) malloc(n*sizeof(int*)); 
  for(int r=0; r<n; r++)	l->marcata[r] = (int*)malloc(sizeof(int)*n);
  
  for(int x=0; x<n; x++)
		for(int y=0; y<n; y++)
			l->marcata[x][y] = LABIRINTO_FALSE;
			
	l->S = (int**) malloc(n*sizeof(int*)); 
  for(int r=0; r<n; r++)	l->S[r] = (int*)malloc(sizeof(int)*n);
  
  for(int x=0; x<n; x++)
		for(int y=0; y<n; y++)
			l->S[x][y] = LABIRINTO_FALSE;
  
	return l;
}

void labirinto_delete(labirinto * lab) {
    // TODO: Da completare
	labirinto_struct *l = (labirinto_struct*)lab;
  int n = l->n;
  for(int r=0; r<n; r++)	free(l->matrix[r]);
  for(int r=0; r<n; r++)	free(l->marcata[r]);
  free(l->matrix); free(l->marcata);
  free(lab);
}

void labirinto_setpiena(labirinto * lab, int r, int c) {
    // TODO: Da completare
  labirinto_struct *l = (labirinto_struct*)lab;
  l->matrix[r][c] = LABIRINTO_PIENA;
}

int labirinto_uscita(labirinto * lab, int r, int c) {
	labirinto_struct *l = (labirinto_struct*)lab;  
	int n = l->n;
	return l->matrix[n-1][n-1] == l->matrix[r][c];
}

int labirinto_percorribile(labirinto * lab, int r, int c) {
    // TODO: Da completare
  labirinto_struct *l = (labirinto_struct*)lab;  
	int n = l->n;
	if(r>=n || c>=n || r<0 || c<0)	return 0;
	int perc = l->S[r][c] == LABIRINTO_FALSE && l->matrix[r][c] == LABIRINTO_VUOTA && l->marcata[r][c] == LABIRINTO_FALSE; 
	return perc;
}



int labirinto_uscitaraggiungibileda(labirinto * lab, int r, int c) {
    // TODO: Da completare
  labirinto_struct *l = (labirinto_struct*)lab;  
	int n = l->n;
	int a = 0;
	int x = 0, y = 0;
	
	
	l->marcata[r][c] = LABIRINTO_TRUE;
	if(r==n-1 && c==n-1)	return 1;
			
	if(labirinto_percorribile(lab, r+1, c)){
		x = r+1;
		y = c;
	}	
	else if(labirinto_percorribile(lab, r, c+1)){
		x = r;
		y = c+1;
	}
	else if(labirinto_percorribile(lab, r, c-1)){
		x = r;
		y = c-1;
	}
	else if(labirinto_percorribile(lab, r-1, c)){
		x = r-1;
		y = c;
	}
	
	else if(!l->S[r][c]){
		l->S[r][c] = LABIRINTO_TRUE;
		for(int row=0; row<n; row++)
			for(int col=0; col<n; col++)
				l->marcata[row][col] = LABIRINTO_FALSE;
	}
	else{
		l->marcata[r][c] = LABIRINTO_FALSE;
		return 0;
	}
			
	return labirinto_uscitaraggiungibileda(lab, x, y);
			
}

int labirinto_risolvibile(labirinto * lab) {
    // TODO: Da completare
  return labirinto_uscitaraggiungibileda(lab, 0, 0);
}

void labirinto_tostring(labirinto * lab, char * buffer, int buffer_size) {
	labirinto_struct * ptr = (labirinto_struct *) lab;
        assert(buffer_size >= (ptr->n + 1) * ptr->n);
    buffer[0] = '\0';
    char *buffer_ptr = buffer;
    int i;
    for (i = 0; i < ptr->n; i++) {
        int j;
        for (j = 0; j < ptr->n; j++) {
            char c;
            if(ptr->matrix[i][j] == LABIRINTO_PIENA)
                c = '#';
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_FALSE)
                c = '.'; 
            if(ptr->matrix[i][j] == LABIRINTO_VUOTA && ptr->marcata[i][j] == LABIRINTO_TRUE)
                c = '+'; 
            buffer_ptr[0] = c;
            buffer_ptr++;
        }
        buffer_ptr[0] = '\n';
        buffer_ptr++;
    }
    buffer_ptr[0] = '\0';
}
