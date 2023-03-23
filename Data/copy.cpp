//copy files and put it in approprate format for visualization of traveling waves
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>



using namespace std;


const int nb=102;
const int NT=500;
ifstream f("fitzp=2.dat",ios::in);
ofstream g("utwp=2.dat",ios::out);
ofstream h("pair.dat",ios::out);




void recopie(void)
{  
double x=0;
for (int k=0;k<NT;k++)
  {for (int i=0;i<nb;i++)
   {f>>x;
    if (i%2 ==0)
      {cout<<"x= "<<x<< ", i= "<<i<<endl;
       } 
    else
      {
      g<<x;
       g<<" ";} 
       }
   g<<endl;
   } 

}


int main(int argc, char** argv)
{  

recopie();
f.close();
g.close();
}



