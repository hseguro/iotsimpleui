#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

class Framebuffer{
    public:
        char *fb_memory = 0;
        long int screensize = 0;
        int width, height;
        int bpp;
        int Init();
        int Resize(int width, int height);
        void Close();
    private:
        int fb_fd = 0;
        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
};

int Framebuffer::Init(){
    fb_fd = open("/dev/fb1", O_RDWR);
    if(fb_fd == -1){
        perror("Error: cannot open framebuffer device");
        return -1;
    }

    if(ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo) == -1){
        perror("Error: reading fixed information");
        return -1;
    }

    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        return -1;
    }

    width = vinfo.xres;
    height = vinfo.yres;
    bpp = vinfo.bits_per_pixel;

    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    fb_memory = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);

    if((int)fb_memory == -1){
        perror("Error: failed to map framebuffer device to memory");
        return -1;
    }

    //memset(fb_memory, 100, screensize);

    return 1;
}

int Framebuffer::Resize(int width, int height){
    return 0;
}

void Framebuffer::Close(){
    munmap(fb_memory, screensize);
    close(fb_fd);
}