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
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TString.h>
#include <TGraph2DErrors.h>

//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"

#define vdrift 0.01297 //mm/ns
#define tsample 80 //ns
#define nsample 512 //campioni

#define beampos 120 // mm, posizione fascio

#define nr 32
#define rinf 0
#define rup 32

#define ncol 64
#define cinf 0
#define cup 64

#define rbeam_inf 13 //
#define rbeam_up 18

using namespace std;

void clean_th1(TH1* h);
void clean_th2(TH2* h);
void clean_th3(TH3* h);


void terminal_input(Int_t event, Int_t x, Int_t y, TObject *selected);
TH3F* build_tpc(TString lookup);

int ica;
string in;

void shotrack(TString fname="../data/ACTAR_852.root_clean.root", TString tname="CleanEventTree", bool wr=false, TString ltable="../LookupTable.dat"){
  
  TFile *f = new TFile(fname,"R");
  TTree *t = (TTree*)f->Get(tname);
  
  TTreeReader myReader(t);
  TTreeReaderValue<int> evnum(myReader,"eventnum");
  TTreeReaderValue<vector<cHitxyz>> hits(myReader,"hits");

  
  TCanvas *c0 = new TCanvas ("c0","c0",1800,700);
  c0->Divide(3,1);
  TH3F *tpc=new TH3F("tpc","tpc",64,0,128,32,0,64,170,0,170);
  
  TH2F *hzy  = new TH2F("hzy","hzy",32,0,64,170,0,170);
  hzy->SetYTitle("ns");
  hzy->SetXTitle("y [mm]");
  TH2F *hyx  = new TH2F("hzy","hzy",64,0,128,32,0,64);
  hyx->SetYTitle("y [mm]");
  hyx->SetXTitle("x [mm]");  
  
  bool exit=false;
  bool anotherevent=true;
  int evsel=0;
 
  
  while(!exit){

    if(anotherevent==true){

      clean_th3(tpc);
      clean_th2(hyx);
      clean_th2(hzy);

      if(in!="n"){
	myReader.SetEntry(0);
	int first = *evnum;
	myReader.SetEntry(t->GetEntries()-1);
	int last =  *evnum;
	
	cout << "First Event: " << first << " Last Event: " << last << endl; 
	cout << "Select event number: ";
	cin >> evsel;
	
	if (myReader.SetEntry(evsel-first) != TTreeReader::EEntryStatus::kEntryValid) {
	  cout << "Error in retrieving the requested event" << endl;
	  return;
	}
	anotherevent=false;
      }
      else {
	myReader.SetEntry(myReader.GetCurrentEntry()+1);
	evsel=*evnum;
      }
    }
    cout << "Ev: " << evsel << endl;
    
    
    for(auto&& hit: *hits){ 
      if(hit.getGlobalChannelId()>19999) continue; //not TPC
      
      vector<Double_t> pos=hit.getXYZ();
      tpc->Fill(pos[0],pos[1],pos[2],hit.getPeakHeight());
      hyx->Fill(pos[0],pos[1],hit.getPeakHeight());
      hzy->Fill(pos[1],pos[2],hit.getPeakHeight());
      
    }
    
    c0->Modified();
    c0->Update();
    c0->cd(1);
    tpc->Draw("LEGO2");
    c0->cd(2);
    hzy->Draw("col");
    c0->cd(3);
    hyx->Draw("colz");
    
    ica=0;
    cout << "e for another event, q for exit" << endl;
    c0->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0, 0,
		"terminal_input(Int_t,Int_t,Int_t,TObject*)");//connette il canvas a un evento grafico (non chiarissimo come funziona)
    while(ica!=1){
      usleep(100);
      gClient->HandleInput();//fondamentale, se no non funziona
    }
    c0->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");
    if(in=="e" || in=="n") {
      anotherevent=true;
    }
    if(in=='q') exit=true;
    
  }
  
  
}


void terminal_input(Int_t event, Int_t x, Int_t y, TObject *selected){

  if(event==24){ //tastiera su TPad
    if(gPad->GetEventX() == 101) { // e
      in = "e";
      ica=1;
      return;
    }
    if(gPad->GetEventX() == 113) { // q
      in = "q";
      ica=1; 
      return;
    }
    if(gPad->GetEventX() == 110) { // n
      in = "n";
      ica=1; 
      return;
    }
  }
  
}


TH3F* build_tpc(TString lookup){

  ifstream in(lookup);

  if(!in){
    cout << "Error while trying to open lookup table file " << lookup << endl;
    return NULL;
  }

  string line;
  getline(in,line); //la prima riga è intestazione

  vector<int> vrow;
  vector<int> vcol;
   
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
      
    if(nom!="TPC") continue;
    if(row!=-1) vrow.push_back(row);
    if(col!=-1) vcol.push_back(col);
  }
  
  auto rmax = *max_element(std::begin(vrow), std::end(vrow));
  auto cmax = *max_element(std::begin(vcol), std::end(vcol)); 
  auto rmin = *min_element(std::begin(vrow), std::end(vrow));
  auto cmin = *min_element(std::begin(vcol), std::end(vcol)); 
  
  // cout << rmax << " " << rmin << endl;
  // cout << cmax << " " << cmin << endl;

  int nx= (cmax-cmin)/2;
  int xmin= cmin*2+1;
  int xmax= cmax*2+1;
  int ny= (rmax-rmin)/2;
  int ymin= rmin*2+1;
  int ymax= rmax*2+1;
  int nz=nsample;
  int zmin=0;
  int zmax=nsample*tsample;
  
  
  TH3F* plane = new TH3F("tpc","tpc",nx,xmin,xmax,ny,ymin,ymax,nz,zmin,zmax);
  plane->SetYTitle("y");
  plane->SetXTitle("x");
  plane->SetZTitle("z");
  
  return plane;
  
}



void clean_th1(TH1 *h){
  for(int i=1; i<=h->GetNbinsX(); i++){
    h->SetBinContent(i,0);
  }
  h->ResetStats();
}

void clean_th2(TH2 *h){
  for(int i=1; i<=h->GetNbinsX(); i++){
    for(int j=1; j<=h->GetNbinsY(); j++){
      h->SetBinContent(i,j,0);
    }
  }
    h->ResetStats();
}

void clean_th3(TH3 *h){
  for(int i=1; i<=h->GetNbinsX(); i++){
    for(int j=1; j<=h->GetNbinsY(); j++){
      for(int k=1; k<=h->GetNbinsZ(); k++){
	h->SetBinContent(i,j,k,0);
      }
    }
  }
  h->ResetStats();
}
