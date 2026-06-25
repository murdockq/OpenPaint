#ifndef OPENPAINT_HISTORY_H
#define OPENPAINT_HISTORY_H

#include <cstddef>
#include <vector>

namespace openpaint {

// Templated undo/redo history. The previous implementation in
// OpenPaintMDIChildFrame used a raw std::vector and two integer cursors
// (m_HistoryIndex) that could be decremented past zero or incremented past
// the end, which produced std::out_of_range. This class enforces bounds
// and gives the GUI a small, well-defined surface to call.
//
// Semantics:
//  - Push(item) appends a new state. The "redo" branch is dropped because
//    the user started a new edit from somewhere in the past.
//  - Undo() returns the state one step back from the current position, or
//    false if already at the oldest recorded state.
//  - Redo() returns the state one step forward from the current position,
//    or false if already at the newest recorded state.
//  - Current() returns the state at the current position.
//  - Size is capped at kMaxSize: the oldest entries are dropped when the
//    cap is exceeded.
template <typename T>
class History
{
public:
    explicit History(std::size_t maxSize = 64)
        : m_maxSize(maxSize ? maxSize : 1)
    {
    }

    std::size_t MaxSize() const { return m_maxSize; }
    std::size_t Size() const { return m_states.size(); }

    // True when the cursor is not at the newest state.
    bool CanRedo() const { return m_cursor + 1 < m_states.size(); }
    // True when the cursor is not at the oldest state.
    bool CanUndo() const { return m_cursor > 0; }

    const T& Current() const { return m_states[m_cursor]; }

    // Append a new state, dropping anything in the redo branch and
    // trimming the oldest entries past the cap.
    void Push(const T& item)
    {
        if (m_cursor + 1 < m_states.size())
        {
            m_states.erase(m_states.begin() + (m_cursor + 1), m_states.end());
        }
        m_states.push_back(item);
        m_cursor = m_states.size() - 1;
        Trim();
    }

    // Move one step back in history. Returns false (and leaves the cursor
    // unchanged) when already at the oldest entry.
    bool Undo()
    {
        if (!CanUndo())
        {
            return false;
        }
        --m_cursor;
        return true;
    }

    // Move one step forward in history. Returns false when already at the
    // newest entry.
    bool Redo()
    {
        if (!CanRedo())
        {
            return false;
        }
        ++m_cursor;
        return true;
    }

    // Forget everything.
    void Clear()
    {
        m_states.clear();
        m_cursor = 0;
    }

private:
    void Trim()
    {
        while (m_states.size() > m_maxSize)
        {
            m_states.erase(m_states.begin());
            if (m_cursor > 0)
            {
                --m_cursor;
            }
        }
    }

    std::vector<T> m_states;
    std::size_t m_cursor = 0;
    std::size_t m_maxSize = 1;
};

} // namespace openpaint

#endif // OPENPAINT_HISTORY_H

