// Unit tests for the openpaint::History<T> class.

#include <catch2/catch_test_macros.hpp>

#include "History.h"

#include <string>

using openpaint::History;

TEST_CASE("History starts empty with the current item at the head", "[History]")
{
    History<int> h;
    REQUIRE(h.Size() == 1);
    REQUIRE(h.Current() == 0);
    REQUIRE_FALSE(h.CanUndo());
    REQUIRE_FALSE(h.CanRedo());
}

TEST_CASE("History::Push appends and grows", "[History]")
{
    History<int> h;
    h.Push(1);
    h.Push(2);
    h.Push(3);
    REQUIRE(h.Size() == 4);
    REQUIRE(h.Current() == 3);
    REQUIRE(h.CanUndo());
    REQUIRE_FALSE(h.CanRedo());
}

TEST_CASE("History::Undo walks back and Undo past the oldest state is a no-op", "[History]")
{
    History<int> h;
    h.Push(1);
    h.Push(2);

    REQUIRE(h.Undo());
    REQUIRE(h.Current() == 1);

    REQUIRE(h.Undo());
    REQUIRE(h.Current() == 0);
    REQUIRE_FALSE(h.CanUndo());

    // Third Undo is a no-op (returns false, doesn't move the cursor).
    REQUIRE_FALSE(h.Undo());
    REQUIRE(h.Current() == 0);
}

TEST_CASE("History::Redo walks forward and Redo past the newest state is a no-op", "[History]")
{
    History<int> h;
    h.Push(1);
    h.Push(2);
    h.Undo();
    h.Undo();

    REQUIRE(h.CanRedo());
    REQUIRE(h.Redo());
    REQUIRE(h.Current() == 1);

    REQUIRE(h.CanRedo());
    REQUIRE(h.Redo());
    REQUIRE(h.Current() == 2);
    REQUIRE_FALSE(h.CanRedo());

    REQUIRE_FALSE(h.Redo());
    REQUIRE(h.Current() == 2);
}

TEST_CASE("History::Push after Undo drops the redo branch", "[History]")
{
    History<int> h;
    h.Push(1);
    h.Push(2);
    h.Push(3);
    h.Undo();
    h.Undo(); // back at state 1
    h.Push(99);
    REQUIRE(h.Size() == 3); // [0, 1, 99]
    REQUIRE(h.Current() == 99);
    REQUIRE_FALSE(h.CanRedo());
    REQUIRE(h.CanUndo());
    REQUIRE(h.Undo());
    REQUIRE(h.Current() == 1);
}

TEST_CASE("History caps the number of stored states", "[History]")
{
    History<int> h(3); // max 3 entries
    h.Push(1);
    h.Push(2);
    h.Push(3);
    h.Push(4);
    REQUIRE(h.Size() == 3);
    REQUIRE(h.Current() == 4);
    REQUIRE(h.CanUndo());
    // The cursor is at the newest, so the oldest is reachable in one Undo.
    REQUIRE(h.Undo());
    REQUIRE(h.Current() == 3);
    REQUIRE_FALSE(h.CanUndo()); // [1, 2, 3, 4] trimmed to [2, 3, 4]
}

TEST_CASE("History::Clear resets to a single entry", "[History]")
{
    History<std::string> h;
    h.Push("a");
    h.Push("b");
    h.Clear();
    REQUIRE(h.Size() == 1);
    REQUIRE(h.Current() == "");
    REQUIRE_FALSE(h.CanUndo());
    REQUIRE_FALSE(h.CanRedo());
}

TEST_CASE("History works with non-trivial value types", "[History]")
{
    History<std::string> h;
    h.Push(std::string("alpha"));
    h.Push(std::string("beta"));
    REQUIRE(h.Current() == "beta");
    REQUIRE(h.Undo());
    REQUIRE(h.Current() == "alpha");
}
