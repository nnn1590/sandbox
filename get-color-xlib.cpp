#include <iostream>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

typedef struct{
	int x, y;
} Pos;

Pos get_pos(Display *dpy, Window root){
	Window root_return, child_return;
	Pos root_pos;
	int win_x, win_y;
	unsigned int mask;

	XQueryPointer(dpy, root, &root_return, &child_return, &root_pos.x, &root_pos.y, &win_x, &win_y, &mask);

	return root_pos;
}

int main(int, char**) {
	XColor c;
	Display *d = XOpenDisplay((char *) NULL);

	int x=0;  // Pixel x 
	int y=0;  // Pixel y

	XImage *image;
	image = XGetImage (d, XRootWindow (d, XDefaultScreen (d)), x, y, 1, 1, AllPlanes, XYPixmap);
	c.pixel = XGetPixel (image, 0, 0);
	XFree (image);
	XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);
	cout << c.red/256 << " " << c.green/256 << " " << c.blue/256 << "\n";

	Window cha = XCreateSimpleWindow(d,RootWindow(d,DefaultScreen(d)), 100, 50, 800, 530, 1, 96653, c.pixel);
	XMapWindow(d,cha); //ウィンドウのマップ
	XFlush(d); //Xサーバーにイベントを送信する
	GC gc = XCreateGC(d, cha, 0, 0);
	Font font = XLoadFont(d, "r24");
	XSetFont(d, gc, font);
	XColor aka, dummy;
	XAllocNamedColor( d, XDefaultColormap(d, XDefaultScreen (d)), "red", &aka, &dummy );
	Pos pos;
	while( 1 ) {
		pos = get_pos(d, XRootWindow(d, XDefaultScreen (d)));
		image = XGetImage (d, XRootWindow(d, XDefaultScreen (d)), pos.x, pos.y, 1, 1, AllPlanes, XYPixmap);
		c.pixel = XGetPixel (image, 0, 0);
		XFree (image);
		XQueryColor (d, XDefaultColormap(d, XDefaultScreen (d)), &c);
		//XSetBackground( d, gc, aka.pixel );    /* 色の設定 */
		XSetForeground( d, gc, c.pixel );    /* 色の設定 */
		string Str = to_string(c.red/256) + " " + to_string(c.green/256) + " " + to_string(c.blue/256);
		XFillRectangle(d, cha, gc, 10, 32, 640, 128);  /* 長方形 */
		XDrawImageString(d, cha, gc, 100,100, Str.c_str(), strlen(Str.c_str()));
		//cout << Str.c_str();
		XFlush( d );
	}

	return 0;
}
