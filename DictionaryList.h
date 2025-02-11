#ifndef DICTIONARY_LIST_H
#define DICTIONARY_LIST_H

#include <iostream>

template <typename KeyT>
class DictionaryList {
public:
    DictionaryList() = default;

    //copy constructor
    DictionaryList(const DictionaryList& dictionaryList) {
        if (dictionaryList.head_ != nullptr) {
            head_ = new Node(*dictionaryList.head_); //todo bad_alloc
            Node* currentNode = head_;
            Node* currentNodeOfOther = dictionaryList.head_->nextNode;
            while (currentNodeOfOther!=nullptr) {
                currentNode->nextNode = new Node(*currentNodeOfOther);//todo bad_alloc
                currentNodeOfOther = currentNodeOfOther->nextNode;
                currentNode = currentNode->nextNode;
            }
        }
    }

    //move constructor
    DictionaryList(DictionaryList&& dictionaryList) noexcept {
        std::swap(head_, dictionaryList.head_);
    }

    ~DictionaryList() {
        Node* currentNode = head_;
        while (currentNode != nullptr) {
            const Node* nodeToDelete = currentNode;
            currentNode = currentNode->nextNode;
            delete nodeToDelete;
        }
    }

    //copy assignment operator
    DictionaryList<KeyT>& operator=(const DictionaryList<KeyT>& dictionaryList) {
        DictionaryList dictionaryListCopy(dictionaryList);
        swap(dictionaryListCopy);
        return *this;
    }

    //move assignment operator
    DictionaryList<KeyT>& operator=(DictionaryList<KeyT>&& dictionaryList) noexcept {
        std::swap(head_, dictionaryList.head_);
        return *this;
    }

    bool insert(const KeyT& element) {
        if (head_ == nullptr) {
            head_ = new Node(element, nullptr); //todo bad_alloc
            return true;
        }

        Node* currentNode = head_;
        Node* prevNode = nullptr;
        while (currentNode != nullptr) {
            if (currentNode->data == element) {
                return false;
            }

            if ((prevNode != nullptr) && (prevNode->data < element) && (currentNode->data > element)) {
                Node* newNode = new Node(element, currentNode); //todo bad_alloc
                prevNode->nextNode = newNode;
                return true;
            }
            if ((prevNode == nullptr) && (element < currentNode->data)) {
                Node* newNode = new Node(element, head_); //todo bad_alloc
                head_ = newNode;
                return true;
            }

            prevNode = currentNode;
            currentNode = currentNode->nextNode;
        }
        if (prevNode != nullptr && prevNode->data < element) {
            prevNode->nextNode = new Node(element, nullptr); //todo bad_alloc
            return true;
        }
        return false;
    }

    bool remove(const KeyT& element) {
        if (head_ != nullptr && head_->data == element && head_->nextNode == nullptr) {
            delete head_;
            return true;
        }

        Node* currentNode = head_;
        while (currentNode != nullptr) {
            if (currentNode->nextNode != nullptr && currentNode->nextNode->data == element) {
                const Node* nodeToDelete = currentNode->nextNode;
                currentNode->nextNode = currentNode->nextNode->nextNode;
                delete nodeToDelete;
                return true;
            }
            if (currentNode->nextNode != nullptr && currentNode->nextNode->data > element) {
                return false;
            }
            currentNode = currentNode->nextNode;
        }
        return false;
    }

    bool search(const KeyT& element) {
        Node* currentNode = head_;
        while (currentNode != nullptr) {
            if (currentNode->data == element) {
                return true;
            }
            if (currentNode->data > element) {
                return false;
            }
            currentNode = currentNode->nextNode;
        }
        return false;
    }

    void merge(DictionaryList& other) {
        Node* otherNode = other.head_;
        if (other.head_->data < head_->data) {
            otherNode = other.head_->nextNode;
            other.head_->nextNode = head_;
            head_ = other.head_;
        }

        Node* currentNode = head_;
        while (currentNode->nextNode != nullptr && otherNode != nullptr) {
            if (currentNode->data < otherNode->data && currentNode->nextNode->data > otherNode->data) {
                Node* nodeToInsert = otherNode;
                nodeToInsert->nextNode = currentNode->nextNode;
                currentNode->nextNode = nodeToInsert;

                otherNode = otherNode->nextNode;
                continue;
            }
            currentNode = currentNode->nextNode;
        }
        if (otherNode != nullptr) {
            currentNode->nextNode = otherNode;
        }

        other.head_ = nullptr;
    }

    void subtract(const DictionaryList& other) {
        //do nothing
    }

    template <typename KeyT1>
    friend std::ostream& operator<<(std::ostream&, const DictionaryList<KeyT1>&);

private:
    struct Node {
        KeyT data;
        Node* nextNode;

        Node(KeyT data, Node* nextNode):
            data(data),
            nextNode(nextNode)
        { }
    };

    Node* head_ = nullptr;

    void swap(DictionaryList<KeyT>& dictionaryList) noexcept {
        std::swap(head_, dictionaryList.head_);
    }
};


template <typename  KeyT>
DictionaryList<KeyT> intersect(const DictionaryList<KeyT>& first, const DictionaryList<KeyT>& second) {
    //do nothing
    return DictionaryList<KeyT>();
}


template <typename  KeyT>
std::ostream& operator<<(std::ostream& os, const DictionaryList<KeyT>& dictionaryList) {
    auto currentNode = dictionaryList.head_;
    while (currentNode != nullptr) {
        os << currentNode->data << " ";
        currentNode = currentNode->nextNode;
    }
    return os;
}

#endif //DICTIONARY_LIST_H
