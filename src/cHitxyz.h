#include <TObject.h>
#include <vector>

#ifndef cHitxyz_h
#define cHitxyz_h

/**
\brief Class to store each channel's hit
*/

class cHitxyz: public TObject {
  private:
    Double_t peakheight;
    Double_t peaktime;
    std::vector<Double_t> xyz;  
    Int_t flag; //identification flags for hough transformation
    
    /**
    \brief Unique id for each channel
    It is computed as follows:
    globalchannelid = channel + 100 * agetnumber +  1000 * asadnumber + 10000 * cobonumber
    */
    Int_t globalchannelid;
  public:
    cHitxyz();
    cHitxyz(Int_t globu, Double_t uheight, Double_t utime, Double_t xu, Double_t yu, Double_t zu, Int_t fu);
	cHitxyz(const cHitxyz &);
    virtual ~cHitxyz();

    Double_t getPeakHeight() const {return peakheight;}
    Double_t getPeakTime  () const {return peaktime;  }

    void setHoughFlag(Int_t flagu) {flag=flagu;}
    Int_t getHoughFlag() {return flag;}
    
    Int_t getGlobalChannelId() const   {return globalchannelid;}
    void  setGlobalChannelId(Int_t cu) {globalchannelid = cu;}

    void setPeakHeight(Double_t uh) {peakheight = uh;}
    void setPeakTime  (Double_t ut) {peaktime   = ut;}

    void setXYZ(Double_t xu, Double_t yu, Double_t zu){
      xyz.push_back(xu);
      xyz.push_back(yu);
      xyz.push_back(zu);
    }

    void clear(){
      peakheight      = -1;
      peaktime        = -1;
      globalchannelid = -1;
      xyz.clear();
    }

    std::vector<Double_t>&       getXYZ()       {return xyz;}
    const std::vector<Double_t>& getXYZ() const {return xyz;}

    ClassDef(cHitxyz, 1);
};

#endif
