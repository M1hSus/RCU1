byte key[] = {3,1,5,2,6,4,2,3,1,6,5,4,1,2,3,5,6,4,2,1,5,3,6,4,1,2,5,6,3,4,2,1};
// The encryption key must consist of digits from 1 to 6 

void encrypt(byte data[]) {
  for(byte i = 0; i <= 32; i++) data[i] *= key[i];
}

void decrypt(byte data[]) {
  for(byte i = 0; i <= 32; i++) data[i] /= key[i];
}