const char SETTINGS_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Settings</title>
    <style>
        body {
            background-color: #f1faee;
        }

        button {
            background-color: #457b9d;
            border: none;
            color: white;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            width: 20em;
        }

        select {
            background-color: #457b9d;
            border: none;
            color: white;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            width: 20em;
        }

        input {
            border: none;
            border-bottom: 2px solid #457b9d;
            color: black;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            width: 16em;
        }

        table {
            font-family: Arial, Helvetica, sans-serif;
            border-collapse: collapse;
            width: 100%;
        }

        td,
        th {
            border: 1px solid #ddd;
            padding: 8px;
        }

        tr:hover {
            background-color: #ddd;
        }

        th {
            padding-top: 12px;
            padding-bottom: 12px;
            text-align: left;
            background-color: #1d3557;
            color: white;
        }
    </style>
</head>

<body>
    <script type="text/javascript">
        function redirect(url) {
            window.location.href = url;
        }
        function commit(variable, value) {
            var xhttp = new XMLHttpRequest();
            var url = "/data?" + variable + "=" + value;
            console.log(url);
            xhttp.open("GET", url, true);
            xhttp.send();
        }
    </script>


    <table>
        <!--Overall Settings-->
        <tr>
            <th>Overall Settings</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Clock Type</td>
            <td>
                <select onChange="commit('clockType', this.value);">
                    <option value="0">Letters</option>
                    <option value="1">Lamp</option>
                </select>
            </td>
        </tr>
        <tr>
            <td>Time Type</td>
            <td>
                <select onChange="commit('timeType', this.value);">
                    <option value="0">15 nach x</option>
                    <option value="1">viertel x+1</option>
                </select>
            </td>
        </tr>
        <tr>
            <td>Timesource</td>
            <td>
                <select onChange="commit('DcfWlanMode', this.value);">
                    <option value="1">WLAN</option>
                    <option value="0">DCF77</option>
                </select>
            </td>
        </tr>
        <tr>
            <td>Brightness</td>
            <td><input onChange="commit('brightness', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Save all Settings from Ram</td>
            <td><button onclick="commit('saveALL',);">Save</button></td>
        </tr>
        <tr>
            <td>Load all Settings from Rom</td>
            <td><button onclick="commit('loadALL',);">Load</button></td>
        </tr>

        <!--ColorMode-->
        <tr>
            <th>Colormode</th>
            <th></th>
        </tr>
        <tr>
            <td>
                <label>Choose a Colormode</label>
            </td>
            <td>
                <select name="colormode" onChange="commit('colorMode', this.value);">
                    <option value="0">Static Color</option>
                    <option value="1">Breathe</option>
                    <option value="2">Color Cycle</option>
                    <option value="3" disabled>Saison</option>
                    <option value="4">Rainbow Cycle</option>
                    <option value="5">Explosion</option>
                    <option value="6">Spiral</option>
                    <!--<option value="420">Void</option>-->
                </select>
            </td>
        </tr>

        <!--Static Color-->
        <tr>
            <th>Static Color</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Red</td>
            <td><input onChange="commit('sc_redval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Green</td>
            <td><input onChange="commit('sc_greenval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Blue</td>
            <td><input onChange="commit('sc_blueval', this.value);" type="number" min="0" max="255"></td>
        </tr>

        <!--Breathe Color-->
        <tr>
            <th>Breathe Color</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Red</td>
            <td><input onChange="commit('breathe_redval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Green</td>
            <td><input onChange="commit('breathe_greenval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Blue</td>
            <td><input onChange="commit('breathe_blueval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Delay</td>
            <td><input onChange="commit('breathe_delay', this.value);" type="number" min="0"></td>
        </tr>

        <!--Rainbow Cycle-->
        <tr>
            <th>Rainbow Cycle</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Verzögerung</td>
            <td><input onChange="commit('rainbowcycle_verzoegerung', this.value);" type="number" min="0"></td>
        </tr>
        <tr>
            <td>Farbsprung</td>
            <td><input onChange="commit('rainbowcycle_farbsprung', this.value);" type="number" min="0"></td>
        </tr>

        <!--Explosion Color-->
        <tr>
            <th>Explosion Color</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Red</td>
            <td><input onChange="commit('explosion_redval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Green</td>
            <td><input onChange="commit('explosion_greenval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Blue</td>
            <td><input onChange="commit('explosion_blueval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Delay</td>
            <td><input onChange="commit('explosion_delay', this.value);" type="number" min="0"></td>
        </tr>

        <!--Spiral Color-->
        <tr>
            <th>Spiral Color</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Red Primary</td>
            <td><input onChange="commit('spiral_redval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Green Primary</td>
            <td><input onChange="commit('spiral_greenval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Blue Primary</td>
            <td><input onChange="commit('spiral_blueval', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Red Secondary</td>
            <td><input onChange="commit('spiral_redval2', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Green Secondary</td>
            <td><input onChange="commit('spiral_greenval2', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Blue Secondary</td>
            <td><input onChange="commit('spiral_blueval2', this.value);" type="number" min="0" max="255"></td>
        </tr>
        <tr>
            <td>Delay</td>
            <td><input onChange="commit('spiral_delay', this.value);" type="number" min="0"></td>
        </tr>
        
        <!--Wlan Zugangsdaten-->
        <tr>
            <th>Wlan Information</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>SSID</td>
            <td><input onChange="commit('wlan_ssid', this.value);"></td>
        </tr>
        <tr>
            <td>Password</td>
            <td><input type="password" onChange="commit('wlan_pw', this.value);"></td>
        </tr>
        <tr>
            <td>Save login credentials</td>
            <td><button onclick="commit('save_wlan',);">Save</button></td>
        </tr>
        <!--Debug-->
        <tr>
            <th>Debug</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>Get All</td>
            <td><button onclick="redirect('/data?getALL');">Get</button></td>
        </tr>
        <tr>
            <td>Crash on purpose</td>
            <td><button onclick="commit('crash',);">Crash</button></td>
        </tr>
    </table>

</html>
)=====";

const char WLAN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Wlan</title>
    <style>
        body {
            background-color: #f1faee;
        }

        button {
            background-color: #457b9d;
            border: none;
            color: white;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            width: 20em;
        }

        select {
            background-color: #457b9d;
            border: none;
            color: white;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            width: 20em;
        }

        input {
            border: none;
            border-bottom: 2px solid #457b9d;
            color: black;
            padding: 10px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            width: 16em;
        }

        table {
            font-family: Arial, Helvetica, sans-serif;
            border-collapse: collapse;
            width: 100%;
        }

        td,
        th {
            border: 1px solid #ddd;
            padding: 8px;
        }

        tr:hover {
            background-color: #ddd;
        }

        th {
            padding-top: 12px;
            padding-bottom: 12px;
            text-align: left;
            background-color: #1d3557;
            color: white;
        }
    </style>
</head>

<body>
    <script type="text/javascript">
        function redirect(url) {
            window.location.href = url;
        }
        function commit(variable, value) {
            var xhttp = new XMLHttpRequest();
            var url = "/data?" + variable + "=" + value;
            console.log(url);
            xhttp.open("GET", url, true);
            xhttp.send();
        }
    </script>


    <table>  
        <!--Wlan Zugangsdaten-->
        <tr>
            <th>Wlan Information</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>SSID</td>
            <td><input onChange="commit('wlan_ssid', this.value);"></td>
        </tr>
        <tr>
            <td>Password</td>
            <td><input type="password" onChange="commit('wlan_pw', this.value);"></td>
        </tr>
        <tr>
            <td>Save login credentials</td>
            <td><button onclick="commit('save_wlan',);">Save</button></td>
        </tr>
    </table>

    <button onclick="redirect('/');">Go on main Page</button>

</html>
)=====";