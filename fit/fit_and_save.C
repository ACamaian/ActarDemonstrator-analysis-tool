//Per C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <map>
#include <tuple>
 
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
#include <TVector3.h>
#include <TVectorD.h>
#include <TMatrixD.h>
#include <TVirtualFitter.h>
#include <TGraphErrors.h>
#include <TGraph2D.h>

//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"

using namespace std;

std::map<int,std::vector<float>> buildOSCARmap(TString lookup);
std::map<int,tuple<int,float,string>> load_list_of_runs(TString name);
TGraph2D *create_graph(vector<double> a, vector<double> b);
void clean_tgraph(TGraphErrors *g);
void DistancePointToLine_weigheted(int &npar, double *gin, double &fval, double *par, int iflag);
void get_vertex(vector<double> ll, vector<double> ll2, Double_t vertex_temp[]);
void VertexFitterFunction(int &npar, double *gin, double &sum, double *par, int iflag);
Double_t distance_point_line(TVector3 p, TVector3 a, TVector3 b);
Double_t bragg_function(Double_t *x, Double_t *par);
Float_t RadToDeg(){return 1 * 180./TMath::Pi();}
Float_t DegToRad(){return 1 * TMath::Pi()/180.;}
void GetThetaPhi(TVector3 b, TVector3 a, Float_t Angles[]);
Float_t GetThetaPlane(TVector3 a, TVector3 ref);
Float_t  GetTheta(TVector3 a, TVector3 ref);
Float_t  GetPhi(TVector3 a, TVector3 ref);
void GetPartAnglesFromTheBeam(TVector3 lipart,TVector3 libeam, Double_t Angles[]);
float e2v(float e,float m) {
  float v=300.*TMath::Sqrt(2*e/(931.5*m));
  return v;
}
float v2e(float v,float m)    {
  float e=0.5*m*931.5*v*v/(300*300);

  return e;
}
float  vcm_classica(float vp,int ap, int at)
{
  float vcm=ap*vp/(at+ap);
  return vcm;
}
#define vdrift 0.01297 //mm/ns
#define nsample 170 //campioni
#define sampling_period 80. //ns, ie 12.5 MHz
#define cal 0.030 // 10.6*pow(10,-2) // keV/a.u.
#define beam_amu 20. 
#define part_amu 4.

int main(int argc,char ** argv){
  //----
  //Input File
  //----
  TString list_run=argv[2];
  TString file_name = argv[1];
  TString out_name = argv[3];
    
  std::map<int,tuple<int,float,string>> list_of_runs=load_list_of_runs(list_run);
  Int_t nfiles=0;
  cout << "List of files to analize:" << endl;
  for(auto &&lor:list_of_runs){
    cout << lor.first << " " << get<0>(lor.second) << endl; //" " << get<1>(lor.second) << " " << get<2>(lor.second) << endl;
    nfiles++;
  }    
    
  TFile *tavole = new TFile("Tavole/Eloss_alpha_5mm.root");
  TGraph *geloss = (TGraph*) tavole->Get("eloss_alpga_5mm_exp");
  tavole->Close();
  Int_t NN=geloss->GetN();
  Double_t *er = geloss->GetX();
  Double_t *de = geloss->GetY();
    
    
  map<int, vector<float>> oscar_map =  buildOSCARmap("LookupTable.dat");
    
  //----
  //Utility
  //----
  map<int,vector<double>> lines;
  map<int,vector<double>> serv;
  map<int,vector<double>> outlines;
  vector<vector<double>> points;
  vector<vector<double>> points_oscar;
  vector<vector<double>> saved_lines;
  Double_t vertex[5]={0,0,0,9999,9999};
    
  Double_t theta_part=0; //w.r.t the beam
  Double_t phi_part=0; //w.r.t the beam
  Double_t eres_part=0, ex=0;
    
  Double_t v_part[3]={0,0,0}, v_part_cm[3]={0,0,0};
    
  Double_t eres_beam=0;
  Double_t eres_part_cm=0;
  Double_t range_part=0;
  Double_t phi_part_cm=0; 
  Double_t theta_part_cm=0;  
  Double_t theta_ne_cm=0; 
  Double_t Epart0=0, Theta0=0, Phi0=0, X0=0;
    
  Int_t idcode=0;
    
  Double_t theta_xx[2]={0,0}; //0 is the beam, 1 is the particle
  Double_t phi_yy[2]={0,0}; //0 is the beam, 1 is the particle
  Bool_t inside=false;
    
  TH3F *h3[10];
  for(int i=0; i<10; i++){
    h3[i]=new TH3F(Form("h3_line_%d",i+1),Form("h3_line_%d",i+1),64,0,128,32,0,64,nsample,0,nsample*vdrift*sampling_period);
  } 
    
  //----
  //Output File
  //----
  TFile *fout = new TFile(out_name,"RECREATE");
  TTree *tout[nfiles];
  Int_t ff=list_of_runs.begin()->first;
  for(auto &&lor:list_of_runs){
    fout->cd();
    
    string title=get<2>(lor.second);
    tout[lor.first-ff] = new TTree(Form("PhysicsTree_%d",get<0>(lor.second)),Form("Physics tree r.%d", get<0>(lor.second)));
    tout[lor.first-ff]->Branch("points",&points);
    tout[lor.first-ff]->Branch("points_oscar",&points_oscar);
    tout[lor.first-ff]->Branch("vertex", vertex, "vertex[5]/D"); //x,y,z, d1, d2
    tout[lor.first-ff]->Branch("lines", &saved_lines);
    tout[lor.first-ff]->Branch("theta_part", &theta_part, "theta_part/D"); 
    tout[lor.first-ff]->Branch("phi_part", &phi_part, "phi_part/D");
    tout[lor.first-ff]->Branch("v_part", v_part, "v_part[3]/D");
    tout[lor.first-ff]->Branch("eres_beam", &eres_beam, "eres_beam/D");
    tout[lor.first-ff]->Branch("eres_part", &eres_part, "eres_part/D");
    tout[lor.first-ff]->Branch("range_part", &range_part, "range_part/D");
    tout[lor.first-ff]->Branch("eres_part_cm", &eres_part_cm, "eres_part_cm/D");
    tout[lor.first-ff]->Branch("theta_part_cm", &theta_part_cm, "theta_part_cm/D");
    tout[lor.first-ff]->Branch("theta_ne_cm", &theta_ne_cm, "theta_ne_cm/D"); 
    tout[lor.first-ff]->Branch("phi_part_cm", &phi_part_cm, "phi_part_cm/D"); 
    tout[lor.first-ff]->Branch("v_part_cm", v_part_cm, "v_part_cm[3]/D");
    tout[lor.first-ff]->Branch("ex", &ex, "ex/D");
	
    tout[lor.first-ff]->Branch("idcode", &idcode, "idcode/I");
	
    tout[lor.first-ff]->Branch("theta_xx", theta_xx, "theta_xx[2]/D"); //0 is the beam, 1 is the particle
    tout[lor.first-ff]->Branch("phi_yy", phi_yy, "phi_yy[2]/D"); //0 is the beam, 1 is the particle
	
    tout[lor.first-ff]->Branch("inside", &inside, "inside/B");
    
    tout[lor.first-ff]->Branch("Epart0", &Epart0, "Epart0/D");
    tout[lor.first-ff]->Branch("X0", &X0, "X0/D");
    tout[lor.first-ff]->Branch("Theta0", &Theta0, "Theta0/D");
    tout[lor.first-ff]->Branch("Phi0", &Phi0, "Phi0/D");
  }
    
    
    
  //----
  //Loop
  //----
  cout << "Opening " << file_name << endl;
  TFile *fin = new TFile (file_name,"R");
  TTree *t;
  fout->cd();
  for(auto &&lor:list_of_runs){    	
    
    cout << "Reading  TTree " << Form("HoughEventTree_%d",get<0>(lor.second)) << " of " << nfiles << endl;
    t = (TTree*) fin->Get(Form("HoughEventTree_%d",get<0>(lor.second)));
	
    TTreeReader reader(t);
    TTreeReaderValue<int> evnum(reader,"eventnum");
    TTreeReaderValue<cEvent> event(reader,"event");
    TTreeReaderValue<vector<cHitxyz>> hits(reader,"hits");
    TTreeReaderValue<double> ee0(reader,"Epart0");
    TTreeReaderValue<double> xx0(reader,"X0");
    TTreeReaderValue<double> tt0(reader,"Theta0");
    TTreeReaderValue<double> pp0(reader,"Phi0");
    
    cout << "Entries: " << t->GetEntries() << endl; 

    reader.SetEntry(0);
    
    Int_t entry=0;
    while(reader.Next()){ 
 
      entry++;
      //if(entry==50) break;
      if(entry%100==0) cout << "Entry: " << entry << endl;
      
      Bool_t gotosave=false;  
      idcode = event->getIDCode();
      //cout << entry-1 << " " << idcode << endl;
      
      //--reading the event and preparing the TH3F(s)
      serv.clear();
      outlines.clear();
      points.clear();
      points_oscar.clear();
      saved_lines.clear();
      lines = event->getLines();
      vertex[0]=0; vertex[1]=0; vertex[2]=0; vertex[3]=9999; vertex[4]=9999;
      theta_part=0;
      phi_part=0;
      v_part[0]=0; v_part[1]=0; v_part[2]=0;
      eres_beam=0;
      eres_part=0;
      range_part=0;
      eres_part_cm=0;
      theta_part_cm=0;
      theta_ne_cm=0;
      phi_part_cm=0;
      v_part_cm[0]=0; v_part_cm[1]=0; v_part_cm[2]=0;
      ex=0;
      theta_xx[0]=0; theta_xx[0]=0;
      phi_yy[0]=0; phi_yy[1]=0;
      inside=false;
      Epart0=0; Theta0=0; Phi0=0; X0=0;
      
      Epart0= *ee0*1000.;
      Theta0= *tt0*RadToDeg();
      Phi0= *pp0*RadToDeg();
      X0= *xx0;
      
      Int_t ibeam=-1, itrack=-1;

      //--
      if(idcode<=10) {
	outlines = lines;
	gotosave=true;
	//cout << "idcode <10 -> gotosave" << endl;
      }
      
      //find the vertex between the two lines given by hough to exclude the vertex region from the fit
      Double_t v_temp[5]={0,0,0,9999,9999}; // 3,4 is the distance between the vertex and the two lines
      Double_t prevertex[5]={0,0,0,9999,9999}; 
      double dist_temp=9999;
      
      if(!gotosave){
	for(auto &&ll: lines){
	  for(auto &&ll2: lines){
	    if(ll.first>=ll2.first) continue;
	    //cout << ll.first << " " << ll2.first << endl;
	    get_vertex(ll.second,ll2.second, v_temp); //(A1(3),B1(3), A2(3),B2(3))
	    //cout << v_temp[0] << " " << v_temp[1] << " " << v_temp[2] << " " << v_temp[3] << " " << v_temp[4] << endl;
	    if(dist_temp>v_temp[3] || dist_temp>v_temp[4]){
	      dist_temp=min(v_temp[3],v_temp[4]);
	      for(int i=0; i<5; i++) prevertex[i]=v_temp[i];
	    }
	    else {
	      idcode = 999*100 + idcode;
	      gotosave=true;
	      //cout << "prevertex non converge -> gotosave" << endl;
	    }
	  }
	 }
        }
	  //cout << lines[0][0] << " " << lines[0][1] << " " << lines[0][2] << " " << lines[0][3] << " " << lines[0][4] << " " << lines[0][5] << endl;
	  //cout << lines[1][0] << " " << lines[1][1] << " " << lines[1][2] << " " << lines[1][3] << " " << lines[1][4] << " " << lines[1][5] << endl;
	  //cout << prevertex[0] << " " << prevertex[1] << " " << prevertex[2] << endl;


	  if(!gotosave){
	    if(prevertex[0]<=0 || prevertex[1]<=0 || prevertex[2]<=0) {idcode = 998*100 + idcode; gotosave=true; /*cout << "x pre" << endl;*/}
	    if(prevertex[0]>=124 || prevertex[1]>=64) {idcode = 997*100 + idcode; gotosave=true; /*cout << "y pre" << endl;*/}
	    if(prevertex[1]>=36 || prevertex[1]<=26) {idcode = 996*100 + idcode; gotosave=true; /*cout << "z pre" << endl;*/}
	  }
	  //fill TH3F

	  for(auto &&ll:lines) h3[ll.first]->Reset();
	
	if(!gotosave){	
	  for(auto &&hit : *hits){
	    if(hit.getGlobalChannelId()>19999) {
	      int gid= hit.getGlobalChannelId();
	      int cob= gid/10000;
	      int asad = (gid-cob*10000)/1000;
	      if(asad==0) continue; 
			 	
	      float xx = oscar_map[gid].at(0);
	      float yy = oscar_map[gid].at(1);
	      float zz = oscar_map[gid].at(2);
		
	      vector<double> temp;
	      temp.push_back(xx);
	      temp.push_back(yy);
	      temp.push_back(zz);
	      temp.push_back(hit.getPeakHeight());
	      points_oscar.push_back(temp);
			 
	    }
	    else {// TPC
      
	      int iflag= hit.getHoughFlag(); //index of the lines and point clouds - 0 is the beam - 1 is the track == lines.first
	      vector<Double_t> pos=hit.getXYZ();
	      Double_t charge=hit.getPeakHeight();
                        
	      pos.push_back(hit.getPeakHeight()*cal); // da qui sono keV
						    
	      //exclude from the fit the region closest to the found preliminary vertex
	      Float_t dist_from_vertex=0;
	      for(int ip=0; ip<3; ip++) dist_from_vertex+=pow(pos[ip]-prevertex[ip],2);
	      dist_from_vertex=sqrt(dist_from_vertex);
	      //cout << dist_from_vertex << endl;
			
	      if(dist_from_vertex<5)pos.push_back(-1);
	      else pos.push_back((double)iflag);
	      points.push_back(pos);
			
	      if(dist_from_vertex<5) continue;
	      h3[iflag]->Fill(pos[0],pos[1],pos[2],charge*cal); 
	    }                                    
	  }
		
	  //----    
	  // fit the graph now
	  //----
	  TString pname[6] = {"Ax","Ay","Az","Bx","By","Bz"};
	  TVirtualFitter *fitter = TVirtualFitter::Fitter(0,6);
	  fitter->SetDefaultFitter("Minuit");
	  fitter->SetErrorDef(1);    // Chi - Square minimization
	  double arglist[2];
	  arglist[0] = -1;
	  fitter->ExecuteCommand("SET PRINT", arglist, 1);
	  fitter->ExecuteCommand("SET NOW", arglist, 1);
      
	  //cout << "Fitter ready " << endl;     
	  for(auto ll: lines){                 
	    // set the function and the initial parameter values (A(3), B(3));
	    Double_t pStart[6]={ll.second.at(0),ll.second.at(1),ll.second.at(2),ll.second.at(3),ll.second.at(4),ll.second.at(5)};                   
	    for(int j=0; j<6; j++){ 
	      if(j<3){    
		//fitter->SetParameter(j,pname[j],pStart[j],0.01,0,600);    
		//fitter->FixParameter(j);    
	      }  
	      else fitter->SetParameter(j,pname[j],pStart[j],0.01,pStart[j]-0.5,pStart[j]+0.5);    
	    }
              
	    //compute the A(3) without the vertex region
	    float ctot=0;
	    for(int i=0; i<h3[ll.first]->GetNbinsX(); i++){
	      for(int j=0; j<h3[ll.first]->GetNbinsY(); j++){
		for(int k=0; k<h3[ll.first]->GetNbinsZ(); k++){  
		  if(h3[ll.first]->GetBinContent(i,j,k)<=0) continue;
		  else {
		    pStart[0] += h3[ll.first]->GetXaxis()->GetBinCenter(i) * h3[ll.first]->GetBinContent(i,j,k);
		    pStart[1] += h3[ll.first]->GetYaxis()->GetBinCenter(j) * h3[ll.first]->GetBinContent(i,j,k);
		    pStart[2] += h3[ll.first]->GetZaxis()->GetBinCenter(k) * h3[ll.first]->GetBinContent(i,j,k);
		    ctot+=h3[ll.first]->GetBinContent(i,j,k);
		  }
		}
	      }
	    }
	    for(int i=0; i<3; i++) {
	      pStart[i]/=ctot;
	      fitter->SetParameter(i,pname[i],pStart[i],0.,-200,200);    
	      fitter->FixParameter(i); 
	    }
                    
	    // set the object to be fitted and the function to ne minimized
	    fitter->SetObjectFit(h3[ll.first]);
	    fitter->SetFCN(DistancePointToLine_weigheted);
                
	    // set last parameters and run
	    arglist[0] = 1000; // number of function calls 
	    arglist[1] = 0.005; // tolerance 
	    fitter->ExecuteCommand("MIGRAD",arglist,0);
    
	    float_t mod= sqrt(pow(fitter->GetParameter(3),2)+pow(fitter->GetParameter(4),2)+pow(fitter->GetParameter(5),2));
	    vector<double> line_fitted={fitter->GetParameter(0),fitter->GetParameter(1),fitter->GetParameter(2),
	      fitter->GetParameter(3)/mod,fitter->GetParameter(4)/mod,fitter->GetParameter(5)/mod};
                
	    serv.emplace(ll.first,line_fitted);
     
	    //cout << line_fitted[0] << " " << line_fitted[1] << " " << line_fitted[2] << endl;
	    //cout << line_fitted[3] << " " << line_fitted[4] << " " << line_fitted[5] << endl;
	    //cout << " \n" ;
            
	  }
	  delete fitter;
		
		
	  //-----
	  //find the final vertex
	  //-----
	  //cout << "Vertex: " << endl;
	  Double_t dist=9999;
	  Double_t v2[5]={0,0,0,9999,9999};
	  vertex[0]=0;
	  vertex[1]=0;
	  vertex[2]=0;
	  vertex[3]=9999;
	  vertex[4]=9999;
	  for(auto &&ll: serv){
	    for(auto &&ll2: serv){
	      if(ll.first>=ll2.first) continue;
	      get_vertex(ll.second,ll2.second, v2); //(A1(3),B1(3), A2(3),B2(3))
	      //cout << v2[0] << " " << v2[1] << " " << v2[2] << " " << v2[3] << " " << v2[4] << endl;
	      //cout << dist << endl;
	      if(dist>v2[3] || dist>v2[4]){
		dist=min(v2[3],v2[4]);
		ibeam= ll.first; // the beam
		itrack= ll2.first; // the track
		for(int i=0; i<5; i++) vertex[i]=v2[i];
	      }
	      else {idcode = 989*100 + idcode;
	  	gotosave = true;
	      }
	    }
	  }
         }
	  //cout << serv[0][0] << " " << serv[0][1] << " " << serv[0][2] << " " << serv[0][3] << " " << serv[0][4] << " " << serv[0][5] << endl;
	  //cout << serv[1][0] << " " << serv[1][1] << " " << serv[1][2] << " " << serv[1][3] << " " << serv[1][4] << " " << serv[1][5] <<endl;	
	  //cout << vertex[0] << " " << vertex[1] << " " << vertex[2] << endl;
	 
	 
	  //Saving only the (2) lines associated to the vertex

	  if(!gotosave){
	    if(vertex[0]<=0 || vertex[1]<=0 || vertex[2]<=0){idcode = 998*100 + idcode; gotosave=true;}
	    if(vertex[0]>=124 || vertex[1]>=64 ) {idcode = 998*100 + idcode; gotosave=true;}
	    if(vertex[1]>=36 || vertex[1]<=26) {idcode = 998*100 + idcode; gotosave=true;}  
	  }
	
      

      //cout << entry-1 << " " << idcode << endl;
      
      if(!gotosave){
	for(auto &&ll: serv){
	  if(ll.first==ibeam || ll.first==itrack) {	
	    //cout << ll.second[3] << " " << ll.second[4] << " " << ll.second[5] << endl;
	    if(vertex[0]<ll.second[0]){
	      Int_t sign_y = (ll.second[1]-vertex[1])/abs(ll.second[1]-vertex[1]);
	      Int_t sign_z = (ll.second[2]-vertex[2])/abs(ll.second[2]-vertex[2]);	
	      Int_t sign_x = (ll.second[0]-vertex[0])/abs(ll.second[0]-vertex[0]);		
	      if(sign_x!=ll.second[3]/abs(ll.second[3]))ll.second[3]= (-1)*ll.second[3];
	      if(sign_y!=ll.second[4]/abs(ll.second[4]))ll.second[4]= (-1)*ll.second[4];
	      if(sign_z!=ll.second[5]/abs(ll.second[5]))ll.second[5]= (-1)*ll.second[5];
	    }
	    else {
	      Int_t sign_y = (vertex[1]-ll.second[1])/abs(ll.second[1]-vertex[1]);
	      Int_t sign_z = (vertex[2]-ll.second[2])/abs(ll.second[2]-vertex[2]);	
	      Int_t sign_x = (vertex[0]-ll.second[0])/abs(ll.second[0]-vertex[0]);		
	      if(sign_x!=ll.second[3]/abs(ll.second[3]))ll.second[3]= (-1)*ll.second[3];
	      if(sign_y!=ll.second[4]/abs(ll.second[4]))ll.second[4]= (-1)*ll.second[4];
	      if(sign_z!=ll.second[5]/abs(ll.second[5]))ll.second[5]= (-1)*ll.second[5];				
	    }
	    //cout << ll.second[3] << " " << ll.second[4] << " " << ll.second[5] << endl;	
	  }	
	}		
      
      
	Float_t tt[2]={0,0};
	TVector3 l1(serv[ibeam][3],serv[ibeam][4],serv[ibeam][5]);
	TVector3 l2(serv[itrack][3],serv[itrack][4],serv[itrack][5]);
	TVector3 xaxis(1,0,0);    
	TVector3 yaxis(0,1,0);
	tt[0]=GetTheta(l1,xaxis);
	tt[1]=GetTheta(l2,xaxis);
      
	Int_t itemp=0;
	Int_t hbeam= ibeam, htrack= itrack; // storing the original flag to pick uo them latelyin outline, h3, ...
	//cout << tt[0] << " " << tt[1] << endl;
	if(tt[0]>tt[1]){ // if the order was inverted 	
	  itemp = itrack;
	  itrack = ibeam;
	  ibeam = itemp;
	}
    
	for(auto &&ll: serv){
	  if(ll.first==ibeam || ll.first==itrack) {		
	    if(ll.first==itrack){
	      Int_t sign_y = (ll.second[1]-vertex[1])/abs(ll.second[1]-vertex[1]);
	      Int_t sign_z = (ll.second[2]-vertex[2])/abs(ll.second[2]-vertex[2]);	
	      Int_t sign_x = (ll.second[0]-vertex[0])/abs(ll.second[0]-vertex[0]);
	      if(sign_x!=ll.second[3]/abs(ll.second[3]))ll.second[3]= (-1)*ll.second[3];
	      if(sign_y!=ll.second[4]/abs(ll.second[4]))ll.second[4]= (-1)*ll.second[4];
	      if(sign_z!=ll.second[5]/abs(ll.second[5]))ll.second[5]= (-1)*ll.second[5];
	    }
	    //cout << ll.second[3] << " " << ll.second[4] << " " << ll.second[5] << endl;
	    outlines.emplace(ll.first, ll.second);
	  }
	}	
	serv.clear(); 
	    	
	//-----
	//compute the angles;
	//-----
     
	TVector3 ll[2];
	for(int i=0; i<3; i++){
	  ll[0][i]=outlines[hbeam].at(i+3);
	  ll[1][i]=outlines[htrack].at(i+3);
	}
       		
	Float_t the3d_xx[2]={GetTheta(ll[ibeam],xaxis),GetTheta(ll[itrack],xaxis)};		
		
	saved_lines.push_back(outlines[htrack]);
	saved_lines.push_back(outlines[hbeam]);
			
		
	//if(abs(atan(ll[ibeam][1]/ll[ibeam][0]))*RadToDeg()>2) continue; //fascio torto, mylar, 2 tracks o fit non riuscito
   
	theta_xx[0]=GetTheta(ll[ibeam],xaxis)*RadToDeg();
	theta_xx[1]=GetTheta(ll[itrack],xaxis)*RadToDeg();
	phi_yy[0]=GetTheta(ll[ibeam],yaxis)*RadToDeg();
	phi_yy[1]=GetTheta(ll[itrack],yaxis)*RadToDeg();
		
	Double_t Angles[2];
	GetPartAnglesFromTheBeam(ll[itrack],ll[ibeam], Angles);
	theta_part=Angles[0]*RadToDeg();
	phi_part=Angles[1]*RadToDeg();
			       
      	//cout << phi_part << " " << Phi0 << endl;
				
	//---
	//Is inside or not? Check the border of the physical cube
	//---		
	TH2F *hxy = (TH2F*) h3[htrack]->Project3D("yx");
	TH2F *hzy = (TH2F*) h3[htrack]->Project3D("zy");
	Int_t zbin_beam=0;
	for(int iz=1; iz<=hzy->GetNbinsY(); iz++){
	  Float_t min=hzy->GetYaxis()->GetBinLowEdge(iz);
	  Float_t max=hzy->GetYaxis()->GetBinUpEdge(iz);
	  if(vertex[2]<max && vertex[2]>min){
	    zbin_beam=iz;
	    break;
	  }
	}
			
	Int_t zbin_min = zbin_beam - (int)(100./vdrift/sampling_period);
	Int_t zbin_max = zbin_beam + (int)(70./vdrift/sampling_period);
		
	/*cout << hzy->GetNbinsY() << endl;
	  cout << zbin_beam << " " << zbin_min << " "  << zbin_max << " " << zbin_max - zbin_min << endl;
	  cout << vertex[2] << " " << hzy->GetYaxis()->GetBinCenter(zbin_min) <<  " " << hzy->GetYaxis()->GetBinCenter(zbin_max) << " " <<  hzy->GetYaxis()->GetBinCenter(zbin_max)-hzy->GetYaxis()->GetBinCenter(zbin_min) << endl;
	  cout << " \n";*/
		
	Double_t border = hxy->Integral(1,64,32,32) +
	  hxy->Integral(64,64,6,32) +
	  hxy->Integral(1,64,6,6) +
	  hxy->Integral(1,1,6,32) +
	  hzy->Integral(1,32,zbin_min,zbin_min)+
	  hzy->Integral(1,32,zbin_max,zbin_max);
				  
				  
	if(border>0) inside=false;
	else inside=true;				
				 
	delete hxy;
	delete hzy;
	eres_part=0; 
	range_part=0;
	
	//--
        //Eres
	//--
      
        for(auto &&hit : *hits){
	    if(hit.getGlobalChannelId()>19999) {
	    
	    }
	    else{
	     int iflag= hit.getHoughFlag(); //index of the lines and point clouds - 0 is the beam - 1 is the track == lines.first
	     Double_t charge=hit.getPeakHeight();
	    
	     if(iflag == htrack) eres_part += charge*cal;
	     if(iflag == hbeam) eres_beam += charge*cal;
	    }
	}
	
	if(eres_part>10000) continue;
      
      	//--
        //RANGE
	//--
      
	TVector3 vvertex(vertex[0],vertex[1],vertex[2]);
	//cout << vertex[0] << " " << vertex[1] << " " << vertex[2] << endl;
	for(int i=1; i<=h3[htrack]->GetNbinsX(); i++){
	  for(int j=1; j<=h3[htrack]->GetNbinsY(); j++){
	    for(int k=1; k<=h3[htrack]->GetNbinsZ(); k++){
				
	      if(h3[htrack]->GetBinContent(i,j,k)<=0) continue;
								
	      TVector3 p(h3[htrack]->GetXaxis()->GetBinCenter(i), h3[htrack]->GetYaxis()->GetBinCenter(j), h3[htrack]->GetZaxis()->GetBinCenter(k));
	      //cout << p[0] << " " << p[1] << " " << p[2] << endl;
	      double t = ll[itrack].Dot(p-vvertex)/ll[itrack].Mag2();
	      TVector3 h = vvertex + ll[itrack]*t; 
	      //cout << abs((vvertex-h).Mag()) << endl;
				
				
	      if(range_part<abs((vvertex-h).Mag())) range_part = abs((vvertex-h).Mag());
	      else continue;				
	    }
	  }
	}	
		
	/*Int_t ide=0;
	Float_t DE=0;
	if(inside){
	  for(int i=0; i<NN; i++) if(er[i]>eres_part && er[i+1]<eres_part) {ide=i; break;}
	  DE=de[ide];
	}
	else DE=0;
	eres_part += DE;*/
		
	float ebeam_lab=20*50*1000. - 1965.48; // keV - DE mylar
		
	float vv= 300.*sqrt(2*eres_part/1000./4./931.5);
	v_part[0]=vv*ll[itrack][0];
	v_part[1]=vv*ll[itrack][1];
	v_part[2]=vv*ll[itrack][2];
		
	float vbeam_cm[3]={0,0,0};	
	float vcm= 20 * sqrt(2*ebeam_lab/1000./20./931.5)*300. /24.; // in mm/ns
				
	v_part_cm[0]=v_part[0]-vcm; //in mm/ns
	v_part_cm[1]=v_part[1];
	v_part_cm[2]=v_part[2];	
		
	vbeam_cm[0]= sqrt(2*ebeam_lab/1000./20./931.5)*300. - vcm;
	vbeam_cm[1]=0;
	vbeam_cm[2]=0;
		
	float vqp_cm[3];
	vqp_cm[0] = -v_part_cm[0]* 4. / 20.;
	vqp_cm[1] = -v_part_cm[1]* 4. / 20.;
	vqp_cm[2] = -v_part_cm[2]* 4. / 20.;		
		
	float vv_cm=0;
	float vv_beam_cm=0;
	float vv_qp_cm=0;
		
	for(int k=0; k<3; k++) {
	  vv_cm+=v_part_cm[k]*v_part_cm[k];
	  vv_beam_cm+=vbeam_cm[k]*vbeam_cm[k];
	  vv_qp_cm+=vqp_cm[k]*vqp_cm[k];
	}
	vv_cm=sqrt(vv_cm);
	vv_beam_cm=sqrt(vv_beam_cm);
	vv_qp_cm=sqrt(vv_qp_cm);
						
	eres_part_cm=   0.5* 4 * 931.5 * (vv_cm*vv_cm/300./300.) * 1000.; //keV		
	ex=eres_part*(2*sqrt(4./20. * (ebeam_lab)/eres_part)*cos(theta_part*DegToRad())-(1+4./20.)) / 1000.;
		
	theta_part_cm = 180-abs(atan(vv*sin(theta_part*DegToRad())/(vv*cos(theta_part*DegToRad())-vcm))*RadToDeg()); ;
	phi_part_cm = phi_part;
	theta_ne_cm = 180- theta_part_cm;
      
	idcode = 100*100 + idcode;
	gotosave = true;
      }

      
      //cout << theta_part_cm << " " << theta_ne_cm << endl;
		
      //----
      //store the event and fill the ttree
      //----
      if(gotosave){		
	event->setEventNumber(*evnum);
	event->setIsgood(true);
	tout[lor.first-ff]->Fill();
      }
      
    }//end loop entries
    fout->cd();
    fout->WriteTObject(tout[lor.first-ff],tout[lor.first-ff]->GetName());
    //break;
  }//end loop ttre
  fout->Close();  
  fin->Close();
} //the end
  


map<int,vector<float>> buildOSCARmap(TString lookup){

  float oscar_cols=12;
  float oscar_rows=7;
  Double_t wx_ats=64, wy_ats=32, wz_ats=85;
  Double_t wx_o=5, wy_o=0.1, wz_o=5;
  Double_t morto_x=1.3, morto_z_up=2.8, morto_z_down=1.6;
  Double_t y_oscar= 65;
  Double_t z_oscar=50;
  Double_t x_oscar=-12;
  
 
  map<int, vector<float>> xy;
  vector<float> temp;
   
  ifstream in(lookup);
  pair<int,int> col_row;
  if(!in){
    cout << "Error while trying to open lookup table file " << lookup << endl;
    vector<float> temp;
    temp.push_back(-1);
    xy.emplace(-1,temp);
    return xy;
  }

  string line;
  getline(in,line); //la prima riga � intestazione
  
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

    if(type<3) continue; //not oscar
    if(chan==11 || chan==22 || chan==45 || chan==56) continue; //no fpn;
    
    int gid= chan+aget*100+asad*1000+cob*10000; 
    
    float bx = col-1; //0 - 12
    float by = row-1; // 0 - 8
    
    float pd_center_x = x_oscar + 2*wx_o*bx + (2*bx)*morto_x + wx_o;
    float pd_center_z = z_oscar + by*morto_z_up + (by+1)*morto_z_down + 2*wz_o*by + wz_o; ;
    float pd_center_y=0; 
    if(nom=="OSCAR_L") pd_center_y = -y_oscar;
    else if (nom=="OSCAR_R") pd_center_y= 64 +  y_oscar;
     
    cout << nom << " " << bx << " " << by << " " << pd_center_x << " " << pd_center_y << " " << pd_center_z << endl; 
    
    temp.clear();
    temp.push_back(pd_center_x);
    temp.push_back(pd_center_y);
    temp.push_back(pd_center_z);
    
    xy.emplace(gid,temp);
    
  }//end while

  return xy;

}


map<int,tuple<int, float, string>> load_list_of_runs(TString name){    

  ifstream list_of_runs(name);
  map<int,tuple<int,float,string>> lof;
  if(!list_of_runs){
    cout << "Error while trying to open list_of_run file " << name << endl;
    lof.emplace(-1,make_tuple(-1,-1,"-1"));
  }
  string line;
  int nline=0;
  int ifile=0, irun=0;
  float ivelo=-1;
    
  while(getline(list_of_runs,line)){
    nline++;
    if(line.length()<=0) continue;
    if(line[0]=='#') continue;
    stringstream ss;
    string sys="-1";
    ss.str(line);
	 
    ss>>irun; //>>ivelo>>sys;
    lof.emplace(nline,make_tuple(irun,ivelo,sys));
    ifile++;
    
  }	
  return lof;
	
}    



void DistancePointToLine_weigheted(int &npar, double *gin, double &fval, double *par, int iflag){
  
  double chi2 = 0;
  double etot = 0;
    
  TH3F *h3 = (TH3F*)TVirtualFitter::GetFitter()->GetObjectFit();;
    
  int xbins=h3->GetNbinsX();
  int ybins=h3->GetNbinsY();
  int zbins=h3->GetNbinsZ();
        
    
  TVector3 a(par[0],par[1],par[2]);
  TVector3 b(par[3],par[4],par[5]);
    
  for(int i=1; i<=xbins; i++){
    for(int j=1; j<=ybins; j++){
      for(int k=1; k<=zbins; k++){
	if(h3->GetBinContent(i,j,k)<=0) continue;
	double xx, yy, zz, ee;
                    
	ee=h3->GetBinContent(i,j,k);
	xx=h3->GetXaxis()->GetBinCenter(i);
	yy=h3->GetYaxis()->GetBinCenter(j);
	zz=h3->GetZaxis()->GetBinCenter(k);
                    
	TVector3 p(xx,yy,zz);                    
	double t = b.Dot(p-a)/b.Mag2();
                    
	TVector3 h = a + b*t; 
                    
	double d = (p-h).Mag();
                    
	chi2 += ee*ee*pow(d,2);
	etot += pow(ee,2);
      }
    }
  }
    
  fval=chi2/etot;
  //cout << fval << endl;
       
}


TGraph2D *create_graph(vector<double> a, vector<double> b){

  TGraph2D *g = new TGraph2D();
  g->SetMarkerStyle(20);
  if(a.size()!=3 && b.size()!=3 ) {cout << "NO lines" << endl; return NULL;}
  for(int i=-100; i<100; i++){
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

void clean_tgraph(TGraphErrors *g){
    
  Int_t npoints=g->GetN();
  if(g->GetN()>0){
    for(int i=0; i<npoints; i++){
      g->RemovePoint(g->GetN()-1);     
    }    
  }
}


void get_vertex(vector<double> ll, vector<double> ll2, Double_t vertex_temp[]){
    
  //the idea is to find the point which minimize the distance from the input lines
    
  TVirtualFitter *vertex_fitter = TVirtualFitter::Fitter(0,3);
  vertex_fitter->SetDefaultFitter("Minuit");
  vertex_fitter->SetErrorDef(1);    // Chi-square minimization

  double arglist[3];
  arglist[0] = -1;
  vertex_fitter->ExecuteCommand("SET PRINT", arglist, 1);
  vertex_fitter->ExecuteCommand("SET NOW", arglist, 1);
        
  // each rows contains the parameters of a line
  // cols 0, 1, 2 contains intercept components
  // "    3, 4, 5  "   "   direction  "    "
       
  Double_t l1[6]={ll[0],ll[1],ll[2],ll[3],ll[4],ll[5]};
  Double_t l2[6]={ll2[0],ll2[1],ll2[2],ll2[3],ll2[4],ll2[5]};
        
  vertex_fitter->SetParameter(0, "xV", 64, 0.0001, 0,128);
  vertex_fitter->SetParameter(1, "yV", 32, 0.0001, 0,64);
  vertex_fitter->SetParameter(2, "zV", l1[2], 0.0001, 0,9999);
        
  TVectorD line1; line1.Use(6,l1);
  TVectorD line2; line2.Use(6,l2);
        
  TMatrixD lines(2,6);
  TMatrixDRow(lines,0) = line1;
  TMatrixDRow(lines,1) = line2;
        
  vertex_fitter->SetObjectFit(&lines);
  vertex_fitter->SetFCN(VertexFitterFunction);
 
  arglist[0] = 1000; // number of function calls 
  arglist[1] = 0.005;    // tolerance 
  vertex_fitter->ExecuteCommand("MIGRAD",arglist,0);
 
  //save the results
  for(int i=0; i<3; i++) {
    vertex_temp[i] = vertex_fitter->GetParameter(i);
    //cout << vertex_temp[i] << endl;
  }
        
        
  delete vertex_fitter;
        
  TVector3 p(vertex_temp[0],vertex_temp[1], vertex_temp[2]);
  for(int i=0; i<lines.GetNrows(); i++){
    TVector3 a(lines[i][0], lines[i][1], lines[i][2]);
    TVector3 b(lines[i][3], lines[i][4], lines[i][5]);
    vertex_temp[i+3] = distance_point_line(p,a,b);
  }
        
  if(vertex_temp[3]<2 && vertex_temp[4]<2){
  }
  else {
    vertex_temp[3]=9999;
    vertex_temp[4]=9999;
    vertex_temp[0]=0;
    vertex_temp[1]=0;
    vertex_temp[2]=0;
  }
}

void VertexFitterFunction(int &npar, double *gin, double &sum, double *par, int iflag){
    
  TMatrixD lines = *((TMatrixD*)(TVirtualFitter::GetFitter()->GetObjectFit())); 
 
  TVector3 p(par[0], par[1], par[2]);
 
  double chi2 = 0;
 
  for(int i=0; i<lines.GetNrows(); i++){
    TVector3 a(lines[i][0], lines[i][1], lines[i][2]);
    TVector3 b(lines[i][3], lines[i][4], lines[i][5]);
                    
    double d = distance_point_line(p,a,b);
                    
    chi2 += d*d;
  }
    
  sum = chi2;
}

Double_t distance_point_line(TVector3 p, TVector3 a, TVector3 b){
    
  double t = b.Dot(p-a)/b.Mag2();
  TVector3 h = a + b*t; 
  return (p-h).Mag();
}

Float_t GetThetaPlane(TVector3 a, TVector3 ref){
  Float_t mod_a=0, mod_ref=0;
  Float_t pro=0;
  for(int i=0; i<2; i++){;
    mod_ref+=ref[i]*ref[i];
    mod_a+=a[i]*a[i];
    pro+=a[i]*ref[i];
  }
  if(a[1]>0) return TMath::ACos(pro/(sqrt(mod_a)*sqrt(mod_ref)));
  else return -TMath::ACos(pro/(sqrt(mod_a)*sqrt(mod_ref)));
}


Double_t bragg_function(Double_t *x, Double_t *par){

  Double_t f = par[0]*TMath::Exp(par[3]*par[3]*par[2]*par[2]/2+par[3]*(x[0]-par[1]))*(1-TMath::Erf(-(par[1]-x[0])/sqrt(2)/par[2]+par[3]*par[2]/sqrt(2)));
  return f;
  
}

Float_t GetTheta(TVector3 a, TVector3 ref){
  Float_t mod_a=0, mod_ref=0;
  Float_t pro=0;
  for(int i=0; i<3; i++){;
    mod_ref+=ref[i]*ref[i];
    mod_a+=a[i]*a[i];
    pro+=a[i]*ref[i];
  }
  return abs(TMath::ACos(pro/(sqrt(mod_a)*sqrt(mod_ref))));
   
}

Float_t GetPhi(TVector3 a, TVector3 ref){
  Float_t mod_a=0, mod_ref=0;
  Float_t pro=0;
  for(int i=1; i<3; i++){;
    mod_ref+=ref[i]*ref[i];
    mod_a+=a[i]*a[i];
    pro+=a[i]*ref[i];
  }    
  if(a[2]>=0) {
    return TMath::ACos(pro/(sqrt(mod_a)*sqrt(mod_ref)));
  }
  else{
    return abs(2*TMath::Pi()-TMath::ACos(pro/sqrt(mod_a)*sqrt(mod_ref)));
  }
}


void GetThetaPhi(TVector3 b, TVector3 a, Float_t Angles[]){
    
  Float_t mod_a=0, mod_b=0;
  Float_t pro=0;
  a={1,0,0};
  for(int i=0; i<3; i++){;
    mod_b+=b[i]*b[i];
    mod_a+=a[i]*a[i];
    pro+=a[i]*b[i];
  }

  Float_t Theta = abs(TMath::ACos(pro/(sqrt(mod_a)*sqrt(mod_b))));
    
    
  mod_a=0; mod_b=0; pro=0;
  a={0,1,0};
  for(int i=1; i<3; i++){;
    mod_b+=b[i]*b[i];
    mod_a+=a[i]*a[i];
    pro+=a[i]*b[i];
  }
    
  Float_t Phi = TMath::ACos(pro/(sqrt(mod_a)*sqrt(mod_b)));
    
  if(b[2]>=a[2]) {
    Angles[0]=Theta; 
    Angles[1]=Phi;
  }
  else{
    Angles[0]=Theta;
    Angles[1]=abs(2*TMath::Pi()-Phi);
  }
  
}


void GetPartAnglesFromTheBeam(TVector3 lipart,TVector3 libeam, Double_t Angles[]){
  //Rotation of ibeam to allineate along (1,0,0)
  TVector3 xaxis(1,0,0);
  Float_t angle1 = GetThetaPlane(libeam,xaxis);

  libeam.RotateZ(-angle1);
  Float_t sign=libeam[2]/abs(libeam[2]);
  Float_t angle2 = TMath::ACos(libeam[0]/libeam.Mag());
  libeam.RotateY(angle2*sign);

  //Rotation of ipart with the same angles
  lipart.RotateZ(-angle1);
  lipart.RotateY(angle2*sign);

  //Compute the angles Theta3D and Phi of ipart w.r.t.  ibeam
  Float_t aa[2];
  GetThetaPhi(lipart,libeam,aa);
  Angles[0]=aa[0];
  Angles[1]=aa[1];
}
		  
