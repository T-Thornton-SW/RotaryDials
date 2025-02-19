#ifndef SCREENVIEW_HPP
#define SCREENVIEW_HPP

#include <gui_generated/screen_screen/screenViewBase.hpp>
#include <gui/screen_screen/screenPresenter.hpp>

class screenView : public screenViewBase
{
public:
    screenView();
    virtual ~screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    //TT INSERTED CODE!!!!
    void dialClickHandler(const Dial& d, const ClickEvent& e);
    virtual void handleDragEvent(const DragEvent& Event);
protected:
    Callback<screenView, const Dial&, const ClickEvent&> dialClickedCallback;
};

#endif // SCREENVIEW_HPP
