#include <iostream>

using namespace std;

bool is_prime(uint32_t a)
{
  if(a == 1 or a == 0)
    return false;
  for(uint32_t i=2; i<=a/2; i++)
    if(a % i == 0) return false;
  return true;
}

uint32_t fast_pow(uint32_t a, uint32_t power, uint32_t order)
{
  if(power == 0)
    return 1;
  if(power % 2 == 1)
    return fast_pow(a, power-1, order) * a % order;
  int b = fast_pow(a, power/2, order);
  return b*b % order;
}

struct GFElement // element of Galious field
{
  uint32_t value;
  uint32_t order; // order of field
  GFElement() : value(0), order(0) {};
  explicit GFElement(uint32_t p_order, uint32_t p_value=0)
  {
    /*if(!is_prime(p_order))
      throw "Constructor error(!!!): this program can't \
          \n  work with not prime-order finite fields";*/
    value = p_value;
    order = p_order;
  }

  void checkOrders(GFElement b) { if(b.order != order) throw "wrong orders"; }

  GFElement &operator=(GFElement b)
  {
    order = b.order;
    value = b.value;
    return *this;
  }

  GFElement &operator+=(GFElement b)
    { return *this = GFElement{ order, (value+b.value) % order }; }
  GFElement &operator-=(GFElement b)
    { return *this = GFElement{ order, (order + value - b.value) % order };; }
  GFElement &operator*=(GFElement b)
    { return *this = GFElement{ order, (value*b.value) % order }; }
  GFElement inverse() { return GFElement{order, fast_pow(value, order-2, order)}; }
  GFElement &operator/=(GFElement b) { return *this *= b.inverse(); }

  GFElement operator+(GFElement b)
    { GFElement result{*this}; return result+=b; }
  GFElement operator*(GFElement b)
    { GFElement result{*this}; return result*=b; }
  
  bool operator==(GFElement b) { checkOrders(b); return value == b.value; }
  bool operator==(int b) { return value == b % order; }
  bool operator!=(GFElement b) { return !(*this == b); }
  bool operator!=(int b) { return !(*this == b); }
};

istream &operator>>(istream &is, GFElement &a)
{
  is >> a.value;
  a.value = a.value % a.order;
  return is;
}

ostream &operator<<(ostream &os, GFElement a)
{
  os << a.value;
  return os;
}

void print_(GFElement **A, GFElement *B, uint32_t COUNT_OF_EQS, uint32_t COUNT_OF_VARS)
{
  for(uint32_t i=0; i<COUNT_OF_EQS; i++) {
    for(uint32_t j=0; j<COUNT_OF_VARS; j++)
      cout << A[i][j] << " ";
    cout << "| " << B[i] << endl;
  }
}

void gauss(GFElement **A, GFElement *B, uint32_t COUNT_OF_EQS, uint32_t COUNT_OF_VARS)
{
  for(uint32_t step=0; step<COUNT_OF_EQS; step++) {
    print_(A, B, COUNT_OF_EQS, COUNT_OF_VARS);
    cout << endl;

    if(A[step][step] == 0) {
      for(uint32_t j=0; j<COUNT_OF_EQS; j++) {
      
      }
    }

    if(A[step][step] != 1) {
      GFElement k = A[step][step].inverse();
      cout << "Multiply " << step << " row by " << k << ":" << endl;
      for(uint32_t i=step; i<COUNT_OF_VARS; i++)
        A[step][i] *= k;
      B[step] *= k;

      print_(A, B, COUNT_OF_EQS, COUNT_OF_VARS);
      cout << endl;
    }

    for(uint32_t i=0; i<COUNT_OF_EQS; i++) {
      if(i == step) continue;
      GFElement k = A[i][step];
      for(uint32_t j=step; j<COUNT_OF_VARS; j++)
        A[i][j] -= A[step][j] * k;
      B[i] -= B[step] * k;
    }
  }
}

int main()
{
  uint32_t ORDER;
  uint32_t COUNT_OF_VARS;
  uint32_t COUNT_OF_EQS;
  cout << "Order of field: ";
  cin >> ORDER;
  if(!is_prime(ORDER)) {
    cout << "My program still unable to work with non-prime order finite fields" << endl;
    return 1;
  }
  cout << "Count of variables: ";
  cin >> COUNT_OF_VARS;
  
  cout << "Count of equations: ";
  cin >> COUNT_OF_EQS;

  GFElement **A = new GFElement*[COUNT_OF_EQS];
  GFElement *B = new GFElement[COUNT_OF_EQS];
  for(uint32_t i=0; i<COUNT_OF_EQS; i++) {
    A[i] = new GFElement[COUNT_OF_VARS];
    for(uint32_t j=0; j<COUNT_OF_VARS; j++)
      A[i][j] = GFElement{ ORDER };
    B[i] = GFElement{ ORDER };
  }

  cout << "Type matrix A[" << COUNT_OF_EQS << "x" << COUNT_OF_VARS << "] of SLE:" << endl;
  for(uint32_t i=0; i<COUNT_OF_EQS; i++)
    for(uint32_t j=0; j<COUNT_OF_VARS; j++)
      cin >> A[i][j];

  cout << "Type vector B[" << COUNT_OF_EQS << "] - vector of right hand side:" << endl;
  for(uint32_t i=0; i<COUNT_OF_EQS; i++)
    cin >> B[i];

  gauss(A, B, COUNT_OF_EQS, COUNT_OF_VARS);
}

