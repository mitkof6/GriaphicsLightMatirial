#define L1_X 0.0
#define L1_Y 200.0
#define L1_Z 50.0

#define L2_X -L1_X
#define L2_Y -L1_Y
#define L2_Z -L1_Z

#define PI 3.14


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

