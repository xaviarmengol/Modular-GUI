#include <Arduino.h>

class BtnSerial {

    private:
        int _btnNum = 0;
        char _btnChar = '1';

        bool _readSerial(char readChar){

            int foundChar = 0;

            if (Serial.available()>0) {
                char inChar;
                inChar = Serial.peek();

                if (inChar == readChar) {
                    inChar = Serial.read();
                    foundChar = 1;
                }
                //Serial.println(inChar);
            }

            return (foundChar);
        }

    public:

        BtnSerial(int btnNum) : _btnNum(btnNum) {
            if (_btnNum == 0) _btnChar = '1';
            else if (_btnNum == 1) _btnChar = '2';
            else if (_btnNum == 2) _btnChar = '3';
        };

        //~BtnSerial();

        int wasPressed() {
            return (_readSerial(_btnChar));
        }

        int wasReleased() {
            return(wasPressed());
        }

        int pressedFor(int ms) {
            return(_readSerial('w'));
        };

};