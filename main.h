extern int mainWindow;
extern int w;
extern int h;

extern bool blend;
extern bool bp;
extern GLuint texture[1];
extern int start_flag;
int LoadGLTextures();
void init();

void drawObstacle(float xx, float yy, float zz);
void drawTunnel();
void drawTunnel2();
void drawPlane();
