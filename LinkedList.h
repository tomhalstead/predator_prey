/************************* LinkedList.h ****************************************

Assignment: Linked List Class, Assignments 13-1,13-2,13-5
Author: Thomas Halstead

Purpose: Linked list and node class implementations.
         13-1:  Reverse(): Reverses the order of the nodes in the list
         13-2:  Merge() and InsertMerge(): Merges two pre-sorted lists into one
                                           sorted list. 
         13-5:  Iteration implementation:  Node<T>* iterator
                                           First(), Last(), Prev(), Next(),++,--
                                           Item(), Remove(), Delete()
                                           InsertBefore(T value)
                                           InsertAfter(T value)
                                           Insert(T value)
*******************************************************************************/
#ifndef LL_LIST_H
#define LL_LIST_H
#include <iostream>

/* Forward declarations */
template<class T>
class List;

template<class T>
class Node;

template<class T>
std::ostream& operator << (std::ostream& out, const Node<T>& Right);

template <class T>
std::istream& operator >> (std::istream& in, Node<T>& Right);

template<class T>
std::ostream& operator << (std::ostream& out, const List<T>& Right);

template <class T>
std::istream& operator >> (std::istream& in, List<T>& Right);

template <class T>
List<T> Merge(const List<T>& Left, const List<T>& Right);

template <class T>
class Node {
      public:
           friend class List<T>;
           Node<T>(){Next=NULL;}
           Node<T>(T value);
           Node<T>(const Node<T>& copyThis);
           ~Node<T>();
           Node& operator =(const Node<T>& copyThis);
           friend std::ostream& operator << <>(std::ostream &, const Node<T> &Right);
           friend std::istream& operator >> <>(std::istream& in, Node<T>& Right);

           T Item;
           Node<T>* Next;
};

template<class T>
class List {
      public:
             List<T>();
             List<T>(T value);
             List<T>(Node<T> value);
             List<T>(const List<T>& copyThis);
             ~List<T>();
             List& operator =(const List<T>& copyThis);
             void InsertHead(T value);
             void InsertHead(Node<T> value);             
                  /* Insert a value at the head of list */

             void InsertEnd(T value);
             void InsertEnd(Node<T> value);
                  /* Insert a value at the tail of list */

             void InsertBefore(T value);
             void InsertBefore(Node<T> value);
                  /* Insert a value before iterator */

             void InsertAfter(T value);
             void InsertAfter(Node<T> value);
                  /* Insert a value after iterator */
             
             void InsertSorted(T value);
             void InsertSorted(Node<T> value);
                  /* Inserts a value before the first location it's less than */

             void InsertMerge(const List<T>& list);
                  /* Merges [list] into the list. Both lists must already be
                     sorted, but the [sorted] state does not need to be set */ 
             void AppendList(const List<T>& list);
                  /* Appends [list] to the end of the list. */
             Node<T>* RemoveHead();
                  /* Removes the head node from the list; returns its address.
                     Calling function is responsible for deleting the node. */
             Node<T>* RemoveEnd();
                  /* Removes the tail node from the list; returns its address.
                     Calling function is responsible for deleting the node. */
             Node<T>* Remove();
                  /* Removes node at [iterator] from the list, returns address.
                     Calling function is responsible for deleting the node. */
             bool DeleteHead();
                  /* Removes the head node from the list and deletes it */
             bool DeleteEnd();
                  /* Removes the tail node from the list and deletes it */
             bool Delete();
                  /* Removes node at iterator from the list and deletes it */
             bool isEmpty() const{return head==NULL;}
                  /* Returns true if list is empty */
             
             //bool Sorted() const{ return sorted; }
                  /* Returns whether list's sorted state is set */
             //void Sorted(bool value);
                  /* Sets the list's sorted state to [value]. Sorts if true */
             
             bool Ascending() { return ascend; }
                  /* True if the list is set to sort ascending */
             void Ascending(bool value);
                  /* Change the Ascending state */
             unsigned int Count() const;
                  /* Returns number of Items in list */
             unsigned int Search(T value);
                  /* Searches for [value] in list. Sets [iterator] to address
                  if found or to NULL if not found. Calling function responsible
                  for resetting the iterator */
             void Sort(); /* Performs a merge sort */
             void Reverse(); /* Reverses the list */
             T* Item() const;
                  /* Returns copy of Item at [iterator]. Calling function
                     responsible for deleting copy */
             void Prev();
                  /* Moves [iterator] to the previous Item in the list.
                     [iterator] = NULL after head */
             void Next();
                  /* Moves [iterator] to the next Item in the list.
                     [iterator] = NULL after tail */
             void First() {iterator = head; }
             void Last() {iterator = tail; }
             void operator ++(int) { Next(); } /* Increments iterator */
             void operator ++() { Next(); }
             void operator --(int) { Prev(); } /* Decrements iterator */
             void operator --() { Prev(); }
             friend std::ostream& operator << <>(std::ostream &, const List<T> &Right);
             friend std::istream& operator >> <>(std::istream& in, List<T>& Right);             
             friend List<T> Merge <>(const List<T>& Left, const List<T>& Right);
                 /* Merges [Left] and [Right], returns the result.  Both lists
                    must be sorted, but the sorted state need not be set */
      private:
             void InsertBefore(Node<T> value, Node<T>* location);
             void InsertAfter(Node<T> value, Node<T>* location);
             void InsertBefore(T value, Node<T>* location);
             void InsertAfter(T value, Node<T>* location);
             Node<T>* Remove(Node<T>* location);
             bool Delete(Node<T>* location);
             Node<T>* Prev(Node<T>* location);
                  /* Returns address of the node before location,
                     NULL if none exists */
             void copy(const List<T>& copyThis);
                  /* Sets the list to a copy of [copyThis] */
             bool inList(Node<T>* location);
                  /* Returns true if address is in list */             
             bool ascend;
                  /* True causes to sort ascending, false causes descending */
             
             //bool sorted;
                  /* Sorted state. If true, forces all Insert functions to use
                     the InsertSorted() function instead. */
             Node<T>* head; /* Address of first node in list, NULL when empty */
             Node<T>* tail; /* Address of last node in list */
             Node<T>* iterator; /* First value is head, NULL at end of list */
};
/*************************Node<T> Implementation*******************************/
template <class T>
Node<T>::Node(T value) {
     Item = value;
     Next = NULL;
}

template <class T>
Node<T>::Node(const Node<T>& copyThis) {
     Item = copyThis.Item;
     Next = NULL;
}

template <class T>
Node<T>::~Node() {
     if(Next != NULL)
          delete Next;
}

template <class T>
Node<T>& Node<T>::operator =(const Node<T>& copyThis) {
      if(this != &copyThis) {
           Item = copyThis.Item;
           Next = NULL;
      }
      return *this;
}

template <class T>
std::ostream& operator << (std::ostream& out, const Node<T>& Right) {
      out << Right.Item;
      return out;
}

template <class T>
std::istream& operator >> (std::istream& in, Node<T>& Right) {
      in >> Right.Item;
      return in;
}

/***********************List<T> Implementation*********************************/
template <class T>
List<T>::List() {
     head = NULL;
     tail = NULL;
     iterator = NULL;
//     sorted = false;
     ascend = true;
}
template <class T>
List<T>::List(T value) {
     iterator = head = NULL;
//     sorted = false;
     ascend = true;
     InsertHead(value);
}

template <class T>
List<T>::List<T>(Node<T> value) {
     iterator = head = NULL;
//     sorted = false;
     ascend = true;
     InsertHead(value);
}

template <class T>
List<T>::List(const List<T>& copyThis){
     iterator = NULL;
     copy(copyThis);
}
template <class T>
List<T>::~List(){
     if(!isEmpty())
          delete head;
}

template <class T>
T* List<T>::Item() const {
     T* temp;
     if(iterator != NULL)
          temp = &(iterator->Item);
     else
          temp = NULL;
     return temp;
}

template <class T>
void List<T>::Prev() {
     iterator = Prev(iterator); /* Prev returns NULL if passed [head] */
}

template <class T>
void List<T>::Next() {
    if(iterator != NULL)
        iterator = iterator->Next;
}
             
template <class T>
void List<T>::InsertHead(T value) {
/*******************************************************************************
Name: InsertHead()
Purpose: Inserts a value at the head of the list.
Arguments:       T value             The value to insert
Return Value:    void
*******************************************************************************/
//    if(sorted)
//        InsertSorted(value);
//    else {
        Node<T> *temp = new Node<T>;
        temp->Item = value;
        temp->Next = head;        
        if(isEmpty())
             tail = temp;
        head = temp;
//    }
}
template <class T>
void List<T>::InsertHead(Node<T> value) {
    InsertHead(value.Item);
}

template <class T>
void List<T>::InsertEnd(T value) {
/*******************************************************************************
Name: InsertEnd()
Purpose: Inserts a value at the end of the list.
Arguments:       T value            The value to insert
Return Value:    void
*******************************************************************************/
//    if(sorted)
//         InsertSorted(value);
    if(isEmpty())
         InsertHead(value);
    else
         InsertAfter(value,tail);
}
template <class T>
void List<T>::InsertEnd(Node<T> value) {
    InsertEnd(value.Item);
}

template <class T>
void List<T>::InsertBefore(T value, Node<T>* location) {
/*******************************************************************************
Name: InsertBefore()
Purpose: Inserts a value in front of the specified Item
Arguments:       T value             The value to insert
                 Node<T>* location   The node to insert in front of
Return Value:    void
*******************************************************************************/
//     if(sorted)
//          InsertSorted(value);
     if(isEmpty() || location==head)
          InsertHead(value);
     else {
          Node<T>* prev = Prev(location);
          Node<T>* temp = new Node<T>;
          temp->Next = prev->Next;
          prev->Next = temp;
          temp->Item = value;
     }
}
template <class T>
void List<T>::InsertBefore(Node<T> value, Node<T>* location) {
    InsertBefore(value.Item,location);
}

template <class T>
void List<T>::InsertBefore(T value) {
/*******************************************************************************
Name: InsertBefore()
Purpose: Inserts a value in front of the specified index
Arguments:       T value             The value to insert
Return Value:    void
*******************************************************************************/
//     if(sorted)
//         InsertSorted(value);
//     else {
         if(iterator != NULL)
              InsertBefore(value,iterator);
         else
              InsertHead(value);
//     }
}
template <class T>
void List<T>::InsertBefore(Node<T> value) {
     InsertBefore(value.Item);
}

template <class T>
void List<T>::InsertAfter(T value, Node<T>* location) {
/*******************************************************************************
Name: InsertAfter()
Purpose: Inserts a value behind the specified Item
Arguments:       T value             The value to insert
                 Node<T>* location   The node to insert after
Return Value:    void
*******************************************************************************/
//     if(sorted)
//         InsertSorted(value);
//     else {
         Node<T>* temp;
         temp = new Node<T>;
         temp->Item = value;
         temp->Next = location->Next;
         location->Next = temp;
         if(location==tail)
              tail = temp;
//     }
}
template <class T>
void List<T>::InsertAfter(Node<T> value, Node<T>* location) {
     InsertAfter(value,location);
}

template <class T>
void List<T>::InsertAfter(T value) {
/*******************************************************************************
Name: InsertAfter()
Purpose: Inserts a value behind the iterator
Arguments:       T value             The value to insert
Return Value:    void
*******************************************************************************/
//     if(sorted)
//         InsertSorted(value);
//     else {
         if(iterator != NULL)
             InsertAfter(value,iterator);
         else
             InsertEnd(value);
//     }
}
template <class T>
void List<T>::InsertAfter(Node<T> value) {
     InsertAfter(value.Item);
}

template <class T>
void List<T>::InsertSorted(T value) {
/*******************************************************************************
Name: InsertSorted()
Purpose: Inserts a value before the first Item which it is less than, if
         ascending, or the first Item which it is greather than if descending.
Arguments:       T value            The value to insert
Return Value:    void
*******************************************************************************/
     Node<T>* temp = new Node<T>(value);
     if(isEmpty()) {
          temp->Next = NULL;
          head = temp;
          tail = temp;
     } else {
          if((ascend && (value < head->Item)) ||
            (!ascend && (value > head->Item))) 
          {
               temp->Next = head;
               head = temp;
          } else {
               Node<T>* walker = head;
               while(walker->Next != NULL) {
                    if(ascend && (value < walker->Next->Item))
                        break;
                    else if(!ascend && (value > walker->Next->Item))
                        break;
                    else
                        walker = walker->Next;
               }
               temp->Next = walker->Next;
               walker->Next = temp;
               if(walker == tail)
                   tail = temp;
          }
     }
}
template <class T>
void List<T>::InsertSorted(Node<T> value) {
     InsertSorted(value.Item);
}

template <class T>
void List<T>::InsertMerge(const List<T>& list) {
/*******************************************************************************
Name: InsertMerge()
Purpose: Merges another list into the list. Both must first be sorted in the
         same direction; respects Ascending state;
Arguments:      const List<T>& list         The list to insert
Return Value:   void
*******************************************************************************/
     if(this == &list)
          return;
     Node<T>* lWalker = head;
     Node<T>* rWalker = list.head;
     while(rWalker != NULL) {
          if(lWalker == NULL) {
               InsertEnd(rWalker->Item);
               rWalker = rWalker->Next;
          }
          else {
               if(
                 (ascend && (rWalker->Item < lWalker->Item)) ||
                 (!ascend && (rWalker->Item > lWalker->Item))
               ){
                    InsertBefore(rWalker->Item,lWalker);
                    rWalker = rWalker->Next;
               } else {
                    lWalker = lWalker->Next;
               }
          }
     }
}

template <class T>
void AppendList(const List<T>& list) {
/*******************************************************************************
Name: AppendList()
Purpose: Appends another list to the end of the list.
Arguments:       const List<T>& list     The list to append
Return Value:    void
*******************************************************************************/
     Node<T>* walker = list.head;
     while(walker != NULL) {
          InsertEnd(walker->value);
          walker = walker->next;
     }
}

template <class T>
Node<T>* List<T>::RemoveHead() {
/*******************************************************************************
Name: RemoveHead()
Purpose: Removes the head node and returns its address.  Calling function is
         responsible for deleting the returned node.
Arguments:           none
Return Value:        Node<T>*         The address of the removed node, NULL if
                                      none exists.
*******************************************************************************/
     if(head == NULL)
          return NULL;
     if(head==tail)
          tail = NULL;
     if(head==iterator)
          Next();
     Node<T>* temp = head;
     head = temp->Next;
     temp->Next = NULL;
     return temp;
}

template <class T>
Node<T>* List<T>::RemoveEnd() {
/*******************************************************************************
Name: RemoveEnd()
Purpose: Removes the tail node and returns its address.  Calling function is
         responsible for deleting the returned node.
Arguments:           none
Return Value:        Node<T>*         The address of the removed node, NULL if
                                      none exists.
*******************************************************************************/
     if(tail == head)
          return RemoveHead();
     if(tail==iterator)
          iterator = NULL;
     Node<T>* end = tail;
     Node<T>* prev = Prev(tail);
     prev->Next = NULL;
     tail = prev;
     return end;
}

template <class T>
Node<T>* List<T>::Remove(Node<T>* location) {
/*******************************************************************************
Name: Remove()
Purpose: Removes the node and returns its address.  Calling function is
         responsible for deleting the returned node.
Arguments:           Node<T>* location   The address of the node to remove
Return Value:        Node<T>*            The address of the removed node, NULL
                                         if none exists.
*******************************************************************************/
     if(location == head)
          return RemoveHead();
     else if(location == tail)
          return RemoveEnd();
     Node<T>* prev = Prev(location);
     if(prev != NULL) {
          prev->Next = location->Next;
          location->Next = NULL;
          return location;
     }
     return NULL;
}

template <class T>
Node<T>* List<T>::Remove() {
/*******************************************************************************
Name: Remove()
Purpose: Removes the node located at [iterator]
Arguments:       none
Return Value:    Node<T>*         The address of the removed node. NULL if no
                                  node removed.
*******************************************************************************/
     if(iterator==head)
          return RemoveHead();
     if(iterator==tail)
          return RemoveEnd();
     Node<T>* next = iterator->Next;
     Node<T>* temp = Remove(iterator);
     iterator = next;
     return temp;
}

template <class T>
bool List<T>::DeleteHead() {
/*******************************************************************************
Name: DeleteHead()
Purpose: Removes the head node from the list and deletes it.
Arguments:       none
Return Value:    bool          Returns true if a node was deleted.
*******************************************************************************/
     Node<T>* temp = RemoveHead();
     if(temp != NULL) {
          delete temp;
          return true;
     }
     return false;
}

template <class T>
bool List<T>::DeleteEnd() {
/*******************************************************************************
Name: DeleteEnd()
Purpose: Removes the tail node from the list and deletes it.
Arguments:       none
Return Value:    bool          Returns true if a node was deleted.
*******************************************************************************/
     Node<T>* temp = RemoveEnd();
     if(temp != NULL) {
          delete temp;
          return true;
     }
     return false;
}

template <class T>
bool List<T>::Delete(Node<T>* location) {
/*******************************************************************************
Name: Delete()
Purpose: Removes the node from the list and deletes it.
Arguments:       Node<T>* location    The address of the node to delete.
Return Value:    bool                 Returns true if a node was deleted.
*******************************************************************************/
     Node<T>* temp = Remove(location);
     if(temp != NULL) {
          delete temp;
          return true;
     }
     return false;
}
template <class T>
bool List<T>::Delete() {
     return Delete(iterator);
}

template <class T>
List<T>& List<T>::operator =(const List<T>& copyThis) {
      if(this != &copyThis) {
           delete head;
           copy(copyThis);
      }
      return *this;
}


/* Disabled
template <class T>
void List<T>::Sorted(bool value) {
     if(value && !sorted)
          Sort();
     sorted = value;
} */

template <class T>
void List<T>::Ascending(bool value) {
//     if(sorted && (ascend ^ value))
//          Reverse(); 
     ascend = value;
}

template <class T>
unsigned int List<T>::Count() const{
/*******************************************************************************
Name: Count()
Purpose: Returns the number of nodes in the list.
Arguments:       none
Return Value:    unsigned int        The number of nodes
*******************************************************************************/
    unsigned int numItems = 0;
    for(Node<T>* walker = head; walker != NULL; walker = walker->Next)
         numItems++;
    return numItems;
}

template <class T>
std::ostream& operator << (std::ostream& out, const List<T>& Right) {
    Node<T>* walker = Right.head;
    if(!Right.isEmpty()) {
         out << "[" << *walker << "]";
         walker = walker->Next;
    }
    while(walker!= NULL)
    {
        out << "->[" << *walker << "]";
        walker = walker->Next;
    }
    out << "->|||";
    return out;
}

template <class T>
std::istream& operator >> (std::istream& in, List<T>& Right) {
    T value;
    in >> value;
    Right.InsertHead(value);
    return in;
}

template <class T>
unsigned int List<T>::Search(T value) {
/*******************************************************************************
Name: Search()
Purpose: Searches for [value] in the list, moves iterator to the Node if found,
         NULL if not.
Arguments:        T value        The value to search for.
Return Value:     unsigned int   Returns number of steps taken to find [value].
                                 If not found, this value will be Count()
*******************************************************************************/
     unsigned int index = 0;
     if(head!=NULL) {
         First();
         while(iterator != NULL) {
              if(iterator->Item == value)
                   return index;
              Next();
              index++;
         }
     }
     return Count();
}

template <class T>
void List<T>::Sort() {
/*******************************************************************************
Name: Sort()
Purpose: Sorts the list using a merge sort
Arguments:     none
Return Value:  void
*******************************************************************************/
     unsigned int numItems = Count();
     if(numItems > 1) { /* If the list conatins only 1 Item, it is sorted */
          /* Divide the list into halves */
          unsigned int half = numItems / 2;
          List<T> left, right;
          left.ascend = ascend;
          right.ascend = ascend;
          Node<T>* value;
          for(unsigned int i = 0; i < half; i++) {
               value = RemoveHead();
               left.InsertHead(value->Item);
               delete value;
          }
          while(head != NULL) {
               value = RemoveHead();
               right.InsertHead(value->Item);
               delete value;
          }
          /* Sort each half */
          left.Sort();
          right.Sort();
          /* Merge the sorted lists and copy the result */
          *this = Merge(left,right);
     }
}
template <class T>
List<T> Merge(const List<T>& Left, const List<T>& Right) {
       List<T> result = Left;
       result.InsertMerge(Right);
       return result;
}

template <class T>
void List<T>::Reverse() {
/*******************************************************************************
Name: Reverse()
Purpose: Reverses the list.
Arguments:      none
Return Value:   void
*******************************************************************************/
    if(isEmpty())
         return;
//    if(sorted)
//         ascend = !ascend;
         
    Node<T>* next;
    Node<T>* prev;
    Node<T>* temp;
    /* Walk through each node of the list and set it's link to previous node */
    tail = prev = head;
    next = head->Next;
    head->Next = NULL;
    while(next != NULL) {
        temp = next->Next;
        next->Next = prev;
        prev = next;
        next = temp;
    }
    head = prev;
}

template <class T>
Node<T>* List<T>::Prev(Node<T>* location) {
/*******************************************************************************
Name: Prev()
Purpose: Returns the address of the previous node
Arguments:       Node<T>* location     The node to locate the previous for
Return Value:    Node<T>*              The address of the previous node, NULL if
                                       none exists or location invalid.
*******************************************************************************/
    if(location == head || isEmpty())
        return NULL;
    Node<T>* walker = head;
    bool found = false;
    while(walker != NULL && !found) {
        if(walker->Next == location)
            found = true;
        else
            walker = walker->Next;
    }
    return walker;
}

template <class T>
void List<T>::copy(const List<T>& copyThis) {
/*******************************************************************************
Name: copy()
Purpose: Sets the list to a copy of [copyThis].  Calling function is responsible
         for deleting the contents of the current list, first.
Arguments:        const List<T>& copyThis         This list to copy
Return Value:     void
*******************************************************************************/
     Node<T>* copyWalker = copyThis.head;
     Node<T>* walker = head = NULL;
     Node<T>* temp;
     while(copyWalker != NULL) {
          temp = new Node<T>;
          temp->Item = copyWalker->Item;
          temp->Next = NULL;
          if(head==NULL)
               head = temp;
          else
               walker->Next = temp;
          walker = temp;
          tail = temp;
          copyWalker = copyWalker->Next;
     }
//     sorted = copyThis.sorted;
     ascend = copyThis.ascend;
}

template <class T>
bool List<T>::inList(Node<T>* location) {
/*******************************************************************************
Name: inList()
Purpose: Determines if the address is a node in the list
Arguments:          Node<T>* location        The address to check
Return Value:       bool                     True if location is a node in list
*******************************************************************************/
     Node<T>* walker = head;
     while(walker != NULL && walker != location) {
          walker = walker->Next;
          if(walker==location)
               return true;
     }
     return false;
}

#endif
