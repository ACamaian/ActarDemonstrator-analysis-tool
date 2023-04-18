//
// pointcloud.cpp
//     Class for holding a set of 3D points
//
// Author:  Tilman Schramke, Christoph Dalitz
// Date:    2017-03-16
// License: see LICENSE-BSD2
//

#include "pointcloud.h"
#include <stdio.h>
#include <math.h>

using namespace std;

// translate point cloud so that center = origin
// total shift applied to this point cloud is stored in this->shift
void PointCloud::shiftToOrigin(){
  Vector3d p1, p2, newshift;
  this->getMinMax3D(&p1, &p2);
  newshift = (p1 + p2) / 2.0;
  for(size_t i=0; i < points.size(); i++){
    points[i] = points[i] - newshift;
  }
  shift = shift + newshift;
}

// mean value of all points (center of gravity)
Vector3d PointCloud::meanValue() const {
  Vector3d ret;
  for(size_t i = 0; i < points.size(); i++){
    ret = ret + points[i];
  }
  if (points.size() > 0)
    return (ret / (double)points.size());
  else
    return ret;
}

// bounding box corners
void PointCloud::getMinMax3D(Vector3d* min_pt, Vector3d* max_pt){
  if(points.size() > 0){
    *min_pt = points[0];
    *max_pt = points[0];

    for(std::vector<Vector3d>::iterator it = points.begin(); it != points.end(); it++){
      if(min_pt->x > it->x) min_pt->x = it->x;
      if(min_pt->y > it->y) min_pt->y = it->y;
      if(min_pt->z > it->z) min_pt->z = it->z;

      if(max_pt->x < (*it).x) max_pt->x = (*it).x;
      if(max_pt->y < (*it).y) max_pt->y = (*it).y;
      if(max_pt->z < (*it).z) max_pt->z = (*it).z;
    }
  } else {
    *min_pt = Vector3d(0,0,0);
    *max_pt = Vector3d(0,0,0);
  }
}

// reads point cloud data from the given file
// (see IPOL paper for file format)
int PointCloud::readFromFile(const char* path){
  FILE* f = fopen(path, "r");
  if (!f) return 1;

  char line[1024];
  Vector3d point;
  int n;
  while (fgets(line, 1023, f)) {
    if (line[0] == '#') continue;
    n = sscanf(line, "%lf,%lf,%lf", &point.x, &point.y, &point.z);
    if (n != 3) {
      fclose(f);
      return 2;
    }
    points.push_back(point);
#ifdef WEBDEMO
    if (points.size() > 1E6) {
      fprintf(stderr, "Error: program was compiled in WEBDEMO mode, "
              "which only permits less than 10^6 points in point cloud\n");
      return 3;
  }
#endif
  }

  fclose(f);
  return 0;
}

void PointCloud::insertPoint(double x, double y, double z){
 
    Vector3d point(x,y,z);
    points.push_back(point);
    
}


// store points closer than dx to line (a, b) in Y
void PointCloud::pointsCloseToLine(const Vector3d &a, const Vector3d &b, double dx, PointCloud* Y) {

  Y->points.clear();
  Y->charge.clear();
  Y->time.clear();
  Y->gid.clear();
  
  for (size_t i=0; i < points.size(); i++) {
    // distance computation after IPOL paper Eq. (7)
    double t = (b * (points[i] - a));
    Vector3d d = (points[i] - (a + (t*b)));
    if (d.norm() <= dx) {
      Y->points.push_back(points[i]);
      //---added to copy energy, time and gid information
      Y->insertCharge(charge[i]);
      Y->insertGID(gid[i]);
      Y->insertTime(time[i]);
    }
  }
}

// removes the points in Y from PointCloud
// WARNING: only works when points in same order as in pointCloud!
void PointCloud::removePoints(const PointCloud &Y){

  if (Y.points.empty()) return;
  std::vector<Vector3d> newpoints;
  std::vector<double> newcharge;
  std::vector<double> newtime;
  std::vector<int> newgid;
  size_t i,j;

  // important assumption: points in Y appear in same order in points
  for (i = 0, j = 0; i < points.size() && j < Y.points.size(); i++){
    if (points[i] == Y.points[j]) {
      j++;
    } else {
      newpoints.push_back(points[i]);
      //---added to copy energy, time and gid information
      newcharge.push_back(charge[i]);
      newtime.push_back(time[i]);
      newgid.push_back(gid[i]);
    }
  }
  // copy over rest after end of Y
  for (; i < points.size(); i++){
    newpoints.push_back(points[i]);
    newcharge.push_back(charge[i]);
    newtime.push_back(time[i]);
    newgid.push_back(gid[i]);
  }
  
  points = newpoints;
  time = newtime;
  charge = newcharge;
  gid = newgid;
}


  //to order the point cloud in a charge-value decreasing order
void PointCloud::orderCloud() {

	//std::cout << "order" << std::endl;

  if(points.size()==0){
  	std::cout << "No points stored in the cloud" << std::endl;
	return;
  }

  if(charge.size()==0){
  	std::cout << "No charge stored in the cloud" << std::endl;
	return;
  }
  
 std::map<int, double> map;
 for(int i=0; i<charge.size(); i++) map.emplace(i, charge[i]);
 
 // create an empty vector of pairs
 std::vector<std::pair<int, double>> vec;
 
 // copy key-value pairs from the map to the vector
 std::copy(map.begin(),
            map.end(),
            std::back_inserter<std::vector<std::pair<int, double>>>(vec));
 
 
 
 // sort the vector by increasing the order of its pair's second value
 // if the second value is equal, order by the pair's first value
 std::sort(vec.begin(), vec.end(),[](const std::pair<int, double> &l, const std::pair<int, double> &r){
                if (l.second != r.second) {
                    return l.second < r.second;
                }
 
                return l.first < r.first;
            });
  
  //std::cout << "qui" << std::endl;
  
  std::vector<Vector3d> new_points;
  
  std::vector<double> new_charge;
  std::vector<double> new_time;
  std::vector<int> new_gid;
  
  //std::cout << charge.size() << " " << time.size() << " " << gid.size() << " " << points.size() << std::endl;
  
  for(int i=vec.size()-1; i>=0; i--){
  	std::pair<int, double> tpair = vec.at(i);
	
	//std::cout << tpair.first << std::endl;
	
	new_charge.push_back(charge[tpair.first]);
	new_time.push_back(time[tpair.first]);
	new_gid.push_back(gid[tpair.first]);
	new_points.push_back(points[tpair.first]);
  }
  
  //for(int i=0; i<new_charge.size(); i++) std::cout << i << " " << new_charge[i] << std::endl;
  
  if(charge.size()!=new_charge.size()){
  	std::cout << "Charge size not conserved" << std::endl;
  }
   if(time.size()!=new_time.size()){
  	std::cout << "Time size not conserved" << std::endl;
  }
   if(gid.size()!=new_gid.size()){
  	std::cout << "GID size not conserved" << std::endl;
  }
   if(points.size()!=new_points.size()){
  	std::cout << "Points size not conserved" << std::endl;
  }
  
  charge.swap(new_charge);
  time.swap(new_time);
  gid.swap(new_gid);
  points.swap(new_points);
}



