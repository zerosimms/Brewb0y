//Rudimentary counter

void startCounter() {
  if (buttonState == HIGH && !startCountingDown) {
    startCountingDown = true; 
  }
}

void checkTimer() {
  if (timer > 0 && startCountingDown){
    if (seconds >= 1){
      seconds = seconds -1; 
    }
    if (seconds == 0){
      timer = timer -1;
      seconds = 60;
    }
    if (timer <= 0){
      timer = 0;
      seconds = 0;   
    }
    delay(1000);
  }
}
