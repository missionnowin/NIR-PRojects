#include "KonField.hh"
#include "G4SystemOfUnits.hh"
  
 KonField::KonField()
 {
//   B1 = 0.225*tesla; //E=2.5AGeV
   B1 = 0.40*tesla;  //E=5AGeV
   Z1max = 79.*cm;
   Z1min = -170.*cm;
//   Z2max = 760.*cm;
//   Z2min = 400.*cm;
 }
 
 KonField::~KonField()
 {;}
 
 void KonField::GetFieldValue(const double Point[3],double *Bfield) const
 {
   Bfield[0] = 0.;
   Bfield[2] = 0.;
   if(Point[2]<Z1max && Point[2]>Z1min)
     {Bfield[1] = B1;}
//   else if(Point[2]<Z2max && Point[2]>Z2min)      
//     {Bfield[1] = B2;}
     else
     {Bfield[1] = 0.;}
 }



