/**
 * clang++-7 -Wall -pedantic -std=c++17 src/main.cpp -o desktop-entry-file-creator `pkg-config gtkmm-3.0 --cflags --libs`
 */
#include <iostream>
#include <gtkmm.h>

#include "app/App.h"

static void onAssistantApply() {
    std::cout << "Assistant::apply\n";
}

static void onAssistantCancel() {
    std::cout << "Assistant::cancel\n";

    App::app->quit();
}

static void onAssistantClose() {
    std::cout << "Assistant::close\n";
}

static void onAssistantEscape() {
    std::cout << "Assistant::escape\n";
}

static void onAssistantPrepare() {
    std::cout << "Assistant::prepare\n";
}

int main(int argc, char *argv[])
{
    const Glib::ustring app_id = "com.github.hbobenicio.modern_cpp_examples.gtkmm_examples.desktop_entry_file_creator";
    const std::string assistantResourcePath = "app/assistant/Assistant.glade";

    App::app = Gtk::Application::create(argc, argv, app_id);

    auto builder = Gtk::Builder::create();
    try {
        builder->add_from_file(assistantResourcePath);

    } catch(const Glib::FileError& err) {
        std::cerr << "error: Glib::FileError: " << err.what() << '\n';
        return EXIT_FAILURE;

    } catch(const Glib::MarkupError& err) {
        std::cerr << "error: MarkupError: " << err.what() << '\n';
        return EXIT_FAILURE;

    } catch(const Gtk::BuilderError& err) {
        std::cerr << "error: BuilderError: " << err.what() << '\n';
        return EXIT_FAILURE;
    }

    // Get the Assistant widget
    Gtk::Assistant* assistant = nullptr;
    builder->get_widget("Assistant", assistant);
    if (!assistant) {
        std::cerr << "error: widget Assistant not found in " << assistantResourcePath << "\n";
        return EXIT_FAILURE;
    }

    assistant->signal_apply().connect(sigc::ptr_fun(onAssistantApply));
    assistant->signal_cancel().connect(sigc::ptr_fun(onAssistantCancel));
    assistant->signal_close().connect(sigc::ptr_fun(onAssistantClose));
    // assistant->signal_escape().connect(sigc::ptr_fun(onAssistantEscape));
    // assistant->signal_prepare().connect(sigc::ptr_fun(onAssistantPrepare));

    return App::app->run(*assistant);
}
