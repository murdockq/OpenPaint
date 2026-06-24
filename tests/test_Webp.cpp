// Round-trip test for WebP support via wxImage.
//
// wxInitAllImageHandlers() does not register the WebP handler in
// wxWidgets 3.2.1+, so OpenPaintMainApp::OnInit does it explicitly. This
// test exercises the same code path and confirms libwebp is actually linked
// in, not just compiled. The whole file is gated on wxUSE_LIBWEBP so it
// compiles to an empty translation unit on wxWidgets builds without libwebp.

#include <catch2/catch_test_macros.hpp>

#if defined(wxUSE_LIBWEBP) && wxUSE_LIBWEBP

#include <wx/image.h>
#include <wx/imagwebp.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#include <cstdio>
#include <string>

namespace {

wxImage MakeTestImage(int w, int h)
{
    wxImage img(w, h);
    unsigned char* data = img.GetData();
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            data[(y * w + x) * 3 + 0] = static_cast<unsigned char>((x * 7 + y * 3) & 0xFF);
            data[(y * w + x) * 3 + 1] = static_cast<unsigned char>((x * 5 + y * 11) & 0xFF);
            data[(y * w + x) * 3 + 2] = static_cast<unsigned char>((x * 13 + y * 2) & 0xFF);
        }
    }
    return img;
}

std::string MakeTempWebpPath()
{
    wxFileName name(wxStandardPaths::Get().GetTempDir(),
                    wxT("openpaint_webp_test"),
                    wxT("webp"));
    return std::string(name.GetFullPath().mb_str());
}

} // namespace

TEST_CASE("wxImage can save and reload a .webp file", "[webp]")
{
    const std::string path = MakeTempWebpPath();
    wxImage img = MakeTestImage(33, 17);

    // Force lossless encoding so the test can compare pixels exactly. The
    // GUI uses wxWidgets' default (lossy) settings; we only need to verify
    // the encoder/decoder round-trips, not the lossy quality.
    img.SetOption(wxIMAGE_OPTION_WEBP_FORMAT, static_cast<int>(wxWebPImageFormat::Lossless));
    img.SetOption(wxIMAGE_OPTION_WEBP_QUALITY, 100);
    REQUIRE(img.SaveFile(wxString::FromUTF8(path.c_str()), wxBITMAP_TYPE_WEBP));

    wxImage loaded;
    REQUIRE(loaded.LoadFile(wxString::FromUTF8(path.c_str()), wxBITMAP_TYPE_WEBP));
    REQUIRE(loaded.GetWidth() == 33);
    REQUIRE(loaded.GetHeight() == 17);

    const unsigned char* o = img.GetData();
    const unsigned char* l = loaded.GetData();
    for (int i = 0; i < 33 * 17 * 3; ++i)
    {
        REQUIRE(static_cast<int>(o[i]) == static_cast<int>(l[i]));
    }

    std::remove(path.c_str());
}

#endif // wxUSE_LIBWEBP
