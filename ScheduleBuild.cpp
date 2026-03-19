//take class codes as input
// give options for earliest start time
#include "Schedule.h"
#include "Section.h"
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;


    vector<Section> getCourses(vector<Section>& sections, vector<string> courseTitles) { //returns vector of sections with only listed class names
        vector<Section> activeClasses;
        for (const Section& s : sections) {
            for (const string& courseTitle : courseTitles) {
                if (courseTitle == s.getCourseTitle()) {
                    activeClasses.push_back(s);
                }
            }
        }
        return activeClasses;
    }

    vector<Section> getEarliestStartTime(vector<Section>& activeClasses, string earliestStartTime) { // takes input start time as a string with format XX:XX, returns vector of sections excluding times earlier than that
        vector<Section> earliestStartTimes;
        for (const Section& s : activeClasses) {
            if (s.getStartTime() <= earliestStartTime) {
                earliestStartTimes.push_back(s);
            }
        }
        return earliestStartTimes;
    }

    vector<Section> getLatestEndTime(vector<Section>& activeClasses, string latestEndTime) {// takes input end time as a string with format XX:XX, returns vector of sections excluding times later than that
        vector<Section> latestEndTimes;
        for (const Section& s : activeClasses) {
            if (s.getEndTime() >= latestEndTime) {
                latestEndTimes.push_back(s);
            }
        }
        return latestEndTimes;
    }

    vector<vector<Section>> splitCourses(vector<Section> activeCourses) { // splits courses based on course title (eg: MATH 100) into a 2d vector by name
        vector<vector<Section>> splitCourses;
        splitCourses.push_back(vector<Section>());
        int individualCourses = 0;
        for (int i = 0; i < activeCourses.size(); i++){
            if (i > 0 && activeCourses[i].getCourseTitle() != activeCourses[i - 1].getCourseTitle()) {
                splitCourses.push_back(vector<Section>());
                individualCourses++;
            }
        splitCourses[individualCourses].push_back(activeCourses[i]);
        }
        return splitCourses;
    }

    vector<Schedule> createSchedules(vector<Section>& sections, vector<string> courseTitles, bool startPreference, bool endPreference, string earliestStartTime, string latestEndTime) {
        vector<Section> activeCourses;
        vector<Schedule> Schedules;
        vector<vector<Section>> groupedCourses;
        activeCourses = getCourses(sections, courseTitles);
        activeCourses = getEarliestStartTime(activeCourses, earliestStartTime);
        activeCourses = getLatestEndTime(activeCourses, latestEndTime);
        groupedCourses = splitCourses(activeCourses);
        for (int i = 0; i < groupedCourses.size(); i++) {
            for (int j = 0; j < groupedCourses[i].size(); j++) {
                
            }
        }
    }
