#ifndef DIAL_FULL_MOTION_HPP
#define DIAL_FULL_MOTION_HPP
#include <gui/containers/Dial_Generic.hpp>
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
    DialData data;
    void handleClick(int16_t,int16_t);
protected:
};

#endif // DIAL_FULL_MOTION_HPP
