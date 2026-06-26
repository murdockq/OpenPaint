#ifndef __SizePicker__
#define __SizePicker__

#include <wx/bmpbuttn.h>
#include <wx/panel.h>
#include <wx/string.h>

class SizePickerButton : public wxPanel
{
public:
    SizePickerButton(wxWindow* parent, wxWindowID id,
                     int value, int min, int max,
                     const wxString& label = wxEmptyString,
                     const wxSize& size = wxDefaultSize);

    int GetValue() const { return m_value; }
    void SetValue(int value);
    void SetRange(int min, int max);

private:
    int m_value, m_min, m_max;
    wxString m_label;
    wxBitmapButton* m_button;

    void UpdatePreview();
    void OnButtonClick(wxCommandEvent& event);
    wxBitmap CreatePreviewBitmap(int size) const;
};

#endif // __SizePicker__
