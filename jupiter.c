#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define JUPITERAU 0.0009545
#define EARTHAU 0.000003003
main()
{
 double me, ms, mj, xe, ye, vex, vey, dt = 0.0001, t=0, eper, re, jper, xj, yj, vjx, vjy, rj, rej;
 char terraarquivo[10], jupiterarquivo[10];
 int i;
 FILE *fj, *ft;
 for(i=-12;i<=12;i++){
 sprintf(terraarquivo, "terra%d.dat", i);
 sprintf(jupiterarquivo, "jupiter%d.dat", i);
 if((fj=fopen(jupiterarquivo,"w"))==NULL) printf("Fail Jupiter\n");
 if((ft=fopen(terraarquivo,"w"))==NULL) printf("Fail Terra\n");
 
 fprintf(fj,"#X\tY\tVx\tVy\tTempo\tR\tEc\n");
 fprintf(ft,"#X\tY\tVx\tVy\tTempo\tR\tEc\n");
 me=EARTHAU;
 ms=1.;
 mj=pow(10,i)JUPITERAU;
 xe=1.;
 ye=0.;
 vex=0.;
 vey=2.*M_PI;
 eper= 1.;
 jper=11.89;
 xj=5.2;
 yj=0.;
 vjx=0.;
 vjy=2.*M_PI*xj/jper;
 for(t=0.; t<jper; t+=dt)
 {
  //printf("TESTE\n");
  re=sqrt(pow(xe,2) + pow(ye,2));
  rj=sqrt(pow(xj,2) + pow(yj,2));
  
  rej=sqrt(pow(xe-xj,2)) + pow(ye-yj,2);
  
  vex = vex -4*pow(M_PI,2)*xe*dt/pow(re,3) - 4*pow(M_PI,2)*(mj/ms)*(xe-xj)*dt/pow(rej,3);
  vey = vey -4*pow(M_PI,2)*ye*dt/pow(re,3) - 4*pow(M_PI,2)*(mj/ms)*(ye-yj)*dt/pow(rej,3);
  
  vjx = vjx -4*pow(M_PI,2)*xj*dt/pow(rj,3) - 4*pow(M_PI,2)*(me/ms)*(xj-xe)*dt/pow(rej,3);
  vjy = vjy -4*pow(M_PI,2)*yj*dt/pow(rj,3) - 4*pow(M_PI,2)*(me/ms)*(yj-xe)*dt/pow(rej,3);
  
  xe=xe+vex*dt;
  ye=ye+vey*dt;
  
  xj=xj+vjx*dt;
  yj=yj+vjy*dt;
  fprintf(fj,"%g\t%g\t%g\t%g\t%g\t%g\t%g\n", xj, yj, vjx, vjy, t, rj, mj*0.5*(vjx*vjx+vjy*vjy));
  fprintf(ft,"%g\t%g\t%g\t%g\t%g\t%g\t%g\n", xe, ye, vex, vey, t, re, me*0.5*(vex*vex+vey*vey));
  
  }
  fclose(fj);
  fclose(ft);
  }
 }
