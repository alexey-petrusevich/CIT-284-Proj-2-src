#include "Word.h"
#include <iostream>
#include <string>
#include <io.h>
#include <conio.h>
#include <list>
#include <fstream>
#include <iomanip>
using std::setw;
using std::wcout;
using std::wcin;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::wfstream;
using std::getline;
using std::ios;
using std::left;

const std::string FILENAME = "words.dat";
const int OUT_WIDTH = 20;

enum Choice {
	CREATE_LIST = 1,
	GERMAN_NOUNS = 2,
	GERMAN_VERBS = 3,
	GERMAN_PREPOSITIONS = 4,
	GERMAN_ADJECTIVES = 5,
	GERMAN_ADVERBS = 6,
	GERMAN_CARDINAL_NUMBERS = 7,
	SEARCH_FOR_WORD = 8,
	QUIT = 9
};

// prototypes
Choice displayMenu();
bool checkFile();
void createList(); // creates a list and saves it in the file
void displayWords(list<Word>, PartOfSpeech); // displays nouns only
void searchForWord(list<Word>); // searches the list of words and returns a word if found (either german or english)
void invalidChoice(); // displays an error message if invalid options was selected by user
list<Word> loadList(); // loads the list from the file if file exists
void setGender(wstring&, Gender&);
void capitalizeNoun(wstring&);
wstring getArticle(Word);
void sortWords(list<Word>&);

class ListNotFoundException {};

int main() {

	Choice choice;
	bool listExists;

	// to hold the list of words
	list<Word> words;

	do {

		// check if list exists
		listExists = checkFile();

		if (listExists) {
			// load items from the list
			words = loadList();
		}

		// read user's choice
		choice = displayMenu();

		try {
			// do what user selected
			switch (choice)
			{
			case Choice::CREATE_LIST:
				createList();
				break;
			case Choice::GERMAN_NOUNS:
				if (!listExists) throw ListNotFoundException();
				displayWords(words, PartOfSpeech::NOUN);
				break;
			case Choice::GERMAN_VERBS:
				if (!listExists) throw ListNotFoundException();
				displayWords(words, PartOfSpeech::VERB);
				break;
			case Choice::GERMAN_PREPOSITIONS:
				if (!listExists) throw ListNotFoundException();
				displayWords(words, PartOfSpeech::PREPOSITION);
				break;
			case Choice::GERMAN_ADJECTIVES:
				if (!listExists) throw ListNotFoundException();
				displayWords(words, PartOfSpeech::ADJECTIVE);
				break;
			case Choice::GERMAN_ADVERBS:
				if (!listExists) throw ListNotFoundException();
				displayWords(words, PartOfSpeech::ADVERB);
				break;
			case Choice::GERMAN_CARDINAL_NUMBERS:
				if (!listExists) throw ListNotFoundException();
				displayWords(words, PartOfSpeech::CARDINAL_NUMBER);
				break;
			case Choice::SEARCH_FOR_WORD:
				if (!listExists) throw ListNotFoundException();
				// search either german or english
				searchForWord(words);
				break;
			case Choice::QUIT:
				if (!listExists) throw ListNotFoundException();
				cout << "\n\n" << "Quitting the program ..." << endl;
				system("pause");
				break;
			default:
				// invalid choice
				invalidChoice();
				break;
			}
		}
		catch (ListNotFoundException) {

			system("cls");

			cout << "Error! List with words not found!" << endl;

			system("pause");
		}

	} while (choice != Choice::QUIT || !listExists);

	return 0;
}

// function displays main menu
Choice displayMenu() {

	system("cls");

	cout << "Select an option: \n"
		<< "\n" << Choice::CREATE_LIST << ". Create the word list"
		<< "\n" << Choice::GERMAN_NOUNS << ". German to English nouns"
		<< "\n" << Choice::GERMAN_VERBS << ". German to English verbs"
		<< "\n" << Choice::GERMAN_PREPOSITIONS << ". German to English preposition"
		<< "\n" << Choice::GERMAN_ADJECTIVES << ". German to English adjectives"
		<< "\n" << Choice::GERMAN_ADVERBS << ". German to English adverbs"
		<< "\n" << Choice::GERMAN_CARDINAL_NUMBERS << ". German to English cardinal numbers"
		<< "\n" << Choice::SEARCH_FOR_WORD << ". Search for a word"
		<< "\n" << Choice::QUIT << ". Quit" << endl;

	// _getch() return ascii value of key entered
	Choice choice = (Choice)(_getch() - 0x30);

	return choice;
}

// function checks if file exists and returns 'true' if exists and 'false' otherwise
bool checkFile() {
	// if file can be accessesd
	if (_access(FILENAME.c_str(), 00) != -1) { // 00 - regular file

		return true;
	}
	else {
		// file does not exists
		return false;
	}
}

void createList()
{

	int numWords;

	bool listExists = checkFile();

	if (listExists) {

		system("cls");
		cout << "List of words already exists!" << endl;
		system("pause");
		return;

	}

	do {
		system("cls");

		cout << "Enter number of words you want to add: ";
		string numWordsStr;
		bool invalidInput = false;
		getline(cin, numWordsStr);

		for (int i = 0; i < numWordsStr.length(); i++) {
			if (!isdigit(numWordsStr.at(i))) {
				// display error message and break out of for loop; ask for input again
				cout << "You must enter a positive integer!" << endl;

				system("pause");
				invalidInput = true;
				break;
			}
		}

		if (!invalidInput) {
			// convert to integer
			numWords = atoi(numWordsStr.c_str());
			break;
		}

	} while (true);

	std::wfstream out(FILENAME, std::ios::out | std::ios::binary);

	for (int i = 0; i < numWords; i++) {


		// get German word
		wstring germanWord;
		wchar_t c;

		do {
			system("cls");
			wcout << "Use the following keys for umlaut charachters:\n"
				<< "F1 - " << Word::A_LOW << "\n"
				<< "F2 - " << Word::A_UP << "\n"
				<< "F3 - " << Word::O_LOW << "\n"
				<< "F4 - " << Word::O_UP << "\n"
				<< "F5 - " << Word::U_LOW << "\n"
				<< "F6 - " << Word::U_UP << "\n\n"

				<< "Enter a german word: [" << i + 1 << "] " << germanWord;


			c = _getch();
			// if function key is pressed first _getch() returns 0, and second returns acutal key
			if (c == 0) {
				c = _getch();
				switch (c) {
				case 59: // F1
					c = Word::A_LOW;
					break;
				case 60: // F2
					c = Word::A_UP;
					break;
				case 61: // F3
					c = Word::O_LOW;
					break;
				case 62: // F4
					c = Word::O_UP;
					break;
				case 63: // F5
					c = Word::U_LOW;
					break;
				case 64: // F6
					c = Word::U_UP;
					break;
				}
			}
			if (c == '\r') {
				if (germanWord.length() == 0) {
					cout << endl << "You must enter a word!" << endl;
					system("pause");
					continue;
				}
				else {
					break;
				}
				
			}
			germanWord += c;

			if (c == '\b') { // backspace
				germanWord.erase(germanWord.length() - 2);
			}

		} while (true);


		//wcout << germanWord << endl;

		// get part of speech

		int partOfSpeech;
		bool invalidEntry;
		Gender gender = Gender::NONE; // none by default; non nouns will have this gender

		do {
			invalidEntry = false;
			cout << endl << "Enter part of speech: " << endl
				<< PartOfSpeech::NOUN << ". Noun" << "\n"
				<< PartOfSpeech::VERB << ". Verb" << "\n"
				<< PartOfSpeech::PREPOSITION << ". Preposition" << "\n"
				<< PartOfSpeech::CARDINAL_NUMBER << ". Cardinal number" << "\n"
				<< PartOfSpeech::ADVERB << ". Adverb" << "\n"
				<< PartOfSpeech::ADJECTIVE << ". Adjective" << "\n"
				<< endl;

			partOfSpeech = _getch();

			partOfSpeech -= 0x30;



			switch (partOfSpeech) {
			case PartOfSpeech::NOUN:
				setGender(germanWord, gender); // sets gender
			case PartOfSpeech::VERB:
			case PartOfSpeech::PREPOSITION:
			case PartOfSpeech::CARDINAL_NUMBER:
			case PartOfSpeech::ADVERB:
			case PartOfSpeech::ADJECTIVE:
				break;
			default:
				invalidEntry = true;
				invalidChoice();
				break;
			}

		} while (invalidEntry);


		wstring englishWord;
		// get English word
		do {

			wcout << "Enter English meaning of the word \'" << germanWord << "\': ";

			getline(wcin, englishWord);
			// if nothing entered
			if (englishWord.length() == 0) {
				cout << "You did not enter an English word!" << endl;
				system("pause");
				continue;
			}
			else break;

		} while (true);

		// write combination to the file

		// [German word] [part of speech] [English word] [gender]
		out << germanWord << '\n' << partOfSpeech << '\n' << englishWord << '\n' << gender << endl;

		wcout << endl
			<< "[" << germanWord << "]" << " - " << "[" << englishWord << "]" << " added to the list!" << endl;

		system("pause");

	}

	out.close();

	// add read-only attribute to the file read-only 
	// FILENAME = words.dat
	system("attrib +r words.dat");

}

void displayWords(list<Word> list, PartOfSpeech partOfSpeech)
{

	wstring partOfSpeechStr;

	switch (partOfSpeech) {
	case PartOfSpeech::NOUN:
		partOfSpeechStr = L"NOUNS";
		break;
	case PartOfSpeech::VERB:
		partOfSpeechStr = L"VERBS";
		break;
	case PartOfSpeech::PREPOSITION:
		partOfSpeechStr = L"PREPOSITIONS";
		break;
	case PartOfSpeech::ADJECTIVE:
		partOfSpeechStr = L"ADJECTIVES";
		break;
	case PartOfSpeech::ADVERB:
		partOfSpeechStr = L"ADVERBS";
		break;
	case PartOfSpeech::CARDINAL_NUMBER:
		partOfSpeechStr = L"CARDINAL NUMBERS";
		break;
	}

	if (list.size() != 0) sortWords(list);

	int numWords = 0;

	system("cls");
	std::list<Word>::iterator iter;

	wcout << std::right << 
		setw(OUT_WIDTH) << partOfSpeechStr << endl << endl <<
		left <<
		setw(OUT_WIDTH) << L"GERMAN WORD" << setw(OUT_WIDTH) << L"ENGLISH MEANING" << endl << endl;

	// wcout << "List size: " << list.size() << endl;

	for (iter = list.begin(); iter != list.end(); iter++) {
		Word word = *iter;
		if (word.getPartOfSpeech() == partOfSpeech) {
			wstring germanWord = word.getGermanWord();
			wstring englishWord = word.getEnglishWord();
			wstring article;
			if (partOfSpeech == PartOfSpeech::NOUN) {
				capitalizeNoun(germanWord);
				article = getArticle(word);
			}
			wcout << left <<
				setw(OUT_WIDTH) << article + germanWord <<
				setw(OUT_WIDTH) << englishWord << endl << endl;

			numWords++;
		}
	}
	if (numWords == 0) {
		wcout << "NO " << partOfSpeechStr << "!" << endl;
	}
	system("pause");
}



void searchForWord(list<Word> list)
{

	if (list.size() == 0) return;

	// display search menu

	wstring searchableWord;
	wchar_t c;

	do {
		system("cls");
		wcout << "Use the following keys for umlaut charachters:\n"
			<< "F1 - " << Word::A_LOW << "\n"
			<< "F2 - " << Word::A_UP << "\n"
			<< "F3 - " << Word::O_LOW << "\n"
			<< "F4 - " << Word::O_UP << "\n"
			<< "F5 - " << Word::U_LOW << "\n"
			<< "F6 - " << Word::U_UP << "\n\n"

			<< "Enter a word: " << searchableWord;


		c = _getch();
		// if function key is pressed first _getch() returns 0, and second returns acutal key
		if (c == 0) {
			c = _getch();
			switch (c) {
			case 59: // F1
				c = Word::A_LOW;
				break;
			case 60: // F2
				c = Word::A_UP;
				break;
			case 61: // F3
				c = Word::O_LOW;
				break;
			case 62: // F4
				c = Word::O_UP;
				break;
			case 63: // F5
				c = Word::U_LOW;
				break;
			case 64: // F6
				c = Word::U_UP;
				break;
			}
		}
		if (c == '\r') break;

		searchableWord += c;

		if (c == '\b') { // backspace
			searchableWord.erase(searchableWord.length() - 2);
		}

	} while (true);

	std::list<Word>::iterator iter;

	for (iter = list.begin(); iter != list.end(); iter++) {

		Word word = *iter;
		wstring germanWord = word.getGermanWord();
		wstring englishWord = word.getEnglishWord();

		// wcsstr = strstr for wchar_t
		if (wcsstr(germanWord.c_str(), searchableWord.c_str()) || wcsstr(englishWord.c_str(), searchableWord.c_str())) {
			// match found
			system("cls");
			wcout << "Match found!" << endl
				<< left << setw(OUT_WIDTH) << "GERMAN WORD" << setw(OUT_WIDTH) << "ENGLISH MEANING" << endl << endl;

			wstring germanWord = word.getGermanWord();
			wstring article;
			wstring englishWord = word.getEnglishWord();

			if (word.getPartOfSpeech() == PartOfSpeech::NOUN) {
				capitalizeNoun(germanWord);
				article = getArticle(word);
			}

			wcout << left << setw(OUT_WIDTH) << article + germanWord  << setw(OUT_WIDTH) << englishWord << endl << endl;
			system("pause");
			return;
		}
	}

	// no match
	system("cls");
	wcout  << endl << "No match found!" << endl;
	system("pause");
}

void invalidChoice()
{
	cout << "Invalid choice entered!" << endl;
	system("pause");
}

list<Word> loadList()
{
	// file existance checked before calling the function

	wfstream in(FILENAME, ios::in | ios::binary);

	list<Word> list;

	// [germanWord] [partOfSpeech] [englishWord] [gender]
	wstring germanWord;
	int partOfSpeech;
	wstring englishWord;
	int gender;

	while (in) {

		wstring temp;

		std::getline(in, germanWord);

		std::getline(in, temp);
		partOfSpeech = _wtoi(temp.c_str());

		std::getline(in, englishWord);

		std::getline(in, temp);
		gender = _wtoi(temp.c_str());
		if (!in) break;
		// in >> germanWord >> partOfSpeech >> englishWord >> gender;
		Word word(germanWord, (PartOfSpeech)partOfSpeech, englishWord, (Gender)gender);

		list.push_back(word);
	}

	//cout << "List loaded. Size: " << list.size();
	//system("pause");

	return list;
}

void setGender(wstring& germanWord, Gender& gender) {

	do {
		cout << "What is gender of the noun?" << endl
			<< Gender::MASCULINE << ". Masculine" << endl
			<< Gender::FEMININE << ". Feminine" << endl
			<< Gender::NEUTER << ". Neuter" << endl;

		gender = (Gender)(_getch() - 0x30);

	} while (gender != Gender::MASCULINE && gender != Gender::FEMININE && gender != Gender::NEUTER);

}

void capitalizeNoun(wstring& noun) {

	if (noun.length() == 0) return;


	wchar_t c;

	if (noun.at(0) == Word::A_LOW) {
		c = Word::A_UP;
	}
	else if (noun.at(0) == Word::O_LOW) {
		c = Word::O_UP;
	}
	else if (noun.at(0) == Word::U_LOW) {
		c = Word::U_UP;
	}
	else {
		c = toupper(noun.at(0));
	}

	wstring str;
	str += c;
	// from 0th position of str 1 character long
	noun.replace(0, 1, str);
}

wstring getArticle(Word germanWord) {
	if (germanWord.getPartOfSpeech() == PartOfSpeech::NOUN) {
		switch (germanWord.getGender()) {
		case Gender::MASCULINE:
			return L"der ";
		case Gender::FEMININE:
			return L"die ";
		case Gender::NEUTER:
			return L"das ";
		default:
			return L"";
		}
	}
	else return L"";
}

void sortWords(list<Word>& list) {

	if (list.size() == 0) return;

	int listSize = list.size();

	Word* words = new Word[listSize];

	std::list<Word>::iterator iter;

	int x;

	for (x = 0, iter = list.begin(); x < listSize, iter != list.end(); iter++, x++) {
		words[x] = *iter;
	}

	// bubble sort
	for (int i = 0; i < x - 1; i++) {
		for (int j = i + 1; j < x; j++) {
			if (words[i].compareTo(words[j]) == 1) {
				Word temp = words[i];
				words[i] = words[j];
				words[j] = temp;
			}
		}
	}

	// rewrite list
	std::list<Word> sortedList;

	for (int i = 0; i < x; i++) {
		sortedList.push_back(words[i]);
	}

	list = sortedList;

	delete[] words;
}