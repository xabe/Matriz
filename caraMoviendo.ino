//Código para controlar una matrix sin multiplexación
int col[8] = {2,3,4,5,6,7,8,9}; //Positivos
int row[8] = {10,11,12,13,14,15,16,17}; //Negativos

int displayContent [8][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
int blank [8][8] =          {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
int smile_1 [8][8] =        {{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{1,0,1,0,0,1,0,1},{1,0,0,0,0,0,0,1},{1,0,1,0,0,1,0,1},{1,0,0,1,1,0,0,1},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0}};
int smile_2 [8][8] =        {{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{1,0,1,0,0,1,0,1},{1,0,0,0,0,0,0,1},{1,0,1,1,1,1,0,1},{1,0,0,0,0,0,0,1},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0}};
int smile_3 [8][8] =        {{0,0,1,1,1,1,0,0},{0,1,0,0,0,0,1,0},{1,0,1,0,0,1,0,1},{1,0,0,0,0,0,0,1},{1,0,0,1,1,0,0,1},{1,0,1,0,0,1,0,1},{0,1,0,0,0,0,1,0},{0,0,1,1,1,1,0,0}};

int pauseDelay = 500;

void setup(){  
 for(int i = 0; i < 8; i++){
   pinMode(col[i],OUTPUT);
   pinMode(row[i],OUTPUT);
 } 
 
 //Chequeamos que funciona todos los led's
  checkMatrix();
  
 //Apagamos la matrix
 for(int i = 0; i < 8; i++){
   digitalWrite(col[i],LOW);
   digitalWrite(row[i],LOW);
 }
}

void checkMatrix(){
 for (int x = 0; x < 8; x++) {//Fila
    for(int z = 0; z < 8; z++){//Apagamos todas las filas menos la actual
      digitalWrite(row[z],HIGH);
      if(z==x)
      {
        digitalWrite(row[z],LOW);//Encedemos la fila que estamos actualmente
      }
    }
    for (int y = 0; y < 8; y++) {//columnas
      digitalWrite(col[0],LOW); //Apagamos todas las columnas menos la actual
      digitalWrite(col[1],LOW);
      digitalWrite(col[2],LOW);
      digitalWrite(col[3],LOW);
      digitalWrite(col[4],LOW);
      digitalWrite(col[5],LOW);
      digitalWrite(col[6],LOW);
      digitalWrite(col[7],LOW);
      digitalWrite(col[y],HIGH);//Encedemos la columna que estamos actualmente
      delay(40);
    }
    delay(200);
 }

}

void copyArray(int original[8][8]){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      displayContent[i][j] = original[i][j];
    }
  }
}

int * getColumn(int original[8][8], int column){
  int result [8] = {0,0,0,0,0,0,0,0};
  for(int i = 0; i < 8; i++){
      result[i] = original[i][column];
  }
  return result;
}

int * getRow(int original[8][8], int row){
  int result [8] = {0,0,0,0,0,0,0,0};
  for(int i = 0; i < 8; i++){
      result[i] = original[row][i];
  }
  return result;
}

// Desplazamiento de la imagen hacia la izquierda

void shiftRegisterLeft(int original[8]){
  for(int i = 0; i < 8; i++){
    for(int j = 1; j < 8; j++){
      displayContent[i][j-1] = displayContent[i][j];
    }
  }  
  for(int i = 0; i < 8; i++){
    displayContent[i][7] = original[i];
  }
}

void displayScrolLeft(){
  copyArray(blank);
  for(int i = 0; i < 8; i++){
    shiftRegisterLeft(getColumn(smile_1,i));
    displayScreen();
  }
  for(int i = 0; i < 8; i++){
    shiftRegisterLeft(getColumn(smile_2,i));
    displayScreen();
  }
  for(int i = 0; i < 8; i++){
    shiftRegisterLeft(getColumn(smile_3,i));
    displayScreen();
  }
}

// Desplazamiento de la imagen hacia la derecha

void shiftRegisterRigth(int original[8]){
  for(int i = 0; i < 8; i++){
    for(int j = 6; j >=0; j--){
      displayContent[i][j+1] = displayContent[i][j];
    }
  }  
  for(int i = 0; i < 8; i++){
    displayContent[i][0] = original[i];
  }
}

void displayScrolRigth(){
  copyArray(blank);
  for (int i = 0; i < 8; i++){
    shiftRegisterRigth(getColumn(smile_1,i));
    displayScreen();
  }
  for(int i = 0; i < 8; i++){
     shiftRegisterRigth(getColumn(smile_2,i));
     displayScreen();
  }
  for(int i = 0; i < 8; i++){
     shiftRegisterRigth(getColumn(smile_3,i));
     displayScreen();
  } 
}

// Desplazamiento de la imagen hacia la arriba

void shiftRegisterTop(int original[8]){
  for(int i = 0; i < 8; i++){ //columnas
    for(int j = 0; j < 8; j++){ // fila
      displayContent[j][i] = displayContent[j+1][i];
    }
  }  
  for(int i = 0; i < 8; i++){
    displayContent[7][i] = original[i];
  }
}

void displayScrolTop(){
  copyArray(blank);
  for (int i = 0; i < 8; i++){
    shiftRegisterTop(getRow(smile_1,i));
    displayScreen();
  }
  for(int i = 0; i < 8; i++){
     shiftRegisterTop(getRow(smile_2,i));
     displayScreen();
  }
  for(int i = 0; i < 8; i++){
     shiftRegisterTop(getRow(smile_3,i));
     displayScreen();
  } 
}

// Desplazamiento de la imagen hacia la abajo

void shiftRegisterBottom(int original[8]){
  for(int i = 0; i < 8; i++){ //columnas
    for(int j = 7; j >= 0; j--){ // fila
      displayContent[j][i] = displayContent[j-1][i];
    }
  }  
  for(int i = 0; i < 8; i++){
    displayContent[0][i] = original[i];
  }
}

void displayScrolBottom(){
  copyArray(blank);
  for(int i = 7; i >= 0; i--){
     shiftRegisterBottom(getRow(smile_1,i));
    displayScreen();
  }
  for(int i = 7; i >= 0; i--){
     shiftRegisterBottom(getRow(smile_2,i));
     displayScreen();
  }
  for(int i = 7; i >= 0; i--){
     shiftRegisterBottom(getRow(smile_3,i));
     displayScreen();
  } 
}

void loop(){
  displayScrolLeft();
  displayBlank();
  displayScrolRigth();
  displayBlank();
  displayScrolTop();
  displayBlank();
  displayScrolBottom();
  displayBlank();
}

void displayBlank(){
  copyArray(blank);
  displayScreen();
}

void displayScreen() {
  for (int x = 0; x < pauseDelay; x++){//Para repitir la imagen en un cierto tiempo cambiar por libreria timer
    for (int thisRow = 0; thisRow < 8; thisRow++) { //Seleccionamos la fila
      digitalWrite(row[thisRow], LOW); // encedemos la fila entera
      for (int thisCol = 0; thisCol < 8; thisCol++) {//seleccionamos la columna
        digitalWrite(col[thisCol], displayContent[thisRow][thisCol]); //activamos o desactivamos esa columna dependiendo el valor de la matrix
        digitalWrite(col[thisCol], LOW);//Apagamos esa columna
      }
      digitalWrite(row[thisRow], HIGH);//Apagamos la fila entera
    }
  }
}

