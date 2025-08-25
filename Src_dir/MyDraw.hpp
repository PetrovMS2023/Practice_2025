#pragma once
#include <gtkmm.h>
#include <vector>
#include "Data.hpp"
#ifndef GTKMM_EXAMPLE_MYAREA_H
#define GTKMM_EXAMPLE_MYAREA_H

#include <gtkmm/drawingarea.h>

class MyArea : public Gtk::DrawingArea
{
public:
  std::vector<SignalA> sgListD;
  MyArea();
  virtual ~MyArea();
  void setParam(double a, double b, double c,Gdk::RGBA color,bool mod);
  void setList(std::vector<SignalA> listS);
  gfloat f(gfloat x);
  void setT(double t);
  protected:
  double scale;
  virtual bool on_scroll(GdkEventScroll* event);
  //Перекрытие стандартного обработчика сигналов:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
private:
  double a,b,c,t;
  bool allL;
  Gdk::RGBA selected_color_area;
};

#endif // GTKMM_EXAMPLE_MYAREA_H
