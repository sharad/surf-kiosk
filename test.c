#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to clear the root window and draw a white rectangle
void draw_rectangle(Display *dpy, Window root) {
    // Get the screen's default graphics context and other attributes
    int screen = DefaultScreen(dpy);
    GC gc = XCreateGC(dpy, root, 0, NULL);

    if (!gc) {
        fprintf(stderr, "Failed to create graphics context.\n");
        return;
    }

    // Set the background color to black (or any other desired color)
    XSetWindowBackground(dpy, root, BlackPixel(dpy, screen));

    // Clear the window to apply the new background color
    XClearWindow(dpy, root);

    // Create a pixmap for the background
    XWindowAttributes root_attrs;
    XGetWindowAttributes(dpy, root, &root_attrs);
    Pixmap bg_pixmap = XCreatePixmap(dpy, root, root_attrs.width, root_attrs.height, root_attrs.depth);

    // Fill the background pixmap with the black color
    XFillRectangle(dpy, bg_pixmap, gc, 0, 0, root_attrs.width, root_attrs.height);

    // Draw a white rectangle in the center of the pixmap
    XSetForeground(dpy, gc, WhitePixel(dpy, screen));
    int rect_width = 200, rect_height = 150;
    int x = (root_attrs.width - rect_width) / 2;
    int y = (root_attrs.height - rect_height) / 2;
    XFillRectangle(dpy, bg_pixmap, gc, x, y, rect_width, rect_height);

    // Set the pixmap as the background of the root window
    XSetWindowBackgroundPixmap(dpy, root, bg_pixmap);

    // Clear the window again to display the new background pixmap
    XClearWindow(dpy, root);

    // Flush the display to apply changes
    XFlush(dpy);

    // Free resources
    XFreePixmap(dpy, bg_pixmap);
    XFreeGC(dpy, gc);
}

// Periodic redraw function
void periodic_redraw(Display *dpy, Window root) {
    while (1) {
        draw_rectangle(dpy, root);
        sleep(5);  // Redraw every 5 seconds to keep it persistent
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

    // Draw the initial white rectangle
    draw_rectangle(dpy, root);

    // Periodically redraw the rectangle to maintain its visibility
    periodic_redraw(dpy, root);

    XCloseDisplay(dpy);
    return 0;
}

