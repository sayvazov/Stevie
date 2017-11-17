#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class StevieApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void StevieApp::setup()
{
}

void StevieApp::mouseDown( MouseEvent event )
{
}

void StevieApp::update()
{
}

void StevieApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( StevieApp, RendererGl )
