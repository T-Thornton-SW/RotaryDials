#ifndef DIAL_HPP
#define DIAL_HPP
#include <gui/containers/Dial_Generic.hpp>
#include <gui_generated/containers/DialBase.hpp>

class Dial : public DialBase
{
public:
    Dial();
    virtual ~Dial() {}

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
};

#endif // DIAL_HPP
