#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/TriMesh.h"
#include "cinder/MayaCamUI.h"
#include "cinder/gl/Vbo.h"

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
    
    gl::VboMeshRef          mVboMesh;
    
    static const int VERTICES_X = 50, VERTICES_Z = 50;
    
    // camera
	MayaCamUI               mMayaCam;
	CameraPersp             mCamera;
};

void mMeshTutorialApp::setup()
{
    // setup cameras
	mCamera = CameraPersp(getWindowWidth(), getWindowHeight(), 75.0f, 200.0f, 10000.0f);
	mCamera.setEyePoint( Vec3f(300.0f, 300.0f, 10.0f) );
	mCamera.setCenterOfInterestPoint( Vec3f(0.0f, 0.0f, 0.0f) );
	mMayaCam.setCurrentCam( mCamera );
    
	// setup the parameters of the Vbo
	int totalVertices = VERTICES_X * VERTICES_Z;
	int totalQuads = ( VERTICES_X - 1 ) * ( VERTICES_Z - 1 );
	gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setDynamicPositions();
	layout.setStaticTexCoords2d();
	mVboMesh = gl::VboMesh::create( totalVertices, totalQuads * 4, layout, GL_QUADS );
    
	// buffer our static data - the texcoords and the indices
	vector<uint32_t> indices;
	for( int x = 0; x < VERTICES_X; ++x ) {
		for( int z = 0; z < VERTICES_Z; ++z ) {
			// create a quad for each vertex, except for along the bottom and right edges
			if( ( x + 1 < VERTICES_X ) && ( z + 1 < VERTICES_Z ) ) {
				indices.push_back( (x+0) * VERTICES_Z + (z+0) );
				indices.push_back( (x+1) * VERTICES_Z + (z+0) );
				indices.push_back( (x+1) * VERTICES_Z + (z+1) );
				indices.push_back( (x+0) * VERTICES_Z + (z+1) );
			}
		}
	}
    
    mVboMesh->bufferIndices(indices);
    
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
	mCamera.setPerspective( 75.0f, getWindowAspectRatio(), 300.0f, 1000 );
	
	// and in turn, let OpenGL know we have a new camera
	gl::setMatrices( mCamera );
}

void mMeshTutorialApp::update()
{
    // update the camera
    gl::setMatrices( mCamera );
    
	const float timeFreq = 5.0f;
	const float zFreq = 3.0f;
	const float xFreq = 7.0f;
	float offset = getElapsedSeconds() * timeFreq;
    
    
	// dynmaically generate our new positions based on a simple sine wave
	gl::VboMesh::VertexIter iter = mVboMesh->mapVertexBuffer();
	for( int x = 0; x < VERTICES_X; ++x ) {
		for( int z = 0; z < VERTICES_Z; ++z ) {
			float height = sin( z / (float)VERTICES_Z * zFreq + x / (float)VERTICES_X * xFreq + offset ) / 5.0f;
			iter.setPosition( Vec3f( x / (float)VERTICES_X, height, z / (float)VERTICES_Z ) );
			++iter;
		}
	}
    
    
}

void mMeshTutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );

    gl::scale( Vec3f( 200, 200, 200 ) );
    gl::enableWireframe();
    
    gl::draw(mVboMesh);
    
}

CINDER_APP_NATIVE( mMeshTutorialApp, RendererGl )