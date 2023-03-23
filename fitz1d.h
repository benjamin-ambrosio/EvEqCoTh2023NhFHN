#ifndef FITZ_H
#define FITZ_H
#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>


using namespace std;
const double T=100, T0=0 ; // T=Maximal Time

const double h=0.04;//space step
const double al1=0,al2=0,be1=0,be2=0;
const double du=1.0, dv=0.0;// diffusion coefficients
const double eps=0.1;// slow fast parameter epsilon
const double A=1/eps;

const double eps2=0.02;
const double del=0.;
const double a=-1,b=1;
const double p=1.9;
const int nb=int(floor((b-a)/h)); // taille de la longueur du tableau (solution en espace)
double dt=0.00001; // pas de temps unite = 1 min
const double AA=dt*A;
double dtmin=dt;
double a0=0.52,a1=0.011, a2=1.14,k1=-1.54,k2=1.54, cg=0.7, alpha=100;

double* alea;
double* alea2;













// This class represents the solutio (u,v)(x,t) at a fixed time t
class syst {
public:
  syst();
  syst(double, double *, double *);
  syst(const syst&);
  syst& operator=(const syst&);
  syst& affect(double, double *, double *);
  syst& affect(double, double, double);
  syst& init(double, double);
  syst& init(double (*)(int), double (*)(int)); 
  void F();
 
void printu(ofstream& );
void printv(ofstream& );
  void printuv(ofstream& );

  void printt(ofstream& );
  int debut(){return t>T0;};
  int fin(){return t<T;};
 int cent(){return ((int)t==20);};
 int cent2(){return ((int)t==1090);};
  int div(){return (floor(10*t)-floor(10*(t-dt)));};
  int div2(){return ((int)(100*t)% 700)==0;};
int div3(){return ((int)(1000*t)% 100 )==0;};
int div4(){return (floor((100)*t)-floor((100)*(t-dt)));};
  ~syst();
private:
 double t;  
 double* u;
 double* v;       
};














// cubic function
double f(double x)
{return (double)(-1)*x*x*x+2.5*x;}

//cubic function
double f1(double x)
{return (double)-x*x*x+3*x;}

//derivative of f1
double df1(double x)
{return (double)-3*x*x+3;}


//cubic function
double f2(double x)
{return (double)-x*x*x+alpha*x;}

//fonction donnant la valeur du parametre c en fonction du temps et de l'espace
double c0(double t, int i)
{
return 0;
  }

//the function c1 is constant
double c1(double t, int i)
{return -1.5;
  }


double c2(double t, int i)// c2 is constabt-wise 0 at the center -1.12 anywhere else
{if ((i==(nb/2)-1)|| (i==(nb/2))|| (i==(nb/2+1)) )
return 0.0;
else 
return -1.12;
}

double c2bis(double t, int i)/
{if ((i==(nb/2)-1)|| (i==(nb/2)) )
return 0.0;
else 
return -1.12;
}

double c3(double t, int i)
{
  return p*(-pow(a+i*h,6)/6+0.4*(a+b)*pow(a+i*h,5)
  -0.25*(a*a+b*b+4*a*b)*pow(a+i*h,4)+(2/3)*(a*a*b+b*a*b)*pow(a+i*h,3)
  -0.5*(a*a*b*b)*pow(a+i*h,2));
 }

double c4(double t, int i)// polynomial function
{
    return (p/pow(a,2))*pow(a+i*h,2)*((pow(a+i*h,2)/pow(a,2))-2.0);
}

double c5(double t, int i)// polynomial function (p/a^4)x^4-2(P/a^2)x^2
{
    return (p/pow(a,4))*pow(a+i*h,4)-(2*p/pow(a,2))*pow(a+i*h,2);
}


double tau1(int i)
{if (i<(nb/2))
  return -1;
else if (i>(nb/2))
return 1;
else 
  return 0;

}


double tau0(int i)
{
  return 0;

}






//function c to be used in the .cpp
double c(double t, int i)
{     
 return c5(t,i);
}



double tau(int i)
{return tau0(i);
}

double ci1(int i)
{
    return c4(0,i);
}

double ci2(int i)
{
    return -ci1(i)*ci1(i)*ci1(i)+3*ci1(i);
}
























#endif
