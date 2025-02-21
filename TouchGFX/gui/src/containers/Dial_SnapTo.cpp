#include <gui/containers/Dial_SnapTo.hpp>
#include <touchgfx/Utils.hpp>
#include <math.h>
#define DIAL_RADIUS 	64
#define DIAL_CENTRE 	128
#define WINDOW_PIXELS	256
#define BUFFER_RADIUS 	(DIAL_RADIUS+10)
#define DIAL_CIRCUM		(2*M_PI*DIAL_RADIUS)
#define DIAL_CIRC_DEG	360
#define CONVERTER_VAL	DIAL_CIRC_DEG/DIAL_CIRCUM
#define MAX_VAL			360
#define MIN_VAL			0
#define DOMAIN_STRECH	60
#define CENTRE_ZERO		0
#define CENTRE_ONE		90
#define CENTRE_TWO		180
#define CENTRE_THREE	270

const float dial_sector_max[DIAL_MAX_VAL] = {DOMAIN_STRECH+CENTRE_ZERO,DOMAIN_STRECH+CENTRE_ONE,DOMAIN_STRECH+CENTRE_TWO,DOMAIN_STRECH+CENTRE_THREE};
//const float dial_sector_max[DIAL_MAX_VAL]= {CENTRE_ZERO-DOMAIN_STRECH,CENTRE_ONE-DOMAIN_STRECH,CENTRE_TWO-DOMAIN_STRECH,CENTRE_THREE-DOMAIN_STRECH};
const float dial_sector_centre[DIAL_MAX_VAL]={CENTRE_ZERO,CENTRE_ONE,CENTRE_TWO,CENTRE_THREE};

Dial_SnapTo::Dial_SnapTo()
{

}

void Dial_SnapTo::initialize()
{
    Dial_SnapToBase::initialize();
	/*Dial_SnapTo::data.angle = 0;
	Dial_SnapTo::data.angle_old = 0;
	Dial_SnapTo::data.firstClick = true;
	Dial_SnapTo::current_dial_value = DIAL_MIN_VAL;
	Dial_SnapTo::DialList = {Dial_SnapTo::zero_dialpos,Dial_SnapTo::one_dialpos,Dial_SnapTo::two_dialpos,Dial_SnapTo::three_dialpos};*/
}

///<summary>
///Perform click action on dial
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial_SnapTo::setXYCoord(int16_t x, int16_t y)
{
	/*if(x>=0&&y>=0&&x<WINDOW_PIXELS&&y<WINDOW_PIXELS)
	{
		x-=DIAL_CENTRE;	y-=DIAL_CENTRE;
		touchgfx_printf("Corrected Coords %i %i\tAngleB %1.2f\n", x,y,Dial_SnapTo::angle);
		updateAngle(x, y);//get the current angle of user
		handleClick(x,y);//perform analysis on user click.
		//update our field data at end
		if(Dial_SnapTo::isRotating==true)
		{
			Dial_SnapTo::x_old = x;
			Dial_SnapTo::y_old = y;
			Dial_SnapTo::angle_old = Dial_SnapTo::angle;
		}
	}*/
}

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial_SnapTo::handleClick(int16_t x,int16_t y)
{
	/*if(Dial_SnapTo::isVisible())
	{
		//if it's the first click
		if(Dial_SnapTo::firstClick==true)
		{
			Dial_SnapTo::isRotating=false;
			//check if we're in the goldilocks zone
			if(Dial_SnapTo::isGoldilocks(x,y))
			{
				Dial_SnapTo::isRotating=true;
			}
			Dial_SnapTo::firstClick=false;
		}
		else if(Dial_SnapTo::isRotating==true)
		{
			Dial_SnapTo::updateDistance(x,y);
		}
	}*/
}
///<summary>
///Reset the Dial for a fresh new click
///</summary>
void Dial_SnapTo::Release()
{
	//Dial_SnapTo::firstClick = true;
	//Dial_SnapTo::isRotating = false;
	//Dial_SnapTo::dial_visual.setRotation(dial_sector_centre[Dial_SnapTo::current_dial_value%DIAL_MAX_VALUE]);
	Dial_SnapTo::dial_visual.invalidate();
	//Dial_SnapTo::angle_old = dial_sector_centre[Dial_SnapTo::current_dial_value%DIAL_MAX_VALUE];//reset the dial to the nearest sector centre
}


//boundaries:: each dial position extends 60 degrees out from it's own "centre position".
//when a dial is rotated towards the end points of it's domain it will rotate up to 5 degrees in that direction.
//meaning we calculate which sector it's currently locked to, and then divide current angle off from centre point by 12
//if it moves out of a domain, we set that domain's number colour back to black, update the new domain's colour to orange, and update
//domain number.

