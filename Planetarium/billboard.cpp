#include "billboard.h"

BillBoard::BillBoard(vec2 dimensions, vec2 origin, vec2 uv1, vec2 uv2){
	Vertex vertex = {
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
		vec3(0.0f, 0.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
		vec2(0.0f, 0.0f)
	};

	Vertex vertices[4];
	
	// Top left
	vertices[0] = vertex;
	vertices[0].Position = vec4(-origin, 0.0f, 1.0f);
	vertices[0].UvCoordinate = uv1;

	// Top right
	vertices[1] = vertex;
	vertices[1].Position = vec4(dimensions.x - origin.x, origin.y, 0.0f, 1.0f);
	vertices[1].UvCoordinate = vec2(uv2.x, uv1.y);

	// Bottom left
	vertices[2] = vertex;
	vertices[2].Position = vec4(origin.x, dimensions.y - origin.y, 0.0f, 1.0f);
	vertices[2].UvCoordinate = vec2(uv1.x, uv2.y);

	// Bottom right
	vertices[3] = vertex;
	vertices[3].Position = vec4(dimensions - origin, 0.0f, 1.0f);
	vertices[3].UvCoordinate = uv2;
}