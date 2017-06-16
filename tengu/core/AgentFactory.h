// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Agent factory, agent's classes recognizer.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   "Фабрика агентов", распознавание классов агентов.                              *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 16 jun 2017 at 09:40 *
// ********************************************************************************************************************

#pragma once

#include <QJsonObject>
#include <QDebug>

#include "AbstractStorageableEntity.h"
#include "AbstractAgent.h"
#include "ProcessStart.h"
#include "ProcessStop.h"
#include "Process.h"
#include "Task.h"

namespace tengu {
    
    class AgentFactory {
        
        public:
            // static bool hasAgent( QJsonObject json );
            static AbstractStorageableEntity * createEntity( QJsonObject json );
        
    };
    
};
