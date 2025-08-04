#include "TimeMicro.h"
#include <regex> 

TimeMicro::TimeMicro()
	: total_seconds(0)
{}


TimeMicro::TimeMicro(const size_t hour, const size_t minute, const size_t second, const size_t milliseconds) : total_seconds(0) {
	if (hour > 23) {
		throw std::invalid_argument("Invalid hour value. Must be between 00 and 23.");
	}
	if (minute > 59) {
		throw std::invalid_argument("Invalid minute value. Must be between 00 and 59.");
	}
	if (second > 59) {
		throw std::invalid_argument("Invalid second value. Must be between 00 and 59.");
	}
	if (milliseconds > 999) {
		throw std::invalid_argument("Invalid microsecond value. Must be between 000 and 999.");
	}
 
	total_seconds = hour * 3600 + minute * 60 + second + milliseconds / 1000; // Convert milliseconds to seconds
}

TimeMicro::TimeMicro(const std::string& time_str)
	: total_seconds(0) {
	if (time_str.empty()) {
		throw std::invalid_argument("TimeMicro string cannot be empty.");
	}
	std::regex time_regex("^([01]\\d|2[0-3]):[0-5]\\d:[0-5]\\d$");
	if (!std::regex_match(time_str, time_regex)) {
		throw std::invalid_argument("TimeMicro string must be in the format HH:MM:SS.");
	}
	int hour = std::stoi(time_str.substr(0, 2));
	int minute = std::stoi(time_str.substr(3, 2));
	int second = std::stoi(time_str.substr(6, 2));
	total_seconds = hour * 3600 + minute * 60 + second;
}

std::string TimeMicro::to_string(const bool& twelve_h) const {
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

std::string TimeMicro::to_string() const {
	return to_string(false);
}

// Comparison operators
bool TimeMicro::operator==(const TimeMicro& other) const {
	return total_seconds == other.total_seconds;
}

bool TimeMicro::operator!=(const TimeMicro& other) const {
	return !(*this == other);
}

bool TimeMicro::operator<(const TimeMicro& other) const {
	return total_seconds < other.total_seconds;
}

bool TimeMicro::operator<=(const TimeMicro& other) const {
	return total_seconds <= other.total_seconds;
}

bool TimeMicro::operator>(const TimeMicro& other) const {
	return total_seconds > other.total_seconds;
}

bool TimeMicro::operator>=(const TimeMicro& other) const {
	return total_seconds >= other.total_seconds;
}	

// Postfix & Prefix increment and decrement operators
TimeMicro& TimeMicro::operator++() { // Prefix increment
	total_seconds = (total_seconds + 1) % 86400; // Wrap around after 24 hours
	return *this;
}

TimeMicro TimeMicro::operator++(int) { // Postfix increment
	TimeMicro temp = *this;
	++(*this); // Call prefix increment
	return temp;
}

TimeMicro& TimeMicro::operator--() { // Prefix decrement
	total_seconds = (total_seconds == 0) ? 86399 : (total_seconds - 1); // Wrap around to 23:59:59 if at 00:00:00
	return *this;
}

TimeMicro TimeMicro::operator--(int) { // Postfix decrement
	TimeMicro temp = *this;
	--(*this); // Call prefix decrement
	return temp;
}

bool TimeMicro::is_am() const {
	return get_hour() < 12;
}

int TimeMicro::get_hour() const {
	return total_seconds / 3600;
}

int TimeMicro::get_minute() const {
	return (total_seconds % 3600) / 60;
}

int TimeMicro::get_second() const {
	return total_seconds % 60;
}

// Stream operators
std::ostream& operator<<(std::ostream& os, const TimeMicro& time) {
	os << time.to_string();
	return os;
}

