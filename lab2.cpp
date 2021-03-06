/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name:马致远
 * Student ID:517021910070
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(set<string> &english);

void show_ans(vector<string> &ans)
{
	cout << "Found ladder:";
	cout << ans[0];
	for (int i = 1; i < ans.size(); i++)
	{
		cout << "->" << ans[i];
	}
	cout << endl
		<< endl;
}

void input_words(string &start, string &dest)
{
	cout << "Enter start word (enter ':q' to quit):";
	cin >> start;
	if (start == ":q")
	{
		exit(0);
	}
	cout << "Enter destination word:";
	cin >> dest;
}

vector<string> getnextword(string&word, set<string>* dict , set<string>* used)
{
	vector<string> result;
	for (char c = 'a'; c <= 'z'; c++)
	{
		for (int i = 0; i < word.length(); i++) 
		{
			if (c == word[i]) 
			{
				continue;
			}
			string temp = word;
			temp[i] = c;//change one char in the string
			
			if (dict->find(temp) != dict->end()&&used->find(temp)==used->end())//that new word is in the dict and it is not used
			{
				result.push_back(temp);
				used->insert(temp);//record it,it is used
			}



		}
	}
	return result;

}
void read_english(set<string> &english)
{
	while (true)
	{
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		ifstream file_input(file_name.c_str());
		if (file_input.is_open())
		{
			string temp_word;
			while (getline(file_input, temp_word))
			{
				english.insert(temp_word);
			}
			break;
		}
	}
}

int main()
{
	set<string> english;
	set<string> usedwords;
	set<string>* dict = &english;
	set<string>* used = &usedwords;
	string start="";
	string dest="";
    read_english(english);
	input_words(start, dest);
	queue<vector<string>> q;//Create an empty queue
	vector<string> ladderone;
	vector<string> ans;
	ladderone.push_back(start);//Add the start word to a new ladder. 
	usedwords.insert(start);
	q.push(ladderone);//Add the ladder to the queue. 
	while (!q.empty())//while (the queue is not empty) 
	{
		vector<string> temp;
		temp = q.back();
		q.pop();//Dequeue the first ladder from the queue. 
		if (temp.back()==dest) //if (the final word in this ladder is the destination word) {Return this ladder as the solution.}
		{
			show_ans(temp);
			return 0;
		}
		vector<string> nextword = getnextword(temp.back(), dict,used);
		for (int i=0;i<nextword.size();i++)//each word in the lexicon of English words that differs by one letter
		{
				vector<string> newtemp = temp;
				newtemp.push_back(nextword[i]);
				q.push(newtemp);
				
			
		}
	}
	cout << "no ladder exists";


	
	return 0;
}

