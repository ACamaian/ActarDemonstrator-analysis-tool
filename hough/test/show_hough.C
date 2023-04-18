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
#include <TGraph2D.h>

#define vdrift 0.1129 //mm/ns
#define nsample 512 //campioni
#define sampling_period 80 //ns, ie 12.5 MHz

using namespace std;

//Defined class
#include "../../src/cHitxyz.h"
#include "../../src/cEvent.h"

TGraph2D *g(vector<double> a, vector<double> b);

void show_hough(int nentry=1){

  TFile *f = new TFile("/home/camaiani/ATS_perdite/data/Eloss_cf4_test_hough.root");
  TTree *t = (TTree*)f->Get("HoughEventTree_144");

  TH3F *hxyz = new TH3F("hxyz","hxyz",64,0,128,32,0,64,100,1150,1350);
  hxyz->SetXTitle("x mm");
  hxyz->SetYTitle("y mm");
  hxyz->SetZTitle("z mm");  
    
  TTreeReader r(t);
  TTreeReaderValue<int> evnum(r,"eventnum");
  TTreeReaderValue<cEvent> ev(r,"event");
  TTreeReaderValue<vector<cHitxyz>> hits(r,"hits");
  
  r.SetEntry(nentry);
  cout << *evnum << endl;

  map<int,pair<vector<double>,vector<double>>> lines;
  lines=ev->getLines();
  Int_t nlines=lines.size();
  TH1F *hcharge[nlines];
  TH1F *hy[nlines];
  TH1F *hx[nlines];
  TH1F *hz[nlines];
  for(int i=0; i<nlines; i++){
  	hcharge[i] = new TH1F(Form("hcharge_%d",i), Form("hcharge_%d",1), 100, 0, 1e07);
	hx[i] = new TH1F(Form("hx_%d",i), Form("hx_%d",i), 64,0,128);
	hy[i] = new TH1F(Form("hy_%d",i), Form("hy_%d",i), 32,0,64);
	hz[i] = new TH1F(Form("hz_%d",i), Form("hz_%d",i), 200,1150,1350);
  }
  
  for(auto&& hit: *hits){ 
    vector<Double_t> pos=hit.getXYZ();
//     if(hit.getHoughFlag() == 2)  
        hxyz->Fill(pos[0],pos[1],pos[2], hit.getPeakHeight());
  	int iflag=hit.getHoughFlag()-1;
	hcharge[iflag]->Fill(hit.getPeakHeight());
	hx[iflag]->Fill(pos[0]);
	hy[iflag]->Fill(pos[1]);
	hz[iflag]->Fill(pos[2]);
  }
  
  TCanvas *c0 = new TCanvas("c0","c0",900,900);
  c0->Divide(3,2);
  c0->cd(1);
  hxyz->Draw("BOX2 Z");
  for(int i=0; i<nlines; i++){
  	c0->cd(2);
	hcharge[i]->SetLineColor((i==0)?1:2);
	hcharge[i]->DrawNormalized((i==0)?"":"same");
	
	c0->cd(3);
	hx[i]->SetLineColor((i==0)?1:2);
	hx[i]->DrawNormalized((i==0)?"":"same");
	
	c0->cd(4);
	hy[i]->SetLineColor((i==0)?1:2);
	hy[i]->DrawNormalized((i==0)?"":"same");
	
	c0->cd(5);
	hz[i]->SetLineColor((i==0)?1:2);
	hz[i]->DrawNormalized((i==0)?"":"same");
	
  }
  
  
  
  c0->cd(1);
  TGraph2D *l[10];
  for(auto ll: lines){
    l[ll.first+1] = new TGraph2D();
    l[ll.first+1]= g(ll.second.first,ll.second.second);
    l[ll.first+1]->SetMarkerColor(ll.first+1);
    l[ll.first+1]->Draw("psame");
  }
}



TGraph2D *g(vector<double> a, vector<double> b){

  TGraph2D *g = new TGraph2D();
  g->SetMarkerStyle(20);
  if(a.size()!=3 && b.size()!=3 ) {cout << "NO lines" << endl; return NULL;}
  for(int i=-100; i<100; i++){
    float pos[3]={0,0,0};
    for(int k=0; k<3; k++){
      pos[k]=a[k]+i*b[k];
    }
    g->SetPoint(g->GetN(),pos[0],pos[1],pos[2]);
  }
  return g;
}
