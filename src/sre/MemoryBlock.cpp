#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <algorithm>
#include <bdd.h>

#include "MemoryBlock.hpp"

using namespace std ;

struct sort_head_pred {
    bool operator()(const pair<int,int> &left, const pair<int,int> &right) {
        return ((left.first < right.first) || (left.first==right.first && left.second < right.second)) ;
    }
};

void MemoryBlock::makeBDD() {
	bdd x ;
	bddvalues_ = bddtrue ;
	if (varValues_.size()<varCount_) {
		cerr << "ERROR! : MemoryBlock : varCount_ , varValues_ size mismatch.\n" ;
		exit(EXIT_FAILURE) ;
	}
	else {
		for (int i=0; i<varCount_; i++) {
			if (varValues_[i]) x = bdd_ithvar(i) ;
			else  x = bdd_nithvar(i) ;
			bddvalues_ = bddvalues_ & x ;
		}	
	}
}

MemoryBlock::MemoryBlock() {
	bddvalues_ = bddtrue ;
	varValues_.clear() ;
	varCount_ = 0 ;
	strong_ = false ;
}

MemoryBlock::MemoryBlock(int count) {
	varValues_.clear() ;
	heads_.clear() ;
	varCount_ = count ;
	strong_ = false ;
	
	for (int i=0; i<count; i++) 
		varValues_.push_back(true) ;
	makeBDD() ;	
}

MemoryBlock::MemoryBlock(int count, vector<bool> &varVals) {
	varValues_.clear() ;
	heads_.clear() ;
	varCount_ = count ;
	strong_ = false ;
	
	for (int i=0; i<count; i++) 
		varValues_.push_back(varVals[i]) ;
	makeBDD() ;
}

MemoryBlock::MemoryBlock(vector<bool> varVals) {
	int count = varVals.size() ;
	
	varValues_.clear() ;
	heads_.clear() ;
	varCount_ = count ;
	strong_ = false ;
	
	for (int i=0; i<count; i++) 
		varValues_.push_back(varVals[i]) ;
	makeBDD() ;
}

MemoryBlock::MemoryBlock(vector<bool> varVals, vector<pair<int,int> > headVals) {
	int count = varVals.size() ;
	
	varValues_.clear() ;
	heads_.clear() ;
	varCount_ = count ;
	
	for (int i=0; i<count; i++) 
		varValues_.push_back(varVals[i]) ;
	makeBDD() ;
	
	if (headVals.empty()) strong_ = false ;
	else {
		for (int i=0; i<headVals.size(); i++) 
			heads_.push_back(headVals[i]) ;
		strong_ = true ;
		sortHeads() ;
	}
}

MemoryBlock::MemoryBlock(const MemoryBlock& mBlock) {
	varValues_.clear() ;
	varCount_ = mBlock.getVarCount() ;
	
	for (int i=0; i<varCount_; i++) 
		varValues_.push_back(mBlock.getVal(i)) ;
	makeBDD() ;
	
	strong_ = mBlock.strong() ;
	
	vector<pair<int,int> > headVals = mBlock.getHeads();
	for (int i=0; i<headVals.size(); i++) 
		heads_.push_back(headVals[i]) ;
}

void MemoryBlock::setVarVal (int varnum, bool varVal) {
	if (varnum>=varCount_) {
		cerr << "ERROR! : MemoryBlock : requested position exceeds varCount_. \n" ;
		exit(EXIT_FAILURE) ;
	}
	else {
		if (varValues_[varnum] != varVal) {
			varValues_[varnum] = varVal ;
			makeBDD() ;
		}
	}
}

bool MemoryBlock::getVal(int varnum) const {
	if (varnum>=varCount_) {
		cerr << "ERROR! : MemoryBlock : requested variable=" << varnum << " exceeds varCount_="<< varCount_ <<". \n" ;
		exit(EXIT_FAILURE) ;
	}
	return varValues_[varnum] ;
}

void MemoryBlock::addHead(int m, int n) {
	int headCount = heads_.size() ;
	for (int i=0; i<headCount; i++) {
		if (heads_[i].first==m && heads_[i].second==n ) {
			cout << "WARNING! : MemoryBlock : addHead : Head already present." << endl ;
			return ;
		}
	}
	heads_.push_back(make_pair(m,n)) ;
	strong_ = true ;
}
		
void MemoryBlock::removeHead(int m, int n) {
	for (int i=0; i<heads_.size(); i++) {
		if (heads_[i].first==m && heads_[i].second==n ) {
			heads_.erase(heads_.begin()+i) ; i-- ;
		}
	}
	if (heads_.size()==0) strong_ = false ;
}
	
void MemoryBlock::makeWeak() {
	heads_.clear() ;
	strong_ = false ;
}
	
void MemoryBlock::sortHeads() {
	sort(heads_.begin(), heads_.end(), sort_head_pred());
}


bool MemoryBlock::operator == (MemoryBlock mBlock) {
	if (strong_) {
		if (!mBlock.strong()) return false ;
		else {
			sortHeads() ; mBlock.sortHeads() ;
			int headCount = heads_.size() ;
			vector<pair<int,int> > headVals = mBlock.getHeads();
			for (int i=0; i<headCount; i++) {
				if (heads_[i].first!=headVals[i].first || heads_[i].second!=headVals[i].second )
					return false ;
			}
		}
	}
	else {
		if (mBlock.strong()) return false ;
	}
	for (int i=0; i<varCount_; i++) {
		if (varValues_[i] != mBlock.getVal(i))
			return false ;
	}
	
	return true ;
}

