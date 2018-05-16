enum fan_speed {
  OFF = B00,
  HI = B01,
  MED = B10,
  LO = B11
};

enum flag {
//DIP switch
//1234, N = ON position (away from numbers)  
  NNNN = B0000,
  
  NNNO = B1000,
  NNON = B0100,
  NONN = B0010,
  ONNN = B0001,

  NNOO = B1100,
  NONO = B1010,
  NOON = B0110,
  ONON = B0101,
  OONN = B0011,
  ONNO = B1001,
  
  NOOO = B1110,
  ONOO = B1101,
  OONO = B1011,
  OOON = B0111,

  OOOO = B1111
};

