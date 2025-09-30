//UMBC - CSEE - CMSC 341 - Fall 2025 - Proj1
#include "railroad.h"
Railroad::Railroad(){
    m_numStations = 0;
    m_head = nullptr;
    m_tail = nullptr;
}

Railroad::~Railroad(){
    Railroad::clearNetwork();
}

void Railroad::clearNetwork(){
    
}

bool Railroad::extendAtHead(int newCode, int passengers){
    Station* cart = new Station(newCode, passengers);
    if(cart == nullptr) {return false;}

    if(m_head == nullptr){
        m_head = new Station(newCode, passengers);
        if(m_head = nullptr){return false;}

        m_tail = m_head;
        return true;
    }
    
    if(unique(m_head, cart)){
        m_head->m_previous = cart;
        cart->m_next = m_head;
        m_head = cart;

        return true;
    }else{
        return false;
    }
    

}

bool Railroad::extendAtTail(int newCode, int passengers){
    Station* cart = new Station(newCode, passengers);
    if(!cart){
        return false;
    }

    if(m_tail == nullptr){
        m_tail = new Station(newCode,passengers);
    }

    if(unique(m_head, cart)){
        m_tail->m_next = cart;
        cart->m_previous = m_tail;
        m_tail = cart;
        return true;

    }else{
        return false;
    }
}

void Railroad::dump(){
    if (m_head != nullptr){
        int northCode, southCode, eastCode, westCode;
        Station *temp = m_head;
        while(temp != nullptr){
            if (temp->m_north != nullptr) northCode = temp->m_north->m_code;
            else northCode = -1;
            if (temp->m_south != nullptr) southCode = temp->m_south->m_code;
            else southCode = -1;
            if (temp->m_east != nullptr) eastCode = temp->m_east->m_code;
            else eastCode = -1;
            if (temp->m_west != nullptr) westCode = temp->m_west->m_code;
            else westCode = -1;
            cout << temp->m_code << 
                    " (" << 
                    "P: " << temp->m_passengers << 
                    ", N: " << northCode <<
                    ", S: " << southCode <<
                    ", E: " << eastCode <<
                    ", W: " << westCode <<
                    ")" << endl;
            temp = temp->m_next;
        }
    }
}

bool Railroad::makeRoute(list< pair<int,DIRECTION> > route){
    if(unique(m_head, route.front().first) || !possible(route)){
        return false;
    }else{

        pair<int, DIRECTION> prev = {NULL, NONE};
        for(pair x: route){
            Station* cart = position(m_head, x.first);

            Station* prevCart = position(m_head, prev.first);
            if(prev.second == NORTH){
                prevCart->m_north == cart;
            }else if(prev.second == SOUTH){
                prevCart->m_south == cart;
            }else if(prev.second == EAST){
                prevCart->m_east == cart;
            }else if(prev.second == WEST){
                prevCart->m_west == cart;
            }

            prev.second = x.second;
            prev.first = x.first;

            if(cart == nullptr){
                extendAtTail(x.first, 0);
            }
            
        }

        return true;
    }
}

int Railroad::travel(list< pair<int,DIRECTION> > route){
    if(!possible(route)){
        return -1;
    }else{
        int count = 0;

            for(pair x: route){
                Station* cart = position(m_head, x.first);
                
                count =+ cart->m_passengers;
            

            

        }

        return count;
    }
}

bool Railroad::setNumPassengers(int code, int passengers){
    Station* cart = position(m_head, code);
    if(cart){
        cart->m_passengers = passengers;
        return true;
    }else{
        return false;
    }
}

bool Railroad::removeStation(int aCode){
    if(unique(m_head, aCode) || position(m_head, aCode) == nullptr){
        return false;
    }else{
        //Head case
        if(position(m_head,aCode) == m_head){
            Station* temp = m_head;

            m_head = m_head->m_next;

            if(m_head != nullptr){
                m_head->m_previous = nullptr;
            }

            //should I delete north south pointers too?
            delete temp;
            return true;

            //Tail case
        }else if(position(m_tail, aCode) == m_tail){
            Station* temp = m_tail;

            if(temp->m_previous != nullptr){
                temp->m_previous->m_next = nullptr;
            }

            delete temp;
            return true;

            //Middle case
        }else{
            Station* temp = position(m_head, aCode);

            temp->m_previous->m_next = temp->m_previous;

            temp->m_next->m_previous = temp->m_previous;

            delete temp;
            return true;
        }

    }
}

void Railroad::clearAllRoutes(){

    Station* temp = m_head;
    while(temp != nullptr){
        temp->m_north = nullptr;
        temp->m_south = nullptr;
        temp->m_west = nullptr;
        temp->m_east = nullptr;

        temp = temp->m_next;
    }
}

const Railroad & Railroad::operator=(const Railroad & rhs){
    Railroad(rhs);
    return *this;
}

Railroad::Railroad(const Railroad & rhs){
        if(this != &rhs){
            clearNetwork();
            

            m_head = new Station* ;

    }

}