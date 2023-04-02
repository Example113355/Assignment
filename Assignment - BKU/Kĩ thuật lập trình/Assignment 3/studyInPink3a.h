/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x = 0, int y = 0);
    string toString() const {
        return "<Point[" + to_string(this->x) + "," + to_string(this->y) + "]>";
    }

    int distanceTo(const Point& otherPoint) const {
        double d;
        d = sqrt(pow(x - otherPoint.x, 2) + pow(y - otherPoint.y, 2));
        return ceil(d);
    }
};
Point::Point(int a, int b) {
    x = a;
    y = b;
}

class Node {
private:
    Point point;
    Node * next;

    friend class Path;

public:
    Node(const Point& point = Point(), Node* next = NULL) {
        this->point = point;
        this->next = next;
    }
    string toString() const {
        return "<Node[" + point.toString() + "]>";
    }
};


class Path {
private:
    Node * head;
    Node * tail;
    int count;
    int length;

public:
    Path() {
        head = NULL;
        tail = NULL;
        count = 0;
        length = -1;
    }
    ~Path() {
        while (head != NULL) {
            Node* temp = head->next;
            delete head;
            head = temp;
        }
        head = NULL;
        tail = NULL;
        count = 0;
        length = -1;
    }

    void addPoint(int x, int y) {
        if (count == 0) {
            Node* tmp = new Node(Point(x,y),NULL);
            head = tmp;
            tail = tmp;
            length = 0;
        }
        else {
            Node* tmp = new Node(Point(x, y),NULL);
            length += ceil(tail->point.distanceTo(tmp->point));
            tail->next = tmp;
            tail = tmp;
        }
        count++;
    }
    string toString() const {
        Node* tmp = this->head;
        string a = "<Path[count:" + to_string(count) + ",length:" + to_string(length) + ",[";
        while (tmp!=NULL) {
            a = a + tmp->toString() + ",";
            tmp = tmp->next;
        }
        if(count != 0)
            a.pop_back();
        a += "]]>";
        return a;
    }
    Point getLastPoint() const {
        Node* temp = tail;
        return temp->point;
    }
    int getLength() const{
        return length;
    }
};

class Character {
private:
    string name;
    Path * path;

public:
    Character(const string& name = "") {
        this->name = name;
        this->path = new Path();
    }
    ~Character() {
        
    }

    string getName() const {
        return this->name;
    }
    void setName(const string& name) {
        this->name = name;
    }

    void moveToPoint(int x, int y) {
        this->path->addPoint(x, y);
    }
    string toString() const {
        string a = "<Character[name:" + name + ",path:" + path->toString() + "]>";
        return a;
    }
    int getlength() const{
        return path->getLength();
    }
    Point getLastPoint() const {
        return path->getLastPoint();
    }
};

bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ) {
    int l2 = chMurderer.getlength();
    int l1 = chWatson.getlength();
    if ((l1 - l2) <= maxLength) {
        Point a = chMurderer.getLastPoint();
        Point b = chWatson.getLastPoint();
        outDistance = a.distanceTo(b);
        if (outDistance > maxDistance) {
            return false;
        }
    }
    else {
        outDistance = -1;
        return false;
    }
    return true;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */