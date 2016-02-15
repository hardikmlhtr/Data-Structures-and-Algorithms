/* 
Date: Mon 25/Jan/16
Written by: Hardik Malhotra
For: DSA continuos evaluation
*/

#include<stdio.h>
#include<malloc.h>

void space(int n){
	int i =0;
	for (i;i<n;i++){
		printf(" ");
	}
}

int main(int args,char **argv){
	int **array, i, j, n;
	printf("Enter n \n");
	scanf("%d", &n);
	
	array = (int **) malloc (n* sizeof(int *));
	for (i=0;i<n;i++){
		array[i] = (int *) malloc((i+1) * sizeof(int));
	}

	for (i=0;i<n;i++)
	{
		for(j=0;j<i+1;j++)
		{
			if(j == 0 || j == i) array[i][j] = 1;
			else{
				array[i][j] = array[i-1][j-1] + array[i-1][j];
			}
		}
	}
	printf("\n");
	
	for(i=0;i<n; i++){
		space(n-1-i);
		for(j=0; j<i+1; j++)
		{
			printf("%d", array[i][j]);
			space(1);
		}
		printf("\n");	
	}
	printf("\n");
	return 0;
}
