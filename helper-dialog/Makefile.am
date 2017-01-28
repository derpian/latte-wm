# $Id$

AM_CPPFLAGS =								\
	$(GTK_CFLAGS) 							\
	$(LIBX11_CFLAGS)						\
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\"

helper_dialogdir = $(HELPER_PATH_PREFIX)/xfce4/xfwm4

helper_dialog_PROGRAMS =						\
	helper-dialog

helper_dialog_SOURCES =							\
	helper-dialog.c

helper_dialog_CFLAGS =							\
	$(LIBX11_CFLAGS)						\
	$(GTK_CFLAGS)

helper_dialog_LDADD =							\
	$(LIBX11_LIBS)							\
	$(LIBX11_LDFLAGS)						\
	$(GTK_LIBS)

