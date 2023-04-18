#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
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

TH2F* build_padplane(TString lookup);
pair<int, int> getPadFromGlobalID(int gsel, TString lookup);
void terminal_input(Int_t event, Int_t x, Int_t y, TObject *selected);

int ica;
string in;

void showhit_values(TString fname="../out/ACTAR_852.root",TString ltable="../LookupTable.dat"){
  
  TFile *f = new TFile(fname,"R");
  TTree *t = (TTree*)f->Get("rawEventTree");

  TTreeReader myReader(t);
  TTreeReaderValue<int> evnum(myReader,"eventnum");
  TTreeReaderValue<vector<cHit>> hits(myReader,"hits");

  bool exit=false;
  bool anotherevent=true;
  int evsel=0;
  
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
      anotherevent=false;
    }

    for(auto&& hit: *hits){ 
      if(hit.getGlobalChannelId()>19999) continue; //not TPC
      
      Float_t max = hit.getPeakHeight();
      Float_t time = hit.getPeakTime();
      Int_t gid = hit.getGlobalChannelId();

      cout << gid << " " << max << " " << time << endl;
    }

    cout << "Command: ";
    cin >> in;
    if(in=="e") {
      anotherevent=true;
    }
    if(in=='q') exit=true;
  }
  

  
}

void showhit_padplane(TString fname="../out/ACTAR_852.root",TString ltable="../LookupTable.dat"){

  TFile *f = new TFile(fname,"R");
  TTree *t = (TTree*)f->Get("rawEventTree");

  TTreeReader myReader(t);
  TTreeReaderValue<int> evnum(myReader,"eventnum");
  TTreeReaderValue<vector<cHit>> hits(myReader,"hits");
 
    int evsel=0;
  
    TCanvas *c0 = new TCanvas ("c0","c0",600,900);
  c0->Divide(1,2);
  TH2F *padplane=build_padplane(ltable);
  TH2F *padplane_time= new TH2F("pad_time","pad_time",padplane->GetNbinsX(),padplane->GetXaxis()->GetFirst(),padplane->GetXaxis()->GetLast(),512,0,512);

  
  bool exit=false;
  bool anotherevent=true;
  
  pair<int,int> pad_pair;
  while(!exit){

    if(anotherevent==true){

      for(int i=0; i<padplane->GetNbinsX(); i++) for(int j=0; j<padplane->GetNbinsY(); j++) padplane->SetBinContent(i,j,0);
      for(int i=0; i<padplane_time->GetNbinsX(); i++) for(int j=0; j<padplane_time->GetNbinsY(); j++) padplane_time->SetBinContent(i,j,0);
      
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

    for(auto&& hit: *hits){ 
      if(hit.getGlobalChannelId()>19999) continue; //not TPC

      
      Float_t max = hit.getPeakHeight();
      Float_t time = hit.getPeakTime();
      Int_t gid = hit.getGlobalChannelId();

      pad_pair  =  getPadFromGlobalID(gid,ltable);

      padplane->SetBinContent(pad_pair.first,pad_pair.second,max);
      //  cout << time << endl;
      padplane_time->SetBinContent(pad_pair.first,time,1);
    }

    padplane->SetMinimum(1);
    c0->cd(1);
    padplane->Draw("colz");
    c0->cd(2);
    padplane_time->Draw();

    c0->Modified();
    c0->Update();

    ica=0;
    cout << "e for another event, q for exit" << endl;
    c0->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0, 0,
		"terminal_input(Int_t,Int_t,Int_t,TObject*)");//connette il canvas a un evento grafico (non chiarissimo come funziona)
    while(ica!=1){
      usleep(100);
      gClient->HandleInput();//fondamentale, se no non funziona
    }
    c0->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");
    if(in=="e") {
      anotherevent=true;
    }
    if(in=='q') exit=true;
  }
  
  
}



TH2F* build_padplane(TString lookup){

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
  
  TH2F* plane = new TH2F("tpc","tpc",cmax-cmin,cmin,cmax,rmax-rmin,rmin,rmax);
  plane->SetYTitle("row");
  plane->SetXTitle("col");
  return plane;
  
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

    int gid= chan+aget*100+asad*1000+cob*10000;
    if(gid==gsel){
      col_row = make_pair(col,row);
      break;
    }
  }

  return col_row;
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
  }
  
}
