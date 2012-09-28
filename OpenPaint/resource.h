/*
 * OpenPaint
 * www.sourceforge.net/projects/openpaint
 *
 * Copyright (C) 2007, Steven Jedlicka
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

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
#include "res/go-next.xpm"

#include    "res/color-fill.xpm"
#include    "res/color-gradient.xpm"
#include    "res/color-picker.xpm"
#include    "res/draw-airbrush.xpm"
#include    "res/draw-brush.xpm"
#include    "res/draw-eraser.xpm"
#include    "res/draw-freehand.xpm"
#include    "res/draw-polygon.xpm"
#include   "res/draw-polyline.xpm"
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

