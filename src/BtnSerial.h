#include <Arduino.h>

class BtnSerial {

    private:
        int _btnNum = 0;
        char _btnChar = '1';

        bool _readSerial(){

            int retVal = 0;

            if (Serial.available()>0) {
                char inChar;
                inChar = Serial.peek();

                if (inChar == _btnChar) {
                    inChar = Serial.read();
                    retVal = 1;
                }
                //Serial.println(inChar);
            }

            return (retVal);
        }

    public:

        BtnSerial(int btnNum) : _btnNum(btnNum) {
            if (_btnNum == 0) _btnChar = '1';
            else if (_btnNum == 1) _btnChar = '2';
            else if (_btnNum == 2) _btnChar = '3';
        };

        //~BtnSerial();

        int wasPressed() {
            return (_readSerial());
        }

        int wasReleased() {
            return(wasPressed());
        }

        int pressedFor(int ms) {};

};