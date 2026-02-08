#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{
public:

	static bool IsNumberBetween(short Number, short From, short To) {
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(int Number, int From, int To) {
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(float Number, float From, float To) {
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(double Number, double From, double To) {
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {
		if (clsDate::IsDate1AfterDate2(From, To)) {
			clsDate::SwapDates(From, To);
		}
		return (Date.IsDate1AfterDate2(From) && Date.IsDate1BeforeDate2(To));
	}
	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To, bool IncludingEndDay) {
		if (IncludingEndDay)
			return (Date.IsDate1AfterDate2(From) && (Date.IsDate1BeforeDate2(To) || Date.IsDate1EqualsDate2(To)));
		return (Date.IsDate1AfterDate2(From) && Date.IsDate1BeforeDate2(To));
	}
	
	static int ReadNumber(string ErrorMessage = "Invalid number, Enter again!\n") {
		int Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static int ReadNumberBetween(int From, int To, string ErrorMessage = "Invalid number, Enter again!\n") {
		int Number = ReadNumber();
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadNumber();
		}
		return Number;
	}

	static double ReadDNumber(string ErrorMessage = "Invalid number, Enter again!\n") {
		double Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	static double ReadDNumberBetween(double From, double To, string ErrorMessage = "Invalid number, Enter again!\n") {
		double Number;
		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDNumber();
		} ;
		return Number;
	}

	static bool IsValideDate(clsDate Date) {
		return Date.IsValid();
	}


};
