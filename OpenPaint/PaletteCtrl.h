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

#ifndef __PaletteCtrl__
#define __PaletteCtrl__

#include <wx/colour.h>
#include <wx/panel.h>
#include <wx/clrpicker.h>

class PaletteCtrl : public wxPanel
{
protected:
	// Handlers for ColorPanel events.
	virtual void OnPalette( wxMouseEvent& event );
	virtual void OnForeground( wxMouseEvent& event );
	virtual void OnBackground( wxMouseEvent& event );
	
public:
	/** Constructor */
    PaletteCtrl( wxWindow* parent, int id = wxID_ANY, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, int style = wxTAB_TRAVERSAL );

};

#endif
