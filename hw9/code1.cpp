#include "DoubleLinkList.h"

int main() {
	ST::DLL<int> l{1,2,3,4,3,5,8,6,6,8,7,2,3};
	l.popByValue(3);
	l.popByValue(6);

	l.corectSize();
}