//Per C++
#include <iostream>
#include <algorithm>   
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
#include <TLine.h>
#include <TVirtualFitter.h>
#include <TVector3.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <TF1.h>
#include <TGraphErrors.h>

//Per ARDA
#include "../src/cRawEvent.h"
#include "../src/cHit.h"

//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"

#define vdrift 0.01297 //mm/ns
#define nsample 512 //campioni
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


map<int,tuple<int,float,string>> load_list_of_runs(TString name);
TH2F* build_padplane(TString lookup);
int nhit(TH3*h,int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, int thr);
map<int,std::pair<float,float>> buildXYmap(TString lookup);
pair<int, int> getPadFromGlobalID(int gsel, TString lookup);
pair<float, float> getXYFromGlobalID(int gsel, TString lookup);
pair<int,int> size(TH2*h, int thr, int yinf, int yup, TString s);
vector<pair<int,int>>  time_tracks(TH2*h,int ybinmin, int ybinmax, int zmin, int zmax);
void terminal_input(Int_t event, Int_t x, Int_t y, TObject *selected);
void clean_th1(TH1* h);
void clean_th2(TH2* h);
void clean_th3(TH3* h);
map<int,int> peak_search(TH1*h, int thr, int range);

int NPEAKS =5;
int ica;
string in;


int main (int argc, char ** argv){

    //----
    //Input File
    //----
    TString list_run=argv[2];
    TString path_to_files = argv[1];
    TString lookup_name = argv[3];
    TString out_name = argv[4];
    
    map<int,tuple<int,float,string>> list_of_runs=load_list_of_runs(list_run);
    Int_t nfiles=0;
    
    cout << "List of files to analize:" << endl;
    for(auto &&lor:list_of_runs){
    	cout << lor.first << " " << get<0>(lor.second)  << endl; //<< " " << get<1>(lor.second) << " " << get<2>(lor.second) << endl;
    	nfiles++;
    }    
    
    map<int, pair<float,float>> xy_map =  buildXYmap(lookup_name);
    //cout << "GiD vs XY positions:" << endl;
    //for(auto &&xy: xy_map){
    //	cout << xy.first << " " << xy.second.first << " " << xy.second.second << endl;
    //}
    
    //----
    //Tools for the analysys
    //----
    map<int, pair<int,int>> v_ybins_beam;
    map<int,int> zbeam_bin;
    map<int, pair<int,int>> z_in_time;
    map<int,int> is_a_good_beam;
    map<int,int> zcode;
    
     TH1F* htime =  new TH1F("htime","htime",nsample,0,nsample*sampling_period+1);
     htime->SetXTitle("ns");
     TH2F* hzy =  new TH2F("hzy","hzy",nr,rinf,rup,nsample,0,nsample*sampling_period+1);
      hzy->SetXTitle("y pad");
      hzy->SetYTitle("ns");
      TH2F* hyx =  new TH2F("hyx","hyx",ncol,cinf,cup,nr,rinf,rup);
      hyx->SetXTitle("x pad");
      hyx->SetYTitle("y pad");

      TH3F *hxyz = new TH3F("hxyz","hxyz",ncol,cinf,cup,nr,rinf,rup,nsample,0,nsample*sampling_period+1);
      hxyz->SetXTitle("x pad");
      hxyz->SetYTitle("y pad");
      hxyz->SetYTitle("z tbin");  
    
    
    //----
    //Output File
    //----
    cEvent *event = new cEvent();
    TFile *fout = new TFile(out_name,"RECREATE");
    TTree *tout[nfiles];
    Int_t ff=list_of_runs.begin()->first;
    fout->cd();
    for(auto &&lor: list_of_runs){
    	string title=get<2>(lor.second);
    	tout[lor.first-ff] = new TTree(Form("EventTree_%d",get<0>(lor.second)),Form("EventTree for r.%d system with XYZ positions", get<0>(lor.second)));
	tout[lor.first-ff]->Branch("event",&event);
    }
    
    //---
    //Loop on the files
    //---
    
    vector<cHitxyz> event_hits;
    cHitxyz temp_hit;     
    TFile *fin[nfiles];
    TTree *tin[nfiles];
    
    for(auto &&lor: list_of_runs){
    	cout << "Reading " << Form("%s/ACTAR_%d.root",path_to_files.Data(),get<0>(lor.second)) << endl;
    	
	fin[lor.first-ff] = new TFile(Form("%s/ACTAR_%d.root",path_to_files.Data(),get<0>(lor.second)),"R");
    	tin[lor.first-ff] = (TTree*) fin[lor.first-ff]->Get("rawEventTree");
    	
	TTreeReader reader(tin[lor.first-ff]);
	TTreeReaderValue<int> evnum(reader,"eventnum");
  	TTreeReaderValue<vector<cHit>> hits(reader,"hits");
	
	Int_t entry=0;
	cout << "Reading file n." << lor.first-ff << " of " << nfiles << endl;
	cout << "Entries: " << tin[lor.first-ff]->GetEntries() << endl; 
	while(reader.Next()){
		entry++;
		
		if(entry%1000==0)cout << "Entry n.: " << entry << endl;
    		
		//clear the container
		bool good=false;
		
		event->clear();
		event_hits.clear();
    		htime->Reset();
		hzy->Reset();
		hyx->Reset();
		hxyz->Reset();		

    		z_in_time.clear();    
    		v_ybins_beam.clear();
    		zbeam_bin.clear();
    		is_a_good_beam.clear();
    		zcode.clear();
		
		 //preliminary check
		
    		for(auto&&hit: *hits){ //preliminary check
      			if(hit.getGlobalChannelId()>19999) continue; //not TPC

      			Float_t time= hit.getPeakTime()*sampling_period;
      			Float_t xx = xy_map[hit.getGlobalChannelId()].first;
      			Float_t yy = xy_map[hit.getGlobalChannelId()].second; 
      			Float_t xpad = (xx-1)/2;
      			Float_t ypad = (yy-1)/2;
      
      			if(time>upperlimit_time) continue;

      			hxyz->Fill(xpad,ypad,time,hit.getPeakHeight());
      			hzy->Fill(ypad,time);
      			hyx->Fill(xpad,ypad);

      			if(ypad>=13 && ypad<=18){ //beam row
				htime->Fill(time,1);
      			}
    		}
		
		Int_t thr=20;
    		Int_t range=5;
    		zbeam_bin=peak_search(htime,thr,range); //+- 5*80ns; N.B restituisce i BIN a cui si trovano i candidati fasci

		if(zbeam_bin.size()<1) continue;
		for(auto &&z : zbeam_bin) {
      			is_a_good_beam.emplace(z.first,false);
    		}

		//cerco la continuità nei tempi e in y
	        for(auto &&z: zbeam_bin){
	     
	     		z_in_time.emplace(z.first,make_pair(0,0));

	     		int zbeam=z.second;
	     		int zbinmin=zbeam-(int)(95./vdrift/sampling_period);
	     		if(zbinmin<0) zbinmin=0;
	     		int zbinmax=zbeam+(int)(75./vdrift/sampling_period);
	     
	    		 pair<int,int> temp = make_pair(0,0);
	     		temp = size(hzy,1,zbeam-1,zbeam+1,"x");
	    		 v_ybins_beam.emplace(z.first,temp); //ritorna il primo e ultimo bin sopra 1;
	     		hzy->GetYaxis()->SetRange(zbinmin,zbinmax);	   

	     		//conto i pad per intervalli di tempo
	     
	     		float leftpad_up=nhit(hxyz,cinf+1,cup,rinf+1,v_ybins_beam[z.first].first-1,zbeam+range+1,zbinmax,1);
	     		float leftpad_mid=nhit(hxyz,cinf+1,cup,rinf+1,v_ybins_beam[z.first].first-1,zbeam-range,zbeam+range,1);
	     		float leftpad_low=nhit(hxyz,cinf+1,cup,rinf+1,v_ybins_beam[z.first].first-1,zbinmin,zbeam-range-1,1);	
	     
	     		float rightpad_up=nhit(hxyz,cinf+1,cup,v_ybins_beam[z.first].second+1,rup,zbeam+range+1,zbinmax,1);
	     		float rightpad_mid=nhit(hxyz,cinf+1,cup,v_ybins_beam[z.first].second+1,rup,zbeam-range,zbeam+range,1);
	     		float rightpad_low=nhit(hxyz,cinf+1,cup,v_ybins_beam[z.first].second+1,rup,zbinmin,zbeam-range-1,1);	

	     		float pad[10]={leftpad_up,leftpad_mid,leftpad_low,rightpad_up,rightpad_mid,rightpad_low,leftpad_up+leftpad_mid,leftpad_mid+leftpad_low,rightpad_up+rightpad_mid,rightpad_mid+rightpad_low};

	     		bool table[10];
	     		for(int ic=0; ic<6; ic++) {
	       			if(pad[ic]>10)  table[ic]=true;
	       			else table[ic]=false;
	     		}
	     		if(pad[0]>0&&pad[1]>0 && pad[6]>10){
	       			table[6]=true;
	       			table[0]=false;
	       			table[1]=false;
	     		}
	     		else table[6]=false;
	     		if(pad[2]>0&&pad[1]>0 && pad[7]>10){
	       			table[7]=true;
	       			table[1]=false;
	       			table[2]=false;
	     		}
	     		else table[7]=false;
	     		if(pad[3]>0&&pad[4]>0 && pad[8]>10){
	       			table[8]=true;
	       			table[3]=false;
	       			table[4]=false;
	     		}
	     		else table[8]=false;
	     		if(pad[5]>0&&pad[4]>0 && pad[9]>10){
	       			table[9]=true;
	       			table[4]=false;
	       			table[5]=false;
	     		}
	     		else table[9]=false;

	     
	     		for(int ic=0; ic<10; ic++){
	       			bool bad=false;
	       			if(table[ic]==false) {
	         		zcode.emplace(z.first*100+ic,-99); 
	         		bad=false;
	         		//cout << ic << " false " << z.second << endl;
	         		continue;
	       			}

	       			int ybinmin=0;
	       			int ybinmax=0;
	       			if(ic==0 || ic==2){ybinmin=rinf+1; ybinmax=v_ybins_beam[z.first].second-1; }
	       			else if(ic ==1 || ic==6 || ic==7){ybinmin=rinf+1; ybinmax=v_ybins_beam[z.first].first-1; }
	       			else if (ic==3 || ic==5){ybinmin=v_ybins_beam[z.first].first+1, ybinmax=rup;}
	       			else if (ic==4 || ic==8 || ic==9){ybinmin=v_ybins_beam[z.first].second+1, ybinmax=rup;}

	       			int zmin=0;
	       			int zmax=0;
	       			if(ic==0 || ic==3){zmin=zbeam+range+1; zmax=zbinmax;}
	       			else if(ic==1 || ic==4) {zmin=zbeam-range; zmax=zbeam+range;}
	       			else if(ic==2 || ic==5) {zmin=zbinmin; zmax=zbeam-range-1;}
	       			else if(ic==6 || ic==8) {zmin=zbeam-range; zmax=zbinmax;}
	       			else if(ic==7 || ic==9) {zmin=zbinmin-range; zmax=zbeam+range;}

	       		if(zmin<0) zmin=0;

	       		//tempi nella finestra
	       		vector<pair<int,int>> temp_time = time_tracks(hzy,ybinmin,ybinmax,zmin,zmax);
	       		for(uint j=0; j<temp_time.size(); j++) {

	         		
	         		bad=false;
	         		float ref=0, val=0, first=0, last=0;	 
	         		if(bad!=true){

	           	               if(ic==0 || ic==3){
	             	                       ref=zbeam+range;
	             	                       val=temp_time[j].first;
	             	                       last=temp_time[j].second+1;
	             	                       first=zbeam-range-1;
	           	               }

	           	               if(ic==2 || ic==5){
	             	                       ref=zbeam-range;
	             	                       val=temp_time[j].second;
	             	                       last=zbeam+range+1;
	             	                       first=temp_time[j].first-1;
	           	               }

	            	               if(ic==1 || ic==4){
	             	                       ref=zbeam;
	             	                       val=temp_time[j].first;
	             	                       last=zbeam+range+1;
	             	                       first=zbeam-range-1;
	           	               }

	            	               if(ic==6 || ic==8){
	              	                       ref=zbeam;
	              	                       val=temp_time[j].first;
	              	                       last=temp_time[j].second;
	              	                       first=zbeam-range-1;
	            	               }

	           	               if(ic==7 || ic==9){
	              	                       ref=zbeam;
	              	                       val=temp_time[j].second;
	              	                       last=zbeam+range+1;
	              	                       first=temp_time[j].first-1;
	            	               }
	           
	         		}

	         
	         	if(ref==0 && val==0) continue;

	         	TH1D *hy = hzy->ProjectionX("hy",first,last);
	         
	        	if((ic<3 || ic==6 || ic==7) && hy->GetBinContent(ybinmax)==0) 	   bad=true;
	        	else if (((ic>=3 && ic<6) || ic==8 || ic==9) && hy->GetBinContent(ybinmin)==0) bad=true;
	        	
			if(abs(ref-val)>10) bad=true;
	        	

	        	if(bad!=true){
	        	  
	        	  int npad_true=0;
	        	  if(ic<3 || ic==6 || ic==7) npad_true=nhit(hxyz,1,64,1,13,first,last,1);
	        	  if(ic==3 || ic==4 || ic==5 || ic==8 || ic==9) npad_true=nhit(hxyz,1,64,21,32,first,last,1);

	        	  if(npad_true<10) bad=true;
	        	  if(bad==true) {
			  	delete hy;
			  	continue;
			  }
	        	 
	        	  pair<int,int> bin_time=make_pair(first,last);
	        	  z_in_time[z.first]=bin_time;
	        	  is_a_good_beam[z.first]=true;
	        	  good=true;
	        	  zcode.emplace(z.first*100+ic,1);
			  delete hy;
	        	}     
	       	}
	     }
	   }
	   hzy->GetXaxis()->UnZoom();
	   hzy->GetYaxis()->UnZoom();

	   if(good==false) continue;
		
		//copy on the output tree
		event_hits.clear();
		event->clear();
		map<double,bool> check_map;
		//cout << "EVENTOOOOOO    " << zbeam_bin.size() << endl;
		for(auto &&hit: *hits){
			if(hit.getGlobalChannelId()>19999){
					temp_hit.clear();
		     	    		temp_hit.setPeakHeight(hit.getPeakHeight());
    		     	    		temp_hit.setGlobalChannelId(hit.getGlobalChannelId());
    		     	    		temp_hit.setPeakTime(hit.getPeakTime());
    		     	    		temp_hit.setXYZ(9999,9999,9999);
					//cout << hit.getGlobalChannelId() << " " << hit.getPeakTime() << " " << hit.getPeakHeight() << endl;
					event_hits.push_back(temp_hit);
			} //not TPC
			else {
			Int_t gid = hit.getGlobalChannelId();
      			Float_t max_adc = hit.getPeakTime();
			Float_t max = hit.getPeakHeight();
			Float_t xpos = xy_map[gid].first;
      			Float_t ypos = xy_map[gid].second;
			Float_t zpos = vdrift*max_adc*sampling_period;
			Float_t time= hit.getPeakTime()*sampling_period;
			//cout << (int)zpos << " " << xpos << " " << ypos << endl;
			//cout << (int)zpos*100000+xpos*100+ypos << " " << 0 << endl;
			double zz=(int)zpos;
			check_map.emplace(zz*100000+xpos*100+ypos,false);
			     
			      for(auto &&z:zbeam_bin){

    				if(is_a_good_beam[z.first]==false) continue;
	
    				if(time<hzy->GetYaxis()->GetBinCenter(z_in_time[z.first].first)) continue;
    				if(time>hzy->GetYaxis()->GetBinCenter(z_in_time[z.first].second)) continue;
	
				if(check_map[zz*100000+xpos*100+ypos]==false){
		     	    		temp_hit.clear();
		     	    		temp_hit.setPeakHeight(max);
    		     	    		temp_hit.setGlobalChannelId(gid);
    		     	    		temp_hit.setPeakTime(max_adc);
    		     	    		temp_hit.setXYZ(xpos,ypos,zpos);

					//cout << check_map[(int)zpos*10000+xpos*100+ypos] << endl;
		
					//cout << fixed << xpos << " " << ypos << " " << zpos << " " << max << " " << zz*100000+xpos*100+ypos << endl;
		
		     	    		event_hits.push_back(temp_hit);
					check_map[zz*100000+xpos*100+ypos]=true;
					}
				else {
					//cout << check_map[zz*100000+xpos*100+ypos] << endl;
					//cout << fixed << "Gia inserito: " << xpos << " " << ypos << " " << zpos << " " << max << " " <<zz*100000+xpos*100+ypos << endl;
					}
				}
				}
			}
		//cout << hits->size() << " " << event_hits.size() << endl;	
		event->setEventNumber(*evnum);
		event->setIsgood(true);
    		event->append(event_hits);
		tout[lor.first-ff]->Fill();
		//if(entry>100) break;
	}//end reader loop
	fin[lor.first-ff]->Close();
	fout->cd();
	fout->WriteTObject(tout[lor.first-ff], tout[lor.first-ff]->GetName());
    }
   
    delete  htime;
    delete hzy;
    delete hyx;
    delete hxyz;  

    cout << "Exit" << endl;
    fout->Close();
} //end main
    
    
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


map<int,pair<float,float>> buildXYmap(TString lookup){

  map<int, pair<float,float> > xy;
  
  ifstream in(lookup);
  pair<int,int> col_row;
  if(!in){
    cout << "Error while trying to open lookup table file " << lookup << endl;
    col_row=make_pair(-1,-1);
    xy.emplace(-1,col_row);
    return xy;
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

    if(cob>=2) continue;
    if(chan==11 || chan==22 || chan==45 || chan==56) continue; //no fpn;
    
    int gid= chan+aget*100+asad*1000+cob*10000;
    col_row = make_pair(col*2+1,row*2+1); //in mm;
  
    xy.emplace(gid,col_row);
    
  }//end while

  return xy;
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


map<int,int> peak_search(TH1*h, int thr, int range){

  int nfound=0;
  vector<int> xp;
  vector<int> xbin;

  int cnt=0;
  int cnt_up=0;
  int cnt_down=0;
  int cnt_up2=0;
  int cnt_down2=0;

  float time=0;
  float integral=0;
  for(int i=2; i<h->GetNbinsX(); i++){
    cnt=0;
    cnt_up=0;
    cnt_down=0;

    cnt=h->GetBinContent(i);
    cnt_up=h->GetBinContent(i+1);
    cnt_down=h->GetBinContent(i-1);
    cnt_up2=h->GetBinContent(i+2);
    cnt_down2=h->GetBinContent(i-2);

    time=h->GetBinCenter(i);
    integral=h->Integral(i-range,i+range);
    if(cnt>cnt_down && cnt>cnt_up){
      if(integral>thr){
	xp.push_back(time);
	xbin.push_back(i);
	nfound++;
      }
    }
    if(cnt>cnt_down&&cnt==cnt_up&&cnt>cnt_up2){
      if(integral>thr){
	xp.push_back(time);
	xbin.push_back(i);
	nfound++;
      }
    }
  }

  map<int,int> xxp;

  // for(int i=0; i<xp.size(); i++){
  //   cout << xbin[i] << " ";
  // }
  // cout << " \n";
  
  for(uint i=0; i<xp.size(); i++){
    if(xp.size()>1){
      if(i+1==xp.size()){
	//cout << "salvo " << xbin[i] <<   endl;
	xxp.emplace(xbin[i],xbin[i]);
	break;
      }
      else{
	for(uint j=i+1; j<xp.size(); j++){
	  //	cout << xp[i] << " " << xp[j] << endl;
	  //cout << xbin[i] << " " << xbin[j] << endl;
	  if(abs(xp[i]-xp[j])>range*h->GetBinWidth(1)) {
	    //cout << "salvo " << xbin[i] <<   endl;
	    xxp.emplace(xbin[i],xbin[i]);
	    break;
	  }
	  else{
	    //cout << "medio" << endl;
	    xp[i+1]=(xp[i]+xp[j])/2.;
	    xbin[i+1]=(xbin[i]+xbin[j])/2;
	    break;
	  }
	}
      }
    }
    else{
      xxp.emplace(xbin[i],xbin[i]);
    }
    
  }
    
  
    return xxp;
}


pair<int,int> size(TH2*h,int thr, int yinf, int yup, TString s){
   
  TH1D* hp;
  if(s=="x"){
    hp=h->ProjectionX("temp",yinf,yup);
  }
  
  pair<int,int> bins;
  int min=0;//hp->FindFirstBinAbove(thr);
  int max=0;//hp->FindLastBinAbove(thr);
  for(int i=14; i<=20; i++){
    //cout << i << " " << hp->GetBinContent(i) << endl;
    if(hp->GetBinContent(i)>=thr){
    min=i;
    break;
    }
  }
  for(int i=20; i>=14; i--){
    if(hp->GetBinContent(i)>=thr){
      max=i;
      break;
    }
  }
  bins=make_pair(min,max);
  
  delete hp;
  return bins;
  
   
}


    
int nhit(TH3*h,int xmin, int xmax, int ymin, int ymax, int zmin, int zmax, int thr){

  int npad=0;

  h->GetZaxis()->SetRange(zmin,zmax);
  h->GetXaxis()->SetRange(xmin,xmax);
  h->GetYaxis()->SetRange(ymin,ymax);
  
  TH2D *hp =(TH2D*)h->Project3D("yx");
  
  for(int i=hp->GetXaxis()->GetFirst(); i<hp->GetXaxis()->GetLast(); i++){
    for(int j=hp->GetYaxis()->GetFirst(); j<hp->GetYaxis()->GetLast(); j++){
      if(hp->GetBinContent(i,j)>thr) {
	npad++;
      }
    }
  }

  // TCanvas *c1=new TCanvas("c1","c1");
  // hp->Draw("col");
  // c1->Modified();
  // c1->Update();
  // getchar();
  // delete c1;
  
  h->GetZaxis()->UnZoom();
  h->GetYaxis()->UnZoom();
  h->GetXaxis()->UnZoom();
  delete hp;
  return npad;
}


vector<pair<int,int>>  time_tracks(TH2*h,int ybinmin, int ybinmax, int zmin, int zmax){
  h->GetYaxis()->SetRange(zmin,zmax);
  TH1D* hz = h->ProjectionY("hz",ybinmin,ybinmax);
  
  int nzero_cons=0, nfull=0;
  int start=-1, stop=-1;
  vector<pair<int,int>> serv;
  vector<pair<int,int>> picco;
  //cout << hz->GetXaxis()->GetLast() << endl;
  for(int ibin=hz->GetXaxis()->GetFirst(); ibin<=hz->GetXaxis()->GetLast(); ibin++){
    
    if(hz->GetBinContent(ibin)>0) {nfull++; nzero_cons=0;}
    if(hz->GetBinContent(ibin)==0) {nzero_cons++;}
    
    if(ibin==hz->GetXaxis()->GetFirst() && hz->GetBinContent(ibin)>0 && hz->GetBinContent(ibin+1)>0 && start==-1){
      start=ibin;
    }
    if(ibin>hz->GetXaxis()->GetFirst() && hz->GetBinContent(ibin)>0 && hz->GetBinContent(ibin-1)==0 && start==-1) {
      start=ibin;
    }  
    if(ibin<=hz->GetXaxis()->GetLast()-1 && hz->GetBinContent(ibin)>0 && hz->GetBinContent(ibin+1)==0 && stop==-1 && nfull>1){
      stop=ibin;
    }
    if(ibin==hz->GetXaxis()->GetLast() && hz->GetBinContent(ibin)>0 && hz->GetBinContent(ibin-1)>0){
      stop=ibin;
    }
    if(ibin==hz->GetXaxis()->GetLast() && hz->GetBinContent(ibin)==0){
      if(start!=-1 && stop==-1) stop=start;
    }
    
    //cout << ibin << " " << hz->GetBinContent(ibin) << " -> " << nzero_cons << " " << nfull << " -> " << start << " " << stop << endl;

    
    if(start!=-1 && stop!=-1){
      //cout << "Picco: " << start << " " << stop << endl;
      serv.push_back(make_pair(start,stop));
      start=-1;
      stop=-1;
      nzero_cons=0;
      nfull=0;
    }

    if(nzero_cons==10 || ibin==hz->GetXaxis()->GetLast()){
      int offset = h->GetYaxis()->GetFirst()-1;
      if(serv.size()>1) {
	//cout << "!!!! " << serv[0].first+offset << " " << serv[serv.size()-1].second+offset << " !!!!" << endl;
	//cout << hz->Integral(serv[0].first,serv[serv.size()-1].second) << endl;
	//if(hz->Integral(serv[0].first,serv[serv.size()-1].second)>10)

	picco.push_back(make_pair(serv[0].first+offset, serv[serv.size()-1].second+offset));
      }
      else if (serv.size()==1) {
	//cout << "!!!! " << serv[0].first << " " << serv[0].second << " !!!!" << endl;
	//if(hz->Integral(serv[0].first,serv[0].second)>100)

	picco.push_back(make_pair(serv[0].first+offset, serv[0].second+offset));
      }
      start=-1;
      stop=-1;
      nfull=0;
      nzero_cons=0;
      serv.clear();
    }
    
    
  }
  return picco;
}

