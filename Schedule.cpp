#include "Schedule.h"
#include <algorithm>

bool Schedule::canAdd(const Section& newClass) const {
    for (const Section& currClass : classes) {
        if (conflicts(currClass, newClass)) return false;
        if (currClass.getSectionId() == newClass.getSectionId()) return false;
        if (currClass.getCourseTitle() == newClass.getCourseTitle() &&
            currClass.getComponent() == newClass.getComponent()) return false;
    }
    return true;
}

void Schedule::add(const Section& section) {
    classes.push_back(section);
}

void Schedule::remove(const Section& section) {
    classes.erase(
        std::remove_if(classes.begin(), classes.end(),
                       [&](const Section& c) { return c.getSectionId() == section.getSectionId(); }),
        classes.end());
}

std::vector<Section> Schedule::getClasses() const {
    return classes;
}

bool conflicts(const Section& a, const Section& b) {
    const std::set<std::string>& aDays = a.getDays();
    const std::set<std::string>& bDays = b.getDays();

    for (const std::string& day : aDays) {
        if (bDays.find(day) != bDays.end()) {
            if (a.getStartTime() < b.getEndTime() && b.getStartTime() < a.getEndTime()) {
                return true;
            }
        }
    }
    return false;
}