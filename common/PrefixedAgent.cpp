// ********************************************************************************************************************
// *                                                                                                                  *
// *    "Prefixed agent" is "agent with the prefix". Prefix plus agent name = path in redis subscribed channels to    *
// *                                       most common messages to / from this agent.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// * PrefixedAgent - это "агент с префиксом". Префикс плюс имя агента дают путь в редисе для подписываемых каналов,   *
// *                                  в которых ходят общие сообщения к / от этого агента.                            *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 26 may 2017 at 15:53 *
// ********************************************************************************************************************

#include "PrefixedAgent.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Конструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::PrefixedAgent::PrefixedAgent( QString prefix, QString name, QObject * parent )
    : AbstractAgent( name, parent ) 
{
    _prefix = prefix;
    
    // The activity of this channel throught redis.
    // Активность данного канала через редис.
    /*
    AbstractAgent::reaction_t rActivity;
    rActivity.channel = QString(_prefix + "activity" );
    rActivity.reaction = reinterpret_cast< AbstractAgent::reaction_callback_t > ( & this->__on_activity_received );
    addReaction( rActivity );
    */
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                 The request of activity change has been received.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Поступил запрос изменения активности.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::PrefixedAgent::__on_activity_received( QString channel, QString message ) {
    /*
    Q_UNUSED( channel );
    bool a = false;
    bool ok = false;
    int i = message.toInt( & ok ) ;
    if ( (message.toUpper() == "TRUE" ) || ( ( ok ) && ( i != 0 ) ) ) a = true;
    _setActivity( a );
    */
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Деструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::PrefixedAgent::~PrefixedAgent() {
}
