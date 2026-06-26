#include "SizePicker.h"

#include <wx/dcmemory.h>
#include <wx/popupwin.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/settings.h>

namespace
{
    const int PREVIEW_SIZE = 28;
    const int POPUP_WIDTH = 180;
    const int POPUP_HEIGHT = 90;
}

class SizePickerPopup : public wxPopupTransientWindow
{
public:
    SizePickerPopup(wxWindow* parent, SizePickerButton* owner,
                    int value, int min, int max, const wxString& label)
        : wxPopupTransientWindow(parent), m_owner(owner), m_min(min), m_max(max)
    {
        SetSize(POPUP_WIDTH, POPUP_HEIGHT);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        if (!label.IsEmpty())
        {
            wxStaticText* lbl = new wxStaticText(this, wxID_ANY, label,
                wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
            sizer->Add(lbl, 0, wxEXPAND | wxALL, 4);
        }

        wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

        m_slider = new wxSlider(this, wxID_ANY, value, min, max,
            wxDefaultPosition, wxSize(120, -1), wxSL_HORIZONTAL | wxSL_LABELS);
        rowSizer->Add(m_slider, 1, wxEXPAND | wxALL, 4);

        m_spin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, min, max, value);
        rowSizer->Add(m_spin, 0, wxALIGN_CENTER_VERTICAL | wxALL, 4);

        sizer->Add(rowSizer, 0, wxEXPAND);

        SetSizer(sizer);
        Layout();

        m_slider->Connect(wxEVT_COMMAND_SLIDER_UPDATED,
            wxCommandEventHandler(SizePickerPopup::OnSlider), NULL, this);
        m_spin->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED,
            wxSpinEventHandler(SizePickerPopup::OnSpin), NULL, this);
    }

    void OnDismiss() override
    {
        m_owner->SetValue(m_spin->GetValue());
    }

private:
    SizePickerButton* m_owner;
    int m_min, m_max;
    wxSlider* m_slider;
    wxSpinCtrl* m_spin;

    void OnSlider(wxCommandEvent&)
    {
        m_spin->SetValue(m_slider->GetValue());
    }

    void OnSpin(wxSpinEvent&)
    {
        m_slider->SetValue(m_spin->GetValue());
    }
};

wxBitmap SizePickerButton::CreatePreviewBitmap(int size) const
{
    wxBitmap bmp(PREVIEW_SIZE, PREVIEW_SIZE);
    wxMemoryDC dc(bmp);
    dc.SetBackground(*wxLIGHT_GREY_BRUSH);
    dc.Clear();

    dc.SetPen(*wxBLACK_PEN);
    dc.SetBrush(*wxBLACK_BRUSH);

    int cx = PREVIEW_SIZE / 2;
    int cy = PREVIEW_SIZE / 2;
    double ratio = (m_max > m_min) ? double(size - m_min) / (m_max - m_min) : 0.0;
    int r = 2 + int(ratio * 10.0);
    if (r < 1) r = 1;

    dc.DrawCircle(cx, cy, r);

    dc.SelectObject(wxNullBitmap);
    return bmp;
}

void SizePickerButton::UpdatePreview()
{
    m_button->SetBitmapLabel(CreatePreviewBitmap(m_value));
    m_button->SetToolTip(wxString::Format(wxT("%s: %d"), m_label, m_value));
}

void SizePickerButton::OnButtonClick(wxCommandEvent&)
{
    SizePickerPopup* popup = new SizePickerPopup(this, this,
        m_value, m_min, m_max, m_label);
    wxPoint btnPos = m_button->GetScreenPosition();
    wxSize btnSize = m_button->GetSize();
    popup->SetPosition(wxPoint(btnPos.x, btnPos.y + btnSize.y));
    popup->Popup();
}

SizePickerButton::SizePickerButton(wxWindow* parent, wxWindowID id,
                                   int value, int min, int max,
                                   const wxString& label, const wxSize& size)
    : wxPanel(parent, id, wxDefaultPosition,
              size.IsFullySpecified() ? size : wxSize(PREVIEW_SIZE + 8, PREVIEW_SIZE + 8))
    , m_value(value), m_min(min), m_max(max), m_label(label)
{
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    m_button = new wxBitmapButton(this, wxID_ANY, CreatePreviewBitmap(m_value),
        wxDefaultPosition, wxSize(PREVIEW_SIZE, PREVIEW_SIZE), wxBU_AUTODRAW);
    sizer->Add(m_button, 0, wxALL, 2);
    SetSizer(sizer);
    Layout();
    SetMinSize(wxSize(PREVIEW_SIZE + 8, PREVIEW_SIZE + 8));

    m_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(SizePickerButton::OnButtonClick), NULL, this);
}

void SizePickerButton::SetValue(int value)
{
    if (value < m_min) value = m_min;
    if (value > m_max) value = m_max;
    if (value == m_value) return;
    m_value = value;
    UpdatePreview();

    wxCommandEvent evt(wxEVT_COMMAND_SPINCTRL_UPDATED, GetId());
    evt.SetInt(m_value);
    evt.SetEventObject(this);
    ProcessWindowEvent(evt);
}

void SizePickerButton::SetRange(int min, int max)
{
    m_min = min;
    m_max = max;
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;
    UpdatePreview();
}
