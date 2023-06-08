//Signed Distance Function Primitives
//@Author Ömer Faruk Tekin

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <iomanip>
using namespace std;

double sdf_sphere(double x, double y, double z, double r) {
	return sqrt(x*x+y*y+z*z)-r;
}
double sdf_square(double x1, double y1, double z1, double r1) {
	return sqrt((max((abs(x1) - r1), 0.0))* (max((abs(x1) - r1), 0.0))+ (max((abs(y1) - r1), 0.0)) * (max((abs(y1) - r1), 0.0))+ (max((abs(z1) - r1), 0.0)) * (max((abs(z1) - r1), 0.0)));
}
double sdf_torus(double x2, double y2, double z2, double r2x,double r2y) {
	float p2 = sqrt(x2 * x2 + z2 * z2) - r2x;
	return sqrt(p2*p2+y2*y2)-r2y;
}
double sdf_capsule(double px,double py,double pz,double ax, double ay, double az, double bx, double by, double bz,double r3) {
	double abx = bx - ax; double aby = by - ay; double abz = bz - az;
	double apx = px - ax; double apy = py - ay; double apz = pz - az;
	double t = (abx * apx + aby * apy + abz * apz) / (abx * abx + aby * aby + abz * abz);

	if (t < 0) { t = 0; }
	else if (t > 1) { t = 1; }

	double cx = ax + t * abx; double cy = ay + t * aby; double cz = az + t * abz;
	return sqrt((px-cx)*(px-cx)+(py-cy)*(py-cy)+(pz-cz)*(pz-cz)) - r3;
}
double sdf_substraction(double _x,double _y) {
	return max(-_x, _y);
}
double sdf_inter(double _x, double _y) {
	return max(_x, _y);
}
double sdf_union(double _x, double _y) {
	return min(_x, _y);
}

int main(){
	vector<double> sdf_vec_x{};
	vector<double> sdf_vec_y{};
	vector<double> sdf_vec_z{};
	vector<double> sdf_vec_m{};
	vector<double> sdf_vec_m_sp{};
	vector<double> sdf_vec_m_cube{};
	vector<double> sdf_vec_m_tr{};
	vector<double> sdf_vec_m_cp{};
	vector<double> sdf_vec_m_subs{};
	vector<double> sdf_vec_m_inter{};
	vector<double> sdf_vec_m_union{};
	vector<double> sdf_vec_m_face{};
	vector<double> sdf_vec_m_eye_l{};
	vector<double> sdf_vec_m_eye_r{};
	vector<double> sdf_vec_m_mouth{};
	//CREATING SPACE
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j ++) {
			for (int k = 0; k < 100; k ++) {
				sdf_vec_x.push_back(i);
				sdf_vec_y.push_back(j);
				sdf_vec_z.push_back(k);
			}
		}
	}
	//SPHERE
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_sp.push_back(sdf_sphere(sdf_vec_x[q]-50, sdf_vec_y[q]-50, sdf_vec_z[q]-50, 40)); //Center: (50,50,50) Radius: 45
		if (sdf_vec_m_sp[q] < 0) { sdf_vec_m_sp[q] = 0; }
	}
	//CUBE
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_cube.push_back(sdf_square(sdf_vec_x[q] - 50, sdf_vec_y[q] - 50, sdf_vec_z[q] - 50, 25)); //Center: (50,50,50) Length: 15
		if (sdf_vec_m_cube[q] < 0) { sdf_vec_m_cube[q] = 0; }
	}
	//TORUS
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_tr.push_back(sdf_torus(sdf_vec_x[q] - 50, sdf_vec_y[q] - 50, sdf_vec_z[q] - 50, 35,15)); //Center: (50,50,50) Torus Inner Radius: 20 Scanning Radius: 15
		if (sdf_vec_m_tr[q] < 0) { sdf_vec_m_tr[q] = 0; }
	}
	//CAPSULE
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_cp.push_back(sdf_capsule(sdf_vec_x[q], sdf_vec_y[q] , sdf_vec_z[q], 60,60,60,40,40,40,20)); //A(60,60,60) B(40,40,40) Radius: 20
		if (sdf_vec_m_cp[q] < 0) { sdf_vec_m_cp[q] = 0; }
	}

	//SUBSTRACTION
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_subs.push_back(sdf_substraction(sdf_vec_m_cube[q], sdf_vec_m_sp[q])); //Substraction mathematical operation
	}
	//INTERSECTION
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_inter.push_back(sdf_inter(sdf_vec_m_cube[q], sdf_vec_m_sp[q])); //Intersection mathematical operation
	}
	//UNION
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_union.push_back(sdf_union(sdf_vec_m_cube[q], sdf_vec_m_sp[q])); //Union mathematical operation
	}
	
	
	//CREATING OBJECT WITH MATHEMATICAL OPERATIONS
	//LEFT EAR
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_eye_l.push_back(sdf_sphere(sdf_vec_x[q] - 30, sdf_vec_y[q] - 85, sdf_vec_z[q] - 70, 10)); 
		if (sdf_vec_m_eye_l[q] < 0) { sdf_vec_m_sp[q] = 0; }
	}
	//RIGHT EAR
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_eye_r.push_back(sdf_sphere(sdf_vec_x[q] - 70, sdf_vec_y[q] - 85, sdf_vec_z[q] - 70, 10)); 
		if (sdf_vec_m_eye_r[q] < 0) { sdf_vec_m_sp[q] = 0; }
	}
	//MOUTH
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_mouth.push_back(sdf_torus(sdf_vec_x[q] - 50, sdf_vec_y[q] - 50, sdf_vec_z[q] - 50, 40, 10)); 
		if (sdf_vec_m_mouth[q] < 0) { sdf_vec_m_tr[q] = 0; }
	}
	//FACE
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_face.push_back(sdf_union(sdf_vec_m_sp[q], sdf_vec_m_eye_l[q])); 
	}
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_face[q]=(sdf_union(sdf_vec_m_face[q], sdf_vec_m_eye_r[q])); 
	}
	for (int q = 0; q < sdf_vec_x.size(); q++) {
		sdf_vec_m_face[q] = (sdf_substraction(sdf_vec_m_mouth[q], sdf_vec_m_face[q])); 
	}
	try {
		cout << "\nWriting  array contents to file...";
		//open file for writing
		ofstream fw("c:\\deneme\\deneme.txt", std::ofstream::out);
		//check if file was successfully opened for writing
		if (fw.is_open())
		{
			//store array contents to text file
			for (int z = 0; z < sdf_vec_x.size(); z++) {
				fw << sdf_vec_x[z] <<" "<< sdf_vec_y[z] << " " << sdf_vec_z[z] << " " << sdf_vec_m_face[z] << "\n";
			}
			fw.close();
		}
		else cout << "Problem with opening file";
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}