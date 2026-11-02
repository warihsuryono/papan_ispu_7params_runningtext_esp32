void runningText() {
    unsigned long now = millis();
    if (now - lastMove >= SCROLL_INTERVAL) {
        lastMove = now;
        pos1--;
        pos2--;
        if (pos1 < -textWidth1) pos1 = AREA_WIDTH;
        if (pos2 < -textWidth2) pos2 = AREA_WIDTH;
        runningtext1.clear(FansElectronics_Bitmap::Black);
        runningtext2.clear(FansElectronics_Bitmap::Black);
        runningtext1.drawText(pos1, 0, textatas.c_str());
        runningtext2.drawText(pos2, 0, textbawah.c_str());
        dmd.clear();
        dmd.drawBitmap(0, 0, runningtext1, FansElectronics_Bitmap::White);
        dmd.drawBitmap(AREA_WIDTH, 0, runningtext2, FansElectronics_Bitmap::White);
    }
}

int get_h_graph(int value){
    int result = 0;
    if(value > 300) result = map(value, 301, 500, 78, 96);
    else if(value > 100) result = map(value, 101, 300, 39, 77);
    else result = map(value, 0, 100, 0, 38);
    return result;
}

void drawGraph(){
    h_pm25 = get_h_graph(pm25.toInt());
    h_pm10 = get_h_graph(pm10.toInt());
    h_so2 = get_h_graph(so2.toInt());
    h_no2 = get_h_graph(no2.toInt());
    h_co = get_h_graph(co.toInt());
    h_o3 = get_h_graph(o3.toInt());
    h_hc = get_h_graph(hc.toInt());

    dmd.fill(0, 16, h_pm25, 16, FansElectronics_Bitmap::White);
    dmd.fill(96, 16, h_pm10, 16, FansElectronics_Bitmap::White);
    dmd.fill(192, 16, h_so2, 16, FansElectronics_Bitmap::White);
    dmd.fill(288, 16, h_no2, 16, FansElectronics_Bitmap::White);

    dmd.fill(96, 32, h_co, 16, FansElectronics_Bitmap::White);
    dmd.fill(192, 32, h_o3, 16, FansElectronics_Bitmap::White);
    dmd.fill(288, 32, h_hc, 16, FansElectronics_Bitmap::White);    
}