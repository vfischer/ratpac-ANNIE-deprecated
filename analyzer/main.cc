#include "RATPAC_analyzer.hh"

#include <TString.h>
#include <TPRegexp.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TCanvas.h>

#include <cstdlib>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h> // getopt
#include <vector>
#include <algorithm>

using namespace std;

Int_t main(Int_t argc, Char_t** argv)
{
  Char_t option;
  TString type;
  TString inpath;
  TString outpath;
  TString indir="./";
//   TString outdir="./";
  TString *outdir=0;
  
  if (argc <= 1)
  {
    std::cerr << "Hey! You need to set options, dude..\n\n"
    << "  MANDATORY:\n"
    << "-t [type]  : type of analysis: phase1, phase2 \n"
    << "   OPTIONAL:\n"
    << "-i [inpath]: path to the input (not implemented yet)\n"
    << "-p [outpath]: path to the output\n"
    << std::endl;
    exit(-1);  
  }
  
  UInt_t NbFiles=argc-1;
  vector<TString> InputFiles;
  struct stat buf;
  
  while ((option = getopt(argc,argv,"-ip:t:")) != -1)
  {
    switch (option) {
      case 't':
	type = optarg;
	NbFiles -= 2;
	break;
      case 'i':
	indir = optarg;
	NbFiles -=2;
	break;
      case 'p':
	outdir = new TString(optarg);
	NbFiles -=2;
	break;
      case '?':
	std::cerr << "\n *** Say what? Invalid option..." << std::endl;
	return -1;      
	break;
    }
  }
  
    if (outdir == 0) {
    outdir = new TString(getenv("PWD"));
  }
  
  if (!TPMERegexp("/$").Match(*outdir)) {*outdir = *outdir + "/";}
    
  // filling files vectors
  if (NbFiles > 0) { InputFiles.reserve(NbFiles); 
    cout << NbFiles << " files to analyze" << endl;}
    else { 
      cout << "no file to analyse" << endl; 
    }
    for (Int_t i=argc-NbFiles; i<argc; i++) {
      if ( stat(argv[i],&buf) == -1) { 
	cout << TString("can not 'stat' file: ") + argv[i] << endl; 
	exit(-1);
      } else {
	InputFiles.push_back( TString(argv[i]) );
      }
    }
    
    if ( InputFiles.empty() ) {
      cout << "There are no input files ====> Exit...\n";
      exit(-1);
    }
    
    // Analyzer and loops
    Analyzer * Ana;
    
    if ( type == "run1" ) {
      Ana = new Analyzer(InputFiles, "run1", *outdir);
	Ana->Initialization();
	Ana->Loop();
	Ana->Finalize();  
    } else 
    
    if ( type == "run2" ) {
      Ana = new Analyzer(InputFiles, "run2", *outdir);
	Ana->Initialization();
	Ana->Loop();
	Ana->Finalize();  
    } else {
      std::cerr << "\n *** Say what? Invalid type..." << std::endl; abort();
    }
	
    delete Ana;
	InputFiles.clear();
	delete outdir;
    
    std::cout << "\n ... End of analysis \n" << std::endl;
    return 0;
    
}