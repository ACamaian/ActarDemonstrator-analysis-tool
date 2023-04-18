#include "cHitxyz.h"

ClassImp(cHitxyz);

/// Default constructor
cHitxyz::cHitxyz() {
  peakheight      = -1;
  peaktime        = -1;
  globalchannelid = -1;
  flag=-1;
}

/// Constructor
cHitxyz::cHitxyz(Int_t globu, Double_t uheight, Double_t utime, Double_t xu, Double_t yu, Double_t zu, Int_t fu){
  globalchannelid = globu;
  peakheight      = uheight;
  peaktime        = utime;
  xyz={xu,yu,zu};
  flag=fu;
}

///Copy constructor
cHitxyz::cHitxyz(const cHitxyz &h) {
  globalchannelid = h.globalchannelid;
  peakheight      = h.peakheight;
  peaktime        = h.peaktime;
  xyz       = h.xyz;
  flag = h.flag;
}

/// Destructor
cHitxyz::~cHitxyz() {}
