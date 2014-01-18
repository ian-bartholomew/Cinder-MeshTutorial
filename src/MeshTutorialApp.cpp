#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MeshTutorialApp : public AppNative {
public:
	void setup();
	void mouseDown( MouseEvent event );
	void update();
	void draw();
    
    ci::TriMesh mesh;
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
    
    
    
    // Position and Color for the four corners
    mesh.appendVertex( Vec3f( 10, 10, 0 ) );
    mesh.appendColorRgb( Color( 1, 0, 0 ) );
    mesh.appendVertex( Vec3f( 10, 300, 0 ) );
    mesh.appendColorRgb( Color( 0, 1, 0 ) );
    mesh.appendVertex( Vec3f( 300, 300, 0 ) );
    mesh.appendColorRgb( Color( 0, 0, 1 ) );
    mesh.appendVertex( Vec3f( 300, 10, 0 ) );
    mesh.appendColorRgb( Color( 0, 0, 0 ) );
    
    // Indices for each of the four corners
    int vIdx0 = mesh.getNumVertices() - 4;
    int vIdx1 = mesh.getNumVertices() - 3;
    int vIdx2 = mesh.getNumVertices() - 2;
    int vIdx3 = mesh.getNumVertices() - 1;
    
    // Two triangles to create our square
    mesh.appendTriangle( vIdx0, vIdx1, vIdx2 );
    mesh.appendTriangle( vIdx0, vIdx2, vIdx3 );
    
    gl::draw(mesh);
    
}

CINDER_APP_NATIVE( MeshTutorialApp, RendererGl )