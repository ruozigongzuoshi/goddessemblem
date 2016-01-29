#include "WidgetHPSlot.h"
#include "Entity.h"

WidgetHPSlot::WidgetHPSlot() {
	m_entity = NULL;
	m_slider = NULL;
}

WidgetHPSlot::~WidgetHPSlot() {
	CC_SAFE_RELEASE(m_entity);
	CC_SAFE_RELEASE(m_slider);
}

WidgetHPSlot* WidgetHPSlot::create( Entity* entity ) {
	WidgetHPSlot* hpSlot = new WidgetHPSlot();

	if(hpSlot && hpSlot->init(entity)) {
		hpSlot->autorelease();
	}
	else {
		CC_SAFE_DELETE(hpSlot);
	}

	return hpSlot;
}

bool WidgetHPSlot::init( Entity* entity ) {
	bool bRet = false;

	do {
		CC_SAFE_RETAIN(entity);
		this->m_entity = entity;
		
		m_slider = CCControlSlider::create(
			"widget/sliderBg.png", 
			"widget/sliderValue.png", 
			"widget/sliderThumb.png");
		m_slider->setTouchEnabled(false);
		this->addChild(m_slider);
		bRet = true;
	} while (0);

	return bRet;
}

CCControlSlider* WidgetHPSlot::getSlider() {
	return m_slider;
}

