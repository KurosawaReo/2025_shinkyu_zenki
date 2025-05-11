#include "Global.h"

//“–‚½‚è”»’è(ŽlŠp‚ÆŽlŠp)
BOOL IsHitBox(DBL_XY pos1, INT_XY size1, DBL_XY pos2, INT_XY size2) {
    
    //’†‰›Šî€À•W‚Å‚Ì”»’è.
    if (fabs(pos1.x - pos2.x) <= (size1.x + size2.x)/2 && 
        fabs(pos1.y - pos2.y) <= (size1.y + size2.y)/2)
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//“–‚½‚è”»’è(‰~‚Æ‰~)
BOOL IsHitCircle(DBL_XY pos1, int r1, DBL_XY pos2, int r2) {

}