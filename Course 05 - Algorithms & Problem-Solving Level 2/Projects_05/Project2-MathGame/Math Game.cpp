#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <ctime>
using namespace std;

enum enQuestionLevel { Esey = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOpType OperationType;
	enQuestionLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionLevel QuestionsLevel;
	enOpType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

string GetOpTypeSymbol(enOpType OpType) {
	switch (OpType)
	{
	case enOpType::Add:
		return "+";
	case enOpType::Sub:
		return "-";
	case enOpType::Mul:
		return "x";
	case enOpType::Div:
		return "/";
	default:
		return "Mix";
	}
}

enOpType GetRandomOperationType()
{
	return (enOpType)RandomNumber(1, 4);
}

string GetQuestionLevelString(enQuestionLevel QuestionLevel) {
	string arrQuestionLevelString[4] = { "Esey" , "Mediem" , "Hard", "Mixed" };
	return arrQuestionLevelString[QuestionLevel - 1];
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}

short ReadHowManyQuestions() {
	short HowManyQuestions = 0;
	do {
		cout << "How Many Questions do you want to answer ? 1 to 10 ";
		cin >> HowManyQuestions;
	} while (HowManyQuestions <= 0 || HowManyQuestions > 10);

	return HowManyQuestions;
}

enQuestionLevel ReadQuestionLevel() {
	short QuestionLevel = 0;
	do {
		cout << "Enter Questions Level? [1]:Esey, [2]:Med, [3]:Hard, [4]:Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOpType ReadOpType() {
	short OpType = 0;
	do {
		cout << "Enter Operatoin Type ? [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return (enOpType)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOpType OpType)
{
	switch (OpType)
	{
	case enOpType::Add:
		return Number1 + Number2;
	case enOpType::Sub:
		return Number1 - Number2;
	case enOpType::Mul:
		return Number1 * Number2;
	case enOpType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOpType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

	if (OpType == enOpType::MixOp)
		OpType = GetRandomOperationType();

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Esey:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}

	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = QuestionLevel;

	return Question;
}

void PrintLine() {
	cout << "____________________\n";
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
	PrintLine();
}

void CorrectTneQuestionAns(stQuizz& Quizz, short QuestionNumber) {
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer == Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer! :-)\n";

	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Wrong Answer! :-( \n";
		cout << "Correct Answer is: " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;

	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

int ReadPlayerAns() {
	int Ans = 0;
	cout << "Your Answer: ";
	cin >> Ans;
	return Ans;
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);


		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAns();

		CorrectTneQuestionAns(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResult(bool Pass) {
	if (Pass)
		return "PASS :-)\n";
	else
		return "FAIL :-(\n";

	PrintLine();
}

void ShowFinalGameResults(stQuizz Quizz) {
	cout << "\n";
	PrintLine();
	cout << "Final Results is " << GetFinalResult(Quizz.isPass);
	PrintLine();

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Question level     : " << GetQuestionLevelString(Quizz.QuestionsLevel) << endl;
	cout << "Opertoin Type      : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	PrintLine();

	SetScreenColor(Quizz.isPass);
}

void GenerateQuizzQuestions(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

void PlayMathGame() {
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestionListAnswers(Quizz);

	ShowFinalGameResults(Quizz);
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}