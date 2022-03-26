#include <iostream>
#include "omp.h"

using namespace std;

//
// Check to see if a number is prime.
//
bool is_prime(long long x) {
  if (x<2) return false;
  long long t=2;
  while (t*t <= x) {
    if (x%t == 0) {
      return false;
    }
    t++;
  }
  return true;
}

// Count the number of primes between a and b, inclusive

long long count_primes(long long a, long long b) {
  long long sum=0;
  //for loop executed in parallel with a redduction clause for "sum"
  #pragma omp parallel for reduction(+: sum)
  for (long long i = a;i<=b;i++) {
    if (is_prime(i)) sum++;
  }
  return sum;
}

int main() {
  long long a;
  long long b;

  cout << "Enter two large integers " << endl;
  cin >> a;
  cin >> b;

  cout << a << " Start " << endl;
  cout << b << " End " << endl;
  
  long long total = count_primes(a,b);

  cout << "Number of prime numbers between " << a << " and " << b << " = " << total << endl;
}