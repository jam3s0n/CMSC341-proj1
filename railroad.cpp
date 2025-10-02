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
    Station* temp = m_head;

    while(temp != nullptr){

        temp = temp->m_next;
        delete temp->m_previous;
    }

    m_head = nullptr;
    m_tail = nullptr;
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
        m_head = m_tail;
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
        cout<<"here";
        return false;
    }else{

        pair<int, DIRECTION> prev = {-1, NONE};
        for(pair x: route){

            if(prev.first == -1){
                //do nothing
                prev.second = x.second;
                prev.first = x.first;

                if(position(m_head, x.first) == nullptr){
                    extendAtTail(x.first, 0);
                    }
            }else{


                Station* cart = position(m_head, x.first);
                if(cart == nullptr){
                    extendAtTail(x.first, 0);
                }

                
                Station* prevCart = position(m_head, prev.first);

                if(prev.second == NORTH){
                    prevCart->m_north = cart;
                }else if(prev.second == SOUTH){
                    prevCart->m_south = cart;
                }else if(prev.second == EAST){
                    prevCart->m_east = cart;
                }else if(prev.second == WEST){
                    prevCart->m_west = cart;
                }

                prev.second = x.second;
                prev.first = x.first;

            }
            
        }

        return true;
    }
}

int Railroad::travel(list< pair<int,DIRECTION> > route){
    if(!travelPossible(route)){
        return -1;
    }else{
        int count = 0;

            for(pair x: route){
                Station* cart = position(m_head, x.first);
                
                count += cart->m_passengers;
            

            

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

        //get the station given the code
        Station* cart = position(m_head, aCode);

        Station* temp = m_head;
        while(temp != nullptr){

             if(temp->m_north == cart){
                temp->m_north = nullptr;

            }else if(temp->m_south = cart){
                temp->m_south = nullptr;

            }else if(temp->m_east = cart){
                temp->m_east = nullptr;

            }else if(temp->m_west = cart){
                temp->m_west = nullptr;
            }           



            temp = temp->m_next;
        }



        //Head case
        if(position(m_head,aCode) == m_head){
            Station* temp = m_head;

            //delete the pointers
            m_head->m_north = nullptr;
            m_head->m_south = nullptr;
            m_head->m_east = nullptr;
            m_head->m_west = nullptr;

            m_head = m_head->m_next;

            if(m_head != nullptr){
                m_head->m_previous = nullptr;
            }

            delete temp;
            temp = nullptr;
            return true;

            //Tail case
        }else if(position(m_tail, aCode) == m_tail){
            Station* temp = m_tail;

             //delete the pointers
            m_tail->m_north = nullptr;
            m_tail->m_south = nullptr;
            m_tail->m_east = nullptr;
            m_tail->m_west = nullptr;



            if(temp->m_previous != nullptr){
                temp->m_previous->m_next = nullptr;

                m_tail = temp->m_previous;
            }

            delete temp;
            temp = nullptr;
            return true;
        
            //Middle case
        }else{
            Station* temp = position(m_head, aCode);

            //delete the pointers
            temp->m_north = nullptr;
            temp->m_south = nullptr;
            temp->m_east = nullptr;
            temp->m_west = nullptr;


            if(temp != nullptr){
                temp->m_previous->m_next = temp->m_next;

                temp->m_next->m_previous = temp->m_previous;
            }
                delete temp;
                temp = nullptr;
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
    
    if(this != &rhs){

            Station* temp = rhs.m_head;

            while(temp != nullptr){
                extendAtTail(temp->m_code, temp->m_passengers);
                temp = temp->m_next;
            }
    }


    return *this;
}

Railroad::Railroad(const Railroad & rhs){
        if(this != &rhs){
            clearNetwork();

            Station* temp = rhs.m_head;

            while(temp != nullptr){
                extendAtTail(temp->m_code, temp->m_passengers);
                temp = temp->m_next;
            }
    }

}