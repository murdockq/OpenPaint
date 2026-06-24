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

#ifndef __SubTextToolPanel__
#define __SubTextToolPanel__

#include "OpenPaintGUI.h"

class SubTextToolPanel : public TextToolPanel
{
protected:
    virtual void OnFont( wxCommandEvent& event );
    virtual void OnSize( wxSpinEvent& event );
    virtual void OnBold( wxCommandEvent& event );
    virtual void OnItalic( wxCommandEvent& event );
    virtual void OnUnderline( wxCommandEvent& event );
public:
    SubTextToolPanel( wxWindow* parent );
};

#endif // __SubTextToolPanel__
