#include <iostream>
#include <cstdio>
#include <vector>
#include <bdd.h>
#include "MemoryBlock.hpp"

using namespace std ;

#ifndef ATOMIC_EXPR_DEF
#define ATOMIC_EXPR_DEF

enum AtomicType { 
	WEAK_SYM,
	STRONG_SYM,
	STAR_EXPR
}; 

class AtomicExpr {
	
	int blocknum_ ;
	bdd combined_ ;
	MemoryBlock symbol_ ;
	AtomicType ExprType_ ;
	 
	public :
		
		AtomicExpr(vector<MemoryBlock>& mBlocks) ;
		AtomicExpr() {ExprType_ = STAR_EXPR ; blocknum_ = 0 ; combined_ = bddfalse;}
		AtomicExpr(AtomicType type) {ExprType_ = type ;}
		AtomicExpr(MemoryBlock& block) ;
		AtomicExpr(AtomicType type, MemoryBlock& block) ;
		
		AtomicType getExprType() {return ExprType_ ;}
		MemoryBlock getSymbol() {return symbol_ ;}
		
		bool checkInclusion() ;
		
		int blocknum() {return blocknum_ ;}
		int getBlockNum() {return blocknum_ ;}
		bdd getBDD() {return combined_ ;}
		
		void addBlock(MemoryBlock& mBlock);
		
		bool checkInclusion(MemoryBlock& test) ;
		
		bool checkInclusion(AtomicExpr& atomicExpr) ;
		
		bool operator <= (AtomicExpr& atomicExpr) ;
		bool operator >= (AtomicExpr& atomicExpr) ;
	
} ;

#endif
