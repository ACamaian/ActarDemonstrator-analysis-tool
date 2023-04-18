//
// pointcloud.h
//     Class for holding a set of 3D points
//
// Author:  Tilman Schramke, Christoph Dalitz
// Date:    2017-03-16
// License: see LICENSE-BSD2
//

#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include "vector3d.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <algorithm>



class PointCloud {   
public:
 
  PointCloud(){};
  ~PointCloud(){};
 
  // translation of pointCloud as done by shiftToOrigin()
  Vector3d shift;
  
  // points of the point cloud
  std::vector<Vector3d> points;
  
  std::vector<double> charge;
  std::vector<double> time;
  std::vector<int> gid;  
  
  double totalCharge=0;

  // translate point cloud so that center = origin
  void shiftToOrigin();
  // mean value of all points (center of gravity)
  Vector3d meanValue() const;
  // bounding box corners
  void getMinMax3D(Vector3d* min_pt, Vector3d* max_pt);
  // reads point cloud data from the given file
  int readFromFile(const char* path);
  // store points closer than dx to line (a, b) in Y
  void pointsCloseToLine(const Vector3d &a, const Vector3d &b,
                         double dx, PointCloud* Y);
  // removes the points in Y from PointCloud
  // WARNING: only works when points in same order as in pointCloud!
  void removePoints(const PointCloud &Y);
  
  //to insert a single point
  void insertPoint(double x, double y, double z);
  
  //to store charge, time and gid;
  void insertCharge(double x){charge.push_back(x);};
  void insertGID(int x){gid.push_back(x);}; 
  void insertTime(double x){time.push_back(x);};  
  void computeTotalCharge(){totalCharge=0; for(uint i=0; i<charge.size(); i++) totalCharge += charge[i]; totalCharge /= points.size();}
  
  
  double getCharge(int i){return charge[i];};
  double getTotalCharge(){return totalCharge;};
  double getTime(int i){return time[i];};
  double getGID(int i){return gid[i];};
  
  void orderCloud();
};

#endif /* POINTCLOUD_H_ */
