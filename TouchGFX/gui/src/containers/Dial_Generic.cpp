#include <gui/containers/Dial_Generic.hpp>

#define CIRCLE_DEGS 360
#define DIAL_CIRCUM		(2*M_PI)
#define DIAL_CIRC_DEG	360

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial_Generic::handleClick(DialData* Dial, int16_t x,int16_t y)
{
		//quickly grab the x y coord angle
		Dial_Generic::updateAngle(Dial,x,y);
		if(Dial->first_click==true)
		{
			//if it's the first click
			Dial->is_rotating=false;
			//check if we're in the goldilocks zone
			if(Dial_Generic::isGoldilocks(Dial,x,y))
			{
				Dial->is_rotating=true;
			}
			Dial->first_click=false;
		}
		else if(Dial->is_rotating==true)
		{
			Dial_Generic::updateDistance(Dial,x,y);
			Dial->x_old = x;
			Dial->y_old = y;
			Dial->angle_old = Dial->angle;
		}
		//todo: add snap to circle class
		if(Dial->value_ref<0)
		{
			Dial->value_ref += CIRCLE_DEGS;
		}
		if(Dial->value_ref>CIRCLE_DEGS)
		{
			Dial->value_ref -= CIRCLE_DEGS;
		}
}

///<summary>
///Perform logic of user click
///</summary>
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
void Dial_Generic::updateDistance(DialData* Dial, int16_t x, int16_t y)
{
	float step1 = (float)sqrt(pow((double)(x-Dial->x_old),2)+pow((double)(y-Dial->y_old),2));
	float unitChange = ((step1)*(float)DIAL_CIRC_DEG/(float)(DIAL_CIRCUM*Dial->dial_radius));
	//allows us to skip if they're moving it directly back and forth.
	if(Dial->angle!=Dial->angle_old)
	{
		//detect if we've gone cc or cw based on cross product
		if((x*Dial->y_old)-(y*Dial->x_old)>0)
		{
			//we're going counter clockwise
			Dial->value_ref-=unitChange;
			if(Dial->value_ref<Dial->angle_min)
			{
				if(Dial->wrap_around==true)
				{
					Dial->value_ref = Dial->angle_max - (Dial->value_ref-Dial->angle_min);
				}
				else
				{
					Dial->value_ref=Dial->angle_min;
				}
			}
		}
		else
		{
			//we're going clockwise
			Dial->value_ref+=unitChange;
			if(Dial->value_ref>Dial->angle_max)
			{
				if(Dial->wrap_around==true)
				{
					Dial->value_ref = Dial->angle_min + (Dial->value_ref-Dial->angle_max);
				}
				else
				{
					Dial->value_ref=Dial->angle_max;
				}
			}
		}
		//Dial::dial_visual.setRotation(Dial::value_ref);
		//Dial::dial_rep.setArc(0, Dial::value_ref);
		//Dial::dial_visual.invalidate();
		//Dial::dial_rep.invalidate();
		touchgfx_printf("Output value %f with val %f \n",Dial->value_ref,step1);
	}
}


///<summary>
///Establish if click is in the "goldilocks"
///pixel region to enable dial control
///<item><param name="x"> x coord of the object</param></item>
///<item><param name="y"> y coord of the object</param></item>
///</summary>
///<returns>Bool value if within acceptable use region.</returns>
bool Dial_Generic::isGoldilocks(DialData* Data, int16_t x, int16_t y)
{
	bool retval = false;
	//ensure that it's within the goldilocks zone to start moving the dial around!
	if((int16_t)sqrt(pow((double)x,2)+pow((double)y,2))<(Data->dial_radius+Data->dial_buffer))
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
void Dial_Generic::updateAngle(DialData* Dial, int16_t x, int16_t y)
{
	//tan(0) = 0 which means that opposite is x axis
	//derive angle using tan = opp/adj
	switch(y>0)
	{
	case false:
		//dealing with areas above circle centre
		Dial->angle = -std::atan((double)(x)/(double)(y));
		break;
	default:
		//dealing with areas on circle centre
		if(y==0)
		{
			//don't update if x is also 0!
			if(x!=0)
			{
				Dial->angle = x>0 ? M_PI_2:-M_PI_2;//if x is right, angle = 90deg, otherwise angle=270deg
			}
		}
		//dealing with areas below circle centre
		else
		{
			Dial->angle = M_PI - std::atan((double)(x)/(double)(y));
		}
		break;
	}
	if(Dial->angle<0)
	{
		Dial->angle+=2*M_PI; //I can't be bothered with negative values they're such a bore. Force angles positive.
	}
}

