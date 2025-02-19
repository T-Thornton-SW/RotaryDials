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
    void dialClickHandler(const Dial_full_motion&, const ClickEvent&);
    void dialClickHandler(const Dial& , const ClickEvent& );
    void dialClickHandler(const Dial_SnapTo& , const ClickEvent&);

    virtual void handleDragEvent(const DragEvent& );
protected:
    Callback<screenView, const Dial_full_motion&, const ClickEvent&> dialFMClickedCallback;
    Callback<screenView, const Dial&, const ClickEvent&> dialClickedCallback;
    Callback<screenView, const Dial_SnapTo&, const ClickEvent&> dialSTClickedCallback;

};

#endif // SCREENVIEW_HPP
