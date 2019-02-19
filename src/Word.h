#ifndef  WORD_H
#define WORD_H
#include <string>
using std::wstring; // uses wchar_t type for unicode characters

enum Gender {
	NONE = 0,
	MASCULINE = 1,
	FEMININE = 2,
	NEUTER = 3
};

enum PartOfSpeech {
	NOUN = 1,
	VERB = 2,
	PREPOSITION = 3,
	CARDINAL_NUMBER = 4,
	ADVERB = 5,
	ADJECTIVE = 6
};


class Word {
private:
	wstring englishWord;
	wstring germanWord;
	PartOfSpeech partOfSpeech;
	Gender gender;
public:
	// constructors
	Word();
	Word(wstring germanWord, PartOfSpeech partOfSpeech, wstring englishWord, Gender gender = Gender::NONE);
	// setters
	void setEnglishWord(wstring);
	void setGermanWord(wstring);
	void setPartOfSpeech(PartOfSpeech);
	void setGender(Gender);
	// getters
	wstring getEnglishWord();
	wstring getGermanWord();
	PartOfSpeech getPartOfSpeech();
	Gender getGender();
	// other
	wstring toString();

	// constants
	const static wchar_t A_LOW;
	const static wchar_t A_UP ;
	const static wchar_t O_LOW;
	const static wchar_t O_UP;
	const static wchar_t U_LOW;
	const static wchar_t U_UP;

	int compareTo(Word);
};
#endif // ! WORD_H
