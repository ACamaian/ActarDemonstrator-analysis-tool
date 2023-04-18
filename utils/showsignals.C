#include <iostream>
#include <map>

#include <TROOT.h>
#include <TSystem.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH2F.h>
#include <TString.h>

#include <cRawEvent.h>
#include <cHit.h>
#include <cRawSignal.h>
#include <pSignal.h>

using namespace std;

void terminal_input(Int_t event, Int_t x, Int_t y, TObject *selected);

int ica;
string in;


void showsignals(TString fname="../out/ACTAR_852.root"){

  TFile *f = new TFile(fname,"R");
  TTree *t = (TTree*)f->Get("rawEventTree");

  TTreeReader myReader(t);
  TTreeReaderValue<int> evnum(myReader,"eventnum");
  TTreeReaderValue<vector<cRawSignal>> sigs(myReader,"signal");
  
  int evsel=0;
  int gsel=0;
  
  
  TCanvas *c0 = new TCanvas ("c0","c0");
  TH2F *frame = new TH2F("frame","frame",512,0,512,100,-100,500);
  frame->SetXTitle("samples");
  frame->Draw("LP");

  bool exit=false;
  bool anothersignal=true;
  bool anotherevent=true;
  map<int,map<int,pSignal>> psig;
  while(!exit){

    if(anotherevent==true){
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

      map<int, pSignal> temp;
      for(auto&& sig: *sigs){ //automatically deduces the correct type
	int gid = sig.getGlobalChannelId();
	temp.emplace(gid,sig);
      }
      psig.emplace(evsel,temp);
      anotherevent=false;
    }
    
    if(anothersignal==true){
      cout << "Fired channels:" << endl;
      for(map<int,pSignal>::iterator it = psig[evsel].begin(); it!=psig[evsel].end(); ++it){
	cout<< it->first <<  " ";
      }
      cout << " \n";
      
      cout << "Select channel GlobalID: ";
      cin >> gsel;
      anothersignal=false;
    }

    psig[evsel][gsel].Draw("LP");
    cout << psig[evsel][gsel].RMS(0,50) << endl;
					   
    c0->Modified();
    c0->Update();
    
    ica=0;
    cout << "e for another event, s for another signal, n for another signal and event, q for exit" << endl;
    c0->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0, 0,
		"terminal_input(Int_t,Int_t,Int_t,TObject*)");//connette il canvas a un evento grafico (non chiarissimo come funziona)
    while(ica!=1){
      usleep(100);
      gClient->HandleInput();//fondamentale, se no non funziona
    }
    c0->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");
    
    if(in=="s") {
      anothersignal=true;
      anotherevent=false;
    }
    if(in=="e") {
      anothersignal=false;
      anotherevent=true;
    }
    if(in=="n"){
      anothersignal=true;
      anotherevent=true;
    }

    
    if(in=='q') exit=true;


  }

  
}


void terminal_input(Int_t event, Int_t x, Int_t y, TObject *selected){

  
  if(event==24){ //tastiera su TPad

    cout << gPad->GetEventX() << endl;

    if(gPad->GetEventX() == 101) { // e
      in = "e";
      ica=1;
      return;
    }

    if(gPad->GetEventX() == 115) { // s
      in = "s";
      ica=1; 
      return;
    }

     if(gPad->GetEventX() == 116) { // t
      in = "t";
      ica=1; 
      return;
    }

     if(gPad->GetEventX() == 110) { // n
       in = "n";
       ica=1;
       return;
     }
       
    if(gPad->GetEventX() == 113) { // q
      in = "q";
      ica=1; 
      return;
    }
  }
  
}

