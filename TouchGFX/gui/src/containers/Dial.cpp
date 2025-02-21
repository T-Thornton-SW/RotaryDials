#include <gui/containers/Dial.hpp>
#include <touchgfx/Utils.hpp>
#include <math.h>
#define DIAL_RADIUS 	64
#define DIAL_BUFFER		10
#define DIAL_CENTRE 	128
#define WINDOW_PIXELS	256
#define MAX_VAL			360
#define MIN_VAL			0

Dial::Dial(){ }

void Dial::initialize()
{
    DialBase::initialize();
	Dial::data.angle_max = MAX_VAL;
	Dial::data.angle_min = MIN_VAL;
	Dial::data.dial_radius = DIAL_RADIUS;
	Dial::data.dial_buffer = DIAL_BUFFER;
}

///<summary>
///Perform click action on dial
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial::setXYCoord(int16_t x, int16_t y)
{
	if(x>=0&&y>=0&&x<WINDOW_PIXELS&&y<WINDOW_PIXELS)
	{
		x-=DIAL_CENTRE;	y-=DIAL_CENTRE;
		touchgfx_printf("Corrected Coords %i %i\tAngle %1.2f\n", x,y,Dial::data.angle);
		handleClick(x,y);//perform analysis on user click.
	}
}

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial::handleClick(int16_t x,int16_t y)
{
	if(Dial::isVisible())
	{
		Dial_Generic::handleClick(&(Dial::data),x,y);
		if(Dial::data.is_rotating==true)
		{
			Dial::dial_visual.setRotation(Dial::data.value_ref);
			Dial::dial_rep.setArc(0, Dial::data.value_ref);
			Dial::dial_visual.invalidate();
			Dial::dial_rep.invalidate();
		}
	}
}

///<summary>
///Reset the Dial for a fresh new click
///</summary>
void Dial::Release()
{
	Dial::data.first_click = true;
	Dial::data.is_rotating = false;
}
