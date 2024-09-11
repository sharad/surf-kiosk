/* #include <X11/Xlib.h> */
/* #include <gtk/gtk.h> */

/* // Minimal test function to draw something on the root window */
/* void draw_to_root(Display *dpy, Window root) { */
/*     GC gc = XCreateGC(dpy, root, 0, NULL); */
/*     XSetForeground(dpy, gc, WhitePixel(dpy, DefaultScreen(dpy))); */
/*     XFillRectangle(dpy, root, gc, 50, 50, 200, 200); */
/*     XFreeGC(dpy, gc); */
/*     XFlush(dpy); */
/* } */

/* int main(int argc, char *argv[]) { */
/*     gtk_init(&argc, &argv); */

/*     Display *dpy = XOpenDisplay(NULL); */
/*     if (!dpy) { */
/*         fprintf(stderr, "Failed to open X display.\n"); */
/*         return 1; */
/*     } */

/*     Window root = DefaultRootWindow(dpy); */
/*     draw_to_root(dpy, root); */

/*     XCloseDisplay(dpy); */
/*     return 0; */
/* } */




#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to draw a white rectangle on the root window
void draw_rectangle(Display *dpy, Window root) {
    // Get the screen's default graphics context and other attributes
    int screen = DefaultScreen(dpy);
    GC gc = XCreateGC(dpy, root, 0, NULL);

    if (!gc) {
        fprintf(stderr, "Failed to create graphics context.\n");
        return;
    }

    XSetForeground(dpy, gc, WhitePixel(dpy, screen));

    // Get root window dimensions
    XWindowAttributes root_attrs;
    XGetWindowAttributes(dpy, root, &root_attrs);

    // Draw a white rectangle in the center of the screen
    int rect_width = 200, rect_height = 150;
    int x = (root_attrs.width - rect_width) / 2;
    int y = (root_attrs.height - rect_height) / 2;
    XFillRectangle(dpy, root, gc, x, y, rect_width, rect_height);

    XFlush(dpy);
    XFreeGC(dpy, gc);
}

// Event loop to handle Expose events
void event_loop(Display *dpy, Window root) {
    XEvent ev;

    while (1) {
        XNextEvent(dpy, &ev);
        if (ev.type == Expose) {
            // Redraw the rectangle when an Expose event occurs
            draw_rectangle(dpy, root);
        }
    }
}

int main() {
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Unable to open display.\n");
        return 1;
    }

    int screen = DefaultScreen(dpy);
    Window root = RootWindow(dpy, screen);

    // Select for Expose events on the root window
    XSelectInput(dpy, root, ExposureMask);

    // Draw the initial white rectangle
    draw_rectangle(dpy, root);

    // Enter the event loop
    event_loop(dpy, root);

    XCloseDisplay(dpy);
    return 0;
}
