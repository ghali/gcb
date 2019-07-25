/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#ifndef NODE_H
#define NODE_H

#include <algorithm>

template<typename T>
class Node
{
    T i;
    Node *negative_child;
    Node *positive_child;

public:
    Node(const T& i = T()) : i(i),
                             negative_child(NULL),
                             positive_child(NULL) {}
    Node(const Node<T>& mynode)
    {
        i = mynode.i;
        negative_child = (mynode.negative_child != NULL) ?
            new Node<T>( *(mynode.negative_child) ) : NULL;
        positive_child = (mynode.positive_child != NULL) ?
            new Node<T>( *(mynode.positive_child) ) : NULL;
    }
    virtual ~Node()
    {
        if(negative_child)
        { delete negative_child; negative_child=NULL; }
        if(positive_child)
        { delete positive_child; positive_child=NULL; }
    }

    Node<T>& operator=(const Node<T>& rs)
    {
        if(this == *rs)
            return *this;
        else {
            i = rs.i;
            negative_child = rs.negative_child;
            positive_child = rs.positive_child;
            return *this;
        }
    }

    bool operator==(const Node<T>& N) const
    {
        bool root_equality = (i == N.i);

        if(!root_equality) return false;

        bool neg_eq = false;

        if(negative_child != NULL)
            if(N.negative_child == NULL)
                return false;
            else
                neg_eq = (*negative_child == *N.negative_child);
        else
            if(N.negative_child != NULL)
                return false;
            else
                neg_eq = true;

        if(!neg_eq) return false;

        bool pos_eq = false;

        if(positive_child != NULL)
            if(N.positive_child == NULL)
                return false;
            else
                pos_eq = (*positive_child == *N.positive_child);
        else
            if(N.positive_child != NULL)
                return false;
            else
                pos_eq = true;

        return pos_eq;
    }

    Node<T>* get_negative_child() const {
        return negative_child;
    }
    Node<T>* get_positive_child() const {
        return positive_child;
    }
    void insert(const T& item)
    {
        bool difference_is_negative = (item < i);
        if( difference_is_negative )
            if( negative_child )
                negative_child->insert(item);
            else
                negative_child = new Node<T>(item);
        else
            if( positive_child )
                positive_child->insert(item);
            else
                positive_child = new Node<T>(item);
    }
    Node * find(const T& item)
    {
        if( i == item )
            return this;

        bool difference_is_negative = (item < i);
        if( difference_is_negative )
            if( negative_child )
                return negative_child->find(item);
            else
                return NULL;
        else
            if( positive_child )
                return positive_child->find(item);
            else
                return NULL;
    }
    int height() const
    {
        int negative_branch = negative_child ?
            negative_child->height() : 0;
        int positive_branch = positive_child ?
            positive_child->height() : 0;
        return 1 + std::max( negative_branch, positive_branch );
    }
    int size() const
    {
        int negative_branch = negative_child ?
            negative_child->size() : 0;
        int positive_branch = positive_child ?
            positive_child->size() : 0;
        return 1 + negative_branch + positive_branch;
    }
};

#endif // NODE_H
