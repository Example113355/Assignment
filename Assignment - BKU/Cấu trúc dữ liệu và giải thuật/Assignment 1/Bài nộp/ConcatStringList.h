#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class CharAlNode {
public:
    string s;
    CharAlNode* next;

    CharAlNode() {

    }

    CharAlNode(string s, CharAlNode* next) {
        this->s = s;
        this->next = next;
    }

    string reverseStr()
    {
        string h = s;
        int n = h.length();
        for (int i = 0; i < n / 2; i++)
            swap(h[i], h[n - i - 1]);
        return h;
    }
};

class refNode {
public:
    CharAlNode* refItem;
    int count;
    refNode* next;

    refNode() {
        count = 0;
        refItem = 0;
        next = 0;
    }

    refNode(CharAlNode* item) {
        refItem = item;
        count = 0;
        next = 0;
    }
};


class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    class delNode {
    public:
        delNode* next;
        refNode* refHead;
        refNode* refTail;
        bool check_concat;

        delNode() {
            refHead = refTail = 0;
            next = 0;
            check_concat = 0;
        }
        delNode(ConcatStringList* item) {
            refHead = refList.search(item->head);
            refTail = refList.search(item->tail);
            next = 0;
            check_concat = item->cc;
        }
        int countRef() {
            if (refHead == refTail) {
                return refHead->count;
            }
            else {
                return refHead->count + refTail->count;
            }
        }
    };
    // TODO: may provide some attributes

public:
    CharAlNode* head;
    CharAlNode* tail;
    int size;
    bool cc;

    ConcatStringList(const char* s) {
        string h = s;
        head = new CharAlNode(h, NULL);
        tail = head;
        size = h.length();
        refList.add(head);
        refList.add(tail);
        cc = 0;
    }
    ConcatStringList(CharAlNode* head, CharAlNode* tail) {
        this->head = head;
        this->tail = tail;
        cc = 0;
    }
    void add(string s) {            // theem vao cuoi
        CharAlNode* temp = new CharAlNode(s, 0);
        if (head == 0) {
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
        size += s.length();
    }
    void apend(string s) {
        CharAlNode* temp = new CharAlNode(s, 0);
        if (head == 0) {
            head = temp;
            tail = temp;
            size += s.length();
        }
        else {
            temp->next = head;
            head = temp;
        }
        size += s.length();
    }
    int length() const {
        return size;
    }
    char get(int index) const {
        if (index >= size)
            throw out_of_range("Index of string is invalid!");
        else {
            CharAlNode* temp = head;
            while (index > temp->s.length()) {
                index = index - temp->s.length();
                temp = temp->next;
            }
            return temp->s[index];
        }
    }
    int indexOf(char c) const {
        CharAlNode* temp = head;
        int k = 0;
        for (int i = 0; i < size; i++) {
            if (temp->s[i - k] == c)
                return i;
            else if (temp->s[i - k + 1] == 0) {
                temp = temp->next;
                k = i + 1;
            }
        }
        return -1;
    }
    std::string toString() const {
        string h = "";
        for (CharAlNode* temp = head; temp != tail->next; temp = temp->next) {
            h += temp->s;
        }
        return h;
    }
    ConcatStringList concat(const ConcatStringList& otherS) const {
        tail->next = otherS.head;
        refList.add(this->head);
        refList.add(otherS.tail);
        ConcatStringList* temp = new ConcatStringList(this->head, otherS.tail);
        temp->size = this->size + otherS.size;
        temp->cc = 1;
        return *temp;
    }
    ConcatStringList subString(int from, int to) const {
        if ((to > size || from >= size || to < 0 || from < 0 || size == 0)) {
            throw out_of_range("Index of string is invalid");
        }
        if (from >= to)
            throw logic_error("Invalid range");
        CharAlNode* temp = head;
        while (from >= temp->s.length()) {
            from -= temp->s.length();
            to -= temp->s.length();
            temp = temp->next;
        }
        ConcatStringList* key = new ConcatStringList(0, 0);
        int size = temp->s.length();
        key->add((temp->s).substr(from, min(to - from, size - from)));
        if (to < size - from + 1) {
            refList.add(key->head);
            refList.add(key->tail);
            return *key;
        }
        to -= temp->s.length();
        temp = temp->next;
        while (to > temp->s.length()) {
            key->add(temp->s);
            to -= temp->s.length();
            temp = temp->next;
        }
        key->add((temp->s).substr(0, to));
        refList.add(key->head);
        refList.add(key->tail);
        return *key;
    }
    ConcatStringList reverse() const {
        CharAlNode* temp = head;
        ConcatStringList* key = new ConcatStringList(0, 0);
        key->size = this->size;
        string h;
        while (temp != tail->next) {
            h = temp->reverseStr();
            key->apend(h);
            temp = temp->next;
        }
        refList.add(key->head);
        refList.add(key->tail);
        return *key;
    }

    void clear() {
        CharAlNode* temp = head->next;
        while (temp != 0) {
            CharAlNode* item = temp;
            temp = temp->next;
            delete item;
        }
    }
    ~ConcatStringList() {
        refList.minus(head);
        refList.minus(tail);
        delNode* temp = new delNode(this);
        //cout << head << " " << tail << endl;
        delStrList.add(temp);
        delStrList.check();
        refList.check();
    }

public:
    class ReferencesList {
        // TODO: may provide some attributes
    public:
        refNode* head;
        refNode* tail;
        int length;

    public:
        ReferencesList() {
            head = tail = 0;
            length = 0;
        }
        int size() const {
            return length;
        }
        int refCountAt(int index) const {
            if (index < 0 || index >= length) {
                throw out_of_range("Index of references list is invalid!");
            }
            refNode* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->count;
        }
        std::string refCountsString() const {
            string h = "RefCounts[";
            for (refNode* temp = head; temp != 0; temp = temp->next) {
                if (temp != head) {
                    h += ",";
                }
                h += to_string(temp->count);
            }
            h += "]";
            return h;
        }
        void add(CharAlNode* temp) {
            refNode* pre;
            bool flag = false;
            for (pre = head; pre != 0; pre = pre->next) {
                if (pre->refItem == temp) {
                    pre->count++;
                    this->remove(pre);
                    this->addIndex(pre);
                    return;
                }
            }
            refNode* key = new refNode(temp);
            key->count = 1;
            this->addIndex(key);
        }
        void remove(refNode* item) {
            if (length == 1) {
                head = tail = 0;
            }
            else if (item == head) {
                head = head->next;
            }
            else {
                refNode* temp = head;
                while (temp->next != item) {
                    temp = temp->next;
                }
                if (item == tail) {
                    tail = temp;
                    tail->next = 0;
                }
                else
                    temp->next = temp->next->next;
            }
            item->next = 0;
            length--;
        }
        void addIndex(refNode* item) {
            if (length == 0) {
                head = item;
                tail = item;
            }
            else if (item->count == 0) {
                tail->next = item;
                tail = item;
            }
            else if (item->count == 1) {
                item->next = head;
                head = item;
            }
            else {
                refNode* temp = head;
                while (temp->next != 0 && temp->next->count != 0 && temp->next->count < item->count) {
                    //cout << "run" << endl;
                    temp = temp->next;
                }
                if (temp == tail) {
                    tail->next = item;
                    tail = item;
                }
                else {
                    item->next = temp->next;
                    temp->next = item;
                }
            }
            length++;
        }
        void minus(CharAlNode* item) {
            refNode* temp = refList.search(item);
            temp->count--;
            this->remove(temp);
            this->addIndex(temp);
        }
        refNode* search(CharAlNode* item) {
            for (refNode* temp = head; temp != 0; temp = temp->next) {
                if (temp->refItem == item) {
                    return temp;
                }
            }
        }
        void check() {
            if (head->count == 0) {
                refNode* temp = head;
                while (temp != 0) {
                    refNode* tmp = temp;
                    temp = temp->next;
                    delete tmp;
                }
                head = tail = 0;
                length = 0;
            }
        }

        ~ReferencesList() {
            while (head != 0) {
                refNode* temp = head;
                head = head->next;
                delete temp;
            }
            head = tail = 0;
            length = 0;
        }
    };

    class DeleteStringList {
        // TODO: may provide some attributes
    public:
        delNode* head;
        delNode* tail;
        int length;
    public:
        DeleteStringList() {
            head = tail = 0;
            length = 0;
        }
        void add(delNode* item) {
            //cout << length << endl;
            if (length == 0) {
                head = tail = item;
                tail->next = 0;
            }
            else {
                tail->next = item;
                tail = item;
                tail->next = 0;

            }
            length++;
        }
        int size() const {

            return length;
        }
        std::string totalRefCountsString() const {
            string h = "TotalRefCounts[";
            delNode* temp = head;
            //cout << temp << endl;
            while (temp != 0) {
                if (temp != head) {
                    h += ",";
                }
                //cout << temp->countRef() << endl;
                h += to_string(temp->countRef());

                temp = temp->next;
            }
            h += "]";
            return h;
        }
        void check() {
            delNode* temp = head;
            while (temp != 0) {
                if (temp->countRef() == 0) {
                    //cout << "check" << endl;
                    if (!temp->check_concat) {
                        //cout<<"check_concat"<<" " << temp->refHead << " " << temp->refTail << endl;
                        CharAlNode* key_h = temp->refHead->refItem;
                        CharAlNode* key_t = temp->refTail->refItem;
                        CharAlNode* curent = key_h;
                        while (curent != key_t) {
                            CharAlNode* alt = curent;
                            curent = curent->next;
                            delete alt;
                        }
                    }
                    delNode* alt = temp;
                    temp = temp->next;
                    delStrList.del(alt);
                }
                else {
                    temp = temp->next;
                }
            }
            //cout << "checked" << endl;
        }
        void del(delNode* item) {
            if (length == 1) {
                delete head;
                head = tail = 0;
            }
            else {
                if (item == head) {
                    delNode* temp = head;
                    head = head->next;
                    delete temp;
                }
                else if (item == tail) {
                    delNode* temp = head;
                    while (temp->next != item) {
                        temp = temp->next;
                    }
                    delNode* key = temp->next;
                    delete key;
                    temp->next = 0;
                    tail = temp;
                }
                else {
                    delNode* temp = head;
                    while (temp->next != item) {
                        temp = temp->next;
                    }
                    delNode* key = temp->next;
                    temp->next = temp->next->next;
                    delete key;
                }
            }
            length--;
        }
    };
};

#endif // __CONCAT_STRING_LIST_H__