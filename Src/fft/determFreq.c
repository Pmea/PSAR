#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	FILE * f=fopen("result-dft", "r");
	double seuil= 0.2;
	printf("seuil: %lf\n", seuil);
	int echan=44100 / 2;
	double tab[echan];

	char yolo[64];

	for(int i=0; i<echan; i++){
		memset(yolo, '\0', 64);
		fscanf(f, "%s", yolo);
		tab[i]=atof(yolo);
		//printf("%lf\n", tab[i]);
	}

	for(int i=1; i<echan-1; i++){
		if(tab[i] > seuil){
			//printf("%d: %lf\n",i, tab[i]);
			if( tab[i] > tab[i-1] && tab[i] > tab[i+1]){
				printf("freq fond: %d\n", i);
				//printf("%lf < %lf < %lf\n", tab[i-1], tab[i], tab[i+1]);
			}
		}
	}

}