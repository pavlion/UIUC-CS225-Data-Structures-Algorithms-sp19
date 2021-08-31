/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
	length_ = 0;//change
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  //return List<T>::ListIterator(NULL);
  return List<T>::ListIterator(head_);//change
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  //return List<T>::ListIterator(NULL);
  return List<T>::ListIterator(NULL);//change
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class. 
 */
 
 
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  while(curr!=NULL){
	ListNode *n = curr->next;
	delete curr;
	curr = n;  
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
  //cout<<"dtor is invoked!"<<endl;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode *node = new ListNode(ndata);
  node->next = NULL;
  node->prev = tail_;
  
  if(tail_ != NULL){
	tail_->next = node;
  }
  if(head_ == NULL){
	head_ = node;
  }
  
  tail_ = node;
  length_++;  
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  
  for (int i = 0; i < splitPoint; i++) {
	if(curr == NULL) return NULL;
	curr = curr->next;
  }
  if (curr != NULL && curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  //for empty list head = curr = tail = NULL
  for(int i=1; curr!=tail_ && curr!=NULL; ++i){
	
	if (i%2 == 0) { //start from 2 => curr!=head, and has prev!=NULL
	  curr->prev->next = curr->next;
	  curr->next->prev = curr->prev;
	  
	  ListNode *nextElement = curr->next;
	  curr->prev = tail_;
	  curr->next = NULL;
	  tail_->next = curr;
	  tail_ = curr;
	  
	  curr = nextElement;
	}
	else 
		curr = curr->next;
  
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
 
 
 
 
 
 
 template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == NULL || endPoint == NULL) 
	  return;
  
  ListNode * curr = startPoint;
  ListNode * back = endPoint;
  startPoint = back;
  endPoint	 = curr;
  while(curr != back && curr != NULL && back != NULL){
	  ListNode *temp1 = curr->next;
	  ListNode *temp2 = curr->prev;
	  //cout<<"curr, back data"<<curr->data<<","<<back->data<<endl;
	  
	  if(curr->next != NULL && curr->next == back){
		temp1 = back->next;
		temp2 = curr->prev;
		if(curr->prev != NULL) 
			curr->prev->next = back;
		if(back->next != NULL)
			back->next->prev = curr;
		
		back->next = curr;
		curr->prev = back;
		curr->next = temp1;	
		back->prev = temp2;
		ListNode *t = startPoint;
		 // while (t!=NULL && t->prev!=endPoint){
		//	  cout<<t->data<<",";
		//	  t = t->next;
		 // }
		  //cout<<endl<<endl;
		break;
	  }	  
	  else{
		  temp1 = curr->next;
		  temp2 = curr->prev;
		  if(curr->prev != NULL) 
			curr->prev->next = back;
		  if(curr->next != NULL )
			curr->next->prev = back;
		  curr->next = back->next;
		  curr->prev = back->prev;
		  
		  if(back->prev != NULL) 
			back->prev->next = curr;
		  if(back->next != NULL)
			back->next->prev = curr;
		  back->next = temp1;
		  back->prev = temp2;			  
		  
		  temp2 = curr->prev;
		  curr = back->next;
		  back = temp2;
		  ListNode *t = startPoint;
		  //while (t!=NULL && t->prev!=endPoint){
			//  cout<<t->data<<",";
			//  t = t->next;
		  //}
		  //cout<<endl<<endl;
	    }
	  
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(head_ == NULL || n ==1 || n<=0)
	return;
  int cnt = 1;
  ListNode *curr = head_;
  ListNode *lastStart = head_;
  
  while(curr != NULL) { //cout<<cnt<<endl;
	if(cnt%n ==0 || curr->next == NULL ){
		ListNode *t = curr->next;
		if(cnt==n){
			head_ = curr;
			//cout<<"head_->data:"<<head_->data<<endl;
		}
		
		reverse(lastStart, curr);
		//cout<<"lastStart, curr data"<<lastStart->data<<","<<curr->data<<endl;
		lastStart = t;
		curr = t; 
		++cnt;
	}
	else {
		curr = curr->next;
		++cnt;
	}
	
	
	  
  }
  
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first == NULL)
	  return second;
  else if(second == NULL)
	  return first;
  
  ListNode *newHead = NULL;
  ListNode *curr = NULL;
  ListNode *n1 = first, *n2 = second;
  
  while( n1 != NULL && n2 != NULL){
	  if(n1->data < n2->data){
		ListNode *n1Next = n1->next;
		if (newHead==NULL){
			newHead = n1;
			n1->prev = NULL;
			n1->next = NULL;
			curr = n1;
		}
	    else {
			curr->next = n1;
			n1->prev = curr;
			n1->next = NULL;
			curr = n1;
		}
		n1 = n1Next;
	  }
	  else{
		ListNode *n2Next = n2->next;
		if (newHead==NULL){
			newHead = n2;
			n2->prev = NULL;
			n2->next = NULL;
			curr = n2;
		}
	    else {
			curr->next = n2;
			n2->prev = curr;
			n2->next = NULL;
			curr = n2;
		}
		n2 = n2Next;
	  }
  }
  
  if(n1 == NULL && n2 != NULL){
	curr->next = n2;
	n2->prev = curr;
  }
  else if(n2 == NULL && n1 != NULL){
	curr->next = n1;
	n1->prev = curr;
  }
 
  /*
  List<T>::ListIterator iter1, iter2;
  for(iter1 = begin(); iter1 != end(); ++iter1)
	for(iter2 = begin(); iter2 != end(); ++iter2){
      if(iter1->data < iter2->data){
		newHead = (newHead==NULL)?*iter:newHead;
		
	  }
	*/
	
  return newHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if( chainLength == 1 )
	  return start;
  
  //cout<<"chainLength="<<chainLength<<endl;
  typename List<T>::ListNode *secondHead = split(start, chainLength/2);
  ListNode *curr = start;  int cnt=0;
  while(curr != NULL){curr=curr->next;cnt++;}
  //cout<<"start length="<<cnt<<endl;
  
  
  start = mergesort(start, chainLength/2);
  secondHead = mergesort(secondHead, chainLength - chainLength/2);
  
  return merge(start, secondHead);
}
