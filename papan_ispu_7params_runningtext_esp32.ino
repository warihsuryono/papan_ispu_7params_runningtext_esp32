#include <FansElectronics_DMD32.h>
#include <fonts/Arial_Black_16.h>

#define PIN_DATA1 8
#define PIN_DATA2 7
#define PIN_DATA3 6
#define PIN_DATA4 9
#define PIN_CLK 18
#define PIN_LAT 14
#define PIN_OE 21
#define PIN_A 17
#define PIN_B 4

#define PIN_TRIMPOT 5

#define PANEL_WIDE 12
#define PANEL_HIGH 4

#define DISPLAY_WIDTH 384
#define DISPLAY_HEIGHT 16
#define AREA_WIDTH 192

#define SCROLL_INTERVAL 40

#define modem Serial1

#define MAX_MODEM_LENGTH 256
#define MAX_SPLIT_ITEMS 10

FansElectronics_DMD32 dmd;
DmdPins pinsHUB12 = {PIN_A, PIN_B, -1, -1, PIN_LAT, PIN_CLK, PIN_OE, PIN_DATA1, PIN_DATA2, PIN_DATA3, PIN_DATA4};

FansElectronics_Bitmap runningtext1(AREA_WIDTH, DISPLAY_HEIGHT);
FansElectronics_Bitmap runningtext2(AREA_WIDTH, DISPLAY_HEIGHT);

String modem_received = "";
String from_modem[5] = { "", "", "", "", "" };
String pm25 = "";
String pm10 = "";
String so2 = "";
String co = "";
String o3 = "";
String no2 = "";
String hc = "";
String textatas = "ISPU - PEMERINTAH KABUPATEN BATANG HARI";
String textbawah = "BATANG HARI SUPER TANGGUH";
unsigned long parsing_delay = 10000;
unsigned long trimpot_delay = 1000;
unsigned long parsing_timer = millis();
unsigned long trimpot_timer = millis();
bool is_parsing = false;
bool is_modem_available = false;
int brightness;
int pos1 = AREA_WIDTH;
int pos2 = AREA_WIDTH;
int textWidth1 = 0;
int textWidth2 = 0;
unsigned long lastMove = 0;

int h_pm25 = 0;
int h_pm10 = 0;
int h_so2 = 0;
int h_no2 = 0;
int h_co = 0;
int h_o3 = 0;
int h_hc = 0;

void setup() {
  Serial.begin(115200);
  modem.begin(9600);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_TRIMPOT, ADC_11db);

  dmd.begin(PANEL_HUB12, PANEL_WIDE, PANEL_HIGH, pinsHUB12, SCAN_PARALLEL);
  dmd.setDoubleBuffer(true);
  dmd.setFont(Arial_Black_16);

  brightness = map(analogRead(PIN_TRIMPOT), 0, 4095, 0, 255);

  dmd.setBrightness(brightness);

  runningtext1.setFont(Arial_Black_16);
  runningtext2.setFont(Arial_Black_16);
  textWidth1 = runningtext1.textWidth(textatas);
  textWidth2 = runningtext2.textWidth(textbawah);
  pos1 = AREA_WIDTH;
  pos2 = AREA_WIDTH;
  lastMove = millis();

  Serial.println("PAPAN ISPU 7 PARAMS RUNNING TEXT");
  Serial.print("Brightness : ");
  Serial.println(brightness);
}

void loop() {
  listen_serial();
  listen_modem();
  parsing_data();
  runningText();
  drawGraph();
  dmd.swapBuffersAndCopy();
  dmd.update();
}