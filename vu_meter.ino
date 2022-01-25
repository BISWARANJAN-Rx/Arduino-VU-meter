int arr[10];

int i = 0;
int check(int superMax)
{
  if (superMax < 15)
  {
    Serial.println("SLEEP NO_SIGNAL");

    return 3;
  } else if (superMax <= 300)
  {
    Serial.println("Sensitivity HIGH");
    return 2;
  }
  else if (superMax <= 650)
  {
    Serial.println("Sensitivity MID");
    return 1;
  } else
  {
    Serial.println("Sensitivity LOW");
    return 0;
  }
}
void setup() {
  arr[0] = 11;
  arr[1] = 10;
  arr[2] = 9;
  arr[3] = 8;
  arr[4] = 7;
  arr[5] = 6;
  arr[6] = 5;
  arr[7] = 4;
  arr[8] = 3;
  arr[9] = 2;
  for (i = 0; i < 10; i++)
  {
    pinMode(arr[i], OUTPUT);
  }

  for (i = 0; i < 10; i++)
  {
    digitalWrite(arr[i], HIGH);
    delay(150);
  }
  for (i = 0; i < 10; i++)
  {
    digitalWrite(arr[i], LOW);
    delay(150);
  }

  Serial.begin(2000000);


}

void loop() {
  while (analogRead(A1) < 50)
  { static int fade = 0;
    static int flag = 0;
    Serial.println("Week Signal");
    analogWrite(11, fade);
    if (flag == 0)
    {
      fade++;
    } else {
      fade--;
    }
    if (fade >= 255)
    {
      flag = 1;
    }
    if (fade <= 0)
    {
      flag = 0;
    }

    delay(5);
  }
  int sensorValue = 0;
  int scale;
  int maxi = 0;
  int superMax = 0;
  unsigned long savedTime = millis();
  int storeEvent = 0;
  int prescale = 88;
  while (true)
  {
    unsigned long ml = millis();
    if (ml < savedTime)
    {
      savedTime = ml;
    }
    if (ml - savedTime > 5000)
    {
      storeEvent = check(superMax);
      superMax = 0;
      savedTime = ml;
    }

    switch (storeEvent) {
      case 0:
        prescale = 88;
        break;
      case 1:
        prescale = 60;
        break;
      case 2:
        prescale = 25;
        break;
      case 3:

        while (sensorValue < 15)
        {
          static int cas = 0;
          for (int i = 0; i < 100; i++)
          {
            int temp = analogRead(A1);
            if (temp > sensorValue)
            {
              sensorValue = temp;
            }

          }

          digitalWrite(arr[cas], HIGH);
          delay(1000);
          digitalWrite(arr[cas], LOW);

          cas++;
          if (cas >= 10)
          {
            cas = 0;
          }

          superMax = 500;
        }


    }


    maxi = 0;
    for (i = 0; i < 60; i++)
    {

      sensorValue = analogRead(A1);
      if (sensorValue > maxi)
      {
        maxi = sensorValue;
      }


    }

    if (maxi > superMax)
    {
      superMax = maxi;
    }

    
//    for (i = 0; i < 10; i++)
//    {
//      digitalWrite(arr[i], LOW);
//    }
    
    //For Faster response
    for (i = 2; i <= 7; i++)
    {
      PORTD=~(1<<i)&PORTD;
    }
    for (i = 0; i <=3; i++)
    {
      PORTB=~(1<<i)&PORTB;
    }
      
     Serial.println(maxi); 

    for (i = 0; i < (maxi / prescale) && (i < 10); i++) {
      digitalWrite(arr[i], HIGH);
    }
  }
}
