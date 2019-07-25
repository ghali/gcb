/* The following code example is described in the book "Introduction
 * to Geometric Computing" by Sherif Ghali, Springer-Verlag, 2008.
 *
 * Copyright (C) 2008 Sherif Ghali. This code may be freely copied,
 * modified, or republished electronically or in print provided that
 * this copyright notice appears in all copies. This software is
 * provided "as is" without express or implied warranty; not even for
 * merchantability or fitness for a particular purpose.
 */

#include "embed_tree_by_rank_e2.h"
// #include "embed_tree_tidier_e2.h"

#include "tree_draw/node.h"

#include <cassert>
#include <iostream>

using std::endl;
using std::cout;

typedef Node<int> Node_type;
typedef Point_E2<float> Point_E2f;
typedef std::map<const Node_type*, Point_E2f > My_map;

void test_tree()
{
    Node_type * N = new Node_type(5);
    N->insert(3);    N->insert(2);
    N->insert(4);    N->insert(1);
    N->insert(6);    N->insert(7);

    assert( N->find(99) == NULL );
    assert( N->find(5) == N );
    assert( N->find(3) == N->get_negative_child() );

    Node_type * Ncopy = new Node_type( *N );

    assert( *Ncopy == *N );

    delete Ncopy;
    delete N;
}

void test_embed_single_node()
{
    Node_type * N = new Node_type(9);
    My_map M = embed_tree_by_rank_E2<Node_type, float >(N);
    assert( Point_E2f( 0, 0 ) == M[N] );

    delete N;
}

void test_embed_tree_by_rank_e2()
{
    int numbers[] = {5,3,4,6,7};
    Node_type * N = new Node_type(numbers[0]);
    int i = 0;
    while( ++i!=5 )
        N->insert(numbers[i]);

    My_map M = embed_tree_by_rank_E2<Node_type, float >(N);

    assert( Point_E2f( 0, -2 ) == M[N->get_negative_child()] );
    assert( Point_E2f( 1, -4 ) == M[N->get_negative_child()->get_positive_child()] );
    assert( Point_E2f( 2,  0 ) == M[N] );
    assert( Point_E2f( 3, -2 ) == M[N->get_positive_child()] );
    assert( Point_E2f( 4, -4 ) == M[N->get_positive_child()->get_positive_child()] );

    delete N;
}
#if 0
void test_embed_tree_tidier_e2()
{
    {
        int numbers[] = {5,3,4,6,7};
        Node_type * N = new Node_type(numbers[0]);
        int i = 0;
        while( ++i!=5 )
            N->insert(numbers[i]);

        My_map M = embed_tree_tidier_E2<Node_type, float >(N);

        assert( Point_E2f( -1, -2 ) == M[N->get_negative_child()] );
        assert( Point_E2f(  0, -4 ) == M[N->get_negative_child()->get_positive_child()] );
        assert( Point_E2f(  0,  0 ) == M[N] );
        assert( Point_E2f(  1, -2 ) == M[N->get_positive_child()] );
        assert( Point_E2f(  2, -4 ) == M[N->get_positive_child()->get_positive_child()] );

        delete N;
    }
    {
        int numbers[] = {3,2,4,1,5};
        Node_type * N = new Node_type(numbers[0]);
        int i = 0;
        while(++i!=5)
            N->insert(numbers[i]);

        My_map M = embed_tree_tidier_E2<Node_type, float >(N);

        cout << M[N->find(3)] << endl;
        cout << M[N->find(2)] << endl;
        cout << M[N->find(4)] << endl;
        cout << M[N->find(1)] << endl;
        cout << M[N->find(5)] << endl;

        delete N;
    }
}
#endif
int main()
{
    test_tree();
    test_embed_single_node();
    test_embed_tree_by_rank_e2();
//    test_embed_tree_tidier_e2();
}
