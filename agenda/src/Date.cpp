#include "Date.hpp"
#include <string>
#include <iostream>

using namespace std;

Date::Date() {
	m_year = 0;
	m_month = 0;
	m_day = 0;
	m_hour = 0;
	m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
	m_year = t_year;
	m_month = t_month;
	m_day = t_day;
	m_hour = t_hour;
	m_minute = t_minute;
}

int Date::getYear(void) const {
	return m_year;
}

void Date::setYear(const int t_year) {
	m_year = t_year;
}

int Date::getMonth(void) const {
	return m_month;
}

void Date::setMonth(const int t_month) {
	m_month = t_month;
}

int Date::getDay(void) const {
	return m_day;
}

void Date::setDay(const int t_day) {
	m_day = t_day;
}

int Date::getHour(void) const {
	return m_hour;
}

void Date::setHour(const int t_hour) {
	m_hour = t_hour;
}

int Date::getMinute(void) const {
	return m_minute;
}

void Date::setMinute(const int t_minute) {
	m_minute = t_minute;
}

bool Date::isValid(const Date t_date) {
	if (t_date.getYear() < 1000 || t_date.getYear() > 9999)
		return 0;
	if (t_date.getMonth() < 1 || t_date.getMonth() > 12)
		return 0;
	if (t_date.getMonth() == 1 || t_date.getMonth() == 3 || t_date.getMonth() == 5 || t_date.getMonth() == 7 || t_date.getMonth() == 8 || t_date.getMonth() == 10 || t_date.getMonth() == 12) {
		if (t_date.getDay() > 31 || t_date.getDay() < 1)
			return 0;
	}
	if (t_date.getMonth() == 4 || t_date.getMonth() == 6 || t_date.getMonth() == 9 || t_date.getMonth() == 11) {
		if (t_date.getDay() > 30 || t_date.getDay() < 1)
			return 0;
	}
	if ((t_date.getYear() % 4 == 0 && t_date.getYear() % 100 != 0) || (t_date.getYear() % 400 == 0)) {
		if (t_date.getMonth() == 2)
			if (t_date.getDay() < 1 || t_date.getDay() > 29)
				return 0;
	} else {
		if (t_date.getMonth() == 2)
			if (t_date.getDay() < 1 || t_date.getDay() > 28)
				return 0;
	}
	if (t_date.getHour() < 0 || t_date.getHour() > 23)
		return 0;
	if (t_date.getMinute() < 0 || t_date.getMinute() > 59)
		return 0;
	return 1;
}

Date Date::stringToDate(const string t_dateString) {
	string temp = t_dateString;
	bool correct = 1;
	int i = 0;
	if (temp.length() != 16)
		correct = 0;
	for(i = 0; i < 4; i ++) {
		if (temp[i] >= '0' && temp[i] <= '9');
		else
			correct = 0;
	}
	if (temp[4] != '-' || temp[7] != '-' || temp[10] != '/' || temp[13] != ':')
		correct = 0;
	for (i = 5; i < 7; i ++) {
		if (temp[i] < '0' || temp[i] > '9')
			correct = 0;
	}
	for (i = 8; i < 10; i ++) {
		if (temp[i] < '0' || temp[i] > '9')
			correct = 0;
	}
	for (i = 11; i < 13; i ++) {
		if (temp[i] < '0' || temp[i] > '9')
			correct = 0;
	}
	for (i = 14; i <= 15; i ++) {
		if (temp[i] < '0' || temp[i] > '9')
			correct = 0;
	}
	Date datetemp;
	int middle;
	if (correct != 0) {
		middle = (temp[0] - '0') * 1000 + (temp[1] - '0') * 100 + (temp[2] - '0') * 10 + (temp[3] - '0');
		datetemp.setYear(middle);
		middle = (temp[5] - '0') * 10 + (temp[6] - '0');
		datetemp.setMonth(middle);
		middle = (temp[8] - '0') * 10 + (temp[9] - '0');
		datetemp.setDay(middle);
		middle = (temp[11] - '0') * 10 + (temp[12] - '0');
		datetemp.setHour(middle);
		middle = (temp[14] - '0') * 10 + (temp[15] - '0');
		datetemp.setMinute(middle);
	}
	if (correct == 0) {
		datetemp.setYear(0);
		datetemp.setMonth(0);
		datetemp.setDay(0);
		datetemp.setHour(0);
		datetemp.setMinute(0);
	}
	return datetemp;
}

Date::Date(string dateString) {
	Date temp = stringToDate(dateString);
	m_year = temp.getYear();
	m_month = temp.getMonth();
	m_day = temp.getDay();
	m_hour = temp.getHour();
	m_minute = temp.getMinute();
}

string Date::dateToString(Date t_date) {
	bool correct = isValid(t_date);
	string temp;
	if (correct == 0)
		temp = "0000-00-00/00:00";
	else {
		temp = t_date.getYear() / 1000 + '0';
		temp += ((t_date.getYear() / 100) % 10 + '0');
		temp += ((t_date.getYear() / 10) % 10 + '0');
		temp += (t_date.getYear() % 10 + '0');
		temp += '-';
		temp += (t_date.getMonth() / 10) + '0';
		temp += (t_date.getMonth() % 10) + '0';
		temp += '-';
		temp += (t_date.getDay() / 10) + '0';
		temp += (t_date.getDay() % 10) + '0';
		temp += '/';
		temp += (t_date.getHour() / 10) + '0';
		temp += (t_date.getHour() % 10) + '0';
		temp += ':';
		temp += (t_date.getMinute() / 10) + '0';
		temp += (t_date.getMinute() % 10) + '0';
	}
	return temp;
}

Date& Date::operator=(const Date &t_date) {
	m_year = t_date.getYear();
	m_month = t_date.getMonth();
	m_day = t_date.getDay();
	m_hour = t_date.getHour();
	m_minute = t_date.getMinute();
}

bool Date::operator==(const Date &t_date) const {
	if (m_year != t_date.getYear())
		return 0;
	else {
		if (m_month != t_date.getMonth())
			return 0;
		else {
			if (m_day != t_date.getDay())
				return 0;
			else {
				if (m_hour != t_date.getHour())
					return 0;
				else {
					if (m_minute != t_date.getMinute())
						return 0;
					else
						return 1;
				}
			}
		}
	}
}

bool Date::operator>(const Date &t_date) const {
	if (m_year > t_date.getYear())
		return 1;
	else if (m_year < t_date.getYear())
		return 0;
	else {
		if (m_month > t_date.getMonth())
			return 1;
		else if (m_month < t_date.getMonth())
			return 0;
		else {
			if (m_day > t_date.getDay())
				return 1;
			else if (m_day < t_date.getDay())
				return 0;
			else {
				if (m_hour > t_date.getHour())
					return 1;
				else if (m_hour < t_date.getHour())
					return 0;
				else {
					if (m_minute > t_date.getMinute())
						return 1;
					else
						return 0;
				}
			}
		}
	}
}

bool Date::operator<(const Date &t_date) const {
	if (m_year < t_date.getYear())
		return 1;
	else if (m_year > t_date.getYear())
		return 0;
	else {
		if (m_month < t_date.getMonth())
			return 1;
		else if (m_month > t_date.getMonth())
			return 0;
		else {
			if (m_day < t_date.getDay())
				return 1;
			else if (m_day > t_date.getDay())
				return 0;
			else {
				if (m_hour < t_date.getHour())
					return 1;
				else if (m_hour > t_date.getHour())
					return 0;
				else {
					if (m_minute < t_date.getMinute())
						return 1;
					else
						return 0;
				}
			}
		}
	}
}

bool Date::operator>=(const Date &t_date) const {
	if (m_year > t_date.getYear())
		return 1;
	else if (m_year < t_date.getYear())
		return 0;
	else {
		if (m_month > t_date.getMonth())
			return 1;
		else if (m_month < t_date.getMonth())
			return 0;
		else {
			if (m_day > t_date.getDay())
				return 1;
			else if (m_day < t_date.getDay())
				return 0;
			else {
				if (m_hour > t_date.getHour())
					return 1;
				else if (m_hour < t_date.getHour())
					return 0;
				else {
					if (m_minute >= t_date.getMinute())
						return 1;
					else
						return 0;
				}
			}
		}
	}
}

bool Date::operator<=(const Date &t_date) const {
	if (m_year < t_date.getYear())
		return 1;
	else if (m_year > t_date.getYear())
		return 0;
	else {
		if (m_month < t_date.getMonth())
			return 1;
		else if (m_month > t_date.getMonth())
			return 0;
		else {
			if (m_day < t_date.getDay())
				return 1;
			else if (m_day > t_date.getDay())
				return 0;
			else {
				if (m_hour < t_date.getHour())
					return 1;
				else if (m_hour > t_date.getHour())
					return 0;
				else {
					if (m_minute <= t_date.getMinute())
						return 1;
					else
						return 0;
				}
			}
		}
	}
}