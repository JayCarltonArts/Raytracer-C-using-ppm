#include "Raytracing.h"

using namespace std;

Vector3D::~Vector3D(){};
Vector3D::Vector3D() {
  v[0] = 0;
  v[1] = 0;
  v[2] = 0;
}
// Vector3D constructor with a vector list
Vector3D::Vector3D(double x, double y, double z) {
  v[0] = x;
  v[1] = y;
  v[2] = z;
}

/*double Vector3D::get_coord(int in) {
  if (in == 0) {
    return v[in];
  } else if (in == 1) {
    return v[in];
  } else if (in == 2) {
    return v[in];
  } else {
    return 0;
  }
}*/

double Vector3D::getX() const { return v[0]; }
double Vector3D::getY() const { return v[1]; }
double Vector3D::getZ() const { return v[2]; }

void Vector3D::operator=(Vector3D const &ar) {
  v[0] = ar.v[0];
  v[1] = ar.v[1];
  v[2] = ar.v[2];
}

Vector3D Vector3D::operator-(const Vector3D &v1) const {
  Vector3D result;

  result.v[0] = v[0] - v1.v[0];
  result.v[1] = v[1] - v1.v[1];
  result.v[2] = v[2] - v1.v[2];

  return result;
}

// Function to calculate the dot product of two vectors
double dot(const Vector3D &vector1, const Vector3D &vector2) {
  double result = vector1.v[0] * vector2.v[0] + vector1.v[1] * vector2.v[1] +
                  vector1.v[2] * vector2.v[2];

  return result;
}

// Overloading the multiplication operator to multiply vectors with a scalar
Vector3D Vector3D::operator*(double const &v1) {
  Vector3D result;

  result.v[0] = v[0] * v1;
  result.v[1] = v[1] * v1;
  result.v[2] = v[2] * v1;

  return result;
}

Vector3D Vector3D::operator+(const Vector3D &v1) const {
  Vector3D result;

  result.v[0] = v[0] + v1.v[0];
  result.v[1] = v[1] + v1.v[1];
  result.v[2] = v[2] + v1.v[2];

  return result;
}

Vector3D Vector3D::operator*(double const &v1) const {
  Vector3D result;

  result.v[0] = v[0] * v1;
  result.v[1] = v[1] * v1;
  result.v[2] = v[2] * v1;

  return result;
}

double norm(Vector3D &v1) {
  double Magnitude = 0;
  Vector3D result(0, 0, 0);
  for (int i = 0; i < 3; i++) {
    Magnitude = Magnitude + pow(v1.v[i], 2);
  }
  Magnitude = sqrt(Magnitude);
  //result = v1 * (1 / Magnitude);
  return Magnitude;
}

/*

Vector3D Vector3D::operator-(Vector3D const &v1) {
  Vector3D result;

  result.v[0] = v[0] - v1.v[0];
  result.v[1] = v[1] - v1.v[1];
  result.v[2] = v[2] - v1.v[2];

  return result;
}







Vector3D Vector3D::operator-(int const &v1) {
  Vector3D result;

  result.v[0] = v[0] - v1;
  result.v[1] = v[1] - v1;
  result.v[2] = v[2] - v1;

  return result;
}

ostream &operator<<(ostream &out, const Vector3D &ar) {
  out << ar.v[0] << ',' << ar.v[1] << ',' << ar.v[2] << endl;
  return out;
}

// Overloading the multiplication operator to multiply vectors with a scalar






Vector3D Vector3D::operator*(int const &v1) {
  Vector3D result;

  result.v[0] = v[0] * v1;
  result.v[1] = v[1] * v1;
  result.v[2] = v[2] * v1;

  return result;
}

*/

Array::~Array(){};
Array::Array() {
  x = 0;
  y = 0;
  z = 0;
}
Array::Array(int r, int g, int b) {
  x = r;
  y = g;
  z = b;
}
Array Array::operator*(double const &v1) {
  Array result;

  result.x = x * v1;
  result.y = y * v1;
  result.z = z * v1;

  return result;
}
Array Array::operator+(double const &v1) {
  Array result;

  result.x = x + v1;
  result.y = y + v1;
  result.z = z + v1;

  return result;
}
int Array::getxyz(int in) const {
  if (in == 0) {
    return x;
  } else if (in == 1) {
    return y;
  } else if (in == 2) {
    return z;
  } else {
    return 0;
  }
}

//---------------------
// Sphere class

sphere::sphere() {
  radius = 0;
  color = Array(0, 0, 0);
  r2 = 0;
}

sphere::sphere(Vector3D cen, double rad, Array rgb,double spec) {
  color = rgb;
  center = cen;
  radius = rad;
  specular = spec;
  r2 = rad * rad;
}

//------------------------------------------------
/*
Camara::Camara(){
        position = [0,0,0];
        rotation = [0,0,0][0,0,0];
    };


Camara::Camara(double pos[],double rot[][]){

        position = pos;
        rotation = rot;
    };
*/
Light::Light() {
  type = ' ';
  intensity = 0;
  position = Array(0, 0, 0);
  direction = Array(0, 0, 0);
}
Light::~Light() {}

Light::Light(string type, double intensity, Array direction, Array position) {
  type = type;
  intensity = intensity;
  direction = direction;
  position = position;
}

Scene::Scene() {
  spheres[0] =
      sphere(Vector3D(0, -1, 3), 1, Array(255, 0, 0), 5000);//, 0.2);
  spheres[1] = sphere(Vector3D(2, 0, 4), 1, Array(0, 0, 255) , 500);//, 0.3);
  spheres[2] = sphere(Vector3D(-2, 0, 4), 1, Array(0, 255, 0), 10);//, 0.4);
  spheres[3] =
      sphere(Vector3D(0, -5001, 0), 5000, Array(255, 255, 0), 1000);//, 0.5);

   Lights[0] = Light("ambient", 0.2, Array(0, 0, 0), Array(0, 0, 0));
   Lights[1] = Light("point", 0.6, Array(0, 0, 0), Array(2, 1, 0));
   Lights[2] = Light("direction", 0.2, Array(1, 4, 4), Array(0, 0, 0));
}
