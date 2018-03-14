#include "AgendaService.hpp"
#include <list>
#include <string>
#include <vector>

using namespace std;

AgendaService::AgendaService() {
	startAgenda();
}

AgendaService::~AgendaService() {
	quitAgenda();
}

bool AgendaService::userLogIn(const std::string userName, const std::string password) {
	list<User> temp = listAllUsers();
	for (list<User>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
		if (userName == iter -> getName()) {
			if (password == iter -> getPassword())
				return true;
		}
	}
	return false;
}

bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
	User temp(userName, password, email, phone);
	list<User> test = listAllUsers();
	for (list<User>::iterator iter = test.begin(); iter != test.end(); ++iter) {
		if (userName == iter -> getName())
			return false;
	}
	m_storage -> createUser(temp);
	return true;
}

bool AgendaService::deleteUser(const std::string userName, const std::string password) {
	int judg = m_storage -> deleteUser([=](const User &t) -> bool {
		if (userName == t.getName() && password == t.getPassword())
			return true;
		else
			return false;
	});
	if (judg) {
		m_storage -> deleteMeeting([=](const Meeting &t) -> bool {
			if (userName == t.getSponsor())
				return true;
			vector<string> v;
			v = t.getParticipator();
			for (int i = 0; i < v.size(); i ++) {
				if (userName == v[i])
					return true;
			}
			return false;
		});
	}
	if (judg)
		return true;
	else
		return false;
}

list<User> AgendaService::listAllUsers(void) const {
	list<User> temp;
	temp = m_storage -> queryUser([=](const User &u) -> bool {
		return true;
	});
	return temp;
}

bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
	list<User> temp;
	Date sd = Date::stringToDate(startDate);
	Date ed = Date::stringToDate(endDate);
	bool sd_ = Date::isValid(sd);
	bool ed_ = Date::isValid(ed);
	if (!sd_ || !ed_)
		return false;
	temp = m_storage -> queryUser([=](const User &u) -> bool {
		if (userName == u.getName())
			return true;
		else
			return false;
	});
	if (participator.size() == 0)
		return false;
	if (temp.empty())
		return false;
	temp = m_storage -> queryUser([=](const User &u) -> bool {
		for (int i = 0; i < participator.size(); i ++) {
			if (participator[i] == u.getName())
				return true;
		}
		return false;
	});
	if (temp.empty())
		return false;
	if (ed == sd) 
		return false;
	list<Meeting> test;
	test = m_storage -> queryMeeting([=](const Meeting &t) -> bool {
		if (title == t.getTitle())
			return true;
		else
			return false;
	});
	if (!test.empty())
		return false;
	test = m_storage -> queryMeeting([=](const Meeting &s) -> bool {
		bool is_part_spon = 0;
		bool is_part_part = 0;
		int a = 0, b = 0;
		vector<string> v = s.getParticipator();
		for (a = 0; a < participator.size(); a ++) {
			if (participator[a] == s.getSponsor())
				is_part_spon = 1;
		}
		for (a = 0; a < participator.size(); a ++) {
			for (b = 0; b < v.size(); b ++) {
				if (participator[a] == v[b])
					is_part_part = 1;
			}
		}
		if (userName == s.getSponsor() || is_part_spon == 1) {
			if (sd >= s.getEndDate() || ed <= s.getStartDate())
				return false;
			else
				return true;
		}
		bool is_user_part = 0;
		for (a = 0; a < v.size(); a ++) {
			if (userName == v[a])
				is_user_part = 1;
		}
		if (is_user_part == 1 || is_part_part == 1) {
			if (sd >= s.getEndDate() || ed <= s.getStartDate())
				return false;
			else
				return true;
		}
		return false;
	});
	if (!test.empty())
		return false;
	if (sd > ed)
		return false;
	int j = 0, k = 0, l = 0;
	for (j = 0; j < participator.size(); j ++) {
		for (k = j + 1; k < participator.size(); k ++) {
			if (participator[j] == participator[k]) {
				l = 1;
			}
		}
	}
	for (j = 0; j < participator.size(); j ++) {
		if (userName == participator[j])
			l = 1;
	}
	if (l == 1)
		return false;
	Meeting m(userName, participator, sd, ed, title);
	m_storage -> createMeeting(m);
	return true;
}

list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
	list<Meeting> temp;
	temp = m_storage -> queryMeeting([=](const Meeting &t) -> bool {
		if (userName == t.getSponsor() && title == t.getTitle())
			return true;
		vector<string> v;
		v = t.getParticipator();
		for (int i = 0; i < v.size(); i ++) {
			if (userName == v[i] && title == t.getTitle())
				return true;	
		}
		return false;
	});
	return temp;
}

list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
	list<Meeting> temp;
	Date sd = Date::stringToDate(startDate);
	Date ed = Date::stringToDate(endDate);
	bool sd_ = Date::isValid(sd);
	bool ed_ = Date::isValid(ed);
	if (!sd_ || !ed_)
		return temp;
	temp = m_storage -> queryMeeting([=](const Meeting &t) -> bool {
		if (t.getSponsor() == userName) {
			if (sd > t.getEndDate() || ed < t.getStartDate())
				return false;
			else
				return true;
		}
		int judg = 0;
		vector<string> v;
		v = t.getParticipator();
		for (int i = 0; i < v.size(); i ++) {
			if (userName == v[i])
				judg ++;
		}
		if (!judg) {
			return false;
		} else {
			if (sd > t.getEndDate() || ed < t.getStartDate())
				return false;
			else
				return true;
		}
	});
	return temp;
}

list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
	list<Meeting> temp;
	temp = m_storage -> queryMeeting([=](const Meeting &t) -> bool {
		if (userName == t.getSponsor()) {
			return true;
		}
		vector<string> v;
		v = t.getParticipator();
		for (int i = 0; i < v.size(); i ++) {
			if (userName == v[i])
				return true;
		}
		return false;
	});
	return temp;
}

list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
	list<Meeting> temp;
	temp = m_storage -> queryMeeting([=](const Meeting &t) -> bool {
		if (userName == t.getSponsor())
			return true;
		else
			return false;
	});
	return temp;
}

list<Meeting> AgendaService::listAllParticipateMeetings(const std::string userName) const {
	list<Meeting> temp;
	temp = m_storage -> queryMeeting([=](const Meeting &t) -> bool {
		vector<string> v;
		v = t.getParticipator();
		for (int i = 0; i < v.size(); i ++) {
			if (userName == v[i])
				return true;
		}
		return false;
	});
	return temp;
}

bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
	int judg = m_storage -> deleteMeeting([=](const Meeting &t) -> bool {
		if (userName == t.getSponsor() && title == t.getTitle())
			return true;
		else
			return false;
	});
	if (judg)
		return true;
	else
		return false;
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
	int judg = m_storage -> deleteMeeting([=](const Meeting &t) -> bool {
		if (userName == t.getSponsor())
			return true;
		else
			return false;
	});
	if (judg)
		return true;
	else
		return false;
}

void AgendaService::startAgenda(void) {
	m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
	m_storage = NULL;
}