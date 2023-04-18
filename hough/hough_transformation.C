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

//Per Hough
#include "transformation/vector3d.h"
#include "transformation/pointcloud.h"
#include "transformation/hough.h"
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "transformation/eigen_install/include/eigen3/Eigen/Dense"


//Defined class
#include "../src/cHitxyz.h"
#include "../src/cEvent.h"


using Eigen::MatrixXf;
using namespace std;

double orthogonal_LSQ(const PointCloud &pc, Vector3d* a, Vector3d* b);
void do_hough_algoritm(PointCloud X, double dxu, int nlinesu, int minvotesu, int verbose, cEvent *ev);
std::map<int,tuple<int,float,string>> load_list_of_runs(TString name);


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
    
    //----
    //Output File
    //----
    cEvent *event = new cEvent();
    TFile *fout = new TFile(out_name,"RECREATE");
    TTree *tout[nfiles];
    Int_t ff=list_of_runs.begin()->first;
    Double_t e0=0, t0=0, p0=0, xx0=0;
     for(auto &&lor:list_of_runs){
    	fout->cd();
    
    	string title=get<2>(lor.second);
    	tout[lor.first-ff] = new TTree(Form("HoughEventTree_%d",get<0>(lor.second)),Form("HoughEventTree equalized for r.%d system with XYZ positions", get<0>(lor.second)));
  	tout[lor.first-ff]->Branch("Epart0", &e0, "Epart0/D");
 	tout[lor.first-ff]->Branch("Theta0", &t0, "Theta0/D");
  	tout[lor.first-ff]->Branch("Phi0", &p0, "Phi0/D");
  	tout[lor.first-ff]->Branch("X0", &xx0, "X0/D");
	tout[lor.first-ff]->Branch("event",&event);
	
	}
    
       
    //----
    //Loop
    //----
    cout << "Opening " << file_name << endl;
    TFile *fin = new TFile (file_name,"R");
    TTree *t;
    fout->cd();
    for(auto &&lor:list_of_runs){
    	    
    	cout << "Reading  TTree " << Form("EventTree_%d",get<0>(lor.second)) << " of " << nfiles << endl;
   	t = (TTree*) fin->Get(Form("EventTree_%d",get<0>(lor.second)));
	
	TTreeReader reader(t);
	TTreeReaderValue<int> evnum(reader,"eventnum");
  	TTreeReaderValue<vector<cHitxyz>> hits(reader,"hits");
	TTreeReaderValue<Bool_t> isgood(reader,"isgood");
	TTreeReaderValue<Int_t> idcode(reader,"idcode");
	TTreeReaderValue<Double_t> epart0(reader,"Epart0");
	TTreeReaderValue<Double_t> theta0(reader,"Theta0");
	TTreeReaderValue<Double_t> phi0(reader,"Phi0");
	TTreeReaderValue<Double_t> x0(reader,"X0");
	
	cout << "Entries: " << t->GetEntries() << endl; 
	
	Int_t entry=0;
	
	vector<cHitxyz> event_hits; // mi servono per non ATS
	cHitxyz temp_hit;     
   	while(reader.Next()){ 
 
        	//if(entry%100==0)cout << "Ev: " << entry << endl;
 		if(entry>100000) break;
 		
       		entry++;
		 
       		if(entry%1000==0) cout << "Entry: " << entry << endl;
        
        	event->clear();
    		event_hits.clear();
    
        	PointCloud X;
            	for(auto &&hit : *hits){
                	if(hit.getGlobalChannelId()>19999){
				temp_hit.clear();
		     	    	temp_hit.setPeakHeight(hit.getPeakHeight());
    		     	    	temp_hit.setGlobalChannelId(hit.getGlobalChannelId());
    		     	    	temp_hit.setPeakTime(hit.getPeakTime());
    		     	    	temp_hit.setXYZ(9999,9999,9999);
				//cout << hit.getGlobalChannelId() << " " << hit.getPeakTime() << " " << hit.getPeakHeight() << endl;
				event_hits.push_back(temp_hit);
			}
			else {//TPC
      
                	vector<Double_t> pos=hit.getXYZ();
                	X.insertPoint(pos[0],pos[1],pos[2]);
			
			//cout << pos[0] << " " << pos[1] << " " << pos[2] << " " << hit.getPeakHeight() << endl;
                
                 	X.insertCharge(hit.getPeakHeight());
			//X.insertCharge(1.);
                 	X.insertTime(hit.getPeakTime());
                 	X.insertGID(hit.getGlobalChannelId());
			}
			  
            	}
            
	    	if(X.points.size()<2) continue;
	  		
		X.orderCloud();	
			
       		do_hough_algoritm(X, 3, 0, 12, false, event); //PointCloud X, double dxu [mm], int nlinesu, int minvotesu, int verbose, cEvent *ev
						//*** i punti in X, e le rispettive lines, vengono già settati in event!!!
       		
		
		
		if(event->getLines().size()<=1) {
			event->setIDCode(0+*idcode); // 0 = no hough + no trigger
			event->setIsgood(false);		// 1 = no hough + ok trigger
       		}
		else   	{
			event->setIDCode(10+*idcode); //10 = ok hough + no trigger
			event->setIsgood(true); 		 //11 = ok hough + ok trigger
			}
		//cout << entry-1 << " " << event->getIDCode() << endl;	
			
		event->setIsgood(*isgood);
		event->append(event_hits);
        	event->setEventNumber(*evnum);
		e0= *epart0;
		t0= *theta0;
		p0= *phi0;
		xx0= *x0;
        	tout[lor.first-ff]->Fill();
		
    		}//end loop entries
	
	fout->cd();
	fout->WriteTObject(tout[lor.first-ff],tout[lor.first-ff]->GetName());
   }//end loop ttre
  fout->Close();  
  fin->Close();
}


void do_hough_algoritm(PointCloud X, double dxu, int nlinesu, int minvotesu, int verbose, cEvent *ev){
    
  //preparing the event and the lines to be stored  
  ev->clear();  
     
  vector<double> totalCharge;   
     
  vector<cHitxyz> event_hits;
  event_hits.clear();
  
  cHitxyz temp_hit;  
  
  std::map<int,vector<double> > found_lines;
    
  // default values for command line options
  double opt_dx = dxu;
  int opt_nlines = nlinesu;
  int opt_minvotes = minvotesu;
  int opt_verbose = verbose;
    
  // number of icosahedron subdivisions for direction discretization
  int granularity = 4;
  int num_directions[7] = {12, 21, 81, 321, 1281, 5121, 20481};
    
  // bounding box of point cloud
  Vector3d minP, maxP, minPshifted, maxPshifted;
  // diagonal length of point cloud
  double d;
  
  //common errors
  if (opt_dx < 0){
    fprintf(stderr, "Error: dx < 0!\n");
    
  }
  if (opt_nlines < 0){
    fprintf(stderr, "Error: nlines < 0!\n");
    
  }
  if (opt_minvotes < 0){
    fprintf(stderr, "Error: minvotes < 0!\n");
  
  }
  if (opt_minvotes < 2){
    opt_minvotes = 2;
  }
  if (X.points.size() < 2) {
    fprintf(stderr, "Error: point cloud has less than two points\n");

  }

  // center cloud and compute new bounding box
  X.getMinMax3D(&minP, &maxP);
  d = (maxP-minP).norm();
  if (d == 0.0) {
    fprintf(stderr, "Error: all points in point cloud identical\n");
    
  }
  X.shiftToOrigin();
  X.getMinMax3D(&minPshifted, &maxPshifted);

 
  // estimate size of Hough space
  if (opt_dx == 0.0) {
    opt_dx = d / 32.0;
  }
  else if (opt_dx >= d) {
    fprintf(stderr, "Error: dx too large\n");
   
  }
  double num_x = floor(d / opt_dx + 0.5);
  double num_cells = num_x * num_x * num_directions[granularity];
  if (opt_verbose) {
    printf("info: x'y' value range is %f in %.0f steps of width dx=%f\n",
           d, num_x, opt_dx);
    printf("info: Hough space has %.0f cells taking %.2f MB memory space\n",
           num_cells, num_cells * sizeof(unsigned int) / 1000000.0);
  }

   
  // first Hough transform
  Hough* hough;
  try {
    hough = new Hough(minPshifted, maxPshifted, opt_dx, granularity);
  } catch (const std::exception &e) {
    fprintf(stderr, "Error: cannot allocate memory for %.0f Hough cells"
            " (%.2f MB)\n", num_cells, 
            (double(num_cells) / 1000000.0) * sizeof(unsigned int));
    
  }
  hough->add(X);
  
   
  // iterative Hough transform
  // (Algorithm 1 in IPOL paper)
  PointCloud Y;	// points close to line
  double rc;
  unsigned int nvotes;
  int nlines = 0;
  do {
    Vector3d a; // anchor point of line
    Vector3d b; // direction of line

    hough->subtract(Y); // do it here to save one call

    nvotes = hough->getLine(&a, &b);
             
    if (opt_verbose) {
      Vector3d p = a + X.shift;
      printf("info: highest number of Hough votes is %i for the following "
             "line:\ninfo: a=(%f,%f,%f), b=(%f,%f,%f)\n",
             nvotes, p.x, p.y, p.z, b.x, b.y, b.z);
    }

    X.pointsCloseToLine(a, b, opt_dx, &Y);

    rc = orthogonal_LSQ(Y, &a, &b);
    if (rc==0.0) break;

    X.pointsCloseToLine(a, b, opt_dx, &Y);
    nvotes = Y.points.size();
        
    if (nvotes < (unsigned int)opt_minvotes) break;

    rc = orthogonal_LSQ(Y, &a, &b);
    if (rc==0.0) break;

    a = a + X.shift;
    
    Y.computeTotalCharge();	
    totalCharge.push_back(Y.getTotalCharge());
    nlines++;
        
    if(opt_verbose)    printf("%f %f %f %f %f %f %lu\n",a.x, a.y, a.z, b.x, b.y, b.z, Y.points.size());
    
    //Compute the center of gravity for Y taking into account the charge of the point
    double xmed=0, ymed=0, zmed=0;
    double ctot=0;
    for(uint i=0; i<Y.points.size(); i++){
        xmed+=(Y.points[i].x + X.shift.x)*Y.charge[i];
        ymed+=(Y.points[i].y + X.shift.y)*Y.charge[i];
        zmed+=(Y.points[i].z + X.shift.z)*Y.charge[i];
        ctot+=Y.charge[i];
    }
    xmed/=ctot;
    ymed/=ctot;
    zmed/=ctot;
    
    sort(totalCharge.begin(), totalCharge.end());
    
     //Storing the points and the found line
    vector<double> serv={xmed, ymed, zmed, b.x, b.y, b.z};      
    
    int temp=0;
    for(uint j=0; j<totalCharge.size(); j++){ //to sort the found_line map in a decreasin order of ctot
      //std::cout << ctot/(float)Y.points.size() << " " << totalCharge[j] << std::endl;
      
      if(ctot/(float)Y.points.size()!=totalCharge[j]) {
      temp++;
      if(temp==totalCharge.size()) cout << "NON TROVATO" << endl;
      continue;
      }
      else temp=0;
      
      //cout << j << endl;
      
      found_lines.emplace(j,serv);
    
    	for(uint i=0; i<Y.points.size(); i++){
       		temp_hit.clear();
      		 temp_hit.setPeakHeight(Y.charge[i]);
       		temp_hit.setPeakTime(Y.time[i]);
       		temp_hit.setGlobalChannelId(Y.gid[i]);
       
       		temp_hit.setXYZ(Y.points[i].x + X.shift.x, Y.points[i].y + X.shift.y, Y.points[i].z + X.shift.z);
       		temp_hit.setHoughFlag(j);
       
       		event_hits.push_back(temp_hit);
    		}
    
    	}
	X.removePoints(Y);
    
   
  } while ((X.points.size() > 1) && 
           ((opt_nlines == 0) || (opt_nlines > nlines)));

  
  // clean up
  delete hough;
  
  //save everything
  ev->append(event_hits);
  ev->setLines(found_lines); 
}


double orthogonal_LSQ(const PointCloud &pc, Vector3d* a, Vector3d* b){
  double rc = 0.0;

  // anchor point is mean value
  *a = pc.meanValue();

  // copy points to libeigen matrix
  Eigen::MatrixXf points = Eigen::MatrixXf::Constant(pc.points.size(), 3, 0);
  for (int i = 0; i < points.rows(); i++) {
    points(i,0) = pc.points.at(i).x;
    points(i,1) = pc.points.at(i).y;
    points(i,2) = pc.points.at(i).z;
  }

  // compute scatter matrix ...
  MatrixXf centered = points.rowwise() - points.colwise().mean();
  MatrixXf scatter = (centered.adjoint() * centered);

  // ... and its eigenvalues and eigenvectors
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> eig(scatter);
  Eigen::MatrixXf eigvecs = eig.eigenvectors();

  // we need eigenvector to largest eigenvalue
  // libeigen yields it as LAST column
  b->x = eigvecs(0,2); b->y = eigvecs(1,2); b->z = eigvecs(2,2);
  rc = eig.eigenvalues()(2);

  return (rc);
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

