/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	//cout<<"first:"<<first<<" second:"<<second<<" curDim"<<curDim<<endl;
	if (first[curDim] != second[curDim]) return first[curDim] < second[curDim];
	else return first < second;

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	double dist1 = 0, dist2 = 0;
	for (int i=0; i < Dim; ++i){
		dist1 += (potential[i] - target[i])*(potential[i] - target[i]);
		dist2 += (currentBest[i] - target[i])*(currentBest[i] - target[i]);
	}
	//dist1 = sqrt(dist1);
	//dist2 = sqrt(dist2);

	if (dist1 != dist2)  return (dist1 < dist2);
    return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	root = NULL;
	points = newPoints;
	if (points.size() == 0) return;
	root = build(0, points.size()-1, 0);
}

template <int Dim>
void printList(vector<Point<Dim>>& points){
	cout<<"print points:";
	for(unsigned i=0;i<points.size();++i)
		cout<<points[i]<<" ";
	cout<<endl;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build(int start, int end, int dimension)
{
  KDTree<Dim>::KDTreeNode* child = NULL;
  if (start >= end) {
	if (start == end)
		child = new KDTreeNode( points[start] );  
	return child;
  }
  int middle = (start + end) / 2;
  // rearrage the data, so that the middle value is the real median
  // our goal is not to find the median, but to force the median
  // to be in the middle of the array.
  quickSelect(start, end, middle, dimension);
  child = new KDTreeNode( points[middle] );
  child->left = build(start, middle-1, (dimension + 1) % Dim);
  child->right = build(middle+1, end, (dimension + 1) % Dim);
  
  return child;
}

template <int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int k, int dimension)
{
  if (start >= end) return;
  // index is where the new pivot are in the array.
  int index = partition(start, end, (start + end) / 2, dimension);
  //if (index == k) {
	//cout<<"index == k = "<<index<<endl;
  //}
  if (index > k) quickSelect(start, index-1, k, dimension);
  else if (index < k) quickSelect(index+1, end, k, dimension);
}

template <int Dim>
int KDTree<Dim>::partition(int start, int end, int pivot, int dimension)
{
  //points[pivot].print();cout<<endl;
  Point<Dim> pivotValue = points[pivot];
  // move the pivot to the end
  swap(points[pivot], points[end]);

  int storeIndex = start;
  // move everything "smaller" than the pivotValue to the leftmost
  for (int i = start; i < end; ++i) {
    if (smallerDimVal(points[i], pivotValue, dimension)) {
      swap(points[storeIndex], points[i]);
      ++storeIndex;
    }
  }
  // place pivot to the right position
  // so everything left to the pivot is "smaller" than pivot
  // also, everything is larger is right to the pivot
  swap(points[storeIndex], points[end]);

  return storeIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) 
{
  /**
   * @todo Implement this function!
   */
   root = copy(other.root);
   points = other.points;
   size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
		points = rhs.points;
		size = rhs.size;
    }
	
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
  root = NULL; 
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
	if (root!=NULL)
		return _NNHelper(root, 0, points[(points.size()-1)/2], query);
	return Point<Dim>();
}

template <int Dim>
Point<Dim> KDTree<Dim>::_NNHelper(KDTreeNode* subRoot, int dim, const Point<Dim>& curBest, const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
	if ( subRoot == NULL) return  curBest;
	if ( subRoot->left == NULL && subRoot->right == NULL){
		if ( shouldReplace(query, curBest, subRoot->point) )
			return subRoot->point;
		else return curBest;			
	}
	
	Point<Dim> retval = curBest; // candidate for curBest
	bool goRight = true;
	// 1. check the subtree that contains the target.
	//cout<<"smallerDimVal="<<smallerDimVal(subRoot->point, query, dim)<<" subRoot->point="<<subRoot->point<<" query="<<query<<" dim="<<dim<<endl;
	if ( smallerDimVal(subRoot->point, query, dim) ){ // we should go right
		if (subRoot->right != NULL)
			retval = _NNHelper(subRoot->right, (dim+1)%Dim, curBest, query);
		goRight = true;
	}
	else {
	//if ( smallerDimVal(query, subRoot->point, dim) ){
		if (subRoot->left != NULL)
			retval = _NNHelper(subRoot->left, (dim+1)%Dim, curBest, query);
		goRight = false;	
	}
	
	// 2.check the current node.
	if (shouldReplace(query, retval, subRoot->point))
        retval = subRoot->point;
	
	// 3.check the other subtree
	Point<Dim> p = subRoot->point;
	
	double distance = 0;
	double newDist = (p[dim] - query[dim])*(p[dim] - query[dim]);
	for (int i=0; i < Dim; ++i){
		distance += (retval[i] - query[i])*(retval[i] - query[i]);
	}
	
	if ( newDist <= distance){
		if (goRight){
			if (subRoot->left != NULL)
				retval = _NNHelper(subRoot->left, (dim+1)%Dim, retval, query);
		}
		else{
			if (subRoot->right != NULL)
				retval = _NNHelper(subRoot->right, (dim+1)%Dim, retval, query);
		}
	}
		
	return retval;
}

