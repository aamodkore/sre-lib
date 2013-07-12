#include <iostream>
#include <cstdio>
#include <vector>
#include <list>

#include "MemoryBlock.hpp"

using namespace std ;

#ifndef WORD_DEF
#define WORD_DEF

class Word {
	
	int letterCount_ ;
	vector<MemoryBlock> letters_ ;
	 
	public :
		
		Word() {letters_.clear(); letterCount_=0 ;}
		Word(vector<MemoryBlock>& mBlocks) ;
		Word(list<MemoryBlock*> mBlocks) ;
		
		void addLetter(MemoryBlock& mletter) ;
	
		int getLength() {return letterCount_ ;}
		int length() {return letterCount_ ;}
		bool empty() {return letters_.empty() ;}
		
		MemoryBlock getLetter(int n) ;
		
		MemoryBlock* letter(int i) ;
		
		void removeLetter(int i) ;
		
		bool operator <=(Word& word) ;
		bool operator >=(Word& word) ;
		
	
} ;

#endif
