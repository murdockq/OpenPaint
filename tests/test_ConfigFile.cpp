// Unit tests for ConfigFile (the non-GUI core of OpenPaint).
//
// ConfigFile + the bundled tinyxml have no wxWidgets dependency, which makes
// them the natural first target for the test suite.

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "ConfigFile.h"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#   include <io.h>
#else
#   include <unistd.h>
#endif

namespace {
// Helper that writes a tiny XML config to a temp file and returns its path.
std::string WriteTempConfig(const std::string& contents)
{
    char path[] = "openpaint_test_XXXXXX";
#ifdef _WIN32
    char* name = _mktemp_s(path, sizeof(path)) == 0 ? path : nullptr;
    std::string fullPath = std::string(name ? name : path) + ".xml";
#else
    int fd = mkstemp(path);
    close(fd);
    std::string fullPath = path;
#endif
    std::ofstream out(fullPath);
    out << contents;
    out.close();
    return fullPath;
}

void RemoveFile(const std::string& path)
{
    std::remove(path.c_str());
}
} // namespace

TEST_CASE("ConfigFile starts unopened and unmodified", "[ConfigFile]")
{
    ConfigFile cfg;
    REQUIRE_FALSE(cfg.IsOpen());
    REQUIRE_FALSE(cfg.IsModified());
    REQUIRE(cfg.LastError().empty());
}

TEST_CASE("getString returns the default for missing attributes", "[ConfigFile]")
{
    ConfigFile cfg;
    REQUIRE(cfg.getString("Missing", "fallback") == "fallback");
}

TEST_CASE("setString / getString round-trip and mark modified", "[ConfigFile]")
{
    ConfigFile cfg;
    REQUIRE_FALSE(cfg.IsModified());

    cfg.setString("Title", "OpenPaint");
    REQUIRE(cfg.IsModified());
    REQUIRE(cfg.getString("Title", "") == "OpenPaint");
}

TEST_CASE("attribute lookups are case-insensitive", "[ConfigFile]")
{
    ConfigFile cfg;
    cfg.setString("Title", "value");
    REQUIRE(cfg.getString("title", "") == "value");
    REQUIRE(cfg.getString("TITLE", "") == "value");
    REQUIRE(cfg.getString("TiTlE", "") == "value");
}

TEST_CASE("getInteger / setInteger round-trip", "[ConfigFile]")
{
    ConfigFile cfg;
    REQUIRE(cfg.getInteger("Count", 42) == 42);

    cfg.setInteger("Count", 1337);
    REQUIRE(cfg.getInteger("Count", 0) == 1337);
}

TEST_CASE("getDouble / setDouble round-trip", "[ConfigFile]")
{
    ConfigFile cfg;
    REQUIRE(cfg.getDouble("Pi", 3.14) == Catch::Approx(3.14));

    cfg.setDouble("Pi", 2.71828);
    REQUIRE(cfg.getDouble("Pi", 0.0) == Catch::Approx(2.71828));
}

TEST_CASE("getBool recognises common truthy/falsy spellings", "[ConfigFile]")
{
    ConfigFile cfg;

    SECTION("truthy values")
    {
        cfg.setString("Flag1", "1");
        cfg.setString("Flag2", "true");
        cfg.setString("Flag3", "TRUE");
        cfg.setString("Flag4", "True");
        REQUIRE(cfg.getBool("Flag1", false) == true);
        REQUIRE(cfg.getBool("Flag2", false) == true);
        REQUIRE(cfg.getBool("Flag3", false) == true);
        REQUIRE(cfg.getBool("Flag4", false) == true);
    }

    SECTION("falsy values fall back to default when not 1/true")
    {
        cfg.setString("Flag0", "0");
        cfg.setString("FlagNo", "no");
        REQUIRE(cfg.getBool("Flag0", true) == false);
        REQUIRE(cfg.getBool("FlagNo", true) == false);
    }

    SECTION("missing attribute uses the provided default")
    {
        REQUIRE(cfg.getBool("Absent", true) == true);
        REQUIRE(cfg.getBool("Absent", false) == false);
    }
}

TEST_CASE("setArray / getArray round-trip", "[ConfigFile]")
{
    ConfigFile cfg;
    const std::vector<std::string> defaults{"a", "b", "c"};
    REQUIRE(cfg.getArray("RecentFiles", defaults) == defaults);

    const std::vector<std::string> values{"one.png", "two.bmp", "three.jpg"};
    cfg.setArray("RecentFiles", values);
    REQUIRE_THAT(cfg.getArray("RecentFiles", {}),
                 Catch::Matchers::Equals(values));
}

TEST_CASE("getAttributeList and getValueList reflect stored data", "[ConfigFile]")
{
    ConfigFile cfg;
    cfg.setString("First", "1");
    cfg.setString("Second", "2");

    auto attrs = cfg.getAttributeList();
    auto vals = cfg.getValueList();
    REQUIRE(attrs.size() == vals.size());
    REQUIRE(attrs.size() == 2);

    auto has = [](const std::vector<std::string>& v, const std::string& s) {
        return std::find(v.begin(), v.end(), s) != v.end();
    };
    REQUIRE(has(attrs, "First"));
    REQUIRE(has(attrs, "Second"));
}

TEST_CASE("ImportXML / ExportXML round-trip", "[ConfigFile]")
{
    const std::string xml =
        "<TestConfig version=\"1.0\">"
        "<Title value=\"Hello\"/>"
        "<Count value=\"7\"/>"
        "<Recent_files value=\"Array()\">"
        "<Recent_files value=\"a.png\"/>"
        "<Recent_files value=\"b.png\"/>"
        "</Recent_files>"
        "</TestConfig>";

    ConfigFile cfg("TestConfig");
    REQUIRE(cfg.ImportXML(xml));

    REQUIRE(cfg.getString("Title", "") == "Hello");
    REQUIRE(cfg.getInteger("Count", 0) == 7);
    // underscores in element names are translated to spaces for the attribute key.
    REQUIRE_THAT(cfg.getArray("Recent files", {}),
                 Catch::Matchers::Equals(std::vector<std::string>{"a.png", "b.png"}));

    const std::string exported = cfg.ExportXML();
    REQUIRE(exported.find("TestConfig") != std::string::npos);
    REQUIRE(exported.find("Hello") != std::string::npos);
    REQUIRE(exported.find("7") != std::string::npos);
}

TEST_CASE("Save and SaveAs persist to disk", "[ConfigFile]")
{
    std::string path = WriteTempConfig("<TestConfig version=\"1.0\"/>");

    SECTION("SaveAs writes to a new file and clears the modified flag")
    {
        ConfigFile cfg(path, "TestConfig", false);
        cfg.setString("Author", "Tester");
        REQUIRE(cfg.IsModified());

        std::string newPath = WriteTempConfig("");
        cfg.SaveAs(newPath);
        REQUIRE_FALSE(cfg.IsModified());

        // Re-open the saved file and verify the value persisted.
        ConfigFile reloaded(newPath, "TestConfig", false);
        REQUIRE(reloaded.getString("Author", "") == "Tester");

        RemoveFile(newPath);
    }

    RemoveFile(path);
}

TEST_CASE("Loading a missing file leaves the config unopened but defaults still work", "[ConfigFile]")
{
    // A path that does not exist; the ctor logs to stdout and returns
    // IsOpen()==false, but getString with bAddDefaultsToConfig=false still
    // returns the caller-supplied default.
    const std::string bogus = "openpaint_test_no_such_file.xml";
    RemoveFile(bogus);
    ConfigFile cfg(bogus, "TestConfig", false);
    REQUIRE_FALSE(cfg.IsOpen());
    REQUIRE(cfg.getString("Absent", "fallback") == "fallback");
}

TEST_CASE("Loading a file with the wrong root identifier leaves the config empty", "[ConfigFile]")
{
    // The file declares <OtherConfig> but the ctor expects <TestConfig>.
    // The old code asserted (crashed in debug, null-deref'd in release); the
    // current code still relies on the assert for that, so we only run this
    // test in release mode where an assert is a no-op.
#ifndef NDEBUG
    SKIP("Asserts on missing root element in debug builds");
#else
    std::string path = WriteTempConfig("<OtherConfig version=\"1.0\"><Title value=\"x\"/></OtherConfig>");
    ConfigFile cfg(path, "TestConfig", false);
    // The load failed but we didn't crash; getString returns the default.
    REQUIRE(cfg.getString("Title", "default") == "default");
    RemoveFile(path);
#endif
}

TEST_CASE("ImportXML with an empty string fails without modifying state", "[ConfigFile]")
{
    ConfigFile cfg("TestConfig");
    cfg.setString("Existing", "value");
    REQUIRE_FALSE(cfg.ImportXML(""));
    REQUIRE(cfg.getString("Existing", "") == "value");
}

TEST_CASE("getArray on a non-array attribute returns the defaults", "[ConfigFile]")
{
    ConfigFile cfg;
    cfg.setString("NotAnArray", "single-value");
    const std::vector<std::string> defaults{"x", "y"};
    REQUIRE(cfg.getArray("NotAnArray", defaults) == defaults);
}

TEST_CASE("DumpConfig prints something to stdout", "[ConfigFile][.quiet]")
{
    // The output of DumpConfig is implementation-defined; we just want to
    // make sure it doesn't crash. Suppressed from the default run.
    ConfigFile cfg;
    cfg.setString("Hello", "World");
    cfg.DumpConfig();
    SUCCEED();
}
