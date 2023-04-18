void test_ev2(){
 
  ifstream ifs;
  ifs.open ("ev2_pr1.dat", std::ifstream::in);

  string line;
  getline(ifs,line);
  
  double e0=0.5748646;
  double epart=0;
  
  while(getline(ifs,line)){
  	stringstream ss;
	ss.str(line);
	
	double xx, yy, zz, ee;
	
	ss>> xx >> yy >> zz >> ee;
	if(ee!=235){cout << xx << " " << yy << " " << zz << " " << ee << endl;
  	 epart += e0*0.15;
}  };
  
  cout << epart << " " << e0 << endl;
  
}
