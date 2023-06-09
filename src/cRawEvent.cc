#include "cRawEvent.h"

using namespace std;

cRawEvent::cRawEvent(): eventnum(-1),
                        timestamp(0) {}

cRawEvent::~cRawEvent() {}

void cRawEvent::clear() {
  eventnum  = -1;
  timestamp = 0;
  hits.clear();

  #ifdef INCRAWSIG
  signal.clear();
  #endif
}

void cRawEvent::append(const vector<cHit> &h) {
  hits.insert(hits.end(), h.begin(), h.end());
}

void cRawEvent::append(const cRawEvent& e) {
  append(e.hits);

  #ifdef INCRAWSIG
  signal.insert(signal.end(), e.signal.begin(), e.signal.end());
  #endif
}

ClassImp(cRawEvent);
