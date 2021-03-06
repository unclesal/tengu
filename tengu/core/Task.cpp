// ********************************************************************************************************************
// *                                                                                                                  *
// *                       The task. The agent which can calculate something using QJSEngine.                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                    Задача. Агент, который может что-нибудь вычислять, используя QJSEngine.                       *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 09 jun 2017 at 09:57 *
// ********************************************************************************************************************

#include "Task.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The constructor.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Конструктор.                                               *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Task::Task () 
    : SproutableAgent()
{
    _class_name = "Task";
    _entity_type = ET_Task;
    
    // __start_condition = tr("// At least this one function must be exists") + "\n\nfunction start() {\n    return ( true );\n};\n";
    // __algorythm = tr("// At least this one functiom must be exists") + "\n\nfunction step() {\n};\n";
    // __stop_condition = tr("// At least this one function must be exists") + "\n\nfunction stop() {\n    return (true);\n};\n";

    __qmlEngine = nullptr;
    __qmlObject = nullptr;

    __create_qml();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Set default QML value for this task.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                            Установка начального значения QML для данной задачи.                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Task::__create_qml() {
    
    __qml = "import QtQuick 2.4\n\n";
    __qml += "Item {\n";
    __qml += "    id : " + getSystemName() + "\n";
    
    __qml += "    // " + tr("Start condition for this task.") + "\n";
    __qml += "    function start() {\n";
    __qml += "        return true\n";
    __qml += "    }\n\n";
    
    __qml += "    // " + tr("One step of execution process for this task.") + "\n";
    __qml += "    function step() {\n";
    __qml += "    }\n\n";
    
    __qml += "    // " + tr ("Stop condition for this task.") + "\n";
    __qml += "    function stop() {\n";
    __qml += "        return true;\n";
    __qml += "    }\n\n";
    
    __qml += "} // Item\n";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         The execution process was failed.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Процесс выполнения завершился неудачно.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Task::__failed_with_errors ( QQmlComponent & component ) {
    
    QString msg = tr("Execution failed. ");
    
    QList<QQmlError> errors = component.errors();
    if ( errors.count() > 0 ) {
        QQmlError fe = errors.at(0);
        msg += tr("Line: ") + fe.line() + tr(", column: ") + fe.column() + ", msg=" + fe.toString();
    };
    
    emit signalFailed( msg );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                            Has QML Object such method?                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Есть ли в QML объекте такой метод?                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Task::__qmlObject__has_method ( QString methodName ) {
    
    if ( ! __qmlObject ) return false;
    
    const QMetaObject* metaObject = __qmlObject->metaObject();
    QStringList methods;
    for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
        methods << QString::fromLatin1(metaObject->method(i).name());
    
    return ( methods.contains( methodName ) );        
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Prepare the task for launch.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                              Подготовка задачи к запуску.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Task::_prepare_for_execution() {
    
    SproutableAgent::_prepare_for_execution();
    
    QQmlEngine * qmlEngine = this->qmlEngine(); // new QQmlEngine( parent );
    
    if ( ! qmlEngine ) {
        emit signalFailed( tr("The QML Engine pointer is null.") );
        return;
    }
    
    QQmlComponent component( qmlEngine );
    
    component.setData( __qml.toUtf8(), QUrl());
    if ( component.isError() ) {
        __failed_with_errors( component );
        return;
    };
    
    __qmlObject = component.create();
    
    if ( ! __qmlObject ) {
        emit signalFailed( tr("__qmlObject is null") );
    };
        
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           One step of task running process.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                               Один шаг выполнения задачи.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Task::_step() {
    qDebug() << "Task::_step()";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Got some value from some sprout.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Получение некоторого значения от некоторого спраута.                             *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Task::_sprout_got_value ( QString sproutSysName, QVariant value ) {
    
    qDebug() << "Task::_sprout_got_value, name=" << sproutSysName << ", value=" << value;
    QString methodName = QString("on__") + sproutSysName + "__got_value";
    
    if ( ! __qmlObject ) return;
    if ( ! __qmlObject__has_method( methodName ) ) {
        qDebug() << "Task::_sprout_got_value, no such method " << methodName;
        return;
    }
    
    QMetaObject::invokeMethod( __qmlObject, methodName.toUtf8().data(),
        Q_ARG( QVariant, value )
    );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Try to activate this task.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Попытка активации данной задачи.                                      *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Task::_tryActivate() {
    
    qDebug() << "Task::_tryActivate, " << getHumanName() << ", isFocused? " << isFocused() << ", isActive? " << isActive();
        
    if ( _activity ) {
        emit signalFailed( tr("Call tryActivate method for already active task ") + getHumanName() );
        return false;
    };
    
    if ( ! __qmlObject ) {
        emit signalFailed( tr("Call tryActivate, but qml object is emtpy. Task is ") + getHumanName() );
        return false;
    };
    
    QVariant retValue;
    
    // Is there a "start" method?
    // Есть ли метод "старт"?
    
    if ( ! __qmlObject__has_method( "start" ) ) {
        emit signalFailed( tr("Task ") + getHumanName() + tr(", method \"start\" not found.") );
        return false;
    };
        
    QMetaObject::invokeMethod( __qmlObject, "start",
        Q_RETURN_ARG(QVariant, retValue)
    );
    
    if ( ( retValue.isNull() ) || ( ! retValue.isValid() ) ) {
        emit signalFailed( tr("Task::_tryActivate(), method start has returned nothing for the task \"") + getHumanName() + "\"");
        return false;
    };
        
    bool result = retValue.toBool();
    
    if ( result ) {
        
        // Activate this task.
        // Активация этой задачи.
        
        setFocus( false, this );
        
        _activity = true;
        emit signalActivated( _activity );
        
        // After activation we need to do at least one execution step.
        // После активации нам надо сделать как минимум один шаг выполнения.
        
        _step();
        
        
    };
        
    return result;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Free this task resources after execution.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Освободить ресурсы данной задачи после ее выполнения.                           *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Task::_free_after_execution() {
    qDebug() << "Free task after execution";
    SproutableAgent::_free_after_execution();
    
    if ( __qmlObject ) {
        delete( __qmlObject );
        __qmlObject = nullptr;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Convert task to JSON object.                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Преобразование задачи в объект JSON.                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

QJsonObject tengu::Task::toJSON() {
    
    QJsonObject o = SproutableAgent::toJSON();
    
    o[ JSON_COLLECTION_ELEMENT ] = "tasks";
    
    // o["start_condition"] = __start_condition;
    // o["algorythm"] = __algorythm;
    // o["stop_condition"] = __stop_condition;
    
    o["qml"] = __qml;
    
    return o;
    
}

// ********************************************************************************************************************
// *                                                                                                                  * 
// *                                Convert JSON representation to object's data field values.                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     Преобразование из JSONа в поля этого объекта.                                *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Task::fromJSON(QJsonObject json) {
    
    bool result = SproutableAgent::fromJSON( json );
    
    // if ( json.contains("start_condition") ) __start_condition = json.value("start_condition").toString();
    // if ( json.contains("algorythm") ) __algorythm = json.value("algorythm").toString();
    // if ( json.contains("stop_condition") ) __stop_condition = json.value("stop_condition").toString();
    
    if ( json.contains("qml") ) __qml = json.value("qml").toString();
    
    return result;
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Return start condition                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                               Вернуть условие старта задачи                                      *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
QString tengu::Task::startCondition() {

    return __start_condition;
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   Set start condition.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                             Установить условие старта задачи.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::Task::setStartCondition( QString start ) {

    __start_condition = start;
    _somethingChanged();
    
};
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Return the task algorythm                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Вернуть алгоритм задачи.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
QString tengu::Task::algorythm() {

    return __algorythm;

};
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Set the task algorythm.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Установить алгоритм выполнения задачи.                                *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::Task::setAlgorythm( QString alg ) {

    __algorythm = alg;
    _somethingChanged();
    
};
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Return the stop task condition.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                              Вернуть условие остановки задачи.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
QString tengu::Task::stopCondition() {

    return __stop_condition;
    
};
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Set the stop task condition.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Установить условие останова задачи.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::Task::setStopCondition( QString stop ) {

    __stop_condition = stop;
    _somethingChanged();
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Return the QML( script contents ) for the task.                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Вернуть QML ( скриптовое содержимое ) этой задачи.                              *
// *                                                                                                                  *
// ********************************************************************************************************************

QString tengu::Task::qml() {

    return __qml;
    
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Set QML (script contents ) for this task.                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// * Установить QML ( скриптовое содержимое ) данной задачи. *
// * *
// ********************************************************************************************************************

void tengu::Task::setQml ( QString qml ) {
    
    __qml = qml;
    _somethingChanged();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                     The destructor.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                        Деструктор.                                               *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Task::~Task() {
    
    if ( __qmlObject ) {
        delete( __qmlObject );
        __qmlObject = nullptr;
    };
    
}


