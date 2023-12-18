
/*
Name: IRI_SUB (iri_sub_)
Parameters:

	jmag:   				0=GEOGRAPHIC, 1=GEOMAGNETIC COORDINATES
	alati,along   			LATITUDE NORTH AND LONGITUDE EAST IN DEGREES
	iyyyy        			YEAR AS YYYY, e.g. 1985
	mmdd (-ddd)   			DATE (OR DAY OF YEAR AS A NEGATIVE NUMBER)
	dhour         			LOCAL TIME (OR UNIVERSAL TIME + 25) IN DECIMAL HOURS
	heibeg,heiend,heistp	HEIGHT RANGE IN KM; maximal 100 heights (i.e. int((heiend-heibeg)/heistp)+1.le.100)

Addendum:

    JF switches to turn off/on (.true./.false.) several options

    i       .true.                  .false.          standard version
    -----------------------------------------------------------------
    1    Ne computed            Ne not computed                     t
    2    Te, Ti computed        Te, Ti not computed                 t
    3    Ne & Ni computed       Ni not computed                     t
    4    B0,B1 - Bil-2000       B0,B1 - other models jf(31)     false
    5    foF2 - CCIR            foF2 - URSI                     false
    6    Ni - DS-1995 & DY-1985 Ni - RBV-2010 & TBT-2015        false
    7    Ne - Tops: f10.7<188   f10.7 unlimited                     t            
    8    foF2 from model        foF2 or NmF2 - user input           t
    9    hmF2 from model        hmF2 or M3000F2 - user input        t
   10    Te - Standard          Te - Using Te/Ne correlation        t
   11    Ne - Standard Profile  Ne - Lay-function formalism         t
   12    Messages to unit 6     to messages.txt on unit 11          t
   13    foF1 from model        foF1 or NmF1 - user input           t
   14    hmF1 from model        hmF1 - user input (only Lay version)t
   15    foE  from model        foE or NmE - user input             t
   16    hmE  from model        hmE - user input                    t
   17    Rz12 from file         Rz12 - user input                   t
   18    IGRF dip, magbr, modip old FIELDG using POGO68/10 for 1973 t
   19    F1 probability model   only if foF1>0 and not NIGHT        t
   20    standard F1            standard F1 plus L condition        t
 (19,20) = (t,t) f1-prob, (t,f) f1-prob-L, (f,t) old F1, (f,f) no F1
   21    ion drift computed     ion drift not computed          false
   22    ion densities in %     ion densities in m-3                t
   23    Te_tops (Bil-1985)     Te_topside (TBT-2012)           false
   24    D-region: IRI-1990     FT-2001 and DRS-1995                t
   25    F107D from APF107.DAT  F107D user input (oarr(41))         t
   26    foF2 storm model       no storm updating                   t
   27    IG12 from file         IG12 - user                         t
   28    spread-F probability 	 not computed                    false
   29    IRI01-topside          new options as def. by JF(30)   false
   30    IRI01-topside corr.    NeQuick topside model   	     false 
 (29,30) = (t,t) IRIold, (f,t) IRIcor, (f,f) NeQuick, (t,f) IRIcor2
   31    B0,B1 ABT-2009	     B0 Gulyaeva-1987 h0.5               t   
 (4,31) = (t,t) Bil-00, (f,t) ABT-09, (f,f) Gul-87, (t,f) not used
   32    F10.7_81 from file     F10.7_81 - user input (oarr(46))    t
   33    Auroral boundary model on/off  true/false	             false
   34    Messages on            Messages off                        t
   35    foE storm model        no foE storm updating           false
   36    hmF2 w/out foF2_storm  with foF2-storm                     t
   37    topside w/out foF2-storm  with foF2-storm                  t
   38    turn WRITEs off in IRIFLIP   turn WRITEs on                t
   39    hmF2 (M3000F2)         new models                      false
   40    hmF2 AMTB-model        Shubin-COSMIC model             false
 (39,40) = (t,t) hmF2-old, (f,t) AMTB, (f,f) Shubin, (t,f) not used
   41    Use COV=F10.7_365      COV=f(IG12) (IRI before Oct 2015)   t
   42    Te with PF10.7 dep.	 w/o PF10.7 dependance               t
   43    B0 from model          B0 user input in OARR(10)           t
   44    B1 from model          B1 user input in OARR(35)           t
   45    HNEA=65/80km dya/night HNEA user input in OARR(89)         t
   46    HNEE=2000km 	         HNEE user input in OARR(90)         t
   47    CGM computation on 	 CGM computation off             false
      ....
   50    
   ------------------------------------------------------------------

  Depending on the jf() settings additional INPUT parameters may 
  be required:

       Setting              INPUT parameter
    -----------------------------------------------------------------
    jf(8)  =.false.     OARR(1)=user input for foF2/MHz or NmF2/m-3
    jf(9)  =.false.     OARR(2)=user input for hmF2/km or M(3000)F2

    jf(10 )=.false.     OARR(15),
                        OARR(16)=user input for Ne(300km), Ne(400km)/m-3. 
                        Use OARR()=-1 if one of these values is not available. 
                        If jf(23)=.false. then 
                            Ne(300km), Ne(550km)/m-3.

    jf(13) =.false.     OARR(3)=user input for foF1/MHz or NmF1/m-3 
    jf(14) =.false.     OARR(4)=user input for hmF1/km
    jf(15) =.false.     OARR(5)=user input for foE/MHz or NmE/m-3 
    jf(16) =.false.     OARR(6)=user input for hmE/km
    jf(17) =.flase.     OARR(33)=user input for Rz12
    jf(25) =.false.     OARR(41)=user input for daily F10.7 index
    jf(27) =.false.     OARR(39)=user input for IG12
    jf(32) =.false.     OARR(46)=user input for 81-day avg F10.7
    jf(43) =.false.     OARR(10)=user input for B0
    jf(44) =.false.     OARR(35)=user input for B1
    jf(45) =.false.     OARR(89)=user input for HNEA (Ne lower boundary)
    jf(46) =.false.     OARR(90)=user input for HNEE (Ne upper boundary)

===============================================================================

  OUTPUT:      
            OUTF(1:20,1:1000)
               OUTF(1,*)  ELECTRON DENSITY/M-3
               OUTF(2,*)  NEUTRAL TEMPERATURE/K
               OUTF(3,*)  ION TEMPERATURE/K
               OUTF(4,*)  ELECTRON TEMPERATURE/K
               OUTF(5,*)  O+ ION DENSITY/% or /M-3 if jf(22)=f 
               OUTF(6,*)  H+ ION DENSITY/% or /M-3 if jf(22)=f
               OUTF(7,*)  HE+ ION DENSITY/% or /M-3 if jf(22)=f
               OUTF(8,*)  O2+ ION DENSITY/% or /M-3 if jf(22)=f
               OUTF(9,*)  NO+ ION DENSITY/% or /M-3 if jf(22)=f

        IF JF(6)=.FALSE.:
               OUTF(10,*)  CLUSTER IONS DEN/% or /M-3 if jf(22)=f
               OUTF(11,*)  N+ ION DENSITY/% or /M-3 if jf(22)=f
               OUTF(12,*)  
               OUTF(13,*)  

        IF jf(24)=.FALSE.:    
                OUTF(14,1:11) standard IRI-Ne for 60,65,..,110km 
                       12:22) Friedrich (FIRI) model at these heights 
                       23:33) standard Danilov (SW=0, WA=0) 
                       34:44) for minor Stratospheric Warming (SW=0.5) 
                       45:55) for major Stratospheric Warming (SW=1) 
                       56:66) weak Winter Anomaly (WA=0.5) conditions
                       67:77) strong Winter Anomaly (WA=1) conditions

               OUTF(15-20,*)  free

===============================================================================

    OARR(1:100)   ADDITIONAL OUTPUT PARAMETERS         

        #OARR(1) = NMF2/M-3           #OARR(2) = HMF2/KM
        #OARR(3) = NMF1/M-3           #OARR(4) = HMF1/KM
        #OARR(5) = NME/M-3            #OARR(6) = HME/KM
        OARR(7) = NMD/M-3             OARR(8) = HMD/KM
        OARR(9) = HHALF/KM           #OARR(10) = B0/KM
        OARR(11) =VALLEY-BASE/M-3     OARR(12) = VALLEY-TOP/KM
        OARR(13) = TE-PEAK/K          OARR(14) = TE-PEAK HEIGHT/KM
        #OARR(15) = TE-MOD(300KM)     #OARR(16) = TE-MOD(400KM)/K
        OARR(17) = TE-MOD(600KM)      OARR(18) = TE-MOD(1400KM)/K
        OARR(19) = TE-MOD(3000KM)     OARR(20) = TE(120KM)=TN=TI/K
        OARR(21) = TI-MOD(430KM)      OARR(22) = X/KM, WHERE TE=TI
        OARR(23) = SOL ZENITH ANG/DEG OARR(24) = SUN DECLINATION/DEG
        OARR(25) = DIP/deg            OARR(26) = DIP LATITUDE/deg
        OARR(27) = MODIFIED DIP LAT.  OARR(28) = Geographic latitude
        OARR(29) = sunrise/dec. hours OARR(30) = sunset/dec. hours
        OARR(31) = ISEASON (1=spring) OARR(32) = Geographic longitude
        #OARR(33) = Rz12               OARR(34) = Covington Index
        #OARR(35) = B1                 OARR(36) = M(3000)F2
        $OARR(37) = TEC/m-2           $OARR(38) = TEC_top/TEC*100.
        #OARR(39) = gind (IG12)        OARR(40) = F1 probability 
        #OARR(41) = F10.7 daily        OARR(42) = c1 (F1 shape)
        OARR(43) = daynr              OARR(44) = equatorial vertical 
        OARR(45) = foF2_storm/foF2_quiet         ion drift in m/s
        #OARR(46) = F10.7_81           OARR(47) = foE_storm/foE_quiet 
        OARR(48) = spread-F probability          
        OARR(49) = Geomag. latitude   OARR(50) = Geomag. longitude  
        OARR(51) = ap at current time OARR(52) = daily ap
        OARR(53) = invdip/degree      OARR(54) = MLT-Te
        OARR(55) = CGM-latitude       OARR(56) = CGM-longitude
        OARR(57) = CGM-MLT            OARR(58) = CGM lat eq. aurl bodry
        OARR(59) = CGM-lati(MLT=0)    OARR(60) = CGM-lati for MLT=1
        OARR(61) = CGM-lati(MLT=2)    OARR(62) = CGM-lati for MLT=3
        OARR(63) = CGM-lati(MLT=4)    OARR(64) = CGM-lati for MLT=5
        OARR(65) = CGM-lati(MLT=6)    OARR(66) = CGM-lati for MLT=7
        OARR(67) = CGM-lati(MLT=8)    OARR(68) = CGM-lati for MLT=9
        OARR(69) = CGM-lati(MLT=10)   OARR(70) = CGM-lati for MLT=11
        OARR(71) = CGM-lati(MLT=12)   OARR(72) = CGM-lati for MLT=13
        OARR(73) = CGM-lati(MLT=14)   OARR(74) = CGM-lati for MLT=15
        OARR(75) = CGM-lati(MLT=16)   OARR(76) = CGM-lati for MLT=17
        OARR(77) = CGM-lati(MLT=18)   OARR(78) = CGM-lati for MLT=19
        OARR(79) = CGM-lati(MLT=20)   OARR(80) = CGM-lati for MLT=21
        OARR(81) = CGM-lati(MLT=22)   OARR(82) = CGM-lati for MLT=23
        OARR(83) = Kp at current time OARR(84) = magnetic declination 
        OARR(85) = L-value            OARR(86) = dipole moment 
        OARR(87) = SAX300             OARR(88) = SUX300 
        #OARR(89) = HNEA              #OARR(90) = HNEE 
                    # INPUT as well as OUTPUT parameter
                    $ special for IRIWeb (only place-holders)
            for more details got to end of subroutine
*/
extern void iri_sub_(char *jf, int jmag, 
                        float alati, float along, 
                        int iyyyy, int mmdd, float dhour, float 
                        heibeg, float heiend, float heistp, float *outf, float *oarr);

/* END-OF-FILE */