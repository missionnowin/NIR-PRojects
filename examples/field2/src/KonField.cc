#include "KonField.hh"
#include "G4SystemOfUnits.hh"

KonField::KonField()
{
	Bx = 6.0 * tesla;
	Zmax = 15. * cm;
	Zmin = -15. * cm;
}

KonField::~KonField()
{
	;
}

void KonField::GetFieldValue(const double Point[3], double* Bfield) const
{
	Bfield[2] = 0.;
	Bfield[1] = 0.;
	if (Point[2]<Zmax && Point[2]>Zmin)
		//   { Bfield[0] = Bx*Point[2]; }
	{
		Bfield[0] = Bx;
	}
	else
	{
		Bfield[0] = 0.;
	}
}







