#include "GWWinFactory.h"
#include "GWDiv.h"
#include "GWScale9Button.h"
#include "GlobalSetting/GlobalPath.h"
#include "GlobalSetting/GlobalParam.h"
#include "GWScale9Win.h"
#include "GWNormalWin.h"
#include "GWLabel.h"
#include "GWAnimationWin.h"

bool GWWinFactory::init() {
    return true;
}

GWBase* GWWinFactory::createWin( EnumWinType enWinType )
{
    GWBase* win = NULL;
    switch(enWinType) {
    case en_Win_None:

        break;
    case en_Win_Scale9Button:
        win = GWScale9Button::create(
            CCLabelTTF::create("GWScale9Button", PATH_FONT_PUBLIC, GlobalParam::PublicFontSize), 
            CCScale9Sprite::create(PATH_PublicUI_BlueBtn));
        break;
    case en_Win_Div:
        win = GWDiv::create();
        break;
    case en_Win_Scale9Win:
        win = GWScale9Win::create();
        break;
	case en_Win_NormalWin:
		win = GWNormalWin::create();
		break;
	case en_Win_AnimationWin:
		win = GWAnimationWin::create();
		break;
	case en_Win_Label:
		win = GWLabel::create();
		break;
    }

    if(win != NULL) {
        win->setEnWinType(enWinType);
    }

    return win;
}