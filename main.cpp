#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <typeinfo>

//valid symbols:
const std::string Symbols = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz�������";
const std::string Capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ���";

typedef std::map<std::string, size_t> WordCount;
typedef std::multimap<size_t, std::string> CountWord;

template<typename A, typename B>
std::pair<B,A> flip(const std::pair<A, B> &pair)
{
	return std::pair<B, A>(pair.second, pair.first);
}


void countWords(const std::string inputFile, WordCount &WordCounter )
{
	std::fstream file;
	file.open(inputFile.c_str(), std::ios::in);
	std::string fileLine;
	std::string word;

	while (!file.eof())
	{
		getline(file, fileLine);

		std::string::iterator it;
		for (it = fileLine.begin(); it != fileLine.end(); ++it)
		{
			//search for other symbols and replace them:
			if (Symbols.find(*it) > Symbols.length())
			{
				*it = ' ';
			}
			else if (Capital.find(*it) < Capital.length()) {

				*it += 32;
			}
		}

		std::stringstream ssline(fileLine); //sstram for fileLine

		while (ssline >> word)
		{
			WordCounter[word]++;
		}
	}
	file.close();
}

CountWord flipMap(WordCount &WordCounter)
{
	CountWord CountWord;
	for (std::map<std::string, size_t>::iterator itr = WordCounter.begin(); itr != WordCounter.end(); ++itr)
	{
		CountWord.insert(flip(*itr));
	}
	return CountWord;
}
void printCounter_tofile(CountWord& CountWord, const std::string outputFile)
{
	std::fstream output;
	output.open(outputFile.c_str(), std::ios::out);

	for (std::map<size_t, std::string>::iterator itr = --CountWord.end(); itr != CountWord.begin(); --itr)
	{
		output << itr->first << " " << itr->second << std::endl;
	}
	output.close();
}

void findWord(const std::string word, WordCount &WordCounter)
{
	std::cout << "Das Wort \"" << word << "\" kommt " << WordCounter[word] << " mal vor." << std::endl;
}

void printCounter(CountWord& CountWord)
{


	for (std::map<size_t, std::string>::iterator itr = --CountWord.end(); itr != CountWord.begin(); --itr)
	{
		std::cout << itr->first << " " << itr->second << std::endl;
	}

}


int main()
{

	WordCount myCounter1; //to count and find words
	WordCount myCounter2;

	countWords("text1.txt",  myCounter1);
	countWords("text2.txt",  myCounter2);

	CountWord myCountWord1 = flipMap(myCounter1); // to print ordered histogramm
	CountWord myCountWord2 = flipMap(myCounter2);

	//printCounter(myCountWord1);
	printCounter(myCountWord2);

	findWord("et", myCounter2);

	//system("pause");
	return 0;
}
