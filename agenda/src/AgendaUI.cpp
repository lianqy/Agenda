#include "AgendaUI.hpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

bool lock = 1, beginning_ = 1;

AgendaUI::AgendaUI() {
	if (m_userName.size() != 0)
		m_userName.clear();
	if (m_userPassword.size() != 0)
		m_userPassword.clear();
	startAgenda();
}

void AgendaUI::OperationLoop(void) {
	if (beginning_ == 1) {
		executeOperation(getOperation());
		beginning_ = 0;
	}
	if (lock != 0) {
	if (m_userName.size() == 0) {
		startAgenda();
	} else {
		cout << "*-----------------------------Agenda-------------------------------*" << endl;
		cout << "*  Action:                                                         *" << endl;
		cout << "*  o    -- log out Agenda                                          *" << endl;
		cout << "*  q    -- quit Agenda                                             *" << endl;
		cout << "*  dc   -- delete Agenda account                                   *" << endl;
		cout << "*  lu   -- list all Agenda user                                    *" << endl;
		cout << "*  cm   -- create a meeting                                        *" << endl;
		cout << "*  la   -- list all meetings                                       *" << endl;
		cout << "*  las  -- list all sponsor meetings                               *" << endl;
		cout << "*  lap  -- list all participator meetings                          *" << endl;
		cout << "*  qm   -- query meeting by title                                  *" << endl;
		cout << "*  qt   -- query meeting by time interval                          *" << endl;
		cout << "*  rsp  -- reset your password                                     *" << endl;
		cout << "*  dm   -- delete metting by title                                 *" << endl;
		cout << "*  da   -- delete all meetings                                     *" << endl;
		cout << "*------------------------------------------------------------------*" << endl;
		cout << endl << "Agenda@" << m_userName << " : #";
		if (executeOperation(getOperation()));
		else {
			cout << "Sorry, no such operation" << endl;
		}
	}}
	if (lock == 0)
		return;
	else
		OperationLoop();	
}

void AgendaUI::startAgenda(void) {
	lock = 1;
	beginning_ = 1;
	cout << "*-----------------------------Agenda-----------------------------*" << endl;
	cout << "*  Action:                                                       *" << endl;
	cout << "*  l  -- log in Agenda by user name and password                 *" << endl;
	cout << "*  r  -- register an Agenda account                              *" << endl;
	cout << "*  q  -- quit Agenda                                             *" << endl;
	cout << "*  f  -- find your password                                      *" << endl;
	cout << "*----------------------------------------------------------------*" << endl;
	cout << endl << endl;
	cout << "Agenda : ~$";
}

string AgendaUI::getOperation() {
	string operation;
	cin >> operation;
	return operation;
}

bool AgendaUI::executeOperation(std::string t_operation) {
	if (t_operation == "l") {
		userLogIn();
		return true;
	}
	if (t_operation == "r") {
		userRegister();
		return true;
	}
	if (t_operation == "f") {
		zhaohuimima();
		return true;
	}
	if (t_operation == "q") {
		quitAgenda();
		return true;
	}
	if (t_operation == "rsp") {
		xiugaimima();
		return true;
	}
	if (t_operation == "o") {
		userLogOut();
		return true;
	}
	if (t_operation == "dc") {
		deleteUser();
		return true;
	}
	if (t_operation == "lu") {
		listAllUsers();
		return true;
	}
	if (t_operation == "cm") {
		createMeeting();
		return true;
	}
	if (t_operation == "la") {
		listAllMeetings();
		return true;
	}
	if (t_operation == "las") {
		listAllSponsorMeetings();
		return true;
	}
	if (t_operation == "lap") {
		listAllParticipateMeetings();
		return true;
	}
	if (t_operation == "qm") {
		queryMeetingByTitle();
		return true;
	}
	if (t_operation == "qt") {
		queryMeetingByTimeInterval();
		return true;
	}
	if (t_operation == "dm") {
		deleteMeetingByTitle();
		return true;
	}
	if (t_operation == "da") {
		deleteAllMeetings();
		return true;
	}
	return false;
}

void AgendaUI::userLogIn(void) {
	cout << "[log in]  [user name]  [password]" << endl;
	cout << "[log in]  " ;
	string name_, password_; 
	cin >> name_ >> password_;
	if (m_agendaService.userLogIn(name_, password_)) {
		cout << "[log in]  succeed!" << endl;
		m_userName = name_;
		m_userPassword = password_;
	} else {
		cout << "[error]  log in fail!" << endl;
	}
}

void AgendaUI::userRegister(void) {
	cout << "[register]  [user name]  [password]  [email]  [phone]" << endl;
	cout << "[register]  ";
	string name_, password_, email_, phone_;
	cin >> name_ >> password_ >> email_ >> phone_;
	if (m_agendaService.userRegister(name_, password_, email_, phone_)) {
		cout << "[register]  succeed!" << endl;
	} else {
		cout << "[error]  register fail!" << endl;
	}
}

void AgendaUI::quitAgenda(void) {
	cout << "Thank you for using our system!" << endl;
	cout << "Goodbye~" << endl;
	lock = 0;
}

void AgendaUI::userLogOut(void) {
	m_userName.clear();
	m_userPassword.clear();
}

void AgendaUI::deleteUser(void) {
	if (m_agendaService.deleteUser(m_userName, m_userPassword)) {
		cout << "[delete agenda account]  succeed!" << endl;
		m_userName.clear();
		m_userPassword.clear();
	}
}

void AgendaUI::listAllUsers(void) {
	list<User> temp;
	temp = m_agendaService.listAllUsers();
	cout << "[list all users]" << endl << endl;
	cout << left << setw(20) << "name" << setw(20) << "email" << setw(20) << "phone" << endl;
	for (list<User>::iterator iter = temp.begin(); iter != temp.end(); iter ++) {
		cout << left << setw(20) << (*iter).getName() << setw(20) << (*iter).getEmail() << setw(20) << (*iter).getPhone() << endl;
	} 
}

void AgendaUI::createMeeting(void) {
	cout << "[create meeting]  [the number of participator]" << endl;
	cout << "[create meeting]  ";
	int num_;
	cin >> num_;
	string name_[num_];
	for (int i = 0; i < num_; i ++) {
		cout << "[create meeting]  [please enter the participator " << i + 1 << " ]" << endl;
		cout << "[create meeting]  ";
		cin >> name_[i];
	}
	std::vector<string> v;
	for (int j = 0; j < num_; j ++)
		v.push_back(name_[j]);
	string title_, sd_, ed_;
	cout << "[create meeting]  [title]  [start time(yyyy-mm-dd/hh:mm)]  [end time(yyyy-mm-dd/hh:mm)]" << endl;
	cout << "[create meeting]  ";
	cin >> title_ >> sd_ >> ed_;
	if (m_agendaService.createMeeting(m_userName, title_, sd_, ed_, v)) {
		cout << "[create meeting]  succeed!" << endl;
	} else {
		cout << "[create meeting]  error!" << endl;
	}
}

void AgendaUI::listAllMeetings(void) {
	cout << "[list all meetings]" << endl << endl;
	list<Meeting> temp;
	temp = m_agendaService.listAllMeetings(m_userName);
	printMeetings(temp);
}

void AgendaUI::listAllSponsorMeetings(void) {
	cout << "[list all sponsor meetings] " << endl << endl;
	list<Meeting> temp = m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(temp);
}

void AgendaUI::listAllParticipateMeetings(void) {
	cout << "[list all participator meetings]" << endl << endl;
	list<Meeting> temp = m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(temp);
}

void AgendaUI::queryMeetingByTitle(void) {
	cout << "[query meeting]  [title]" << endl;
	cout << "[query meeting]  ";
	string title_;
	cin >> title_;
	list<Meeting> temp = m_agendaService.meetingQuery(m_userName, title_);
	printMeetings(temp);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
	cout << "[query meetings]  [start time(yyyy-mm-dd)]  [end time(yyyy-mm-dd)]" << endl;
	cout << "[query meetings]  ";
	string sd_, ed_;
	cin >> sd_ >> ed_;
	list<Meeting> temp = m_agendaService.meetingQuery(m_userName, sd_, ed_);
	printMeetings(temp);
}

void AgendaUI::deleteMeetingByTitle(void) {
	cout << "[delete meeting]  [title_]" << endl;
	cout << "[delete meeting]  ";
	string title_;
	cin >> title_;
	if (m_agendaService.deleteMeeting(m_userName, title_)) {
		cout << "[delete meeting by title]  succeed!" << endl;
	} else {
		cout << "[error]  delete meeting fail!" << endl;
	}
}

void AgendaUI::deleteAllMeetings(void) {
	m_agendaService.deleteAllMeetings(m_userName);
	cout << "[delete all meetings]  succeed!" << endl;
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
	cout << left << setw(10) << "title" << setw(10) << "sponsor" << setw(20) << "start time" << setw(20) << "end time" << setw(15) << "participator" << endl;
	for (list<Meeting>::iterator iter = t_meetings.begin(); iter != t_meetings.end(); iter ++) {
		cout << left << setw(10) << (*iter).getTitle() << setw(10) << (*iter).getSponsor() << setw(20) << Date::dateToString((*iter).getStartDate());
		cout << left << setw(20) << Date::dateToString((*iter).getEndDate());
		std::vector<string> v = (*iter).getParticipator();
		if (v.size() != 1) {
		for (int i = 0; i < v.size(); i ++) {
			if (i == 0)
				cout << v[0] << ',';
			else {
				if (i != v.size() - 1)
					cout << v[i] << ',';
				else
					cout << v[i];
			}
		}
		cout << endl;
	}
	if (v.size() == 1)
		cout << setw(15) << v[0] << endl;
		
	}
}

void AgendaUI::xiugaimima(void) {
	cout << "[reset your password]  [new password]" << endl;
	cout << "[reset your password]  ";
	string x;
	cin >> x;
	cout << "[reset your password]  [input your new password again]" << endl;
	cout << "[reset your password]  ";
	string y;
	cin >> y;
	if (x == y) {
		cout << "[reset your password]  succeed!" << endl;
		list<User> temp;
		temp = m_agendaService.listAllUsers();
		User temp_;
		for (auto iter = temp.begin(); iter != temp.end(); iter ++) {
			if ((*iter).getName() == m_userName)
				temp_ = *iter;
		}
		temp_.setPassword(x);
		string email_ = temp_.getEmail();
		string phone_ = temp_.getPhone();
		m_agendaService.deleteUser(m_userName, m_userPassword);
		m_agendaService.userRegister(m_userName, x, email_, phone_);
		executeOperation("o");
	} else {
		cout << "[reset your password]  fail!" << endl;
	}
}

void AgendaUI::zhaohuimima(void) {
	cout << "[find your password]  [name]  [email]  [phone]" << endl;
	cout << "[find your password]  ";
	string name_, email_, phone_;
	cin >> name_ >> email_ >> phone_;
	list<User> temp;
	User temp_;
	temp = m_agendaService.listAllUsers();
	for (auto iter = temp.begin(); iter != temp.end(); iter ++) {
		if (name_ == (*iter).getName())
			temp_ = *iter;
	}
	if (temp_.getName() != name_) {
		cout << "[find your password]  fail! No this user!" << endl;
		return;
	}
	if (temp_.getEmail() != email_ || temp_.getPhone() != phone_) {
		cout << "[find your password]  fail!" << endl;
	} else {
		cout << "[find your password]  [password]" << endl;
		cout << "[find your password]  " << temp_.getPassword() << endl;
	}
}