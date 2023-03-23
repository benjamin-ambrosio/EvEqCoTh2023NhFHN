#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
int main()
{
ofstream g("fic.txt",ios::out); //this is the output file to be called by gnuplot
g<<"reset"<<endl;
g<<"set xrange [-1:1]"<<endl;
g<<"set yrange [-3:3]"<<endl;
for (int i=0;i<1000;i++)

{
//Each line or index in gnuplot represents the solution u(x,t) for fixed t. 
//We obtain a movie of the temporal evolution of u(x,t) ///////////////////////////////////////////////////
g<<"plot 'fitz.dat' ind"<<' '<<i<<' ';
g<<  "using 1:2 with lines title 't="<<((double)i)/10<<"'"<<endl; 
g<< "pause 0.1"<< endl;

}
g<<"reset"<<endl;
g.close();

// For movies in avi; not used here
// mencoder mf://*.jpg -mf w=800:h=600:fps=25:type=jpg -ovc lavc -lavcopts vcodec=mpeg4 -oac copy -o sortie.avi

}
