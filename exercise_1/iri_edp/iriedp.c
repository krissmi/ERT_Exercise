#include <stdio.h>
#include <stdlib.h>

#include "iri_sub.h"
#include "iri_web.h"


int main(int argc, char *argv[]) 
{
	printf("Program start\n");

	char *jf = calloc(50, sizeof(int));
	int jmag = 0; 
    float alati = 0.0f; 
	float along = 0.0f; 
    int iyyyy = 0; 
	int mmdd = 0; 
	float dhour = 0.0f; 
	float heibeg = 0.0f;
	float heiend = 0.0f;
	float heistp = 0.0f;
	float *outf = calloc(1, sizeof(float));
	float *oarr = calloc(1, sizeof(float));

	iri_sub_(jf, jmag, alati, along, iyyyy, mmdd, dhour, heibeg, heiend, heistp, outf, oarr);

	free(jf);

	return 0;
}

/* END-OF-FILE */