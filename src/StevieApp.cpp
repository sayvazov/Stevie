#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder\gl\Texture.h"
#include "ground.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class StevieApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

private:
	CameraPersp myCam;
	gl::GlslProgRef shader;
	ground* gr;
	
	float time;
	float lastTime;
	bool spinning = true;
};

void StevieApp::setup()
{
	myCam.lookAt(glm::vec3(0, -2 ,1), glm::vec3(0, 0, 0));
	shader = gl::GlslProg::create(loadAsset("shader.vert"), loadAsset("shader.frag"));

	gr = new ground(shader);
	gr->setup();
	
}

void StevieApp::mouseDown( MouseEvent event )
{
	spinning = !spinning;
}

void StevieApp::update()
{
	if (spinning)
	{
		time += getElapsedSeconds() - lastTime;
		vec3 eyePoint(cos(time) * 2, sin(time) * 2, 1);
		myCam.lookAt(eyePoint, vec3(0, 0, 0));
		myCam.setWorldUp(vec3(0, 0, 1));
	}
	lastTime = getElapsedSeconds();
}

void StevieApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::pushModelMatrix();

	gl::setMatrices(myCam);
	gr->draw();
	
	gl::popModelMatrix();
}

CINDER_APP( StevieApp, RendererGl )
