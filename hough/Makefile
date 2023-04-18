CC = g++
CFLAGS = -O3 -Wall
LDFLAGS = -lstdc++

SRC = ../src/

OBJ = cHitxyz.o cHitxyzDict.cxx cEvent.o cEventDict.cxx

#for Hough transformation
# include directory of libeigen
LIBEIGEN = /home/camaiani/ATS_ne20/hough/transformation/eigen_install/include/eigen3
TDIR= /home/camaiani/ATS_ne20/hough/transformation/
TOBJ = $(TDIR)/hough.o  $(TDIR)/sphere.o  $(TDIR)/vector3d.o $(TDIR)/pointcloud.o

hought_transformation.out : hough_transformation.C $(OBJ) $(TOBJ)
	$(CC)  $(CFLAGS) $^ `root-config --cflags --glibs` -lTreePlayer -o $@ 

%.o: $(SRC)%.cc
	$(CC) -c -Wall -I`root-config --incdir` $^

%Dict.cxx: $(SRC)%.h $(SRC)%LinkDef.h
	rootcling -f $@ -c $^

$(TDIR)%.o: $(TDIR)%.cpp
	$(CC) -Wall -O -I$(LIBEIGEN) $(CPPFLAGS) -c $(TDIR)$*.cpp -o $@

clean:
	rm -f *.o *.cxx *.pcm $(TDIR)/*.o *.out
