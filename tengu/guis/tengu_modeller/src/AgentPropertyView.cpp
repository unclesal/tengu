// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        The MVC-based view for agent property.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Основанное на MVC представление свойств агента.                                *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 01 jun 2017 at 10:18 *
// ********************************************************************************************************************

#include "AgentPropertyView.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The constructor.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Конструктор.                                               *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AgentPropertyView::AgentPropertyView(QWidget * parent) 
    : QTableView( parent )
{
    horizontalHeader()->hide();
    verticalHeader()->hide();
    
    QHeaderView * vh = verticalHeader();
    vh->setSectionResizeMode(QHeaderView::Fixed);
    vh->setDefaultSectionSize( 16 );    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                 Resize event handler.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Обработчик события изменения размеров.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AgentPropertyView::resizeEvent ( QResizeEvent* event ) {
    
    QAbstractItemView::resizeEvent ( event );    
    adjustColumnWidth();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                 Adjusting column width                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                Подгонка ширины столбцов.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AgentPropertyView::adjustColumnWidth() {    
    int nameColumnWidth = round( width() / 2.5 );
    int valueColumnWidth = width() - nameColumnWidth - 3;
    setColumnWidth( 0, nameColumnWidth );
    setColumnWidth( 1, valueColumnWidth );        
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                     The destructor.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AgentPropertyView::~AgentPropertyView() {
}

