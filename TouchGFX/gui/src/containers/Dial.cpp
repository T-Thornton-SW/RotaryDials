#include <gui/containers/Dial.hpp>
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

Dial::Dial()
{

}

void Dial::initialize()
{
    DialBase::initialize();
	Dial::angle = 0;
	Dial::angle_old = 0;
	Dial::firstClick = true;
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
		touchgfx_printf("Corrected Coords %i %i\tAngle %1.2f\n", x,y,Dial::angle);
		updateAngle(x, y);//get the current angle of user
		handleClick(x,y);//perform analysis on user click.
		//update our field data at end
		if(Dial::isRotating==true)
		{
			Dial::x_old = x;
			Dial::y_old = y;
			Dial::angle_old = Dial::angle;
		}
	}
}

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial::handleClick(int16_t x,int16_t y)
{
	//if it's the first click
	if(Dial::firstClick==true)
	{
		Dial::isRotating=false;
		//check if we're in the goldilocks zone
		if(Dial::isGoldilocks(x,y))
		{
			Dial::isRotating=true;
		}
		Dial::firstClick=false;
	}
	else if(Dial::isRotating==true)
	{
		Dial::updateDistance(x,y);
	}
}

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial::updateDistance(int16_t x, int16_t y)
{
	float step1 = (float)sqrt(pow((double)(x-Dial::x_old),2)+pow((double)(y-Dial::y_old),2));
	float unitChange = ((step1)*(float)DIAL_CIRC_DEG/(float)DIAL_CIRCUM);
	//allows us to skip if they're moving it directly back and forth.
	if(Dial::angle!=Dial::angle_old)
	{
		//detect if we've gone cc or cw based on cross product
		if((x*Dial::y_old)-(y*Dial::x_old)>0)
		{
			//we're going counter clockwise
			Dial::value_ref-=unitChange;
			if(Dial::value_ref<MIN_VAL)
			{
				Dial::value_ref=MIN_VAL;
			}
		}
		else
		{
			//we're going clockwise
			Dial::value_ref+=unitChange;
			if(Dial::value_ref>MAX_VAL)
			{
				Dial::value_ref=MAX_VAL;
			}
		}
		Dial::dial_visual.setRotation(Dial::value_ref);
		Dial::dial_rep.setArc(0, Dial::value_ref);
		Dial::dial_visual.invalidate();
		Dial::dial_rep.invalidate();
		touchgfx_printf("Output value %f with val %f \n%f \n",Dial::value_ref,step1,CONVERTER_VAL);
	}
}


///<summary>
///Establish if click is in the "goldilocks"
///pixel region to enable dial control
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
///</summary>
///<returns>Bool value if within acceptable use region.</returns>
bool Dial::isGoldilocks(int16_t x, int16_t y)
{
	bool retval = false;
	//ensure that it's within the goldilocks zone to start moving the dial around!
	if((int16_t)sqrt(pow((double)x,2)+pow((double)y,2))<BUFFER_RADIUS)
	{
		retval = true;
	}
	return retval;
}




///<summary>
///Update the angle of the click position relative to the circle
///NOTE: REMEMBER THAT ATAN OPERATES IN RADIANS!!!
///</summary>
///<item><param name="x"> x coord of the click</param></item>
///<item><param name="y"> y coord of the click</param></item>
void Dial::updateAngle(int16_t x, int16_t y)
{
	//tan(0) = 0 which means that opposite is x axis
	//derive angle using tan = opp/adj
	switch(y>0)
	{
	case false:
		//dealing with areas above circle centre
		Dial::angle = -std::atan((double)(x)/(double)(y));
		break;
	default:
		//dealing with areas on circle centre
		if(y==0)
		{
			//don't update if x is also 0!
			if(x!=0)
			{
				Dial::angle = x>0 ? M_PI_2:-M_PI_2;//if x is right, angle = 90deg, otherwise angle=270deg
			}
		}
		//dealing with areas below circle centre
		else
		{
			Dial::angle = M_PI - std::atan((double)(x)/(double)(y));
		}
		break;
	}
	if(Dial::angle<0)
	{
		Dial::angle+=2*M_PI; //I can't be bothered with negative values they're such a bore. Force angles positive.
	}
}

///<summary>
///Reset the Dial for a fresh new click
///</summary>
void Dial::Release()
{
	Dial::firstClick = true;
	Dial::isRotating = false;
}
