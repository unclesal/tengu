// ********************************************************************************************************************
// *                                                                                                                  *
// *           The sprout from / to agent, the communication branch between agents using redis messages.              *
// *                                  In other hand this is a property of the agent.                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                 Отросток из / в агента. Веточка для связи между агентами через сообщения редиса.                 *
// *                                  С другой стороны, он же и "свойство" агента.                                    *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 27 may 2017 at 08:38 *
// ********************************************************************************************************************

#include "Sprout.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                The constructor.                                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Конструктор.                                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Sprout::Sprout( QString name, AbstractAgentKernel * owner )
    : QObject()
{
    __name = name;
    __owner = owner;
    __subscribed = false;
    __subscribtion_requested = false;
    __inputChannel = QString("");
    __outputChannel = QString("");
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Add input redis channel.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Добавить канал редиса по входу.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setInputChannel( QString channel ) {
    if ( ! channel.isEmpty() ) {
        __inputChannel = channel;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Add output redis channel.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Добавить выходной канал редиса.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setOutputChannel( QString channel ) {
    if ( ! channel.isEmpty() ) __outputChannel = channel ;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                        Get the value of object (procedure for providing property behaviour)                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                  Получить значение объекта (процедура для обеспечения поведения как "свойства")                  *
// *                                                                                                                  *
// ********************************************************************************************************************

QVariant tengu::Sprout::__getValue() {    
    return __value;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                    Set the value of this object (for property, but also can be use directly)                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *    Установить значение для данного объекта. Вообще-то для свойства, но может быть использовано и напрямую.       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::__setValue( QVariant val ) {
    __value = val;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Somewhat has been subscribed.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          что-то было реально подписано.                                          *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::subscribed( QString channel ) {
    if (
        ( ! __subscribed )
        && ( ! __inputChannel.isEmpty() )
        && ( __inputChannel == channel ) 
    ) {
        __subscribed = true;
    }
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Somewhat has been unsubscribed.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                               Что-то отписалось.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::unsubscribed( QString channel ) {

    if ( _to_me( channel ) ) {
        __subscribed = false;
        __subscribtion_requested = false;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    The possibility to subscribe for this sprout.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Возможность для данного объекта подписаться.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::subscribe() {

    if ( 
        ( ! __subscribed ) 
        && ( ! __subscribtion_requested )
        && ( ! __inputChannel.isEmpty() )
        && ( __owner )
        && ( __owner->_sub_redis ) 
        && ( __owner->__sub_redis_connected )
    ) {
        __owner->_sub_redis->subscribe( __inputChannel );
        __subscribtion_requested = true;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Was this message addressed to me?                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Было ли данное сообщение адресовано мне?                                      *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::_to_me( QString channel ) {

    return ( ( ! __inputChannel.isEmpty() ) && ( channel == __inputChannel ) );
        
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Handle the message from redis.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Обработать сообщение из редиса.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::handleMessage( QString channel, QString value ) {

    if ( _to_me( channel ) ) {
        __value.setValue( value );
        emit signalGotValue( __value );
        return true;
    };
    return false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Деструктор.                                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Sprout::~Sprout() {
}

