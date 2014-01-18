#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MeshTutorialApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void MeshTutorialApp::setup()
{
}

void MeshTutorialApp::mouseDown( MouseEvent event )
{
}

void MeshTutorialApp::update()
{
}

void MeshTutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( MeshTutorialApp, RendererGl )
