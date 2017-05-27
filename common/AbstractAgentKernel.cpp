// ********************************************************************************************************************
// *                                                                                                                  *
// *    The "kernel" of abstract agent. Class has been introduced to automatically work of properties (sprouts).      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *  "Ядро" абстрактного агента. Класс был введен для автоматической работы "свойств" (они же "отростки" - Sprout).  *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 27 may 2017 at 08:31 *
// ********************************************************************************************************************

#include "AbstractAgentKernel.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                 The constructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Конструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractAgentKernel::AbstractAgentKernel( QString name, QObject * parent )
    : QObject( parent )
{
    _name = name;
    
    __activity = false;
    
    __pub_redis_connected = false;
    __sub_redis_connected = false;
    
    // Creating redis'es objects.
    // Создание редисовых объектов.
    
    _createRedises();
    
    // Binding redis object
    // Связка публикатора редиса.
    
    QObject::connect( _pub_redis, SIGNAL( signalConnected() ), this, SLOT( __on_pub_redis_connected() ) );
    QObject::connect( _pub_redis, SIGNAL( signalDisconnected() ), this, SLOT( __on_pub_redis_disconnected() ) );
    QObject::connect( _pub_redis, SIGNAL( signalError(QString) ), this, SLOT( __on_redis_error( QString ) ) );
    
    // Binding the subscriber redis object
    // Связка объекта подписчика на редиса.
    
    QObject::connect( _sub_redis, SIGNAL( signalConnected() ), this, SLOT( __on_sub_redis_connected() ) );
    QObject::connect( _sub_redis, SIGNAL( signalDisconnected() ), this, SLOT( __on_sub_redis_disconnected() ) );
    QObject::connect( _sub_redis, SIGNAL( signalError(QString) ), this, SLOT( __on_redis_error( QString) ) );
    QObject::connect( _sub_redis, SIGNAL( signalSubscribed(QString) ), this, SLOT( __on_subscribed( QString ) ) );
    QObject::connect( _sub_redis, SIGNAL( signalUnsubscribed(QString) ), this, SLOT( __on_unsubscribed( QString ) ) );
    QObject::connect( _sub_redis, SIGNAL( signalGotMessage(QString, QString) ), this, SLOT( __on_got_message( QString, QString ) ) );
    
    // The timers for agent.
    // Таймеры для этого агента.
    
    __ping_timer = new QTimer( this );
    QObject::connect( __ping_timer, SIGNAL( timeout() ), this, SLOT( __on_ping_timer() ) );
    __ping_timer->start( 100 );
    
    __connect_timer = new QTimer();
    QObject::connect( __connect_timer, SIGNAL( timeout() ), this, SLOT( __on_connect_timer() ) );
    __connect_timer->start( 1000 );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                     Creating of redises objects. Override this procedure to change LoRedis class.                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                   Создание объектов редиса. Перекройте эту функцию для изменения класса LoRedis.                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::_createRedises() {
    _pub_redis = new LoRedis();
    _sub_redis = new LoRedis();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Callback procedure after got some value from redis.                           *
// *                         It is empty in this class and should be overriden in the descendants.                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                           Callback-процедура после получения некоторого значения из редиса.                      *
// *                           Она в данном классе пустая, ее надо бы перекрывать в потомках.                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::_got_value( QString sproutName ) {
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Connection timer fired.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Срабатывание таймера соединения.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_connect_timer() {
    
    if ( ( ! __pub_redis_connected ) && ( _pub_redis ) ) _pub_redis->connect();
    if ( ( ! __sub_redis_connected ) && ( _sub_redis ) ) _sub_redis->connect();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          On the ping timer fire event.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                               Тычок таймера пинга.                                               *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_ping_timer() {
    
    if ( __pub_redis_connected ) {
        
        // Publish the last live time of this agent.
        // This time allows you to conclude whether the agent is running or not
        
        // Публикация последнего времени жизни этого агента.
        // Это время позволяет делать вывод, выполняется этот агент или нет.
        
        QDateTime dt = QDateTime::currentDateTime();
        QTime time = QTime::currentTime();
        QString repr = QString::number( dt.toTime_t() ) + "." + QString::number( time.msec() );
        QString channel = QString("agents.") + _name + ".ping";
        _pub_redis->publish( channel, repr );
        _pub_redis->set( channel, repr );
    };
    
    // In any case, it does not matter whether we are connected or not.
    // This is enought to call only one static class method independed of 
    // quantity of real objects.
    
    // В любом случае, не имеет значения, соединены мы или нет.
    // Достаточно просто одного вызова статической функции класса, не надо по 
    // каждому из объектов.
    
    LoRedis::processEvents();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      The publisher was connected to redis.                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Публикатор соединился с редисом.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_pub_redis_connected() {
    __pub_redis_connected = true;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      The subscriber was connected to redis.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Подписчик соединился с редисом.                                          *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_sub_redis_connected() {
    __sub_redis_connected = true;
    // _subscribe();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    The publisher was disconnected from redis.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Публикатор рассоединился с редисом.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_pub_redis_disconnected() {
    __pub_redis_connected = false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    The subscriber was disconnected from redis.                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Подписчик рассоединился с редисом.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_sub_redis_disconnected() {
    __sub_redis_connected = false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Someone from redises have an error.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        У кого-то из редисов возникла ошибка.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::__on_redis_error ( QString message ) {
    qDebug() << "AbstractAgentKernel::__on_error: " << message;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Is the publisher connected to redis?                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Соединен ли публикатор с редисом?                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractAgentKernel::isPublisherConnected() {
    return __pub_redis_connected;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Is the subscriber connected to redis?                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Соединен ли подписчик с редисом?                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractAgentKernel::isSubscriberConnected() {
    return __sub_redis_connected;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Subscribe function.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                Функция подписки.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

/*
void tengu::AbstractAgentKernel::__subscribe() {
    
    if ( __sub_redis_connected ) {
        
        bool locked = __reMutex.tryLock( 300 );
        
        if ( locked ) {
            
            for ( int i=0; i<__reactions.length(); i++ ) {
                reaction_t * reaction = __reactions.at(i);
                
                // We here only look at submitting an application for a subscription, but not for the fact 
                // of subscription itself.
                
                // Здесь смотрим только на подачу заявки на подписку, но не на сам факт подписки.
                
                if ( ! reaction->subscribtion_applicated ) {
                    _sub_redis->subscribe( reaction->channel );
                    reaction->subscribtion_applicated = true;
                };
            };
            
            __reMutex.unlock();
            
        } else {
            // Error handler for AbstractAgent.
            // Обработка ошибок для абстрактного агента.
            qDebug() << "AbstractAgent::_subscribe(): could not lock the mutex.";
        };
    };
}
*/

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Set activity for this agent.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Установка активности для данного агента.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::_setActivity(bool a) {
    __activity = a;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Is this agent active?                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Является ли данный агент активным?                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractAgentKernel::isActive() {
    return __activity;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Abstract agent cannot be used directly.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                              Абстрактный агент не может быть использован напрямую.                               *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractAgentKernel::usable() {
    return false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                      Public connect procedure. It should be called after full initialization.                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                   Публичная процедура соединения. Ее надо вызывать после полной инициализации.                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractAgentKernel::connect() {
    
    // Connect redises if they exists.
    // Соединение редисеров, если они есть.
    
    if ( _pub_redis ) _pub_redis->connect();
    if ( _sub_redis ) _sub_redis->connect();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Деструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractAgentKernel::~AbstractAgentKernel()
{
}

