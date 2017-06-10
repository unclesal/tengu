// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Table MVC-model for agent's properties.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Табличная MVC-модель для свойств агента.                                *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 01 jun 2017 at 11:35 *
// ********************************************************************************************************************

#include "AgentPropertyModel.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Конструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AgentPropertyModel::AgentPropertyModel()
    : QAbstractItemModel()
{
    // __workspace = workspace;
    __rows = 0;
    __columns = 0;
    __item = nullptr;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Return the column count for this MVC-model.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     Вернуть число столбцов для данной MVC-модели.                                *
// *                                                                                                                  *
// ********************************************************************************************************************

int tengu::AgentPropertyModel::columnCount(const QModelIndex & parent ) const {
    return __columns;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Return model index for specivied element                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Вернуть индекс в модели для указанного элемента.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

QModelIndex tengu::AgentPropertyModel::index(int row, int column, const QModelIndex & parent ) const {

    QModelIndex res;
    return res;
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Get a parent for the child.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Вернуть родителя для данного дитяти.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

QModelIndex tengu::AgentPropertyModel::parent( const QModelIndex & child ) const {

    QModelIndex res;
    return res;
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Return the row count for this model element.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Вернуть число строк для данного элемента модели.                              *
// *                                                                                                                  *
// ********************************************************************************************************************

int tengu::AgentPropertyModel::rowCount( const QModelIndex & parent ) const {
    return __rows;
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Return data for this model index.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Вернуть данные для этого индекса.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

QVariant tengu::AgentPropertyModel::data(const QModelIndex & index, int role ) const {

    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Set appropriate agent for data model.                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Установка соответствующего агента для модели данных.                            *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AgentPropertyModel::setItem ( tengu::AbstractAgentItem * item ) {

    __item = item;
    
    // From top to bottom on the inheritance.
    // Сверху вниз по наследованию.
    
    TaskItem * taskItem = qobject_cast< TaskItem * >( item );
    if ( taskItem ) {
        
        // It was a Task class representation.
        // Это было представление класса Task.
        
        __columns = 2;
        __rows = 10;        
    };
    
    
    emit layoutChanged();
    
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AgentPropertyModel::~AgentPropertyModel() {
}


