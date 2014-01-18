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
    
    // camera
	MayaCamUI               mMayaCam;
	CameraPersp             mCamera;
};

void mMeshTutorialApp::setup()
{
    // setup cameras
	mCamera = CameraPersp(getWindowWidth(), getWindowHeight(), 75.0f, 50.0f, 10000.0f);
	mCamera.setEyePoint( Vec3f(300.0f, 300.0f, 200.0f) );
	mCamera.setCenterOfInterestPoint( Vec3f(100.0f, 100.0f, 0.0f) );
	mMayaCam.setCurrentCam( mCamera );
    
    gl::VboMesh::Layout layout;
    layout.setStaticIndices();
    layout.setDynamicColorsRGBA();
    layout.setStaticPositions();
    
    int vertCount = 24;
    int quadCount = 6;
    mVboMesh = gl::VboMesh::create(vertCount, quadCount * 4, layout, GL_QUADS);
    
    
    vector<uint32_t> indices;
    int i=0;
    while(i < 24){
        indices.push_back(i);
        i++;
    }
    
    mVboMesh->bufferIndices(indices);
    
    std::vector<Vec3f> positions;
    
    positions.push_back(Vec3f(100, 200, 1));
    positions.push_back(Vec3f( 200, 200, 1));
    positions.push_back(Vec3f( 200, 100, 1));
    positions.push_back(Vec3f(100, 100, 1));
    
    positions.push_back(Vec3f( 200, 200, 1));
    positions.push_back(Vec3f( 200, 200, 100));
    positions.push_back(Vec3f( 200, 100, 100));
    positions.push_back(Vec3f( 200, 100, 1));
    
    positions.push_back(Vec3f( 200, 200, 100));
    positions.push_back(Vec3f(100, 200, 100));
    positions.push_back(Vec3f(100, 100, 100));
    positions.push_back(Vec3f( 200, 100, 100));
    
    positions.push_back(Vec3f(100, 200, 100));
    positions.push_back(Vec3f(100, 200, 1));
    positions.push_back(Vec3f(100, 100, 1));
    positions.push_back(Vec3f(100, 100, 100));
    
    positions.push_back(Vec3f(100, 200, 100));
    positions.push_back(Vec3f( 200, 200, 100));
    positions.push_back(Vec3f( 200, 200, 1));
    positions.push_back(Vec3f(100, 200, 1));
    
    positions.push_back(Vec3f(100, 100, 100));
    positions.push_back(Vec3f( 200, 100, 100));
    positions.push_back(Vec3f( 200, 100, 1));
    positions.push_back(Vec3f(100, 100, 1));
    
    // now we can buffer positions
    mVboMesh->bufferPositions(positions);
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
    
    float g = sin(getElapsedSeconds());
    float b = cos(getElapsedSeconds());
    gl::VboMesh::VertexIter iter = mVboMesh->mapVertexBuffer();
    for( int x = 0; x < 24; ++x ) {
        //positions.at(x) *= 1.001;
        iter.setColorRGBA( ColorA( 1 - (g+b/3), g, b, 0.5) );
        ++iter;
    }
    
    
}

void mMeshTutorialApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );

    gl::enableWireframe();
    
    gl::draw(mVboMesh);
    
}

CINDER_APP_NATIVE( mMeshTutorialApp, RendererGl )