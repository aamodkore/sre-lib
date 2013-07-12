#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std ;

enum SwitchType { 
	ALPHA, BETA
}; 

class switch_queue {
	int range_ ; 
	bool switch_ ;
	
	queue<int> alphaQ_ ;
	queue<int> betaQ_ ;

	vector <bool> alphaVec_ ; 
	vector <bool> betaVec_ ; 

	private :
		void rangeCheck(int k) {
			if (range_>k && k>=0) ;
			else {
				cerr << "ERROR! : switch_queue : Value given(" << k << ") exceeds range(" << range_ << ")\n" ;
				exit(EXIT_FAILURE) ;
			}
		}
	
	public :
		switch_queue() :
			range_(2) ,
			alphaVec_(2,false) ,
			betaVec_(2,false) ,
			switch_(true) {}
		
		switch_queue(int range) :
			range_(range) ,
			alphaVec_(range,false) ,
			betaVec_(range,false) ,
			switch_(true) {}
		
		bool change() {
			return (switch_ = !switch_) ;
		}
		
		bool switch_to(SwitchType sw) {
			return (switch_ = sw) ;
		}
		
		bool switch_to(bool sw) {
			if (sw==ALPHA) return (switch_ = true) ;
			else return (switch_ = false) ;
		}
		
		bool state() {
			return switch_ ;
		}
		
		bool empty() {
			if (switch_) return alphaQ_.empty() ;
			else return betaQ_.empty() ;
		}
		
		int size() {
			if (switch_) return alphaQ_.size() ;
			else return betaQ_.size() ;
		}
		
		void push(int k) {
			rangeCheck(k) ;
			if (switch_) {
				if (!alphaVec_[k]) {alphaQ_.push(k); alphaVec_[k]=true;} }
			else {
				if (!betaVec_[k]) {betaQ_.push(k); betaVec_[k]=true;} }
		}
		
		void swush(int k) {
			rangeCheck(k) ;
			if (!switch_) {
				if (!alphaVec_[k]) {alphaQ_.push(k); alphaVec_[k]=true;} }
			else {
				if (!betaVec_[k]) {betaQ_.push(k); betaVec_[k]=true;} }
		}
		
		int pop() {
			int k ;
			if (switch_) {
				k = alphaQ_.front() ;
				alphaQ_.pop(); alphaVec_[k]=false ;
			}
			else {
				k = betaQ_.front() ;
				betaQ_.pop(); betaVec_[k]=false ;
			}
			return k ;
		}
		
		int& front() {
			if (switch_) return alphaQ_.front() ;
			else return betaQ_.front() ;
		}
} ;
