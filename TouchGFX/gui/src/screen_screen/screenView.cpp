#include <gui/screen_screen/screenView.hpp>




screenView::screenView(): dialClickedCallback(this, &screenView::dialClickHandler) { }



void screenView::setupScreen()
{
    screenViewBase::setupScreen();
    dial1.setClickAction(dialClickedCallback);
}

void screenView::tearDownScreen()
{
    screenViewBase::tearDownScreen();
}

void screenView::dialClickHandler(const Dial& d, const ClickEvent& evt)
{
	touchgfx_printf("test ");
    if (&d == &dial1)
    {
    	touchgfx_printf("test2 \n");
    	ClickEvent::ClickEventType clickEventTemp = evt.getType();
    	//make sure it's a click event
    	switch(clickEventTemp)
    	{
    	case(ClickEvent::ClickEventType::PRESSED):
    		//generate the coordinates
			{
				int16_t tempa = evt.getX();//-dial1.getX();
				int16_t tempb = evt.getY();//-dial1.getY();
				dial1.setXYCoord(tempa,tempb);
			}
			break;
    	default:
    		touchgfx_printf("test3\n");
    		dial1.Release();
    		break;
    	}
    }
}

void screenView::handleDragEvent(const DragEvent& evt)
{
	int16_t x_coord = evt.getNewX()-dial1.getX();
	int16_t y_coord = evt.getNewY()-dial1.getY();
	dial1.setXYCoord(x_coord,y_coord);
}


