void process_serial_input(HardwareSerial &port) {
  while (port.available() > 0) {
    char c = (char)port.read();
    if (c == '@') {
      modem_received.trim();
      if (modem_received.length() > 0) {
        execute_data(modem_received);
      } else {
        modem_received = "";
      }
    } else if (c == '\r' || c == '\n') {
      // Abaikan CR/LF dari Terminal
    } else {
      if (modem_received.length() < MAX_MODEM_LENGTH) {
        modem_received += c;
      } else {
        Serial.println("ERROR: Data serial terlalu panjang!");
        modem_received = "";
      }
    }
  }
}

void listen_serial() {
  process_serial_input(Serial);
}

void listen_modem() {
  process_serial_input(modem);
}

void execute_data(String cmd) {
  modem_received = "";
  Serial.print("FROM Modem : ");
  Serial.println(cmd);
  if (cmd.length() == 0) return;
  if (cmd.startsWith("s#1;")) from_modem[0] = cmd;
  else if (cmd.startsWith("s#2;")) from_modem[1] = cmd;
  else if (cmd.startsWith("s#3;")) from_modem[2] = cmd;
  else if (cmd.startsWith("s#4;")) from_modem[3] = cmd;
  else if (cmd.startsWith("s#5;")) from_modem[4] = cmd;
  is_modem_available = false;
}

void parsing_data(){
    unsigned long now_ms = millis();
    if (now_ms - parsing_timer >= parsing_delay) {
        is_parsing = true;
        parsing_timer = now_ms;
        for (int i = 0; i < 5; i++) {
            if(from_modem[i] != ""){
                String* datas = split(from_modem[i], ';');
                if(i==0 && datas[1] != ""){
                    pm25 = datas[1];
                    pm10 = datas[2];
                    so2 = datas[3];
                    co = datas[4];
                    o3 = datas[5];
                    no2 = datas[6];
                    hc = datas[7];
                }
                else if(i==1 && datas[1] != "") textatas = datas[1];
                else if(i==2 && datas[1] != "") textatas = textatas + " " + datas[1];
                else if(i==3 && datas[1] != "") textbawah = datas[1];
                else if(i==4 && datas[1] != "") textbawah = textbawah + " " + datas[1];
                from_modem[i] = "";
            }
        }
        textWidth1 = runningtext1.textWidth(textatas);
        textWidth2 = runningtext2.textWidth(textbawah);
        print_all_value();
        is_parsing = false;
    }
}

String* split(String data, char separator) {
  static String splitted[MAX_SPLIT_ITEMS];
  for (int i = 0; i < MAX_SPLIT_ITEMS; i++) { splitted[i] = ""; }
  int index = 0;
  int start = 0;

  for (int i = 0; i <= data.length(); i++) {
    if (i == data.length() || data.charAt(i) == separator) {
      if (index >= MAX_SPLIT_ITEMS) {
        Serial.println("ERROR: Jumlah token melebihi batas!");
        return splitted;
      }
      splitted[index] = data.substring(start, i);
      index++;
      start = i + 1;
    }
  }
  return splitted;
}

void print_all_value(){
    for (int i = 0; i < 5; i++) {
        Serial.print("from_modem [");
        Serial.print(i);
        Serial.print("] : ");
        Serial.println(from_modem[i]);
    }
    // Serial.print("data1 :");
    // Serial.print(pm25);
    // Serial.print(';');
    // Serial.print(pm10);
    // Serial.print(';');
    // Serial.print(so2);
    // Serial.print(';');
    // Serial.print(no2);
    // Serial.print(';');
    // Serial.print(co);
    // Serial.print(';');
    // Serial.print(o3);
    // Serial.print(';');
    // Serial.println(hc);
    
    // Serial.print("data2 dan 3 :");
    // Serial.print(textatas);
    // Serial.println(';');
    
    // Serial.print("data4 dan 5 :");
    // Serial.print(textbawah);
    // Serial.println(';');
    
}