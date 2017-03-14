#include "color.h"
#include "grafika.h"
#include "framebuffer.h"

int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
int displayWidth, displayHeight;

/*
Initiate connection to framebuffer
*/
void initScreen() {
    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    if (vinfo.yres < 700) {
        screensize = vinfo.xres * finfo.line_length * vinfo.bits_per_pixel / 8;
    } else {
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    }

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                fbfd, 0);
    if ((long)fbp == -1) {
    perror("Error: failed to map framebuffer device to memory");
    exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
    displayWidth = vinfo.xres;
    displayHeight = vinfo.yres;
}

/*Color struct consists of Red, Green, and Blue */
/*
Procedure untuk menggambar ke framebuffer

squareSize    : square size
x   : x coordinate
y   : y coordinate
C       : Color struct (Red, Green, Blue)
*/
void setXY (int squareSize, int x, int y, Color C) {
    long int location;
    int i,j;
    if (((x)>=0) && ((x + squareSize)<vinfo.xres) && ((y)>=0) && ((y + squareSize)<vinfo.yres)) {
        for (i = x; i < (x+squareSize); i++) {
            for (j = y; j < (y+squareSize); j++) {
                location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;

                if (fbp + location) { //check for segmentation fault
                    if (vinfo.bits_per_pixel == 32) {
                        *(fbp + location) = C.B;            //Blue
                        *(fbp + location + 1) = C.G;        //Green
                        *(fbp + location + 2) = C.R;        //Red
                        *(fbp + location + 3) = 0;          //Transparancy
                    } else  { //assume 16bpp
                        int r = C.R;     //Red
                        int g = C.G;     //Green
                        int b = C.B;     //Blue

                        unsigned short int t = r<<11 | g << 5 | b;
                        *((unsigned short int*)(fbp + location)) = t;
                    }
                } else {
                    return;
                }
            }
        }
    }
}



/*
Set screen background with C color
*/
void printBackground(Color C) {
    long int location;
    int width = displayWidth - 6;
    int height = displayHeight - 6;
    int i,j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = C.B;         //Blue
                *(fbp + location + 1) = C.G;     //Green
                *(fbp + location + 2) = C.R;     //Red
                *(fbp + location + 3) = 0;       //No transparency
            } else  { //assume 16bpp
                int r = C.R;     //Red
                int g = C.G;     //Green
                int b = C.B;     //Blue

                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
    }
}



/*
Function untuk mendapatkan warna dari suatu pixel pada posisi x dan y
*/
Color getXY(int x, int y) {
    long int location;
    Color out;
    out.R = -999; out.G = -999; out.B = -999;
    if (((x)>=0) && (x<vinfo.xres) && ((y)>=0) && (y<vinfo.yres)) {

        location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;

        if (fbp + location) { //check for segmentation fault
            if (vinfo.bits_per_pixel == 32) {

                out.R = (int) *(fbp + location + 2);        //Red
                out.G = (int) *(fbp + location + 1);        //Green
                out.B = (int) *(fbp + location);            //Blue
                if (out.R < 0) out.R += 256;
                if (out.G < 0) out.G += 256;
                if (out.B < 0) out.B += 256;

                *(fbp + location + 3) = 0;          //Transparancy
            } else  { //assume 16bpp
                int t = *((unsigned short int*)(fbp + location));
                out.R = (t & 63488) >> 11;     //Red
                out.G = (t & 2016) >> 5;     //Green
                out.B = t & 31;     //Blue

            }
        }
    } else {
    }
    return out;
}


/*
Closing the framebuffer connection
*/
void terminate(){
    munmap(fbp, screensize);
    close(fbfd);
}