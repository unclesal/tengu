// ********************************************************************************************************************
// *                                                                                                                  *
// *      The top level for modelling of a system: a set of agents and it's states for graphics representation.       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *    Верхний уровень моделирования системы: множество агентов и их состояний для графического представления.       *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 02 jun 2017 at 16:47 *
// ********************************************************************************************************************

#include "WorkSpace.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The constructor.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Конструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::WorkSpace::WorkSpace()
    : AbstractAgent()
{
    setSystemName( tr("Workspace") );
    setHumanName( tr("Workspace") );
    _entity_type = ET_Workspace;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Overrided function for add a child into workspace                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                            Перекрытая функция для добавления ребенка в рабочее пространство.                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::WorkSpace::addChild ( tengu::AbstractAgent * child ) {
    
    tengu::AbstractAgent::addChild ( child );
    
    QList<AbstractAgent * > hisChildren = children();
    
    Vehicle * vehicle = dynamic_cast<Vehicle * > ( child );
    
    if ( vehicle ) {
        
        // Automatic naming for vehicles.
        // Автоматическое именование "самоходок".
        
        int vehiclesCount = 0;
        for ( int i=0; i<hisChildren.count(); i++ ) {
            AbstractAgent * och = hisChildren.at(i);
            Vehicle * vch = dynamic_cast< Vehicle * > ( och );
            if ( vch ) vehiclesCount ++;
        };
        
        if ( child->getSystemName().isEmpty() ) child->setSystemName( tr("Vehicle_") + QString::number( vehiclesCount ) );
        if ( child->getHumanName().isEmpty() ) child->setHumanName( tr("Vehicle ") + QString::number( vehiclesCount ) ) ;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Delete workspace children.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Удаление детей из рабочего пространства.                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::WorkSpace::deleteChildren() {
    
    // AbstractAgent::deleteChildren();    
    
    XPlaneSimulator * xp_simulator = nullptr;
    
    foreach( AbstractAgent * child, _children ) {
        
        // Delete all but not an xplane simulator
        // Удаляем всех но не X-Plane симулятор.
        
        XPlaneSimulator * cur = dynamic_cast< XPlaneSimulator * >( child );
        if ( ! cur ) {
            removeChild( child );
            delete( child );
        } else xp_simulator = cur;
    };
    
    _children.clear();    
    
    if ( xp_simulator ) _children[ xp_simulator->getUUID() ] = xp_simulator;
    
    
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::WorkSpace::~WorkSpace() {
}
