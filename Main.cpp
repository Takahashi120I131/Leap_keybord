# include <Siv3D.hpp>
# include <Siv3DAddon/LeapMotion.hpp>
#define WINVER 0x0500
#include <windows.h>
#include <Leap.h>
# include <stdio.h>
//#include <iostream>
//#include <cstring>

# define keysize 150
# define keygap 2
# define Leapkeysize 60
#define WinXSize 1920
#define WinYSize 1080

#define keypointX WinXSize - keysize * 5 - keygap * 4 - 100
#define keypointY 100 + keysize

int WinSizeX = GetSystemMetrics(SM_CXSCREEN);
int WinSizeY = GetSystemMetrics(SM_CYSCREEN);

using namespace Leap;


class SampleListener : public Listener {
public:

    
private:
};

int CountTest = 0;

int pointx = 0;
int pointy = 0;
int pointz = 0;

int jpoint = 0;
int ipoint = 0;

int location = 0;
int maxlocation = 0;
bool keyflg = true;
bool Aaflg = true;
bool minflg = false;
int DominantHandLeft = 0;
float HandSize = 0.6;

TextWriter writer;
INPUT ip;


String keyspell[4][5] = {
    {{'U','p'},{'@','/',':','_','1'},{'A','B','C','2'}, {'D','E','F','3'},{'D','e','l'}},
    {{'L','e','f','t'}, {'G','H','I','4'},{'J','K','L','5'},{'M','N','O','6'},{'R','i','g','h','t'}},
    {{'D','o','w','n'},{'P','Q','R','S','7'},{'T','U','V','8'},{'W','X','Y','Z','9'},{'S','p','a','s','e'}},
    {{'K','a','n','a'},{'a','/','A',' '},{'""','&','-','0'},{',','.', '?', '!',';'}, {'E','n','t','e','r'}}
};
String keyspell2[4][5] = {
    {{'U','p'},{'@','/',':','_','1'},{'a','b','c','2'}, {'d','e','f','3'},{'D','e','l'}},
    {{'L','e','f','t'}, {'g','h','i','4'},{'j','k','l','5'},{'m','n','o','6'},{'R','i','g','h','t'}},
    {{'D','o','w','n'},{'p','q','r','s','7'},{'t','u','v','8'},{'w','x','y','z','9'},{'S','p','a','s','e'}},
    {{'K','a','n','a'},{'a','/','A',' '},{'""','&','-','0'},{',','.', '?', '!',';'}, {'E','n','t','e','r'}}
};
int keyprint[4][5][5] = {
    {{0xC8},{0xC0,0x35,0x28,'_',0x02},{0x1E,0x30,0x2E,0x03}, {0x20,0x12,0x21,0x04},{0x0E}},
    {{0XCB}, {0x22,0x23,0x17,0x05},{0x24,0x25,0x26,0x06},{0x32,0x31,0x18,0x07},{0XCD}},
    {{0xD0},{0x19,0x10,0x13,0x1F,0x08},{0x14,0x16,0x2F,0x09},{0x11,0x2D,0x15,0x2C,0x0A},{0x39}},
    {{0x70},{'a','/','A',' '},{'""','&','-','0'},{',','.', '?', '!',';'}, {0x1C}}
};



String text;

Cylinder Stick(const Vec3& from, const Vec3& to, double r = 0.1)
{
    const Vec3 v = to - from;

    const double length = v.length();

    if (!length)
    {
        return Cylinder(0.0, 0.0);
    }

    const Vec3 direction = v / length;

    const auto rotation = Quaternion::RotationArc(Vec3::Up, direction);

    return Cylinder(from, r, length, rotation).moveBy(direction * length * 0.5);
}

void writetext(int, float, int);
void Leapkey(float, float, float);
void RunProgram(int);

void RunProgram(int FingerEntry)
{

    if (FingerEntry == 1) {
        char passbuf[] = "\"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE\"";
        system(passbuf);
    }
    else if (FingerEntry == 2)
    {
        char passbuf[] = "\"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\"";
        system(passbuf);
    }

}


void Main(void)
{



    int a = 0;
    int FingerEntry = 0;
    bool tipflg = false;

    SampleListener listener;
    Controller controller;

    // イベントを受け取るリスナーを登録する
    controller.addListener(listener);
    const Frame frame = controller.frame();
    Leap::FingerList fingers = frame.fingers();
    fingers.extended().count();

    Window::Resize(1920, 1080);
    LeapMotion::RegisterAddon();

    const Font font(36), font2(30), font3(24);
    font(text).draw(20, 100);
    //テスト
    GUI gui(GUIStyle::Default);
    //gui.addln(L"button2", GUIButton::Create(L"1加算"));
    //gui.addln(L"text", GUITextArea::Create(10,5));


    gui.setTitle(L"タイトル");

    // 最大 6 文字に設定
    gui.add(L"text", GUITextField::Create(100));
    //ここまで
    while (System::Update())
    {
        /*if (GetAsyncKeyState('R'))
        {
            int DominantHandLeft = 0;
        }
        if (GetAsyncKeyState('L'))
        {
            int DominantHandLeft = 1;
        }*/
       // Graphics3D::FreeCamera();
        //テスト
        if (gui.button(L"button2").pushed)
        {
            a += 1;
        }
        //ここまで
        for (const auto& hand : LeapMotion::Hands())
        {

            const Vec3 scaledPos = hand.pos * 0.05 * HandSize;
            const Frame frame = controller.frame();
            fingers = frame.fingers();
            FingerEntry = fingers.extended().count();
            const double rock = hand.grabStrength;
            const double tip = hand.pinchStrength;
            Sphere(scaledPos, 0.5 * HandSize).draw(HSV(hand.id * 30).toColor());

           
            //a = a + 3;



            int p = 0;
            /*if (rock == 1 && DominantHandLeft == hand.isLeft) {
                a = 0;

                Sleep(3000);
                const Frame frame = controller.frame();
                fingers = frame.fingers();
                FingerEntry = fingers.extended().count();
                RunProgram(FingerEntry);
            }*/
            /*if (tip == 1 && DominantHandLeft != hand.isLeft) {
                LeapMotion::RegisterAddon();
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                tipflg = true;
            }
            if (tip == 0 && DominantHandLeft != hand.isLeft && tipflg == true) {
                tipflg = false;
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }*/
            if (DominantHandLeft != hand.isLeft) {
                SetCursorPos(1920+hand.pos.x * 4 + WinSizeX / 2, -hand.pos.z * 4 + WinSizeY / 2);
            }
            for (const auto& finger : hand.fingers)
            {

                for (const auto& joint : finger.joints)
                {
                    p++;
                    Sphere(joint * 0.05 * HandSize, 0.2).draw(HSV(finger.id * 10).toColor());

                    if (p == 10 && DominantHandLeft == hand.isLeft)
                    {
                        font(joint).draw(200, 20);
                        Leapkey(joint.x, joint.y, joint.z);
                    }
                }

                const int begin = (finger.type == LeapMotion::FingerType::Thumb)
                    || (finger.type == LeapMotion::FingerType::Pinky) ? 0 : 1;

                for (int i = begin; i < 4; ++i)
                {
                    Stick(finger.joints[i] * 0.05 * HandSize, finger.joints[i + 1] * 0.05 * HandSize).draw();

                }

            }

            for (int i = 0; i < Min<int>(4, hand.fingers.size()); ++i)
            {
                Stick(hand.fingers[i].joints[1] * 0.05 * HandSize, hand.fingers[i + 1].joints[1] * 0.05 * HandSize).draw();
            }

            Stick(hand.fingers[0].joints[0] * 0.05 * HandSize, hand.fingers[hand.fingers.size() - 1].joints[0] * 0.05 * HandSize).draw();


        }
        if (a >= 1000) { a = 0; };
        font(a).draw(200, 100);
        font(FingerEntry).draw(200, 200);
        font(L"左手でマウス操作\n右手でキー入力\n(スマホ入力の動き)").draw(20, 300, Palette::White);
        font(gui.textField(L"text").text).draw(200,900);
        //a++;


        //可視化キーボード出力処理
        {
            int i, j;
            Color max = Palette::White;
            Color mid = Palette::Skyblue;
            Color min = Palette::Orange;

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 5; j++)
                {
                    if (i == pointz && j == pointx) {
                        if (pointy == 1)
                        {
                            Rect(keypointX + keysize * j + keygap * j, keypointY + keysize * i + keygap * i, keysize).draw(mid);
                            if (Aaflg)
                            {
                                font2(keyspell[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                            }
                            else
                            {
                                font2(keyspell2[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                            }
                            minflg = false;
                        }
                        else if (pointy == 2 && minflg == false)
                        {
                            ipoint = i;
                            jpoint = j;

                            minflg = true;
                        }
                        else if (pointy == 2 && minflg)
                        {
                            Rect(keypointX + keysize * j + keygap * j, keypointY + keysize * i + keygap * i, keysize).draw(max);
                            if (Aaflg)
                            {
                                font2(keyspell[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                            }
                            else
                            {
                                font2(keyspell2[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                            }
                        }
                        else if (pointy == -1)
                        {
                            Rect(keypointX + keysize * j + keygap * j, keypointY + keysize * i + keygap * i, keysize).draw(max);
                            if (Aaflg)
                            {
                                font2(keyspell[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                            }
                            else
                            {
                                font2(keyspell2[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                            }
                            minflg = false;
                        }
                    }
                    else
                    {
                        Rect(keypointX + keysize * j + keygap * j, keypointY + keysize * i + keygap * i, keysize).draw(max);
                        if (Aaflg)
                        {
                            font2(keyspell[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                        }
                        else
                        {
                            font2(keyspell2[i][j]).draw(keypointX + keysize * j + keygap * j + 5, keypointY + keysize * i + keygap * i + keysize / 2, Palette::Red);
                        }
                    }

                }
            }
            if (minflg) {
                if (jpoint != 0 && jpoint != 4) {
                    Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(mid);
                    Rect(keypointX + keysize * (jpoint - 1) + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(mid);
                    Rect(keypointX + keysize * (jpoint + 1) + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(mid);
                    Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * (ipoint - 1) + keygap * ipoint, keysize).draw(mid);
                    Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * (ipoint + 1) + keygap * ipoint, keysize).draw(mid);

                    if (jpoint > pointx) {
                        Rect(keypointX + keysize * (jpoint - 1) + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(min);
                    }
                    else if (jpoint < pointx) {
                        Rect(keypointX + keysize * (jpoint + 1) + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(min);
                    }
                    else if (ipoint > pointz) {
                        Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * (ipoint - 1) + keygap * ipoint, keysize).draw(min);
                    }
                    else if (ipoint < pointz) {
                        Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * (ipoint + 1) + keygap * ipoint, keysize).draw(min);
                    }
                    else if (ipoint == pointz && jpoint == pointx) {
                        Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(min);
                    }

                    if (Aaflg)
                    {
                        font2(keyspell[ipoint][jpoint][0]).drawAt(keypointX + keysize * jpoint + keygap * jpoint + keysize / 2, keypointY + keysize * ipoint + keygap * ipoint + keysize / 2, Palette::Red);
                        font2(keyspell[ipoint][jpoint][1]).drawAt(keypointX + keysize * (jpoint - 1) + keygap * jpoint + keysize / 2, keypointY + keysize * ipoint + keygap * ipoint + keysize / 2, Palette::Red);
                        font2(keyspell[ipoint][jpoint][2]).drawAt(keypointX + keysize * jpoint + keygap * jpoint + keysize / 2, keypointY + keysize * (ipoint - 1) + keygap * ipoint + keysize / 2, Palette::Red);
                        font2(keyspell[ipoint][jpoint][3]).drawAt(keypointX + keysize * (jpoint + 1) + keygap * jpoint + keysize / 2, keypointY + keysize * ipoint + keygap * ipoint + keysize / 2, Palette::Red);
                        font2(keyspell[ipoint][jpoint][4]).drawAt(keypointX + keysize * jpoint + keygap * jpoint + keysize / 2, keypointY + keysize * (ipoint + 1) + keygap * ipoint + keysize / 2, Palette::Red);
                    }
                    else
                    {
                        font2(keyspell2[ipoint][jpoint]).draw(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint + keysize / 2, Palette::Red);
                    }
                }
                else {
                    Rect(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint, keysize).draw(min);
                    font2(keyspell[ipoint][jpoint]).draw(keypointX + keysize * jpoint + keygap * jpoint, keypointY + keysize * ipoint + keygap * ipoint + keysize / 2, Palette::Red);
                }
               
            }
        }
        //ここまで
        Box(0,0,0,1);

        if (GetAsyncKeyState('esc'))
        {
            return;
        }
    }
}

void writetext(int x, float y, int z)
{
    bool beforekeyflg = keyflg;


    //キー設定
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.wVk = 0; //We're doing scan codes instead
    ip.ki.dwExtraInfo = 0;

    //This let's you do a hardware scan instead of a virtual keypress
    ip.ki.dwFlags = KEYEVENTF_SCANCODE;
    ip.ki.wScan = 0x1E;  //Set a unicode character to use (A)
    //ここまで

    if (pointy == 2)
    {
        //if (jpoint >= -1 && jpoint <= 5) 
       // {
        if (jpoint - x >= 1 && y > 200 && keyflg && jpoint != 0 && jpoint != 4)
        {
            if (Aaflg)
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][1];
            }
            else
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][1];
            }
            location++;
            maxlocation++;
            keyflg = false;
            minflg = false;
        }
        else if (jpoint - x <= -1 && y > 200 && keyflg && jpoint != 0 && jpoint != 4)
        {
            if (Aaflg)
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][3];
            }
            else
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][3];
            }
            location++;
            maxlocation++;
            keyflg = false;
            minflg = false;
        }
        else if (ipoint - z >= 1 && y > 200 && keyflg && jpoint != 0 && jpoint != 4)
        {
            if (Aaflg)
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][2];
            }
            else
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][2];
            }
            location++;
            maxlocation++;
            keyflg = false;
            minflg = false;
        }
        else if (ipoint - z <= -1 && y > 200 && keyflg && jpoint != 0 && jpoint != 4)
        {
            if (Aaflg)
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][4];
            }
            else
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][4];
            }
            location++;
            maxlocation++;
            keyflg = false;
            minflg = false;
        }
        else if (y > 200 && keyflg)
        {
            if (Aaflg)
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][0];
            }
            else
            {
                ip.ki.wScan = keyprint[ipoint][jpoint][0];
            }
            location++;
            maxlocation++;
            keyflg = false;
            minflg = false;
        }

       // }
        


        //入力処理
        if (keyflg == false && beforekeyflg) {
            SendInput(1, &ip, sizeof(INPUT));
            ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        }
        //ここまで

    }
}
void Leapkey(float x,float y,float z)
{
    int i, j;

    for (i = -1; i < 5; i++)
    {
        for (j = -1; j < 6; j++)
        {
            if ((x > -(Leapkeysize * 2.5) + Leapkeysize * j) && (x < -(Leapkeysize * 2.5) + Leapkeysize * (j + 1))&& (z < (Leapkeysize * 2) - Leapkeysize * i) &&(z > (Leapkeysize * 2) - Leapkeysize * (i + 1)))
            {
                writetext(j, y, i);
                if (y > 400)
                {
                    pointy = -1;
                    keyflg = true;
                    minflg = false;
                }
                else if (y > 200)
                {
                    pointy = 1;
                    keyflg = true;
                    minflg = false;
                }
                else if (y > 150)
                {
                    pointy = 2;
                }

                if (j == -1)
                {
                   // j = 0;
                }
                if (j == 5)
                {
                   // j = 4;
                }


                if (i == -1)
                {
                   // i = 0;
                }
                if (i == 4)
                {
                   // i = 3;
                }
                //if (minflg == false) {
                    pointx = j;
                    pointz = i;
                //}
                return;
            }
        }
    }

}
