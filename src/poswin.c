/*      $Id$

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2, or (at your option)
        any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., Inc., 51 Franklin Street, Fifth Floor, Boston,
        MA 02110-1301, USA.


        xfwm4    - (c) 2002-2011 Olivier Fourdan
          based on a patch from Joshua Blanton <jblanton@irg.cs.ohiou.edu>
        latte-wm - (c) 2017 Vitaliy Kopylov
	http://latte-desktop.org/

 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>

#include "client.h"
#include "frame.h"
#include "poswin.h"

static void poswin_widget_class_init (PoswinWidgetClass *klass);

static GType
poswin_widget_get_type (void)
{
    static GType type = G_TYPE_INVALID;

    if (G_UNLIKELY (type == G_TYPE_INVALID))
    {
        static const GTypeInfo info =
        {
            sizeof (PoswinWidgetClass),
            NULL,
            NULL,
            (GClassInitFunc) poswin_widget_class_init,
            NULL,
            NULL,
            sizeof (Poswin),
            0,
            NULL,
            NULL,
        };

        type = g_type_register_static (GTK_TYPE_WINDOW, "Xfwm4PoswinWidget", &info, 0);
    }

    return type;
}

static void
poswin_widget_class_init (PoswinWidgetClass *klass)
{
    /* void */
}

Poswin *
poswinCreate (GdkScreen *gscr)
{
    Poswin *poswin;
    GtkWidget *frame;

    poswin = g_object_new (poswin_widget_get_type(), "type", GTK_WINDOW_POPUP, NULL);

    gtk_window_set_screen (GTK_WINDOW (poswin), gscr);
    gtk_container_set_border_width (GTK_CONTAINER (poswin), 0);
    gtk_window_set_resizable (GTK_WINDOW (poswin), TRUE);

    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_OUT);
    gtk_container_set_border_width (GTK_CONTAINER (frame), 0);
    gtk_container_add (GTK_CONTAINER (poswin), frame);

    poswin->label = gtk_label_new ("");
    gtk_misc_set_alignment (GTK_MISC (poswin->label), 0.5, 0.5);
    gtk_misc_set_padding (GTK_MISC (poswin->label), 3, 3);
    gtk_widget_show (poswin->label);
    gtk_container_add(GTK_CONTAINER(frame), poswin->label);
    gtk_widget_show_all (frame);

    return poswin;
}

void
poswinSetPosition (Poswin * poswin, Client *c)
{
    /* 32 is enough for (NNNNNxNNNNN) @ (-NNNNN,-NNNNN) */
    gchar label[32];
    gint x, y, px, py, pw, ph;
    gint wsize, hsize;

    g_return_if_fail (poswin != NULL);
    g_return_if_fail (c != NULL);
    g_return_if_fail (c->size->width_inc != 0);
    g_return_if_fail (c->size->height_inc != 0);

    x = frameX (c);
    y = frameY (c);

    wsize = (c->width - c->size->base_width) / c->size->width_inc;
    hsize = (c->height - c->size->base_height) / c->size->height_inc;

    if (wsize < 0)
    {
        wsize = 0;
    }
    if (hsize < 0)
    {
        hsize = 0;
    }

#ifdef SHOW_POSITION
    g_snprintf (label, 32, "(%dx%d) @ (%i,%i)", wsize, hsize, x, y);
#else
    g_snprintf (label, 32, "(%dx%d)", wsize, hsize);
#endif
    gtk_label_set_text (GTK_LABEL (poswin->label), label);
    gtk_widget_queue_draw (GTK_WIDGET(poswin));
    gtk_window_get_size (GTK_WINDOW (poswin), &pw, &ph);
    px = x + (frameWidth (c) - pw) / 2;
    py = y + (frameHeight (c) - ph) / 2;
    gtk_window_move (GTK_WINDOW (poswin), px, py);
}

void
poswinDestroy (Poswin * poswin)
{
    g_return_if_fail (poswin != NULL);

    gtk_widget_destroy (GTK_WIDGET(poswin));
}

void
poswinShow (Poswin * poswin)
{
    g_return_if_fail (poswin != NULL);

    gtk_widget_show (GTK_WIDGET(poswin));
}

void
poswinHide(Poswin * poswin)
{
    g_return_if_fail (poswin != NULL);

    gtk_widget_hide (GTK_WIDGET(poswin));
}
