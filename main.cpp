/**
 * Тумаков М8О-206Б-19
 * Создать класс TransNumber для работы с трансцендентными числами. 
 * Трансцендентное число представлено парой (a, b), где a – действительная часть, 
 * b – трансцендентная часть. Трансцендентная часть представляет собой действительное 
 * число b, умноженное на константу 2. Реализовать арифметические операции 
 * (по аналогии с операциями над комплексными числами в алгебраической форме), 
 * и операции сравнения по значению (a+b*2).  Арифметические операции, а также
 * сравнения (больше, меньше и равно) необходимо реализовать в виде перегрузки операторов.
 * Необходимо реализовать пользовательский литерал для работы с константами типа TransNumber.
 */

#include <iostream>
#include <cmath>

using namespace std;

class TransNumber
{
public:
    // конструктор по умолчанию
    TransNumber() {
        a = 0;
        b = 0;
    }
    //конструктор класса
    TransNumber(const double& new_a, const double& new_b) {
        a = new_a;
        b = new_b * 2;
    }
    //геттер a
    double GetA() const {
        return a;
    }
    //геттер b
    double GetB() const {
        return b;
    }
    //сеттер a
    double& GetA() {
        return a;
    }
    //сеттер b
    double& GetB() {
        return b;
    }
    

private:
    double a;   
    double b;
};

//перегрузка оператора >>
istream& operator>>(istream& stream, TransNumber& num) {
    double one, two;
    stream >> one;
    stream >> two;
    num = {one, two};
    return stream;
}
//перегрузка оператора <<
ostream& operator<<(ostream& stream, const TransNumber& num) {
    stream << "(" << num.GetA() << ", 2 * " << num.GetB()/2 << ")";
    return stream;
}
//перегрузка оператора +
TransNumber operator+(const TransNumber& lhs, const TransNumber& rhs){
    double c=lhs.GetA() + rhs.GetA(), d=lhs.GetB() + rhs.GetB();
    return {c, d/2};
}
//перегрузка оператора +=
void operator+=(TransNumber& lhs,const TransNumber& rhs){
    lhs.GetA() = lhs.GetA() + rhs.GetA();
     lhs.GetB()=lhs.GetB() + rhs.GetB();
}
//перегрузка оператора -
TransNumber operator-(const TransNumber& lhs, const TransNumber& rhs){
    double c=lhs.GetA() - rhs.GetA(), d=lhs.GetB() - rhs.GetB();
    return {c, d/2};
}
//перегрузка оператора -=
void operator-=(TransNumber& lhs, const TransNumber& rhs){
    lhs.GetA() = lhs.GetA() - rhs.GetA();
     lhs.GetB()=lhs.GetB() - rhs.GetB();
}
//перегрузка оператора *
TransNumber operator*(const TransNumber& lhs, const TransNumber& rhs){
    double c, d;
    c = (lhs.GetA() * rhs.GetA()) - (lhs.GetB() * rhs.GetB());
    d = ((lhs.GetA() * rhs.GetB()) + (rhs.GetA() * lhs.GetB()));
    return {c, d/2}; 
}
//перегрузка оператора *=
void operator*=(TransNumber& lhs, const TransNumber& rhs){
    lhs.GetA() = (lhs.GetA() * rhs.GetA()) - (lhs.GetB() * rhs.GetB());
    lhs.GetB() = ((lhs.GetA() * rhs.GetB()) + (rhs.GetA() * lhs.GetB())); 
}
//перегрузка оператора /
TransNumber operator/(const TransNumber& lhs, const TransNumber& rhs){
    double c, d;
    if(rhs.GetA() == 0 && rhs.GetB() == 0){
        cout<<endl;
        cout<<"Error: division on Zero";
        return {0, 0};
    }
    c = (lhs.GetA() * rhs.GetA()) + (lhs.GetB() * rhs.GetB()) / (rhs.GetA()*rhs.GetA() +  rhs.GetB() *  rhs.GetB());
    d = ((rhs.GetA() * lhs.GetB()) - (lhs.GetA() * rhs.GetB())) / (rhs.GetA()*rhs.GetA() +  rhs.GetB() *  rhs.GetB());
    return {c, d/2}; 
}
//перегрузка оператора /=
void operator/=(TransNumber& lhs, const TransNumber& rhs){
    if(rhs.GetA() == 0 && rhs.GetB() == 0){
        cout<<"Error: division on Zero";
    } 
    else {
    lhs.GetA() = (lhs.GetA() * rhs.GetA()) + (lhs.GetB() * rhs.GetB()) / (rhs.GetA()*rhs.GetA() +  rhs.GetB() *  rhs.GetB());
    lhs.GetB() = ((rhs.GetA() * lhs.GetB()) - (lhs.GetA() * rhs.GetB())) / (rhs.GetA()*rhs.GetA() +  rhs.GetB() *  rhs.GetB());
    }
}
//перегрузка оператора >
bool operator>(const TransNumber& lhs, const TransNumber& rhs){
    double c = lhs.GetA() + lhs.GetB();
    double d = rhs.GetA() + rhs.GetB();
    if(c > d){
        return true;
    }
    else {
        return false;
    }
}
//перегрузка оператора <
bool operator<(const TransNumber& lhs, const TransNumber& rhs){
    double c = lhs.GetA() + lhs.GetB();
    double d = rhs.GetA() + rhs.GetB();
    if(c < d){
        return true;
    }
    else {
        return false;
    }
}
//перегрузка оператора ==
bool operator==(const TransNumber& lhs, const TransNumber& rhs){
    double c = lhs.GetA() + lhs.GetB();
    double d = rhs.GetA() + rhs.GetB();
    if(c == d){
        return true;
    }
    else {
        return false;
    }
}
//пользовательский литерал
const TransNumber operator"" _trans(const char *str, size_t size){
    int body=0, k=1;
    double exp=0;
    double arr[2] = {0, 0};
    bool dot=false;
    for(int i = 0; i < size; ++i) {
        if(str[i] == '(' || str[i] == ' '){
            continue;
        }
        else if(str[i] == '.'){
            dot=true;
            continue;
        }
        else if(str[i] == ','){
            dot=false;
            arr[0] = body + exp;
            body = 0;
            exp = 0;
            continue;
        }
        else if(str[i] == ')'){
            arr[1] = body + exp;
            break;
        }
        if(dot){
            exp += (str[i] - '0')*pow(0.1, k);
            ++k; 
        }
        else{
            body = 10*body + str[i] - '0';
        }
    }
    return {arr[0], arr[1]};
}
int main() {
    TransNumber a,b, c = "(17, 34)"_trans;
    cin >> a;
    cout << a << endl;
    cin >> b;
    cout << b<<endl;
    cout<<"Operator + : "<<a << " + "<< b << " = " << a + b << endl;
    cout<<"Operator - : "<<a << " - "<< b << " = " << a - b << endl;
    cout<<"Operator * : "<<a << " *"<< b << " = " << a * b << endl;
    cout<<"Operator / : "<<a << " / "<< b << " = " << a / b << endl;
    if(a > b){
        cout<<" a more then b" << endl;
    }
    else if(a < b){
        cout<<" a less then b" << endl;
    }
    else if(a == b){
        cout<<" a equal b" << endl;
    }
    return 0;
}