#ifndef DESKTOP_ENTRY_FILE_CREATOR_APP_H
#define DESKTOP_ENTRY_FILE_CREATOR_APP_H

#include <glibmm/refptr.h>
#include <gtkmm/application.h>

namespace App {
    extern Glib::RefPtr<Gtk::Application> app;
}

#endif
