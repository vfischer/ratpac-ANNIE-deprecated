/** \file AmBeSource.cc
 *  AmBeSource C++ file.  Implements the constructor, copy
 *  constructor, and overloaded = operator and defines the
 *  AmBeNeutronSpectrum function.
 *
 *  Author: Vincent Fischer
 */
#include <RAT/AmBeSource.hh>

#include <G4ParticleDefinition.hh>
#include <G4Gamma.hh>
#include <G4Neutron.hh>

#include <CLHEP/Random/RandFlat.h>
#include <CLHEP/Random/RandGeneral.h>
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include <cmath>
#include <iostream>
#include <fstream>   // file I/O
#include <iomanip>   // format manipulation
#include <cstring>
#include <vector>

#undef DEBUG

namespace RAT {

  double AmBeSource::massNeutron = 0.; // allocate storage for static variable

  AmBeSource::AmBeSource()
  {
      // Verify that all maps and vectors are empty.
      Nneutron = 0;
      Ngamma = 0;
      neutronE.clear();
      Tneutron.clear();
      gammaE.clear();
      Tgamma.clear();

      // setup the probability density as a function of energy

      // Random generators according to probability densities.
      static CLHEP::RandGeneral* fGenerate = 0;

      static const float flow = 0.; static const float fhigh = 50.;

      static bool first = true;
      if (first)
	{
	  first = false;

	  // Initialize the G4 particle definitions.
	  G4ParticleDefinition* neutron = G4Neutron::Neutron();
	  massNeutron = neutron->GetPDGMass() * CLHEP::MeV;

	  // In the original code, the probability densities used the
	  // funlxp and funlux routines in CERNLIB to generate random
	  // numbers.  The following code uses CLHEP to generate the
	  // same "histograms" for the RandGeneral random-number
	  // generator.

	  const size_t probDensSize = 200;
	  double fspace[probDensSize];

#ifdef DEBUG
	  std::cout << "AmBeSource initialization" << std::endl;
#endif
	  // Find function values at bin centers.
	  for ( size_t i=0; i != probDensSize; i++ )
	    {
	      float value = (float(i) + 0.5) * (fhigh - flow) / (float) probDensSize;
	      fspace[i] = AmBeNeutronSpectrum(value);
#ifdef DEBUG
	      std::cout << "   i=" << i << " f,m,g="
			<< fspace[i] << std::endl;
#endif
	    }

	  // Define random-number generators.
	  fGenerate = new CLHEP::RandGeneral(fspace,probDensSize);

#ifdef DEBUG
	  std::cout << " Random generator test (f):" << std::endl;
	  for ( size_t i=0; i != 20; i++ )
	    {
	      std::cout << i << ": "
			<< fGenerate->shoot() * (fhigh - flow) + flow << std::endl;
	    }

#endif
	}


      // pick a neutron multiplicity					     
      Nneutron = 1; // only one neutron generated
      
      //std::cout << "   " << Nneutron << " neutrons" << std::endl;
      //
      // pick a momentum direction for each neutron
      //
      for (int nn=0; nn<Nneutron; nn++)
	{
	  double neutronKE = fGenerate->shoot() * (fhigh - flow) + flow;
// 	  G4cout << "neutronKE = " << neutronKE*CLHEP::MeV << G4endl;
	  double energy = massNeutron + neutronKE;
// 	  G4cout << "energy = " << energy*CLHEP::MeV << G4endl;
	  // Generate momentum direction uniformly in phi and cos(theta).
	  double phi = CLHEP::RandFlat::shoot(0.,M_PI);
	  double cosTheta = CLHEP::RandFlat::shoot(-1.,1.);
	  double sinTheta = sqrt( 1. - cosTheta*cosTheta );

	  // Compute the momentum squared. If it comes out negative
	  // due to roundoff errors, just set it equal to zero. This
	  // prevents problems when we take the square root below.
	  double neutronP2 = std::max(0., energy*energy
	    - massNeutron*massNeutron);

	  // Compute the momentum components
	  double neutronP = std::sqrt(neutronP2);
	  double px = neutronP * sinTheta * cos(phi);
	  double py = neutronP * sinTheta * sin(phi);
	  double pz = neutronP * cosTheta;
#ifdef DEBUG
	  std::cout << "AmBeSource::AmBeSource() - neutron energy "
		    << nn << " = " << energy
		    << ", KE=" << neutronKE
		    << ", (px,py,pz)=("
		    << px << "," << py << "," << pz << ")"
		    << std::endl;
#endif
	  CLHEP::HepLorentzVector momentum(px,py,pz,energy);
	  neutronE.push_back( momentum );
	  Tneutron.push_back( 0. );
	}

      Ngamma = 1; //only 1 gamma generated

#ifdef DEBUG
      std::cout << "AmBeSource::AmBeSource - "
		<< "m=" << m << " => "
		<< Ngamma << " photons" << std::endl;
#endif
      // pick a momentum for each gamma
      //
      double tote = 0.;
      for(int nn=0; nn<Ngamma; nn++)
	{
	  double energy = 4.43; //from the C12 firzt excited state
	  // Generate momentum direction uniformly in phi and cos(theta).
	  double phi = CLHEP::RandFlat::shoot(0.,M_PI);
	  double cosTheta = CLHEP::RandFlat::shoot(-1.,1.);
	  double sinTheta = sqrt( 1. - cosTheta*cosTheta );
	  double px = energy * sinTheta * cos(phi);
	  double py = energy * sinTheta * sin(phi);
	  double pz = energy * cosTheta;
#ifdef DEBUG
	  std::cout << "AmBeSource::AmBeSource() - gamma energy "
		    << nn << " = " << energy
		    << ", (px,py,pz)=("
		    << px << "," << py << "," << pz << ")"
		    << std::endl;
#endif
	  CLHEP::HepLorentzVector momentum(px,py,pz,energy);
	  gammaE.push_back( momentum );
	  tote += energy;

	  const size_t len2 = 2;
	  float rv[len2];
	  for ( size_t i=0; i<len2; i++ ) rv[i] = CLHEP::RandFlat::shoot();
	  //
	  // 80% of gammas have T_1/2 = 0.01 ns and 20% have T_1/2 = 1 ns
	  //
	  double halflife;
	  if(rv[0] < 0.8)
	    halflife = 0.01;
	  else
	    halflife = 1.0;
	  Tgamma.push_back( halflife*log(1/rv[1]) );
	}
      //std::cout << "          total energy = " << tote << std::endl;
  }

  AmBeSource::~AmBeSource()
  {;}

  AmBeSource::AmBeSource(const AmBeSource& _AmBeSource)
  {
    Nneutron  = _AmBeSource.Nneutron;
    Ngamma    = _AmBeSource.Ngamma;
    neutronE  = _AmBeSource.neutronE;
    Tneutron  = _AmBeSource.Tneutron;
    gammaE    = _AmBeSource.gammaE;
    Tgamma    = _AmBeSource.Tgamma;
  }

  AmBeSource& AmBeSource::operator=(const AmBeSource& rhs){

    if (this != &rhs)
      {
	Nneutron  = rhs.Nneutron;
	Ngamma    = rhs.Ngamma;
	neutronE  = rhs.neutronE;
	Tneutron  = rhs.Tneutron;
	gammaE    = rhs.gammaE;
	Tgamma    = rhs.Tgamma;
      }
    return *this;
  }

  float AmBeSource::AmBeNeutronSpectrum(const float& x){

    // return the neutron spectrum N(x)
    float N = 0.;

    float scale = 1/(2*M_PI*0.359);
    //std::cout << "scale " << scale << std::endl;

    float fminus = exp(-(sqrt(x)-sqrt(0.359))*(sqrt(x)-sqrt(0.359))/1.175);
    float fplus  = exp(-(sqrt(x)+sqrt(0.359))*(sqrt(x)+sqrt(0.359))/1.175);

    N = scale*(fminus-fplus);

    //std::cout << "N " << N << std::endl;
    return N;
  }

  float AmBeSource::AmBeGammaSpectrum(const float& x){

    // return the gamma spectrum N(x)
    float N = 0.;

    float gaussian = 1.8367*exp(-0.5*((x-0.45934)/0.31290)*((x-0.45934)/0.31290));
    float exponential = exp(0.84774-0.89396*x);

    if(x <= 0.744){
      N = gaussian;
    }
    else{
      N = exponential;
    }

    //std::cout << "N " << N << std::endl;
    return N;
  }

} // namespace RAT
