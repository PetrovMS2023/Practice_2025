#include "MyDraw.hpp"
#include <gtkmm.h>
#include <cairomm/context.h>
#include <sstream>
#include <iostream>
#define PI 3.14159265

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}
// size, t, func param
MyArea::MyArea()
{
set_size_request(600,300);
a=1;
b=1;
c=30;
t=4;
scale = 2.0;
allL=false;
add_events(Gdk::SCROLL_MASK);
signal_scroll_event().connect(sigc::mem_fun(*this,&MyArea::on_scroll));
}

MyArea::~MyArea()
{
this->selected_color_area.set_rgba(1, 0.2, 0.2, 0.6);
}

// sin wave
gfloat MyArea::f (gfloat x)
{
    return a * sin ((2*b*PI)*x+c*PI/180);
}

// Func Param
void MyArea::setParam(double a, double b, double c,Gdk::RGBA color,bool mod)
{
    this->a=a;
    this->b=b;
    this->c=c;
    this->selected_color_area=color;
    allL=mod;
}

void MyArea::setList(std::vector<SignalA> listS)
{
    this->sgListD=listS;
    allL=true;
}
// set time
void MyArea::setT(double t)
{
    this->t=t;
}

bool MyArea::on_scroll(GdkEventScroll* event)
{
    if (event->direction == GDK_SCROLL_UP)
    {
    scale*=1.1;
    }
    else
    if (event->direction == GDK_SCROLL_DOWN)
    {
    scale/=1.1;
    }
    if (scale < 0.5) scale = 0.5;
    if (scale > 100) scale = 100;
    std:: cout << scale << std::endl;
    queue_draw();
return true;
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();
  const int intX = 10,intY = 6,pX=t,pY=2;

  // масштабирование до единичного квадрата (значения ширины и высоты рабочей области находятся в диапазоне от 0 до 1)
  cr->translate(0,height/2);
  cr->scale(width/pX, height/pY);
  cr->set_line_width(0.01);

  // Grid stroke
  cr->set_source_rgba(0, 0, 0, 1);
  cr->move_to(0, -1);
  cr->line_to(0,1);
  cr->stroke();
  cr->move_to(0, 0);
  cr->line_to(t, 0);
  cr->stroke();
  cr->select_font_face("Courier",Cairo::FONT_SLANT_NORMAL,Cairo::FONT_WEIGHT_NORMAL);
  cr->set_font_size(0.1);

  // X axis
  for (int i = 1; i<intX; i++ )
  {
    cr->move_to(i*((float)pX/intX),0);
    cr->line_to(i*((float)pX/intX),(float)pY/20);
    cr->move_to(i*((float)pX/intX),1);
    cr->show_text(to_string_with_precision(i*((float)pX/intX)));

  }
  cr->stroke();

  // Y axis
  for (int i = 0; i<intY; i++ )
  {
    cr->move_to(0,pY/2-i*((float)pY/intY));
    cr->line_to((float)pX/40,pY/2-i*((float)pY/intY));
    cr->move_to(pX/40+0.02,(pY/2-i*((float)pY/intY))-0.02);
    cr->show_text(to_string_with_precision(-scale*(pY/2-i*((float)pY/intY))));
  }
  cr->stroke();
  if ((sgListD.size() > 0)&&allL)
  {for (int j = 0 ;j<sgListD.size();j++)
    {
    this->setParam(sgListD[j].Ampl,sgListD[j].Freq,sgListD[j].Angl,sgListD[j].color,true);
    allL=true;
    cr->set_source_rgba(this->selected_color_area.get_red(),this->selected_color_area.get_green(),this->selected_color_area.get_blue(),this->selected_color_area.get_alpha());
    cr->move_to(0, f(0));
    // function
    for (double i = 0; i <= t; i += 0.0005)
        {
        cr->line_to(i,-f(i)/scale);
        cr->move_to(i,-f(i)/scale);
        }
    cr->stroke();
    }
    if (!allL) this->sgListD.clear();
    }
  else
  {
  cr->set_source_rgba(this->selected_color_area.get_red(),this->selected_color_area.get_green(),this->selected_color_area.get_blue(),this->selected_color_area.get_alpha());
  cr->move_to(0, f(0));

  // function
  for (double i = 0; i <= t; i += 0.0005)
        {
        cr->line_to(i,-f(i)/scale);
        cr->move_to(i,-f(i)/scale);
        }
  cr->stroke();
  }
  return true;

}
