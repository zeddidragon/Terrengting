#ifndef ZEDDY_SPHERE_H_
#define ZEDDY_SPHERE_H_

#include "model.h"

class Sphere : public Model{
public:
	Sphere(unsigned int slices);
private:
	void VertexRow(float latitude, int slices, Vertex* vertices, int& index);
	void Top(int slices, GLuint* indices, int& index);
	void Bottom(int slices, GLuint* indices, int& index);
	void QuadRow(int slices, int currentSlice, GLuint* indices, int& index);
	vec4 Point(float latitude, float longtitude);
};

#endif