// WordCount.cpp
// Tianrui Hu 8355711 05/13/2020
#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {
//	for (size_t i = 0; i < CAPACITY; i++) {
 //   table[i] = vector<pair<std::string, int>>;
 // }
}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getNumUniqueWords() const {
	int result = 0;
	for(int i = 0; i < (int)CAPACITY; i++){
		result += table[i].size();
	}
	return result;
}

int WordCount::getTotalWords() const {
	int result = 0;
	for(int i = 0; i < (int)CAPACITY; i++){
		for(size_t j = 0; j < table[i].size();j++){
			result += table[i].at(j).second;
		}
	}
	return result;
}

int WordCount::getWordCount(std::string word) const {
	word = makeValidWord(word);
	int key = hash(word);
	int result;
	for(size_t j = 0; j < table[key].size();j++){
		if(table[key].at(j).first==word)
			result = table[key].at(j).second;
	}
	return result;
}
	
int WordCount::incrWordCount(std::string word) {
	word = makeValidWord(word);
	if(word=="")
		return 0;
	int key = hash(word);
	bool present = false;
	int result;
	for(size_t j = 0; j < table[key].size();j++){
		if(table[key].at(j).first==word){
			table[key].at(j).second++;
			present = true;
			result = table[key].at(j).second;
		}
	}
	if(!present){
		table[key].push_back(std::pair<std::string, int>(word,1));
		result = 1;}
	return result;
}

int WordCount::decrWordCount(std::string word) {
	word = makeValidWord(word);
	if(word=="")
		return 0;
	int key = hash(word);
	bool present = false;
	int result;
	for(size_t j = 0; j < table[key].size();j++){
		if(table[key].at(j).first==word){
			present = true;
			if(table[key].at(j).second==1){
				result = 0;
				table[key].erase(table[key].begin()+j);
			}
			else{
			table[key].at(j).second--;
			result = table[key].at(j).second;
			}
		}
	}
	if(!present){
		return -1;}
	return result;
}

bool WordCount::isWordChar(char c) {
	if((c>=65&&c<=90)||(c>=97&&c<=122))
		return true;
	return false;
}

std::string WordCount::makeValidWord(std::string word) {
	std::string result;
	bool valido = false;
	for (size_t i = 0; i < word.size(); i++) {
		if(isWordChar(word.at(i))||word.at(i)==39||word.at(i)==45)
			result+=word.at(i);
	}
	for (size_t i = 0; i < word.size(); i++)
		if(isWordChar(word.at(i)))
			valido = true;
	if(!valido)
		return "";
	//int start=0,end=result.size()-1;
	//bool st=0,et=0;

	for (size_t i = 0; i < result.size(); i++) {
		if(result.at(i)>=65&&result.at(i)<=90)
			result.at(i) = result.at(i) + 32;}

	for (size_t i = 0; i < result.size(); i++) {
		
		if(result.at(0)==39||result.at(0)==45)
		  { //cout << result.at(0) << endl;
			result.erase(result.begin()+0);}
		else
			{//start = i;
			break;}
	//	st=1;
	}
	for (size_t i = result.size()-1; i >= 0 ; i--) {
		if(result.at(i)==39||result.at(i)==45)
			result.erase(i);
		else
			{//end = i;
			break;}
		//	et=1;
	}
	//if(st)
	//result.erase(result.begin(),result.begin()+start-1);
	//if(et)
	//result.erase(result.begin()+result.size()-end,result.begin()+result.size()-1);
	return result;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	int num = getNumUniqueWords();
	std::pair<std::string, int> list[num], temp;
	for(int i = 0; i< num;){
		for(int j =0; j< CAPACITY; j++){
			if(!table[j].empty()){
				for(size_t k = 0; k < table[j].size();k++){
					list[i] = table[j].at(k);
					i++;
				}
			}
		}
	}
	for(int i = 0; i< num;i++){
		for(int j = i+1; j<num;j++){
			if(list[i].first<list[j].first){
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
	for(int i = 0; i< num;i++){
	out << list[i].first << "," << list[i].second << "\n";
	}
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	int num = getNumUniqueWords();
	std::pair<std::string, int> list[num], temp;
	for(int i = 0; i< num;){
		for(int j =0; j< CAPACITY; j++){
			if(!table[j].empty()){
				for(size_t k = 0; k < table[j].size();k++){
					list[i] = table[j].at(k);
					i++;
				}
			}
		}
	}
	for(int i = 0; i< num;i++){
		for(int j = i+1; j<num;j++){
			if(list[i].second>list[j].second){
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
			if(list[i].second==list[j].second&&list[i].first>list[j].first){
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
	for(int i = 0; i< num;i++){
	out << list[i].first << "," << list[i].second << "\n";
	}
}

void WordCount::addAllWords(std::string text) {
	std::string insert = "";
	for (size_t i = 0; i < text.size(); i++) {
		if(text.at(i)==32)
		{   
			incrWordCount(insert);
			insert = "";
		}else
		if(text.at(i)==92&&(text.at(i)==110||text.at(i)==116))
		{
			incrWordCount(insert);
			insert = "";
			i++;
		}
		else
		insert += text.at(i);
	}
	if(insert!="")
		incrWordCount(insert);
	return;
}
