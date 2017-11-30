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
	
	groundSurface = Surface(256, 256, true);
	for (int row = 0; row < groundSurface.getHeight(); row++)
	{
		for (int col = 0; col < groundSurface.getWidth(); col++)
		{
			groundSurface.setPixel(ivec2(col, row), ColorA8u(row, col, 128, 128));
		}
	}

	groundTexture = gl::Texture::create(groundSurface);
	groundTexture->bind(1);

	Surface groundNormalSurface = algorithm::generatePerlin(16, 16);//algorithm::surfaceFromMatrix(*algorithm::createPerlinNoise(256, 16, 128));
	groundNormalTexture = gl::Texture::create(groundNormalSurface);
	groundNormalTexture->bind(0);

	groundShader->uniform("diffuseMap", 0);
	groundShader->uniform("normalMap", 1);
	groundShader->uniform("ciLightDir", vec3(1, 1, 1));

	groundPlane = geom::Plane().normal(vec3(0, 0, 1)).origin(vec3(0, 0, 0));
	groundBatch = ci::gl::Batch::create(groundPlane, groundShader);

}

void ground::draw()
{
	gl::pushModelMatrix();
	//groundTexture->bind();
	groundBatch->draw();
	//groundTexture->unbind();
	gl::popModelMatrix();
}
