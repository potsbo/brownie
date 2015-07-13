#pragma once
#include <stdio.h>
#include <set>
using namespace std;
// 和集合の計算
template<typename T> 
set<T> Union(set<T>& rsettA, set<T>&rsettB) {
	set<T> settUnion(rsettA);
	for(T c : rsettB){
		settUnion.insert(c);
	}
	return settUnion;
}

// 積集合の計算
template<typename T>
set<T> Product(set<T>& rsettA, set<T>&rsettB) {
	set<T> settProduct;
	for(T c : rsettB){
		if(rsettA.find(c) != rsettA.end())
			settProduct.insert(c);
	}
	return settProduct;
}

// 補集合の計算
/* template<class T> set<T> Complement(set<T>& rsettA, set<T>&rsettB) { */
/* 	set<T> settComplement(rsettA); */
/* 	for (set<T>::iterator itt = rsettB.begin(); itt != rsettB.end(); itt++) { */
/* 		settComplement.erase(*itt); */
/* 	} */
/* 	return settComplement; */
/* } */
