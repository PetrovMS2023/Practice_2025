
static int counter = 0;

struct SignalA
{
int id;
float Ampl;
float Freq;
float Angl;
Gdk::RGBA color;
SignalA()
{
Ampl = 1;
Freq = 1;
Angl = 30;
this->color.set_rgba(1, 0.2, 0.2, 0.6);
id = counter;
counter++;
};
};
