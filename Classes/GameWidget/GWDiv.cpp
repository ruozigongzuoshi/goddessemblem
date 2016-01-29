#include "GWDiv.h"
#include "GlobalSetting/GlobalParam.h"
#include "GlobalSetting/GlobalPath.h"

#include "cocos2d.h"
USING_NS_CC;

bool GWDiv::init() {
    iOffset = 0;
    return true;
}

GWDiv::GWDiv() {

}

GWDiv::~GWDiv() {

}

void GWDiv::draw( void ) {
    CCPoint pos = getPosition();
    CCSize size = getContentSize();

    int x = pos.x;
    int y = pos.y;

    /* 
        ����ڵ��Ѿ������������꣬���漸��ͼ��ʱ�����Ա���ڵ�Ϊ��׼�ģ�
        Ҳ����˵������ͼ���൱�ڽڵ���ӿؼ������Լ���ͼ�ε�����Ϊ��0�� 0������
    */
    x = 0;
    y = 0;

    //CCLOG("x = %d, width = %f, height = %f", x, size.width, size.height);

    /* ���е�Ϊ����� */
    CCPoint filledVertices[] = { 
        ccp(x - size.width / 2, y + size.height / 2), 
        ccp(x + size.width / 2, y + size.height / 2), 
        ccp(x + size.width / 2, y - size.height / 2),
        ccp(x - size.width / 2, y - size.height / 2),
    };

    ccDrawSolidPoly(filledVertices, 4, ccc4f(0.5f, 0.5f, 1, 1 ) );

    CCPoint filledVertices2[] = { 
        ccp(x, y), 
        ccp(x + size.width, y), 
        ccp(x + size.width, y - size.height),
        ccp(x, y - size.height),
    };
    //ccDrawSolidPoly(filledVertices2, 4, ccc4f(0.9f, 0.5f, 1, 1 ) );

    CCPoint filledVertices3[] = { 
        ccp(x, y), 
        ccp(x + size.width, y), 
        ccp(x + size.width, y + size.height),
        ccp(x, y + size.height),
    };
    //ccDrawSolidPoly(filledVertices3, 4, ccc4f(0.1f, 0.5f, 1, 1 ) );
}