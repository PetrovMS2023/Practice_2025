#include <gtk/gtk.h>
#include <math.h>
#include <gtkmm.h>
#include "prWindow.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create();
    if(argc > 1)
    {
        std::cout << argv[1] << std::endl;
        std::cout << argv[2] << std::endl;
        mainWindow mainWindow1(std::stoi(argv[1]),std::stoi(argv[2]));
        return app->run(mainWindow1);
    }
    else
    {
        mainWindow mainWindow1;
        return app->run(mainWindow1);
    }
}
