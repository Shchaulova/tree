//
// Created by Светлана on 22.03.2019.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

// Реализация интерфейса

void Tree::insert(int new_value) {
    if (root != nullptr) {
        root = root->Insert(new_value);
    } else {
        root = new Element{new_value, nullptr};
    }
}

bool Tree::exists(int value) {
    return this->Find(value) != nullptr;
}

void Tree::remove(int value_to_remove) {
    root = Element::Remove(root, value_to_remove);
}

void Tree::print() {
    cout << *this->root << endl;
}

// Остальные функции

void Tree::Element::CalcDepth() {
    int ldepth = left != nullptr? left->depth : 0;
    int rdepth = right != nullptr ? right->depth : 0;
    depth = (ldepth > rdepth ? ldepth : rdepth) + 1;
}

Tree::Element *Tree::Element::LittleLeftRotate() {
    Element *right = this->right;
    this->right = right->left;
    right->left = this;
    right->head = this->head;
    this->head = right;
    CalcDepth();
    right->CalcDepth();
    return right;
}

Tree::Element *Tree::Element::LittleRightRotate() {
    Element *left = this->left;
    this->left = left->right;
    left->right = this;
    left->head = this->head;
    this->head = left;
    CalcDepth();
    left->CalcDepth();
    return left;
}

Tree::Element *Tree::Element::BigLeftRotate() {
    right = right->LittleRightRotate();
    return LittleLeftRotate();
}

Tree::Element *Tree::Element::BigRightRotate() {
    left = left->LittleLeftRotate();
    return LittleRightRotate();
}

Tree::Element *Tree::Element::Insert(Tree::TreeValueType new_value) {
    if (new_value == this->value) {
        return this;
    } else if (new_value > this->value) {
        if (right == nullptr) {
            right = new Element{new_value, this};
        } else {
            right = right->Insert(new_value);
        };
    } else {
        if (left == nullptr) {
            left = new Element{new_value, this};
        } else {
            left = left->Insert(new_value);
        }
    }

    return Balancing(this);
}

Tree::Element *Tree::Element::Balancing(Element *head) {
    int left_depth = head->left != nullptr ? head->left->depth : 0;
    int right_depth = head->right != nullptr ? head->right->depth : 0;

    int balance = right_depth - left_depth;

    if (balance == -2) {
        int ll_depth = head->left->left ? head->left->left->depth : 0;
        int lr_depth = head->left->right ? head->left->right->depth : 0;
        if (lr_depth - ll_depth > 0) {
            head = head->BigRightRotate();
        } else {
            head = head->LittleRightRotate();
        }
    } else if (balance == 2) {
        int rl_depth = head->right->left ? head->right->left->depth : 0;
        int rr_depth = head->right->right ? head->right->right->depth : 0;
        if (rr_depth - rl_depth < 0) {
            head = head->BigLeftRotate();
        } else {
            head = head->LittleLeftRotate();
        }
    } else {
        head->CalcDepth();
    }
    return head;
}

std::ostream &operator<<(std::ostream &os, const Tree::Element &element) {
    os << "(";
    if (element.left) {
        os << *element.left;
    }
    os << element.value;
    if (element.right) {
        os << *element.right;
    }
    return os << ")";
}

const Tree::Element *Tree::Element::Find(const Tree::TreeValueType &value_to_find) const {
    if (value == value_to_find) {
        return head;
    }
    if (value_to_find < value) {
        if (left == nullptr) {
            return nullptr;
        }
        return left->Find(value_to_find);
    }
    if (right == nullptr) {
        return nullptr;
    }
    return right->Find(value_to_find);
}

Tree::Element *Tree::Element::Remove(Element *head, Tree::TreeValueType value_to_remove) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->value != value_to_remove) {
        if (value_to_remove > head->value) {
            head->right = Remove(head->right, value_to_remove);
        } else {
            head->left = Remove(head->left, value_to_remove);
        }
    } else {
        if (head->left == nullptr && head->right == nullptr) {
            delete head;
            return nullptr;
        }

        Element *element_to_swap = head;
        int left_depth = element_to_swap->left != nullptr ? element_to_swap->left->depth : 0;
        int right_depth = element_to_swap->right != nullptr ? element_to_swap->right->depth : 0;

        if (left_depth > right_depth) {
            for (element_to_swap = head->left;
                 element_to_swap->right != nullptr; element_to_swap = element_to_swap->right);
        } else {
            for (element_to_swap = head->right;
                 element_to_swap->left != nullptr; element_to_swap = element_to_swap->left);
        }
        TreeValueType c = element_to_swap->value;
        element_to_swap->value = head->value;
        head->value = c;

        if (left_depth > right_depth) {
            head->left =  Remove(head->left, value_to_remove);
        } else {
            head->right =  Remove(head->right, value_to_remove);
        }
    }
    return Balancing(head);
}

void Tree::Element::Clear(Tree::Element *root) {
    if (root == nullptr) {
        return;
    }
    if (root->left) {
        Clear(root->left);
    }
    if (root->right) {
        Clear(root->right);
    }
    delete root;
}

std::ostream &operator<<(std::ostream &os, const Tree &tree) {
    return os << *tree.root;
}

const Tree::Element *Tree::Find(const Tree::TreeValueType &value_to_find) const {
    if (root != nullptr) {
        return root->Find(value_to_find);
    }
    return nullptr;
}

Tree::~Tree() {
    Element::Clear(root);
    root = nullptr;
}
