#include <iostream>
#include <unordered_set>
#include <sstream>
#include "Section.h"
#include "ScheduleBuild.h"
#include "Schedule.h"
#include "dataHandling/loadSections.h"
#include "printSchedule.h"
#include <regex>

int main() {
	try {
		std::vector<Section> sections = loadSectionsFromCsv("dataHandling/testData.csv");

		std::cout << "Welcome to CourseAlign!\n";

		std::cout << "Enter desired class list. Class names should be all capital letters followed by a number, and classes should be seperated by a space (eg 'MATH245 MATH254').";
		std::string input;
		std::getline(std::cin, input);

		std::regex pattern("^([A-Z]+[0-9]+)(\\s+[A-Z]+[0-9]+)*$");

		if (!std::regex_match(input, pattern)) {
			std::cerr << "Invalid format. Example: MATH245 MATH254\n";
			return 1;
		}

		std::vector<std::string> desiredCourses;
		std::istringstream iss(input);
		std::string course;

		while (iss >> course) {
			desiredCourses.push_back(course);
		}

		std::unordered_set<std::string> validCourses;

		for (const Section& s : sections) {
			validCourses.insert(s.getCourseCode());
		}

		for (const std::string& c : desiredCourses) {
			if (validCourses.find(c) == validCourses.end()) {
				std::cerr << "Course not found: " << c << std::endl;
				return 1;
			}
		}

		bool startPreference = false;
		bool endPreference = false;
		std::string earliestStartTime = "";
		std::string latestEndTime = "";

		std::cout << "Do you want to set an earliest start time? (y/n): ";
		char startChoice;
		std::cin >> startChoice;

		if (startChoice == 'y' || startChoice == 'Y') {
			startPreference = true;
			std::cout << "Enter earliest start time (HH:MM): ";
			std::cin >> earliestStartTime;
		}

		std::cout << "Do you want to set a latest end time? (y/n): ";
		char endChoice;
		std::cin >> endChoice;

		if (endChoice == 'y' || endChoice == 'Y') {
			endPreference = true;
			std::cout << "Enter latest end time (HH:MM): ";
			std::cin >> latestEndTime;
		}

		std::unordered_set<std::string> seen;
		std::vector<std::string> uniqueCourses;

		for (const std::string& c : desiredCourses) {
			if (seen.insert(c).second) {
				uniqueCourses.push_back(c);
			}
		}

		desiredCourses = uniqueCourses;

		std::vector<Schedule> schedules = createSchedules(sections, desiredCourses, startPreference, endPreference, earliestStartTime, latestEndTime);
		// vector<Schedule> createSchedules(vector<Section>& sections, vector<string> courseTitles, bool startPreference, bool endPreference, string earliestStartTime, string latestEndTime) {

		if (schedules.empty()) {
			std::cout << "No valid schedules found.\n";
		} else {
			for (const Schedule& sched : schedules) {
				printSchedule(sched);
				printCalendar(sched);
			}
		}

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
