#include <assert.h>
#include <stdio.h>

#include "max_gap.h"

int maxGap(int * array, int start, int end) {
	// TODO: Da completare
		
	int mid = (end+start)/2;
	int prev = array[mid]-array[mid-1];
	int next = array[mid+1]-array[mid];
	if(next < prev)
		return prev;
	else
		return next;
	int a = maxGap(array, start, mid-1);
	int b = maxGap(array, mid, end-1);
	if (a<b) return b;
	else return a;
}
