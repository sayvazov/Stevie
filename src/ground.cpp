#include "ground.h"
#include "algorithm.h"


ground::ground(gl::GlslProgRef shader)
{
	groundShader = shader;
	
}


ground::~ground()
{
}

void ground::setup()
{
	//Some colors, to show off
	groundSurface = Surface(256, 256, true);
	for (int row = 0; row < groundSurface.getHeight(); row++)
	{
		for (int col = 0; col < groundSurface.getWidth(); col++)
		{
			groundSurface.setPixel(ivec2(col, row), ColorA8u(row, col, 128, 255));
		}
	}
	groundTexture = gl::Texture::create(groundSurface);
	groundTexture->bind(0);
	groundShader->uniform("diffuseMap", 0);

	groundShader->uniform("ciLightDir", vec3(1, 1, 1.0));

	//make some hills
	std::unique_ptr<algorithm::matrix<float>>perlin = algorithm::createPerlinNoise(256, 7, 0.4);
	geom::Plane groundPlane = geom::Plane()
		.normal(vec3(0, 0, 1))
		.origin(vec3(0, 0, 0))
		.subdivisions(glm::ivec2(256, 256))
		.size(glm::vec2(10, 10));
	groundMesh = gl::VboMesh::create(groundPlane);

	//Transfer hills into VBOmesh
	auto mappedPosAttrib = groundMesh->mapAttrib3f(geom::Attrib::POSITION, false);
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			vec3 &pos = *mappedPosAttrib;
			mappedPosAttrib->z = perlin->at(i)[j];
			++mappedPosAttrib;
		}
	}
	mappedPosAttrib.unmap();
}

void ground::draw()
{
	
	gl::pushModelMatrix();
	groundShader->bind();
	gl::draw(groundMesh);
	gl::popModelMatrix();
}
