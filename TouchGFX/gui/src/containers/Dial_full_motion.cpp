#include <gui/containers/Dial_full_motion.hpp>
#include <touchgfx/Utils.hpp>
#include <math.h>
#define DIAL_RADIUS 	64
#define DIAL_BUFFER		10
#define DIAL_CENTRE 	128
#define WINDOW_PIXELS	256
#define BUFFER_RADIUS 	(DIAL_RADIUS+DIAL_BUFFER)
#define DIAL_CIRCUM		(2*M_PI*DIAL_RADIUS)
#define DIAL_CIRC_DEG	360
#define CONVERTER_VAL	DIAL_CIRC_DEG/DIAL_CIRCUM
#define MAX_VAL			360
#define MIN_VAL			0

Dial_full_motion::Dial_full_motion(){ }

void Dial_full_motion::initialize()
{
    Dial_full_motionBase::initialize();

	Dial_full_motion::data.angle_max = MAX_VAL;
	Dial_full_motion::data.angle_min = -MAX_VAL;
	Dial_full_motion::data.dial_radius = DIAL_RADIUS;
	Dial_full_motion::data.dial_buffer = DIAL_BUFFER;
	Dial_full_motion::data.wrap_around = true;

}

///<summary>
///Perform click action on dial
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial_full_motion::setXYCoord(int16_t x, int16_t y)
{
	if(x>=0&&y>=0&&x<WINDOW_PIXELS&&y<WINDOW_PIXELS)
	{
		x-=DIAL_CENTRE;	y-=DIAL_CENTRE;

		handleClick(x,y);//perform analysis on user click.
		touchgfx_printf("Corrected Coords %i %i\tAngleB %1.2f\n", x,y,Dial_full_motion::data.angle);
		//update our field data at end
		if(Dial_full_motion::isRotating==true)
		{
			Dial_full_motion::x_old = x;
			Dial_full_motion::y_old = y;
			Dial_full_motion::angle_old = Dial_full_motion::angle;
		}
	}
}

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial_full_motion::handleClick(int16_t x,int16_t y)
{
	if(Dial_full_motion::isVisible())
	{
		Dial_Generic::handleClick(&(Dial_full_motion::data),x,y);
		if(Dial_full_motion::data.is_rotating==true)
		{

			Dial_full_motion::dial_visual.setRotation(Dial_full_motion::data.value_ref);
			Dial_full_motion::dial_rep.setArc(0, Dial_full_motion::data.value_ref);
			Dial_full_motion::dial_visual.invalidate();
			Dial_full_motion::dial_rep.invalidate();
		}

	}
}

///<summary>
///Reset the Dial for a fresh new click
///</summary>
void Dial_full_motion::Release()
{
	Dial_full_motion::data.first_click = true;
	Dial_full_motion::data.is_rotating = false;
}
