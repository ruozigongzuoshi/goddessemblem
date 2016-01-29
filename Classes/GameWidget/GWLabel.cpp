#include "GWLabel.h"
#include "GlobalSetting/GlobalPath.h"
#include "FileLoad\I18N.h"
#include <string>

GWLabel::GWLabel() {

}

GWLabel::~GWLabel() {

}

bool GWLabel::init() {
	bool bRet = false;

	do 
	{
		m_label = CCLabelTTF::create("", PATH_FONT_PUBLIC, 24);
		this->addChild(m_label);
		bRet = true;
	} while (0);

	return bRet;
}

void GWLabel::setsText( const char* sText ) {
	//m_label->setString(sText);
	CCString* src = CCString::create(sText);
	CCString* dst = CCString::create("");

	/* 判断是否要从配置文件中获取字符串 */
	dst->m_sString = src->m_sString.substr(0, 1);
	if(dst->m_sString.compare("@") == 0) {
		src->m_sString = src->m_sString.substr(1, src->length());
		
		int strKey = src->intValue();

		m_label->setString(I18N::shareI18N()->getcStringByKey(strKey));
	}
	else {
		m_label->setString(sText);
	}
}

void GWLabel::setsText( int iValue ) {
    setsText(CCString::createWithFormat("%d", iValue)->getCString());
}
void GWLabel::setiFontSize( int iFontSize ) {
    m_label->setFontSize(iFontSize);
}

void GWLabel::setAnchorPoint( const CCPoint& anchorPoint ) {
    CCNode::setAnchorPoint(anchorPoint);
    m_label->setAnchorPoint(anchorPoint);
}

void GWLabel::setColorRGB( int r, int g, int b ) {
    m_label->setColor(ccc3(r, g, b));
}