#include "printSchedule.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

// Column widths
static const int W_CODE  = 10;
static const int W_TITLE = 28;
static const int W_SEC   = 10;
static const int W_COMP  = 6;
static const int W_DAYS  = 8;
static const int W_TIME  = 13;
static const int W_INST  = 20;
static const int W_UNITS = 5;
static const int W_MODE  = 8;

// Truncates a string to fit within a given width
static std::string fit(const std::string& s, int width) {
    if ((int)s.size() <= width) return s;
    return s.substr(0, width - 2) + "..";
}

// Joins the days set into a compact string (e.g. "Mo We Fr")
static std::string formatDays(const std::set<std::string>& days) {
    std::string result;
    for (const auto& d : days) {
        if (!result.empty()) result += " ";
        result += d;
    }
    return result.empty() ? "TBD" : result;
}

// Formats "HH:MM" into "H:MMam/pm"
static std::string formatTime(const std::string& t) {
    if (t == "00:00" || t.empty()) return "TBD";
    int h = std::stoi(t.substr(0, 2));
    std::string min = t.substr(3, 2);
    std::string suffix = h >= 12 ? "pm" : "am";
    if (h > 12) h -= 12;
    if (h == 0) h = 12;
    return std::to_string(h) + ":" + min + suffix;
}

static void printDivider() {
    std::cout << "+"
        << std::string(W_CODE  + 2, '-') << "+"
        << std::string(W_TITLE + 2, '-') << "+"
        << std::string(W_SEC   + 2, '-') << "+"
        << std::string(W_COMP  + 2, '-') << "+"
        << std::string(W_DAYS  + 2, '-') << "+"
        << std::string(W_TIME  + 2, '-') << "+"
        << std::string(W_INST  + 2, '-') << "+"
        << std::string(W_UNITS + 2, '-') << "+"
        << std::string(W_MODE  + 2, '-') << "+"
        << "\n";
}

static void printRow(const std::string& code,
                     const std::string& title,
                     const std::string& sec,
                     const std::string& comp,
                     const std::string& days,
                     const std::string& time,
                     const std::string& inst,
                     const std::string& units,
                     const std::string& mode) {
    std::cout << "| " << std::left
        << std::setw(W_CODE)  << fit(code,  W_CODE)  << " | "
        << std::setw(W_TITLE) << fit(title, W_TITLE) << " | "
        << std::setw(W_SEC)   << fit(sec,   W_SEC)   << " | "
        << std::setw(W_COMP)  << fit(comp,  W_COMP)  << " | "
        << std::setw(W_DAYS)  << fit(days,  W_DAYS)  << " | "
        << std::setw(W_TIME)  << fit(time,  W_TIME)  << " | "
        << std::setw(W_INST)  << fit(inst,  W_INST)  << " | "
        << std::setw(W_UNITS) << fit(units, W_UNITS) << " | "
        << std::setw(W_MODE)  << fit(mode,  W_MODE)  << " |"
        << "\n";
}

void printSchedule(const Schedule& s) {
    std::vector<Section> classes = s.getClasses();

    std::cout << "\n  === CourseAlign: Your Schedule ===\n\n";

    if (classes.empty()) {
        std::cout << "  No classes in this schedule.\n\n";
        return;
    }

    printDivider();
    printRow("Course", "Title", "Section", "Comp", "Days", "Time", "Instructor", "Units", "Mode");
    printDivider();

    int totalUnits = 0;
    for (const Section& c : classes) {
        std::string timeStr = formatTime(c.getStartTime()) + " - " + formatTime(c.getEndTime());
        printRow(
            c.getCourseCode(),
            c.getCourseTitle(),
            c.getSectionId(),
            c.getComponent(),
            formatDays(c.getDays()),
            timeStr,
            c.getInstructor(),
            std::to_string(c.getUnits()),
            c.getInstructionMode()
        );
        totalUnits += c.getUnits();
    }

    printDivider();
    std::cout << "\n  Total Units: " << totalUnits << " / 21\n\n";
}
