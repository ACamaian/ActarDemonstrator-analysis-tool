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
#include <TH2.h>
#include <TH1.h>
#include <TH3.h>
#include <TProfile.h>
#include <TString.h>
#include <TSpectrum.h>
#include <TLine.h>
#include <TRandom.h>

//Per ARDA
#include "../src/cRawEvent.h"
#include "../src/cHit.h"
#include "../src/cRawSignal.h"
#include "../src/pSignal.h"

//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"

#define vdrift 0.01297 //mm/ns
#define nsample 170 //campioni
#define sampling_period 80 //ns, ie 12.5 MHz

#define nr 32
#define rinf 0
#define rup 32

#define ncol 64
#define cinf 0
#define cup 64

#define rbeam_inf 13 //
#define rbeam_up 18


#define upperlimit_time nsample*sampling_period //in ns

using namespace std;

pair<int, int> getPadFromGlobalID(int gsel, TString lookup);
pair<float, float> getXYFromGlobalID(int gsel, TString lookup);
Int_t getGlobalIdFromPad(Int_t xpad, Int_t ypad, TString lookup);


int main (int argc, char ** argv){
	
  TString fname=argv[1];
  TString ltable="LookupTable.dat";
    
  ifstream in(fname);
  if(!in.good()) cout << "Input file does not exist" << endl;

  int saveentry=5000;

  TFile *fout;  
  TTree *tout; 
  cEvent *event;
  Double_t epart0=0, theta0=0, phi0=0, x0=0;
  int idfile=0;
  

  vector<cHitxyz> event_hits;
  cHitxyz temp;
  
  string line;
  Int_t entry=0;
  TString nev="";
  Int_t event_num=0;
    
  TRandom *rand = new TRandom();
  Int_t trigger=0;
  while(getline(in,line)){
       
     if(entry==0){   
     idfile++;  
     cout << entry << " " << "Opening a new file: " << Form("../data/simul_out/%s_%d.root",fname.Data(),idfile) << endl;
      fout = new TFile (Form("../data/simul_out/%s_%d.root",fname.Data(),idfile),"RECREATE");
      tout = new TTree("EventTree_0","Simulated Event Tree with XYZ positions ");
      event = new cEvent();
  
      epart0=0, theta0=0, phi0=0, x0=0;
      tout->Branch("event", &event);
      tout->Branch("Epart0", &epart0, "Epart0/D");
      tout->Branch("Theta0", &theta0, "Theta0/D");
      tout->Branch("Phi0", &phi0, "Phi0/D");
      tout->Branch("X0", &x0, "X0/D");
      entry=0; 
      }

    if (in.eof()){ //to save the last event
      	event->setIsgood(true);
	event->setEventNumber(event_num-2);
	event->append(event_hits);
	tout->Fill();

	event->clear(); //preparing the container for the following event
	event_hits.clear();
    }
   
    
    if(line[0]==' ' && line[1]=='n'){
      
      
	event->clear(); //preparing the container for the following event
	event_hits.clear();
	trigger=0;
      
      stringstream ss;
      ss.str(line);
      nev="";
      event_num=0;
      epart0=0; 
      theta0=0; 
      phi0=0; 
      x0=0;

      ss >> nev >> event_num >> epart0 >> theta0 >> phi0 >> x0;
      x0 = x0*10;
           
      if(phi0<0) phi0 = 2*TMath::Pi() - abs(phi0);

      if(entry%100==0)cout << nev << " " << event_num << " " << epart0 << " " << theta0*180/3.14 << " " << phi0*180/3.14 << " " << x0 << endl;
      entry++;
      continue;
    }
    else if(line[0]==' ' && line[1]=='!'){
    
	if(trigger>=10){
		event->setIsgood(true);
		event->setIDCode(1);	
		}
	else{
		event->setIsgood(false);
		event->setIDCode(0);	
	}	
	//cout << event->getIDCode() << endl;
	event->setEventNumber(event_num-1);
	event->append(event_hits);
	//cout << entry << endl;
	tout->Fill();
      
      
      if(entry%saveentry==0 && entry>0) {
       fout->cd();
       tout->Write();
       fout->Close();
       cout << entry << " " << "Saving .." << endl;
       entry=0;
       continue;
      }   
    }
    else{
      stringstream ss;
      ss.str(line);
      Double_t xx=0, yy=0, zz=0, nele=0;
      Int_t xpad=0, ypad=0, zpad=0, gid=0;
      
      ss>> xx >> yy >> zz >> nele;

      xx = xx * 10;
      yy = yy * 10 + 32;
      zz = zz * 10;

      xpad= (xx-1)/2;
      ypad= (yy-1)/2;
      
      zpad= (zz)/(170/nsample);      //sampling of z direction
      zz = zpad + 0.5*(170/nsample);
      
      gid = getGlobalIdFromPad(xpad, ypad, ltable);
      
      temp.clear();
      
      if(nele==235){ //the beam
      	if(rand->Uniform(0,1)<0.7){
		temp.setPeakHeight(nele);
      		temp.setGlobalChannelId(gid);
      		temp.setPeakTime(zpad/vdrift/sampling_period);
      		temp.setXYZ(xx,yy,zz);
	}
	else continue;
      }
      else { //the alpha
      	if(nele>250){
		Int_t xpad=(xx-1)/2, ypad=(yy-1)/2;
		
		if(ypad<3) continue; //broken ASAD	
		
		if(xpad>6){
			if(ypad>4 && ypad<13) trigger++;
			if(ypad>18 && ypad<27) trigger++;
		}	
		
		temp.setPeakHeight(nele);
      		temp.setGlobalChannelId(gid);
      		temp.setPeakTime(zz/vdrift/sampling_period);
      		temp.setXYZ(xx,yy,zz);
		}
	else continue;
	}
      	
	event_hits.push_back(temp);
	
    }
    
  }
    
  delete rand;
  
  fout->cd();
  tout->Write();
  fout->Close();
}


pair<float,float> getXYFromGlobalID(int gsel, TString lookup){

  pair<int, int> col_row;
  col_row=getPadFromGlobalID(gsel,lookup);

  pair<float,float> xy;
  xy = make_pair(col_row.first+1,col_row.second+1); // in mm;

  return xy;
}

pair<int, int> getPadFromGlobalID(int gsel, TString lookup){

  ifstream in(lookup);

  pair<int,int> col_row;
  
  if(!in){
    cout << "Error while trying to open lookup table file " << lookup << endl;
    return col_row=make_pair(-1,-1);
  }

  string line;
  getline(in,line); //la prima riga è intestazione
   
  while(getline(in,line)){
    Int_t  type = -1,
      cob  = -1,
      asad = -1,
      aget = -1,
      chan = -1,
      det = -1,
      row = -1,
      col = -1,
      num = -1;
    string nom = "";
    
    if (line.length() > 0) {
      if (line[0] != '#') {
        stringstream ss;
        ss.str(line);
	ss >>type
	   >>cob
	   >>asad
	   >>aget
	   >>chan
	   >>det
	   >>row
	   >>col
	   >>num
	   >>nom;
      }
    }
    
    int gid= chan+aget*100+asad*1000+cob*10000;
    if(gid==gsel){
      col_row = make_pair(col,row);
      break;
    }
  }

  return col_row;
}


Int_t getGlobalIdFromPad(Int_t xpad, Int_t ypad, TString lookup){

  ifstream in(lookup);
  Int_t gid=0;
  

  string line;
  getline(in,line); //la prima riga è intestazione
   
  while(getline(in,line)){
    Int_t  type = -1,
      cob  = -1,
      asad = -1,
      aget = -1,
      chan = -1,
      det = -1,
      row = -1,
      col = -1,
      num = -1;
    string nom = "";
    
    if (line.length() > 0) {
      if (line[0] != '#') {
        stringstream ss;
        ss.str(line);
	ss >>type
	   >>cob
	   >>asad
	   >>aget
	   >>chan
	   >>det
	   >>row
	   >>col
	   >>num
	   >>nom;
      }
    }
    

    if(xpad==col && ypad==row){
      gid= chan+aget*100+asad*1000+cob*10000;
      break;
    }
  }

  return gid;
}

