// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Control of right rudder's position.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Управление положением правого руля направления.                             *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 10 may 2017 at 16:04 *
// ********************************************************************************************************************

#include "XChRightRudder.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XChRightRudder::XChRightRudder() 
    : XChFloatArray ( "RightRudder" , "sim/flightmodel/controls/rudd_def" , -60 , 60 )
{
    // The right rudder for "classique" model.
    // Правый руддер "классической" модельки.
    
    _templateArray[ 19 ] = 1;
    
    // The right ruder for new model.
    // Правый руддер новой модельки.
    
    _templateArray[ 21 ] = -1;
    
    // The little right down rudder for new model.
    // Правый нижний руддерок новой модельки.
    
    _templateArray[ 23 ] = -1;

}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XChRightRudder::~XChRightRudder() {

}


