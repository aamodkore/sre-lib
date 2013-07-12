#include <iostream>
#include <cstdio>
#include <vector>
#include <bdd.h>
#include "AtomicExpr.hpp"
#include "MemoryBlock.hpp"
#include "bddextra.h"

using namespace std ;


AtomicExpr::AtomicExpr(vector <MemoryBlock>& mBlocks): ExprType_(STAR_EXPR) {
	blocknum_ = 0 ; 
	combined_ = bddfalse;
	for (int i=0; i<mBlocks.size(); i++) {
		combined_ = combined_ | mBlocks[i].getBDDValues() ;
		blocknum_++ ;
	}
}

AtomicExpr::AtomicExpr(AtomicType type, MemoryBlock& block) : 
	symbol_(block) {
		ExprType_ = type ;
		combined_ = block.getBDD() ;
	}

AtomicExpr::AtomicExpr(MemoryBlock& block) : 
	symbol_(block) {
		if (block.strong()) ExprType_ = STRONG_SYM ;
		else ExprType_ = WEAK_SYM ;
		combined_ = block.getBDD() ;
	}
		

void AtomicExpr::addBlock(MemoryBlock& mBlock) {
	combined_ = combined_ | mBlock.getBDDValues() ;
	blocknum_++ ;
}

bool AtomicExpr::checkInclusion(MemoryBlock& test) {
	vector<bool> *testVals = test.getVecValues() ;
	switch (ExprType_) {
		case STAR_EXPR :
			return isTrue(combined_, *testVals) ;
			break ;
		case WEAK_SYM :
		case STRONG_SYM :
		default :
			return (symbol_ == test) ;
			break ;
	}

}

bool AtomicExpr::checkInclusion() {
	return !(ExprType_ == STRONG_SYM) ;
}
		
bool AtomicExpr::checkInclusion(AtomicExpr& atomicExpr) {
	bdd test ;
	switch (ExprType_) {
		case STAR_EXPR :
			if (atomicExpr.getExprType()==STRONG_SYM)
				return false ;
			test = atomicExpr.getBDD() ;
			test = !(test) | combined_ ;
			return (test == bddtrue) ;
			break ;
		case WEAK_SYM :
		case STRONG_SYM :
			if (ExprType_ != atomicExpr.getExprType())
				return false ;
			else {
				if (symbol_ == atomicExpr.getSymbol())
					return true ;
				else return false ;
			}
	}
}

bool AtomicExpr::operator >=(AtomicExpr& atomicExpr) {
	return checkInclusion(atomicExpr) ;
}

bool AtomicExpr::operator <=(AtomicExpr& atomicExpr) {
	return atomicExpr.checkInclusion(*this) ;
}



