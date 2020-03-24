#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (defined(_WIN32) || defined(_WIN64))
#include "lib/windows.h"
#else
#include "lib/linux.h"
#endif

#include "lib/razno.h"

static void p(GtkApplication *app, gpointer user_data) {
    g_print("pritisnuto %d\n",
            gtk_revealer_get_reveal_child(GTK_REVEALER((GtkWidget *)user_data)));
    gtk_revealer_set_reveal_child(GTK_REVEALER((GtkWidget *)user_data), TRUE);
    g_print("pritisnuto %d\n",
            gtk_revealer_get_reveal_child(GTK_REVEALER((GtkWidget *)user_data)));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "oof");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    GtkWidget *list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    window = gtk_application_window_new(app);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
    // gtk_window_set_title(GTK_WINDOW(window), "aaaaaaaaaa");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    gtk_container_add(GTK_CONTAINER(window), list);

    struct lista *l = spisakfoldera("." KC "db");

    if (!l) {
        g_print("Greska\n");
        gtk_main_quit();
    }
    struct clan *c = l->prvi;

    GtkWidget *a = gtk_revealer_new();
    gtk_widget_set_valign(a, GTK_ALIGN_START);
    gtk_revealer_set_transition_type(GTK_REVEALER(a),
                                     GTK_REVEALER_TRANSITION_TYPE_SLIDE_UP);
    gtk_revealer_set_transition_duration(GTK_REVEALER(a), 500);
    gtk_container_add(GTK_CONTAINER(a), gtk_label_new("oof"));
    gtk_box_pack_start(GTK_BOX(list), a, 1, 1, 0);

    while (c) {
        g_print("%x\n", c);
        // g_print("%s\n", c->ime);
        GtkWidget *dugme = gtk_button_new_with_label(c->ime);
        g_signal_connect(dugme, "clicked", G_CALLBACK(p), a);
        gtk_box_pack_start(GTK_BOX(list), dugme, 1, 1, 0);
        c = c->sledeci;
    }
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;

    int status;
    app = gtk_application_new("com.daredon.todo", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}