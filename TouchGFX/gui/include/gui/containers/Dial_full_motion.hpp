#ifndef DIAL_FULL_MOTION_HPP
#define DIAL_FULL_MOTION_HPP

#include <gui_generated/containers/Dial_full_motionBase.hpp>

class Dial_full_motion : public Dial_full_motionBase
{
public:
    Dial_full_motion();
    virtual ~Dial_full_motion() {}

    virtual void initialize();
    virtual void setXYCoord(int16_t,int16_t);
    virtual void Release();

private:
    bool firstClick;
    bool isRotating;
    float angle;
    float angle_old;
    int16_t x_old;
    int16_t y_old;
    float value_ref;

    bool isGoldilocks(int16_t,int16_t);
    void updateAngle(int16_t, int16_t);
    void updateDistance(int16_t,int16_t);
    void handleClick(int16_t,int16_t);
protected:
};

#endif // DIAL_FULL_MOTION_HPP
