#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"


using namespace ci;

class ground
{
public:
	ground(gl::GlslProgRef shader);
	~ground();
	void setup();
	void draw();
private:
	gl::BatchRef groundBatch;
	gl::GlslProgRef groundShader;
	gl::VboMeshRef groundMesh;
	Surface groundSurface;
	gl::TextureRef groundTexture;
	gl::TextureRef groundNormalTexture;
};

