//UMBC - CSEE - CMSC 341 - Fall 2025 - Proj1
#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;
enum DIRECTION {NORTH, SOUTH, EAST, WEST, NONE};
const int DEFNUMPASS = 10; // default number of passengers
class Grader;
class Tester;
class Railroad;
class Station{
    public:
    friend class Grader;
    friend class Tester;
    friend class Railroad;
    Station():m_code(0), m_passengers(0), 
        m_next(nullptr), m_previous(nullptr),
        m_north(nullptr), m_south(nullptr),
        m_east(nullptr), m_west(nullptr){}
    Station(int c, int p):m_code(c), m_passengers(p), 
        m_next(nullptr), m_previous(nullptr),
        m_north(nullptr),m_south(nullptr),
        m_east(nullptr), m_west(nullptr){}
    Station(int c, int p, Station* n, Station* s, Station* e, Station* w):
        m_code(c),m_passengers(p), 
        m_north(n),m_south(s),
        m_east(e),m_west(w){}
    ~Station(){}
    void setStationCode(int aValue){m_code = aValue;}
    int getStationCode(){return m_code;}
    void setNumPassengers(int p){m_passengers=p;}
    int getNumPassegers(){return m_passengers;}
    void setNext(Station * aNode){m_next=aNode;}
    Station * getNext(){return m_next;}
    void setPrevious(Station * aNode){m_previous = aNode;}
    Station * getPrevious(){return m_previous;}
    void setNorth(Station * aNode){m_north = aNode;}
    Station * getNorth(){return m_north;}
    void setSouth(Station * aNode){m_south = aNode;}
    Station * getSouth(){return m_south;}
    void setEast(Station * aNode){m_east = aNode;}
    Station * getEast(){return m_east;}
    void setWest(Station * aNode){m_west = aNode;}
    Station * getWest(){return m_west;}

    private:
    int m_code;//stores the station code number
    int m_passengers;// the number of passengers who board the train
    Station * m_next;
    Station * m_previous;
    Station * m_north;
    Station * m_south;
    Station * m_east;
    Station * m_west;
};

class Railroad{
    public:
    friend class Grader;
    friend class Tester;
    Railroad();
    Railroad(const Railroad & rhs);// copy constructor
    ~Railroad();// delete all memory
    void dump();// print the list of stations
    const Railroad & operator=(const Railroad & rhs);// overloaded assignment operator
    bool extendAtHead(int newCode, int passengers);
    bool extendAtTail(int newCode, int passengers);
    bool makeRoute(list< pair<int,DIRECTION> > route);
    int travel(list< pair<int,DIRECTION> > route);
    bool removeStation(int aCode);// this removes a node from the list
    void clearAllRoutes();// this clears all routes, resets all direction pointers
    bool setNumPassengers(int code, int passengers);
    void clearNetwork();// delete all memory and reset all member variables

    private:
    int m_numStations;// number of stations in the network
    Station * m_head;
    Station * m_tail;

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************

    bool unique(Station* head, Station* cart){
        Station* temp = head;
        while(temp != nullptr){
            if(temp->m_code == cart->m_code){
                return false;
            }

            temp = temp->m_next;
        }
        return true;
    }

        bool unique(Station* head, int m_code){
        Station* temp = head;
        while(temp != nullptr){
            if(temp->m_code == m_code){
                return false;
            }

            temp = temp->m_next;
        }
        return true;
    }

    Station* position(Station* head, int m_code){
            Station* temp = head;
        while(temp != nullptr){
            if(temp->m_code == m_code){
                return temp;
            }

            temp = temp->m_next;
        }
        return nullptr;
    }

    //determines if the route is possible
    bool possible(list< pair<int,DIRECTION> > route){

        DIRECTION d = NONE;
        Station* cart = nullptr;
        for(pair x: route){
            cart = position(m_head, x.first);
            if(x.second == NORTH && cart->m_north != nullptr){
                return false;
            }else if(x.second == SOUTH && cart->m_south != nullptr){
                return false;
            }else if(x.second == EAST && cart->m_east != nullptr){
                return false;
            }else if(x.second == WEST && cart->m_west != nullptr){
                return false;
            }
        }

        return true;
    }


};