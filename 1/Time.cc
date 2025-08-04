#include "Time.h"
#include <regex> 

Time::Time()
	: hours(0), minutes(0), seconds(0)
{}

Time::Time(const size_t hour, const size_t minute, const size_t second)
	: hours(hour), minutes(minute), seconds(second) {
	if (hour > 23) {
		throw std::invalid_argument("Invalid hour value. Must be between 00 and 23.");
	}
	if (minute > 59) {
		throw std::invalid_argument("Invalid minute value. Must be between 00 and 59.");
	}
	if (second > 59) {
		throw std::invalid_argument("Invalid second value. Must be between 00 and 59.");
	}
}

size_t parse_hour(const std::string& time_str) {
	if (time_str.empty()) {
		throw std::invalid_argument("Time string cannot be empty.");
	}
	std::regex hour_regex("^([01]\\d|2[0-3]):");
	std::smatch match;
	if (!std::regex_search(time_str, match, hour_regex)) {
		throw std::invalid_argument("Time string must be in the format HH:MM:SS.");
	}
	return std::stoi(match.str(1));
}

size_t parse_minute(const std::string& time_str) {
	if (time_str.empty()) {
		throw std::invalid_argument("Time string cannot be empty.");
	}
	std::regex minute_regex(":([0-5]\\d):");
	std::smatch match;
	if (!std::regex_search(time_str, match, minute_regex)) {
		throw std::invalid_argument("Time string must be in the format HH:MM:SS.");
	}
	return std::stoi(match.str(1));
}

size_t parese_second(const std::string& time_str) {
	if (time_str.empty()) {
		throw std::invalid_argument("Time string cannot be empty.");
	}
	std::regex second_regex(":([0-5]\\d)$");
	std::smatch match;
	if (!std::regex_search(time_str, match, second_regex)) {
		throw std::invalid_argument("Time string must be in the format HH:MM:SS.");
	}
	return std::stoi(match.str(1));
}

Time::Time(const std::string& time_str) 
	:	hours(parse_hour(time_str)),
		minutes(parse_minute(time_str)),
		seconds(parese_second(time_str)) 
{}

std::string Time::to_string(const bool& twelve_h) const {
	int hours = get_hour();
	int minutes = get_minute();
	int seconds = get_second();

	if (twelve_h) {
		std::string period = (hours < 12) ? "am" : "pm";
		if (hours == 0) {
			hours = 12;
		} else if (hours > 12) {
			hours -= 12; 
		}
		return std::to_string(hours) + ":" + 
		       (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + 
		       (seconds < 10 ? "0" : "") + std::to_string(seconds) + period;
	} else {
		return (hours < 10 ? "0" : "") + std::to_string(hours) + ":" + 
		       (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + 
		       (seconds < 10 ? "0" : "") + std::to_string(seconds);
	}
}

std::string Time::to_string() const {
	return to_string(false);
}


bool Time::is_am() const {
	return get_hour() < 12;
}

int Time::get_hour() const {
	return hours;
}

int Time::get_minute() const {
	return minutes;
}

int Time::get_second() const {
	return seconds;
}


