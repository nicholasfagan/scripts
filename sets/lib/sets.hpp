#ifndef SETS_SETS_HPP
#define SETS_SETS_HPP

#include <unordered_map>
#include <memory>

namespace sets {

    template<class T> class Node;

    /**
     * A collection of disjoint sets that have a representative.
     * sets can be created, joined, and can find their representatives.
     * @tparam T The type to store in the sets.
     */
    template<class T>
    class DisjointSets {
    public:
        DisjointSets() = default;
        void create(T data);
        Node<T> *find(T data);
        void join(T a, T b);
    private:
        std::unordered_map<T, Node<T>> map;
    };

    /**
     * Node contains its data, a pointer to its parent, and a count of its children.
     * @tparam T The type of data.
     */
    template<class T>
    class Node {
        friend class DisjointSets<T>;
        T data;
        Node<T> *parent;
        size_t size;

        /**
         * Subtracts from the count of this node and its parents.
         * @param n number to subtract
         */
        void sub(size_t n) {
            //size -= n;
            //if(parent) parent->sub(n);
        }

        /**
         * Adds to the count of this node and ones above it.
         * @param n number to add.
         */
        void add(size_t n) {
            //size += n;
            //if(parent) parent->add(n);
        }

        /**
         * Sets the parent of this node.
         * Also updates count of old and new parents.
         * @param p The parent to set
         */
        void setParent(Node* p) {
            if(parent) parent->sub(size);
            parent = p;
            if(parent) parent->add(size);
        }


    public:
        /**
         * Create a new Node with the given data, no parent, and size of 1.
         * @param data The data to create with
         */
        explicit Node(T data) : data(std::move(data)), parent(nullptr), size(1) {}

        /**
         * Get the data in this node
         * @return data
         */
        T get() { return data; }

        /**
         * Get the number of children this node has.
         * @return
         */
        size_t count() { return size; }

    };

    template<class T>
    void DisjointSets<T>::create(T data) {
        if(!map.count(data)) map.emplace(data, std::move(data));
    }

    template<class T>
    Node<T>* DisjointSets<T>::find(T data) {
        if (!map.count(data)) return nullptr;
        auto p = &map.at(data);
        auto n = p;
        // find root node of tree
        while (n->parent) n = n->parent;
        // point trace all along to root
        while (p->parent) {
            p->setParent(n);
            p = p->parent;
        }
        // return the root
        return n;
    }

    template<class T>
    void DisjointSets<T>::join(T a, T b) {
        auto A = find(a);
        auto B = find(b);
        if (A && B && A != B) {
            if (A->count() >= B->count())
                B->setParent(A);
            else
                A->setParent(B);
        }
    }

} // namespace sets

#endif //SETS_SETS_HPP
