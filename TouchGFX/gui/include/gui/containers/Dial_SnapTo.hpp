#pragma once
#include <gui/containers/Dial_Generic.hpp>
#include <gui_generated/containers/Dial_SnapToBase.hpp>

#define DIAL_MAX_VAL	4
#define DIAL_MIN_VAL	0


class Dial_SnapTo : public Dial_SnapToBase
{
public:
    Dial_SnapTo();
    virtual ~Dial_SnapTo() {}

    virtual void initialize();
    virtual void setXYCoord(int16_t,int16_t);
    virtual void Release();

private:
    DialData data;
    touchgfx::TextArea DialList[DIAL_MAX_VAL];
    bool isGoldilocks(int16_t,int16_t);
    void updateAngle(int16_t, int16_t);
    void updateDistance(int16_t,int16_t);
    void handleClick(int16_t,int16_t);
protected:
};


