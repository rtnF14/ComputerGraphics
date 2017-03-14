#Grafika Komputer

Implementasi algoritma dasar grafika komputer, pada framebuffer linux..

Untuk build :
1. Clone / download repository ini
2. Buka terminal, masuk ke folder tersebut.
3. Ketik "make"
4. "./itbmapview"

Berikut adalah modul-modul yang digunakan 

##ADT Point
Primitif untuk mengelola struktur data point.
typedef struct {
    int x;
    int y;
} Point;

Point makePoint(int x, int y);


##ADT Queue of Point
Struktur data queue untuk elemen point
typedef struct qi_t* qi_p;
typedef struct qi_t {
    qi_p next;
    Point data;
} queueItem;
typedef struct {
    queueItem* first;
    queueItem* last;
} queue;
void initQueue(queue* q);
char queueEmpty(queue* q);
void insertPoint(queue* q, Point d);
Point nextPoint(queue* q);



##ADT Color
Primitif untuk mengelola struktur data RGB.
typedef struct {
    int R;
    int G;
    int B;
} Color;

Color setColor(int r, int g, int b);
int isColorSame(Color C1, Color C2);



##Modul Framebuffer
ADT untuk mengelola framebuffer.
Membutuhkan ADT Color untuk menggunakan warna RGB.

int fbfd;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize;
char *fbp;
int displayWidth, displayHeight;

void initScreen();
void printBackground(Color C);
void setXY (int squareSize, int x, int y, Color C);
Color getXY(int x, int y);
void terminate();


##Modul Geometry
Kumpulan algoritma untuk menggambar bentuk bentuk geometri dasar.
Setiap bentuk geometri didefinisikan dengan titik dan warnanya .
Membutuhkan ADT Color untuk mendefinisikan warna.
Membutuhkan ADT Point untuk mendefinisikan titik.

void drawBresenhamLine (Point P1, Point P2, Color C, int W);
void drawPolyline (int n, Point *P, Color C, int W);
void drawPolygon (int n, Point *P, Color C, int W);
void drawExplosion (Point initialPoint, int n, Point *P, int scaleFactor);
void drawCircle (int radius, Point P, int W, Color C);
void drawCircleHalf (int radius, Point P, int W, Color C);


##Modul Transform
Kumpulan algoritma untuk melakukan transformasi geometri dasar.
Membutuhkan ADT Point 

Point rotatePoint(Point p ,Point pivot, float angle);
Point* rotateMany(Point p, Point* p1, double angle, int length);
void ScaleLine(Point * p , double scalingFactorX , double scalingFactorY );
void TranslationLine(Point *  p , int xTranslation, int yTranslation);


##Modul Clipping
Algoritma Clipping Cohen-Sutenham



typedef struct
{
	int xLeft;
	int xRight;
	int yTop;
	int yBottom;
} ClippingWindow;


typedef struct
{
	int left;
	int right;
	int top;
	int bottom;
} RegionCode;

typedef struct
{
	int resultStatusCode;
	int isLeftIntersection;
	int isRightIntersection;
	int isTopIntersection;
	int isBottomIntersection;
	int isStartPointCompletelyInside;
	int isEndPointCompletelyInside;
	Point startPoint;
	Point endPoint;
	RegionCode startPointRegionCode;
	RegionCode endPointRegionCode;
} LineAnalysisResult;


ClippingWindow setClippingWindow(int left, int right, int top, int bottom);
RegionCode initRegionCode();
RegionCode computeRegionCode(Point p, ClippingWindow cw);
LineAnalysisResult analyzeLine(Point startPoint, Point endPoint, ClippingWindow cw);
LineAnalysisResult initLineAnalysisResult();
void printRegionCode(RegionCode rc);
int checkRegionCodeBit(int a, int b);
int isPointCompletelyInside(RegionCode x);
int isCompletelyInside(LineAnalysisResult x);
int isCompletelyOutside(LineAnalysisResult x);
void clipLine(LineAnalysisResult lar1, ClippingWindow cw1 , Point * output);


##Modul Keypress
Menangani penekanan keypress
int getch(void);


##Modul Filling
Algoritma untuk melakukan color fill pada objek geometri.
Membutuhkan modul color, point, dan pointqueue

void floodFill(int fp_x, int fp_y, Color C, Color fc);


##Modul Physics
Simulasi fisika "drag" & gravitasi pada titik.
Membutuhkan ADT Point

typedef struct {
  Point pos;
  Point vel;
} PhysicsPoint;

PhysicsPoint makePhysicsPoint(int x, int y, int xvel, int yvel);
void updatePhysicsPoint(PhysicsPoint* pp);



##Modul Game
Implementasi sebuah game shooter , memanfaatkan modul modul yang 
tersedia
