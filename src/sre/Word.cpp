#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>

#include "MemoryBlock.hpp"
#include "Word.hpp"
#include "RegExpr.hpp"

using namespace std ;

Word::Word(vector<MemoryBlock>& mBlocks) {
	letterCount_ = mBlocks.size() ;
	for (int i=0;i<letterCount_;i++) {
		letters_[i]=mBlocks[i];
	}
}

Word::Word(list<MemoryBlock*> mBlocks) {
	letterCount_ = mBlocks.size() ;
	while (!mBlocks.empty()) {
		addLetter(*(mBlocks.front()));
		mBlocks.pop_front() ;
	}
}

void Word::addLetter(MemoryBlock& mletter){
	MemoryBlock mBlock (mletter) ;
	letters_.push_back(mBlock) ;
	letterCount_ ++ ;
}

MemoryBlock Word::getLetter(int i) {
	if (i<letterCount_){
		return letters_[i] ;
	}
	else {
		cerr << "ERROR! : Word : Length of word is shorter." << endl ;
		exit(EXIT_FAILURE) ;
	}
}

MemoryBlock* Word::letter(int i) {
	if (i<letterCount_){
		return &(letters_[i]) ;
	}
	else {
		cerr << "ERROR! : Word : Length of word is shorter." << endl ;
		exit(EXIT_FAILURE) ;
	}
}

void Word::removeLetter(int i) {
	if (i<letterCount_){
		letters_.erase(letters_.begin()+i) ;
		letterCount_ -- ;
	}
	else {
		cerr << "ERROR! : Word : Length of word is shorter." << endl ;
		exit(EXIT_FAILURE) ;
	}
}

bool Word::operator <=(Word& word) {
	sre rExpr (word) ;
	return rExpr.checkInclusion(*this) ;
}
	
	
bool Word::operator >=(Word& word) {
	return word<=(*this) ;
}
