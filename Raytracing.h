#ifndef RAYTRACING_H
#define RAYTRACING_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

// Your class declarations and function prototypes go here

using namespace std;

class Vector3D {
public:
  // Vector3D default constructor
  Vector3D();
  ~Vector3D();

  // Vector3D constructor with a vector list
  Vector3D(double x, double y, double z);
  double getX() const;
  double getY() const;
  double getZ() const;

  void operator=(Vector3D const &ar);
  Vector3D operator-(const Vector3D &v1) const;

  friend double dot(const Vector3D &vector1, const Vector3D &vector2);

  friend double norm(const Vector3D &v1);

  Vector3D operator+(const Vector3D &) const;

  // Vector3D operator-(Vector3D const &v1);

  // Vector3D operator-(int const &v1);

   friend ostream &operator<<(ostream &out, const Vector3D &ar);

  // Overloading the multiplication operator to multiply vectors with a scalar
  Vector3D operator*(double const &v1) const;
  Vector3D operator*(double const &v1);

  

  // Function to calculate the dot product of two vectors

private:
  double v[3];
};

class Array {
public:
  Array();
  ~Array();

  Array(int r, int g, int b);
  Array operator*(double const &v1);
  Array operator+(double const &v1);
  
  int getxyz(int in) const;

private:
  int x;
  int y;
  int z;
};

//#-------------------------------------------
//#Scene creation

class sphere {
public:
  sphere(Vector3D cen, double rad, Array rgb, double sp);//, double refle);
  sphere();
  
  Vector3D center;
  double radius;
  Array color;
  double r2;
  double specular;
  // double refl;
};

class Light {
public:
  Light();
  ~Light();
  Light(string type, double intensity, Vector3D direction, Vector3D position);


  string type;
  double intensity;
  Vector3D position;
  Vector3D direction;
};

class Scene {
public:
  Scene();

  sphere spheres[4];
  Light Lights[3];
};

/*


class Camara{
    public:
    Camara();
    Camara(double pos[],double rot[][]);

};


*/

#endif
