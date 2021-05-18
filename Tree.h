#pragma once
#include "../menu.h"
#include <string>
#include <iostream>
#include <time.h>
#include <string>

struct Tree_Item {
public:
	int inf;
	Tree_Item* NextParent;
	Tree_Item* NextChild;
};

int stop = false;
Tree_Item* pRoot;
Tree_Item* pFind = new Tree_Item();


std::string Show(Tree_Item* pCurrent = pRoot) {
	std::string str = "";
	while (pCurrent != NULL) {
		str += "\n|| " + std::to_string(pCurrent->inf) + " ||: ";
		Tree_Item* pCurrent_Child = pCurrent->NextChild;
		while (pCurrent_Child != NULL) {
			str += " || " + std::to_string(pCurrent_Child->inf) + " || ";
			pCurrent_Child = pCurrent_Child->NextChild;
		}
		pCurrent = pCurrent->NextParent;
	}
	return str;
}

int Push(int inf1, int inf2, Tree_Item* pCurrent = pRoot) {
	while (pCurrent != NULL) {
		if (pCurrent->inf == inf1) {
			Tree_Item* pTemp = new Tree_Item();
			pTemp->NextChild = pCurrent->NextChild;
			pCurrent->NextChild = pTemp;
			pTemp->inf = inf2;
			return 1;
		}
		Tree_Item* pCurrent_Child = pCurrent->NextChild;
		while (pCurrent_Child != NULL) {
			if (pCurrent_Child->inf == inf1 && pCurrent_Child->NextParent == NULL) {
				Tree_Item* pTempParent = new Tree_Item(); Tree_Item* pTemp = new Tree_Item();
				pTempParent->NextParent = pCurrent->NextParent;
				pCurrent->NextParent = pTempParent;
				pTempParent->inf = pCurrent_Child->inf;
				pTempParent->NextChild = pTemp;
				pTemp->inf = inf2;
				pCurrent_Child->NextParent = pTempParent;
				return 1;
			}
			pCurrent_Child = pCurrent_Child->NextChild;
		}
		pCurrent = pCurrent->NextParent;
	}
	return 0;
}

/**/

int Delete(int inf, Tree_Item* pCurrent = pRoot) {
	Tree_Item* pPred_Parent;
	while (pCurrent != NULL) {
		if (pCurrent->inf == inf) {
			Tree_Item* pParent = pCurrent = pRoot;
			while (pParent != NULL) {
				Tree_Item* pChild = pParent->NextChild;
				Tree_Item* pChild_Pred = pParent;
				while (pChild != NULL) {
					if (pChild->inf == inf) {
						pChild_Pred->NextChild = pChild->NextChild;
						Tree_Item* pLast = pParent->NextChild;
						while (pLast->NextChild != NULL) {
							pLast = pLast->NextChild;
						}
						pLast->NextChild = pChild->NextParent->NextChild;
						//pChild->NextParent = NULL;
						pCurrent->NextParent = pCurrent->NextParent->NextParent;
						delete(pChild);
						return 1;
					}
					pChild_Pred = pChild;
					pChild = pChild->NextChild;
				}
				pParent = pParent->NextParent;

			}
		}
		Tree_Item* pCurrent_Child = pCurrent->NextChild;
		Tree_Item* pPred_Child = pCurrent;
		while (pCurrent_Child != NULL) {
			if (pCurrent_Child->inf == inf && pCurrent_Child->NextParent == NULL) {
				pPred_Child->NextChild = pCurrent_Child->NextChild;
				delete(pCurrent_Child);
				if (pCurrent->NextChild == NULL) {
					Tree_Item* pCur = pRoot;
					Tree_Item* pPred = pRoot;
					while (pCur != NULL) {
						if (pCur == pCurrent) {
							pPred->NextParent = pCur->NextParent;
							delete(pCur);
							return 1;
						}
						pPred = pCur;
						pCur = pCur->NextParent;
					}
				}
				return 1;
			}
			pPred_Child = pCurrent_Child;
			pCurrent_Child = pCurrent_Child->NextChild;
		}
		pPred_Parent = pCurrent;
		pCurrent = pCurrent->NextParent;
	}
	return 0;
}

int Search(int inf, Tree_Item* pCurrent = pRoot) {
	while (pCurrent != NULL) {
		Tree_Item* pCurrent_Child = pCurrent->NextChild;
		while (pCurrent_Child != NULL) {
			if (pCurrent_Child->inf == inf) return pCurrent->inf;
			pCurrent_Child = pCurrent_Child->NextChild;
		}
		pCurrent = pCurrent->NextParent;
	}
	return -1;
}