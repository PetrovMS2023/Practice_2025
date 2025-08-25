
#include "prWindow.hpp"
#include <gtkmm.h>
#include <iostream>
#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

mainWindow::mainWindow(int n,int t)
{
Gtk::Box *tBox1 = new Gtk::Box();
Gtk::Box *tBox2 = new Gtk::Box();
Gtk::Box *tBox3 = new Gtk::Box();

button1.add_label("Сохранить");
button2.add_label("Добавить");
button4.add_label("Выбор цвета");
button5.add_label("Все сигналы");
label1.set_text("амплитуда, В");
label2.set_text("частота, Гц");
label3.set_text("начальный угол, °");
set_title("Практика");
set_border_width(10);
add(mainBox);
mainBox.pack_start(box1);
mainBox.pack_start(box2);
mainBox.pack_start(box3);

listBox1.set_selection_mode(Gtk::SelectionMode::SELECTION_SINGLE);
box1.pack_start(listBox1);
dArea.setT(t);
sWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC,Gtk::PolicyType::POLICY_AUTOMATIC);
sWindow.add(dArea);
sWindow.set_min_content_width(300);
box2.pack_start(sWindow);

grid1.attach(label1,0,0,1,1);
grid1.attach(label2,0,1,1,1);
grid1.attach(label3,0,2,1,1);
grid1.attach(entry1,1,0,1,1);
grid1.attach(entry2,1,1,1,1);
grid1.attach(entry3,1,2,1,1);
grid1.attach(button4,0,3,1,1);
grid1.attach(button5,1,6,1,1);
grid1.attach(button1,0,4,1,1);
grid1.attach(button2,1,4,1,1);
box3.pack_start(grid1);

button1.signal_clicked().connect([this](){on_button1_clicked();});
button2.signal_clicked().connect([this](){on_button2_clicked();});
button4.signal_clicked().connect([this](){on_button4_clicked();});
button5.signal_clicked().connect([this](){on_button5_clicked();});
listBox1.signal_row_activated().connect(sigc::mem_fun(*this,&mainWindow::listRowSelected));

for(int i=0;i<n;i++)
{
    SignalA *temp = new SignalA();
    sgList.push_back(*temp);
}
refresh_list();
}

mainWindow::~mainWindow()
{
}

// Save
void mainWindow::on_button1_clicked()
{
    std::cout << "b1";
    Gtk::Label *temp2 = static_cast<Gtk::Label*>(listBox1.get_selected_row()->get_children()[0]);
    SignalA* temp1 = findItem(temp2->get_text());
    temp1->Ampl = std::stof(entry1.get_text());
    temp1->Freq = std::stof(entry2.get_text());
    temp1->Angl = std::stof(entry3.get_text());
    temp1->color=(selected_color);
    refresh_list();
}

// Add
void mainWindow::on_button2_clicked()
{
    std::cout << "b2";
    SignalA *temp = new SignalA();
    temp->Ampl = std::stof(entry1.get_text());
    temp->Freq = std::stof(entry2.get_text());
    temp->Angl = std::stof(entry3.get_text());
    temp->color=(selected_color);
    sgList.push_back(*temp);
    refresh_list();
}

// Color
void mainWindow::on_button4_clicked()
{
    std::cout << "b4";
    Gtk::ColorChooserDialog dialog("choose",*this);
    Gdk::RGBA color;
    color.set_rgba(0,1,0,1);
    dialog.set_rgba(color);
    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
            selected_color = dialog.get_rgba();
            std::cout << "Selected color: R=" << selected_color.get_red()
                      << ", G=" << selected_color.get_green()
                      << ", B=" << selected_color.get_blue()
                      << ", A=" << selected_color.get_alpha() << std::endl;
        } else {
            std::cout << "Color selection cancelled." << std::endl;
        }
}

// all signals
void mainWindow::on_button5_clicked()
{
    this->dArea.setList(sgList);
    dArea.queue_draw();
    show_all_children();
}
// refresh list
void mainWindow::refresh_list()
{
    Gtk::Label *labelTemp;
    Gtk::ListBoxRow *temp;
    for (Gtk::Widget* element : listBox1.get_children ())
        listBox1.remove (*element);
    if (sgList.size() >= 0)for (int i = 0 ;i<sgList.size();i++)
    {
    temp = new Gtk::ListBoxRow();
    labelTemp = new Gtk::Label("signal " + std::to_string(sgList[i].id));
    temp->add(*labelTemp);
    listBox1.append(*temp);
    }
    show_all_children();
    dArea.queue_draw();

}

// fill graph and textbox
inline void mainWindow::listRowSelected(Gtk::ListBoxRow *lbr)
{
Gtk::Label *temp = static_cast<Gtk::Label*>(listBox1.get_selected_row()->get_children()[0]);
SignalA* temp1 = findItem(temp->get_text());
if (temp!=nullptr)
{
    entry1.set_text(to_string_with_precision(temp1->Ampl));
    entry2.set_text(to_string_with_precision(temp1->Freq,0));
    entry3.set_text(to_string_with_precision(temp1->Angl));
    show_all_children();
}
std::cout << "f1";
dArea.setParam(temp1->Ampl,temp1->Freq,temp1->Angl,temp1->color,false);
dArea.queue_draw();
show_all_children();
}

// SignalA by Id in list
SignalA* mainWindow::findItem(Glib::ustring str)
{
    if (sgList.size() >= 0)for (int i = 0 ;i<sgList.size();i++)
    {
        Glib::ustring stemp("signal " + std::to_string(sgList[i].id));
        if (str==stemp)
            return &sgList[i];
    }
    return nullptr;
}


bool mainWindow::onExposeEvent(GdkEventExpose* event)
{
 return true;
}
