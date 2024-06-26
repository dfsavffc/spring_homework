# Дерево отрезков для решения задачи о НВП

## Условие
	Дан массив arr целых чисел размером n. Необходимо удалить из него min число элементов так, чтобы оставшиеся составляли возрастающую последовательность.

## Пример: 
	Дан массив 6,2,5,4,2,5,6, если удалить индексы 0, 2, 4, то получится последовательность 2,4,5,6 - которая возрастает и имеет наибольшую длину.

## Динамическое программирование(решение похожее на решение из файла. O(n^2)Динамическое программирование(решение похожее на решение из файла. O(n^2)
	Будем хранить в массиве d значения, d[i] равен длине наибольшей возрастающей подпоследовательности, которая оканчивается в arr[i]
	Для примера массив d будет равен
	a = 6,2,5,4,2,5,6
	d = 1,1,2,2,1,3,4

	На каждой итерации у нас есть выбор, либо мы запускаем новую подпоследовательность, либо присоединяемся к какой-нибудь подпоследовательности слева. То есть d[i] = max(1, max(d[j]) + 1) при условии, что 0 <= j < i и a[j] < a[i]

Так как подпоследовательность необязательно заканчивается в конце, то ответом будет max(d):

```c++
int a[100000];
int d[100000];

int main() {
    for (int i = 0; i < n; i++) {
        d[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                d[i] = max(d[i], d[j] + 1);
            }
        }
    }
    int ans = *max_element(d, d + n);
}
```

> Нетрудно заметить, что такое решение будет работать за O(n^2)

	Будем максимум на префиксе за O(logn), надо просто объединить динамическое программирование и дерево Фенвика(https://neerc.ifmo.ru/wiki/index.php?title=Дерево_Фенвика):
```c++
class fenwick {  
public:  
  explicit fenwick() {  
    f.resize(1000001, 0);  
  }  
  
  int mx(int i) {  
    int res = INT_MIN;  
    for (; i >= 0; i = (i & (i + 1)) - 1) {  
      res = max(res, f[i]);  
    }  
    return res;  
  }  
  
  void set(int i, int v) {  
    for (; i < 100000; i |= i + 1) {  
      f[i] = max(f[i], v);  
    }  
  }  
  
private:  
  vector<int> f;  
};  
  
int main() {  
  ios::sync_with_stdio(false);  
  cin.tie(nullptr);  
  cout.tie(nullptr);  
  int n;  
  cin >> n;  
  vector<int> arr(n);  
  for (int i = 0; i < n; ++i) cin >> arr[i];  
  
  fenwick tree;  
  for (int i = 0; i < n; ++i) {  
    int q = tree.mx(arr[i]);  
    tree.set(arr[i], q + 1);  
  }  
  cout << tree.mx(100000);  
  return 0;  
}
```

Если элемент в оригинальном массиве <= 10^6, то можно решать без проблем, иначе нужно будет сжать значения.
Что значит сжать значение. Допустим нам дан массив длиной 10^6, но при этом сами числа в массиве могут быть от -10^9 до 10^9. То есть в целом значение имеет 10^18 вариантов значений, что уже не подходит для дерева Фенвика. Поэтому значения нужно сжать. Как это можно сделать. Так как количество элементов у нас ограничено, то мы можем определить биекцию между реальным элементов и его индексом. Причем два одинаковых элемента должны возвращать один и тот индекс. Таким образом даже в худшем случае, когда все числа уникальны, то получившиеся индексы не превысят 10^6, что подходит для использования в Дереве Фенвика.

	Еще раз, теперь наш индекс в дереве Фенвика - это значение. Мы можем быстро найти максимум в отрезке от 0 до i. Более наглядно (d - это обычное динамическое программирование):
	a = 6,2,5,4,2,5,6
	d = 1,1,2,2,1,3,4
	f = 0,0,1,0,2,3,4,0,0....

Мы пробегаемся по всем элементам массива и делаем две операции:

	Находим максимальное значение, которое было до этого значения
	Меняем текущее значение на полученное максимальное + 1
	
![](https://habrastorage.org/getpro/habr/post_images/4e1/a12/ba4/4e1a12ba49be37da4bc571c0cbfc6641.jpg)