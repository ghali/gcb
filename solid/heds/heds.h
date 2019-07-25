/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef HEDS_H
#define HEDS_H

#include <iostream>
#include <vector>
#include <map>
#include "boost/shared_ptr.hpp"

#include "node.h"
#include "halfedge.h"
#include "face.h"

template<typename HEDS_traits>
struct HEDS;

template<typename HEDS_traits>
struct HEDS_reader;

template<typename HEDS_traits>
std::ostream&
operator<< (std::ostream& os, const HEDS<HEDS_traits>& myHEDS);

template<typename HEDS_traits>
struct HEDS
{
    friend class HEDS_reader<HEDS_traits>;

    // The terminology is as follows:
    // 
    // The names 'Node', '[Half]Edge', and 'Face' are reserved for topological objects.
    // Any other name can be used for other attributes (coordinates, normals, colors, ...)
    // 
    // For instance in the example in heds_types.h, the terms 'Vertex',
    // 'Arc', and 'Polyon' are used for non-topological objects.

    typedef typename HEDS_traits::Node_type  Attribute_node_type;
    typedef typename HEDS_traits::Edge_type  Attribute_edge_type;
    typedef typename HEDS_traits::Face_type  Attribute_face_type;

    typedef Node<HEDS_traits>      My_node;
    typedef Halfedge<HEDS_traits>  My_edge;
    typedef Face<HEDS_traits>      My_face;

    // Shared Pointers
    typedef boost::shared_ptr<My_node> My_node_ptr;
    typedef boost::shared_ptr<My_edge> My_edge_ptr;
    typedef boost::shared_ptr<My_face> My_face_ptr;
    // 
    // Replace with the following to switch to concrete pointers.
    // typedef My_node *  My_node_ptr;
    // typedef My_edge *  My_edge_ptr;
    // typedef My_face *  My_face_ptr;


    typedef std::vector< My_node_ptr >  My_node_container;
    typedef std::vector< My_edge_ptr >  My_edge_container;
    typedef std::vector< My_face_ptr >  My_face_container;

    My_node_container V;
    My_edge_container E;
    My_face_container F;


    unsigned int number_of_nodes() const { return V.size(); }
    unsigned int number_of_halfedges() const { return E.size(); }
    unsigned int number_of_faces() const { return F.size(); }

    void stitch_twins();

    void set_halfedge_succ_pred_links();
    void set_node_outgoing_edge();
    bool check_twins() const;

    // Euler operators
    void
    mvfs_mev(const Attribute_node_type & attr_node_0,
             const Attribute_node_type & attr_node_1,
             const Attribute_edge_type & attr_edge_0,
             const Attribute_edge_type & attr_edge_1, // used for twin
             const Attribute_face_type & attr_face,
             My_node_ptr node_0, // Node<HEDS_traits> * node,
             My_node_ptr node_1, // Node<HEDS_traits> * node,
             My_edge_ptr edge_0,
             My_edge_ptr edge_1, // twin
             My_face_ptr face    // Face<HEDS_traits> * face
             );

    void
    mvfs(const Attribute_node_type & attr_node,
         const Attribute_face_type & attr_face,
         My_node_ptr node, // Node<HEDS_traits> * node,
         My_face_ptr face  // Face<HEDS_traits> * face
         );

    void
    mev(My_edge_ptr adjpred,
        My_edge_ptr adjsucc,
        Node<HEDS_traits>     * vert);

    void
    mef(My_edge_ptr pred,
        My_edge_ptr succ);

    void
    kef(My_edge_ptr e);         // e->adjFace is the one deleted.

    friend
    std::ostream&
    operator<< <>(std::ostream& os, const HEDS<HEDS_traits>& myHEDS);

#if 0
    //----------------------------------------------------------------
    // A more primitive interface is also available.
    //----------------------------------------------------------------
    virtual My_node *
    insert_node(const Attribute_node_type & nt =
                Attribute_node_type())
    {
        My_node * mynode = new My_node( nt );
        V.push_back(mynode);
        return mynode;
    }

    virtual My_edge *
    insert_edge(My_node * source, My_node * target,
                const Attribute_edge_type & et =
                Attribute_edge_type() )
    {
        My_edge * newedge = new My_edge(source, target, et);

        source->sourceOf.push_back(newedge);
        target->targetOf.push_back(newedge);

        E.push_back(newedge);
        return newedge;
    }
#endif

};

#include "heds_inl.h"

#endif // HEDS_H
