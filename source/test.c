#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <assert.h>

int charge_image_bouton(GtkWidget *pButton);

void change_bouton(GtkWidget *bouton, gpointer data);

int charge_image_bouton(GtkWidget *pButton){
    assert(pButton!=NULL);
    GdkPixbuf *pb_temp, *pb;
    GtkWidget *image;
    printf("1\n");
    // 1. Charger l’image et la redimensionner (100*100 pixels)
    pb_temp = gdk_pixbuf_new_from_file("images/1.bmp", NULL);
    if(pb_temp == NULL)
    {
        printf(" Erreur de chargement de l’image qu'on tente d'afficher bordel de merde!\n");
        return -1;
    }
    pb = gdk_pixbuf_scale_simple(pb_temp, 20, 20, GDK_INTERP_NEAREST);
    printf("2\n");

    // 2. Placer l’image
    image = gtk_image_new_from_pixbuf(pb);
    printf("3\n");

    gtk_button_set_image(GTK_BUTTON(pButton), image);
    printf("4\n");
    return 0; 
} // fin charge_image_bouton()

void change_bouton(GtkWidget *bouton, gpointer data){
    charge_image_bouton(bouton);
}

int main(int argc, char **argv){

    gtk_init(&argc, &argv);

    GtkWidget *pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *pVBox = gtk_vbox_new(TRUE, 0);
    GtkWidget *pbutton = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(pVBox), pbutton, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pFenetre), pVBox);

    g_signal_connect(G_OBJECT(pbutton), "clicked", G_CALLBACK(change_bouton), NULL);

    gtk_widget_show_all(pFenetre);

    gtk_main();


    return EXIT_SUCCESS;
}