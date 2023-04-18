//Per C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <map>

//Per ROOT
#include <TROOT.h>
#include <TSystem.h>
#include <TGClient.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>
#include <TH1.h>
#include <TH3.h>
#include <TProfile.h>
#include <TString.h>
#include <TSpectrum.h>
#include <TLine.h>
#include <TGraph2D.h>

#define vdrift 0.01297 //mm/ns
#define nsample 512 //campioni
#define sampling_period 80 //ns, ie 12.5 MHz

using namespace std;

//Defined class
#include "../../src/cHitxyz.h"
#include "../../src/cEvent.h"

Float_t DegToRad(){return 1 * 180./TMath::Pi();}
Float_t RadToDeg(){return 1 * TMath::Pi()/180.;}

void check_ev(){

    TFile *f= new TFile("/home/camaiani/ATS_ne20/data/HoughFile_010.root");	
    TTree *t = (TTree*)f->Get("HoughEventTree_852");
    
    TTreeReader r(t);
    TTreeReaderValue<vector<cHitxyz>> hits(r,"hits");
    
    while(r.Next()){
      
       	double xx=0, yy=0, zz=0, ee=0;
	for(auto &&hit: *hits){
		vector<double> pos=hit.getXYZ();
		double eres=hit.getPeakHeight();
		
		if(xx==pos[0] && yy==pos[1] && zz==pos[2] && ee==eres){
		    cout << "DOPPIONE " << endl;
			}
		else{
		    xx=pos[0]; yy=pos[1]; zz=pos[2]; ee=eres;
		}
	}
	
     }
      

  
}
