#include <gui/screen_screen/screenView.hpp>




screenView::screenView(): dialClickedCallback(this, &screenView::dialClickHandler) { }


void screenView::setupScreen()
{
    screenViewBase::setupScreen();
    dial_full_motion.setClickAction(dialFMClickedCallback);
    dial_regular.setClickAction(dialClickedCallback);
    dial_SnapTo.setClickAction(dialSTClickedCallback);


}

void screenView::tearDownScreen()
{
    screenViewBase::tearDownScreen();
}


void screenView::dialClickHandler(const Dial& d, const ClickEvent& evt)
{
	touchgfx_printf("test ");
	if (d.isVisible()==true)
	{
		touchgfx_printf("test2 \n");
		ClickEvent::ClickEventType clickEventTemp = evt.getType();
		//make sure it's a click event
		switch(clickEventTemp)
		{
		case(ClickEvent::ClickEventType::PRESSED):
			//generate the coordinates
			{
				int16_t tempa = evt.getX();//-dial_regular.getX();
				int16_t tempb = evt.getY();//-dial_regular.getY();
				dial_regular.setXYCoord(tempa,tempb);
			}
			break;
		default:
			dial_regular.Release();
			break;
		}
	}

}

void screenView::dialClickHandler(const Dial_full_motion& d, const ClickEvent& evt)
{
	touchgfx_printf("test5 ");
	if (d.isVisible()==true)
	{
		touchgfx_printf("test4 \n");
		ClickEvent::ClickEventType clickEventTemp = evt.getType();
		//make sure it's a click event
		switch(clickEventTemp)
		{
		case(ClickEvent::ClickEventType::PRESSED):
			//generate the coordinates
			{
				int16_t tempa = evt.getX();//-dial_regular.getX();
				int16_t tempb = evt.getY();//-dial_regular.getY();
				dial_full_motion.setXYCoord(tempa,tempb);
			}
			break;
		default:
			dial_full_motion.Release();
			break;
		}
	}

}

void screenView::dialClickHandler(const Dial_SnapTo& d, const ClickEvent& evt)
{
	touchgfx_printf("test ");
/*	if (d.isVisible()==true)
	{
		touchgfx_printf("test2 \n");
		ClickEvent::ClickEventType clickEventTemp = evt.getType();
		//make sure it's a click event
		switch(clickEventTemp)
		{
		case(ClickEvent::ClickEventType::PRESSED):
			//generate the coordinates
			{
				int16_t tempa = evt.getX();//-dial_regular.getX();
				int16_t tempb = evt.getY();//-dial_regular.getY();
				dial_SnapTo.setXYCoord(tempa,tempb);
			}
			break;
		default:
			dial_SnapTo.Release();
			break;
		}
	}*/
}

void screenView::handleDragEvent(const DragEvent& evt)
{

	if(dial_regular.isVisible())
	{
		dial_regular.setXYCoord(evt.getNewX()-dial_regular.getX(),evt.getNewY()-dial_regular.getY());
	}
	else if(dial_SnapTo.isVisible())
	{
		//dial_SnapTo.setXYCoord(evt.getNewX()-dial_SnapTo.getX(),evt.getNewY()-dial_SnapTo.getY());
	}
	else if(dial_full_motion.isVisible())
	{
		dial_full_motion.setXYCoord(evt.getNewX()-dial_full_motion.getX(),evt.getNewY()-dial_full_motion.getY());
	}
}


