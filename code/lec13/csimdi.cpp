#include <nmmintrin.h> // for SSE4.2
#include <immintrin.h> // for AVX
#include <iostream>
#include <string>

void showVec(const std::string& nm, __m128& vec) {
  std::cout << nm << ": "
            << vec[0] << " " << vec[1] << " " << vec[2] << " " << vec[3] << std::endl;  
}

float simdiFun(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3 ) {
  // create vector of numbers a4 and b4: these store 4 floats each
  union { __m128 a4; float a[4]; };
  union { __m128 b4; float b[4]; };

  // set 8 numbers: 4 in a4 and 4 in b4
  a4 = _mm_set_ps(a0, a1, a2, a3);
  b4 = _mm_set_ps(b0, b1, b2, b3);

  showVec("a4", a4); showVec("b4", b4);

  union { __m128 sum4; float sum[4]; };
  sum4 = _mm_add_ps(a4, b4);

  showVec("sum4", sum4);

  return sum4[0]+sum4[1]+sum4[2]+sum4[3];

}

int
main(void) {
  double v = simdiFun(1.0, 2.0, 3.0, 4.0, 10.0, 11.0, 12.0, 13.0);
  std::cout << "Sum " << v << std::endl;
  return 0;
}

