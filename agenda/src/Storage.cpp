#include "Storage.hpp"
#include <functional>
#include <list>
#include <memory>
#include <string>
#include <fstream>
#include "Path.hpp"
#include <vector>
#include "User.hpp"
#include "Meeting.hpp"
#include "Date.hpp"


using namespace std;

shared_ptr<Storage> Storage::m_instance = nullptr;

Storage::Storage() {
	m_dirty = false;
	readFromFile();
}

bool Storage::readFromFile(void) {
	ifstream infile;
	infile.open(Path::userPath);
	if (!infile.good()) {
		return false;
	} else {
		string x, y;
		User temp;
		while (true) {
			getline(infile, x);
			if (x.size() == 0)
				break;
			int i = 0, j = 0, mark = 0;
			for (i = 0; i <= x.length(); i ++) {
				if (x[i] == ',' || i == x.length()) {
					y = x.substr(j + 1, i - j - 2);
					j = i + 1;
					if (mark == 0) {
						temp.setName(y);
					} else if (mark == 1) {
						temp.setPassword(y);
					} else if (mark == 2) {
						temp.setEmail(y);
					} else if (mark == 3) {
						temp.setPhone(y);
					}
					mark += 1;
				}
			}
			m_userList.push_back(temp);
		}
	}
	infile.close();
	ifstream infile_;
	infile_.open(Path::meetingPath);
	if (!infile_.good()) {
		return false;
	} else {
		string x_, y_;
		Meeting temp_;
		while (true) {
			getline(infile_, x_);
			if (x_.size() == 0)
				break;
			int i_ = 0, j_ = 0, mark_ = 0;
			for (i_ = 0; i_ <= x_.length(); i_ ++) {
				if (x_[i_] == ',' || i_ == x_.length()) {
					y_ = x_.substr(j_ + 1, i_ - j_ - 2);
					j_ = i_ + 1;
					if (mark_ == 0) {
						temp_.setSponsor(y_);
					} else if (mark_ == 1) {
						vector<string> v;
						int a = 0, b = 0;
						for (a = 0; a <= y_.length(); a ++) {
							if(y_[a] == '&' || a == y_.length()) {
								string j = y_.substr(b, a - b);
								b = a + 1;
								v.push_back(j);
							}
						}
						temp_.setParticipator(v);
					} else if (mark_ == 2) {
						temp_.setStartDate(Date::stringToDate(y_));
					} else if (mark_ == 3) {
						temp_.setEndDate(Date::stringToDate(y_));
					} else if (mark_ == 4) {
						temp_.setTitle(y_);
					}
					mark_ += 1;
				}
			}
			m_meetingList.push_back(temp_);
		}
	}
	infile_.close();
	return true;
}

bool Storage::writeToFile(void) {
	ofstream outfile;
	outfile.open(Path::userPath, ios::out);
	if (!outfile.good()) {
		return false;
	} else {
		list<User>::iterator iter;
		for (iter = m_userList.begin(); iter != m_userList.end(); iter ++) {
			outfile << '"' << iter -> getName() << '"' << ',';
			outfile << '"' << iter -> getPassword() << '"' << ',';
			outfile << '"' << iter -> getEmail() << '"' << ',';
			outfile << '"' << iter -> getPhone() << '"' << '\n';
		}
	}
	outfile.close();
	ofstream outfile_;
	outfile_.open(Path::meetingPath, ios::out);
	if (!outfile_.good()) {
		return false;
	} else {
		list<Meeting>::iterator iter_;
		for (iter_ = m_meetingList.begin(); iter_ != m_meetingList.end(); iter_ ++) {
			outfile_ << '"' << iter_ -> getSponsor() << '"' << ',';
			vector<string> v;
			v = iter_ -> getParticipator();
			int i = 0;
			outfile_ << '"';
			for (i = 0; i < v.size(); i ++) {
				outfile_ << v[i];
				if (i != v.size() - 1)
					outfile_ << '&';
			}
			outfile_ << '"' << ',';
			outfile_ << '"' << Date::dateToString(iter_ -> getStartDate()) << '"' << ',';
			outfile_ << '"' << Date::dateToString(iter_ -> getEndDate()) << '"' << ',';
			outfile_ << '"' << iter_ -> getTitle() << '"' << '\n';
		}
	}
	outfile_.close();
	return true;
}

shared_ptr<Storage> Storage::getInstance(void) {
	if (m_instance == NULL)
		m_instance = (shared_ptr<Storage>)(new Storage);
	return m_instance;
}

Storage::~Storage() {
	writeToFile();
	m_instance = NULL;
}

void Storage::createUser(const User & t_user) {
	m_userList.push_back(t_user);
	m_dirty = true;
	sync();
}

list<User> Storage::queryUser(function<bool(const User &)> filter) const {
	list<User> temp;
	for (list<User>::const_iterator iter = m_userList.begin(); iter != m_userList.end();  iter ++) {
		if (filter(*iter))
			temp.push_back(*iter);
	}
	return temp;
}

int Storage::updateUser(function<bool(const User &)> filter,
						function<void(User &)> switcher) {
	int result = 0;
	for (auto iter = m_userList.begin(); iter != m_userList.end(); iter ++) {
		if (filter(*iter)) {
			switcher(*iter);
			result ++;
		}
	}
	m_dirty = true;
	sync();
	return result;
}

int Storage::deleteUser(function<bool(const User &)> filter) {
	int result = 0;
	for (list<User>::iterator iter = m_userList.begin(); iter != m_userList.end(); ) {
		if (filter(*iter)) {
			iter = m_userList.erase(iter);
			result ++;
		} else {
			iter ++;
		}
	}
	m_dirty = true;
	sync();
	return result;
}

void Storage::createMeeting(const Meeting & t_meeting) {
	m_meetingList.push_back(t_meeting);
	m_dirty = true;
	sync();
}

list<Meeting> Storage::queryMeeting(function<bool(const Meeting &)> filter) const {
	list<Meeting> temp;
	for (list<Meeting>::const_iterator iter = m_meetingList.begin(); iter != m_meetingList.end(); iter ++) {
		if (filter(*iter))
			temp.push_back(*iter);
	}
	return temp;
}

int Storage::updateMeeting(function<bool(const Meeting &)> filter,
						   function<void(Meeting &)> switcher) {
	int result = 0;
	for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter ++) {
		if (filter(*iter)) {
			switcher(*iter);
			result ++;
		}
	}
	m_dirty = true;
	sync();
	return result;
}

int Storage::deleteMeeting(function<bool(const Meeting &)> filter) {
	int result = 0;
	for (list<Meeting>::iterator iter = m_meetingList.begin(); iter != m_meetingList.end(); ) {
		if (filter(*iter)) {
			iter = m_meetingList.erase(iter);
			result ++;
		} else {
			iter ++;
		}
	}
	m_dirty = true;
	sync();
	return result;
}

bool Storage::sync(void) {
	if (m_dirty) {
		writeToFile();
		m_dirty = false;
		return true;
	} else {
		return false;
	}
}