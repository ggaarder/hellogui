#include <stdio.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define WINDOW_WIDTH    640               // proposed width of main window
#define WINDOW_HEIGHT   480               // proposed height of main window
#define WINDOW_NAME     "hellogui"   // name of main window

GtkWidget *window;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
                              gpointer user_data)
{
    int width, height;
    GtkWidget *win = gtk_widget_get_toplevel(widget);
    gtk_window_get_size(GTK_WINDOW(win), &width, &height);

    cairo_set_line_width (cr, 6);
    cairo_rectangle (cr, 12, 12, width - 26, height - 26);

    cairo_select_font_face(cr, "Purisa", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 24);
    cairo_move_to(cr, width / 2, height / 2);
    char s[16];
    sprintf(s, "Hello GUI!");
    cairo_show_text(cr, s);

    cairo_stroke (cr);

    return FALSE;
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
                        gpointer user_data)
{
  printf("application_clicked called, button %d, x = %d, y= %d\n", event->button, (int)event->x, (int)event->y);
    gtk_widget_queue_draw(widget);
    return TRUE;
}

static void on_quit_event()
{
    gtk_main_quit();
}

int main (int argc, char *argv[])
{
    GtkWidget *darea;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);
    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

    g_signal_connect(G_OBJECT(darea), "draw",  G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_quit_event), NULL);
    g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(clicked),
                     NULL);

    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(window), WINDOW_NAME);

    // init here

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
