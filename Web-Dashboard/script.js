const USERNAME = 'YOUR_ADAFRUIT_USERNAME';
const FEEDS = ['voltage', 'current', 'temp', 'humidity', 'battery'];
const THRESHOLD_TEMP = 35;

// Chart.js Configuration
const commonOptions = {
    responsive: true,
    plugins: { legend: { display: true, position: 'top' } },
    scales: { 
        x: { grid: { display: false } },
        y: { beginAtZero: true, grid: { color: '#f1f5f9' } }
    }
};

const energyChart = new Chart(document.getElementById('energyChart').getContext('2d'), {
    type: 'line',
    data: {
        labels: [],
        datasets: [
            { label: 'Generation (kW)', borderColor: '#10b981', backgroundColor: '#10b98120', data: [], tension: 0.3, fill: true },
            { label: 'Consumption (kW)', borderColor: '#f43f5e', data: [], tension: 0.3 }
        ]
    },
    options: commonOptions
});

const tempChart = new Chart(document.getElementById('tempChart').getContext('2d'), {
    type: 'line',
    data: {
        labels: [],
        datasets: [
            { label: 'Observed Temp (°C)', borderColor: '#f59e0b', data: [], tension: 0.3 },
            { label: 'Threshold (35°C)', borderColor: '#94a3b8', borderDash: [5, 5], data: [], pointRadius: 0 }
        ]
    },
    options: commonOptions
});

async function updateDashboard() {
    let v = 0, c = 0, t = 0;

    for (const feed of FEEDS) {
        try {
            const res = await fetch(`https://io.adafruit.com/api/v2/${USERNAME}/feeds/${feed}/data/last`);
            const data = await res.json();
            const val = parseFloat(data.value);

            if (feed === 'voltage') { v = val; document.getElementById('grid-v').innerText = val.toFixed(0); }
            if (feed === 'current') { c = val; document.getElementById('grid-c').innerText = val.toFixed(0); }
            if (feed === 'temp') { t = val; document.getElementById('temp').innerText = val.toFixed(0); }
            if (feed === 'humidity') document.getElementById('humi').innerText = val.toFixed(0);
            if (feed === 'battery') {
                document.getElementById('battery').innerText = val.toFixed(0);
                document.getElementById('alert-bat').innerText = val.toFixed(1);
            }
        } catch (e) { console.error("Error fetching " + feed); }
    }

    // Calculations
    const solarKW = (v * c) / 1000;
    const loadKW = solarKW * 0.7; // Simulated
    const efficiency = Math.min((solarKW / 2) * 100, 100);

    // Update UI
    document.getElementById('solar-gen').innerText = solarKW.toFixed(2);
    document.getElementById('consumption').innerText = loadKW.toFixed(2);
    document.getElementById('total-gen').innerText = solarKW.toFixed(2);
    document.getElementById('eff-percent').innerText = efficiency.toFixed(1) + "%";
    document.getElementById('eff-bar').style.width = efficiency + "%";

    // Dynamic Alerting
    const alertBox = document.getElementById('alert-box');
    let alerts = '';
    if (t > THRESHOLD_TEMP) {
        alerts += `<div class="p-4 bg-orange-50 text-orange-600 rounded-lg border border-orange-100 text-sm flex items-center"><i class="fas fa-thermometer-high mr-2"></i> HIGH TEMPERATURE ALERT: ${t}°C exceeded threshold!</div>`;
    }
    if (solarKW < 0.01) {
        alerts += `<div class="p-4 bg-amber-50 text-amber-600 rounded-lg border border-amber-100 text-sm flex items-center"><i class="fas fa-broom mr-2"></i> DUST ALERT: Low solar output detected, cleaning suggested.</div>`;
    }
    // Append default battery alert
    alerts += `<div class="p-4 bg-red-50 text-red-600 rounded-lg border border-red-100 text-sm flex items-center"><i class="fas fa-info-circle mr-2"></i> Battery level critically low: ${document.getElementById('battery').innerText}%</div>`;
    alertBox.innerHTML = alerts;

    // Update Charts
    const now = new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit', second: '2-digit' });
    if (energyChart.data.labels.length > 10) {
        [energyChart, tempChart].forEach(chart => {
            chart.data.labels.shift();
            chart.data.datasets.forEach(set => set.data.shift());
        });
    }

    energyChart.data.labels.push(now);
    energyChart.data.datasets[0].data.push(solarKW);
    energyChart.data.datasets[1].data.push(loadKW);
    
    tempChart.data.labels.push(now);
    tempChart.data.datasets[0].data.push(t);
    tempChart.data.datasets[1].data.push(THRESHOLD_TEMP);

    energyChart.update();
    tempChart.update();
}

function manualControl(type) {
    const btn = document.getElementById(`btn-${type}`);
    const isOn = btn.innerText.includes('ON');
    if (isOn) {
        btn.innerText = `Manual ${type.charAt(0).toUpperCase() + type.slice(1)}: OFF`;
        btn.classList.replace('bg-emerald-600', 'bg-slate-800');
    } else {
        btn.innerText = `Manual ${type.charAt(0).toUpperCase() + type.slice(1)}: ON`;
        btn.classList.replace('bg-slate-800', 'bg-emerald-600');
    }
}

setInterval(updateDashboard, 5000);
updateDashboard();
