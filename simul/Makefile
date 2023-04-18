CC = g++
CFLAGS = -O3 -Wall

SRC = ../src/
ARDA = /home/buccola/ats/arda/bin/

OBJ = cHitxyz.o cHitxyzDict.cxx cEvent.o cEventDict.cxx cHit.o cHitDict.cxx cRawEvent.o cRawEventDict.cxx cLookupTable.o cLookupTableDict.cxx pSignal.o pSignalDict.cxx


dat2root_series.out : dat2root_series.C $(OBJ) 
	$(CC) $(CFLAGS) $^ `root-config --cflags --glibs` -lTreePlayer  -o $@ 

%.o: $(SRC)%.cc %Dict.cxx
	$(CC) -c -Wall -fpic `root-config --cflags --glibs` -lTreePlayer $^

%Dict.cxx: $(SRC)%.h $(SRC)%LinkDef.h
	rootcling -f $@ -c $^

clean:
	rm *.o *.cxx *.pcm  *.out
