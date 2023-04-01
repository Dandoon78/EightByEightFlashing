/*
    Multiplexing Assignment
    
    This program uses 16 pins on the Arduino Uno to light up 64 
    LEDs in a specific sequence.
    The pattern is as follows: 
    - Spiral inwards
    - Spiral outwards
    - Zigzag down
    - Zigzag up
    - Spiral inwards
    - Travels to the corners and back
    - Spiral outwards
    - Spiral inwards
    - Forms boxes outline outwards
    - Forms filled in boxes inwards
    - Spiral outwards
    
    Made by: Daniel Roufail
    
    March 31, 2023
    
    Version 2 - Efficient   
*/


// Declaring Constants, Variables and Arrays
// They are all declared as a byte data type because all the values are in between -128 and 127

// Stores the values of the LED pins

// Stores the pins used for the rows 
// This connects to the anode of the LED
// The row pins are digital pins 13, 12, 11, 10, 9, 7, 6
byte rowPinArray[] = {13, 12, 11, 10, 9, 8, 7, 6};

// Stores the pins used for the columns 
// This connects to the cathode of the LED
// The column pins are digital pins 5, 4, 2, 1, 0 and analog pins 5 and 4 
byte columnPinArray[] = {5, 4, 3, 2, 1, 0, A5, A4};

// Declares the indexes used in the program
// They are not all needed but Tinkercad bugs if certain ones are repeated
byte i;
byte x;
byte y; 
byte z;


// Only runs code once
// Sets up the pins
void setup(){
  
  // Cycles through all the eight rows and columns and sets all the pins as output pins
  // Setting them as output makes it so that the LEDs can receive power
  // If a pin is set as output and is not sending out power it acts as the ground (negative)
  for(i = 0; i < 8; i++){
   		pinMode(rowPinArray[i], OUTPUT);
    	pinMode(columnPinArray[i], OUTPUT); 
  }
}

// Runs code infinitely
void loop(){
  
  	// Calls the subroutine displaySequence 
  	// This will make the LEDs light in the set pattern
	displaySequence();
}


// Calls all the sequence subroutines so that the LEDs light in the pattern  	
void displaySequence(){
  	
  	
  	// This resets all the lights turning them all off
  	lightReset();
  	 
  	// This makes the LEDs light up in the spiral pattern inwards then outwards
	spiralIn();
  	spiralOut();
  
  	// This lights the LEDs in a zigzagging pattern going from the top to bottom then back to the top
  	zigZag();
  
  	// This lights the LEDs in a spiral inwards
 	spiralIn();
  
  	// This lights the LEDs to flash towards the corners starting from the center
	towardsCorners();
  
  	// This lights the LEDs to spiral outwards then inwards
  	spiralOut();
  	spiralIn();
  
  	// This lights lines up one at a time forming boxes going from small to big then big to small 
	expandingBox();
  
  	// This lights the LEDs to spiral outwards
  	spiralOut();
}


// This subroutine lights a horizantal line at the row specified
// It will turn off the outter lights depending on how many you want to remove
void horizantalLine(byte row, byte remove){
  	 
  	for(x = 0 + remove; x < 8 - remove; x++){
      	lightLed(row, x);
  	}
}

// This subroutine lights a vertical line at the column specified
// It will turn off the top and bottom lights depending on how many you want to remove
void verticalLine(byte column, byte remove){
	
  	for(x = 0 + remove; x < 8 - remove; x++){
      	lightLed(x, column);	
  	}
}

// This subroutine runs the pattern required to form the box outline outwards and the filled in box inwards
// It will cycles through half the rows and columns to flash each box in its specific order
void expandingBox(){
	
    z = 2;
  	for(y = 5; y < 8; y++){    
      	verticalLine(z, z);
        verticalLine(y, z);  	
      	lightReset();  
  		horizantalLine(z, z);
  		horizantalLine(y, z); 	
      	lightReset();   
      	z = z - 1;
  	}
  
  	z = 0;
  
  	for(y = 7; y > 3; y--){		
  		verticalLine(z, z);
  		verticalLine(y, z);      
      	horizantalLine(z, z);
  		horizantalLine(y, z);    	
      	lightReset();    
      	z = z + 1;
  	}
}

// This subroutine sets the pattern to flash the LEDs going from the center to the corners and back
// Cycles through half the columns and rows to locate the specific LEDs required for the sequence
void towardsCorners(){
  	
  	z = 1;  
  	for(y = 4; y < 8; y++){     	
      	lightLed(y, y - z);
      	lightLed(y - z, y);      	
      	lightReset();     
      	z = z + 2;
  	}
  	
  	z = 8;  
  	for(y = 8; y > 3; y--){      	
      	lightLed(y - 1, y - z);
     	lightLed(y - z, y - 1);     	
      	lightReset();      
      	z = z - 2;
  	}
}

// This subroutine sets the pattern for lighting the LEDs in a zigzag down then back up
// It cycles through all the rows to determine which row is to be flashed in the specified order
void zigZag(){
	
  	for(y = 0; y < 7; y++){    	
      	lightHorizantalFwd(y, 0);
      	lightHorizantalBack(y + 1, 0);      
      	y = y + 1;
    }
  
  	for(y = 8; y > 0; y--){      	
      	lightHorizantalFwd(y - 1, 0);
  	 	lightHorizantalBack(y - 2, 0);      
      	y = y - 1;
  	}
}

// This subroutine sets the pattern for lighting the spiral inwards
void spiralIn(){
  
    // Cycles through all the LEDs to spiral inwards
    for(y = 0; y <= 3; y++){
        
      	// Flashes the LEDs one by one in linest to spiral inwards
      	// The sequence for the spiral inwards is left to right, top to bottom, right to left and bottom to top
      	lightHorizantalFwd(y, y);
        lightVerticalDwn(7 - y, y, 0);
        lightHorizantalBack(7 - y, y);
        lightVerticalUp(y, y);
    } 
}

// This subroutine sets the pattern for lighting the spiral outwards
void spiralOut(){
  
    // Cycles through all the LEDs to spiral inwards
    for(y = 4; y > 0; y--){
        
      	// Flashes the LEDs one by one in lines to spiral outwards
      	// The sequence for the spiral outwards is top to bottom, left to right, bottom to top, right to left
      	lightVerticalDwn(y - 1, y - 1, 1);
        lightHorizantalFwd(8 - y, y - 1);
        lightVerticalUp(8 - y, y - 1);
        lightHorizantalBack(y - 1, y - 1);
    }
}

// This subroutine makes the LEDs flash one by one in a horizantal line from left to right
void lightHorizantalFwd(byte row, byte remove){
	
  	for(x = 0 + remove; x < 8 - remove; x++){      	
    	for(i = 0; i < 8; i++){      		
          	lightLed(i + row, x);		
          	lightReset();
    	}
  	}
}

// This subroutine makes the LEDs flash one by one in a vertical line from top to bottom
void lightVerticalDwn(byte column, byte remove, byte reverse){
	
  	for(x = 0 + remove + reverse; x < 8 - remove; x++){    	
      	for(i = 0; i < 8; i++){      		
          	lightLed(x, i + column);      		
          	lightReset();
    	}
  	}
}

// This subroutine makes the LEDs flash one by one in a horizantal line from right to left
void lightHorizantalBack(byte row, byte remove){
	
  	for(x = 8 - remove; x > 0 + remove; x--){
      	for(i = 0; i < 8; i++){      		
          	lightLed(i + row, x - 1);
      		lightReset();
    	}
  	}
}

// This subroutine makes the LEDs flash one by one in a vertical line from bottom to top
void lightVerticalUp(byte column, byte remove){
	
  	for(x = 8 - remove; x > 1 + remove; x--){
      	for(i = 0; i < 8; i++){
          	lightLed(x - 1, i + column);
      		lightReset();
    	}
  	}
}

// This subroutine resets all the LEDs and turns them off
void lightReset(){
  
  for(i = 0; i < 8; i++){
    digitalWrite(rowPinArray[i], LOW);
    digitalWrite(columnPinArray[i], HIGH);
  } 
}

// This subroutine lights a single LED at the specified row and column
void lightLed(byte row, byte column){
  	
  	digitalWrite(rowPinArray[row], HIGH);
  	digitalWrite(columnPinArray[column], LOW);
  	delay(40);
}
