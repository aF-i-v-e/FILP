#include <iostream>
using namespace std;
template <class T>
class BinomialTree
{
private:
	T* key; //����(���) ��������,
	int degree; // �������
	BinomialTree<T>* child; // ��������� �� ������ ������� ����
	BinomialTree<T>* parent; // ��������� �� �������� ����
	BinomialTree<T>* sibling;// ��������� �� ������� ����� ����, �� �� next

public:

    BinomialTree(T key) {
        this->key = new T(key);
        this->parent = nullptr;
        this->child = nullptr;
        this->sibling = nullptr;
        this->degree = 0;
    }

    BinomialTree() {
        this->key = nullptr;
        this->parent = nullptr;
        this->child = nullptr;
        this->sibling = nullptr;
        this->degree = 0;
    }

    ~BinomialTree() {
        delete child;
        delete sibling;
    }

    // Getter
    BinomialTree<T>* getParent() {
        return parent;
    }

    BinomialTree<T>* getChild() {
        return child; 
    }

    BinomialTree<T>* getSibling() { 
        return sibling;
    }

    T getKeyValue() {
        return *key;
    }

    T* getKey() {
        return key;
    }


    int getDegree() {
        return degree;
    }

    //Setter
    void setParent(BinomialTree<T>* parent) {
        this->parent = parent;
    }

    void setSibling(BinomialTree<T>* sibling) {
        this->sibling = sibling;
    }

    void setChild(BinomialTree<T>* child) {
        this->child = child;
    }

    void setKey(T key) {
        this->key = new T(key);
    }

    void increaseDegree() {
        degree += 1;
    }

    void setDegree(int degree) {
        this->degree = degree;
    }

    bool equalsNullPT() {
        if (this == nullptr)
            return true;
        if (this->getKey() == nullptr)
            return true;
        return false;
    }
    
    //���������� ������ ���� ��������
    static BinomialTree<T>* mergeTrees(BinomialTree<T>* Tree1, BinomialTree<T>* Tree2) {
        BinomialTree<T>* it1 = Tree1;
        BinomialTree<T>* it2 = Tree2;
        BinomialTree<T>* merged;
        if (it1->equalsNullPT()) {
            merged = it2;
            return merged;
        }
        if (it2->equalsNullPT()) {
            merged = it1;
            return merged;
        }

        if (it1->getDegree() < it2->getDegree()) {
            merged = it1;
            it1 = it1->getSibling();

        }
        else {
            merged = it2;
            it2 = it2->getSibling();

        }
        BinomialTree<T>* it3 = merged;
        while (it1 && it2) {
            if (it1->getDegree() < it2->getDegree()) {
                it3->setSibling(it1);
                it1 = it1->getSibling();
            }
            else {
                it3->setSibling(it2);
                it2 = it2->getSibling();
            }
            it3 = it3->getSibling();
        }
        if (it1) it3->setSibling(it1);
        if (it2) it3->setSibling(it2);
        return merged;
    }

    BinomialTree<T>* modify(BinomialTree<T>* otherTree) {
        BinomialTree<T>* newTree = new BinomialTree<T>();
        newTree->setKey(otherTree->getKeyValue());
        newTree->setChild(otherTree->getChild());
        newTree->setParent(otherTree->getParent());
        newTree->setDegree(otherTree->getDegree());
        newTree->setSibling(otherTree);
        return newTree;
    }


    static BinomialTree<T>* combineTreesOfSameDegree(BinomialTree<T>* w) {
        // ����������� �������� ����� ������� 
        BinomialTree<T>* h = w;
        BinomialTree<T>* prev = nullptr;
        BinomialTree<T>* next = h->getSibling();

        while (next) {
            if ((h->getDegree() != next->getDegree()) 
                || (!next->getSibling()->equalsNullPT() && next->getSibling()->getDegree() == h->getDegree())) {
                prev = h;
                h = next;
            } //���������� �� �������, � ������� ���������� �������
            else if (h->getDegree() == next->getDegree()) {
                if (h->getKeyValue() - next->getKeyValue() < 0) { //���������� � ������� 
                    //� ������� ���������
                    h->setSibling(next->getSibling()); //�� ����� ���, ��� ����������, ������������� �������
                    combine(next, h);
                }
                else {
                    if (prev) prev->setSibling(next);
                    combine(h, next);
                    h = next;
                    if (!prev) w = h;
                }
            }
            next = h->getSibling();
        }
        return w;
    }

    //��������� Tree1 � Tree2
    //curH -> curH.sibling
    static BinomialTree<T>* combine(BinomialTree<T>* Tree1, BinomialTree<T>* Tree2) {
        if (!Tree1) return Tree2;
        if (!Tree2) return Tree1;
        Tree1->setParent(Tree2); //������������� ��������
        Tree1->setSibling(Tree2->getChild());
        Tree2->setChild(Tree1);
        Tree2->increaseDegree();
        return Tree2;
    }

    //����� ���������� ������ �� ��� ���������� �������� key 
    BinomialTree<T>* search(T key) {
        if (this->getKeyValue() == key) return this; //���� ��� ���� �������� - ���������� ����

        //���� � ����� �����
        if (!child->equalsNullPT() && child->search(key))   return child->search(key);

        //���� � ����� �������
        if (!sibling->equalsNullPT() && sibling->search(key)) return sibling->search(key);

        return nullptr;
    }

    //���������� ������
    void printTree(string separator) {
        if (parent->equalsNullPT()) {
            cout << this->getKeyValue() << " " << endl;
            if (child) child->printTree(separator + "-");
        }
        else {
            cout << separator << this->getKeyValue() << " " << endl;
            if (child) child->printTree(separator + "-");
            if (sibling) sibling->printTree(separator);
        }
    }
};

template <class T> class BinomialHeap {
private:
    BinomialTree<T>* head; // ������ ����� ������������ ��������, � ������� ����������� ������

public:

    BinomialTree<T>* getHead() {
        return head;
    }

    void setHead(BinomialTree<T>* head) {
        this->head = head;
    }

    //������� ����
    void make() {
        this->head = new BinomialTree<T>();
    }

    //��������, ����������� ��� ������������ ���� � ����
    static BinomialHeap<T> merge(BinomialHeap<T> Heap1, BinomialHeap<T> Heap2) { //����� ��� ���� � ����
        BinomialHeap<T> Heap; // Heap � ��������� ������� 
        Heap.make();

        Heap.head = BinomialTree<T>::mergeTrees(Heap1.getHead(), Heap2.getHead()); //����� ������ ������ 1� � 2� ����
        Heap.head = BinomialTree<T>::combineTreesOfSameDegree(Heap.head); // ���������� � ���� ������ ������� � ���������� ����������� ���������
        return Heap;
    }

    //�������� ����� ������� � ������������ ����
    void insert(T key) {
        BinomialHeap<T> oneElementHeap;//����, ���������� ������������ �������
        oneElementHeap.make();
        oneElementHeap.setHead(new BinomialTree<T>(key));
        *this = BinomialHeap<T>::merge(*this, oneElementHeap);
    }

    //��������� ���� � ����������� ������ �� ������������ ���� � ���������� ��������� �� ����������� ����.
    BinomialTree<T>* extractMinimum() {
        BinomialTree<T>* minimum = this->popMinimumTree();
        BinomialTree<T>* visoutParentTree = setChildNoParent(minimum->getChild());
        BinomialHeap<T> newHeap; //����� ����, ������� �� ������������ �����
        newHeap.make();
        newHeap.setHead(visoutParentTree);
        *this = BinomialHeap<T>::merge(*this, newHeap); // ������� ������ ������ � ������� H'
        return minimum;
    }

    BinomialTree<T>* setChildNoParent(BinomialTree<T>* childTree) {
        BinomialTree<T>* prev = nullptr;
        BinomialTree<T>* next = nullptr;
        while (childTree) {
            childTree->setParent(nullptr); //������������� � �������� �������� null
            next = childTree->getSibling(); // ������� � ���������� �������
            childTree->setSibling(prev); // �������������� �����, ����� � ���������� ������� 
            //��� ������� � ������� �������� degree
            prev = childTree;
            childTree = next;
        }
        return prev;
    }


    BinomialTree<T>* popMinimumTree() {
        if (head) {
            BinomialTree<T>* prev = nullptr;
            BinomialTree<T>* temp = nullptr;
            BinomialTree<T>* minval = head;
            BinomialTree<T>* prevmin = nullptr;
            for (prev = head, temp = head->getSibling();temp != nullptr;prev = prev->getSibling(), temp = temp->getSibling())
                if (temp->getKeyValue() - minval->getKeyValue() <= 0) {
                    prevmin = prev;
                    minval = temp;
                }
            if (prevmin)prevmin->setSibling(minval->getSibling());
            else head = minval->getSibling();
            return minval;
        }
        return nullptr;
    }

    //��������� ��������� ���� �������� x ������������ ����, ���������� ��� ����� ��������
    void decreaseKey(BinomialTree<T>* x, T newValue) {
        if (newValue > x->getKeyValue()) // �������� �� ��, ��� ������� ���� x �� ������ ������������� ����� k  
            return;
        x->setKey(newValue);
        BinomialTree<T>* y = x;
        BinomialTree<T>* yParent = y->getParent();
        while (!yParent->equalsNullPT() && y->getKeyValue() < yParent->getKeyValue()) {
            T temp = y->getKeyValue();
            y->setKey(yParent->getKeyValue());
            yParent->setKey(temp);
            y = yParent; //������ y � yParent �������
            yParent = y->getParent();
        }
    }

    //delete - �������� ������� �� ����
    void deleteTree(BinomialTree<T>* x) {
        T minValue = getMinimum()->getKeyValue();
        decreaseKey(x, minValue - 1); // ���������� ����� �� ���������� ���������� �������� 
        extractMinimum(); // ������� ������� � ����������� ������
    }

    //������� ������� �� ���� �� ��� ��������
    void deleteByValue(T value) {
        BinomialTree<T>* element = findInHeap(value);
        if (element->equalsNullPT()) {
            cout << "Element with value = " + value + " doesn't exist in this heap!" << endl;
            return;
        }
        deleteTree(element);
    }

    BinomialTree<T>* findInHeap(T value) {
        if (head) return  (head->search(value));
        else return NULL;
    }

    //�������� ������� � ����������� ������ ��� �������� �� ����
    BinomialTree<T>* getMinimum() {
        BinomialTree<T>* minTree = head;
        if (head) {
            BinomialTree<T>* tmp = head;
            while (!tmp->equalsNullPT()) {
                if (tmp->getKeyValue() - minTree->getKeyValue() <= 0) {
                    minTree = tmp;
                }
                tmp = tmp->getSibling();
            }
        }
        return minTree;
    }

    //���������� ����
    void printHeap() {
        string separator = "-";
        cout <<"----------------------------------------------------------------"<< endl;
        cout << "Binomial Heap: " << endl;
        BinomialTree<T>* tmp = head;
        while (!tmp->equalsNullPT()) {
            cout << "Binomial Tree: " << endl;
            tmp->printTree(separator);
            cout << endl << endl;
            tmp = tmp->getSibling();
        }
        cout << "----------------------------------------------------------------" << endl;
    }
};

int main() {
    BinomialHeap<int> heap;
    heap.make(); // ������������ make
    heap.printHeap();

    heap.insert(13); // ������������ insert
    heap.insert(1);
    heap.insert(2);
    heap.insert(9);
    heap.insert(10);
    heap.printHeap();

    BinomialTree<int>* minimum = heap.getMinimum(); // ������������ getMinimum
    cout << "Minimum: " << minimum->getKeyValue() << endl;
    minimum = heap.extractMinimum(); // ������������ extractMinimum
    minimum = heap.getMinimum();
    cout << "Minimum: "<< minimum->getKeyValue() << endl;
    heap.printHeap();

    BinomialHeap<int> anotherHeap;
    anotherHeap.make();
    anotherHeap.insert(0);
    anotherHeap.insert(11);
    anotherHeap.insert(6);
    anotherHeap.insert(12);
    anotherHeap.printHeap();
    heap = BinomialHeap<int>::merge(heap, anotherHeap);  // ������������ merge
    heap.printHeap();

    BinomialTree<int>* element = heap.findInHeap(12);
    heap.decreaseKey(element, 5);  // ������������ decreaseKey
    heap.printHeap();

    element = heap.findInHeap(5);
    heap.deleteTree(element);  // ������������ deleteTree(��� � ���� ������� delete)
    heap.printHeap();
}