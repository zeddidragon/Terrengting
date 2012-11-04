#include "sphere.h"

Sphere::Sphere(unsigned int slices){
	vec4 top = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vec4 bottom = vec4(0.0f, -1.0f, 0.0f, 1.0f);

	int index;
	// There will be a "seam" of overlapping vertices for the sake of UV-mapping, hence (slices + 1)
	int vertexCount = slices * (slices + 1);
	
	// On calculating index count
	// Since I'll be using triangles, it means the index count
	// will be 3 * amount of triangles.
	// The bare minimum of feasible slices is 3.
	//
	// In this scenario, there are 3 triangles at the top
	// and 3 at the bottom.
	// Each slice hereafter adds one extra triangle to the top and bottom.
	// So for all the triangles at the top and bottom you can use
	// 2 * slices. Index count is therefore 3 * 2 * slices.
	//
	// The amount of triangles is twice the amount of quads.
	// At the bare minimum of 3 slices, there is 3 * 2  in the quads.
	// 3 horizontally because it wraps, but vertically it doesn't.
	// Generally we can say there's slices * (slices - 1) quads.
	//
	// Total formula:
	//
	// 6s(s-1)

	int indexCount = 6 * slices * (slices - 1);

	Vertex* vertices = new Vertex[vertexCount];
	GLuint* indices = new GLuint[indexCount];
	
	float angleStep = 180.0f / (slices - 1);
	float currentAngle = 90.0f;

	//Generate vertices and normals
	index = 0;
	for (unsigned int i = 0; i < slices; ++i){
		VertexRow(currentAngle, slices, vertices, index);
		currentAngle += angleStep;
	}

	index = 0;
	//Generate indices
	for (unsigned int i = 0; i < slices - 1; ++i){
		QuadRow(slices, i, indices, index);
	}

	/*
	Model::GenerateNormals(vertices, indices, vertexCount, indexCount);
	Model::GenerateTangents(vertices, indices, vertexCount, indexCount);
	Model::GenerateBitangents(vertices, vertexCount);
	*/
	Model::GenerateVao(vertices, indices, vertexCount, indexCount);

	delete[] vertices;
	delete[] indices;
}

//		   Top
//		   /\
//		  /  \
//		 /	  \
//		/______\
// Left			Right
//
// We want our triangle defined clockwise, so we go top-right-left

void Sphere::QuadRow(int slices, int currentSlice, GLuint* indices, int& index){
	int rowSize = slices + 1;
	int start = currentSlice * rowSize;
	int end = start + rowSize - 1;

	int topRight;

	for (topRight = start; topRight < end; ++topRight){
		//First triangle
		indices[index++] = topRight;			  //Top right
		indices[index++] = topRight + 1;		  //Top left
		indices[index++] = topRight + rowSize;	  //Bottom right

		//Second triangle		
		indices[index++] = topRight + 1;		  //Top left
		indices[index++] = topRight + rowSize + 1; //Bottom left
		indices[index++] = topRight + rowSize;	  //Bottom right
	}
}

void Sphere::VertexRow(float latitude, int slices, Vertex* vertices, int& index){
	// The vertices comes out in a clockwise circle starting at (0, y, -1)
	float angleStep = 360.0f / slices;
	float currentAngle = -180.0f;
	float uStep = 1.0f / slices;
	float currentU = 0;

	for (int i = 0; i <= slices; ++i){
		vec4 position = Point(latitude, currentAngle);
		vertices[index].Position = position;
		vertices[index].Normal = vec3(position);
		vertices[index].Tangent = vec3(Point(latitude, currentAngle + 90));
		vertices[index].Bitangent = glm::cross(vertices[index].Normal, vertices[index].Tangent);
		vertices[index].UvCoordinate = vec2(currentU, position.y + 0.5f);

		currentAngle += angleStep;
		currentU += uStep;
		++index;
	}
}

vec4 Sphere::Point(float latitude, float longtitude){
	float rLat, rLong, x, y, z, radius;
	// Radius is the distance from center, ignoring the y-axis.
	// Think radius in the sense of a cylinder.

	rLat = glm::radians(latitude);
	rLong = glm::radians(longtitude);

	// http://www.wolframalpha.com/input/?i=cos%28phi%29+where+phi+goes+from+pi%2F2+to+-pi%2F2
	radius = cos(rLat);

	// http://www.wolframalpha.com/input/?i=sin%28-phi%29+where+phi+goes+from+pi%2F2+to+-pi%2F2
	y = sin(rLat);

	// http://www.wolframalpha.com/input/?i=sin%28-phi%29+where+phi+goes+from+pi+to+-pi
	x = sin(-rLong) * radius;

	// http://www.wolframalpha.com/input/?i=cos%28phi%29+where+phi+goes+from+pi+to+-pi
	z = cos(rLong) * radius;

	// Basically, x and z are calculated as if we're dealing with a cylinder, then
	// multiplied by the radius which is calculated by latitude

	return vec4(x, y, z, 1.0f);
}