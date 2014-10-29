extern float plane_x;
extern float plane_y;
extern float plane_z;

extern float xx;
extern float yy;
extern float zz;

extern float tunnel_z;
extern float tunnel_z2;
extern int frame;
extern char s[60];
extern long time, timebase;
extern int score;
void setOrthographicProjection();
void restorePerspectiveProjection();

void reshapeWindow(int w, int h);
void renderDisplay(void);
