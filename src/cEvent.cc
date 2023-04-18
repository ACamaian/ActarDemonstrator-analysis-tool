#include "cEvent.h"
class TRootIOCtor;


cEvent::cEvent(){
    clear();
}

cEvent::~cEvent() {}

void cEvent::clear() {
  eventnum  = -1;
  hits.clear();
  lines.clear();
  isgood=false;
}


void cEvent::append(const std::vector<cHitxyz> &h) {
  hits.insert(hits.end(), h.begin(), h.end());
}

void cEvent::append(const cEvent& e) {
  append(e.hits);

}

ClassImp(cEvent);
