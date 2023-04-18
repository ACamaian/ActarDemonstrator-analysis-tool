

void plotta_test(TString input="testdata.dat"){

  ifstream in(input);

  TGraph2D *gr[10];

  string line;
  int times=0;
  float xx=0, yy=0, zz=0;
  while(getline(in,line)){
    stringstream ss;
    ss.str(line);
    if(line[0]=='#'){
      gr[times]=new TGraph2D();
      int num=0;
      char hash;
      string line;
      ss >> hash >> line >> num;
      gr[times]->SetName(Form("gr_%d",num));
      times++;
      continue;
    }
    ss >> xx >> yy >> zz;
    gr[times-1]->SetPoint(gr[times-1]->GetN(),xx,yy,zz);
  }

  TH3F *frame = new TH3F("frame","frame",20,-10,10,20,-10,10,20,-10,10);
  frame->Draw();
  for(int i=0; i<3; i++){
    gr[i]->SetMarkerStyle(20+i);
    gr[i]->SetMarkerColor(1+i);
    gr[i]->Draw("psame");
  }

  float a[3][3]={{-0.106754,2.847157,2.875361},
		 {1.185223,-0.164238,-0.828718},
		 {2.147641,2.074387,2.152054}};
  float b[3][3]={{0.578518,0.567724,0.585667},
		 {0.591344,-0.563276,0.577089},
		 {0.562639,0.582842,0.586287}};
  

  TGraph2D *l[3];
  for(int i=0; i<3; i++){
    l[i]=new TGraph2D();
    for(float ipoint=-10; ipoint<10; ipoint += 0.1){
      float xx = a[i][0]+b[i][0]*ipoint;
      float yy = a[i][1]+b[i][1]*ipoint;
      float zz = a[i][2]+b[i][2]*ipoint;
      l[i]->SetPoint(l[i]->GetN(),xx,yy,zz);
    }
    l[i]->Draw("lpsame");
  }


  
  
}




