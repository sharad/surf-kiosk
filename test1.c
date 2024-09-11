#include <X11/Xlib.h>

int main() {
    // Open display
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "Failed to open X display.\n");
        return 1;
    }

    // Get the root window for the default screen
    Window root = DefaultRootWindow(dpy);

    // Create a graphics context
    GC gc = XCreateGC(dpy, root, 0, NULL);
    if (!gc) {
        fprintf(stderr, "Failed to create graphics context.\n");
        XCloseDisplay(dpy);
        return 1;
    }

    // Set drawing color to white
    XSetForeground(dpy, gc, WhitePixel(dpy, DefaultScreen(dpy)));

    // Draw a filled rectangle on the root window
    XFillRectangle(dpy, root, gc, 50, 50, 200, 200);

    // Clean up
    XFreeGC(dpy, gc);
    XFlush(dpy);  // Ensure drawing commands are sent to X server

    // Wait for a few seconds before closing
    sleep(5);

    XCloseDisplay(dpy);
    return 0;
}
