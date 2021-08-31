
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <iostream>
using std::cout;
using std::endl;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
	return (_elems.size()>0)? 1 : -1 ;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    bool hasChild = true;
	if ( leftChild(currentIdx)>= _elems.size() ) hasChild = false;
	if ( rightChild(currentIdx)>= _elems.size() ) hasChild = false;

	return hasChild;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    /// as defined by higherPriority()
	size_t lc = leftChild(currentIdx);
	size_t rc = rightChild(currentIdx);

    return higherPriority( _elems[lc], _elems[rc] )? lc : rc;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
	size_t size = _elems.size();
	size_t lc = leftChild(currentIdx);
	size_t rc = rightChild(currentIdx);
	//cout<<"heapifyDown is invoked: lc="<<lc<<",rc="<<rc<<",size="<<size<<endl;
	// leaf case: stop
	if ( lc>=size && rc>=size )
		return;
	//if ( lc < size ){ //cout<<"left child = "<<_elems[lc]<<endl;
	//	minValue = _elems[lc];
	//	minChildIndex = lc;
	//}
	
	size_t minChildIndex = 0;
	
	if ( rc < size ){ // if we have right child, then we must have left child.
		//cout<<"right child = "<<_elems[rc]<<endl;
		minChildIndex = maxPriorityChild(currentIdx);
	}
	else { // we dont have right child, and it's not leaf
	// so it only has left child
		minChildIndex = lc;
	}
	//cout<<"-----------------------------------"<<endl;
	if( higherPriority( _elems[minChildIndex], _elems[currentIdx]) ) {
		std::swap(_elems[minChildIndex], _elems[currentIdx]);
		heapifyDown(minChildIndex);
	}

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
		_elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
		_elems = elems;
		_elems.insert(_elems.begin(), T());
		size_t size = _elems.size();

		for (unsigned i = parent(size-1); i > 0; --i){
			heapifyDown(i);
		}

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
		T minValue = _elems[1];
		_elems[1] = _elems[ _elems.size()-1 ];
		_elems.pop_back();

		heapifyDown(1);

		return minValue;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
		 _elems.push_back(elem);
		 heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
		if (idx >= _elems.size())
			return;
		
		T oldValue = _elems[idx];
		_elems[idx] = elem;
		
		if (oldValue > elem)
			heapifyUp(idx);
		else 
			heapifyDown(idx);
		
		//for (unsigned i = _elems.size()-1; i > 0; --i){
		//	heapifyDown(i);
		//}
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return (_elems.size() == 1) ;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const{
//{cout<<"getElems:"<<endl;
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);//cout<<_elems[i]<<" ";
    }cout<<endl;
}
