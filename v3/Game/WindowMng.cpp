#include "WindowMng.h"


WindowMng::WindowMng(int width, int height){
	m_width = width;
	m_height = height;
	m_pressingKey = false;

	m_camera = new Camera(Vector3<float>(2.5, 2.5, 3), Vector3<float>(0,0,0));

}

void WindowMng::GLInit(){
	int ok;

	glfwInit();

	ok = glfwOpenWindow(
							m_width, m_height,          // Width and height of window
							8, 8, 8,           // Number of red, green, and blue bits for color buffer
							8,                 // Number of bits for alpha buffer
							24,                // Number of bits for depth buffer (Z-buffer)
							0,                 // Number of bits for stencil buffer
							GLFW_WINDOW        // We want a desktop window (could be GLFW_FULLSCREEN)
						);

    // If we could not open a window, exit now
    if( !ok )
    {
        glfwTerminate();
    }

	

	// Set window title
    glfwSetWindowTitle( "Game Layer" );

	// Enable sticky keys
    glfwEnable( GLFW_STICKY_KEYS );
	
	glfwGetWindowSize( &m_width, &m_height );
    glViewport( 0, 0, m_width, m_height );

	// Set up projection matrix
    glMatrixMode( GL_PROJECTION );    // Select projection matrix
    glLoadIdentity();                 // Start with an identity matrix
    gluPerspective(                   // Set perspective view
        90.0,                         // Field of view = 65 degrees
        (double)m_width/(double)m_height, // Window aspect (assumes square pixels)
        0.01,                          // Near Z clipping plane
        10000.0                         // Far Z clippling plane
    );

	//Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enable z buffer
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void WindowMng::GLConfig(){

	


	// Clear color and depht buffers
    glClearColor( 0.3f, 0.3f, 1.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glRotatef(m_camera->m_rotation.GetX(),1.0,0.0,0.0); //rotate our camera on teh x-axis (left and right)
	glRotatef(m_camera->m_rotation.GetY(),0.0,1.0,0.0); //rotate our camera on the y-axis (up and down)
	glRotatef(m_camera->m_rotation.GetZ(),0.0,0.0,1.0);
	glTranslated(-m_camera->m_pos.GetX(),-m_camera->m_pos.GetY(),-m_camera->m_pos.GetZ()); //translate the screen to the position of our camera


}


Vector3<float> WindowMng::GetCameraPosition(){
	return m_camera->GetPosition();

}

bool WindowMng::isRunning(){

	return (!glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED ));

}

void WindowMng::UpdateKeyboard(){
	m_camera->UpdateKeyboard();
	
	if(glfwGetKey( '1' ) && m_pressingKey == false){
		conf_showWireFrame = !conf_showWireFrame;
		m_pressingKey = true;
	}
	/*
	else if(glfwGetKey( '2' ) && m_pressingKey == false){
		conf_showHeightMap = !conf_showHeightMap;
		m_pressingKey = true;
	}
	else if(glfwGetKey( '3' ) && m_pressingKey == false){
		conf_showVerticesDisplacement = !conf_showVerticesDisplacement;
		m_pressingKey = true;
	}
	else if(glfwGetKey( '4' ) && m_pressingKey == false){
		conf_showBlendTexture = !conf_showBlendTexture;
		m_pressingKey = true;
	}
	else if(glfwGetKey( '5' ) && m_pressingKey == false){
		conf_showLight = !conf_showLight;
		m_pressingKey = true;
	}
	*/

	
	
	if(glfwGetKey( '1' ) == GLFW_RELEASE
		&& glfwGetKey( '2' ) == GLFW_RELEASE
		&& glfwGetKey( '3' ) == GLFW_RELEASE
		&& glfwGetKey( '4' ) == GLFW_RELEASE
		&& glfwGetKey( '5' ) == GLFW_RELEASE){
			m_pressingKey = false;
	}
	
}

void WindowMng::UpdateMouse(){
	m_camera->UpdateMouse();
}