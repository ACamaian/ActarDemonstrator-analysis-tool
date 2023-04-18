void rootlogon()
{
  // Add my own options here:
  TStyle* mcStyle = new TStyle("mcStyle","Cama's Root Styles");
  mcStyle->SetPalette(1,0); // avoid horrible default color scheme
  mcStyle->SetOptStat(0);//1111111);
  mcStyle->SetOptTitle(0);
  mcStyle->SetOptDate(0);
  mcStyle->SetLabelSize(0.06,"xyz"); // size of axis value font
  mcStyle->SetTitleSize(0.06,"xyz"); // size of axis title font
  mcStyle->SetTitleFont(22,"xyz"); // font option
  mcStyle->SetLabelFont(22,"xyz");
  mcStyle->SetTitleOffset(0.90,"x");
  mcStyle->SetTitleOffset(1,"y");
  // default canvas options
  mcStyle->SetCanvasDefW(650);
  mcStyle->SetCanvasDefH(500);
  mcStyle->SetCanvasColor(0);
  mcStyle->SetPadColor(0);
  // canvas...
  mcStyle->SetCanvasBorderMode(0);
  mcStyle->SetCanvasBorderSize(0);
  //margins...
  mcStyle->SetPadBottomMargin(0.12);
  mcStyle->SetPadTopMargin(0.1);
  mcStyle->SetPadLeftMargin(0.13);
  mcStyle->SetPadRightMargin(0.13);
  // grids, tickmarks
  mcStyle->SetPadGridX(0);
  mcStyle->SetPadGridY(0);
  mcStyle->SetPadTickX(0);
  mcStyle->SetPadTickY(0);
  mcStyle->SetFrameBorderMode(0);
  mcStyle->SetPaperSize(22,24);
  //legend
  mcStyle->SetLegendBorderSize(0);
  mcStyle->SetLegendFont(22);
  //hist
  mcStyle->SetHistLineWidth(2);
  //text
  mcStyle->SetTextFont(22);
  //axis
  mcStyle->SetNdivisions(504,"XYZ");
  mcStyle->SetNdivisions(504,"Z");
  // US letter size
  gROOT->SetStyle("mcStyle");
  cout << "Styles are Set!" << endl;
  
  // gStyle->SetOptStat(1111111);
  
  gSystem->SetFlagsOpt("-O3 -Wall"); //cosa fa questo?
  
  gEnv->SetValue("Canvas.ShowEventStatus",1);
  
  //load .so for ARDA
  gSystem->Load("/home/camaiani/install/bin/libMFM.so");  
  gSystem->Load("/home/camaiani/install/bin/libpClasses.so"); 
  gSystem->Load("/home/camaiani/install/bin/libARDAlib.so"); 
  
  printf("--ARDA  Done. --\n");
    
  //tools for analysis
  gROOT->ProcessLine(".L ../../src/cHitxyz.cc+");
  gROOT->ProcessLine(".L ../../src/cEvent.cc+");

  printf("--Custom classes  Done. --\n");
}
