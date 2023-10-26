#include "Raytracing.h"

using namespace std;

double BACKGROUND_COLOR[3] = {255, 255, 255};
int Ch = 300;
int Cw = 300;
int Vh = 1; // Viewport height
int Vw = 1; // Viewport width
int d = 1;  // Projection distance
Scene scene;


pair<double,double> IntersectRaySphere(const Vector3D &O, const Vector3D &D,
                           const sphere &s) {
  double r = s.radius;
  Vector3D CO = O - s.center;

  double a = dot(D, D);
  double b = 2 * dot(CO, D);
  double c = dot(CO, CO) - s.r2;

  double discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0) {
    return make_pair(INFINITY,INFINITY);
  }

  double t1 = (-b + sqrt(discriminant)) / (2 * a);
  double t2 = (-b - sqrt(discriminant)) / (2 * a);

  return make_pair(t1, t2);
}

double ComputeLighting(Vector3D P,Vector3D N, Vector3D V,double s) {
    double i = 0.0;
    Vector3D L;
    Vector3D R;
    for (const Light &light : scene.Lights) {
      
        if (light.type == "ambient") {
           i += light.intensity;
        } 
        else {
            if (light.type == "point") {
              L = light.position - P;
            } 
            else {
               L = light.direction;
            }

          double n_dot_l = dot(N, L);
           if (n_dot_l > 0 ){
               i += light.intensity * n_dot_l/(norm(N) * norm(L));
            }
           // Specular
          if (s != -1) {
            
              R = (N * 2.0) * dot(N, L) - L;
              double r_dot_v = dot(R, V);
              if (r_dot_v > 0) {
                i += light.intensity * pow(r_dot_v/(norm(R) * norm(V)), s);
              }
        }
        }
    }
    
    return i;
}

double colorcheck(double color) {
  if (color >= 255) {
    color = 255;
  } else if (color <= 0) {
    color = 0;
  }
  return color;
}

Vector3D ReflectRay(const Vector3D &R, const Vector3D &N) {
  double dotProduct = dot(N, R);
  return N * 2.0 * dotProduct - R;
}

Array TraceRay(const Vector3D &O, const Vector3D &D, double t_min, double t_max,
               double rec_depth) {
  double closest_t = INFINITY;
  sphere closest_sphere = sphere(Vector3D(0, 0, 0), 0, Array(0, 0, 0),0);


  for (const sphere &sphere : scene.spheres) {
     pair<double, double> T = IntersectRaySphere(O, D, sphere);
    double t1 = T.first;
    double t2 = T.second;

    if (t_min <= t1 && t1 <= t_max && t1 < closest_t) {
      closest_t = t1;
      closest_sphere = sphere;
    }

    if (t_min <= t2 && t2 <= t_max && t2 < closest_t) {
      closest_t = t2;
      closest_sphere = sphere;
    }
  }

  if (closest_t == INFINITY) {
    
    return Array(255, 255, 255);
  }
  
  Vector3D P = O + (D * closest_t);
  Vector3D N = P - closest_sphere.center;
  N = N * (1/norm(N));
 
  double v1 = D.getX();
  double v2 = D.getY();
  double v3 = D.getZ();

  Vector3D neg_D((v1*-1),(v2*-1),(v3*-1));

  
  double i = ComputeLighting(P, N, neg_D, closest_sphere.specular);

  int red = colorcheck(int(closest_sphere.color.getxyz(0) *i));
  int blue = colorcheck(int(closest_sphere.color.getxyz(2)*i));
  int green = colorcheck(int(closest_sphere.color.getxyz(1))*i);
  Array local_color(red, green, blue);

  /*double r = closest_sphere->refl;

  if (rec_depth <= 0 || r <= 0) {
      return local_color;
  }

   Vector3D R = ReflectRay(neg_D, N);
   Array reflected_color = TraceRay(P, R, 0.001, INFINITY, rec_depth - 1);
  */
  return local_color; //* (1 - r) + reflected_color * r;
}

Vector3D CanvasToViewport(double x, double y) {
  double x1 = (x * Vw) / Cw;
  double y1 = (y * Vh) / Ch;
  Vector3D r(x1, y1, d);

  return r;
}

int main() {

  Vector3D O(0, 0, 0);
  ofstream image;
  image.open("image.ppm");

  if (image.is_open()) {
    image << "P3" << endl;
    image << "300 300" << endl;
    image << "255" << endl;
    for (int y = Ch / 2; y > -Ch / 2; --y) {
      for (int x = -Cw / 2; x < Cw / 2; ++x) {
        Vector3D D = CanvasToViewport(x, y);
        Array color = TraceRay(O, D, 1, INFINITY, 3);
        image << color.getxyz(0) << " " << color.getxyz(1) << " "
              << color.getxyz(2) << endl;
      }
    }
  }

  image.close();
  /*Vector3D ar(1.0, 2.0, 3.0);
  Vector3D D;
  D = CanvasToViewport(1, 1);
  cout << D << endl;*/

  return 0;
}
