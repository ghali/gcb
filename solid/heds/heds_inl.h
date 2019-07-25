/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef HEDS_INL_H
#define HEDS_INL_H

#include "heds.h"

template<typename HEDS_traits>
std::ostream&
operator<< (std::ostream& os, const HEDS<HEDS_traits>& H)
{
    typedef typename HEDS<HEDS_traits>::My_node_ptr  My_node_ptr;
    typedef typename HEDS<HEDS_traits>::My_edge_ptr  My_edge_ptr;
    typedef typename HEDS<HEDS_traits>::My_face_ptr  My_face_ptr;

    typedef typename HEDS<HEDS_traits>::My_node_container::const_iterator  NodeP_iterator;
    typedef typename HEDS<HEDS_traits>::My_edge_container::const_iterator  EdgeP_iterator;
    typedef typename HEDS<HEDS_traits>::My_face_container::const_iterator  FaceP_iterator;

    int n = 0; std::map<My_node_ptr,int> MN;
    int e = 0; std::map<My_edge_ptr,int> ME;
    int f = 0; std::map<My_face_ptr,int> MF;

    for(NodeP_iterator vi = H.V.begin(); vi != H.V.end(); ++vi) MN[*vi] = n++;
    for(EdgeP_iterator ei = H.E.begin(); ei != H.E.end(); ++ei) ME[*ei] = e++;
    for(FaceP_iterator fi = H.F.begin(); fi != H.F.end(); ++fi) MF[*fi] = f++;

    os << "----------------Nodes----------------" << std::endl;
    for(NodeP_iterator vi = H.V.begin(); vi!= H.V.end(); ++vi)
        os << "Node " << MN[*vi]
           << "  outgoing_edge: " << ME[(*vi)->outgoing_edge]
           << "  valence: " << (*vi)->valence()
           << "  info: " << (*vi)->info() << std::endl;

    os << "----------------Halfedges----------------" << std::endl;
    for(EdgeP_iterator ei = H.E.begin(); ei!=H.E.end(); ++ei)
        os << "Edge " << ME[*ei]
           << "  source: " << MN[(*ei)->source]
           << "  target: " << MN[(*ei)->target]
           << "  adjFace: " << MF[(*ei)->adjFace]
           << "  pred: " << ME[(*ei)->pred]
           << "  succ: " << ME[(*ei)->succ]
           << "  twin: " << ME[(*ei)->twin]
           << "  info: " << (*ei)->info() << std::endl;

    os << "----------------Faces----------------" << std::endl;
    for(FaceP_iterator fi = H.F.begin(); fi!=H.F.end(); ++fi)
        os << "Face " << MF[*fi]
           << "  edge: " << ME[(*fi)->edge]
           << "  info: " << (*fi)->info() << std::endl;

    return os << std::endl;
}


// Stitch_Twins_By_Associative_Container
template<typename HEDS_traits>
void
HEDS<HEDS_traits>::stitch_twins()
{
    // ...
}

template<typename HEDS_traits>
bool
compare(const Halfedge<HEDS_traits>* e1,
        const Halfedge<HEDS_traits>* e2)
{
    Node<HEDS_traits> *e1s,*e1l,*e2s,*e2l;
    if(e1->source < e1->target) {
        e1s = e1->source;        
        e1l = e1->target;
    }
    else{
        e1l = e1->source;        
        e1s = e1->target;
    }
    if(e2->source < e2->target) {
        e2s = e2->source;        
        e2l = e2->target;
    }
    else{
        e2l = e2->source;        
        e2s = e2->target;
    }
    if(e1s == e2s){
        return  e1l < e2l;
    }
    return e1s < e2s;
}

template<typename HEDS_traits>
bool
is_twin(Halfedge<HEDS_traits>* e1,
        Halfedge<HEDS_traits>* e2)
{
    if(e1->source == e2->target && e2->source == e1->target)
        return true;
    return false;
}

template<typename HEDS_traits>
void
HEDS<HEDS_traits>::set_halfedge_succ_pred_links()
{
    typedef typename My_node_container::iterator     NodeP_iterator;
    typedef typename My_edge_container::iterator HalfedgeP_iterator;

}

template<typename HEDS_traits>
void
HEDS<HEDS_traits>::set_node_outgoing_edge()
{
    typedef typename My_node_container::iterator     NodeP_iterator;
    typedef typename My_edge_container::iterator HalfedgeP_iterator;

    std::map<My_node_ptr, My_edge_ptr> M;
    for(HalfedgeP_iterator hei = E.begin(); hei!= E.end(); ++hei)
        if(!M[(*hei)->source])
            M[(*hei)->source] = (*hei);

    for(NodeP_iterator vi = V.begin(); vi!= V.end(); ++vi)
        (*vi)->outgoing_edge = M[(*vi)];
}

template<typename HEDS_traits>
bool
HEDS<HEDS_traits>::check_twins() const
{
    typedef typename My_edge_container::const_iterator HalfedgeP_iterator;
    for(HalfedgeP_iterator it = E.begin(); it != E.end(); ++it)
    {
        if(*it != (*it)->succ->pred)
            return false;
        if(*it != (*it)->twin->twin)
            return false;
    }
    return true;
}

template<typename HEDS_traits>
void
HEDS<HEDS_traits>::mvfs_mev(const Attribute_node_type & attr_node_0,
                            const Attribute_node_type & attr_node_1,
                            const Attribute_edge_type & attr_edge_0,
                            const Attribute_edge_type & attr_edge_1, // used for twin
                            const Attribute_face_type & attr_face,
                            My_node_ptr node_0, // Node<HEDS_traits> * node,
                            My_node_ptr node_1, // Node<HEDS_traits> * node,
                            My_edge_ptr edge_0,
                            My_edge_ptr edge_1, // twin
                            My_face_ptr face    // Face<HEDS_traits> * face
                            )
{
    // ...
}

template<typename HEDS_traits>
void
HEDS<HEDS_traits>::mev(My_edge_ptr adjpred,
                       My_edge_ptr adjsucc,
                       Node<HEDS_traits> * vert)
{
    // Makes an edge node:
    // The vertex is the new node.
    // The two halfedges are the predecessor and successor of the node
    //  that will become the new source node of the new halfedge.

    // ...
}

template<typename HEDS_traits>
void
HEDS<HEDS_traits>::mef(My_edge_ptr pred,
                       My_edge_ptr succ)
{
    // Make edge face:
    // The pred and succ halfedge pointers are the predecessor
    //  and the successor of the half edge that will be created, with
    //  new face being adjacent to that half edge.

    // ...
}

template<typename HEDS_traits>
void
HEDS<HEDS_traits>::kef(My_edge_ptr e)
{
    // ...
}        

#endif // HEDS_INL_H
