#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
/**Объявления типа данных - график*/
typedef vector< pair<int, int> > Graph;

/**Предельная мощность графиков A и B.*/
const int graphCardinality = 100;

/**Прототипы используемых функций.*/
Graph graphIntersection(Graph, Graph);
Graph graphDifference(Graph, Graph);
Graph graphSymDiff(Graph, Graph);
Graph graphUnion(Graph, Graph);
Graph graphInversion(Graph);
Graph graphComposition(Graph, Graph);
template<class T>
bool contains(vector<T>, T);
void fillUniversum();

/** Функция нахождения пересечения двух графиков.
 *  Аргументы функции - два графика: A и B.
 *  Функция возвращает график C.
 */
Graph graphIntersection(Graph A, Graph B)
{
    Graph C; ///выделение памяти под пересечение

    if (A.empty() || B.empty()) ///если одно из графиков пустой
        return C;               ///возвращаем пустой график

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого графика
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго графика
                {
                    if (A.at(i) == B.at(j)) ///если элементы равны
                        C.push_back(A.at(i)); ///добавляем их значение в пересечение
                }
        }

    sort(C.begin(), C.end()); ///сортировка полученного графика
    return C;
}

/** Функция нахождения разности двух графиков.
 *  Аргументы функции - два графика: A и B.
 *  Функция возвращает график R.
 */
Graph graphDifference(Graph A, Graph B)
{
    Graph R; ///выделение памяти под разность

    if (A.empty()) ///если первое график пустой
        return R;  ///возвращаем пустой график
    if (B.empty()) ///если второе график пустой
        return A;  ///возвращаем первое график

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого графика
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго графика
                {
                    if (A.at(i) != B.at(j)) ///если элементы не равны
                        {
                            if (!contains(R, A[i])) ///проверяем, содержится ли элемент a в разности
                                if (!contains(B, A.at(i))) ///если нет, то проверяем, содержится ли элемент b в разности
                                    R.push_back(A.at(i)); ///если нет, то добавляем его в разность
                        }
                }
        }

    sort(R.begin(), R.end()); ///сортировка полученного графика
    return R;
}

/** Функция нахождения симметрической разности двух графиков.
 *  Аргументы функции - два графика: A и B.
 *  Функция возвращает график S.
 */
Graph graphSymDiff(Graph A, Graph B)
{
    Graph S; ///выделение памяти под объединение

    if (A.empty()) ///если первое график пустой
        return B;  ///возвращаем второе график
    if (B.empty()) ///если второе график пустой
        return A;  ///возвращаем первое график

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого графика
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго графика
                {
                    if (A.at(i) != B.at(j)) ///если элементы не равны
                        {
                            if (!contains(S, A.at(i)) && !contains(B, A.at(i))) ///то проверяем, содержится ли элемент a в симметрической разности и в множестве B
                                S.push_back(A.at(i)); ///если нет, то добавляем его
                            if (!contains(S, B.at(i)) && !contains(A, B.at(i))) ///проверяем, содержится ли элемент b в симметрической разности и в множестве A
                                S.push_back(B.at(i)); ///если нет, то добавляем его
                        }
                }
        }

    sort(S.begin(), S.end()); ///сортировка полученного графика
    return S;
}

/** Функция нахождения объединения двух графиков.
 *  Аргументы функции - два графика: A и B.
 *  Функция возвращает график D.
 */
Graph graphUnion(Graph A, Graph B)
{
    Graph D; ///выделение памяти под объединение

    if (A.empty() && B.empty()) ///если оба графика пустые
        return D; ///возвращаем пустой график
    if (A.empty()) ///если график A - пустой
        return B;  ///возвращаем график B
    if (B.empty()) ///если график B - пустой
        return A;  ///возвращаем график A

    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого графика
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго графика
                {
                    if (A.at(i) != B.at(j)) ///если элементы не равны
                        {
                            if (!contains(D, A.at(i))) ///то проверяем, содержится ли элемент a в объединении
                                D.push_back(A.at(i));  ///если нет, то добавляем его в объединение
                            if (!contains(D, B.at(j))) ///проверяем, содержится ли элемент b в объединении
                                D.push_back(B.at(j));  ///если нет, то добавляем его в объединение
                        }
                    else if (!contains(D, A.at(i)))
                        D.push_back(A.at(i));
                }
        }

    sort(D.begin(), D.end()); ///сортировка полученного графика
    return D;
}

/** Функция нахождения инверсии графика.
 *  Аргумент функции - график А.
 *  Функция возвращает график I.
 */
Graph graphInversion(Graph A)
{
    Graph I(A.size()); ///создание графика с размером, равным размеру исходного графика
    pair<int, int> temp; ///вспомогательная переменная для хранения инверсии пары чисел
    for (size_t i = 0; i < A.size(); i++) ///обход по всем элементам первого графика
        {
            ///создание и добавление в график I инверсии i-ой пары графика A
            temp.first = A[i].second;
            temp.second = A[i].first;
            I[i] = temp;
        }
    return I;
}

/** Функция нахождения композиции двух графиков.
 *  Аргументы функции - два графика: A и B.
 *  Функция возвращает график C.
 */
Graph graphComposition(Graph A, Graph B)
{
    Graph C; ///обявление графика - композиции
    pair<int, int> temp; ///вспомогательная переменная для хранения пары чисел
    for (size_t i = 0; i < A.size(); i ++) ///обход по всем элементам первого графика
        {
            for (size_t j = 0; j < B.size(); j++) ///обход по всем элементам второго графика
                {
                    if (A[i].second == B[j].first) ///если вторая компонента i-й пары равна первой компоненте j-й пары
                        {
                            ///создание и добавление в композицию пары, состоящей из первой компоненты i-ой пары и второй компоненты j-ой пары
                            temp.first = A[i].first;
                            temp.second = B[j].second;
                            if (!contains(C, temp))
                                C.push_back(temp);
                        }
                }
        }
    return C;
}

/** Шаблон функции, которая определяет, содержится ли элемент в множестве.
 *  Аргументы функции - множество элементов dset и элемент element.
 *  Функция возвращает true, если элемент содержится в множестве,
 *  и false, если не содержится.
 */
template<class T>
bool contains(vector<T> dset, T element)
{
    for (size_t i = 0; i < dset.size(); i++) ///обход по всем элементам графика dgraph
        if (dset.at(i) == element)
            return true;
    return false;
}

///Функция корректного считывания с клавиатуры числового значения
void readInteger(int& number)
{
    cin >> number;
    while (!cin.good())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Введено некорректное значение. Повторите ввод: ";
            cin >> number;
        }
}

///Функция корректного считывания с клавиатуры пары чисел
void readPair(pair<int,int>& nPair)
{
    int firstComponent;
    int secondComponent;
    readInteger(firstComponent);
    readInteger(secondComponent);
    nPair.first = firstComponent;
    nPair.second = secondComponent;
}

///Функция вывода на экран всех элементов графика
void printGraph(Graph& dgraph, string title)
{
    if (system("CLS")) ///очистка консоли
        system("clear");
    cout << "-----------------------------------------------------------------" << endl;

    if (dgraph.empty()) ///если графика пустой
        cout << title << " - пустой график!";
    else
        {
            cout << title <<": ";
            for (pair<int,int> element: dgraph) ///последовательный вывод всех всех элементов графика
                cout << "<" << element.first << "," << element.second << "> ";
        }
    cout << endl;
    cout << "-----------------------------------------------------------------" << endl;
}

///Функция освобождения памяти из-под графика
void deleteVector(Graph& vec)
{
    vec.clear();
    vec.shrink_to_fit();
}

int main()
{
    setlocale(0,"");
    Graph A; ///выделение памяти под первый график
    Graph B; ///выделение памяти под второй график
    int numA; ///мощность первого графика
    int numB; ///мощность второго графика
    pair<int,int> temp; ///вспомогательная переменная

    ///ввод мощности первого графика с проверкой соответствия значения мощности условию
    do
        {
            cout << "Введите мощность первого графика: ";
            readInteger(numA);
            if (numA < 0)
                cout<<"Мощность графика не может быть отрицательной!"<<endl;
            if (numA > graphCardinality)
                cout<<"Мощность графика превышает максимально допустимую("<<graphCardinality<<")!"<<endl;
        }
    while (numA < 0 || numA > graphCardinality);

    ///ввод мощности второго графика с проверкой соответствия значения мощности условию
    do
        {
            cout << "Введите мощность второго графика: ";
            readInteger(numB); ///ввод мощности второго графика
            if (numB < 0)
                cout<<"Мощность графика не может быть отрицательной!"<<endl;
            if (numB > graphCardinality)
                cout<<"Мощность графика превышает максимально допустимую("<<graphCardinality<<")!"<<endl;
        }
    while (numB < 0 || numB > graphCardinality);

    int choice; ///переменная, отвечающая за выбор пользователя

    if(numA != 0) ///если мощность графика A не равна нулю
        {
            cout << "Введите элементы графика A:" << endl;
            for (int i = 0; i < numA; i++) ///то для каждого элемента
                {
                    ///ввод значения с проверкой на повторное вхождение элементов в график
                    bool exists;
                    do
                        {
                            cout << "Элемент №" << i+1 << " - ";
                            readPair(temp);
                            if (exists = contains(A, temp))
                                cout<<"Элемент уже содержится в графике! Введите другое значение."<<endl;
                        }
                    while (exists);
                    A.push_back(temp); ///добавление значения в график
                }
        }
    else ///иначе, выводим информацию о том, что A - пустой график
        cout << "A - пустой график." << endl << endl;

    if(numB != 0) ///если мощность графика B не равна нулю
        {
            cout << "Введите элементы графика B:" << endl;
            for (int i = 0; i < numB; i++) ///то для каждого элемента
                {
                    ///ввод значения с проверкой на повторное вхождение элементов в график
                    bool exists;
                    do
                        {
                            cout << "Элемент №" << i+1 << " - ";
                            readPair(temp);
                            if (exists = contains(B, temp))
                                cout<<"Элемент уже содержится в множестве! Введите другое значение."<<endl;
                        }
                    while (exists);
                    B.push_back(temp); ///добавление значения в график
                }
            cout << endl;
        }
    else ///иначе, выводим информацию о том, что B - пустой график
        cout << "B - пустой график." << endl << endl;


    while(true) ///бесконечный цикл вывода меню
        {
            cout << "Выберите операцию:"                       << endl
                 << "1)Пересечение графиков A и B"             << endl
                 << "2)Объединение графиков A и B"             << endl
                 << "3)Разность графиков A и B"                << endl
                 << "4)Разность графиков B и A"                << endl
                 << "5)Симметрическая разность графиков A и B" << endl
                 << "6)Инверсия графика A"                     << endl
                 << "7)Инверсия графика B"                     << endl
                 << "8)Композиция графиков A и B"              << endl
                 << "9)Композиция графиков B и A"              << endl
                 << "0)Выход из программы"                     << endl
                 << "Ваш выбор: ";
            readInteger(choice); ///ввод номера операции
            if (choice < 0 || choice > 9)
                {
                    if (system("CLS")) ///очистка консоли
                        system("clear");
                    cout<<"Введите число от 0 до 9..."<<endl;
                }

            switch (choice) ///Выполнение операции в зависимости от выбора пользователя
                {
                case 1: ///если было выбрано пересечение
                {
                    ///вызов функции нахождения пересечения графиков
                    Graph intersect = graphIntersection(A, B);
                    ///вывод пересечения графиков на экран
                    printGraph(intersect, "Пересечение");
                    ///высвобождение памяти из-под пересечения
                    deleteVector(intersect);
                    break;
                }
                case 2: ///если было выбрано объединение
                {
                    ///вызов функции нахождения объединения графиков и вывод его на экран
                    Graph un = graphUnion(A, B);
                    ///вывод объединения графиков на экран
                    printGraph(un, "Объединение");
                    ///высвобождение памяти из-под объединения
                    deleteVector(un);
                    break;
                }
                case 3: ///если была выбрана разность A и B
                {
                    ///вызов функции нахождения разности графиков A и B
                    Graph differenceAB = graphDifference(A, B);
                    ///вывод разности графиков А и В на экран
                    printGraph(differenceAB, "Разность A и B");
                    ///высвобождение памяти из-под разности
                    deleteVector(differenceAB);
                    break;
                }
                case 4: ///если была выбрана разность B и A
                {
                    ///вызов функции нахождения разности графиков B и A
                    Graph differenceBA = graphDifference(B, A);
                    ///вывод разности графиков В и А на экран
                    printGraph(differenceBA, "Разность B и A");
                    ///высвобождение памяти из-под разности
                    deleteVector(differenceBA);
                    break;
                }
                case 5: ///если была выбрана симметрическая разность A и B
                {
                    ///вызов функции нахождения симметрической разности графиков A и B
                    Graph symdiff = graphSymDiff(A, B);
                    ///вывод симметрической разности графиков А и В на экран
                    printGraph(symdiff, "Симметрическая разность");
                    ///высвобождение памяти из-под симметрической разности
                    deleteVector(symdiff);
                    break;
                }
                case 6: ///если была выбрана инверсия графика A
                {
                    ///вызов функции нахождения инверсии графика A и вывод его на экран
                    Graph inversion = graphInversion(A);
                    ///вывод инверсии графика А на экран
                    printGraph(inversion, "Инверсия графика A");
                    ///высвобождение памяти из-под инверсии
                    deleteVector(inversion);
                    break;
                }
                case 7: ///если была выбрана инверсия графика B
                {
                    ///вызов функции нахождения инверсии графика B и вывод его на экран
                    Graph inversion = graphInversion(B);
                    ///вывод инверсии графика B на экран
                    printGraph(inversion, "Инверсия графика B");
                    ///высвобождение памяти из-под инверсии
                    deleteVector(inversion);
                    break;
                }
                case 8: ///если была выбрана композиция графиков A и B
                {
                    ///вызов функции нахождения композиции графиков A и B и вывод её на экран
                    Graph composition = graphComposition(A, B);
                    ///вывод композиции графиков А и В на экран
                    printGraph(composition, "Композиция графиков A и B");
                    ///высвобождение памяти из-под композиции
                    deleteVector(composition);
                    break;
                }
                case 9: ///если была выбрана композиция графиков B и А
                {
                    ///вызов функции нахождения композиции графиков B и А и вывод её на экран
                    Graph composition = graphComposition(B, A);
                    ///вывод композиции графиков B и А на экран
                    printGraph(composition, "Композиция графиков B и А");
                    ///высвобождение памяти из-под композиции
                    deleteVector(composition);
                    break;
                }
                case 0: ///если был выбран выход из программы
                    return 0; ///закрываем программу
                }
        }
    return 0;
}
