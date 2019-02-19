#include <string>
#include <iostream>
#include <cstring>
#include "Word.h"
using std::wstring;

const wchar_t Word::A_LOW = L'\x84';
const wchar_t Word::A_UP = L'\x8E';
const wchar_t Word::O_LOW = L'\x94';
const wchar_t Word::O_UP = L'\x99';
const wchar_t Word::U_LOW = L'\x81';
const wchar_t Word::U_UP = L'\x9A';

// constructors

Word::Word() {

}

Word::Word(wstring germanWord, PartOfSpeech partOfSpeech, wstring englishWord, Gender gender) {
	Word::germanWord = germanWord;
	Word::partOfSpeech = partOfSpeech;
	Word::englishWord = englishWord;
	Word::gender = gender;
}

// setters

void Word::setEnglishWord(wstring englishWord) {
	_wcslwr_s(const_cast<wchar_t*>(englishWord.c_str()), englishWord.length());
}

void Word::setGermanWord(wstring germanWord) {
	_wcslwr_s(const_cast<wchar_t*>(germanWord.c_str()), germanWord.length());
}

void Word::setPartOfSpeech(PartOfSpeech partOfSpeech) {
	Word::partOfSpeech = partOfSpeech;
}

void Word::setGender(Gender gender) {
	Word::gender = gender;
}

// getters

wstring Word::getEnglishWord() {
	return Word::englishWord;
}

wstring Word::getGermanWord() {
	return Word::germanWord;
}

PartOfSpeech Word::getPartOfSpeech() {
	return Word::partOfSpeech;
}

Gender Word::getGender() {
	return Word::gender;
}

// other

wstring Word::toString() {

	wstring article = L"";

	// if part of speech is a noun
	if (Word::partOfSpeech == PartOfSpeech::NOUN) {
		switch (Word::gender)
		{
		case Gender::MASCULINE:
			article = L"der";
			break;
		case Gender::FEMININE:
			article = L"die";
			break;
		case Gender::NEUTER:
			article = L"das";
			break;
		}

		// capitalize first letter of german word
		germanWord.replace(0, 1, ( L"" + towupper(germanWord.at(0) ) ) );
	}

	// else article will be empty wstring L""
	
	return (article + L" " + germanWord);
}

int Word::compareTo(Word word) {

	wstring thisString = this->germanWord;
	wstring comparableString = word.germanWord;


	// make strings of equal length if necessary
	if (thisString.length() > comparableString.length()) {
		comparableString.append(thisString.length() - comparableString.length(), ' ');
	}
	else if (thisString.length() < comparableString.length()){
		thisString.append(comparableString.length() - thisString.length(), ' ');
	}
	
	// i for thisString, j for comparable string
	for (int i = 0, j = 0; i < thisString.length(), j < comparableString.length();) {
		// beyond 127 is extended ascii table containing umlaut characters
		if (thisString.at(i) > 127 && comparableString.at(j) > 127) {
			// if both are umlauts
			i++; j++; 
		}
		else if (thisString.at(i) > 127) {
			// first word current character is umlaut
			i++;
		}
		else if (comparableString.at(j) > 127) {
			// second word current character is umlaut
			j++;
		}
		else {
			// both current characters are not umlauts
			// if first not umlaut is greater than second not umlaut
			if (thisString.at(i) > comparableString.at(j)) return 1;
			// else if first not umlaut is less than second niot umlaut
			else if (thisString.at(i) < comparableString.at(j)) return -1;
			else {
				// else both characters are equal
				i++; j++;
			}
		}
	}


	// strings are equal
	return 0;
}