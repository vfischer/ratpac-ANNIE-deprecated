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

      // pick a gamma multiplicity
      // According to "Progress in Nuclear Science and Technology  - Volume 4 (2014) pp. 345-348 (http://www.aesj.or.jp/publication/pnst004/data/345_348.pdf)
      // about 25% of Am-Be reactions do not emit a 4.43 MeV gamma (depends on the energy level the carbon atom is excited to after the (alpha,n) reaction)
      // This probability can be changed here is you desire
      double prob_gamma_emission = 0.75; //probability of emitted a gamma along with a neutron
      double prob_gamma = CLHEP::RandFlat::shoot(0.,1.);
      if (prob_gamma < prob_gamma_emission){
	Ngamma = 1; //only 1 gamma generated
      } else {
	Ngamma = 0; //no gamma generated
      }

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
	  double energy = 4.43; //from the C12 first excited state
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

	  // consider the gammas is emitted instantaneously (10^-15 -ish decay time)
	  Tgamma.push_back( 0. );
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

} // namespace RAT
