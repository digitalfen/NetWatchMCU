#include "WebPages.h"


String WebPages::admin() {
  DateTime dt = EmuRTC::getSystemDateTime();
  String html = "<html><head><style>"
                "body { font-family: 'Arial', sans-serif; background-color: #f4f4f4; color: #333; margin: 0; padding: 0; text-align: center; }"
                "h1, h3 { color: #333; }"
                "h1 { text-align: center; padding: 20px 0; background-color: #4CAF50; color: white; margin: 0; }"
                "h3 { text-align: center; }"
                "form { text-align: center; margin: 20px 0; }"
                "button { background-color: #4CAF50; color: white; padding: 10px 20px; font-size: 16px; border: none; cursor: pointer; border-radius: 5px; margin: 5px; }"
                "button:hover { background-color: #45a049; }"
                "label { font-size: 16px; margin: 10px 0 5px; display: inline-block; }"
                "input[type='number'], input[type='text'] { padding: 10px; font-size: 16px; width: 120px; border-radius: 5px; border: 1px solid #ccc; margin: 5px; }"
                "input:focus { border-color: #4CAF50; outline: none; }"
                "hr { margin: 30px 0; }"
                "#datetime { font-weight: bold; color: #4CAF50; font-size: 18px; }"
                "@media (max-width: 600px) {"
                "body { padding: 10px; }"
                "input[type='number'], input[type='text'] { width: 100%; }"
                "} "
                ".datetime-container { display: flex; justify-content: center; gap: 20px; flex-wrap: wrap; }"
                ".time-container { display: flex; justify-content: center; gap: 20px; flex-wrap: wrap; }"
                "</style></head><body>";

  html += "<h1>WiFi Scanner - Admin</h1>";

  String fdt = String(dt.getYear()) + "/"
               + String(dt.getMonth()) + "/"
               + String(dt.getDay()) + " - "
               + String(dt.getHour()) + ":"
               + String(dt.getMinute()) + ":"
               + String(dt.getSecond());
  html += "<h4><span id='datetime'>" + fdt + "</span></h4>";

  html += "<div class='button-container' style='display: flex; justify-content: center; gap: 10px;'>";
  if (GlobalValues::scanning) {
    html += "<form action='/function' method='get'><input type='hidden' name='callable' value='stop_scan'><button>Stop Scan</button></form>";  // mexer aqui
  } else {
    html += "<form action='/function' method='get'><input type='hidden' name='callable' value='start_scan'><button>Start Scan</button></form>";
  }
  html += "<form action='/load' method='get'><input type='hidden' name='path' value='/results'><button>See results</button></form>";
  html += "<form action='/function' method='get'><input type='hidden' name='callable' value='clear_results'><button>Clear results</button></form>";
  html += "</div>";

  html += "<form action='/function' method='get'>";
  html += "<input type='hidden' name='callable' value='save_global'>";
  html += "<h3>Set scanner options</h3>";
  html += "<div class='datetime-container'>";
  html += "<label for='scan_interval'>Scan Interval (ms): </label>";
  html += "<input type='number' id='scan_interval' name='scan_interval' value='" + String(GlobalValues::scan_interval) + "'><br>";
  html += "<label for='scan_duration'>Scan Duration (ms): </label>";
  html += "<input type='number' id='scan_duration' name='scan_duration' value='" + String(GlobalValues::scan_repeat) + "'><br>";
  html += "</div>";

  html += "<h3>Set access point options</h3>";
  html += "<div class='datetime-container'>";
  html += "<label for='ap_ssid'>SSID: </label>";
  html += "<input type='text' id='ap_ssid' name='ap_ssid' value='" + GlobalValues::ap_ssid + "'><br>";
  html += "<label for='ap_pwrd'>Password: </label>";
  html += "<input type='text' id='ap_pwrd' name='ap_pwrd' value='" + GlobalValues::ap_pwrd + "'><br>";
  html += "</div>";

  html += "<h3>Set time and date</h3>";
  html += "<div class='time-container'>";
  html += "<label for='hour'>hh: </label><input type='number' id='hour' name='hour' value=''>";
  html += "<label for='minute'>mm: </label><input type='number' id='minute' name='minute' value=''>";
  html += "<label for='second'>ss: </label><input type='number' id=' ' name='second' value=''>";
  html += "</div>";

  html += "<div class='datetime-container'>";
  html += "<label for='day'>DD: </label><input type='number' id='day' name='day' value=''>";
  html += "<label for='month'>MM: </label><input type='number' id='month' name='month' value=''>";
  html += "<label for='year'>YYYY: </label><input type='number' id='year' name='year' value=''>";
  html += "</div>";

  html += "<button type='submit'>Save Settings</button>";
  html += "</form>";

  html += "<script>"
          "function updateTime() {"
          "  var now = new Date();"
          "  var hours = now.getHours().toString().padStart(2, '0');"
          "  var minutes = now.getMinutes().toString().padStart(2, '0');"
          "  var seconds = now.getSeconds().toString().padStart(2, '0');"
          "  var year = now.getFullYear();"
          "  var month = (now.getMonth() + 1).toString().padStart(2, '0');"
          "  var day = now.getDate().toString().padStart(2, '0');"
          "  document.getElementById('datetime').innerText = hours + ':' + minutes + ':' + seconds + ' - ' + year + '/' + month + '/' + day;"
          "}"
          "setInterval(updateTime, 1000);"
          "</script>";

  html += "</body>" + footer() + "</html>";

  return html;
}

String WebPages::results() {
  String html = "<html><head><style>";
  html += "body { font-family: 'Arial', sans-serif; background-color: #f4f4f4; color: #333; margin: 0; padding: 20px; } ";
  html += ".sssa { display: flex; justify-content: space-evenly; color: #4CAF50; font-size: 26px;}";
  html += ".nav1 { text-align: center; display: flex; justify-content: space-evenly; widht: 100vw;}";
  html += ".console { background-color: #2d2d2d; color: #fff; font-family: 'Courier New', monospace; padding: 20px; border-radius: 5px; box-shadow: 0 2px 10px rgba";
  html += "(0,0,0,0.1); width: 80%; margin: 0 auto; overflow-x: auto; white-space: pre-wrap; word-wrap: break-word; font-size: 16px; }";
  html += "button { background-color: #4CAF50; color: white; border: none; padding: 10px 20px; font-size: 16px; cursor: pointer; border-radius: 5px; margin-top: 20px; }";
  html += "button:hover { background-color: #45a049; }</style>";
  if (GlobalValues::scanning) {
    html += "<script>setTimeout(function(){ window.location.href = '/results'; }, " + String(GlobalValues::scan_interval) + ");</script>";
  }
  html += "</head><body><div class='sssa'><h1>Scan Results</h1></div>";
  html += "<div class='nav1'><form action='/load' method='get'><input type='hidden' name='path' value='/admin'>";
  html += "<button type='submit'>Back to Control Panel</button></form></div>";
  String jres;
  if (GlobalValues::scan_results == "[]") {
    jres = "<br><br><br><br>Empty data<br><br><br><br>";
  } else {
    jres = GlobalValues::scan_results;
  }
  html += "<div class='console'>" + jres + "</div>";
  html += "</body>" + footer() + "</html>";
  return html;
}

String WebPages::load(String path, String msg) {
  String loadingAnimation = R"(<html><style>
body{margin:0;padding:0;background:#ffffff}.container{width:200px;height:100px;padding-top:100px;margin:0 auto}.ball{width:10px;height:10px;margin:10px auto;border-radius:50px}.ball:nth-child(1){
background:#4CAF50;-webkit-animation:right 1s infinite ease-in-out;-moz-animation:right 1s infinite ease-in-out;animation:right 1s infinite ease-in-out}.ball:nth-child(2){background:#4CAF50;-webkit-animation:left
1.1s infinite ease-in-out;-moz-animation:left 1.1s infinite ease-in-out;animation:left 1.1s infinite ease-in-out}.ball:nth-child(3){background:#4CAF50;-webkit-animation:right 1.05s infinite ease-in-out;-moz-animat
ion:right 1.05s infinite ease-in-out;animation:right 1.05s infinite ease-in-out}.ball:nth-child(4){background:#4CAF50;-webkit-animation:left 1.15s infinite ease-in-out;-moz-animation:left 1.15s infinite ease-in-out;
animation:left 1.15s infinite ease-in-out}.ball:nth-child(5){background:#4CAF50;-webkit-animation:right 1.1s infinite ease-in-out;-moz-animation:right 1.1s infinite ease-in-out;animation:right 1.1s infinite ease-in
-out}.ball:nth-child(6){background:#4CAF50;-webkit-animation:left 1.05s infinite ease-in-out;-moz-animation:left 1.05s infinite ease-in-out;animation:left 1.05s infinite ease-in-out}.ball:nth-child(7){background:#fff
fff;-webkit-animation:right 1s infinite ease-in-out;-moz-animation:right 1s infinite ease-in-out;animation:right 1s infinite ease-in-out}@-webkit-keyframes right{0%{-webkit-transform:translate(-15px)}50%{-webkit-trans
form:translate(15px)}100%{-webkit-transform:translate(-15px)}}@-webkit-keyframes left{0%{-webkit-transform:translate(15px)}50%{-webkit-transform:translate(-15px)}100%{-webkit-transform:translate(15px)}}@-moz-keyframes
right{0%{-moz-transform:translate(-15px)}50%{-moz-transform:translate(15px)}100%{-moz-transform:translate(-15px)}}@-moz-keyframes left{0%{-moz-transform:translate(15px)}50%{-moz-transform:translate(-15px)}100%{-moz-
transform:translate(15px)}}@keyframes right{0%{transform:translate(-15px)}50%{transform:translate(15px)}100%{transform:translate(-15px)}}@keyframes left{0%{transform:translate(15px)}50%{transform:translate(-15px)}1
00%{transform:translate(15px)}}</style>
<div class='container'><div class='ball'></div><div class='ball'></div><div class='ball'></div><div class='ball'></div><div class='ball'></div><div class='ball'></div><div class='ball'></div></div>)";
  String html = "<html><style>body { font-family: 'Arial', sans-serif; background-color: #f4f4f4;";
  html += "color: #333; margin: 0; padding: 20; text-align: center; } </style><body><br><h1>" + msg + "</h1>";
  html += "</body></html>";
  return html + loadingAnimation + "<script>setTimeout(function(){ window.location.href = '" + path + "'; }, 1000);</script></body></html>)";
};
