#include <iostream>
using namespace std;

class clsPerson {
private:

	short _ID;
	string _Fristname, _Lastname, _Email, _Phone;

public:
	clsPerson(short ID, string fristname, string lastname, string email, string phone) {
		_ID = ID;
		_Fristname = fristname;
		_Lastname = lastname;
		_Email = email;
		_Phone = phone;
	}

	short ID() { return _ID; }

	void SetFristName(string FristName) { _Fristname = FristName; }
	string FristName() { return _Fristname; }

	void setLastName(string LastName) { _Lastname = LastName; }
	string LastName() { return _Lastname; }

	void setEmail(string Email) { _Email = Email; }
	string Email() { return _Email; }

	void setPhone(string Phone) { _Phone = Phone; }
	string Phone() { return _Phone; }

	string fullname() {
		return _Fristname + " " + _Lastname;
	}

	void Print() {
		cout << "\nInfo";
		cout << "\n______________________________";
		cout << "\nID        :" << _ID;
		cout << "\nFrist Name:" << _Fristname;
		cout << "\nLast Name :" << _Lastname;
		cout << "\nFull Name :" << fullname();
		cout << "\nEmail     :" << _Email;
		cout << "\nPhone     :" << _Phone;
		cout << "\n______________________________\n";
	}

	void SendEmail(string subject, string body) {
		cout << "\nThe fallowing massage sent successfully to email: "
			<< _Email;
		cout << "\nSubject: " << subject;
		cout << "\nBody : " << body << endl;
	}

	void SendSMS(string SMS) {
		cout << "\nThe following SMS sent successfully to Phone: "
			<< _Phone << endl;
		cout << SMS << endl;
	}
};

class clsEmployee : public clsPerson {
private:

	string _Title, _Department;
	float _Salary;

public:
	clsEmployee(short ID, string fristname, string lastname, string Title,
		string email, string phone, float Salary, string Department)
		: clsPerson(ID, fristname, lastname, email, phone) {
		_Title = Title;
		_Salary = Salary;
		_Department = Department;
	}

	void setTitle(string Title) { _Title = Title; }
	string Title() { return _Title; }

	void setSalary(float Salary) { _Salary = Salary; }
	float Salary() { return _Salary; }

	void setDepartment(string Department) { _Department = Department; }
	string Department() { return _Department; }


	void Print() {
		cout << "\nInfo";
		cout << "\n______________________________";
		cout << "\nID        : " << ID();
		cout << "\nFrist Name: " << FristName();
		cout << "\nLast Name : " << LastName();
		cout << "\nFull Name : " << fullname();
		cout << "\nTitle     : " << Title();
		cout << "\nEmail     : " << Email();
		cout << "\nPhone     : " << Phone();
		cout << "\nSalary    : " << Salary();
		cout << "\nDepartment: " << Department();
		cout << "\n______________________________\n";
	}
};

class clsDeveloper : public clsEmployee {
	string _MainProgrammingLanguage;

public:
	clsDeveloper(short ID, string fristname, string lastname, string Title,
		string email, string phone, float Salary, string Department ,string MainProgrammingLanguage)
		:clsEmployee( ID, fristname, lastname, Title, email, phone, Salary, Department)
	{
		_MainProgrammingLanguage = MainProgrammingLanguage;
	}

	void setMainProgrammingLanguage(string MainProgrammingLanguage) { _MainProgrammingLanguage = MainProgrammingLanguage; }
	string MainProgrammingLanguage() { return _MainProgrammingLanguage; }

	void Print() {
		cout << "\nInfo";
		cout << "\n_______________________________________________";
		cout << "\nID                        : " << ID();
		cout << "\nFrist Name                : " << FristName();
		cout << "\nLast Name                 : " << LastName();
		cout << "\nFull Name                 : " << fullname();
		cout << "\nTitle                     : " << Title();
		cout << "\nEmail                     : " << Email();
		cout << "\nPhone                     : " << Phone();
		cout << "\nSalary                    : " << Salary();
		cout << "\nDepartment                : " << Department();
		cout << "\nMain Programming Language : " << MainProgrammingLanguage();
		cout << "\n________________________________________________\n";
	}
};
