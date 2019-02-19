#include <iostream>
#include <string>
#include "Word.h"
using std::wstring;

Noun::Noun(wstring englishWord, wstring germanWord) : Word(englishWord, germanWord) {
	
}

void Noun::setGender(Gender gender) {
	Noun::gender = gender;
}

Gender Noun::getGender() {
	return Noun::gender;
}

wstring Noun::toStringGerman() {

	wstring article;
	wstring word = getGermanWord();

	// determine the article
	switch (gender) {
	case Gender::MASCULINE:
		article = (wchar_t)("der ");
		break;
	case Gender::FEMININE:
		article = (wchar_t)("die ");
		break;
	case Gender::NEUTER:
		article = (wchar_t)("das ");
		break;
	}

	// [article] + [capitalized first letter] + [the rest of the word]
	return article + (wchar_t)toupper(word.at(0)) + word.substr(1, word.length());
}