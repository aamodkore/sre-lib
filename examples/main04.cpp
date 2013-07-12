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
	s.addHead(0,0) ;
	
	Word wordX, wordY ;
	
	wordX.addLetter(a) ; wordX.addLetter(b) ; wordX.addLetter(c) ;
	wordX.addLetter(c) ; wordX.addLetter(a) ; 
	
	wordY.addLetter(a) ; wordY.addLetter(b) ; wordY.addLetter(c) ;
	
	cout << "Inclusion for Y in X: " << (wordY <= wordX) << endl ;
	cout << "Inclusion for X in Y: " << (wordY >= wordX) << endl ;
	cout << "Inclusion for empty word in X: " << (Word() <= wordX) << endl ;
	
	return 0 ;
}
	
