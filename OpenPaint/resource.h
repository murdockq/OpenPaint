#ifndef __Resource_H__
#define __Resource_H__

/** This is a non-windows platform include file to 
    allow xpm file to be built into the project as
    a resource.
*/

#ifndef _WINDOWS
#include "res/std.xpm"
#include "res/document-new.xpm"
#include "res/document-open.xpm"
#include "res/document-save.xpm"
#include "res/edit-undo.xpm"
#include "res/edit-redo.xpm"
#include "res/go-next.xpm"

#include    "res/color-fill.xpm"
#include    "res/color-gradient.xpm"
#include    "res/color-picker.xpm"
#include    "res/draw-airbrush.xpm"
#include    "res/draw-brush.xpm"
#include    "res/draw-eraser.xpm"
#include    "res/draw-freehand.xpm"
#include    "res/draw-polygon.xpm"
#include   "res/draw-ellipse.xpm"
#include   "res/draw-rectangle.xpm"
#include   "res/draw-rectangle-rounded.xpm"

#include   "res/draw-text.xpm"

#include   "res/page-magnifier.xpm"
#include   "res/select-continuous-area.xpm"
#include   "res/select-lasso.xpm"
#include    "res/select-rectangular.xpm"
#include    "res/transform-crop-and-resize.xpm"
#include    "res/transform-flip.xpm"
#include    "res/transform-flip-vertical.xpm"
#include    "res/transform-scale.xpm"
#include    "res/linked.xpm"
#include    "res/unlinked.xpm"
#endif

#endif


