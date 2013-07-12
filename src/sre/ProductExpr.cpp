#include <iostream>
#include <cstdio>
#include <vector>

#include "switch_queue.h"
#include "ProductExpr.hpp"
#include "AtomicExpr.hpp"
#include "Word.hpp"
#include "MemoryBlock.hpp"

using namespace std ;


ProductExpr::ProductExpr(vector<AtomicExpr>& termVec) {
	termCount_ = termVec.size() ;
	for (int i=0; i<termCount_; i++) 
		terms_.push_back(termVec[i]) ;
}




void ProductExpr::addAtomic(AtomicExpr& aExpr){
	termCount_++ ;
	terms_.push_back(aExpr) ;
}


AtomicExpr ProductExpr::getAtomic(int i) {
	if (i<0 || i>=termCount_) {
		cerr << "ERROR! : ProductExpr : Requested term (" <<i <<") exceeds termCount_(" <<termCount_ <<")." << endl ; 
		exit(EXIT_FAILURE) ;
	}
	else {
		return terms_[i] ;
	}
}





bool ProductExpr::checkInclusion(Word& test) {
	switch_queue positions(termCount_+1) ;
	positions.push(0) ;
	
	AtomicExpr expr ;
	int wordlen = test.length(), pos ;
	
	for (int i=0; i<wordlen; i++) {
		if (positions.empty()) return false ;
		
		MemoryBlock block = test.getLetter(i) ;
		while (!positions.empty()) {
			pos = positions.pop() ;
			if (pos < termCount_) {
				expr = terms_[pos] ;
				switch (expr.getExprType()) {
					case STAR_EXPR :
						if (expr.checkInclusion(block))
							positions.swush(pos) ;
						positions.push(pos+1) ;
						break ;
					case WEAK_SYM :
						if (expr.checkInclusion(block))
							positions.swush(pos+1) ;
						positions.push(pos+1) ;
						break ;
					case STRONG_SYM :
						if (expr.checkInclusion(block))
							positions.swush(pos+1) ;
						break ;	
				}
			}
		}
		positions.change() ;
	}
	
	if (positions.empty()) return false ;
	while (!positions.empty()) {
		pos = positions.pop() ;
		if (pos < termCount_) {
			expr = terms_[pos] ;
			if (expr.checkInclusion()) positions.push(pos+1) ;
		}
		else if (pos == termCount_) return true ;
	}
	return false ;
}


bool ProductExpr::checkInclusion(ProductExpr& test) {
	switch_queue positions(termCount_+1) ;
	positions.push(0) ;
	
	AtomicExpr expr ;
	int explen = test.length(), pos ;
	
	for (int i=0; i<explen; i++) {
		if (positions.empty()) return false ;
		
		AtomicExpr aExpr = test.getAtomic(i) ;
		while (!positions.empty()) {
			pos = positions.pop() ;
			if (pos < termCount_) {
				expr = terms_[pos] ;
				switch (expr.getExprType()) {
					case STAR_EXPR :
						if (expr.checkInclusion(aExpr))
							positions.swush(pos) ;
						positions.push(pos+1) ;
						break ;
					case WEAK_SYM :
						if (expr.checkInclusion(aExpr))
							positions.swush(pos+1) ;
						positions.push(pos+1) ;
						break ;
					case STRONG_SYM :
						if (expr.checkInclusion(aExpr))
							positions.swush(pos+1) ;
						break ;	
				}
			}
		}
		positions.change() ;
	}
	
	if (positions.empty()) return false ;
	while (!positions.empty()) {
		pos = positions.pop() ;
		if (pos < termCount_) {
			expr = terms_[pos] ;
			if (expr.checkInclusion()) positions.push(pos+1) ;
		}
		else if (pos == termCount_) return true ;
	}
	return false ;
}


bool ProductExpr::operator <=(ProductExpr& pExpr) {
	return pExpr.checkInclusion(*this) ;
}
	
bool ProductExpr::operator >=(ProductExpr& pExpr) {
	return checkInclusion(pExpr) ;
}
