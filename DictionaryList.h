#ifndef DICTIONARY_LIST_H
#define DICTIONARY_LIST_H

#include <iostream>

template <typename KeyT>
class DictionaryList {
public:
    DictionaryList() = default;

    DictionaryList(const DictionaryList& dictionaryList) {
        if (dictionaryList.head_ != nullptr) {
            head_ = new Node(*dictionaryList.head_);
            Node* currentNode = head_;
            Node* currentNodeOfOther = dictionaryList.head_->nextNode;
            try {
                while (currentNodeOfOther != nullptr) {
                    currentNode->nextNode = new Node(*currentNodeOfOther);
                    currentNodeOfOther = currentNodeOfOther->nextNode;
                    currentNode = currentNode->nextNode;
                }
            }
            catch (const std::bad_alloc& e) {
                Node* currentNodeDeleteLoop = head_;
                while (currentNodeDeleteLoop != nullptr) {
                    Node* nodeToDelete = currentNodeDeleteLoop;
                    currentNodeDeleteLoop = currentNodeDeleteLoop->nextNode;
                    delete nodeToDelete;
                }
            }
        }
    }

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

    DictionaryList<KeyT>& operator=(const DictionaryList<KeyT>& dictionaryList) {
        if (&dictionaryList == this) {
            return *this;
        }

        DictionaryList dictionaryListCopy(dictionaryList);
        swap(dictionaryListCopy);
        return *this;
    }

    DictionaryList<KeyT>& operator=(DictionaryList<KeyT>&& dictionaryList) noexcept {
        if (this != &dictionaryList) {
            DictionaryList copy = DictionaryList(std::move(dictionaryList));
            swap(copy);
        }
        return *this;
    }

    bool insert(const KeyT& element) {
        if (head_ == nullptr) {
            head_ = new Node(element, nullptr);
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
                Node* newNode = new Node(element, head_);
                head_ = newNode;
                return true;
            }

            prevNode = currentNode;
            currentNode = currentNode->nextNode;
        }
        if (prevNode != nullptr && prevNode->data < element) {
            prevNode->nextNode = new Node(element, nullptr);
            return true;
        }
        return false;
    }

    bool remove(const KeyT& element) {
        if (head_ != nullptr && head_->data == element) {
            Node* nodeToDelete = head_;
            head_ = head_->nextNode;
            delete nodeToDelete;
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
        if (&other == this || other.head_ == nullptr) {
            return;
        }

        Node* currentNode = head_;
        Node* otherNode = other.head_;

        if (currentNode == nullptr) {
            head_ = other.head_;
            other.head_ = nullptr;
            return;
        }

        Node* newNode = nullptr;
        if (currentNode->data < otherNode->data) {
            newNode = currentNode;
            currentNode = currentNode->nextNode;
        }
        else if (currentNode->data > otherNode->data) {
            newNode = otherNode;
            otherNode = otherNode->nextNode;
        }
        else {
            newNode = currentNode;
            currentNode = currentNode->nextNode;
            Node* duplicateNodeToDelete = otherNode;
            otherNode = otherNode->nextNode;
            delete duplicateNodeToDelete;
        }
        Node* newHead = newNode;

        while (currentNode != nullptr || otherNode != nullptr) {
            if (currentNode == nullptr) {
                newNode->nextNode = otherNode;
                otherNode = otherNode->nextNode;
                newNode = newNode->nextNode;
                continue;
            }
            if (otherNode == nullptr) {
                newNode->nextNode = currentNode;
                currentNode = currentNode->nextNode;
                newNode = newNode->nextNode;
                continue;
            }

            if (currentNode->data < otherNode->data) {
                newNode->nextNode = currentNode;
                currentNode = currentNode->nextNode;
                newNode = newNode->nextNode;
                continue;
            }
            if (otherNode->data < currentNode->data) {
                newNode->nextNode = otherNode;
                otherNode = otherNode->nextNode;
                newNode = newNode->nextNode;
                continue;
            }
            if (otherNode->data == currentNode->data) {
                newNode->nextNode = currentNode;
                currentNode = currentNode->nextNode;
                Node* duplicateNodeToDelete = otherNode;
                otherNode = otherNode->nextNode;
                delete duplicateNodeToDelete;
                newNode = newNode->nextNode;
                continue;
            }
        }

        newNode->nextNode = nullptr;
        head_ = newHead;
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

        Node(KeyT data, Node* nextNode) :
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