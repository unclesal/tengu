// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Left piece of main window.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                 Левая часть главного окна.                                       *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 28 may 2017 at 15:20 *
// ********************************************************************************************************************

#pragma once

#include <QWidget>
#include <QLayout>
#include <QToolBox>

#include "WorkSpace.h"
#include "TreeStructure.h"

namespace tengu {
    
    class MainWindowLeft : public QWidget {
    
        Q_OBJECT
        
        public:
            MainWindowLeft( WorkSpace * ws );
            virtual ~MainWindowLeft();
            QToolBox * toolbox;
            TreeStructure * treeStructure;
            
        private:
            
    };
    
};

