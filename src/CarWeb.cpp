#include "CarWeb.h"
#include "secrets.h"

WebServer server(80);

void handRoot(){
    // File file = SPIFFS.open("/index.html");
    // if (!file){
    //     server.send(500, "text/plain", "Loi: Khong tim thay file HTML");
    //     return;
    // }

    // server.streamFile(file, "text/html");
    // file.close();

    const char *html = R"""(
      <!DOCTYPE html>
      <html>
      <head>
        <meta charset='UTF-8'>
        <meta name='viewport' content='width=device-width, initial-scale=1.0'>
        <title>ESP32 Car Controller</title>
        <style>
          body { font-family: Arial, sans-serif; text-align: center; background: #1e1e24; color: #fff; margin: 0; padding: 20px; }
          .grid { display: grid; grid-template-columns: repeat(3, 85px); grid-gap: 15px; justify-content: center; margin: 30px auto; }
          button { width: 85px; height: 85px; font-size: 26px; font-weight: bold; background: #00adb5; color: white; border: none; border-radius: 50%; cursor: pointer; box-shadow: 0 4px #007a80; }
          button:active { background: #007a80; transform: translateY(4px); box-shadow: 0 0px; }
          .stop { background: #ff2e63; box-shadow: 0 4px #b51f44; }
          .stop:active { background: #b51f44; }
          .slider-container { margin: 40px auto; max-width: 300px; }
          input[type=range] { width: 100%; height: 12px; border-radius: 5px; background: #393e46; outline: none; appearance: none; }
          input[type=range]::-webkit-slider-thumb { appearance: none; width: 25px; height: 25px; border-radius: 50%; background: #00adb5; cursor: pointer; }
        </style>
      </head>
      <body>
        <h2> ESP32 CAR SIMULATION </h2>
        <div class='grid'>
          <div></div><button onclick="send('forward')">▲</button><div></div>
          <button onclick="send('left')">◀</button><button class='stop' onclick="send('stop')">■</button><button onclick="send('right')">▶</button>
          <div></div><button onclick="send('backward')">▼</button><div></div>
        </div>
        <div class='slider-container'>
          <h3>Tốc độ: <span id='sp'>50</span>%</h3>
          <input type='range' min='0' max='100' value='50' onchange='updateSpeed(this.value)'>
        </div>
        <script>
          let dir = 'stop', speed = 50;
          function send(d) { dir = d; net(); }
          function updateSpeed(s) { document.getElementById('sp').innerText = s; speed = s; net(); }
          function net() { fetch(`/control?dir=${dir}&speed=${speed}`); }
        </script>
      </body>
      </html>

    )""";

    server.send(200, "text/html", html);
}

void handleControl(){
    String direction = server.hasArg("dir") ? server.arg("dir") : "stop";
    uint16_t speedVal = server.hasArg("speed") ? server.arg("speed").toInt() : 0;

    //xu ly dong co

    if(direction == "left"){
        Serial.printf("DIR: %s | Toc do re trai: %d\n", direction.c_str(), left_wheel_speed(speedVal));
    }else if(direction == "right"){
        Serial.printf("DIR: %s | Toc do re phai: %d\n", direction.c_str(), right_wheel_speed(speedVal));
    }else{Serial.printf("DIR: %s | Toc do: %d\n", direction.c_str(), speedVal);}

    server.send(200, "tex/plain", "OK");
}

void WebInit(){
    // if(!SPIFFS.begin(true)){
    //     Serial.println("Mount SPIFFS Failed!!!");
    //     return;
    // }

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){delay(500); Serial.print(".");}
    Serial.println("\nWifi Connected. IP: " + WiFi.localIP().toString());

    server.on("/", handRoot);
    server.on("/control", handleControl);

    server.begin();
}

void WebCtrl(){
    server.handleClient();
}