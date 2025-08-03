#include "Time.h"
#include <regex> 

Time::Time()
	: total_seconds(0)
{}

Time::Time(const size_t hour, const size_t minute, const size_t second)
    : total_seconds([&] {
	if (hour > 23){
		throw std::invalid_argument("Invalid hour value. Must be between 00 and 23.");
	}
	if (minute > 59) {
		throw std::invalid_argument("Invalid minute value. Must be between 00 and 59.");
	}
	if (second > 59) {
		throw std::invalid_argument("Invalid second value. Must be between 00 and 59.");
	}
	return hour * 3600 + minute * 60 + second;
    }())
{}

Time::Time(const std::string& time_str)
	: total_seconds([&] {
	if (time_str.empty()) {
		throw std::invalid_argument("Time string cannot be empty.");
	}
	std::regex time_regex("^([01]\\d|2[0-3]):[0-5]\\d:[0-5]\\d$");
	if (!std::regex_match(time_str, time_regex)) {
		throw std::invalid_argument("Time string must be in the format HH:MM:SS.");
	}
	int hour = std::stoi(time_str.substr(0, 2));
	int minute = std::stoi(time_str.substr(3, 2));
	int second = std::stoi(time_str.substr(6, 2));
	return hour * 3600 + minute * 60 + second;
	}())
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
	return total_seconds / 3600;
}

int Time::get_minute() const {
	return (total_seconds % 3600) / 60;
}

int Time::get_second() const {
	return total_seconds % 60;
}


