#include <iostream>
#include <vector>
#include <bdd.h>

using namespace std ;

#ifndef MEMORY_BLOCK
#define MEMORY_BLOCK

class MemoryBlock {
	
	bdd bddvalues_ ;
	vector<bool> varValues_ ;
	int varCount_ ;
	bool strong_ ;
	vector<pair<int,int> > heads_ ;
	
	private :
		void makeBDD() ;
	
	public :
		
		MemoryBlock() ;
		MemoryBlock(int count) ;
		MemoryBlock(int count, vector<bool> &varVals) ;
		MemoryBlock(vector<bool> varVals) ;
		MemoryBlock(vector<bool> varVals, vector<pair<int,int> > headVals) ;
		MemoryBlock(const MemoryBlock& mBlock) ;
		
		bdd getBDD() {return bddvalues_ ;}
		bdd getBDDValues() {return bddvalues_ ;}
		vector<bool> *getVecValues() {return &varValues_ ;}
		bool getVal(int varnum) const ;
		int getVarCount() const {return varCount_ ;}
		
		bool strong() const {return strong_ ;}
		vector<pair<int,int> > getHeads() const {return heads_ ;}
		void addHead(int m, int n) ;
		void removeHead(int m, int n) ;
		void makeWeak() ;
		void sortHeads() ;
		
		void setVarVal (int varnum, bool varVal) ;
		
		bool operator == (MemoryBlock mBlock);
		
		
	
} ;

#endif
