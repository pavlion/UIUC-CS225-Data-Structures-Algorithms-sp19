#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using std::list;
using std::cout;
using std::endl;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //int outDegree = adjList.at(v.key()).size();
  int inDegree = 0;
  for (const E_byRef & e : edgeList){
    if (e.get().source() == v || e.get().dest() == v)
      ++inDegree;
  }
  //return inDegree + outDegree;
  return inDegree;
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  //vertexMap[key] = v;
  vertexMap.insert({key, v});
  adjList.insert({key, list<edgeListIter>()});

  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  // 1.remove from the hash table
  vertexMap.erase(key);

  // 2.remove incident edges
  list<E_byRef> incidentEdgeList = incidentEdges(key);
  for (E_byRef ebr: incidentEdgeList) {
    removeEdge(ebr.get().source(), ebr.get().dest());
  }
  adjList.erase(key);
  /*
  std::list<edgeListIter>& incidentList = adjList[key];
  for (const auto it: incidentList){
    Edge& e = *it;
    edgeList.erase(it);

    string k = (e.source().key()== key)?e.dest().key():e.source().key();;
    std::list<edgeListIter>& list2 = adjList[k]; // list of the vertex of the other side
    for (const auto it2: list2){
      if (*it2 == e) {
        list2.erase(it2);
        break;
      }
    }
  }*/
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  adjList[v1.key()].push_front(edgeList.begin());
  if (!e.directed()) 
    adjList[v2.key()].push_front(edgeList.begin());

  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  //Edge e( (V(key1)), (V(key2)));
  bool isDirected = false;
  for (edgeListIter it = edgeList.begin(); it != edgeList.end(); it++){
    E& e = it->get();
    isDirected = e.directed();
    if (e.source().key() == key1 && e.dest().key() == key2){
      edgeList.erase(it);cout<<"founded in edgeList:"<<e<<endl;
      break;
    }
  }
  
  edgeListIter edgeIter;
  
  list<edgeListIter>& list1 = adjList.at(key1);
  for (typename list<edgeListIter>::iterator it = list1.begin(); it != list1.end(); it++) {
			E& e = (*it)->get();
			if ( e.dest().key() == key2 ) {
        edgeIter = *it;
				list1.erase(it);cout<<"founded in adjList.at(key1):"<<e<<endl;
				break;
			}
	}
  
  if (isDirected == false){
    // remove both side of edges in the AdjList of the source and dest vertex.
    list<edgeListIter>& list2 = adjList.at(key2);
    for (typename list<edgeListIter>::iterator it = list2.begin(); it != list2.end(); it++) {
        E& e = (*it)->get();
        if ( e.dest().key() == key1 && *it == edgeIter) {
          list2.erase(it);cout<<"founded in adjList.at(key2):"<<e<<endl;
          break;
        }
    }
  }
  
  

}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  //
  //const std::list<edgeListIter>& l = adjList.at(key);
  //for (const edgeListIter& edgeIt: l){
  //  edges.push_back(*edgeIt);
  //}
  
  for (const E_byRef & e : edgeList){
    if (e.get().source().key() == key || e.get().dest().key() == key)
      edges.push_back(e.get());
  }
  
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  // walk thru the one that has lower degree
  //std::string baseKey, targetKey;
  //if ( degree(key1)<degree(key2) ){ 
  //  baseKey = key1; 
  //  targetKey = key2;
  //}
  //else{
  //  baseKey = key2; 
  //  targetKey = key1;
  //}
  
  for (const edgeListIter& eIter: adjList.at(key1)){
		E& e = (*eIter).get();
		if (e.dest().key() == key2)
		 	return true;
	}
  
	return false;
  /*
  modified since we should take direced graph into consideration.
  We can't just based on which degree is lower.
  */
}
