#include <iostream>
#include <string>
#include <set>

class Section {
private:
    const std::string courseCode;
    const std::string courseTitle;
    const std::string sectionId;
    const std::string component;
    const std::string instructor;
    const std::set<std::string> days;
    const std::string startTime;
    const std::string endTime;
    const int units;
    const std::string instructionMode;

public:
    Section(
        std::string courseCode,
        std::string courseTitle,
        std::string sectionId,
        std::string component,
        std::string instructor,
        std::set<std::string> days,
        std::string startTime,
        std::string endTime,
        int units,
        std::string instructionMode
    )
    : courseCode(courseCode),
      courseTitle(courseTitle),
      sectionId(sectionId),
      component(component),
      instructor(instructor),
      days(days),
      startTime(startTime),
      endTime(endTime),
      units(units),
      instructionMode(instructionMode)
    {}

    std::string getCourseCode() const {
        return courseCode;
    }

    std::string getCourseTitle() const {
        return courseTitle;
    }

    std::string getSectionId() const {
        return sectionId;
    }

    std::string getComponent() const {
        return component;
    }

    std::string getInstructor() const {
        return instructor;
    }

    std::set<std::string> getDays() const {
        return days;
    }

    std::string getStartTime() const {
        return startTime;
    }

    std::string getEndTime() const {
        return endTime;
    }

    int getUnits() const {
        return units;
    }

    std::string getInstructionMode() const {
        return instructionMode;
    }
};