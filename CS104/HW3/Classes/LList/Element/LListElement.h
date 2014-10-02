#ifndef LListElement_H_
#define LListElement_H_

using namespace std;

template <class dataType>
class LListElement
{
        public:
                LListElement();
                ~LListElement();

                void setData(dataType s);
                void setNext(LListElement<dataType> *n);
                void setPrev(LListElement<dataType> *p);

                dataType returnData() const;
                LListElement<dataType> *returnNext();
                LListElement<dataType> *returnPrev();

        private:
                dataType data;
                LListElement<dataType> *next, *prev;

};


#include "LListElement.hpp"


#endif //LListElement_H_