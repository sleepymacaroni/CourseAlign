#include <iostream>
#include "Section.h"
#include "Schedule.h"
#include "dataHandling/loadSections.h"
#include "printSchedule.h"

int main() {
    try {
        std::vector<Section> sections = loadSectionsFromCsv("dataHandling/testData.csv");

        Schedule mySchedule;
        for (const Section& s : sections) {
            if (mySchedule.canAdd(s)) {
                mySchedule.add(s);
                std::cout << "Added: " << s.getCourseCode() 
                          << " " << s.getSectionId() << std::endl;
            } else {
                std::cout << "Conflict, duplicate, or exceeding units: " 
                          << s.getCourseCode() << " " << s.getSectionId() << std::endl;
            }
        }

        std::cout << "\nFinal Schedule:\n";
        for (const Section& s : mySchedule.getClasses()) {
            std::cout << s.getCourseCode() << " | " 
                      << s.getCourseTitle() << " | "
                      << s.getSectionId() << " | "
                      << s.getComponent() << " | "
                      << s.getStartTime() << "-" << s.getEndTime() << " | Units: "
                      << s.getUnits() << " | Mode: "
                      << s.getInstructionMode() << std::endl;
        }

        printSchedule(mySchedule);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}