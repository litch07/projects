/***********************************************************************
 *  OptiWatt Smart Booth – ESP32 Web Server (Spec-Compliant, Bugfixed)
 *  ---------------------------------------------------------------
 *  Board : ESP32 DevKit V1
 *  Date  : 2025-10-19
 *
 *  Implements:
 *  - Control hierarchy: Physical/Web > Automation (per-device), Global Auto master
 *  - Modal confirmation to re-enable automation after manual action
 *  - Occupancy state machine (VACANT→ENTRY_ARMED→OCCUPIED→EXIT_ARMED)
 *    with median(9), 300ms debounce, 1.2s refractory, 2s pair window
 *  - 3s per-device vacancy off-delay
 *  - PZEM on UART2, device addresses 0x02 (LED) and 0x03 (Plug)
 *  - 1 Hz /state polling; responsive non-blocking loop
 *  - Preferences: globalAuto, ledAuto, plugAuto, ledGoal, plugGoal
 ***********************************************************************/

#include <WiFi.h>
#include <WebServer.h>
#include <PZEM004Tv30.h>
#include <Preferences.h>

/* ===================  WIFI CONFIG  =================== */
const char* ssid     = "OptiWatt";
const char* password = "PasswordNai";

/* ===================  EMBEDDED HTML / CSS / JS =================== */
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>⚡ OptiWatt Smart Booth</title>
<style>
:root {
  --bg:#0f172a; --card:#1e293b; --text:#f1f5f9;
  --green:#22c55e; --red:#ef4444; --blue:#3b82f6; --muted:#94a3b8;
}
.light { --bg:#f8fafc; --card:#ffffff; --text:#1e293b; }
body {
  background:var(--bg); color:var(--text);
  font-family:Inter,Arial,sans-serif; margin:0; padding:0;
  transition:background .3s,color .3s;
}
header { text-align:center; padding:1rem 0; }
h1 {margin:0;font-size:1.8rem;}
h2 {margin:.2rem 0 .8rem;font-weight:400;font-size:1rem;}
.container {
  display:grid; gap:1rem;
  grid-template-columns:repeat(auto-fit,minmax(250px,1fr));
  padding:0 1rem 2rem;
}
.card {
  background:var(--card); border-radius:1rem;
  padding:1rem; box-shadow:0 2px 6px #0002;
}
button {
  border:none; border-radius:.5rem;
  padding:.5rem 1rem; font-weight:600; cursor:pointer;
  color:#fff; transition:opacity .2s;
}
button:disabled{opacity:.5;cursor:not-allowed;}
.btn-green{background:var(--green);}
.btn-red{background:var(--red);}
.btn-blue{background:var(--blue);width:100%;}
.toggle{position:fixed;top:.8rem;right:.8rem;cursor:pointer;font-size:1.4rem;}
.badge{padding:.2rem .6rem;border-radius:1rem;font-size:.8rem;}
.badge.on{background:var(--green);color:#fff;}
.badge.off{background:#64748b;color:#fff;}
.progress{height:8px;border-radius:4px;background:#475569;overflow:hidden;}
.progress span{display:block;height:100%;background:var(--green);width:0%;}
.warning{background:#facc15;color:#000;padding:.4rem;border-radius:.5rem;font-size:.8rem;margin-bottom:.5rem;display:none;}
footer{font-size:.8rem;padding:1rem 2rem;opacity:.7;}
.grid2x2{display:grid;grid-template-columns:1fr 1fr;gap:.3rem;}
.stat{font-size:.9rem;}
.small{color:var(--muted);font-size:.85rem}
.modal{position:fixed;inset:0;background:rgba(0,0,0,.35);display:none;align-items:center;justify-content:center;z-index:20}
.modal .box{background:var(--card);border:1px solid #334155;border-radius:12px;padding:16px;width:min(480px,92%)}
.modal .box h3{margin:.3rem 0}
.modal .actions{display:flex;gap:8px;justify-content:flex-end;margin-top:10px}
</style>
</head>
<body>
<div class="toggle" id="themeToggle">🌙</div>
<header>
  <h1>⚡ OptiWatt Smart Booth</h1>
  <h2>Smart Energy Management System</h2>
  <div id="occBadge" class="badge off">Vacant</div>
  <button id="globalAutoBtn" class="btn-blue" style="margin-top:.5rem;">Global Auto: ON</button>
</header>

<section class="container" id="stats">
  <div class="card" id="totalPower"><h3>Total Power</h3><div id="totalPowerVal">0 W</div></div>
  <div class="card"><h3>Entries Today</h3><div id="entries">0</div></div>
  <div class="card"><h3>Exits Today</h3><div id="exits">0</div></div>
  <div class="card">
    <h3>Estimated Monthly Cost</h3>
    <div id="monthCost">৳0</div>
    <div class="small" id="projExplain">Avg-based projection from MTD energy</div>
  </div>
</section>

<section class="container">
  <div class="card" id="ledCard">
    <h3>💡 LED <span id="ledAutoBadge" class="badge on">AUTO</span></h3>
    <div id="ledWarn" class="warning">⚠️ Physical switch active. Web controls disabled until released.</div>
    <div class="grid2x2">
      <div class="stat">V: <span id="ledV">0</span></div>
      <div class="stat">I: <span id="ledI">0</span></div>
      <div class="stat">P: <span id="ledP">0</span></div>
      <div class="stat">E: <span id="ledE">0</span> kWh</div>
    </div>
    <div style="margin-top:.6rem;">
      <div>Today’s Cost (est.): ৳<span id="ledCost">0</span></div>
      <div>Goal (daily): <span id="ledGoalVal">100</span> kWh <button id="ledGoalEdit">✏️</button></div>
      <div class="progress"><span id="ledProg"></span></div>
    </div>
    <div style="margin-top:.8rem;">
      <button class="btn-green" id="ledOnBtn">Turn ON</button>
      <button class="btn-red"   id="ledOffBtn">Turn OFF</button>
      <button class="btn-blue"  id="ledAutoBtn">Toggle Automation</button>
    </div>
  </div>

  <div class="card" id="plugCard">
    <h3>🔌 Plug <span id="plugAutoBadge" class="badge on">AUTO</span></h3>
    <div id="plugWarn" class="warning">⚠️ Physical switch active. Web controls disabled until released.</div>
    <div class="grid2x2">
      <div class="stat">V: <span id="plugV">0</span></div>
      <div class="stat">I: <span id="plugI">0</span></div>
      <div class="stat">P: <span id="plugP">0</span></div>
      <div class="stat">E: <span id="plugE">0</span> kWh</div>
    </div>
    <div style="margin-top:.6rem;">
      <div>Today’s Cost (est.): ৳<span id="plugCost">0</span></div>
      <div>Goal (daily): <span id="plugGoalVal">100</span> kWh <button id="plugGoalEdit">✏️</button></div>
      <div class="progress"><span id="plugProg"></span></div>
    </div>
    <div style="margin-top:.8rem;">
      <button class="btn-green" id="plugOnBtn">Turn ON</button>
      <button class="btn-red"   id="plugOffBtn">Turn OFF</button>
      <button class="btn-blue"  id="plugAutoBtn">Toggle Automation</button>
    </div>
  </div>
</section>

<footer>
  <b>📡 Technical Note: Presence Detection System</b><br>
  Two HC-SR04 ultrasonics: <b>Entry</b> = Door ≤ 4 cm then Inside ≤ 30 cm within 2 s; <b>Exit</b> = Inside then Door within 2 s.<br>
  Safeguards: median(9) sampling, 300 ms debounce, 1.2 s refractory, 3 s vacancy off-delay, clamp occupancy ≥ 0.
</footer>

<!-- Modal -->
<div id="modal" class="modal" role="dialog" aria-modal="true">
  <div class="box">
    <h3>Automation is off for this appliance</h3>
    <p class="small">Enable automation again? If enabled, the device will follow occupancy and global rules.</p>
    <div class="actions">
      <button id="keepManual" class="btn-red">Keep Manual</button>
      <button id="enableAuto" class="btn-blue">Enable Automation</button>
    </div>
  </div>
</div>

<script>
/* ---------- THEME ---------- */
const ls = localStorage;
let lightMode = ls.getItem('theme')==='light';
if(lightMode) document.body.classList.add('light');
document.getElementById('themeToggle').onclick = ()=>{
  lightMode = !lightMode;
  document.body.classList.toggle('light');
  document.getElementById('themeToggle').textContent = lightMode ? '☀️' : '🌙';
  ls.setItem('theme', lightMode?'light':'dark');
};

/* ---------- HELPERS ---------- */
function daysInMonth(d){ return new Date(d.getFullYear(), d.getMonth()+1, 0).getDate(); }
function mKey(dev){ const d=new Date(); return `mBase_${dev}_${d.getFullYear()}_${d.getMonth()+1}`; }
function dKey(dev){ const d=new Date(); return `dBase_${dev}_${d.getFullYear()}_${d.getMonth()+1}_${d.getDate()}`; }
function ensureBase(key, curr){
  if(ls.getItem(key)===null) ls.setItem(key, String(curr));
  return parseFloat(ls.getItem(key));
}

/* Slabbed pricing (BD) */
function slabCost(kwh){
  kwh = Math.max(0, kwh);
  let remain=kwh,c=0;
  if(remain<=50) return remain*4.19;
  c+=50*4.19; remain-=50;
  if(remain<=25) return c+remain*5.72;
  c+=25*5.72; remain-=25;
  if(remain<=125) return c+remain*6.00;
  c+=125*6.00; remain-=125;
  if(remain<=100) return c+remain*6.34;
  c+=100*6.34; remain-=100;
  if(remain<=200) return c+remain*9.94;
  c+=200*9.94; remain-=200;
  return c + remain*11.46;
}

/* ---------- CONTROLS ---------- */
function api(path){ return fetch(path).then(()=>refresh()); }
function control(dev,action){ return api(`/control?device=${dev}&action=${action}`); }
document.getElementById('globalAutoBtn').onclick = ()=> api('/globalAuto');

document.getElementById('ledOnBtn').onclick   = ()=>control('led','on').then(()=>showModal('led'));
document.getElementById('ledOffBtn').onclick  = ()=>control('led','off').then(()=>showModal('led'));
document.getElementById('ledAutoBtn').onclick = ()=>control('led','auto');

document.getElementById('plugOnBtn').onclick   = ()=>control('plug','on').then(()=>showModal('plug'));
document.getElementById('plugOffBtn').onclick  = ()=>control('plug','off').then(()=>showModal('plug'));
document.getElementById('plugAutoBtn').onclick = ()=>control('plug','auto');

document.getElementById('ledGoalEdit').onclick  = ()=>{
  const v = prompt("LED daily goal (kWh):", document.getElementById('ledGoalVal').textContent);
  if(v) api(`/setGoal?device=led&goal=${v}`);
};
document.getElementById('plugGoalEdit').onclick = ()=>{
  const v = prompt("Plug daily goal (kWh):", document.getElementById('plugGoalVal').textContent);
  if(v) api(`/setGoal?device=plug&goal=${v}`);
};

/* ---------- MODAL ---------- */
let modalDev = null;
function showModal(dev){ modalDev=dev; document.getElementById('modal').style.display='flex'; }
function closeModal(){ modalDev=null; document.getElementById('modal').style.display='none'; }
document.getElementById('keepManual').onclick = closeModal;
document.getElementById('enableAuto').onclick = ()=>{
  if(!modalDev) return closeModal();
  api(`/control?device=${modalDev}&action=auto`).then(closeModal);
};

/* ---------- UI UPDATE ---------- */
function setSwitchDisabled(dev, active){
  document.getElementById(dev+'Warn').style.display = active ? 'block' : 'none';
  document.getElementById(dev+'OnBtn').disabled   = active;
  document.getElementById(dev+'OffBtn').disabled  = active;
  document.getElementById(dev+'AutoBtn').disabled = active;
}

const lastAuto = { led:true, plug:true };

function updateDev(name,obj){
  document.getElementById(name+'V').textContent = obj.V.toFixed(1);
  document.getElementById(name+'I').textContent = obj.I.toFixed(3);
  document.getElementById(name+'P').textContent = obj.P.toFixed(1);
  document.getElementById(name+'E').textContent = obj.E.toFixed(3);

  setSwitchDisabled(name, !!obj.switch);

  const b = document.getElementById(name+'AutoBadge');
  b.textContent = obj.auto ? 'AUTO' : 'MANUAL';
  b.className = 'badge ' + (obj.auto?'on':'off');

  // daily goal progress from today's baseline
  const dBase = ensureBase(dKey(name), obj.E);
  const dayE  = Math.max(0, obj.E - dBase);
  const prog  = Math.min(100, (dayE / Math.max(0.001, obj.goal)) * 100);
  document.getElementById(name+'GoalVal').textContent = obj.goal.toFixed(1);
  document.getElementById(name+'Prog').style.width = prog.toFixed(1)+'%';

  // show modal once when auto flips to OFF (manual action)
  if(lastAuto[name] && !obj.auto) showModal(name);
  lastAuto[name] = !!obj.auto;

  // rough per-device today's cost using average rate (device-level slab is non-linear)
  const avgRate = 7.742;
  document.getElementById(name+'Cost').textContent = (dayE * avgRate).toFixed(0);
}

function refresh(){
  fetch('/state',{cache:'no-store'})
    .then(r=>r.json())
    .then(d=>{
      const occ = document.getElementById('occBadge');
      occ.textContent = d.occupied ? 'Occupied' : 'Vacant';
      occ.className = 'badge ' + (d.occupied?'on':'off');

      document.getElementById('entries').textContent = d.entryCount;
      document.getElementById('exits').textContent   = d.exitCount;
      document.getElementById('globalAutoBtn').textContent = "Global Auto: " + (d.globalAuto?"ON":"OFF");

      updateDev('led',  d.led);
      updateDev('plug', d.plug);

      const totalP = (d.led.P + d.plug.P).toFixed(1);
      document.getElementById('totalPowerVal').textContent = `${totalP} W`;

      // MTD baseline & average-based projection (applied to combined energy)
      const mBaseLed  = ensureBase(mKey('led'),  d.led.E);
      const mBasePlug = ensureBase(mKey('plug'), d.plug.E);
      const mtdKwh = Math.max(0, (d.led.E - mBaseLed) + (d.plug.E - mBasePlug));
      const costMTD = slabCost(mtdKwh);

      const now = new Date();
      const daysElapsed = Math.max(1, now.getDate());
      const totalDays   = daysInMonth(now);
      const avgDaily    = costMTD / daysElapsed;
      const projected   = avgDaily * totalDays;

      document.getElementById('monthCost').textContent = "৳" + projected.toFixed(0);
      document.getElementById('projExplain').textContent =
        `MTD kWh: ${mtdKwh.toFixed(2)} · Cost MTD: ৳${costMTD.toFixed(0)} · Avg/day: ৳${avgDaily.toFixed(0)} · Days: ${daysElapsed}/${totalDays}`;
    })
    .catch(console.error);
}
setInterval(refresh, 1000);
refresh();
</script>
</body>
</html>
)rawliteral";

/* ===================  PIN DEFINITIONS  =================== */
#define RELAY_LED        14
#define RELAY_PLUG       26
#define SWITCH_LED       25
#define SWITCH_PLUG      33
#define DOOR_TRIG        5
#define DOOR_ECHO        18
#define INSIDE_TRIG      4
#define INSIDE_ECHO      19
#define RELAY_ACTIVE_LOW false

/* ===================  OCCUPANCY STATE MACHINE =================== */
enum OccState : uint8_t { VACANT=0, ENTRY_ARMED, OCCUPIED, EXIT_ARMED };

/* ===================  STRUCTS  =================== */
struct Device {
  const char* name;
  uint8_t relayPin;
  uint8_t switchPin;
  bool relayState;          // current relay output
  bool switchState;         // HIGH idle, LOW pressed
  bool autoEnabled;         // per-device automation
  float V, I, P, E, goal;   // telemetry + goal
  // per-device vacancy off delay (3s)
  bool offDelayPending;
  unsigned long offDelayStartMs;
};

Device led  = {"led",  RELAY_LED,  SWITCH_LED,  false, HIGH, true, 0,0,0,0,100, false, 0};
Device plug = {"plug", RELAY_PLUG, SWITCH_PLUG, false, HIGH, true, 0,0,0,0,100, false, 0};

/* ===================  GLOBALS  =================== */
bool globalAuto = true;

volatile OccState occState = VACANT;
volatile unsigned long occStateSince = 0;
volatile int occupancy = 0;
int entryCount = 0;
int exitCount  = 0;

/* timing (ms) */
const unsigned long REFRACTORY_MS   = 1200UL;
const unsigned long WINDOW_PAIR_MS  = 2000UL;
const unsigned long VACANCY_DELAY_MS= 3000UL;
const unsigned long DEBOUNCE_MS     = 300UL;

/* ultrasonic schedule */
const uint32_t TASK_ULTRA_PERIOD_MS = 40;
const uint32_t ULTRA_TIMEOUT_US     = 12000; // pulseIn timeout

/* PZEM & state poll periods */
const uint32_t PZEM_PERIOD_MS  = 500;

/* thresholds */
const float DOOR_THRESH_CM   = 4.0f;
const float INSIDE_THRESH_CM = 30.0f;

/* ring buffers for median(9) */
static const int MED_N = 9;
float doorBuf[MED_N];  int doorIdx=0;  bool doorFilled=false;
float inBuf[MED_N];    int inIdx=0;    bool inFilled=false;

/* trigger times */
unsigned long lastDoorEventMs=0, lastInsideEventMs=0;
unsigned long refractoryUntilMs=0;
unsigned long armWindowUntilMs=0;
unsigned long vacantSinceMs=0;

/* ===================  SERVICES  =================== */
Preferences prefs;
WebServer server(80);
HardwareSerial pzemSerial(2); // UART2

/* PZEM devices (shared UART2 RX=16 TX=17, distinct modbus addresses) */
PZEM004Tv30 pzemLed (pzemSerial, 16, 17, 0x02);
PZEM004Tv30 pzemPlug(pzemSerial, 16, 17, 0x03);

/* ===================  HELPERS  =================== */
static inline float safeVal(float v){ return isfinite(v)? v : 0.0f; }

void setRelay(Device &d, bool on){
  digitalWrite(d.relayPin, RELAY_ACTIVE_LOW ? !on : on);
  d.relayState = on;
}

void pushDoor(float v){ doorBuf[doorIdx++] = v; if(doorIdx>=MED_N){doorIdx=0;doorFilled=true;} }
void pushInside(float v){ inBuf[inIdx++] = v; if(inIdx>=MED_N){inIdx=0;inFilled=true;} }

float medianFrom(float *buf, int n){
  float tmp[MED_N];
  for(int i=0;i<n;i++) tmp[i]=buf[i];
  // insertion sort for n<=9
  for(int i=1;i<n;i++){
    float k=tmp[i]; int j=i-1;
    while(j>=0 && tmp[j]>k){ tmp[j+1]=tmp[j]; j--; }
    tmp[j+1]=k;
  }
  return tmp[n/2];
}

float medianDoor(){
  int n = doorFilled ? MED_N : (doorIdx==0?1:doorIdx);
  return medianFrom(doorBuf, n);
}
float medianInside(){
  int n = inFilled ? MED_N : (inIdx==0?1:inIdx);
  return medianFrom(inBuf, n);
}

float readUltrasonicCM(uint8_t trig, uint8_t echo){
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  unsigned long dur = pulseIn(echo, HIGH, ULTRA_TIMEOUT_US);
  if(!dur) return 9999.0f;
  float cm = dur / 58.2f;
  return cm>0? cm : 9999.0f;
}

/* ===================  OCCUPANCY LOGIC  =================== */
inline bool within(uint32_t now, uint32_t until){ return (int32_t)(until - now) > 0; }

void setOccState(OccState s){ occState = s; occStateSince = millis(); }

void confirmEntry(){
  if(millis() < refractoryUntilMs) return;
  occupancy++; if(occupancy<0) occupancy=0;
  entryCount++;
  setOccState(OCCUPIED);
  refractoryUntilMs = millis() + REFRACTORY_MS;
  // auto actions (global + per device)
  if(globalAuto){
    if(led.autoEnabled)  setRelay(led,  true);
    if(plug.autoEnabled) setRelay(plug, true);
    led.offDelayPending = plug.offDelayPending = false;
  }
}

void confirmExit(){
  if(millis() < refractoryUntilMs) return;
  if(occupancy>0) occupancy--;
  exitCount++;
  if(occupancy==0){
    setOccState(VACANT);
    vacantSinceMs = millis();
  }else{
    setOccState(OCCUPIED);
  }
  refractoryUntilMs = millis() + REFRACTORY_MS;
}

void processOccupancy(float doorCM, float insideCM){
  uint32_t now = millis();
  bool doorTrig   = (doorCM   <= DOOR_THRESH_CM);
  bool insideTrig = (insideCM <= INSIDE_THRESH_CM);

  // per-sensor debounce & refractory
  if(doorTrig   && (now - lastDoorEventMs)   < DEBOUNCE_MS)  doorTrig   = false;
  if(insideTrig && (now - lastInsideEventMs) < DEBOUNCE_MS)  insideTrig = false;
  if(now < refractoryUntilMs){ doorTrig=false; insideTrig=false; }

  switch(occState){
    case VACANT:
      if(doorTrig){ lastDoorEventMs = now; setOccState(ENTRY_ARMED); armWindowUntilMs = now + WINDOW_PAIR_MS; }
      break;
    case ENTRY_ARMED:
      if(!within(now, armWindowUntilMs)) setOccState(VACANT);
      else if(insideTrig){ lastInsideEventMs = now; confirmEntry(); }
      break;
    case OCCUPIED:
      if(insideTrig){ lastInsideEventMs = now; setOccState(EXIT_ARMED); armWindowUntilMs = now + WINDOW_PAIR_MS; }
      break;
    case EXIT_ARMED:
      if(!within(now, armWindowUntilMs)) setOccState(OCCUPIED);
      else if(doorTrig){ lastDoorEventMs = now; confirmExit(); }
      break;
  }

  // per-device 3s delay after vacancy
  if(occupancy==0 && globalAuto){
    if(vacantSinceMs && (now - vacantSinceMs) >= VACANCY_DELAY_MS){
      if(led.autoEnabled)  setRelay(led,false);
      if(plug.autoEnabled) setRelay(plug,false);
      led.offDelayPending = plug.offDelayPending = false;
      vacantSinceMs = 0;
    }
  }
}

/* ===================  SWITCHES & RELAYS  =================== */
void handlePhysicalSwitch(Device &d){
  bool state = digitalRead(d.switchPin);
  if(state != d.switchState){
    delay(30); // debounce
    if(digitalRead(d.switchPin)==state){
      d.switchState = state;
      if(state==LOW){ // press -> toggle & disable auto
        setRelay(d, !d.relayState);
        if(d.autoEnabled){
          d.autoEnabled=false; savePrefs();
        }
      }
    }
  }
}

void updateRelays(){
  if(!globalAuto) return;

  const bool shouldOn = (occupancy>0);
  Device* arr[2] = { &led, &plug };

  for(Device* d: arr){
    if(!d->autoEnabled){ d->offDelayPending=false; continue; }

    if(shouldOn){
      if(!d->relayState) setRelay(*d, true);
      d->offDelayPending=false;
    }else{
      if(d->relayState){
        if(!d->offDelayPending){
          d->offDelayPending = true;
          d->offDelayStartMs = millis();
        }else if(millis() - d->offDelayStartMs >= VACANCY_DELAY_MS){
          setRelay(*d, false);
          d->offDelayPending = false;
        }
      }else{
        d->offDelayPending = false;
      }
    }
  }
}

/* ===================  TELEMETRY & COST  =================== */
void updateTelemetry(){
  led.V = safeVal(pzemLed.voltage());
  led.I = safeVal(pzemLed.current());
  led.P = safeVal(pzemLed.power());
  led.E = safeVal(pzemLed.energy());

  plug.V = safeVal(pzemPlug.voltage());
  plug.I = safeVal(pzemPlug.current());
  plug.P = safeVal(pzemPlug.power());
  plug.E = safeVal(pzemPlug.energy());
}

/* ===================  STORAGE  =================== */
void loadPrefs(){
  prefs.begin("OptiWatt", true);
  globalAuto       = prefs.getBool("globalAuto", true);
  led.autoEnabled  = prefs.getBool("ledAuto",   true);
  plug.autoEnabled = prefs.getBool("plugAuto",  true);
  led.goal         = prefs.getFloat("ledGoal",  100.0f);
  plug.goal        = prefs.getFloat("plugGoal", 100.0f);
  prefs.end();
}

void savePrefs(){
  prefs.begin("OptiWatt", false);
  prefs.putBool("globalAuto", globalAuto);
  prefs.putBool("ledAuto",    led.autoEnabled);
  prefs.putBool("plugAuto",   plug.autoEnabled);
  prefs.putFloat("ledGoal",   led.goal);
  prefs.putFloat("plugGoal",  plug.goal);
  prefs.end();
}

/* ===================  WEB API  =================== */
String jsonState(){
  bool ledSwitchActive  = (led.switchState  == LOW);
  bool plugSwitchActive = (plug.switchState == LOW);

  char buf[1024];
  snprintf(buf, sizeof(buf),
    "{\"led\":{\"V\":%.2f,\"I\":%.3f,\"P\":%.1f,\"E\":%.3f,\"relay\":%s,\"switch\":%s,\"auto\":%s,\"goal\":%.1f},"
    "\"plug\":{\"V\":%.2f,\"I\":%.3f,\"P\":%.1f,\"E\":%.3f,\"relay\":%s,\"switch\":%s,\"auto\":%s,\"goal\":%.1f},"
    "\"occupied\":%s,\"globalAuto\":%s,\"entryCount\":%d,\"exitCount\":%d}",
    led.V,led.I,led.P,led.E, led.relayState?"true":"false",  ledSwitchActive ?"true":"false",  led.autoEnabled ?"true":"false", led.goal,
    plug.V,plug.I,plug.P,plug.E, plug.relayState?"true":"false", plugSwitchActive?"true":"false", plug.autoEnabled?"true":"false", plug.goal,
    (occupancy>0)?"true":"false", globalAuto?"true":"false", entryCount, exitCount);
  return String(buf);
}

void handleState(){ server.send(200,"application/json",jsonState()); }

void handleControl(){
  if(!server.hasArg("device") || !server.hasArg("action")){
    server.send(400,"text/plain","Bad request"); return;
  }
  String dev = server.arg("device");
  String act = server.arg("action");

  Device* d = nullptr;
  if     (dev=="led")  d = &led;
  else if(dev=="plug") d = &plug;
  else { server.send(404,"text/plain","Unknown device"); return; }

  if(act=="on"){
    setRelay(*d,true);
    if(d->autoEnabled){ d->autoEnabled=false; savePrefs(); }
  } else if(act=="off"){
    setRelay(*d,false);
    if(d->autoEnabled){ d->autoEnabled=false; savePrefs(); }
  } else if(act=="auto"){
    bool prev = d->autoEnabled;
    d->autoEnabled = !d->autoEnabled;
    savePrefs();
    if(d->autoEnabled && globalAuto){
      // conform to occupancy immediately
      setRelay(*d, occupancy>0);
      d->offDelayPending=false;
    }
    if(prev && !d->autoEnabled){ d->offDelayPending=false; }
  } else {
    server.send(400,"text/plain","Unknown action"); return;
  }

  server.send(200,"text/plain","OK");
}

void handleGlobalAuto(){
  globalAuto = !globalAuto;
  if(globalAuto){
    if(led.autoEnabled)  setRelay(led,  occupancy>0);
    if(plug.autoEnabled) setRelay(plug, occupancy>0);
    led.offDelayPending = plug.offDelayPending = false;
  }
  savePrefs();
  server.send(200,"text/plain","OK");
}

void handleSetGoal(){
  if(!server.hasArg("device") || !server.hasArg("goal")){
    server.send(400,"text/plain","Bad request"); return;
  }
  String dev = server.arg("device");
  float goal = server.arg("goal").toFloat();
  if(goal<=0){ server.send(400,"text/plain","Invalid goal"); return; }

  if(dev=="led")      led.goal  = goal;
  else if(dev=="plug")plug.goal = goal;
  else { server.send(404,"text/plain","Unknown device"); return; }

  savePrefs();
  server.send(200,"text/plain","OK");
}

/* ===================  SCHEDULER  =================== */
uint32_t tUltraMs=0, tPzemMs=0;

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while(WiFi.status()!=WL_CONNECTED){ delay(300); Serial.print("."); }
  Serial.println("\nWiFi connected: "+WiFi.localIP().toString());

  // PZEM UART2
  pzemSerial.begin(9600, SERIAL_8N1, 16, 17);

  pinMode(RELAY_LED, OUTPUT);
  pinMode(RELAY_PLUG, OUTPUT);
  pinMode(SWITCH_LED, INPUT_PULLUP);
  pinMode(SWITCH_PLUG, INPUT_PULLUP);
  pinMode(DOOR_TRIG, OUTPUT);
  pinMode(DOOR_ECHO, INPUT);
  pinMode(INSIDE_TRIG, OUTPUT);
  pinMode(INSIDE_ECHO, INPUT);

  // init relays OFF
  setRelay(led,false);
  setRelay(plug,false);

  // initial switch snapshot
  led.switchState  = digitalRead(SWITCH_LED);
  plug.switchState = digitalRead(SWITCH_PLUG);

  loadPrefs();

  // API routes
  server.on("/state",      handleState);
  server.on("/control",    handleControl);
  server.on("/globalAuto", handleGlobalAuto);
  server.on("/setGoal",    handleSetGoal);

  // root UI
  server.on("/", [](){ server.send_P(200, "text/html", index_html); });

  // 302 -> root for unknown paths
  server.onNotFound([](){
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
  });

  server.begin();
  Serial.println("HTTP server started");

  occStateSince = millis();
  tUltraMs = tPzemMs = millis();
}

void loop(){
  server.handleClient();

  // physical switches
  handlePhysicalSwitch(led);
  handlePhysicalSwitch(plug);

  // periodic ultrasonic sampling -> ring buffers -> state machine
  uint32_t now = millis();
  if(now - tUltraMs >= TASK_ULTRA_PERIOD_MS){
    tUltraMs = now;
    float d = readUltrasonicCM(DOOR_TRIG, DOOR_ECHO);
    float i = readUltrasonicCM(INSIDE_TRIG, INSIDE_ECHO);
    pushDoor(d);
    pushInside(i);
    processOccupancy(medianDoor(), medianInside());
  }

  // per-device automation enforcement (and vacancy off-delay)
  updateRelays();

  // telemetry each ~500ms
  if(now - tPzemMs >= PZEM_PERIOD_MS){
    tPzemMs = now;
    updateTelemetry();
  }

  // brief yield to keep loop responsive
  delay(10);
}
