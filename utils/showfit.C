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
#define nsample 170 //campioni
#define sampling_period 80 //ns, ie 12.5 MHz

using namespace std;

//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"

TGraph2D *create_graph(vector<double> a, vector<double> b);
Float_t RadToDeg(){return 180./TMath::Pi();}

void showfit(int nentry=0, TString name="../data/mc_data_sho_hough_3_12_fit.root", int runnum=0){

  TFile *f = new TFile(name);
  TTree *t = (TTree*)f->Get(Form("PhysicsTree_%d",runnum));

  TH3F *hxyz = new TH3F("hxyz","hxyz",64,0,128,32,0,64,nsample,0,nsample*vdrift*sampling_period);
  hxyz->SetXTitle("x mm");
  hxyz->SetYTitle("y mm");
  hxyz->SetYTitle("z mm"); 
  
  TH3F *hxyz_f[2];
  for(int i=0; i<2; i++) hxyz_f[i] = new TH3F(Form("hxyz_f%d",i),Form("hxyz_f%d",i),64,0,128,32,0,64,nsample,0,nsample*vdrift*sampling_period);
  
    
  TTreeReader r(t);
  TTreeReaderValue<vector<vector<double>>> points(r,"points");
  TTreeReaderValue<vector<vector<double>>> lines(r,"lines");
  TTreeReaderArray<Double_t> vertex(r,"vertex");
  TTreeReaderValue<Double_t> theta(r,"theta_part");
  TTreeReaderValue<Double_t> phi(r,"phi_part");
  TTreeReaderValue<Double_t> eres(r,"eres_part");
  TTreeReaderValue<Int_t> idcode(r,"idcode");
  
  TTreeReaderValue<Double_t> Vertex0(r,"X0");
  TTreeReaderValue<Double_t> Theta0(r,"Theta0");
  TTreeReaderValue<Double_t> Phi0(r,"Phi0");
  TTreeReaderValue<Double_t> Epart0(r,"Epart0");
  
  r.SetEntry(nentry);

  Double_t ebeam=0;
   Double_t epart=0;
  
  for(auto&& pp: *points){ 
   cout << pp[0] << " " << pp[1] << " " << pp[2] << " " << pp[3]/0.15 << " " << pp[4] << endl;
    hxyz->Fill(pp[0],pp[1],pp[2], pp[3]);
    
    if(pp[4]==0) ebeam+=pp[3]/0.15;
    if(pp[4]==1) epart+=pp[3]/0.15;
  }

  TCanvas *c0 = new TCanvas("c0","c0");
  hxyz->Draw("BOX2 Z");

  TGraph2D *g[lines->size()];
  Int_t nlines=0;
  for(auto &&ll: *lines){
    vector<double> aa={ll[0],ll[1],ll[2]};
    vector<double> bb={ll[3],ll[4],ll[5]};
    g[nlines] = new TGraph2D();
    g[nlines] = create_graph(aa,bb);
    g[nlines]->SetMarkerColor(nlines+1);
    g[nlines]->Draw("psame");
    nlines++;
  }
  
  TGraph2D *v = new TGraph2D();
  v->SetPoint(0,vertex[0],vertex[1],vertex[2]);  
  v->SetMarkerStyle(20);
  v->SetMarkerColor(6);
  v->Draw("psame");
  
  TGraph2D *v0 = new TGraph2D();
  v0->SetPoint(0,*Vertex0,32,100);  
  v0->SetMarkerStyle(21);
  v0->SetMarkerColor(kOrange);
  v0->Draw("psame");
  
  cout << "Theta and Phi: " << *theta << " " << *phi << endl;
  cout << "Theta0 and Phi0: " << *Theta0 << " " << *Phi0 << endl;
  cout << "Eres: " << *eres << endl ;
  cout << "Epart0: " << *Epart0 << endl ;
  cout << "Vertex: " << vertex[0] << " " << vertex[1] << " " << vertex[2] << endl;
  cout << "Vertex: " << *Vertex0 << " " << 32 << " " << 100 << endl;
  
  
  cout << "IDCode: " << *idcode << endl;
  
  
  cout << "Ebeam f=0 -> " << ebeam << endl;
  cout << "Epart f=1 -> " << epart << endl;
  
  }


void show_simul(TString name = "../data/mc_data_sho_hough_3_12_fit.root"){

  TFile *f = new TFile(name);
  TTree *t = (TTree*)f->Get(Form("PhysicsTree_0"));
  
  TTreeReader r(t);
  TTreeReaderValue<vector<vector<double>>> points(r,"points");
  TTreeReaderValue<vector<vector<double>>> lines(r,"lines");
  TTreeReaderArray<Double_t> vertex(r,"vertex");
  TTreeReaderValue<Double_t> theta(r,"theta_part");
  TTreeReaderValue<Double_t> phi(r,"phi_part");
  TTreeReaderValue<Double_t> eres(r,"eres_part");
  TTreeReaderValue<Int_t> idcode(r,"idcode");
  
  TTreeReaderValue<Double_t> Vertex0(r,"X0");
  TTreeReaderValue<Double_t> Theta0(r,"Theta0");
  TTreeReaderValue<Double_t> Phi0(r,"Phi0");
  TTreeReaderValue<Double_t> Epart0(r,"Epart0");
  
  //---
  // Histos
  //---
  TH1F *hidcode = new TH1F("hidcode","hidcode",400000,0,400000);
  
  TString title[2]={"orig","after"};
  
  TH2F *hvv0[3];
  TH1F *hvertex[3][2];
  for(int i=0; i<3; i++) {
    	hvv0[i] = new TH2F(Form("hvv0_%d",i),Form("hvv0_%d",i),200,0,200,200,0,200);
	for(int j=0; j<2; j++) hvertex[i][j] = new TH1F(Form("hvertex_%d_%s",i,title[j].Data()),Form("hvertex_%d_%s",i,title[j].Data()),200,0,200); 
	}
  TH2F *htt0 = new TH2F("htt0","htt0",95,0,95,95,0,95);
  TH2F *hpp0 = new TH2F("hpp0","hpp0",360,0,360,360,0,360);
  TH2F *hee0 = new TH2F("hee0","hee0",2000,0,2000,2000,0,2000);
  
  TH1F *htheta[2];
  TH1F *hphi[2];
  TH1F *hepart[2];
  for(int j=0; j<2; j++){
  	htheta[j] = new TH1F(Form("htheta_%s",title[j].Data()),Form("htheta_%s",title[j].Data()),95,0,95);
	hphi[j] = new TH1F(Form("hphi_%s",title[j].Data()),Form("hphi_%s",title[j].Data()),360,0,360);
	hepart[j] = new TH1F(Form("hepart_%s",title[j].Data()),Form("hepart_%s",title[j].Data()),2000,0,2000);  
  } 
  
  Int_t entry=0;
  while(r.Next()){
  
   hidcode->Fill(*idcode);
   
   hvertex[0][0]->Fill(*Vertex0);
   hvertex[1][0]->Fill(33);
   hvertex[2][0]->Fill(100);
   
   htheta[0]->Fill(*Theta0);
   hphi[0]->Fill(*Phi0);
   hepart[0]->Fill(*Epart0);
   		
  	if(*idcode==10011){
	  hvertex[0][1]->Fill(vertex[0]);
  	  hvertex[1][1]->Fill(vertex[1]);
   	  hvertex[2][1]->Fill(vertex[2]);
	  
	  htheta[1]->Fill(*theta);
   	  hphi[1]->Fill(*phi);
   	  hepart[1]->Fill(*eres);
	  	
	
	  hvv0[0]->Fill(*Vertex0,vertex[0]);
	  hvv0[1]->Fill(33,vertex[1]);
	  hvv0[2]->Fill(100,vertex[2]);
	  
	  htt0->Fill(*Theta0,*theta);
	  hpp0->Fill(*Phi0,*phi);
	  hee0->Fill(*Epart0,*eres);
	 
	}  
  
  if(*Epart0>1500 && *eres>1500) cout << *Epart0 << " " << *eres << " " << entry << endl; 
  
  entry++;	
  }	


  TCanvas *c0 = new TCanvas("c0","c0");
  hidcode->Draw();
  
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(3,2);
  for(int i=0; i<3; i++) {
  	c1->cd(i+1);
	hvv0[i]->Draw("");
  }
  c1->cd(4);
  htt0->Draw("");
  c1->cd(5);
  hpp0->Draw("");
  c1->cd(6);
  hee0->Draw("colz");
  
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(1,4);
  for(int i=0; i<2; i++){
  	c2->cd(1);
	hvertex[0][i]->SetLineColor(i+1);
	hvertex[0][i]->Draw((i==0)?"":"same");
	c2->cd(2);
	htheta[i]->SetLineColor(i+1);
	htheta[i]->Draw((i==0)?"":"same");
	c2->cd(3);
	hphi[i]->SetLineColor(i+1);
	hphi[i]->Draw((i==0)?"":"same");
	c2->cd(4);
	hepart[i]->SetLineColor(i+1);
	hepart[i]->Draw((i==0)?"":"same");
   }



}


TGraph2D *create_graph(vector<double> a, vector<double> b){

  TGraph2D *g = new TGraph2D();
  g->SetMarkerStyle(20);
  if(a.size()!=3 && b.size()!=3 ) {cout << "NO lines" << endl; return NULL;}
  for(int i=0; i<100; i++){
    float pos[3]={0,0,0};
    for(int k=0; k<3; k++){
      pos[k]=a[k]+i*b[k];
    }
    
    if(pos[0]<0 || pos[0]>128) continue;
    if(pos[1]<0 || pos[1]>64) continue;
    if(pos[2]<0) continue; 
    
    g->SetPoint(g->GetN(),pos[0],pos[1],pos[2]);
  }
  return g;
}
