
#ifndef KonField_H
#define KonField_H 1
 
#include "globals.hh"
#include "G4MagneticField.hh"
 
 class KonField : public G4MagneticField
 {
   public:
     KonField();
     ~KonField();
 
     void GetFieldValue( const  double Point[3],
                                double *Bfield ) const;
 
   private:
     G4double Bx;
     G4double Zmin;
     G4double Zmax;
 };
 
#endif


