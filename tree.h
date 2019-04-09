//
// Created by Светлана on 22.03.2019.
//

#ifndef TREE_C_TREE_CPP_H
#define TREE_C_TREE_CPP_H

#include <ostream>

class Container {

public:

    // Виртуальные методы, будут реализованы далее

    virtual void insert(int value) = 0;

    virtual bool exists(int value) = 0;

    virtual void remove(int value) = 0;

    // Это потом заменим на перегруженный оператор <<

    virtual void print() = 0;

//protected:

    // Виртуальный деструктор

    virtual ~Container() = default;

};

class Tree: public Container {
public:
    using TreeValueType = int;

    struct Element {
    public:
        TreeValueType value;

    private:
        Element(TreeValueType value, Element *head)
                : value(value), head(head), depth(0), left(nullptr), right(nullptr) {}

        static void Clear(Element *head);

        void CalcDepth();

        Element *LittleLeftRotate();

        Element *LittleRightRotate();

        Element *BigLeftRotate();

        Element *BigRightRotate();

        Element *Insert(TreeValueType new_value);

        friend std::ostream &operator<<(std::ostream &os, const Element &element);

        static Element *Balancing(Element *head);

        const Element *Find(const TreeValueType &value) const;

        static Element *Remove(Element *head, TreeValueType value_to_remove);

        int depth;
        Element *head;
        Element *left;
        Element *right;

        friend Tree;
    };

    Tree() : root(nullptr) {}

    ~Tree() override;

    const Element *Find(const Tree::TreeValueType &value_to_find) const;

    friend std::ostream &operator<<(std::ostream &os, const Tree &tree);

    void insert(int value) override;

    bool exists(int value) override;

    void remove(int value) override;

    void print() override;

private:

    Element *root;
};

#endif //TREE_C_TREE_CPP_H
