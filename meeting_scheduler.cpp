#include <iostream>
#include <list>
#include <string>
#include <cassert>

/*
    Takes a list of meetings and removes the meeting names, keeping only the times.
    Args:
        meetings (list): A list of meeting strings.
    Returns:
        (list): A list containing only the meeting times.
*/
std::list<std::string> clean_meetings(std::list<std::string> meetings){
    std::list<std::string> cleaned;
    for (std::string meeting : meetings){
        cleaned.push_back(meeting.substr(meeting.find(':')+2));
    }
    return cleaned;
}

/*
    Takes a time and converts it into the number of minutes after midnight.
    Args:
        time (str): A time in "HH:MM" format.
    Returns:
        (int): The number of minutes after midnight.
*/
int time_to_minutes(const std::string& time) {
      int colon = time.find(':');

      int hours = std::stoi(time.substr(0, colon));
      int minutes = std::stoi(time.substr(colon + 1));

      return hours * 60 + minutes;
  }

/*
    Checks whether any meetings overlap by comparing every meeting with the others.
    Args:
        meetings (list): A list of meeting strings.
    Returns:
        (bool): True if a conflict is found, otherwise false.
*/
bool conflict_checker_double_loop(std::list<std::string> meetings){
    std::list<std::string> clean = clean_meetings(meetings);
    for (std::string meeting1 : clean) {
        std::string end1 = meeting1.substr(meeting1.find('-')+1);
        for (std::string meeting2 : clean) {
            if (meeting2 == meeting1){
                continue;
            }
            std::string start2 = meeting2.substr(0, meeting2.find('-'));
            if (time_to_minutes(start2) < time_to_minutes(end1)){
                return true;
            }
        }
    }
    return false;
}

/*
    Checks whether any meetings overlap after sorting them by start time.
    Args:
        meetings (list): A list of meeting strings.
    Returns:
        (bool): True if a conflict is found, otherwise false.
*/
bool conflict_checker_sort(std::list<std::string> meetings){
    std::list<std::string> clean = clean_meetings(meetings);
    clean.sort([](const std::string& a, const std::string& b) {
      return time_to_minutes(a) < time_to_minutes(b);
    });
    std::string end = ("00:00");
    for (std::string meeting : clean) {
        std::string start = meeting.substr(0, meeting.find('-'));
        if (time_to_minutes(start) < time_to_minutes(end)){
            return true;
        }
        end = meeting.substr(meeting.find('-')+1);
    }
    return false;
}

int main() {
    std::list<std::string> no_conflict = {
        "Meeting A: 10:00-11:00",
        "Meeting B: 12:00-13:00"
    };
    assert(conflict_checker_sort(no_conflict) == false);
    assert(conflict_checker_double_loop(no_conflict) == false);
    assert(conflict_checker_sort({}) == false);
    assert(conflict_checker_double_loop({}) == false);

    std::list<std::string> back_to_back = {
        "Meeting A: 10:00-11:00",
        "Meeting B: 11:00-12:00"
    };
    assert(conflict_checker_sort(back_to_back) == false);

    std::list<std::string> partial_overlap = {
        "Meeting A: 10:00-11:00",
        "Meeting B: 10:30-11:30"
    };
    assert(conflict_checker_sort(partial_overlap) == true);
    assert(conflict_checker_double_loop(partial_overlap) == true);

    std::list<std::string> same_time = {
        "Meeting A: 10:00-11:00",
        "Meeting B: 10:00-11:00"
    };
    assert(conflict_checker_sort(same_time) == true);
    assert(conflict_checker_double_loop(same_time) == true);

    return 0;
}
