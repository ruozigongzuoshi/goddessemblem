#include "GWWinXmlDataSetting.h"

bool GWWinXmlDataSetting::init() {
    return true;
}

void GWWinXmlDataSetting::setXmlEnWinType( GWWinXmlData* xmlData,const char* sText ) {
    if(strcmp(sText, WINType_C_en_Win_None) == 0) {
        xmlData->setEnWinType(en_Win_None);
    }
    else if(strcmp(sText, WINType_C_en_Win_Div) == 0) {
        xmlData->setEnWinType(en_Win_Div);
    }
    else if(strcmp(sText, WINType_C_en_Win_Scale9Win) == 0) {
        xmlData->setEnWinType(en_Win_Scale9Win);
    }
	else if(strcmp(sText, WINType_C_en_Win_Scale9Button) == 0) {
		xmlData->setEnWinType(en_Win_Scale9Button);
	}
	else if(strcmp(sText, WINType_C_en_Win_NormalWin) == 0) {
		xmlData->setEnWinType(en_Win_NormalWin);
	}
	else if(strcmp(sText, WINType_C_en_Win_AnimationWin) == 0) {
		xmlData->setEnWinType(en_Win_AnimationWin);
	}
	else if(strcmp(sText, WINType_C_en_Win_Label) == 0) {
		xmlData->setEnWinType(en_Win_Label);
	}
}

void GWWinXmlDataSetting::setXmliX( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_TEXT_left) == 0) {
        xmlData->setXLeft(true);
    }
    else if(strcmp(sText, XML_TEXT_right) == 0) {
        xmlData->setXRight(true);
    }
    else if(strcmp(sText, XML_TEXT_center) == 0) {
        xmlData->setXCenter(true);
    }
    else {
        xmlData->setiX(atoi(sText));
    }

}

void GWWinXmlDataSetting::setXmliY( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_TEXT_top) == 0) {
        xmlData->setYTop(true);
    }
    else if(strcmp(sText, XML_TEXT_bottom) == 0) {
        xmlData->setYBottom(true);
    }
    else if(strcmp(sText, XML_TEXT_center) == 0) {
        xmlData->setYCenter(true);
    }
    else {
        xmlData->setiY(atoi(sText));
    }
}

void GWWinXmlDataSetting::setXmliAlpha( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setiAlpha(atoi(sText));
}

void GWWinXmlDataSetting::setXmlfScaleX( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setfScaleX(atof(sText));
}

void GWWinXmlDataSetting::setXmlfScaleY( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setfScaleY(atof(sText));
}

void GWWinXmlDataSetting::setXmlfAnchorX( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setfAmchorX(atof(sText));
}

void GWWinXmlDataSetting::setXmlfAnchorY( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setfAmchorY(atof(sText));
}

void GWWinXmlDataSetting::setXmlfDelay( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setfDelay(atof(sText));
}

void GWWinXmlDataSetting::setXmlVisible( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_TEXT_true) == 0) {
        xmlData->setVisible(true);
    }
    else {
        xmlData->setVisible(false);
    }
}

void GWWinXmlDataSetting::setXmlEnable( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_TEXT_true) == 0) {
        xmlData->setEnable(true);
    }
    else {
        xmlData->setEnable(false);
    }
}

void GWWinXmlDataSetting::setXmlTouchable( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_TEXT_true) == 0) {
        xmlData->setTouchable(true);
    }
    else {
        xmlData->setTouchable(false);
    }
}

void GWWinXmlDataSetting::setXmlDes( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setsDes(sText);
}

void GWWinXmlDataSetting::setXmliWidth( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_VALUE_max) == 0) {
        xmlData->setMaxWidth(true);
    }
    else {
        xmlData->setiWidth(atoi(sText));
    }
}

void GWWinXmlDataSetting::setXmliHeight( GWWinXmlData* xmlData, const char* sText ) {
    if(strcmp(sText, XML_VALUE_max) == 0) {
        xmlData->setMaxHeight(true);
    }
    else {
        xmlData->setiHeight(atoi(sText));
    }
}

void GWWinXmlDataSetting::setXmlScale9bg( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setsScale9bg(sText);
}

void GWWinXmlDataSetting::setXmlScale9bgDown( GWWinXmlData* xmlData, const char* sText ) {
    xmlData->setsScale9bgDown(sText);
}

void GWWinXmlDataSetting::setXmlsText( GWWinXmlData* xmlData, const char* sText ) {
	xmlData->setsText(sText);
}

void GWWinXmlDataSetting::setXmlsBgPath( GWWinXmlData* xmlData, const char* sText ) {
	xmlData->setsBg(sText);
}

void GWWinXmlDataSetting::setXmlsAnimation( GWWinXmlData* xmlData, const char* sText ) {
	xmlData->setsAnimation(sText);
}

void GWWinXmlDataSetting::setXmlsAnimationName( GWWinXmlData* xmlData, const char* sText ) {
	xmlData->setsAnimationName(sText);
}

void GWWinXmlDataSetting::setXmlsPlist( GWWinXmlData* xmlData, const char* sText ) {
	xmlData->setsPlist(sText);
}

void GWWinXmlDataSetting::setWinXmlData( GWWinXmlData* xmlData, const char* sName, const char* sText ) {
    if(strcmp(sName, XML_VALUE_enWinType) == 0) {
        setXmlEnWinType(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_x) == 0) {
        setXmliX(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_y) == 0) {
        setXmliY(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_alpha) == 0) {
        setXmliAlpha(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_scaleX) == 0) {
        setXmlfScaleX(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_scaleY) == 0) {
        setXmlfScaleY(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_visible) == 0) {
        setXmlVisible(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_enable) == 0) {
        setXmlEnable(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_touchable) == 0) {
        setXmlTouchable(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_des) == 0) {
        setXmlDes(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_width) == 0) {
        setXmliWidth(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_height) == 0) {
        setXmliHeight(xmlData, sText);
    }
	else if(strcmp(sName, XML_VALUE_scale9bg) == 0) {
		setXmlScale9bg(xmlData, sText);
	}
	else if(strcmp(sName, XML_VALUE_scale9bgDown) == 0) {
		setXmlScale9bgDown(xmlData, sText);
	}
    else if(strcmp(sName, XML_VALUE_text) == 0) {
        setXmlsText(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_marginH) == 0) {
        setXmliMarginH(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_marginV) == 0) {
        setXmliMarginV(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_bg) == 0) {
        setXmlsBgPath(xmlData, sText);
    }
	else if(strcmp(sName, XML_VALUE_Animation) == 0) {
        setXmlsAnimation(xmlData, sText);
    }
	else if(strcmp(sName, XML_VALUE_AnimationName) == 0) {
        setXmlsAnimationName(xmlData, sText);
    }
	else if(strcmp(sName, XML_VALUE_Plist) == 0) {
        setXmlsPlist(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_AnchorX) == 0) {
        setXmlfAnchorX(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_AnchorY) == 0) {
        setXmlfAnchorY(xmlData, sText);
    }
    else if(strcmp(sName, XML_VALUE_fontSize) == 0) {
        setXmliFontSize(xmlData, sText);
    }
	else if(strcmp(sName, XML_VALUE_Loops) == 0) {
        setXmliLoops(xmlData, sText);
    }
	else if(strcmp(sName, XML_VALUE_Delay) == 0) {
        setXmlfDelay(xmlData, sText);
    }
}
