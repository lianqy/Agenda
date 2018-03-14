#include "Meeting.hpp"
#include <string>
#include <vector>

using namespace std;

Meeting::Meeting(string t_sponsor, vector<string> t_participator, Date t_startTime, Date t_endTime, string t_title) {
	m_sponsor = t_sponsor;
	m_participators = t_participator;
	m_startDate = t_startTime;
	m_endDate = t_endTime;
	m_title = t_title;
}

Meeting::Meeting(const Meeting &t_meeting) {
	m_sponsor = t_meeting.getSponsor();
	m_participators = t_meeting.getParticipator();
	m_startDate = t_meeting.getStartDate();
	m_endDate = t_meeting.getEndDate();
	m_title = t_meeting.getTitle();
}

string Meeting::getSponsor(void) const {
	return m_sponsor;
}

void Meeting::setSponsor(const string t_sponsor) {
	m_sponsor = t_sponsor;
}

vector<string> Meeting::getParticipator(void) const {
	return m_participators;
}

void Meeting::setParticipator(const vector<string> t_participators) {
	m_participators = t_participators;
}

Date Meeting::getStartDate(void) const {
	return m_startDate;
}

void Meeting::setStartDate(const Date t_startTime) {
	m_startDate = t_startTime;
}

Date Meeting::getEndDate(void) const {
	return m_endDate;
}

void Meeting::setEndDate(const Date t_endTime) {
	m_endDate = t_endTime;
}

string Meeting::getTitle() const {
	return m_title;
}

void Meeting::setTitle(const string t_title) {
	m_title = t_title;
}

bool Meeting::isParticipator(const string t_username) const {
	int i = 0;
	for (i = 0; i < m_participators.size(); i ++) {
		if(m_participators[i] == t_username)
			break;
	}
	if (i == m_participators.size())
		return 0;
	else
		return 1;
}