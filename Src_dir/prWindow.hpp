#pragma once
#include <gtkmm.h>
#include <vector>
#include "MyDraw.hpp"


class mainWindow : public Gtk::Window
{
public:
mainWindow(int n = 1,int t = 4);
virtual ~mainWindow();

protected:
std::vector<SignalA> sgList;
void on_button1_clicked();
void on_button2_clicked();
void on_button4_clicked();
void on_button5_clicked();
void refresh_list();
void listRowSelected(Gtk::ListBoxRow *lbr);
SignalA* findItem(Glib::ustring str);
Gtk::Button button1, button2,button3,button4,button5;
Gtk::Box box1,box2,box3,mainBox;
Gtk::ScrolledWindow sWindow;
Gtk::Label label1,label2,label3;
Gtk::ListBox listBox1;
Gtk::Entry entry1,entry2,entry3;
Gtk::Grid grid1;
MyArea dArea;
bool onExposeEvent(GdkEventExpose* event);
Gdk::RGBA selected_color;
};

