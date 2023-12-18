
/*
Name IRI_SUB (iri_sub_)
Parameters:
jmag:   				0=GEOGRAPHIC, 1=GEOMAGNETIC COORDINATES
	alati,along   			LATITUDE NORTH AND LONGITUDE EAST IN DEGREES
	iyyyy        			YEAR AS YYYY, e.g. 1985
	mmdd (-ddd)   			DATE (OR DAY OF YEAR AS A NEGATIVE NUMBER)
	dhour         			LOCAL TIME (OR UNIVERSAL TIME + 25) IN DECIMAL HOURS
	heibeg,heiend,heistp	HEIGHT RANGE IN KM; maximal 100 heights (i.e. int((heiend-heibeg)/heistp)+1.le.100)
*/
extern void iri_web_(int jmag, char *jf, float 
                        alati, float along, 
                        int iyyyy, int mmdd, 
                        int iut, float dhour, float height, float h_tec_max, int ivar, 
                        float vbeg, float vend, float vstp, float a, float b);

/* END-OF-FILE */