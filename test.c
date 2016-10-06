#include <stdio.h>

int main(void){
	int result=0;
	int vector[]={1,1,0,1,1,1,1,0,1,1};
	int i;

	for (i=0;i<10;i++){
		result=result<<1;
		result=result+vector[i];
		printf("%d\n",result);
	}

}