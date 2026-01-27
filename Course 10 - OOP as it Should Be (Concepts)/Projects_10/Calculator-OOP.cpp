#include <iostream>
using namespace std;

class clsCalculater {
private:
	float _PreviousResult = 0;
	float _LastNum = 0;
	float _Result = 0;
	enum enLastOp { eAdd = 1, eSub = 2, eMult = 3, eDiv = 4, eClear=5 };
	string _LastOp_String;
	string GetStringOp(enLastOp OpString) {
		switch (OpString) {
		case enLastOp::eAdd: return " Adding ";
		case enLastOp::eSub: return " Subtracting ";
		case enLastOp::eMult: return " Multiplying ";
		case enLastOp::eDiv: return " Dividing ";
		case enLastOp::eClear: return " Clear ";
		}
	}
	

public:
	void Clear() {
		_PreviousResult = 0;
		_LastNum = 0;
		_Result = 0;
		_LastOp_String = GetStringOp(eClear);
	}

	void Add(int Num) {
		_LastNum = Num;
		_LastOp_String = GetStringOp(eAdd);
		_PreviousResult = _Result;
		_Result += Num;
	}

	void Divide(int Num) {
		_LastNum = Num;

		if (Num == 0)
			Num = 1;

		_LastOp_String = GetStringOp(eDiv);
		_PreviousResult = _Result;
		_Result /= Num;
	}

	void Multiply(int Num) {
		_LastNum = Num;
		_LastOp_String = GetStringOp(eMult);
		_PreviousResult = _Result;
		_Result *= Num;
	}

	void Subtract(int Num) {
		_LastNum = Num;
		_LastOp_String = GetStringOp(eSub);
		_PreviousResult = _Result;
		_Result -= Num;
	}

	float GetFinalResult(){
		return _Result;
	}

	void PrintResult() {
		cout << "Result After" << _LastOp_String << _LastNum << " is: " << _Result << endl;
	}

	void CancelLastOp() {
		_LastNum = 0;
		_LastOp_String = " Cancelling Last Operation ";
		_Result = _PreviousResult;
	}

};
