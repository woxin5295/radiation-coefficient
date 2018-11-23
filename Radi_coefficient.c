/* This is a simple c  for calculating the theory radiation coefficient of upgoing p,sv,sh wave.

According to the formulas 4.89, 4.90, 4.91. (Aki,2002. Quantitative seismology)

2018-11-20 Updating by Junqing Liu (刘俊清)
Email:woxin5295@yahoo.com
*/

/***************************/
Cp  : P wave radiation coefficient.
Csv : SV wave radiation coefficient.
Csh : SH wave radiation coefficient.
/***************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#define PI 3.1415926

int main(int argc, char *argv[])
{
	int i,phi,azi,lat;
	float strike,dip,rake,Cp,Csv,Csh,iup,phiup;
	
	if (argc != 5)
	{
			fprintf(stderr,"Usage: %s strike dip rake p\n", argv[0]);
			fprintf(stderr,"   Or: %s strike dip rake sv\n", argv[0]);
			fprintf(stderr,"   Or: %s strike dip rake sh\n", argv[0]);
			exit(1); 
	}			
	
	
	strike=atoi(argv[1])*PI/180;
	   dip=atoi(argv[2])*PI/180;
	  rake=atoi(argv[3])*PI/180;
	  	
	printf("%c",argv[4]);
	
	for (i=0;i<=90;i++) {
	
		iup=i*PI/180;
		lat=-i;  /* For '-JS' projection of GMT */

		for (phi=0;phi<360;phi++) {
		
			phiup=phi*PI/180;
						
			Cp=cos(rake)*sin(dip)*sin(iup)*sin(iup)*sin(2*(phiup-strike)) \
			   -cos(rake)*cos(dip)*sin(2*iup)*cos(phiup-strike) \
			   +sin(rake)*sin(2*dip)*(cos(iup)*cos(iup)-sin(iup)*sin(iup)*sin(phiup-strike)*sin(phiup-strike)) \
			   +sin(rake)*cos(2*dip)*sin(2*iup)*sin(phiup-strike);
			
			Csv=sin(rake)*cos(2*dip)*cos(2*iup)*sin(phiup-strike) \
			   -cos(rake)*cos(dip)*cos(2*iup)*cos(phiup-strike) \
			   +0.5*cos(rake)*sin(dip)*sin(2*iup)*sin(2*(phiup-strike)) \
			   -0.5*sin(rake)*sin(2*dip)*sin(2*iup)*(1+sin(phiup-strike)*sin(phiup-strike));
			   
			Csh=cos(rake)*cos(dip)*cos(iup)*sin(phiup-strike) \
			   +cos(rake)*sin(dip)*sin(iup)*cos(2*(phiup-strike)) \
			   +sin(rake)*cos(2*dip)*cos(iup)*cos(phiup-strike) \
			   -0.5*sin(rake)*sin(2*(dip))*sin(iup)*sin(2*(phiup-strike)) ;
			
						   
			 Cp=fabs(Cp);
			Csv=fabs(Csv);
			Csh=fabs(Csh);
// the follow codes only for upgoing waves.			
			if(phi>180) {
				
				azi=phi-180;
			}
			else {
			
				azi=(180+phi);
			}

			if(strcmp(argv[4],"p")  == 0) {printf("%3d %3d %4.3f\n",azi,lat,Cp); }
			if(strcmp(argv[4],"sv") == 0) {printf("%3d %3d %4.3f\n",azi,lat,Csv);}
			if(strcmp(argv[4],"sh") == 0) {printf("%3d %3d %4.3f\n",azi,lat,Csh);}
			
		}
		
	}
			

    return 0;
}
