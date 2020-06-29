#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
using namespace std;

double Foo(double x){ // функция активации
    x = -x;
    return (1/(1 + pow(2.7, x)));
}


class Neuron {
public:
    double output;
    int numb; // количество входов
    double *w; // весовой коэффициент
    double *data;
    double sum = 0.0;
    void changeWeight();
    double outputValue(double (*func)(double));
    void Set();
    Neuron(int Size, double (*func)(double)){ // конструктор
        this->numb = Size;
        this->data = new double[numb]; // значения
        this->w = new double[numb]; // весовые коэфф
    };

    Neuron(const Neuron &other){    // конструктор копирования
        this->numb = other.numb;
        this->data = new double[other.numb];
        this->w = new double[other.numb];
    };

    Neuron & operator = (const Neuron &other){ // перегрузка оператора
        this->numb = other.numb;
        this->data = new double[other.numb];
        this->w = new double[other.numb];
        return *this;
    }

    ~Neuron(){ // деструктор
        delete[] data;
        delete[] w;
        //cout << "Destruction" << endl;
    };
};

void Neuron::Set(){
    cout << "Enter main values" << endl;
    for (int i = 0; i < numb; i++){
        cin >> data[i];
    }
    cout << "Enter w values" << endl;
    for (int i = 0; i < numb; i++){
        cin >> w[i];
    }
    cout << "Finished" << endl;
}

double Neuron::outputValue(double (*func)(double)){     // функция для вывода
    double sumf = 0.0;
    for (unsigned int i = 0; i < numb; i++){
        sumf += data[i] * w[i];
    }
    output = func(sumf);
    return output;
}

void Neuron::changeWeight(){    // функция для изменения весовых коэф
    cout << "Enter w values" << endl;
    for (int i = 0; i < numb; i++){
        cin >> w[i];
    }
    cout << "Finished" << endl;
}


int main()
{
    int inputNumb;
    cout << "Enter amount of input: " << endl; //const
    cin >> inputNumb;
    Neuron testingNeuron(inputNumb, Foo);                   //проверка работы функций
    testingNeuron.Set();
    cout << testingNeuron.outputValue(Foo) << endl;
    Neuron a(3, Foo);                                   // проверка копирования и перегрузки
    a = testingNeuron;
    cout << a.numb << endl;
    Neuron n(5, Foo);
    a = n = testingNeuron;
    cout << n.numb << endl;
    n.changeWeight();
    a.Set();
    cout << a.outputValue(Foo) << endl;
    return 0;
}
