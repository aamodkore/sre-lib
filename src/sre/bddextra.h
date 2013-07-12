#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <bdd.h>

using namespace std ;

#ifndef BDD_EXTRAS
#define BDD_EXTRAS

bool isTrue(bdd &tree_, vector<bool> &values_) {
	int varnum_ = bdd_varnum(), root=0;
	bdd valTree = tree_ ;
	if (varnum_>values_.size()) {
		cout << "ERROR! : BDD Extras : Vector of values too small." << endl ;
		exit(EXIT_FAILURE) ;
	}
	else {
		while (true) {
			if (valTree == bddtrue) {
				return true ;
			}
			else if (valTree == bddfalse) {
				return false ;
			}
			else {
				root = bdd_var(valTree) ;
				if (values_[root]) valTree = bdd_high(valTree) ;
				else valTree = bdd_low(valTree) ;
			}
		}
	}
	return false ;
}
			
#endif
