// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       The main window of the Tengu Modeller.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Главное окно Tengu-моделлера.                                          *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 27 may 2017 at 08:27 *
// ********************************************************************************************************************

#include "MainWindow.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    
    setWindowTitle( tr("Tengu modeller") );
    setWindowIcon( QIcon( QPixmap(":tengu_32.png") ) );
    
    __workSpace = new WorkSpace( "TheTopWorkspace");
    __agentPropertyModel = new AgentPropertyModel();
    
    QVBoxLayout * lay = new QVBoxLayout();
    lay->setMargin( 0 );
    lay->setSpacing( 0 );
    
    __centerWidget = new QWidget();
    __centerWidget->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ) );
    __centerWidget->setMinimumSize( QSize(800, 600 ) );
    __centerWidget->setLayout( lay );
    
    setCentralWidget( __centerWidget );
    
    __hSplitter = new QSplitter();
    __hSplitter->setHandleWidth( SPLITTERS_HANDLE_WIDTH );
    __hSplitter->setLineWidth( SPLITTERS_LINE_WIDTH );
    
    lay->addWidget( __hSplitter );
    
    __scene = new QGraphicsScene();
    
    
    Task * t = new Task("Task");
    TaskItem * i = new TaskItem( t );
    i->setX( 10 );
    i->setY( 10 );
    __scene->addItem( i );
    
    
    /*
    VehicleItem * w = new VehicleItem( new Vehicle( nullptr, "Vehicle") );
    __canvas->addItem( w );
    w->setX( -20 );
    w->setY( 50 );
    AbstractAgentItem * a = new AbstractAgentItem( __topModel );
    __canvas->addItem( a );
    a->setX( 20 );
    a->setY( -50 );
    */
        
    __left = new MainWindowLeft();
    __createSchema();
    
    __right = new MainWindowRight();
    
    __right->setPropertiesDataModel( __agentPropertyModel );
    
    __hSplitter->addWidget( __left );
    __hSplitter->addWidget( __schema );
    __hSplitter->addWidget( __right );
            
    __createActions();
    __createMainMenu();
    __createToolBar();
    __createStatusBar();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Action's constructor.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                              Конструктор действий программы.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__createActions() {
    
    __actionQuit = new QAction( tr( "Quit" ), this );
    __actionQuit->setIcon( QIcon( QPixmap(":door_open_16.png") ) );
    QObject::connect( __actionQuit, SIGNAL(triggered()), this, SLOT( __on_quit_request() ) );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               The main menu constructor.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                               Конструктор главного меню.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__createMainMenu() {
    
    QMenuBar * mb = menuBar();
    
    QMenu * menuMain = new QMenu("File");
    menuMain->addAction( __actionQuit );
    mb->addMenu( menuMain );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              The status bar constructor.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                              Конструктор строки статуса.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__createStatusBar() {
    QStatusBar * sb = statusBar();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                The toolbar constructor.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Конструктор инструментальной панели.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__createToolBar() {
    
    __toolbar_file = new QToolBar();
    
    addToolBar( Qt::TopToolBarArea, __toolbar_file );
    QToolBar * tb1 = new QToolBar();
    addToolBar( Qt::TopToolBarArea, tb1 );
        
    addToolBarBreak();
    
    __toolbar_elements_library = new QToolBar();
    addToolBar( Qt::TopToolBarArea, __toolbar_elements_library );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                           The constructor of model's schama (graphical view of the model).                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                               Конструктор схемы (графического представления модели).                             *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__createSchema() {
    __schema = new MainWindowSchema( __scene );
    QObject::connect( __schema, SIGNAL( signalItemPressed( AbstractAgentItem * )), this, SLOT( __on_schema_item_pressed ( AbstractAgentItem * ) ) );
    QObject::connect( __schema, SIGNAL( signalItemDoubleClicked( AbstractAgentItem * )), this, SLOT( __on_schema_item_double_clicked( AbstractAgentItem * ) ) );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                              Some element was (once or single) clicked on the schema.                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         На схеме был нажат какой-то элемент.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__on_schema_item_pressed ( tengu::AbstractAgentItem * item ) {
    qDebug() << "MainWindow:: on schema item pressed.";
    AbstractAgent * agent = item->agent();
    __agentPropertyModel->setAgent( agent );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                     Some element was double clicked on the schema.                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       На элементе схемы был двойной щелчок мыши.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__on_schema_item_double_clicked ( tengu::AbstractAgentItem* item ) {

}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Request to quit (exit) from program                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Требование выхода из программы.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__on_quit_request() {
    qApp->quit();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Restore the settings of main window.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Восстановить установки главного окна.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::__restoreSettings() {
            
    QSettings s ( TENGU_ORGANIZATION, TENGU_MODELLER_APPLICATION );
    s.beginGroup("MainWindow");    
    
    // The size of main window.
    // Размеры главного окна.

    QRect mainWindowGeometry = s.value("MainWindowGeometry", QRect(0,0,0,0) ).toRect();
    if ( 
        ( mainWindowGeometry.height() > 100 ) 
        && ( mainWindowGeometry.width() > 100 ) 
        && ( mainWindowGeometry.x() >= 0 )
        && ( mainWindowGeometry.y() >= 0 )
    ) {
        this->setGeometry( mainWindowGeometry );
    };
    
    // The sizes of splitter ( the width of left and right pieces of screen ).
    // Размеры сплиттера (ширина левой и правой частей экрана).
    
    QList<int> splitterSizes;    
    int lw = s.value("LeftWidth", -1 ).toInt();
    int rw = s.value("RightWidth", -1 ).toInt();
    if ( ( lw < 0 ) || ( lw > size().width() ) ) lw = size().width() / 5;
    if ( ( rw < 0 ) || ( rw > size().width() ) ) rw = size().width() / 5;
    
    splitterSizes.append( lw );
    splitterSizes.append( size().width() - lw - rw );
    splitterSizes.append( rw );
    __hSplitter->setSizes( splitterSizes );
    
    // The heights of right part of the screen (where agent's properties is).
    // Высоты правой части экрана (где свойства агента).
    
    QList<int> rs;
    int rTop  = s.value( "AgentsPropertiesHeight", -1 ).toInt();
    if ( ( rTop <= 0 ) || (rTop > size().height() ) ) rTop = 3 * size().height() / 4;
    rs.append( rTop );
    
    int rBottom = s.value( "RightBottomHeight", -1 ).toInt();
    if ( ( rBottom <= 0 ) || (rBottom > size().height() ) ) rBottom = size().height() / 4;
    rs.append( rBottom );
    
    __right->setComponentsHeight( rs );    
        
    s.endGroup();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Show main window event.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Событие появления окна на экране.                                      *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::showEvent( QShowEvent * event ) {
    __restoreSettings();
    QMainWindow::showEvent( event );    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Close main window event.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Событие закрытия главного окна.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindow::closeEvent ( QCloseEvent* event ) {
    
    QWidget::closeEvent ( event );
    
    
    QSettings s ( TENGU_ORGANIZATION, TENGU_MODELLER_APPLICATION );
    
    s.beginGroup("MainWindow");
    
    s.setValue("MainWindowGeometry", geometry() );
    
    s.setValue( "LeftWidth", __left->size().width() );
    s.setValue( "RightWidth", __right->size().width() );
    
    QPair<int,int> right = __right->getComponentsHeights();
    s.setValue( "AgentsPropertiesHeight", right.first );
    s.setValue( "RightBottomHeight", right.second );
    
    s.endGroup();
    
    s.sync();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::MainWindow::~MainWindow() {
}
