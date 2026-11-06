bool runningText() {
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
        dmd.drawBitmap(AREA_WIDTH, 0, runningtext1, FansElectronics_Bitmap::White);
        dmd.drawBitmap(AREA_WIDTH, 16, runningtext2, FansElectronics_Bitmap::White);
        frameChanged = true;
    }
    return true;
}

int get_h_graph(int value){
    int result = 0;
    if(value > 300) result = map(value, 301, 500, 78, 96);
    else if(value > 100) result = map(value, 101, 300, 39, 77);
    else result = map(value, 0, 100, 0, 38);
    return result;
}

bool drawGraph(){
    h_pm10 = get_h_graph(pm10.toInt());
    h_pm25 = get_h_graph(pm25.toInt());
    h_so2 = get_h_graph(so2.toInt());
    h_co = get_h_graph(co.toInt());
    h_o3 = get_h_graph(o3.toInt());
    h_no2 = get_h_graph(no2.toInt());
    h_hc = get_h_graph(hc.toInt());

    dmd.fill(0, 32, DISPLAY_WIDTH, 32, FansElectronics_Bitmap::Black);

    dmd.fill(0 + map(h_pm10,0,96,96,0), 32, h_pm10, 16, FansElectronics_Bitmap::White);
    dmd.fill(96 + map(h_pm25,0,96,96,0), 32, h_pm25, 16, FansElectronics_Bitmap::White);
    dmd.fill(192 + map(h_so2,0,96,96,0), 32, h_so2, 16, FansElectronics_Bitmap::White);
    dmd.fill(288 + map(h_co,0,96,96,0), 32, h_co, 16, FansElectronics_Bitmap::White);

    dmd.fill(96 + map(h_o3,0,96,96,0), 48, h_o3, 16, FansElectronics_Bitmap::White);
    dmd.fill(192 + map(h_no2,0,96,96,0), 48, h_no2, 16, FansElectronics_Bitmap::White);
    dmd.fill(288 + map(h_hc,0,96,96,0), 48, h_hc, 16, FansElectronics_Bitmap::White);  
    
    return true;  
}