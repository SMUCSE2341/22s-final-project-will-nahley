//
// Created by wnahl on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

template <class T>
class AVLNode {
public:
    T element;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(const T &theElement, AVLNode<T>* lt, AVLNode<T>* rt, int h = 0) :
        element(theElement), left(lt), right(rt), height(h) {}

};

class AVLTree {

};


#endif //INC_22S_FINAL_PROJ_AVLTREE_H
