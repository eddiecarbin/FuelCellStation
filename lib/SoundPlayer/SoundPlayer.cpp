

#include <Arduino.h>
#include "SoundPlayer.h"
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

#define PLAY_DELAY 500;

SoundPlayer *SoundPlayer::s_instance = 0;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX

int fileCount = 0;
bool soundPlaying = false;
int soundIdx = 1;
unsigned long lastPlay = 0;

SoundPlayer::SoundPlayer(int pin, int value = 12)
{
}

DFRobotDFPlayerMini myDFPlayer;

void SoundPlayer::initialize()
{
    mySoftwareSerial.begin(9600);
    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(mySoftwareSerial))
    { //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while (true)
            ;
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.volume(30); //Set volume value. From 0 to 30

    fileCount = myDFPlayer.readFileCounts();
    // myDFPlayer.play(1); //Play the first mp3

    // myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
    //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
    myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
    //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
    //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);
    Serial.print("file count = ");
    Serial.println(fileCount);

    soundPlaying = false;
}

void SoundPlayer::update()
{

    if (myDFPlayer.available() && soundPlaying == true)
    {

        if (myDFPlayer.readType() == DFPlayerPlayFinished)
        {
            soundPlaying = false;
            Serial.println("sound complete");
        }
    }
}

bool SoundPlayer::isPlaying()
{
    return soundPlaying;
}

void SoundPlayer::PlaySound(int value = 1)
{
    unsigned long m = millis();
    if (m < lastPlay)
    {
        return;
    }

    if (soundPlaying == true)
    {
        // Serial.println("sound is playing stop!");
        //return;
    }

    soundPlaying = true;
    myDFPlayer.play(value); //Play the first mp3

    lastPlay = m + PLAY_DELAY;
}

void SoundPlayer::StopSound()
{
    soundPlaying = false;
    myDFPlayer.stop();
}

void SoundPlayer::volume(uint8_t value)
{
    myDFPlayer.volume(value);
}

void SoundPlayer::printDetail(uint8_t type, int value)
{
    switch (type)
    {
    case TimeOut:
        Serial.println(F("Time Out!"));
        break;
    case WrongStack:
        Serial.println(F("Stack Wrong!"));
        break;
    case DFPlayerCardInserted:
        Serial.println(F("Card Inserted!"));
        break;
    case DFPlayerCardRemoved:
        Serial.println(F("Card Removed!"));
        break;
    case DFPlayerCardOnline:
        Serial.println(F("Card Online!"));
        break;
    case DFPlayerPlayFinished:
        Serial.print(F("Number:"));
        Serial.print(value);
        Serial.println(F(" Play Finished!"));
        break;
    case DFPlayerError:
        Serial.print(F("DFPlayerError:"));
        switch (value)
        {
        case Busy:
            Serial.println(F("Card not found"));
            break;
        case Sleeping:
            Serial.println(F("Sleeping"));
            break;
        case SerialWrongStack:
            Serial.println(F("Get Wrong Stack"));
            break;
        case CheckSumNotMatch:
            Serial.println(F("Check Sum Not Match"));
            break;
        case FileIndexOut:
            Serial.println(F("File Index Out of Bound"));
            break;
        case FileMismatch:
            Serial.println(F("Cannot Find File"));
            break;
        case Advertise:
            Serial.println(F("In Advertise"));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

SoundPlayer::~SoundPlayer()
{
}
