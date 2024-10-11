#ifndef LIST_HPP
#define LIST_HPP

#include <algorithm>
#include <limits>

// Структура ноды для списка
template <class Type>
struct _List_node {
  _List_node *next_,
      *prev_;  // указатели на следющий и предыдущий элементы списка
  Type value_;  // значение элемента списка

  // конструктор
  _List_node(const Type& value)
      : next_(nullptr), prev_(nullptr), value_(value) {}
};

// Класс итератора списка
template <class Type>
struct _List_iterator {
  // вспомогательные юзинги
  using _self = _List_iterator<Type>;
  using _node = _List_node<Type>;
  using pointer = Type*;
  using reference = Type&;

  _node* current;  // указатель на элемент списка
  _node* last;  // указатель на последний элемент списка (используется для
                // получения значчения если указатель current равен nullptr,
                // пример: *my_list.end();)

  // конструкторы
  _List_iterator() noexcept : current(nullptr), last(nullptr) {}

  _List_iterator(_node* pointer) noexcept : current(pointer), last(nullptr) {}

  _List_iterator(_node* pointer, _node* pointer_of_last) noexcept
      : current(pointer), last(pointer_of_last) {}

  // вспомогательная функция кастования в константу
  _self __const_cast__() const noexcept { return *this; }

  // операторы получения значения элемента
  reference operator*() const noexcept {
    return current == nullptr ? last->value_ : current->value_;
  }

  pointer operator->() const noexcept {
    return current == nullptr ? &last->value_ : &current->value_;
  }

  // операторы перехода к следующему элементу
  _self& operator++() noexcept {
    current = current->next_;
    return *this;
  }

  _self operator++(int) noexcept {
    _self tmp = *this;
    current = current->next_;
    return tmp;
  }

  // операторы перехода к предыдущему элементу
  _self& operator--() noexcept {
    current = current->prev_;
    return *this;
  }

  _self operator--(int) noexcept {
    _self tmp = *this;
    current = current->prev_;
    return tmp;
  }

  // операторы сравнения
  friend bool operator==(const _self& left, const _self& right) noexcept {
    return left.current == right.current;
  }

  friend bool operator!=(const _self& left, const _self& right) noexcept {
    return left.current != right.current;
  }
};

// Класс константного итератора списка
template <class Type>
struct _List_const_iterator {
  // вспомогательные юзинги
  using _self = _List_const_iterator<Type>;
  using _node = const _List_node<Type>;
  using interator = _List_iterator<Type>;
  using pointer = Type*;
  using reference = Type&;

  _node* current;  // указатель на элемент списка
  _node* last;  // указатель на последний элемент списка (используется для
                // получения значчения если указатель current равен nullptr,
                // пример: *my_list.end();)

  // конструкторы
  _List_const_iterator() noexcept : current(nullptr), last(nullptr) {}

  _List_const_iterator(_node* pointer) noexcept
      : current(pointer), last(nullptr) {}

  _List_const_iterator(_node* pointer, _node* pointer_of_last) noexcept
      : current(pointer), last(pointer_of_last) {}

  _List_const_iterator(const interator& it) noexcept
      : current(it.current), last(it.last) {}

  // вспомогательная функция кастования из константу
  interator __const_cast__() const noexcept {
    return interator(const_cast<_List_node<Type>*>(current));
  }

  // операторы получения значения элемента
  Type operator*() const noexcept {
    return current == nullptr ? last->value_ : current->value_;
  }

  pointer operator->() const noexcept {
    return static_cast<const pointer>(&(*this->__const_cast__()));
  }

  // операторы перехода к следующему элементу
  _self& operator++() noexcept {
    current = current->next_;
    return *this;
  }

  _self operator++(int) noexcept {
    _self tmp = *this;
    current = current->next_;
    return tmp;
  }

  // операторы перехода к предыдущему элементу
  _self& operator--() noexcept {
    current = current->prev_;
    return *this;
  }

  _self operator--(int) noexcept {
    _self tmp = *this;
    current = current->prev_;
    return tmp;
  }

  // операторы сравнения
  friend bool operator==(const _self& left, const _self& right) noexcept {
    return left.current == right.current;
  }

  friend bool operator!=(const _self& left, const _self& right) noexcept {
    return left.current != right.current;
  }
};

// Класс списка
template <class Type>
class list {
 public:
  // вспомогательные юзинги
  using size_type = std::size_t;
  using value_type = Type;
  using iterator = _List_iterator<value_type>;
  using const_iterator = _List_const_iterator<value_type>;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;

 protected:
  using _node = _List_node<value_type>;

  _node *first_, *last_;  // указатели на первый и последний элементы списка
  size_type size_;        // размер списка

  // функция копирования
  void __copy__(const list& other) noexcept {
    clear();
    if (other.first_ != nullptr)
      for (const_reference elem : other) push_back(elem);
  }

  // функция переноса
  void __move__(list&& other) noexcept {
    clear();

    size_ = other.size_;
    first_ = other.first_;
    last_ = other.last_;

    other.size_ = 0;
    other.first_ = other.last_ = nullptr;
  }

 public:
  /**
   *  @brief Создает список без каких-либо элементов.
   */
  list() : first_(nullptr), last_(nullptr), size_(0) {}

  /**
   * @brief Создает новый объект списка.
   *
   * @param count - количество элементов в новом списке.
   */
  list(size_type count) : list() {
    value_type value;
    for (size_type i = 0; i < count; i++) push_back(value);
  }

  /**
   * @brief Создает новый объект списка.
   *
   * @param count - количество элементов в новом списке.
   * @param value - значение, которым будет заполнен список.
   */
  list(size_type count, const value_type& value) : list() {
    for (size_type i = 0; i < count; i++) push_back(value);
  }

  /**
   * @brief Конструктор копирования.
   *
   * @param other - список, который нужно скопировать.
   */
  list(const list& other) : list() { __copy__(other); }

  /**
   * @brief Конструктор перемещения.
   *
   * @param other - Список, который нужно переместить.
   */
  list(list&& other) noexcept : list() { __move__(std::move(other)); }

  /**
   * @brief Создает контейнер с содержимым списка инициализаторов init.
   *
   * @param init - список инициализаторов, с помощью которого можно
   * инициализировать элементы контейнера.
   */
  list(std::initializer_list<value_type> init) : list() {
    for (auto& elem : init) push_back(elem);
  }

  /**
   * @brief Уничтожает объект списка.
   */
  ~list() { clear(); }

  /**
   * @brief Оператор копирования.
   *
   * @param right - список, который нужно скопировать.
   * @return list&
   */
  list& operator=(const list& right) {
    __copy__(right);
    return *this;
  }

  /**
   * @brief Оператор перемещения.
   *
   * @param right - Список, который нужно переместить.
   * @return list&
   */
  list& operator=(list&& right) noexcept {
    __move__(std::move(right));
    return *this;
  }

  /**
   * @brief Возвращает итератор к первому элементу.
   *
   * @return iterator
   */
  iterator begin() { return iterator(first_); }

  /**
   * @brief Возвращает итератор const для первого элемента.
   *
   * @return iterator
   */
  const_iterator begin() const { return const_iterator(first_); }

  /**
   * @brief Возвращает итератор const для первого элемента.
   *
   * @return iterator
   */
  const_iterator cbegin() const noexcept { return const_iterator(first_); }

  /**
   * @brief Возвращает итератор к последнему элементу.
   *
   * @return iterator
   */
  iterator end() { return iterator(nullptr, last_); }

  /**
   * @brief Возвращает итератор const к последнему элементу.
   *
   * @return iterator
   */
  const_iterator end() const { return const_iterator(nullptr, last_); }

  /**
   * @brief Возвращает итератор const к последнему элементу.
   *
   * @return iterator
   */
  const_iterator cend() const noexcept {
    return const_iterator(nullptr, last_);
  }

  /**
   * @brief Очищает список.
   */
  void clear() {
    while (size_ > 0) pop_back();
  }

  /**
   * @brief Добавляет новый элемент в конец списка.
   *
   * @param value - Новый элемент.
   */
  void push_back(const value_type& value) { insert(end(), value); }

  /**
   * @brief Добавляет новый элемент в начало списка.
   *
   * @param value - Новый элемент.
   */
  void push_front(const value_type& value) { insert(begin(), value); }

  /**
   * @brief Удаляет последний элемент из списка.
   */
  void pop_back() { erase(end()); }

  /**
   * @brief Удаляет первый элемент из списка.
   */
  void pop_front() { erase(begin()); }

  /**
   * @brief Заменяет содержимое контейнера.
   *
   * @param count - Количество копий.
   * @param value - Значения копий.
   */
  void assign(size_type count, const_reference value) {
    clear();
    for (size_type i = 0; i < count; i++) push_back(value);
  }

  /**
   * @brief Заменяет содержимое элементами из другого списка.
   *
   * @param other - Другой список.
   */
  void assign(list other) { *this = std::move(other); }

  /**
   * @brief Заменяет содержимое копиями файлов из диапазона [first, last].
   *
   * @tparam InputIterator
   * @param first - Итератор, ведущий к первому элементу.
   * @param last - Итератор, ведущий к последнему элементу.
   */
  void assign(iterator first, iterator last) {
    clear();
    for (iterator it = first; it != last; it++) push_back(*it);
  }

  /**
   * @brief Возвращает ссылку на первый элемент.
   *
   * @return reference
   */
  reference front() { return first_->value_; }

  /**
   * @brief Возвращает постоянную ссылку на первый элемент.
   *
   * @return const_reference
   */
  const_reference front() const {
    return static_cast<const_reference>(first_->value_);
  }

  /**
   * @brief Возвращает ссылку на последний элемент.
   *
   * @return reference
   */
  reference back() { return last_->value_; }

  /**
   * @brief Возвращает постоянную ссылку на последний элемент.
   *
   * @return const_reference
   */
  const_reference back() const {
    return static_cast<const_reference>(last_->value_);
  }

  /**
   * @brief Вставляет элемент в указанное место контейнера.
   *
   * @param pos - Позиция, перед которой будет размещен элемент.
   * @param value - Значение элемента.
   * @return iterator
   */
  iterator insert(const_iterator pos, const value_type& value) {
    _node* new_item = new _node(value);
    if (size_ == 0)
      first_ = last_ = new_item;
    else if (pos == begin()) {
      new_item->next_ = first_;
      first_->prev_ = new_item;
      first_ = new_item;
    } else if (pos == end()) {
      new_item->prev_ = last_;
      last_->next_ = new_item;
      last_ = new_item;
    } else {
      _node* prev = pos.current->prev_;
      _node* next = pos.__const_cast__().current;
      prev->next_ = new_item;
      new_item->prev_ = prev;
      next->prev_ = new_item;
      new_item->next_ = next;
    }
    size_++;
    return iterator(new_item);
  }

  /**
   * @brief Вставляет элементы в указанное место контейнера.
   *
   * @param pos - Позиция, перед которой будут располагаться элементы.
   * @param count - Количество вставляемых элементов.
   * @param value - Значение элементов.
   * @return iterator
   */
  iterator insert(const_iterator pos, size_type count,
                  const value_type& value) {
    for (size_type i = 0; i < count; i++) insert(pos, value);
    return pos.__const_cast__();
  }

  /**
   * @brief Вставляет элементы в указанное место контейнера.
   *
   * @param pos - Позиция, перед которой будут располагаться элементы.
   * @param first - Итератор, ведущий к первому элементу.
   * @param last - Итератор переходит к последнему элементу.
   * @return iterator
   */
  iterator insert(const_iterator pos, iterator first, iterator last) {
    iterator start_pos = pos.__const_cast__();
    for (iterator it = first; it != last; it++) {
      insert(pos, *it);
      if (pos != end()) pos++;
    }
    return start_pos;
  }

  /**
   * @brief Вставляет элементы в указанное место контейнера.
   *
   * @param pos - Позиция, перед которой будут располагаться элементы.
   * @param other - Другой список.
   * @return iterator
   */
  iterator insert(const_iterator pos, list<Type> other) {
    iterator start_pos = pos.__const_cast__();
    for (Type elem : other) {
      insert(pos, elem);
      if (pos != end()) pos++;
    }
    return start_pos;
  }

  /**
   * @brief Проверяет, пуст ли список.
   *
   * @return true
   * @return false
   */
  bool empty() const {
    if (first_ == nullptr) return true;
    return false;
  }

  /**
   * @brief Удаляет указанный элемент из контейнера.
   *
   * @param pos - Удаляет элемент в нужном положении.
   * @return iterator
   */
  iterator erase(const_iterator pos) {
    _node* res = nullptr;
    if (size_ == 0) {
    } else if (size_ == 1) {
      delete first_;
      first_ = last_ = nullptr;
    } else if (pos == end() || pos.current == last_) {
      _node* temp = last_;
      last_ = last_->prev_;
      last_->next_ = nullptr;
      delete temp;
      res = last_;
    } else if (pos == begin()) {
      _node* temp = first_;
      first_ = first_->next_;
      first_->prev_ = nullptr;
      delete temp;
      res = size_ == 1 ? last_ : first_->next_;
    } else {
      _node* temp = pos.__const_cast__().current;
      temp->prev_->next_ = temp->next_;
      temp->next_->prev_ = temp->prev_;
      res = size_ == 1 ? last_ : temp->next_;
      delete temp;
    }
    size_--;
    return iterator(res);
  }

  /**
   * @brief Удаляет указанные элементы из контейнера в диапазоне [first, last).
   *
   * @param first - Итератор, ведущий к первому элементу.
   * @param last - Итератор, ведущий к последнему элементу.
   * @return iterator
   */
  iterator erase(const_iterator first, const_iterator last) {
    iterator res;
    for (const_iterator it = first; it != last;) res = erase(it++);
    return res;
  }

  /**
   * @brief Возвращает максимальное количество элементов в контейнере.
   *
   * @return size_type
   */
  size_type max_size() const {
    return static_cast<size_type>((std::numeric_limits<size_type>::max)()) /
           sizeof(_node) /
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
           1;
#else
           2;
#endif
  }

  /**
   * @brief Функция ничего не делает, если other ссылается на тот же объект,
   * что и *this. В противном случае other преобразуется в *this. Оба списка
   * должны быть отсортированы. Никакие элементы не копируются, а контейнер
   * other становится пустым после слияния. Эта операция стабильна: для
   * эквивалентных элементов в двух списках элементы из *this всегда
   * предшествуют элементам из other, и порядок эквивалентных элементов из *this
   * и other не меняется.
   *
   * @param other - Другой список.
   */
  void merge(list& other) {
    merge(std::move(other),
          [](const value_type& a, const value_type& b) { return a <= b; });
  }

  /**
   * @brief Функция ничего не делает, если other ссылается на тот же объект,
   * что и *this. В противном случае other преобразуется в *this. Оба списка
   * должны быть отсортированы. Никакие элементы не копируются, а контейнер
   * other становится пустым после слияния. Эта операция стабильна: для
   * эквивалентных элементов в двух списках элементы из *this всегда
   * предшествуют элементам из other, и порядок эквивалентных элементов из *this
   * и other не меняется.
   *
   * @param other - Другой список.
   */
  void merge(list&& other) {
    merge(std::move(other),
          [](const value_type& a, const value_type& b) { return a <= b; });
  }

  /**
   * @brief  Функция ничего не делает, если other ссылается на тот же объект,
   * что и *this. В противном случае other преобразуется в *this. Оба списка
   * должны быть отсортированы. Никакие элементы не копируются, а контейнер
   * other становится пустым после слияния. Эта операция стабильна: для
   * эквивалентных элементов в двух списках элементы из *this всегда
   * предшествуют элементам из other, и порядок эквивалентных элементов из *this
   * и other не меняется.
   *
   * @tparam Compare должен соответствовать требованиям Compare
   * (https://en.cppreference.com/w/cpp/named_req/Compare).
   * @param other - Другой список.
   * @param comp - объект функции сравнения
   * (т.е. объект, удовлетворяющий требованиям Compare),
   * который возвращает значение true, если первый
   * аргумент меньше (т.е. упорядочен до) второго.
   */
  template <class Compare>
  void merge(list& other, Compare comp) {
    merge(std::move(other), comp);
  }

  /**
   * @brief  The function does nothing if other refers to the same object as
   * *this. Otherwise, merges other into *this. Both lists should be sorted. No
   * elements are copied, and the container other becomes empty after the merge.
   * This operation is stable: for equivalent elements in the two lists, the
   * elements from *this always precede the elements from other, and the order
   * of equivalent elements of *this and other does not change.
   *
   * @tparam Compare - должен соответствовать требованиям Compare
   * (https://en.cppreference.com/w/cpp/named_req/Compare).
   * @param other - Другой список.
   * @param comp - объект функции сравнения
   * (т.е. объект, удовлетворяющий требованиям Compare),
   * который возвращает значение true, если первый
   * аргумент меньше (т.е. упорядочен до) второго.
   */
  template <class Compare>
  void merge(list&& other, Compare comp) {
    if (first_ == other.first_) return;

    list result;

    iterator iter_this = begin();
    iterator iter_other = other.begin();

    while (iter_this != end() && iter_other != other.end()) {
      if (comp(*iter_this, *iter_other)) {
        result.push_back(*iter_this);
        iter_this++;
      } else {
        result.push_back(*iter_other);
        iter_other++;
      }
    }

    while (iter_this != end()) {
      result.push_back(*iter_this);
      iter_this++;
    }
    while (iter_other != other.end()) {
      result.push_back(*iter_other);
      iter_other++;
    }

    other.clear();
    *this = std::move(result);
  }

  /**
   * @briefУдаляет все элементы, которые равны value.
   *
   * @param value - Значение элементов, которые необходимо удалить.
   * return size_type - Количество удаленных элементов.
   */
  size_type remove(const value_type& value) {
    return remove_if([&](const value_type& val) { return val == value; });
  }

  /**
   * @brief Удаляет все элементы, для которых предикат p возвращает значение
   * true.
   *
   * @param p - Унарный предикат, который возвращает значение true, если элемент
   * должен быть удален.
   *
   * return size_type
   */
  template <class UnaryPredicate>
  size_type remove_if(UnaryPredicate p) {
    size_type n = 0;
    _node* cur = first_;
    while (cur != nullptr) {
      if (p(cur->value_)) {
        _node* del = cur;
        cur = cur->next_;
        erase(iterator(del));
        n++;
        continue;
      }
      cur = cur->next_;
    }
    return n;
  }

  /**
   * @brief Изменяет размер контейнера, чтобы он содержал элементы count.
   * Если текущий размер больше, чем count, контейнер уменьшается до его
   * первых элементов count. Если текущий размер меньше, чем count,
   * добавляются дополнительные элементы, вставленные по умолчанию.
   *
   * @param cout - Новый размер контейнера.
   */
  void resize(size_type count) {
    Type val{};
    resize(count, val);
  }

  /**
   * @brief Изменяет размер контейнера, чтобы он содержал элементы count.
   * Если текущий размер больше, чем count, контейнер уменьшается до его
   * первых элементов count. Если текущий размер меньше, чем count, добавляются
   * дополнительные копии value.
   *
   * @param cout - Новый размер контейнера.
   * @param value - Значение, с помощью которого будут инициализированы новые
   * элементы.
   */
  void resize(size_type count, const value_type& value) {
    if (count == size_) return;
    while (count > size_) push_back(value);
    while (count < size_) pop_back();
  }

  /**
   * @brief Изменяет порядок элементов в контейнере на противоположный.
   * Никакие ссылки или итераторы не становятся недействительными.
   */
  void reverse() noexcept {
    iterator left = first_;
    iterator right = last_;

    while (left != right && left.current->prev_ != right.current) {
      Type temp = *left;
      *left = *right;
      *right = temp;
      left++;
      right--;
    }
  }

  /**
   * @brief Возвращает количество элементов в контейнере.
   */
  size_type size() const noexcept { return size_; }

  /**
   * @brief Сортирует элементы и сохраняет порядок расположения эквивалентных
   * элементов. Никакие ссылки или итераторы не становятся недействительными.
   * Элементы сравниваются с помощью оператора <=.
   */
  void sort() {
    sort([](const_reference a, const_reference b) { return a <= b; });
  }

  /**
   * @brief Сортирует элементы и сохраняет порядок расположения эквивалентных
   * элементов. Никакие ссылки или итераторы не становятся недействительными.
   * Элементы сравниваются с помощью компьютера.
   *
   * @tparam Compare - должны соответствовать требованиям Compare
   * (https://en.cppreference.com/w/cpp/named_req/Compare).
   *
   * @param comp - Объект функции сравнения (т.е. объект, удовлетворяющий
   * требованиям Compare), который возвращает значение true, если первый
   * аргумент меньше (т.е. упорядочен до) второго. Сигнатура функции сравнения
   * должна быть эквивалентна следующей:
   * bool cmp(const Type1& a, const Type2& b);
   */
  template <class Compare>
  void sort(Compare comp) {
    if (size_ <= 1) return;

    list a, b;

    iterator it = this->begin();
    for (std::size_t i = 0; i < size_ / 2; i++) {
      a.push_back(*it);
      it++;
    }
    while (it != this->end()) {
      b.push_back(*it);
      it++;
    }

    a.sort();
    b.sort();

    a.merge(b, comp);
    *this = std::move(a);
  }

  /**
   * @brief Переносит все элементы из other в *this. Элементы
   * вставляются перед элементом, на который указывает pos. Контейнер other
   * становится пустым после выполнения операции.
   *
   * @param pos - Элемент, перед которым будет вставлено содержимое.
   * @param other - Другой контейнер для переноса содержимого.
   */
  void splice(const_iterator pos, list& other) {
    insert(pos, other);
    other.clear();
  }

  /**
   * @brief Переносит все элементы из other в *this. Элементы
   * вставляются перед элементом, на который указывает pos. Контейнер other
   * становится пустым после выполнения операции.
   *
   * @param pos - Элемент, перед которым будет вставлено содержимое.
   * @param other - Другой контейнер для переноса содержимого.
   */
  void splice(const_iterator pos, list&& other) { splice(pos, other); }

  /**
   * @brief Переводит элемент, на который он указывает, из other в *this.
   * Элемент вставляется перед элементом, на который указывает post.
   *
   * @param pos - Элемент, перед которым будет вставлено содержимое.
   * @param other - Другой контейнер для переноса содержимого.
   * @param it - Элемент для переноса из other в *this.
   */
  void splice(const_iterator pos, list& other, const_iterator it) {
    insert(pos, *it);
    other.erase(it);
  }

  /**
   * @brief Переводит элемент, на который он указывает, из other в *this.
   * Элемент вставляется перед элементом, на который указывает post.
   *
   * @param pos - Элемент, перед которым будет вставлено содержимое.
   * @param other - Другой контейнер для переноса содержимого.
   * @param it - Элемент для переноса из other в *this.
   */
  void splice(const_iterator pos, list&& other, const_iterator it) {
    splice(pos, other, it);
  }

  /**
   * @brief Переносит элементы в диапазоне [первый, последний) из other в
   * *this. Элементы вставляются перед элементом, на который указывает post.
   *
   * @param pos - Элемент, перед которым будет вставлено содержимое.
   * @param other - Другой контейнер для переноса содержимого.
   * @param first, last - Диапазон элементов для переноса из other в *this.
   */
  void splice(const_iterator pos, list& other, const_iterator first,
              const_iterator last) {
    insert(pos, first.__const_cast__(), last.__const_cast__());
    other.erase(first, last);
  }

  /**
   * @brief Переносит элементы в диапазоне [первый, последний) из other в
   * *this. Элементы вставляются перед элементом, на который указывает post.
   *
   * @param pos - Элемент, перед которым будет вставлено содержимое.
   * @param other - Другой контейнер для переноса содержимого.
   * @param first, last - Диапазон элементов для переноса из other в *this.
   */
  void splice(const_iterator pos, list&& other, const_iterator first,
              const_iterator last) {
    splice(pos, other, first, last);
  }

  /**
   * @brief Заменяет содержимое одного контейнера содержимым другого.
   *
   * @param other - Контейнер для обмена содержимым.
   */
  void swap(list& right) noexcept {
    list temp = std::move(*this);
    *this = std::move(right);
    right = std::move(temp);
  }

  /**
   * @brief Удаляет все последовательные повторяющиеся элементы из контейнера.
   *
   * @return size_type
   */
  size_type unique() {
    return unique(
        [](const value_type& a, const value_type& b) { return a == b; });
  }

  /**
   * @brief Удаляет все последовательные повторяющиеся элементы из контейнера.
   *
   * @tparam BinaryPredicate - должен соответствовать требованиям
   * BinaryPredicate
   * (https://en.cppreference.com/w/cpp/named_req/BinaryPredicate).
   *
   * @param - двоичный предикат, который возвращает значение true, если элементы
   * должны рассматриваться как равные. Сигнатура функции predicate должна быть
   * эквивалентна следующей: bool pred(const Type1 &a, const Type2 &b);
   *
   * @return size_type
   */
  template <class BinaryPredicate>
  size_type unique(BinaryPredicate p) {
    list temp;
    size_type n = 0;

    auto is_exist = [&](const value_type& elem) {
      for (value_type& e : temp)
        if (p(e, elem)) return true;
      return false;
    };

    for (value_type& elem : *this)
      if (!is_exist(elem)) temp.push_back(elem);
    *this = std::move(temp);

    return n;
  }
};

#endif