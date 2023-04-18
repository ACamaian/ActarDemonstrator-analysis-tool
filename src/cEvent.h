#include <vector>
#include <map>
#include <utility>
#include "TObject.h"
#include "cHitxyz.h"

#ifndef cEvent_h
#define cEvent_h

/**
\brief Class that conitains the array of hits for each pad together with the raw signal
*/

class cEvent : public TObject {
  private:
    int eventnum;
    std::vector<cHitxyz>       hits;
    std::map<int,std::vector<double>> lines;
    bool isgood;
    int idcode;
    
  public:
    cEvent();
    virtual ~cEvent();

    void setIsgood(bool is){isgood=is;}
    bool getIsgood(){return isgood;}
    
    int getEventNumber() const {return eventnum; }    
    void setEventNumber(int eu) {eventnum  = eu;}
    
    void setLines(std::map<int,std::vector<double>> lu){lines=lu;};
    std::map<int,std::vector<double>> getLines() {return lines;}
    
    std::vector<cHitxyz>& getHits()       {return hits;}
    const std::vector<cHitxyz>& getHits() const {return hits;}

    void clear();                          ///< Clears the object
    void append(const std::vector<cHitxyz>&); ///< Appends hits to the vector
    
    /// Appends hits and signals (when present) of another event
    void append(const cEvent&);

    void setIDCode(int ii){idcode = ii;};
    int getIDCode(){return idcode;}
    
    ClassDef(cEvent, 2);
};

#endif
