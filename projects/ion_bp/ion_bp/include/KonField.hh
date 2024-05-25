
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
     G4double B1;
     G4double B2;
     G4double Z1min;
     G4double Z1max;
     G4double Z2min;
     G4double Z2max;
 };
 
#endif


