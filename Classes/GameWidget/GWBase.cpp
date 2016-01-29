#include "GWBase.h"
#include "GlobalSetting/GlobalParam.h"


GWBase::GWBase()
: m_ID(-1),
  m_iOrder(GlobalParam::LayerOrder_LvLNormal),
  m_isHasParentWin(false),
  m_isHasChildWin(false) {

}

GWBase::~GWBase() {

}

const EnumWinType GWBase::getEnWinType() { return this->mEnWinType;}
void GWBase::setEnWinType(EnumWinType _mEnWinType) { this->mEnWinType = _mEnWinType;}
const int GWBase::getiOrder() { return this->m_iOrder;}
void GWBase::setiOrder(int _iOrder) { this->m_iOrder = _iOrder;}
const int GWBase::getiWinID() { return this->m_ID;}  

void GWBase::setiWinID(int _ID) { 
    assert(_ID > 0 && "setID: ID mast > 0!");

    /* 控件的ID一旦赋值,就不能再次改变 */
    assert(this->m_ID < 0 && "setID: Don't change my ID, please!");

    this->m_ID = _ID;
}
