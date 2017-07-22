// ********************************************************************************************************************
// *                                                                                                                  *
// *                                     An item which can be linked with another items.                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                Элемент, который может иметь связь с другими элементами.                          *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 22 jun 2017 at 10:33 *
// ********************************************************************************************************************

#include "ItemWithLinks.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ItemWithLinks::ItemWithLinks ( tengu::AbstractEntity * entity, QGraphicsItem* parent ) 
    : AbstractEntityItem ( entity, parent )
{
    _linksOutgoingFromThis = QMap< QString, LinkItem * >();
    _linksIncommingToThis = QMap< QString, LinkItem * >();    
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Add a link which is outgoing from this item.                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Добавить связь, исходящую из данного элемента.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::addOutgoingLink ( tengu::LinkItem * link ) {
    _linksOutgoingFromThis[ link->getUUID() ] = link;
    QObject::connect( link, SIGNAL(signalLinkRemoved(QString)), this, SLOT(removeLink(QString)) );
    // QObject::connect( link, SIGNAL(signalLinked()), this, SLOT( __on__linked() ) );
    link->__setFrom( this );
            
    update();
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Add a link which is incomming to this item                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Добавить связь, входящую в этот элемент.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::addIncommingLink ( tengu::LinkItem * link ) {
    _linksIncommingToThis[ link->getUUID() ] = link;
    QObject::connect( link, SIGNAL(signalLinkRemoved(QString)), this, SLOT(removeLink(QString)) );
    // QObject::connect( link, SIGNAL(signalLinked()), this, SLOT( __on__linked() ) );
    link->__setTo( this );
    
    update();
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Remove the link                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Удаление связи.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::removeLink ( tengu::LinkItem * link ) {
    removeLink( link->getUUID() );    
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Remove the link by it's uuid (slot)                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     Удаление связи по ее идентификатору (слот).                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::removeLink ( QString uuid ) {
    
    if ( _linksIncommingToThis.contains( uuid ) ) {
        QObject::disconnect( _linksIncommingToThis[uuid], SIGNAL(signalLinkRemoved(QString)), this, SLOT( removeLink( QString) ) );
        // QObject::disconnect( _linksIncommingToThis[uuid], SIGNAL(signalLinked()), this, SLOT( __on__linked() ) );
        _linksIncommingToThis.remove( uuid );
    };
    
    if ( _linksOutgoingFromThis.contains( uuid ) ) {
        QObject::disconnect( _linksOutgoingFromThis[uuid], SIGNAL(signalLinkRemoved(QString)), this, SLOT(removeLink(QString)) );
        // QObject::disconnect( _linksOutgoingFromThis[uuid], SIGNAL(signalLinked()), this, SLOT( __on__linked() ) );
        _linksOutgoingFromThis.remove( uuid );
    };
    
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Get all links of this item.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Вернуть все связи данного элемента.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

QList< tengu::LinkItem* > tengu::ItemWithLinks::hisLinks() {
    
    QList< LinkItem * > result;
    
    foreach( LinkItem * item, _linksIncommingToThis ) {
        result.append( item );
    };
    
    foreach( LinkItem * item, _linksOutgoingFromThis ) {
        result.append( item );
    };
    
    return result;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Convert an element to JSON form.                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Преобразование элемента в JSON-форму.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

QJsonObject tengu::ItemWithLinks::toJSON() {
    
    QJsonObject obj = tengu::AbstractEntityItem::toJSON();
    
    AbstractAgent * agent = dynamic_cast<AbstractAgent * > ( _entity );
    
    if ( agent ) {
        
        
        
    };
    
    return obj;
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Convert JSON form to data field of this element.                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Преобразование JSONа в поля данных этого элемента.                             *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::ItemWithLinks::fromJSON ( QJsonObject json ) {
    
    bool result = tengu::AbstractEntityItem::fromJSON ( json );
    return result;
    
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Recalculate coordinates.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                Пересчитать координаты.                                           *
// *                                                                                                                  *
// ********************************************************************************************************************

/*
void tengu::ItemWithLinks::recalculate() {
    
    foreach ( LinkItem * link, _linksIncommingToThis ) {
        link->recalculate();
    };
    
    foreach ( LinkItem * link, _linksOutgoingFromThis ) {
        link->recalculate();
    };
    
}
*/

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Update this element, overrided function.                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Обновление элемента, перекрытая функция.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

/*
void tengu::ItemWithLinks::update( const QRectF & rect ) {
        
    foreach ( LinkItem * link, _linksIncommingToThis ) {
        link->recalculate();
        link->update();
    };
    
    foreach ( LinkItem * link, _linksOutgoingFromThis ) {
        link->recalculate();
        link->update();
    };
    
    AbstractEntityItem::update( rect );    
}
*/

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                 One of existing links was connected to some agent.                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                              Одна из существующих связей была к кому-то присоединена.                            *
// *                                                                                                                  *
// ********************************************************************************************************************

/*
void tengu::ItemWithLinks::__on__linked() {
    update();
}
*/

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                Can this item accept once more incomming link?                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                           Может ли данный элемент принять еще одну входящую связь?                               *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::ItemWithLinks::acceptIncommingLink() {
    return ( _linksIncommingToThis.count() == 0 );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                 Can this item accept once more outgoing link?                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                            Может ли данный элемент принять еще одну исходящую связь?                             *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::ItemWithLinks::acceptOutgoingLink() {
    return ( _linksOutgoingFromThis.count() == 0 );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ItemWithLinks::~ItemWithLinks() {

}

