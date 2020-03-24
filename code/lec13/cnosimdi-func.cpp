
float nosimdiFun(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3 ) {
  float sum4[4];
  sum4[0] = a0+b0;
  sum4[1] = a1+b1;
  sum4[2] = a2+b2;
  sum4[3] = a3+b3;
  return sum4[0]+sum4[1]+sum4[2]+sum4[3];
}
