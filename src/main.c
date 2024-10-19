#include <gtk/gtk.h>
#include <stdlib.h>
#include <vte/vte.h>

void add_terminal_tab(GtkNotebook *notebook) {
    GtkWidget *terminal, *label;
    VteTerminal *vte;
    
    terminal = vte_terminal_new();
    vte = VTE_TERMINAL(terminal);

    GdkRGBA bg_color, fg_color;
    gdk_rgba_parse(&bg_color, "#1c1c1c");
    gdk_rgba_parse(&fg_color, "#f5f5f5");

    GdkRGBA pastel_palette[16];
    gdk_rgba_parse(&pastel_palette[0], "#e57373");
    gdk_rgba_parse(&pastel_palette[1], "#f06292");
    gdk_rgba_parse(&pastel_palette[2], "#ba68c8");
    gdk_rgba_parse(&pastel_palette[3], "#9575cd");
    gdk_rgba_parse(&pastel_palette[4], "#7986cb");
    gdk_rgba_parse(&pastel_palette[5], "#4fc3f7");
    gdk_rgba_parse(&pastel_palette[6], "#4db6ac");
    gdk_rgba_parse(&pastel_palette[7], "#81c784");
    gdk_rgba_parse(&pastel_palette[8], "#aed581");
    gdk_rgba_parse(&pastel_palette[9], "#dce775");
    gdk_rgba_parse(&pastel_palette[10], "#fff176");
    gdk_rgba_parse(&pastel_palette[11], "#ffd54f");
    gdk_rgba_parse(&pastel_palette[12], "#ffb74d");
    gdk_rgba_parse(&pastel_palette[13], "#ff8a65");
    gdk_rgba_parse(&pastel_palette[14], "#a1887f");
    gdk_rgba_parse(&pastel_palette[15], "#90a4ae");

    vte_terminal_set_colors(vte, &fg_color, &bg_color, pastel_palette, 16);

    char *shell[] = {g_strdup(g_getenv("SHELL")), NULL};
    vte_terminal_spawn_async(vte, VTE_PTY_DEFAULT, NULL, shell, NULL, 0, NULL, NULL, NULL, -1, NULL, NULL, NULL);

    label = gtk_label_new("Terminal");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), terminal, label);
    gtk_widget_show_all(terminal);
}

void on_add_tab(GtkWidget *widget, GtkNotebook *notebook) {
    add_terminal_tab(notebook);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *notebook, *menubar, *file_menu, *add_tab_item, *vbox, *menu_item;

    gtk_init(&argc, &argv);
    
    const char *home = getenv("HOME");
    if (home == NULL) {
        g_printerr("HOME variable is not set.\n");
        return 1;
    }

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nox Terminal");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    char *icon_path = g_build_filename(home, ".nox/icon.png", NULL);
    GError *error = NULL;
    if (!gtk_window_set_icon_from_file(GTK_WINDOW(window), icon_path, &error)) {
        g_printerr("Error setting icon: %s\n", error->message);
        g_clear_error(&error);
    }
    g_free(icon_path);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    menubar = gtk_menu_bar_new();
    file_menu = gtk_menu_new();
    menu_item = gtk_menu_item_new_with_label("File");
    add_tab_item = gtk_menu_item_new_with_label("Exit");
    
    g_signal_connect(add_tab_item, "activate", G_CALLBACK(on_add_tab), notebook);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), add_tab_item);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_item);
    
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

    add_terminal_tab(GTK_NOTEBOOK(notebook));

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}