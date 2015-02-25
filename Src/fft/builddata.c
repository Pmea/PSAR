#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(int argc, char* argv[]){
	FILE *f=fopen("data-sinus.data", "w+");

	int pi=3.14159265358979323846264338327950288419716939937510;
	int echan=44100;
	double tab[echan *2];
	int freq;

	char tmp[64];


	for(int i=0; i<echan; i++){
		for(int j=1; j<argc; j++){
			freq=atoi(argv[j]);
			tab[i]+= sin((2* pi *freq*i) / (1.*echan));
		}
		sprintf(tmp,"%lf\n", tab[i]);
		fwrite(tmp, sizeof(char), strlen(tmp), f);
	}


	fclose(f);
	return EXIT_SUCCESS; 
}