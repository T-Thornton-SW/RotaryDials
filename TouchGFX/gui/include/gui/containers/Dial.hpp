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
    DialData data;
    void handleClick(int16_t,int16_t);
};

#endif // DIAL_HPP
