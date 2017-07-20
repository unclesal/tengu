// ********************************************************************************************************************
// *                                                                                                                  *
// *                               The graphical representation for logical AND branching.                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Графическое представление ветвления с логическим И.                              *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 18 jun 2017 at 09:31 *
// ********************************************************************************************************************

#include "ANDorItem.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ANDorItem::ANDorItem ( tengu::ANDor * entity, QGraphicsItem* parent ) 
    : tengu::ResizeableItemWithLinks ( entity , parent )
{
    // For initial sizes only. Will be recalculated by ResizeableItemWithLinks.
    // Только для начальных размеров, будет пересчитано в ResizeableItemWithLinks.
    
    _boundingRect = QRect( 0, 0, 40, 144 );
    
    _class_name = "ANDorItem";
    _entity_type = AbstractEntity::ET_ANDorItem;        
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Entity pointer validation.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Проверка валидности указателя на сущность.                                *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ANDorItem::checkEntity() {
    if ( ! _entity ) _entity = new ANDor();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The paint method.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Метод рисования.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ANDorItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ) {
    
    _storePainterSettings( painter );
    _drawTaskRectangle( painter );
    
    // Execution mode pixmap
    // Картинка режима выполнения.
    
    QPixmap pm = _executionModePixmap();
    painter->drawPixmap( _boundingRect.width() - 34, 6, pm );
    
    // The & label, we talking about logical AND
    // Надпись &, мы говорим о логическом И
    
    QFont font("Tahoma", 22 );
    font.setBold( true );
    painter->setFont( font );
    painter->drawText( QPoint( 14, _boundingRect.height() - 10 ), "&" );
    
    _restorePainterSettings( painter );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Деструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ANDorItem::~ANDorItem() {

}
