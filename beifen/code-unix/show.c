#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "hardwaretime.h"
#include "show.h"
#include "virtualtimers.h"

static double initialtod=0.0;
static int maxtimers;
static double gettime(void);
static double timetodouble(long interval);

static double getrelativetime(void){
return gettime()-initialtod;
}

static double gettime(void){
double thistime=0.0;
struct timeval tval;
if(gettimeofday(&tval,NULL))
fprintf(stderr,"failed to get time of day\n");
else
thistime=tval.tv_sec+(double)tval.tv_usec/MILLION;
return thistime;
}

static void showtimerdata(void){
int i;
printf("(%d,%.3f) A:",getrunning(),timetodouble(getvalue(getrunning())));
for(i=0;i<maxtimers;i++)
if(getvalue(i)>=0)
printf(" (%d,%.3f)",i,timetodouble(getvalue(i)));
printf(" (%dE",getnumberevents());
for(i=0;i<getnumbverevents();i++)
printf(" %d",getevent(i));
printf(")\n");
}

static double timetodouble(long interval){
return (double)interval/MILLION;
}

void show(int traceflag,const char *msg,long val1,long val2,int blockedflag){
int wasblockedflag;
if(!traceflag)
return;
wasblockeflag=blockinterrupt();
printf("**** %8.4f: ",getrelativetime());
printf("%s ",msg);
if(val1>=0)
printf("%ld ",val1);
if(val2>=0)
printf("%ld ",val2);
if(blockedflag)
printf("B");
else
printf("U");
if(blockedflag!=wasblockedflag)
printf("***");
showtimerdata();
fflush(stdout);
if(!wasblockedflag)
unblockinterrupt();
}

void showinit(int maxt){
initialtod=gettime();
maxtimers=maxt;
}

