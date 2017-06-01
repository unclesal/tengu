// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       The main window of the Tengu Modeller.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Главное окно Tengu-моделлера.                                          *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 27 may 2017 at 08:26 *
// ********************************************************************************************************************

#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QLayout>
#include <QGraphicsScene>
#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QSettings>
#include <QRect>

#include "MainWindowLeft.h"
#include "MainWindowSchema.h"
#include "MainWindowRight.h"
#include "Constants.h"
#include "../guis.h"

namespace tengu {
    
    class MainWindow : public QMainWindow {

        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = 0);
            ~MainWindow();
            
        private:
        
            // Horizontal splitter for main window's elements.
            // Горизонтальный сплиттер для элементов главного окна.
            QSplitter * __hSplitter;
            
            QWidget * __centerWidget;
            MainWindowLeft * __left;
            MainWindowSchema * __schema;
            MainWindowRight * __right;
            QGraphicsScene * __canvas;
            
            QToolBar * __toolbar_buttons;
            QToolBar * __toolbar_elements_library;
            
            void __createMainMenu();
            void __createActions();
            void __createToolBar();
            void __createStatusBar();
            
            QAction * __actionQuit;
            
            void __restoreSettings();
            
            void closeEvent( QCloseEvent * event );
            void showEvent( QShowEvent * event );
            
        private slots:
            
            void __on_quit_request();            
                        
            
    };
    
};

