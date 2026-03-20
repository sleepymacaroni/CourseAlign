#include "ScheduleBuild.h"
#include "Schedule.h"
#include "Section.h"
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;


vector<Section> getCourses(vector<Section> &sections, vector<string> courseTitles) {
    //returns vector of sections with only listed class names
    vector<Section> activeClasses;
    for (const Section &s: sections) {
        for (const string &courseTitle: courseTitles) {
            if (courseTitle == s.getCourseTitle()) {
                activeClasses.push_back(s);
            }
        }
    }
    return activeClasses;
}

vector<Section> getEarliestStartTime(vector<Section> &activeClasses, string earliestStartTime) {
    // takes input start time as a string with format XX:XX, returns vector of sections excluding times earlier than that
    vector<Section> earliestStartTimes;
    for (const Section &s: activeClasses) {
        if (s.getStartTime() >= earliestStartTime) {
            earliestStartTimes.push_back(s);
        }
    }
    return earliestStartTimes;
}

vector<Section> getLatestEndTime(vector<Section>& activeClasses, string latestEndTime) {
    // takes input end time as a string with format XX:XX, returns vector of sections excluding times later than that
    vector<Section> latestEndTimes;
    for (const Section& s : activeClasses) {
        if (s.getEndTime() <= latestEndTime) {
            latestEndTimes.push_back(s);
        }
    }
    return latestEndTimes;
}

vector<vector<Section>> splitCourses(vector<Section> activeCourses) {
    // splits courses based on course title (eg: MATH 100) into a 2d vector by name
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

void recurseLoop(vector<Schedule>& schedules, vector<vector<Section>>& courses, int n, Schedule current) {
    //recursively checks all possible combinations of courses for conflicts, then adds them to a vector of schedules
    if (n >= courses.size()) {
        schedules.push_back(current);
        return;
    }
    for (int i = 0; i < courses[n].size(); i++) {
        Schedule currentLoop = current;
        if (currentLoop.canAdd(courses[n][i])) {
            currentLoop.add(courses[n][i]);
            recurseLoop(schedules, courses, n + 1, currentLoop);
        }
    }
}

vector<Schedule> createSchedules(vector<Section>& sections, vector<string> courseTitles, bool startPreference, bool endPreference, string earliestStartTime, string latestEndTime) {
    //creates a vector of valid schedules, takes a vector of all possible sections, vector of strings of the course titles, true/false arguments for the existence of a start/end time preference,
    //and the earliest possible start and end times as a string with format XX:XX (including padded zeros). returns a vector of all possible schedules with these parameters.
    vector<Section> activeCourses;
    vector<Schedule> schedules;
    vector<vector<Section>> groupedCourses;

    activeCourses = getCourses(sections, courseTitles);
    activeCourses = getEarliestStartTime(activeCourses, earliestStartTime);
    activeCourses = getLatestEndTime(activeCourses, latestEndTime);
    groupedCourses = splitCourses(activeCourses);

    int n = 0;
    Schedule current;

    recurseLoop(schedules, groupedCourses, n, current);
    return schedules;
}
