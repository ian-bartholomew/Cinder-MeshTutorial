#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include "cinder/MayaCamUI.h"

#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class mMeshTutorialApp : public AppNative {
public:
	void setup();
    void resize();
	void mouseDown( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void update();
	void draw();
    
    ci::TriMesh mMesh;
    
    // camera
	MayaCamUI               mMayaCam;
	CameraPersp             mCamera;
};

void mMeshTutorialApp::setup()
{
    // setup cameras
	mCamera = CameraPersp(getWindowWidth(), getWindowHeight(), 75.0f, 50.0f, 10000.0f);
	mCamera.setEyePoint( Vec3f(200.0f, 200.0f, 200.0f) );
	mCamera.setCenterOfInterestPoint( Vec3f(0.0f, 0.0f, 0.0f) );
	mMayaCam.setCurrentCam( mCamera );
    
    // Create the points of our cube
    Vec3f v0(-100,-100,-100);
    Vec3f v1( 100,-100,-100);
    Vec3f v2( 100, 100,-100);
    Vec3f v3(-100, 100,-100);
    Vec3f v4(-100,-100, 100);
    Vec3f v5( 100,-100, 100);
    Vec3f v6( 100, 100, 100);
    Vec3f v7(-100, 100, 100);
    
    // Create the colors for each vertex
    Color c0( 0, 0, 0 );
    Color c1( 1, 0, 0 );
    Color c2( 1, 1, 0 );
    Color c3( 0, 1, 0 );
    Color c4( 0, 0, 1 );
    Color c5( 1, 0, 1 );
    Color c6( 1, 1, 1 );
    Color c7( 0, 1, 1 );
    
    Vec3f faces[6][4] = { /* Vertices for the 6 faces of a cube. */
        {v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
        {v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3} };
    
    Color colors[6][4] = { /* colors for each vertex of the cube. */
        {c0, c1, c2, c3}, {c3, c2, c6, c7}, {c7, c6, c5, c4},
        {c4, c5, c1, c0}, {c5, c6, c2, c1}, {c7, c4, c0, c3} };
    
    for (int i = 0; i < 6; i++)
    {
        
        mMesh.appendVertex(faces[i][0]);
        mMesh.appendColorRgb(colors[i][0]);
        mMesh.appendVertex(faces[i][1]);
        mMesh.appendColorRgb(colors[i][1]);
        mMesh.appendVertex(faces[i][2]);
        mMesh.appendColorRgb(colors[i][2]);
        mMesh.appendVertex(faces[i][3]);
        mMesh.appendColorRgb(colors[i][3]);
        
        int numberVertices = mMesh.getNumVertices();
        
        mMesh.appendTriangle( numberVertices - 4, numberVertices - 3, numberVertices - 2 );
        mMesh.appendTriangle( numberVertices - 4, numberVertices - 2, numberVertices - 1 );
        
    }
}

void mMeshTutorialApp::mouseDown( MouseEvent event )
{
    mMayaCam.mouseDown( event.getPos() );
}

void mMeshTutorialApp::mouseDrag( MouseEvent event )
{
	mMayaCam.mouseDrag( event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown() );
	mCamera = mMayaCam.getCamera();
}

void mMeshTutorialApp::resize()
{
    // now tell our Camera that the window aspect ratio has changed
	mCamera.setPerspective( 75.0f, getWindowAspectRatio(), 1, 1000 );
	
	// and in turn, let OpenGL know we have a new camera
	gl::setMatrices( mCamera );
}

void mMeshTutorialApp::update()
{
    // update the camera
    gl::setMatrices( mCamera );
    
    if( mMesh.getNumVertices() == 0 ) return;
    
    // store all the mMesh information
    
    std::vector<Color> col = mMesh.getColorsRGB();
    std::vector<Vec3f> vec = mMesh.getVertices();
    
    int i, j;
    i = mMesh.getNumVertices();
    j = 0;
    
    mMesh.clear();
    
    // something to add a little movement
    float inc = sin( getElapsedSeconds() );
    
    while(j < i)
    {
        // alter the positions array to get a little dynamism
        vec.at(j).x -= inc;
        vec.at(j+1).x += inc;
        vec.at(j+2).x += inc*2.0f;
        vec.at(j+3).x -= inc*2.0f;
        
        // now replace it in the mMesh
        mMesh.appendVertex( vec.at(j));
        mMesh.appendColorRgb( col.at(j) );
        mMesh.appendVertex( vec.at(j+1));
        mMesh.appendColorRgb( col.at(j+1) );
        mMesh.appendVertex( vec.at(j+2));
        mMesh.appendColorRgb( col.at(j+2) );
        mMesh.appendVertex( vec.at(j+3));
        mMesh.appendColorRgb( col.at(j+3) );
        
        int vIdx0 = mMesh.getNumVertices() - 4;
        int vIdx1 = mMesh.getNumVertices() - 3;
        int vIdx2 = mMesh.getNumVertices() - 2;
        int vIdx3 = mMesh.getNumVertices() - 1;
        
        mMesh.appendTriangle( vIdx0, vIdx1, vIdx2 );
        mMesh.appendTriangle( vIdx0, vIdx2, vIdx3 );
        
        // go to the next triangle pair
        j+=4;
    }
    
    
}

void mMeshTutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );

    gl::enableWireframe();
    
    gl::draw(mMesh);
    
}

CINDER_APP_NATIVE( mMeshTutorialApp, RendererGl )