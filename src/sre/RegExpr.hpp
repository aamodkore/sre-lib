#include <iostream>
#include <vector>

#include "ProductExpr.hpp"
#include "Word.hpp"

using namespace std ;

#ifndef SRE_DEF
#define SRE_DEF

class sre {
	
	int termCount_ ;
	vector <ProductExpr> terms_ ;
	 
	public :
		
		sre() {termCount_ = 0; terms_.clear() ;}
		sre(vector<ProductExpr>& termVec) ;
		
		void addProduct(ProductExpr& aExpr) ;
		
		ProductExpr getProduct(int i) ;
		int length() {return termCount_ ;}
		
		bool checkInclusion(Word& test) ;
		bool checkInclusion(ProductExpr& test) ;
		
		bool checkInclusion(sre& test) ;
		bool operator <=(sre& test) ;
		bool operator >=(sre& test) ;
	
} ;

#endif
