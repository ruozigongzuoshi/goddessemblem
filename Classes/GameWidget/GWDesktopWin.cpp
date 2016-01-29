#include "GWDesktopWin.h"

GWDesktopWin::GWDesktopWin()
: mWinDict(NULL),
  mDesIDDict(NULL) {

}

GWDesktopWin::~GWDesktopWin() {
    CC_SAFE_RELEASE_NULL(mWinDict);
}

bool GWDesktopWin::init() {
    mWinDict = CCDictionary::create();
    mWinDict->retain();

    mDesIDDict = CCDictionary::create();
    mDesIDDict->retain();

    this->setTouchEnabled(true);
    return true;
}

void GWDesktopWin::addWin( GWBase* mWin ) {
    assert(mWin && "addWin:mWin is NULL!");

    int iWinID = mWin->getiWinID();

    /* 如果已经存在该ID的控件,则先删除 */
    if(mWinDict->objectForKey(iWinID) != NULL) {
        mWinDict->removeObjectForKey(iWinID);
    }

    /* 添加控件到字典中,方便索引 */
    mWinDict->setObject(mWin, iWinID);
}

void GWDesktopWin::addDesID( int iWinID, const char* sDes ) {
    mDesIDDict->setObject(CCInteger::create(iWinID), sDes);
}

GWBase* GWDesktopWin::getWinByID( int ID ) {
    CCObject* obj = mWinDict->objectForKey(ID);

    if(obj != NULL) {
        return (GWBase*) obj;
    }

    return NULL;
}

GWBase* GWDesktopWin::getWinByDes( const char* sDes ) {
    CCObject* obj = mDesIDDict->objectForKey(sDes);

    if(obj == NULL) {
        return NULL;
    }

    CCInteger* intWinID = (CCInteger*) obj;
    int iWinID = intWinID->getValue();

    return getWinByID(iWinID);
}

void GWDesktopWin::removeAllWins() {
    mWinDict->removeAllObjects();
    mDesIDDict->removeAllObjects();

    this->removeAllChildrenWithCleanup(true);
}

void GWDesktopWin::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GWDesktopWin::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCLOG("touchBegan x = %f, y = %f", pos.x, pos.y);

    return false;
}

void GWDesktopWin::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCLOG("ccTouchMoved x = %f, y = %f", pos.x, pos.y);
}

void GWDesktopWin::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
    CCLOG("ccTouchEnded x = %f, y = %f", pos.x, pos.y);
}
