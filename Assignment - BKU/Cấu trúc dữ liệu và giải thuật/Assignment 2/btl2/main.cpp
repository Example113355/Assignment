#include "ConcatStringTree.h"

int main() {
    
    HashConfig hashConfig(
        2,
        0.202826,
        0.854946,
        0.761086,
        3.40681,
        6
    );
    LitStringHash* litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree* s0 = new ReducedConcatStringTree("GwqWNM1dJf", litStringHash);
    cout << litStringHash->toString() << endl;
    cout<< litStringHash->getLastInsertedIndex()<<endl;
    ReducedConcatStringTree* s1 = new ReducedConcatStringTree("2Knle6wCEmqbeeI8KJK3", litStringHash);
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() << endl;
    ReducedConcatStringTree* s2 = new ReducedConcatStringTree("FPvNrImp7n1d0", litStringHash);
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() << endl;
    ReducedConcatStringTree* s3 = new ReducedConcatStringTree("wtbtDgcsc3U9yc5nadbd", litStringHash);
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() << endl;
    ReducedConcatStringTree* s4 = new ReducedConcatStringTree("QZL8dvdf", litStringHash);
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() << endl;
    ReducedConcatStringTree* s5 = new ReducedConcatStringTree("JJFjje", litStringHash);
    cout << litStringHash->toString() << endl;
    cout << litStringHash->getLastInsertedIndex() << endl;
    ReducedConcatStringTree* s6 = new ReducedConcatStringTree(s1->concat(*s2));
    cout << s6->toString() << endl;
    cout << s6->toStringPreOrder() << endl;
    cout << litStringHash->toString() << endl;

    delete s3;
    delete s6;
    cout << litStringHash->toString() << endl;

    return 0;
}