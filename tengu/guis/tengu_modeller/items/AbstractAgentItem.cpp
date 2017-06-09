// ********************************************************************************************************************
// *                                                                                                                  *
// *                              Abstract graphics object, representation of AbstractAgent.                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                           Абстрактный графический объект, представление AbstractAgent'а.                         *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 08 jun 2017 at 09:00 *
// ********************************************************************************************************************

#include "AbstractAgentItem.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Конструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractAgentItem::AbstractAgentItem(AbstractAgent * agent, QGraphicsItem* parent) 
    : QGraphicsObject( parent )
{
    _agent = agent;
    _boundRect = QRectF(0, 0, 20, 20);
    __mousePressed = false;
    // setAcceptHoverEvents( true );
    // setAcceptTouchEvents( true );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Overrided function for bounding the rectangle.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Перекрытая функция для привязки прямоугольника.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

QRectF tengu::AbstractAgentItem::boundingRect() const {
    return _boundRect;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                    Paint function for abstract graphics agent (only for demonstrate it is empty)                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *             Функция рисования абстрактного графического агента (только чтобы показать, что он пустой)            *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->drawRect(  _boundRect );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Mouse press event handler.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Обработчик события нажатия мышки.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::AbstractAgentItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
    qDebug() << "AbstractAgentItem::mousePressEvent()" ;
    __mousePressed = true;
    QGraphicsItem::mousePressEvent ( event );
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Mouse release event handler.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Обработчик события отпускания мыши.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::AbstractAgentItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ) {
    qDebug() << "AbstractAgentItem::mouseReleaseEvent()" ;
    __mousePressed = false;
    QGraphicsItem::mouseReleaseEvent ( event );
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Mouse move event handler.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Обработчик события перемещения мыши.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::AbstractAgentItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ) {
    qDebug() << "AbstractAgentItem::mouseMoveEvent()";
    QGraphicsItem::mouseMoveEvent ( event );
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractAgentItem::~AbstractAgentItem() {
}


