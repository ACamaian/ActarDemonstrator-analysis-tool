


void checkVotingSpace(TString name = "votingspace.txt"){

  ifstream in;
  in.open(name, std::ifstream::in);
  
  TH1F *hvote[100];
  
  string line;
  
  int ev=0;
  while(getline(in,line)){
  
   if(line[0]=='#') {
   	hvote[ev] = new TH1F (Form("hvote_%d", ev), Form("hvote_%d", ev), 1000, 0, 100);
	ev++;
	}
  
   stringstream ss;
   ss.str(line);
  
   int index=0;
   double vote=0;
   ss >> index >> vote;

   hvote[ev-1] -> Fill(vote);	    
   
  }
  
  hvote[1]->Draw();

}
