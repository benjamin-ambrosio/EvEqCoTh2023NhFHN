#include <iostream>
#include <math.h>
#include <fstream>
#include "fitz1d.h"
using namespace std; 
// This program simulates a non-homogeneous system of the Fitzhugh-Nagumo type (NhFHN) 
// \eps u'=-u^3+3u-v +du_{xx}; v'=u-c(x)
// The non-homogeneity apears with the function c 




    
        

// Laplacian with Neumann Boundary Conditions
double delta(double* x, int i)
 {
 if (i==0)
  return ((x[1]-x[0])/(h*h));
 if (i==nb)
  return ((x[nb-1]-x[nb])/(h*h));
 if ((i>0) && (i<nb)) 
   return ((x[i-1]+x[i+1]-2*x[i])/(h*h));
   }




// Constructor
syst::syst()
{ t=0;
  u= new double[nb+1];
  v= new double[nb+1]; 
  for(int i=0;i<nb+1;i++)
      {u[i]=0;
         v[i]=0;
        }
     
}




// Constructor
syst::syst(double a,double* x, double* y)
{ t=a;
  u= new double[nb+1];
  v= new double[nb+1]; 
  for(int i=0;i<nb+1;i++)
      {u[i]=x[i];
         v[i]=y[i];
        }
     
}

//Constructor
syst::syst(const syst& r)
{t=r.t;
 u= new double[nb+1];
  v= new double[nb+1]; 
 for(int i=0;i<nb+1;i++)
        {u[i]=r.u[i];
         v[i]=r.v[i];
         }
}

//overload of the operator =
syst& syst::operator=(const syst& r)
{t=r.t;
  for(int i=0;i<nb+1;i++)
   {u[i]=r.u[i];
    v[i]=r.v[i];
   }
  return *this;
}

// Assigment operator
syst& syst::affect(double a,double* x, double* y)
{t=a;
  for(int i=0;i<nb+1;i++)
    {u[i]=x[i];
     v[i]=y[i];
     }
  return *this;
}

//Second assigment operator 
syst& syst::affect(double a,double b, double c)
{t=a;
  for(int i=0;i<nb+1;i++)  
       {u[i]=b;
       v[i]=c;
       }
return *this;
}


// Initialization operator with constants
syst& syst::init(double a,double b)
{t=0;
  for(int i=0;i<nb+1;i++)  
       {u[i]=a;
       v[i]=b;
       }
return *this;
}

// second initialization operator with 
//functions *pf1 et *pf2
syst& syst::init(double(*pf1)(int k), double(*pf2)(int k))
{t=0;
  for(int i=0;i<nb+1;i++)
   {u[i]=(*pf1)(i);
    v[i]=(*pf2)(i);
    } 
  return *this;
}



//Writes the values of u in the file f 
void syst::printu(ofstream& f )
{for(int i=0;i<nb+1;i++)
    f<<a+i*h<<' '<<u[i]<<' '<<endl; 
f<<endl;
f<<endl;
}

//Writes the values of v in the file f 
void syst::printv(ofstream& f )
{for(int i=0;i<nb+1;i++)
    f<<a+i*h<<' '<<v[i]<<' '<<endl; 
f<<endl;
f<<endl;
}

//Writes the values of u and v in the file f 
void syst::printuv(ofstream& f )
{for(int i=0;i<nb+1;i++)
    f<<u[i]<<' '; 
 f<<endl<<endl;
for(int i=0;i<nb+1;i++)
    f<<v[i]<<' '; 
 f<<endl<<endl;
}




//Writes the values of u, v abd u_{xx} for some points in space. This way, we can see functions of time and trajectories in phase space for fixed space
void syst::printt(ofstream& f )
{
{f<<t<<" ";
for (int i=0;i<nb+1;i++)
f<<u[i]<<' '<<v[i]<<' '<<delta(u,i)<<' ';
f<<' ';
f<<endl;
//if (div2())    
// useful for some animations
//f<<endl<<endl;  
}
}

//destructor
syst::~syst()
{
 delete[]u;
 delete[]v;
} 




//Iterative function; uses Runge-Kutta 4 method

void syst::F()
{
double* x=new double[nb+1];
double* y=new double[nb+1];
double* yu2=new double[nb+1];
double* yu3=new double[nb+1];
double* yu4=new double[nb+1];
double* yv2=new double[nb+1];
double* yv3=new double[nb+1];
double* yv4=new double[nb+1];


for(int i=0;i<nb+1;i++)
{ 

yu2[i]=u[i]+(AA/2)*(f1(u[i])-v[i]+du*delta(u,i));
yv2[i]=v[i]+(dt/2)*(u[i]-c(t,i));
}

for(int i=0;i<nb+1;i++)
{ 
yu3[i]=u[i]+(AA/2)*(f1(yu2[i])-yv2[i]+du*delta(yu2,i));
yv3[i]=v[i]+(dt/2)*(yu2[i]-c(t,i));
}

for(int i=0;i<nb+1;i++)
{
yu4[i]=u[i]+AA*(f1(yu3[i])-yv3[i]+du*delta(yu3,i));
yv4[i]= v[i]+dt*(yu3[i]-c(t,i));
}

for(int i=0;i<nb+1;i++)
{    
x[i]=u[i]+(AA/6)*((f1(u[i])-v[i]+du*delta(u,i))
   +2*(f1(yu2[i])-yv2[i]+du*delta(yu2,i))
   +2*(f1(yu3[i])-yv3[i]+du*delta(yu3,i))
   +(f1(yu4[i])-yv4[i]+du*delta(yu4,i)));
   
y[i]=v[i]+(dt/6)*((u[i]-c(t,i))
   +2*(yu2[i]-c(t,i))
   +2*(yu3[i]-c(t,i))
   +(yu4[i]-c(t,i)));
}




 
cout<<" "<<u[0]<<" "<<u[1]<<" "<<u[nb/2]<<" "<<u[nb-1]<<" "<<u[nb]<<" "<<delta(u,0)<<" "<<delta(u,nb);
cout<<" "<<nb<<" "<<t<<endl<<endl;
 affect(t+dt,x,y); 


 delete[]x;
 delete[]y;
 delete[]yu2;
 delete[]yv2;
delete[]yu3;
 delete[]yv3;
 delete[]yu4;
 delete[]yv4;
}




  


int main()
{
ofstream g("fitz.dat",ios::out); //output for u
ofstream h("fitzev.dat",ios::out);// output for evolution and some fixed points in space
syst S;
S.init(-1.5,2.0);
//S.init(tau0,tau1);
while(S.fin())
   { S.F();
   if ((S.debut()) && (S.div4()))// we write only after some time and some values of time
   S.printt(h);
   if ((S.debut()) && (S.div())) // same thing
   S.printu(g);     
}


  g.close();
  h.close();

}
