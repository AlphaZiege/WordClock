
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

function handleInput(value) {
    //alert(value);
    //0 = noDir, 1 = up, 2 = left, 3 = right, 4 = down
    if (value.endsWith('w') || value.endsWith('W')) {
        commit('snake_dir', '1');
    }
    if (value.endsWith('a') || value.endsWith('A')) {
        commit('snake_dir', '2');
    }
    if (value.endsWith('s') || value.endsWith('S')) {
        commit('snake_dir', '4');
    }
    if (value.endsWith('d') || value.endsWith('D')) {
        commit('snake_dir', '3');
    }
}

function fillData() {
    let url = '/data?getJSON';

    fetch(url)
        .then(res => res.json())
        .then((out) => {
            document.getElementById('ColorMode').value = out.ColorMode;
            document.getElementById('timeType').value = out.timeType;
            document.getElementById('clockType').value = out.clockType;
            document.getElementById('DcfWlanMode').value = out.DcfWlanMode;
            document.getElementById('Brightness').value = out.Brightness;
            document.getElementById('SolidColorRed').value = out.SolidColorRed;
            document.getElementById('SolidColorGreen').value = out.SolidColorGreen;
            document.getElementById('SolidColorBlue').value = out.SolidColorBlue;
            document.getElementById('BreatheColorRed').value = out.BreatheColorRed;
            document.getElementById('BreatheColorGreen').value = out.BreatheColorGreen;
            document.getElementById('BreatheColorBlue').value = out.BreatheColorBlue;
            document.getElementById('BreatheColorDelay').value = out.BreatheColorDelay;
            document.getElementById('RainbowCycleDelay').value = out.RainbowCycleDelay;
            document.getElementById('RainbowCycleFarbsprung').value = out.RainbowCycleFarbsprung;
            document.getElementById('ExplosionRed').value = out.ExplosionRed;
            document.getElementById('ExplosionGreen').value = out.ExplosionGreen;
            document.getElementById('ExplosionBlue').value = out.ExplosionBlue;
            document.getElementById('ExplosionRed2').value = out.ExplosionRed2;
            document.getElementById('ExplosionGreen2').value = out.ExplosionGreen2;
            document.getElementById('ExplosionBlue2').value = out.ExplosionBlue2;
            document.getElementById('ExplosionDelay').value = out.ExplosionDelay;
            document.getElementById('SpiralRed').value = out.SpiralRed;
            document.getElementById('SpiralGreen').value = out.SpiralGreen;
            document.getElementById('SpiralBlue').value = out.SpiralBlue;
            document.getElementById('SpiralRed2').value = out.SpiralRed2;
            document.getElementById('SpiralGreen2').value = out.SpiralGreen2;
            document.getElementById('SpiralBlue2').value = out.SpiralBlue2;
            document.getElementById('SpiralDelay').value = out.SpiralDelay;
            document.getElementById('Wlan_ssid').value = out.Wlan_ssid;
            document.getElementById('OffhoursBegin_h').value = out.OffhoursBegin_h;
            document.getElementById('OffhoursBegin_m').value = out.OffhoursBegin_m;
            document.getElementById('OffhoursEnd_h').value = out.OffhoursEnd_h;
            document.getElementById('OffhoursEnd_m').value = out.OffhoursEnd_m;
            document.getElementById('OffhoursBrightness').value = out.OffhoursBrightness;
            document.getElementById('version').value = out.version;
            document.getElementById('hostname').value = out.ClockName;
            document.getElementById('Localtime').value = out.local_time;
            document.getElementById('Localdate').value = out.local_date;
            document.getElementById('ntp_time').value = out.ntp_time;
            document.getElementById('Free_Memory').value = out.Free_Memory;
            document.getElementById('CPU_Speed').value = out.CPU_Speed;
            document.getElementById('Uptime').value = msToTime(out.Uptime);
            document.title = out.ClockName;
            return true;
        })
        .catch(err => {
            throw err
        });
    return false;
}

function msToTime(ms) {
    let seconds = (ms / 1000).toFixed(1);
    let minutes = (ms / (1000 * 60)).toFixed(1);
    let hours = (ms / (1000 * 60 * 60)).toFixed(1);
    let days = (ms / (1000 * 60 * 60 * 24)).toFixed(1);
    if (seconds < 60) return seconds + " Seconds";
    else if (minutes < 60) return minutes + " Minutes";
    else if (hours < 24) return hours + " Hours";
    else return days + " Days"
}

let status;

function livesignalListener() {
    if (this.status == 200) {
        status = true;
    }
}

function livesignal() {
    var http = new XMLHttpRequest();

    http.addEventListener("load", livesignalListener);
    http.open("GET", "/live");
    http.send();
}

function load(mode) {
    if (mode != true) {
        fillData();
    }

    var intervalId = setInterval(function () {
        if (status) {
            document.documentElement.style.setProperty('--live-signal', '#0f0');
        }
        else document.documentElement.style.setProperty('--live-signal', '#f00');
        status = false;
        livesignal();
    }, 2500);
}