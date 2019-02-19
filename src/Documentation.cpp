/*
CIT-284 Advanced C++/OOP
Programming Project 2

Professor:			Arland J. Richmond
Student:			Aliaksei Petrusevich
Date Submited:		March 24, 2018


Project Guidelines:

Student's task in this project is tp create a German-English dictionary. The student
will be responsible for entering a total of tenty-five words in German, the part of speech
each word represents and its English meaning. The list is contains the following words

[German Words]			[Part of speech]		[English meaning]

der Mann				noun					man
das Öl					noun					oil
die Frau				noun					woman
das Fräulein			noun					Miss
das Mädchen				noun					girl
das Kind				noun					child
das Haus				noun					house
die Schule				noun					school
die Tür					noun					door
kommen					verb					to come
gehen					verb					to go
sehen					verb					to see
wollen					verb					to want
wissen					verb					to know
können					verb					to be able
vor						preposition				before
nach					preposition				after
zu						preposition				to
bis						preposition				until
ohne					preposition				without
eins					cardinal number			one
zwei					cardinal number			two
drei					cardinal number			three
hoch					adverb					high
gut						adjective/adverb		good


All nouns must begin with a definite article (der, die, das; masculine, feminine, and neuter
in German). All nouns in German must begin with a capital letter, all verbs are presented
in their infinite form.

The student must create a file by prompting himself for the necessary information and then
close the file and do not allow the file to be modified thereafter. The student must program
functionkeys to deal with umlauted letters.

When a menu selection is made (other than 1, 8 or 9) the word list must be sorted in ascending
order and the output should include part of speech and English meaning. Words with special 
characters are to be treated as if the special character is not present; however, the student 
must print that character. In a language such as German, sorting cannot be done by definite article; 
again, however, the article must be placed prior to the word as indicated in the word list.
Options 2 through 9 cannot be selected until the list is created. If this is attempted,
an error message should be displayed. Item 8 should simply be "Enter a word:"



Project description:

	The project is designed to challenge students with extended ASCII table characters, which are not
supported by regular 'char' datatype. Likewise, regular operations with 'string' object cannot
be performed. Thus, 'wchar_t' and 'wsring' are used instead. As a result, other functions
must be used for C-string and wstring operations: wfstream, wcout, wcsstr, etc.
	The project contains a single Word class that is used as a model for every German word. The class
contains german word, english meaning, gender, and part of speech. The latter two are of enumeration
type for simplicity as well as for more practice with that fundamental structure.
	Although pointers do present in the project, their presence was brought to minimum for the purpose
of time and avoidance of possible errors while working with wchar_t type strings.

	Testing was successfylly completed without any noticeable errors or bugs. Based on the output
of the program, it was concluded that the requirements of the project were fulfilled as requested
by the project description.

*/