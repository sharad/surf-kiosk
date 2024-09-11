#include <X11/Xlib.h>
#include <gtk/gtk.h>

// Minimal test function to draw something on the root window
void draw_to_root(Display *dpy, Window root) {
    GC gc = XCreateGC(dpy, root, 0, NULL);
    XSetForeground(dpy, gc, WhitePixel(dpy, DefaultScreen(dpy)));
    XFillRectangle(dpy, root, gc, 50, 50, 200, 200);
    XFreeGC(dpy, gc);
    XFlush(dpy);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Failed to open X display.\n");
        return 1;
    }

    Window root = DefaultRootWindow(dpy);
    draw_to_root(dpy, root);

    XCloseDisplay(dpy);
    return 0;
}




