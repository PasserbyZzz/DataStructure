# STL（Standard Template Library）

## 顺序容器

### 1. `vector`
动态数组，支持随机访问和动态扩展。

#### 常用函数：
| 函数                         | 描述                                                                 |
|------------------------------|----------------------------------------------------------------------|
| `push_back(value)`           | 在末尾添加元素。                                                     |
| `pop_back()`                 | 移除末尾元素。                                                       |
| `size()`                     | 返回当前元素个数。                                                   |
| `capacity()`                 | 返回当前容器的容量（未使用的内存空间）。                              |
| `resize(n, value)`           | 改变容器大小，必要时用 `value` 填充新空间。                          |
| `shrink_to_fit()`            | 减小容量，使其等于当前大小。                                          |
| `at(index)`                  | 返回指定位置的元素（带边界检查）。                                    |
| `operator[]`                 | 返回指定位置的元素（无边界检查）。                                    |
| `insert(vec.begin()+i, value)`    | 在指定位置插入元素。                                                  |
| `erase(vec.begin()+i)`            | 移除指定位置的元素。                                                 |
| `clear()`                    | 清空容器。                                                           |
| `begin()` / `end()`          | 返回首元素和尾后元素的迭代器。                                        |
| `rbegin()` / `rend()`        | 返回逆序迭代器。                                                     |
| `emplace_back(args...)`      | 在末尾直接构造元素，效率比 `push_back` 高。                           |

---

### 2. `deque`
双端队列，支持在两端快速插入和删除。

#### 常用函数：
| 函数                         | 描述                                                                 |
|------------------------------|----------------------------------------------------------------------|
| `push_back(value)`           | 在末尾添加元素。                                                     |
| `push_front(value)`          | 在头部添加元素。                                                     |
| `pop_back()`                 | 移除末尾元素。                                                       |
| `pop_front()`                | 移除头部元素。                                                       |
| `size()`                     | 返回当前元素个数。                                                   |
| `at(index)`                  | 返回指定位置的元素（带边界检查）。                                    |
| `operator[]`                 | 返回指定位置的元素（无边界检查）。                                    |
| `insert(position, value)`    | 在指定位置插入元素。                                                  |
| `erase(position)`            | 移除指定位置的元素。                                                 |
| `clear()`                    | 清空容器。                                                           |
| `begin()` / `end()`          | 返回首元素和尾后元素的迭代器。                                        |
| `rbegin()` / `rend()`        | 返回逆序迭代器。                                                     |
| `emplace_front(args...)`     | 在头部直接构造元素。                                                 |
| `emplace_back(args...)`      | 在末尾直接构造元素。                                                 |

---

### 3. `list`
双向链表，支持在任意位置高效插入和删除。

#### 常用函数：
| 函数                         | 描述                                                                 |
|------------------------------|----------------------------------------------------------------------|
| `push_back(value)`           | 在末尾添加元素。                                                     |
| `push_front(value)`          | 在头部添加元素。                                                     |
| `pop_back()`                 | 移除末尾元素。                                                       |
| `pop_front()`                | 移除头部元素。                                                       |
| `size()`                     | 返回当前元素个数。                                                   |
| `insert(position, value)`    | 在指定位置插入元素。                                                  |
| `erase(position)`            | 移除指定位置的元素。                                                 |
| `remove(value)`              | 移除所有值等于 `value` 的元素。                                       |
| `clear()`                    | 清空容器。                                                           |
| `begin()` / `end()`          | 返回首元素和尾后元素的迭代器。                                        |
| `rbegin()` / `rend()`        | 返回逆序迭代器。                                                     |
| `sort()`                     | 对链表元素排序。                                                     |
| `merge(other_list)`          | 将另一个链表合并到当前链表（需先排序）。                              |
| `splice(position, other_list)` | 将另一个链表的部分或全部元素插入当前链表的指定位置。                  |

---

### 4. `forward_list`
单向链表，只支持单向遍历，较轻量。

#### 常用函数：
| 函数                         | 描述                                                                 |
|------------------------------|----------------------------------------------------------------------|
| `push_front(value)`          | 在头部添加元素。                                                     |
| `pop_front()`                | 移除头部元素。                                                       |
| `insert_after(position, value)` | 在指定迭代器之后插入元素。                                           |
| `erase_after(position)`      | 移除指定迭代器之后的元素。                                            |
| `remove(value)`              | 移除所有值等于 `value` 的元素。                                       |
| `clear()`                    | 清空容器。                                                           |
| `begin()` / `end()`          | 返回首元素和尾后元素的迭代器。                                        |
| `sort()`                     | 对链表元素排序。                                                     |
| `merge(other_list)`          | 合并另一个链表。                                                     |
| `splice_after(position, other_list)` | 在指定位置之后插入另一个链表的内容。                          |

---

### 5. `array`
定长数组，大小在编译时固定。

#### 常用函数：
| 函数                         | 描述                                                                 |
|------------------------------|----------------------------------------------------------------------|
| `at(index)`                  | 返回指定位置的元素（带边界检查）。                                    |
| `operator[]`                 | 返回指定位置的元素（无边界检查）。                                    |
| `front()`                    | 返回第一个元素。                                                     |
| `back()`                     | 返回最后一个元素。                                                   |
| `data()`                     | 返回指向数组的指针。                                                 |
| `size()`                     | 返回数组大小。                                                       |
| `fill(value)`                | 用指定值填充整个数组。                                                |
| `swap(other_array)`          | 交换两个数组的内容。                                                 |

---

### `string` 

C++ 中的 `string` 类提供了丰富的成员函数，方便操作和管理字符串。以下是 `string` 类的常用函数分类及其功能说明。

---

#### 常用函数

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `string()`                      | 构造一个空字符串。                                                   |
| `string(const char* s)`         | 从 C 风格字符串构造一个字符串对象。                                    |
| `string(const string& str)`     | 拷贝构造函数，从另一个字符串对象构造。                                 |
| `string(size_t n, char c)`      | 构造一个包含 `n` 个字符 `c` 的字符串。                                |
| `operator=`                     | 赋值运算符，用另一个字符串或字符数组赋值。                            |
| `assign(str)`                   | 将字符串对象或子字符串赋值给当前字符串。                              |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `size()` 或 `length()`          | 返回字符串的长度（字符数）。                                           |
| `capacity()`                    | 返回字符串的容量（当前分配的存储空间大小）。                          |
| `resize(n)`                     | 修改字符串大小为 `n`，若增大则填充空字符，若减小则截断。               |
| `empty()`                       | 检查字符串是否为空，若为空则返回 `true`。                              |
| `shrink_to_fit()`               | 减小容量以适应实际内容。                                              |
| `max_size()`                    | 返回字符串所能容纳的最大字符数。                                       |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `operator[]`                    | 返回指定位置的字符（无边界检查）。                                     |
| `at(index)`                     | 返回指定位置的字符（带边界检查）。                                     |
| `front()`                       | 返回第一个字符。                                                      |
| `back()`                        | 返回最后一个字符。                                                    |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `append(str)` 或 `+=`           | 在字符串末尾追加内容。                                                |
| `insert(pos, str)`              | 在指定位置插入字符串。                                                |
| `erase(pos, n)`                 | 从指定位置删除 `n` 个字符。                                            |
| `replace(pos, n, str)`          | 用字符串替换从指定位置开始的 `n` 个字符。                              |
| `clear()`                       | 清空字符串内容。                                                      |
| `push_back(c)`                  | 在字符串末尾追加单个字符。                                             |
| `pop_back()`                    | 移除字符串末尾的一个字符。                                             |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `find(str, pos)`                | 从指定位置开始查找子字符串，返回第一个匹配的位置，找不到返回 `string::npos`。 |
| `rfind(str, pos)`               | 从指定位置开始反向查找子字符串。                                       |
| `find_first_of(chars, pos)`     | 查找字符串中第一个匹配字符的位置。                                     |
| `find_last_of(chars, pos)`      | 查找字符串中最后一个匹配字符的位置。                                   |
| `find_first_not_of(chars, pos)` | 查找字符串中第一个不匹配字符的位置。                                   |
| `find_last_not_of(chars, pos)`  | 查找字符串中最后一个不匹配字符的位置。                                 |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `substr(pos, n)`                | 返回从指定位置开始的子字符串（长度为 `n`）。                           |
| `compare(str)`                  | 比较两个字符串，返回 `0`（相等），正值（大于），负值（小于）。           |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `getline(cin, str)`             | 从输入流中读取一行字符串。                                             |
| `cout << str`                   | 输出字符串到标准输出。                                                |

---

| 函数                            | 描述                                                                 |
|---------------------------------|----------------------------------------------------------------------|
| `swap(str)`                     | 交换两个字符串的内容。                                                |
| `c_str()`                       | 返回 C 风格字符串的指针。                                              |
| `data()`                        | 返回字符串的数据指针（与 `c_str` 类似）。                              |

---

## 容器适配器

### 1. `queue`（队列）
`queue` 是先进先出（FIFO）的数据结构，只允许从尾部插入元素，从头部移除元素。

#### 常用函数：
| 函数                     | 描述                                                                 |
|--------------------------|----------------------------------------------------------------------|
| `push(value)`            | 将元素插入队列尾部。                                                  |
| `pop()`                  | 移除队列头部元素。                                                   |
| `front()`                | 返回队列头部元素。                                                   |
| `back()`                 | 返回队列尾部元素。                                                   |
| `size()`                 | 返回队列中元素的个数。                                               |
| `empty()`                | 检查队列是否为空，若为空则返回 `true`。  

### 2. `stack`（栈）

`stack` 是后进先出（LIFO）的数据结构，只允许在栈顶插入和移除元素。

---

#### 常用函数

| 函数                     | 描述                                                                 |
|--------------------------|----------------------------------------------------------------------|
| `push(value)`            | 将元素压入栈顶。                                                     |
| `pop()`                  | 移除栈顶元素。                                                      |
| `top()`                  | 返回栈顶元素。                                                      |
| `size()`                 | 返回栈中元素的个数。                                                |
| `empty()`                | 检查栈是否为空，若为空则返回 `true`。                               |

---

### 3. `priority_queue`（优先队列）

`priority_queue` 是一种基于堆（heap）的容器适配器，支持快速访问最大或最小优先级的元素。默认情况下，它是一个**大顶堆**（最大元素优先），可以通过自定义比较函数实现**小顶堆**。

---

#### 常用函数

| 函数                     | 描述                                                                 |
|--------------------------|----------------------------------------------------------------------|
| `push(value)`            | 将元素插入优先队列。                                                  |
| `pop()`                  | 移除优先队列中优先级最高的元素。                                      |
| `top()`                  | 返回优先队列中优先级最高的元素。                                      |
| `size()`                 | 返回优先队列中的元素个数。                                            |
| `empty()`                | 检查优先队列是否为空，若为空则返回 `true`。                          |

---

#### 构造函数

- 大顶堆
  ```cpp
    priority_queue<int> pq; // 大顶堆
  ```
- 小顶堆
  ```cpp
    priority_queue<int, vector<int>, greater<int>> pq; // 小顶堆
  ```

#### 运算符重载

##### 规则

- 大顶堆：operator< 返回 true 时，较大的元素优先。
- 小顶堆：operator> 返回 true 时，较小的元素优先。

##### 示例

- 大顶堆
    ```cpp
        bool operator<(const Node& other) const {
            return priority < other.priority; // 优先级大的元素优先
        }
    ```

```cpp
