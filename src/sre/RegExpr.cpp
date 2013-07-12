#include <iostream>
#include <cstdlib>
#include <vector>

#include "RegExpr.hpp"
#include "ProductExpr.hpp"
#include "Word.hpp"

using namespace std ;

sre::sre(vector<ProductExpr>& termVec) {
	termCount_ = termVec.size() ;
	terms_.clear() ;
	
	for (int i=0; i< termCount_; i++) 
		terms_[i] = termVec[i] ;
}

sre::sre(Word& word) {
	termCount_ = 1 ;
	terms_.clear() ;
	ProductExpr pExpr (word);
	terms_.push_back(pExpr) ;
}

void sre::addProduct(ProductExpr& pExpr) {
	terms_.push_back(pExpr) ;
	termCount_++ ;
}

ProductExpr sre::getProduct(int i) {
	if (i<0 || i>=termCount_) {
		cerr << "ERROR! : SRE : Requested term (" <<i <<") exceeds termCount_(" <<termCount_ <<")." << endl ; 
		exit(EXIT_FAILURE) ;
	}
	else {
		return terms_[i] ;
	}
}

bool sre::checkInclusion(Word& test) {
	ProductExpr pExpr ;
	for (int i=0; i<termCount_; i++ ) {
		pExpr = terms_[i] ;
		if (pExpr.checkInclusion(test))
			return true ;
	}
	return false ;
}

bool sre::checkInclusion(ProductExpr& test) {
	ProductExpr pExpr ;
	for (int i=0; i<termCount_; i++ ) {
		pExpr = terms_[i] ;
		if (pExpr.checkInclusion(test))
			return true ;
	}
	return false ;
}

bool sre::checkInclusion(sre& rExpr) {
	ProductExpr pExpr ;
	int explen = rExpr.length() ;
	for (int i=0; i<explen; i++ ) {
		pExpr = rExpr.getProduct(i) ;
		if (!checkInclusion(pExpr))
			return false ;
	}
	return true ;
}

bool sre::operator <=(sre& rExpr) {
	return rExpr.checkInclusion(*this) ;
}

bool sre::operator >=(sre& rExpr) {
	return checkInclusion(rExpr) ;
}

