#include "Cursors.h"
#include "Settings/Settings.h"
#include "Display/Grid.h"
#include "Menu/Menu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Cursors::PosU(Chan ch, int numCur)
{
    return CURsU_POS(ch, numCur) / (Grid::Bottom() == Grid::FullBottom() ? 1.0f : 2.0f);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Cursors::NecessaryDraw()
{
    return (CURsU_ENABLED || CURsT_ENABLED) && (CURS_SHOW || Menu::GetNameOpenedPage() == PageSB_Cursors_Set);
}
