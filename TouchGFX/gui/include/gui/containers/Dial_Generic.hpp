#pragma once
#include <stdint.h>
#include <touchgfx/Utils.hpp>
#include <math.h>
class DialData
{
public:
	//the generic dial information with initialisers
    bool wrap_around = false;
    bool first_click =true;
    bool is_rotating =false;
    float angle = 0;
    float angle_old = 0;
    int16_t x_old = 0;
    int16_t y_old = 0;
    float value_ref = 0;//the position reference on the image dial, in most cases equals angle_old.
    int current_dial_value = 0;
    float angle_max = 0;
    float angle_min = 0;
    double dial_radius = 0;
    double dial_buffer = 0;
};


class Dial_Generic
{
	public:
	Dial_Generic(){};//prevent instancing of Dial_Generic
	static void handleClick(DialData*,int16_t,int16_t);

	private:
    static bool isGoldilocks(DialData*,int16_t,int16_t);
    static void updateAngle(DialData*,int16_t, int16_t);
    static void updateDistance(DialData*,int16_t,int16_t);
};
