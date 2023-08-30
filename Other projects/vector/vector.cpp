#include <iostream>
#include <string>
#include "std_lib_facilities.h"

using namespace std;

template <typename T, typename A>
class Vb
{
public:
    int sz;                         //размер вектора
    T *elem;                        //указатель на 1ый элемент
    int space;                      //кол-во элементов + свободное место или слоты для неинициализированных элементов
    A alloc;                        //работает с памятью, вьделяемой для элементов
    Vb()
    {
        sz = 0;
        space = 0;
        elem = nullptr;
    }
    Vb(A &a, int n)
    {
        alloc = a;
        elem = a.allocate(n);
        sz = n;
        space = n;
    }
    ~Vb()
    {
        alloc.deallocate(elem, space);
    }
};

template <typename T, typename A = allocator<T>>
class vectop: private Vb<T,A>              //класс для всех типов Т
{
public:
    vectop()                              //дефолтный конструктор
    {
        this->sz = 0;
        this->elem = nullptr;
        this->space = 0;
    };

    vectop(initializer_list<T> lst)       // Конструктор со списком инициализации
    {
        this->sz = lst.size();
        this->elem = new T[this->sz];
        copy(lst.begin(), lst.end (), this->elem) ;  // Инициализация с помощью copy ()
    }

    explicit vectop(int s) // конструктор выделяет память
    {
        this->sz =  s;
        this->space = s;
        this->elem = new T[s];
    }

    int size() //возвращает количество элементов вектора
    {
        return this->sz;
    }

    ~vectop() // деструктор освобождает память
    {
        delete[] this->elem;
    }

    vectop(const vectop&);                    // копирующий конструктор                           (1)
    vectop& operator= (const vectop&);         //копирующее присвоение                           (2)
    vectop (vectop&& );                        // Перемещающий конструктор                        (3)
    vectop& operator= (vectop&&);             // Перемещающее присваивание                       (4)
    T& operator [] (int n)  // Чтобы обращаться к нек. вектору по индексу v[i]
    {
        return this->elem[n];
    }
    const T& operator [] (int n) const          //Чтобы обращаться к const вектору по индексу v[i]
    {
        return this->elem[n];
    }

    void reserve(int newalloc);                     // добавляет память для новых элементов        (5)
    int capacity () const
    {
        return this->space;
    }
    void resize(int newsize , T val = T());            // изменение размера вектора                (6)
    void push_back (const T& val);                    // добавление элемента                       (7)

    T& at (int n);                                //Доступ с проверкой                            (8)
    const T& at (int n) const;                    //Доступ с проверкой
};

template <typename T, typename A>
vectop<T, A>::vectop(const vectop& arg)
{
    this->sz = arg.sz;
    this->elem = new T[arg.sz];
    copy(arg.elem, arg.elem+arg.sz, this->elem);
}

template <typename T, typename A>
vectop<T,A>&  vectop<T,A>::operator = (const vectop& a)  // делает этот вектор копией вектора а
{
    if (this == &a)
        return *this ;             // Самоприсваивание , ничего делать не надо
    if (a.sz <= this->space)                         // Памяти достаточно, новая память не нужна
    {
        for (int i = 0; i<a.sz; ++i)
            this->elem[i] = a.elem[i];            // Копируем элементы
        this->sz = a.sz;
        return *this ;
    }
    T *p = new T [a.sz];  // выделяем новую память
    for (int i = 0; i < a.sz; i++)
        p[i] = a.elem[i];           // копируем элементы
    delete[] this->elem;                 // освобождаем память
    this->space = a.sz;              // устанавливаем новый размер
    this->elem = p;                       // устанавливаем указатель на новые элементы
    return *this;                   //возвращаем ссылку на текущий объект
}

template <typename T, typename A>
vectop<T,A>::vectop (vectop&& a)
{
    this->sz = a.sz;
    this->elem = a.elem;
    a.sz = 0;               // Делаем вектор а пустым
    a.elem = nullptr;
}

template <typename T, typename A>
vectop<T,A>&  vectop<T,A>::operator = (vectop&& a) // Перемещаем а в текущий вектор
{
    delete[] this->elem;          // Освобождение старой памяти
    this->elem = a.elem;          // Копирование elem и sz из а
    this->sz = a.sz;
    a.elem = nullptr;       // Делаем вектор а пустым
    a.sz = 0;
    return *this;           //Возврат ссылки на себя
}

template <typename T, typename A>
void vectop<T,A>::reserve (int newalloc)
{
    if (newalloc <= this->space)
        return;                     // Размер никогда не уменьшается

    Vb<T,A> b(this->alloc, newalloc);                                // Выделение новой памяти
    uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);    // Копируем старые элементы
    for (int i = 0; i < this->sz; i++)
        this->alloc.destroy(&this->elem[i]);                        //удаляем старые данные
    swap<Vb<T, A>>(*this, b) ;                                      // обмен преставлений
}

template <typename T, typename A>
void vectop<T,A>::resize (int newsize, T val)
{
    this->reserve(newsize) ;
    for (int i = this->sz ; i < newsize ; ++i)
        this->alloc.construct(&this->elem[i], val);     // Создаём
    for (int i = this->sz ; i < newsize ; ++i)
        this->alloc.destroy(&this->elem[i]);            // Удаляем
    this->sz = newsize;
}

template <typename T, typename A>
void vectop<T,A>::push_back (const T& val)
{
    if (this->space == 0)
        reserve(8);                        // Выделяем память для 8 элементов
    else if (this->sz == this->space)
        reserve(2 * this->space);              // Выделяем дополнительную память
    this->alloc.construct(&this->elem[this->sz], val);             // Добавляем val в конец вектора
    ++this->sz;                                       // увеличиваем количество элементов
}

template <typename T, typename A>
T& vectop<T,A>:: at (int n)
{
    if (n < 0 || this->sz <= n)
        throw out_of_range("Выход за диапазон значений");
    return this->elem[n];
}

int main()
{
    vectop<int> v1 = {1,2,3,4,5,6,7,8,9,10};
    vectop<string> v2 = {"help", "me", "please", "I", "want", "to", "die"};
    v1.resize(13, 100);
    for (int i = 0; i < v1.size(); i++)
        cout<<v1[i]<<' ';
    cout<<'\n';

    for(int i = 0; i < v2.size(); i++)
        cout<<v2[i]<<' ';
    cout<<'\n';
}
