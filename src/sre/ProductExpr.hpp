#include <iostream>
#include <vector>

#include "AtomicExpr.hpp"
#include "Word.hpp"

using namespace std ;

#ifndef PRODUCT_EXPR
#define PRODUCT_EXPR

class ProductExpr {
	
	int termCount_ ;
	vector <AtomicExpr> terms_ ;
	 
	public :
		
		ProductExpr() {termCount_ = 0; terms_.clear() ;}
		ProductExpr(vector<AtomicExpr>& termVec) ;
		
		void addAtomic(AtomicExpr& aExpr) ;
		
		AtomicExpr getAtomic(int i) ;
		int length() {return termCount_ ;}
		
		bool checkInclusion(Word& test) ;
		
		bool checkInclusion(ProductExpr& test) ;
		bool operator <=(ProductExpr& pExpr) ;
		bool operator >=(ProductExpr& pExpr) ;
		
} ;

#endif
