// ********************************************************************************************************************
// *                                                                                                                  *
// *                       The start point for process. There should be only one within the process.                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                          Точка старта процесса. Должна быть только одна в пределах процесса.                     *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 09 jun 2017 at 10:39 *
// ********************************************************************************************************************

#include "ProcessStart.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ProcessStart::ProcessStart ( QString systemName ) 
    : AbstractAgent ( systemName )
{

}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ProcessStart::~ProcessStart() {

}
