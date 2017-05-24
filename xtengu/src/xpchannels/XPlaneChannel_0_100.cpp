// ********************************************************************************************************************
// *                                                                                                                  *
// *                     Channel for transform 0..100 integer values to 0..1 float values.                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                  Канал для преобразования целых значений 0..100 в вещественные значения 0..1                     *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 20 may 2017 at 12:10 *
// ********************************************************************************************************************

#include "XPlaneChannel_0_100.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XPlaneChannel_0_100::XPlaneChannel_0_100 ( QString aName, QString path ) 
    : XPlaneChannel ( aName, path, 0, 100 )
{

}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Setting an integer value.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Установка целочисленного значения.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneChannel_0_100::set ( int value ) {
    
    float f = ( float ) value;
    this->set( f );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Setting an float value.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Установка вещественного значения.                                      *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneChannel_0_100::set ( float value ) {
    
    if ( _dataref ) {
        
        float aValue = applyRestrictions( value );  
        aValue = aValue / 100.0;
        xplugin__log( QString("XPlaneChannel_0_100::set(float), value=") + QString::number(value) + ", aValue=" + QString::number( aValue ) );
        XPLMSetDataf( _dataref, aValue );
        
    };
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Деструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XPlaneChannel_0_100::~XPlaneChannel_0_100() {

}


