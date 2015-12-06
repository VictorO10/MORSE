#include <LiquidCrystal.h>


const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 50;  // threshold value to decide when the detected sound is a knock or not
int sensorReading = 0;


int c=10;

//initializing 16x2 LCD
LiquidCrystal lcd(7,6,5,4,3,2); //the input pins for the LCD
//creating the fill for empty cell
  byte fill[8]={
   B00000,
   B00000,
   B00000,
   B00000,
   B00000,
   B00000,
   B00000,
   B00000,
  };

//creating the fill for the arrow cell
  byte pl[8]{
    B00001,
    B00011,
    B00111,
    B01111,
    B01111,
    B00111,
    B00011,
    B00001,
  };

/*
 * We guided ourselves by a morse binary tree and we represented that tree as following:
 *    We made an array of structures
 *    mors *st represents the left child of the current parent
 *    mors *dr represents the right child of the current parent
 *    mors val represents the value (character) that of the current parent
 *    The root(mors [0] . val) and all the other unrepresantable characters have the value NULL ( 0 )
 */
 
struct mors {
  mors* st;
  mors* dr;
  char val;
} morse [70];

void setup() {
  
  //LCD
  lcd.begin(16,2); //turning on the display                
  lcd.createChar(11,fill); //creating the empty cell for the display
  lcd.createChar(12,pl); //creating the arrow for the display
  
  //LED
  //initialising the pins with which we are working
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  //we are turning off all the LEDs
  digitalWrite (8, LOW);
  digitalWrite (12, LOW);
  analogWrite (11, LOW);
  analogWrite (9, LOW);
  analogWrite (10, LOW);

  
  Serial.begin (9600);
  
  // initialization of the structure array
  morse [0] . val = 0;
  morse [0] . st = &morse [1];
  morse [0] . dr = &morse [2];

  morse [1] . val = 'e';
  morse [1] . st = &morse [3];
  morse [1] . dr = &morse [4];

  morse [2] . val = 't';
  morse [2] . st = &morse [5];
  morse [2] . dr = &morse [6];

  morse [3] . val = 'i';
  morse [3] . st = &morse [7];
  morse [3] . dr = &morse [8];

  morse [4] . val = 'a';
  morse [4] . st = &morse [9];
  morse [4] . dr = &morse [10];

  morse [5] . val = 'n';
  morse [5] . st = &morse [11];
  morse [5] . dr = &morse [12];

  morse [6] . val = 'm';
  morse [6] . st = &morse [13];
  morse [6] . dr = &morse [14];

  morse [7] . val = 's';
  morse [7] . st = &morse [15];
  morse [7] . dr = &morse [16];

  morse [8] . val = 'u';
  morse [8] . st = &morse [17];
  morse [8] . dr = &morse [18];

  morse [9] . val = 'r';
  morse [9] . st = &morse [19];
  morse [9] . dr = &morse [20];

  morse [10] . val = 'w';
  morse [10] . st = &morse [21];
  morse [10] . dr = &morse [22];

  morse [11] . val = 'd';
  morse [11] . st = &morse [23];
  morse [11] . dr = &morse [24];

  morse [12] . val = 'k';
  morse [12] . st = &morse [25];
  morse [12] . dr = &morse [26];

  morse [13] . val = 'g';
  morse [13] . st = &morse [27];
  morse [13] . dr = &morse [28];

  morse [14] . val = 'o';
  morse [14] . st = &morse [29];
  morse [14] . dr = &morse [30];

  morse [15] . val = 'h';
  morse [15] . st = &morse [31];
  morse [15] . dr = &morse [32];

  morse [16] . val = 'v';
  morse [16] . st = &morse [33];
  morse [16] . dr = &morse [34];

  morse [17] . val = 'f';
  morse [17] . st = &morse [35];
  morse [17] . dr = NULL;

  morse [18] . val = 0;
  morse [18] . st = &morse [36];
  morse [18] . dr = &morse [37];

  morse [19] . val = 'l';
  morse [19] . st = NULL;
  morse [19] . dr = &morse [38];

  morse [20] . val = 0;
  morse [20] . st = &morse [39];
  morse [20] . dr = NULL;

  morse [21] . val = 'p';
  morse [21] . st = &morse [40];
  morse [21] . dr = &morse [41];

  morse [22] . val = 'j';
  morse [22] . st = &morse [42];
  morse [22] . dr = &morse [43];

  morse [23] . val = 'b';
  morse [23] . st = &morse [44];
  morse [23] . dr = &morse [45];

  morse [24] . val = 'x';
  morse [24] . st = &morse [46];
  morse [24] . dr = NULL;

  morse [25] . val = 'c';
  morse [25] . st = &morse [47];
  morse [25] . dr = &morse [48];

  morse [26] . val = 'y';
  morse [26] . st = &morse [49];
  morse [26] . dr = NULL;

  morse [27] . val = 'z';
  morse [27] . st = &morse [50];
  morse [27] . dr = &morse [51];

  morse [28] . val = 'q';
  morse [28] . st = &morse [52];
  morse [28] . dr = &morse [53];

  morse [29] . val = 0;
  morse [29] . st = &morse [54];
  morse [29] . dr = NULL;

  morse [30] . val = 0;
  morse [30] . st = &morse [55];
  morse [30] . dr = &morse [56];

  morse [31] . val = '5';
  morse [31] . st = NULL;
  morse [31] . dr = NULL;

  morse [32] . val = '4';
  morse [32] . st = NULL;
  morse [32] . dr = NULL;

  morse [33] . val = 0;
  morse [33] . st = NULL;
  morse [33] . dr = NULL;

  morse [34] . val = '3';
  morse [34] . st = NULL;
  morse [34] . dr = NULL;

  morse [35] . val = 0;
  morse [35] . st = NULL;
  morse [35] . dr = NULL;

  morse [36] . val = 0;
  morse [36] . st = &morse [57];
  morse [36] . dr = &morse [58];

  morse [37] . val = '2';
  morse [37] . st = NULL;
  morse [37] . dr = NULL;

  morse [38] . val = 0;
  morse [38] . st = &morse [59];
  morse [38] . dr = NULL;

  morse [39] . val = '+';
  morse [39] . st = NULL;
  morse [39] . dr = &morse [60];

  morse [40] . val = 0;
  morse [40] . st = NULL;
  morse [40] . dr = NULL;

  morse [41] . val = 0;
  morse [41] . st = &morse [61];
  morse [41] . dr = NULL;

  morse [42] . val = 0;
  morse [42] . st = NULL;
  morse [42] . dr = NULL;

  morse [43] . val = '1';
  morse [43] . st = &morse [62];
  morse [43] . dr = NULL;

  morse [44] . val = '6';
  morse [44] . st = NULL;
  morse [44] . dr = &morse [63];

  morse [45] . val = '=';
  morse [45] . st = NULL;
  morse [45] . dr = NULL;

  morse [46] . val = '/';
  morse [46] . st = NULL;
  morse [46] . dr = NULL;

  morse [47] . val = 0;
  morse [47] . st = NULL;
  morse [47] . dr = NULL;

  morse [48] . val = 0;
  morse [48] . st = &morse [64];
  morse [48] . dr = &morse [65];

  morse [49] . val = 0;
  morse [49] . st = NULL;
  morse [49] . dr = &morse [66];

  morse [50] . val = '7';
  morse [50] . st = NULL;
  morse [50] . dr = NULL;

  morse [51] . val = 0;
  morse [51] . st = NULL;
  morse [51] . dr = &morse [67];

  morse [52] . val = 0;
  morse [52] . st = NULL;
  morse [52] . dr = NULL;

  morse [53] . val = 0;
  morse [53] . st = NULL;
  morse [53] . dr = NULL;

  morse [54] . val = '8';
  morse [54] . st = &morse [68];
  morse [54] . dr = NULL;

  morse [55] . val = '9';
  morse [55] . st = NULL;
  morse [55] . dr = NULL;

  morse [56] . val = '0';
  morse [56] . st = NULL;
  morse [56] . dr = NULL;

  morse [57] . val = '?';
  morse [57] . st = NULL;
  morse [57] . dr = NULL;

  morse [58] . val = '_';
  morse [58] . st = NULL;
  morse [58] . dr = NULL;

  morse [59] . val = '"';
  morse [59] . st = NULL;
  morse [59] . dr = NULL;

  morse [60] . val = '.';
  morse [60] . st = &morse [53];
  morse [60] . dr = &morse [54];

  morse [61] . val = '@';
  morse [61] . st = NULL;
  morse [61] . dr = NULL;

  morse [62] . val = '\'';
  morse [62] . st = NULL;
  morse [62] . dr = NULL;

  morse [63] . val = '_';
  morse [63] . st = NULL;
  morse [63] . dr = NULL;

  morse [64] . val = ';';
  morse [64] . st = NULL;
  morse [64] . dr = NULL;

  morse [65] . val = '!';
  morse [65] . st = NULL;
  morse [65] . dr = NULL;

  morse [66] . val = 0;
  morse [66] . st = NULL;
  morse [66] . dr = NULL;

  morse [67] . val = ',';
  morse [67] . st = NULL;
  morse [67] . dr = NULL;

  morse [68] . val = ':';
  morse [68] . st = NULL;
  morse [68] . dr = NULL;
}

double i = 0; //i is a timer which incremetns itself by 0.001 every 0.001 seconds

//Next we have declared the variables which check if we do stuff for the first time, so we do them again only when necessary
bool new_sig = 1; //new sign - the control knock for the first symbol of each word. This variable initializez itself with 1 each time we end a letter, and with 0 after the control knock 
bool new_word = 1; //new word - each time we end a word, we want to put a characte space ' ' after it. In order to avoid putting a ton of them we use this variable which initalizes itself with 0 once a space is put, and with 1 once we start new words :D
bool fst_time = 1; //first time usage after uploading on the arduino. We use this variable only once the avoid a bug with a LED: if we do not tap anything after we start the program the led which represents end of letter lights itself up (we're not gonna take it)
//variables for the lcd display
bool lcd_fst_time_line = 1; //we do not want for the lcd to reset(erase everything on it) each time we go to the line countdown
bool lcd_fst_time_space = 1; //we do not want for the lcd to reset each time we go to the space countdown
bool lcd_fst_time_word = 1; //we do not want for the lcd to reset each time we go to the word countdown
mors* cr_let = &morse [0]; //cr_let - the current letter, which starts from the root
mors* lit_crt; //lit_crt - in order to avoid a bug while displaying the current letter on the LCD, we use this pointer to point to the current letter, because the cr_let varaible resets to the root state
double t = 0; //in order to show the loading bar on the lcd, we use this variable. More on this below

void reset_ecran()
{
  lcd.clear();
    
  for(int x=0;x<10;x++) //we initialise the led with values from 0 to 9, which will be our timer on the LCD
  {
    lcd.setCursor(x,1);
    lcd.print(x);  
  }
  lcd.setCursor(10,1);
  lcd.write(byte(12)); //we overwrite the 9 with the arrow to start the counter

  c = 9;
  t = 0;
}

 void cronometru (char *s, char curent_letter) 
 {
  if (c >= 0)
  {
      lcd.setCursor (15, 0); //we put the current leter on the top right corner of the LCD screen
      lcd.print (curent_letter);
      lcd.setCursor (0, 0); //we print the current signal transmited to the arduino if a knock is detected before the timer ends
      lcd.print(s);
      lcd.setCursor(c,1);  //we write the arrow on the next cell
      lcd.write(byte(12));
      lcd.setCursor(c+1,1); //we erase the previous arrow
      lcd.write(byte(11));
      c--;
  }
}
 

void loop() {

  
  
  // put your main code here, to run repeatedly:

  char crt_msg [15]; // the current message to be send to the LCD display
  
  sensorReading = analogRead(knockSensor);


  /*
   * in order to translate the knocks into morse signals(. and _) we used the following rules:
   * If the delay (i) between the knocks is in:
   *                                         (0.03, 1] - we read a dot (.)
   *                                         (1, 2] - we read a line (_)
   *                                         (2, 4] - we print the letter
   *                                         (4, inf) - we print a space because the word ended
   */
  
  if (new_sig == 0 && i <= 1) //if we read a dot
  {
    //LED
    analogWrite (9, (1-i) * 255); //using a mathematical IVAN formula the LED will fade into darkness as the time to knock for a dot decreases (i in (0.03, 1])
    digitalWrite (8, HIGH); //not using a mathematican IVAN formula the LED will be ON if the next knock will generate a dot.

    //LCD
    strcpy (crt_msg, "."); //in order to print the current symbol on the top left corner of the LCD we use the crt_msg string
    if(i/0.1 >=t) //each 0.1 seconds we move the arrow on the LCD by one cell to the left
    {
      t++;
      if (cr_let == NULL || cr_let -> val == 0) //if the user makes a combination of symbols which can't be printed on the LCD, we just display an empty space on the top right corner and a morse symbol on the top left corner
      {
        cronometru(crt_msg, ' ');
      }
      else //else we display the current symbol on the top right corner and a morse symbol on the top left corner of the LCD
      {
        cronometru(crt_msg, cr_let -> val);
      }
    }
  }
 
  
  
 
  if (new_sig == 0 && i > 1 && i <= 2)//if we read a line
  {
    //LED
    digitalWrite (8, LOW); //we turn off the previous LED
    analogWrite (10, (2-i) * 255); //similar to the LED used for dot
    digitalWrite (12, HIGH);
    
    //LCD
    if (lcd_fst_time_line) //if it is the first time i is in (1, 2] for the current letter we clear the display of the LCD and prepare the '_' symbolfor printing
    {
      strcpy (crt_msg, "_");
      reset_ecran ();
      lcd_fst_time_line = 0;
    }
    if((i - 1)/0.1 >=t)
    {
      t++;
      if (cr_let == NULL || cr_let -> val == 0)
      {
        cronometru(crt_msg, ' ');
      }
      else
      {
        cronometru(crt_msg, cr_let -> val);
      }
    }
}

  if (i > 2 && i <= 4 && fst_time == 0) //if we print a letter
  {
    
    //LED
    digitalWrite (12, LOW);
    analogWrite (11, (2 - (i / 2)) * 255);
    
    //LCD
    if (lcd_fst_time_space)
    {
      strcpy (crt_msg, "Letter");
      reset_ecran ();
      lcd_fst_time_space = 0;
      lit_crt = cr_let; //we use this pointer to save the current letter so we can print it on the LCD on the top-right corner.
    }
    if( ((i/2) - 1) / (0.1) >= t)
    {
      t++;
      
      if (lit_crt == NULL || lit_crt -> val == 0)
      {
       cronometru(crt_msg, ' ');
      }
       else
      {
        cronometru(crt_msg, lit_crt -> val);
      }    
    }

    //Serial
    //We print the current letter in the console if we reached a known character
    if (cr_let != NULL)
    {
      
      if (cr_let -> val != 0  && new_sig == 0)
      {
        Serial.print (cr_let -> val); 
      }
    }
    cr_let = &morse [0]; //we reset the curent letter to the root
    new_sig = 1; 
  }
  
  if (i > 4) //if we print a space (end of word)
  {

    //LCD
    if (lcd_fst_time_word)
    {
      reset_ecran ();
      lcd_fst_time_word = 0;
      strcpy (crt_msg, "Press again");
    }
    if (cr_let == NULL || cr_let -> val == 0)
    {
      cronometru(crt_msg, ' ');
    }
    else
    {
      cronometru(crt_msg, cr_let -> val);
    }

    //SERIAL
    if (new_word == 0) //in order to print the space ' ' only once we use the new_word boolean
    {
      Serial.print (' ');
      new_word = 1;
    }
  }

  
  if (sensorReading > threshold) //if we detect a knock
  {
    fst_time = 0;
    if (new_sig) //this if represents the control knock. The control knock is the one you must do at the start of each letter
    {
      lcd_fst_time_line = 1; //We can reset the LCD for the line again
      lcd_fst_time_space = 1; //We can reset the LCD for the letter to be printed again
      lcd_fst_time_word = 1; //We can reset the LCD for the space to be printed again
      reset_ecran ();
      new_sig = 0;
      i = 0; //this is the control knock, we wait for the next knock to detect the delay.
      analogWrite (11, LOW);//we want the LED which counts down the timer until we can knock to get a letter to be turned OFF
    }
    if (i > 0.03) //we use >0.03 to avoid echos
    {
      lcd_fst_time_space = 1;
      lcd_fst_time_line = 1;
      lcd_fst_time_word = 1;
      reset_ecran ();
      
      //we turn OFF all the LEDs
      digitalWrite (12, LOW);
      digitalWrite (8, LOW);
      analogWrite (11, LOW);
      analogWrite (9, LOW);
      analogWrite (10, LOW);
      
      new_word = 0;
      if (i <= 1)//if we have a dot, we go to the left on the morse tree
      {
        cr_let = cr_let -> st;
       // Serial.println (".");
      }
      if (i > 1 && i <= 2) //if we have a line, we go to the right on the morse tree
      {
        cr_let = cr_let -> dr;
       // Serial.println ("_");
      }
    }
    i = 0;//the next delay will be counter starting from here
  }
  i += 0.001; //the i is the delay and it increments istelf with 0.001 each milisecond
  delay (1);//we have a delay of 1 milisecond
}
