#include <iostream>
#include <list>

class list_class {
    public:
        void list_print(std::list<int> i)
        {
            std::list<int>::const_iterator t;

            for (t = i.begin(); t != i.end(); t ++) {
                std::cout << *t << "->";
            }
            std::cout << std::endl;
        }

        void list_cprint(std::list<int> i)
        {
            std::list<int>::const_iterator t;

            for (t = i.cbegin(); t != i.cend(); t ++) {
                std::cout << *t << "->";
            }
            std::cout << std::endl;
        }

        void list_rprint(std::list<int> i)
        {
            std::list<int>::const_reverse_iterator t;

            for (t = i.rbegin(); t != i.rend(); t ++) {
                std::cout << *t << "->";
            }
            std::cout << std::endl;
        }
};

int main()
{
    std::list<int> i {1, 2, 3, 4, 5}; // setting up the list initialisation
    std::list<int>::const_iterator t;
    std::list<int>::const_reverse_iterator rt;

    std::list<int> new_list {4, 1, 2, 4};

    std::list<int> i_copy = i;
    std::list<int> *i_ptr = &i;

    list_class l;

    //add at front
    i.push_front(4);
    //add at end
    i.push_back(8);

    std::cout << "begin" << std::endl;
    l.list_print(i);

    std::cout << "cbegin" << std::endl;
    l.list_cprint(i);

    std::cout << "rbegin" << std::endl;
    l.list_rprint(i);

    std::cout <<"front element:" << i.front() << std::endl;
    std::cout <<"last element:" << i.back() << std::endl;

    std::cout << "list empty:" << (i.empty() ? "Yes" : "No") << std::endl;

    std::cout << "list element number:" << i.size() << std::endl;

    std::cout << "list max_size:" << i.max_size() << std::endl;

    std::cout << "clearing list" << std::endl;

    i.clear();

    std::cout << "list count:" << i.size() << std::endl
              << "list empty:" << (i.empty() ? "Yes" : "No") << std::endl;

    i.assign(new_list.begin(), new_list.end());

    l.list_print(i);
    l.list_print(i_copy);
    l.list_print(*i_ptr);

    i.sort(std::greater<int>());
    l.list_print(i);

    i.sort(std::less<int>());
    l.list_print(i);
}

