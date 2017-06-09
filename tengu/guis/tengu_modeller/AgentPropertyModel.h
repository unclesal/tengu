// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Table MVC-model for agent's properties.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Табличная MVC-модель для свойств агента.                                *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 01 jun 2017 at 11:32 *
// ********************************************************************************************************************

#pragma once

#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>

// #include "WorkSpace.h"
#include "AbstractAgent.h"

namespace tengu {

    class AgentPropertyModel : public QAbstractItemModel {
        
        Q_OBJECT
        
        public:
            
            AgentPropertyModel();
            virtual ~AgentPropertyModel();
            
            int columnCount(const QModelIndex & parent = QModelIndex() ) const;
            int rowCount( const QModelIndex &parent = QModelIndex() ) const;
            QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
            QModelIndex parent( const QModelIndex & child ) const;
            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
            
            void setAgent( AbstractAgent * agent );
            
        private:
            
            // WorkSpace * __workspace;
            AbstractAgent * __agent;
            int __rows;
            int __columns;
    };
};

