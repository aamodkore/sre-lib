#include <iostream>
#include <cstdio>
#include <vector>
#include <bdd.h>
#include <sre.h>

using namespace std ;

int main() {
	bdd_init(1000, 100) ;
	bdd_setvarnum(2) ;
	
	vector <bool> val1 (2,true) ;
	vector <bool> val2 (2,true) ;
	vector <bool> val3 (2,false) ;
	vector <bool> val4 (2,false) ;
	val2[1]=false; val3[1]=true;
	
	MemoryBlock a(val1),b(val2),c(val4),s(val3) ;
	vector <MemoryBlock> memvec ;
	memvec.push_back(a) ;
	memvec.push_back(b) ;
	memvec.push_back(c) ;
	
	AtomicExpr e1(WEAK_SYM,a), e3(WEAK_SYM,b), e6(WEAK_SYM,b);
	AtomicExpr e4(memvec) ;
	
	vector<AtomicExpr> atvec ;
	atvec.push_back(e1) ; atvec.push_back(e3) ; 
	atvec.push_back(e4) ; atvec.push_back(e6) ; 
	ProductExpr expr(atvec) ;
	
	Word word ;
	
	cout << "Inclusion for Word: " << expr.checkInclusion(word) << endl ;
	
	return 0 ;
}
	
