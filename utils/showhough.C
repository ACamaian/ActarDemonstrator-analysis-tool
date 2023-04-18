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

#define vdrift 0.01297 //mm/ns
#define nsample 512 //campioni
#define sampling_period 80 //ns, ie 12.5 MHz

using namespace std;

//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"

TGraph2D *g(vector<double> a);

void showevent(int nentry=1){

  TFile *f = new TFile("../data/mc_data_sho_hough_3_12.root");
  TTree *t = (TTree*)f->Get("HoughEventTree_0");

  TH3F *hxyz = new TH3F("hxyz","hxyz",64,0,128,32,0,64,nsample,0,512*vdrift*sampling_period);
  hxyz->SetXTitle("x mm");
  hxyz->SetYTitle("y mm");
  hxyz->SetZTitle("z mm");  
    
  TTreeReader r(t);
  TTreeReaderValue<int> evnum(r,"eventnum");
  TTreeReaderValue<cEvent> ev(r,"event");
  TTreeReaderValue<vector<cHitxyz>> hits(r,"hits");
  
  r.SetEntry(nentry);
  cout << *evnum << endl;

  map<int,vector<double>> lines;
  lines=ev->getLines();
  for(auto&& hit: *hits){ 
    vector<Double_t> pos=hit.getXYZ();
//     if(hit.getHoughFlag() == 2)  
        hxyz->Fill(pos[0],pos[1],pos[2], hit.getPeakHeight());
  }
  hxyz->Draw("BOX2 Z");

  
  for(auto &&ll: lines){
  	for(int i=0; i<6; i++){
		cout << ll.first << " " << ll.second.at(i) << endl;
		}
	}
  
  TGraph2D *l[10];
  for(auto ll: lines){
    l[ll.first+1] = new TGraph2D();
    l[ll.first+1]= g(ll.second);
    l[ll.first+1]->SetMarkerColor(ll.first+1);
    l[ll.first+1]->Draw("psame");
  }
}

void showglobal(TString name = "../data/mc_data_hough_4_20.root"){

  TFile *f = new TFile(name);
  TTree *t = (TTree*)f->Get("HoughEventTree_0");

  TH2F *hxy =  new TH2F("hxy","hxy",64,0,128,32,0,64);
  hxy->SetXTitle("x mm");
  hxy->SetYTitle("y mm");
  TH2F *hyz = new TH2F("hyz","hyz",32,0,64,512,0,170);
  hyz->SetXTitle("y mm");
  hyz->SetYTitle("z mm");
  
  TH2F *hxy_g =  new TH2F("hxy_trg","hxy_trg",64,0,128,32,0,64);
  TH2F *hyz_g = new TH2F("hyz_trg","hyz_trg",32,0,64,170,0,170);
  TH2F *hxy_notg =  new TH2F("hxy_notrg","hxy_notrg",64,0,128,32,0,64);
  TH2F *hyz_notg = new TH2F("hyz_notrg","hyz_notrg",32,0,64,170,0,170);
  
  
  int id[4]={0,1,10,11};
  int idcount[4]={0,0,0,0};
  int flagcount[]={0,0,0,0};
  TH2F *hxy_f[4][5];
  TH2F *hyz_f[4][5];
  for(int j=0; j<4; j++){
  	for(int i=0; i<5; i++){
  		hxy_f[j][i] =  new TH2F(Form("hxy_code%d_f%d",id[j],i), Form("hxy_code%d_f%d",id[j],i), 64, 0, 128, 32, 0, 64);
		hyz_f[j][i] =  new TH2F(Form("hyz_code%d_f%d",id[j],i), Form("hzy_code%d_f%d",id[j],i), 32, 0, 64, 170, 0, 170);
  	}
   }
  
  TH1F *hgood = new TH1F("hgood","hgood",5,0,5);
  TH1F *hnlines = new TH1F("hnlines","hnlines",5,0,5);
      
  TTreeReader r(t);
  TTreeReaderValue<int> evnum(r,"eventnum");
  TTreeReaderValue<cEvent> ev(r,"event");
  TTreeReaderValue<vector<cHitxyz>> hits(r,"hits");
  TTreeReaderValue<bool> is_good(r,"isgood");
  
  map<int,vector<double>> lines;
  
  while(r.Next()){
  lines.clear();
  
  int jcode=0;
	if(ev->getIDCode()==0) jcode=0;
	if(ev->getIDCode()==1) jcode=1;
	if(ev->getIDCode()==10) jcode=2;
	if(ev->getIDCode()==11) jcode=3;
		
	idcount[jcode] +=1 ;
  
  int tflag=0;
  for(auto&& hit: *hits){   
    vector<Double_t> pos=hit.getXYZ();
    
        hxy->Fill(pos[0],pos[1], hit.getPeakHeight());
	hyz->Fill(pos[1], pos[2], hit.getPeakHeight());
	
	hxy_f[jcode][hit.getHoughFlag()]->Fill(pos[0],pos[1], hit.getPeakHeight());
	hyz_f[jcode][hit.getHoughFlag()]->Fill(pos[1], pos[2], hit.getPeakHeight());
			
	if(*is_good){
		hxy_g->Fill(pos[0],pos[1], hit.getPeakHeight());
		hyz_g->Fill(pos[1], pos[2], hit.getPeakHeight());
		}
	else{
	   hxy_notg->Fill(pos[0],pos[1], hit.getPeakHeight());
	   hyz_notg->Fill(pos[1], pos[2], hit.getPeakHeight());	
 	}
	  
    
  }	
   int nlines =0;
   lines=ev->getLines();
   for(auto &&ll: lines){
    nlines++;
   }	
   hnlines->Fill(nlines);	
  flagcount[nlines-1]++;
   
  }
  
  TCanvas *c0 = new TCanvas("c0_comulative","c0_comulative");
  c0->Divide(2,3);
  c0->cd(1);
  hxy->Draw("colz");
  c0->cd(2);
  hyz->Draw("colz");
  c0->cd(3);
  hxy_g->Draw("colz");
  c0->cd(4);
  hyz_g->Draw("colz");
  c0->cd(5);
  hxy_notg->Draw("colz");
  c0->cd(6);
  hyz_notg->Draw("colz");
  
  TCanvas *c1 = new TCanvas("c1_comflag","c1_comflag");
  c1->Divide(2,4);
  for(int j=0; j<4; j++){
  for(int i=0; i<2; i++){
  	c1->cd(j*2+1);
	hxy_f[j][i]->SetMarkerColor(i+1);
	hxy_f[j][i]->Draw((i==0)?"":"same");
	c1->cd(j*2+2);
	hyz_f[j][i]->SetMarkerColor(i+1);
	hyz_f[j][i]->Draw((i==0)?"":"same");
  }
  }
  
  TCanvas *c2 = new TCanvas("c2_flag_11_10","c2_flag_11_flag10");
  c2->Divide(2,2);
  for(int j=2; j<4; j++){
  for(int i=0; i<2; i++){
  	c2->cd((j-2)*2+i+1);
	hxy_f[j][i]->SetMarkerColor(i+1);
	hxy_f[j][i]->Draw();
  }
  }
  
  cout << "Ev. totali: " << t->GetEntries() << endl;
  cout << "No Hough No Trigger: " << idcount[0] << endl;
  cout << "No Hough Ok Trigger: " << idcount[1] << endl;
  cout << "Ok Hough No Trigger: " << idcount[2] << endl;
  cout << "Ok Hough Ok Trigger: " << idcount[3] << endl;
  
  cout << " -- Hough Flag:" << flagcount[0] << " " << flagcount[1] << " " << flagcount[2] << " " << flagcount[3] << endl;
  
 /*
  TGraph2D *l[10];
  for(auto ll: lines){
    l[ll.first+1] = new TGraph2D();
    l[ll.first+1]= g(ll.second);
    l[ll.first+1]->SetMarkerColor(ll.first+1);
    l[ll.first+1]->Draw("psame");
  } */
  
}



TGraph2D *g(vector<double> a){

  TGraph2D *g = new TGraph2D();
  g->SetMarkerStyle(20);
  if(a.size()!=6) {cout << "NO lines" << endl; return NULL;}
  for(int i=-100; i<100; i++){
    float pos[3]={0,0,0};
    for(int k=0; k<3; k++){
      pos[k]=a[k]+i*a[k+3];
    }
    g->SetPoint(g->GetN(),pos[0],pos[1],pos[2]);
  }
  return g;
}
