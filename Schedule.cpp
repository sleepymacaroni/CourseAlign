#include <vector>
#include <algorithm>
#include "Section.cpp"
#include <set>
#include <string>

class Schedule {
private:
    std::vector<Section> classes;

public:
    bool canAdd(const Section& newClass) {
        for (const Section& currClass : classes) {

            // time conflict
            if (conflicts(currClass, newClass)) {
                return false;
            }

            // repeat course
            if (currClass.getSectionId() == newClass.getSectionId()) {
                return false;
            }

            // repeat class
            if (currClass.getCourseTitle() == newClass.getCourseTitle() &&
                currClass.getComponent() == newClass.getComponent()) {
                return false;
            }
        }
        return true;
    }

    void add(const Section& section) {
        classes.push_back(section);
    }

    void remove(const Section& section) {
        classes.erase(
            std::remove_if(
                classes.begin(),
                classes.end(),
                [&](const Section& c) {
                    return c.getSectionId() == section.getSectionId();
                }),
            classes.end());
    }

    std::vector<Section> getClasses() const {
        return classes;
    }
};


static bool conflicts(const Section& a, const Section& b) {
    const std::set<std::string>& aDays = a.getDays();
    const std::set<std::string>& bDays = b.getDays();

    for (const std::string& day : aDays) {
        if (bDays.find(day) != bDays.end()) {
            // Simple string comparison: assumes format "HH:MM"
            if (a.getStartTime() < b.getEndTime() &&
                b.getStartTime() < a.getEndTime()) {
                return true;
            }
        }
    }
    return false;
}