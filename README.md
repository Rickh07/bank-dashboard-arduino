# 🏦 Bank Dashboard Arduino

A self-hosted, open-source bank dashboard that runs directly from an SD card on an **Arduino MKR WiFi 1010**. Access your bank accounts from any browser on your local network — no cloud, no servers, no subscriptions.

---

## How it works

The Arduino serves static files (HTML, CSS, JS) from the SD card over your local WiFi network. The browser then connects directly to the [Nordigen (GoCardless)](https://nordigen.com) Open Banking API using your personal credentials stored locally in `CONFIG.JS` — a file that **never leaves your device**.
Browser (LAN) ←→ Arduino MKR WiFi 1010 (SD card) ←→ Nordigen API

---

## Requirements

### Hardware
- Arduino MKR WiFi 1010
- Arduino MKR SD Proto Shield (or equivalent)
- MicroSD card (FAT32, any size)

### Accounts
- Free [Nordigen / GoCardless](https://ob.nordigen.com) account (Open Banking PSD2)

---

## Setup

1. Clone the repository
```bash
git clone https://github.com/Rickh07/bank-dashboard-arduino.git
```

2. Copy the config template and fill in your credentials
```bash
cp CFGEX.JS CONFIG.JS
```
Then edit `CONFIG.JS` with your Nordigen keys.

3. Copy all files to the SD card root

4. Open the sketch in `arduino/sketch.ino` and upload it to your MKR WiFi 1010

5. Open your browser and navigate to the Arduino's IP address (shown on Serial Monitor)

---

## ⚠️ Security

- `CONFIG.JS` is **gitignored** — your API keys will never be pushed to GitHub
- The dashboard is **LAN-only** — never expose the Arduino to the public internet
- Nordigen tokens are read-only by default

---

## Project structure

```
SD:/
├── INDEX.HTM     → main page
├── STYLE.CSS     → styles
├── APP.JS        → main logic
├── NORDIG.JS     → Nordigen API wrapper
├── CFGEX.JS      → config template (safe to share)
└── CONFIG.JS     → your API keys (gitignored)
arduino/
└── sketch.ino    → Arduino web server sketch

```

---

## Contributing

Pull requests are welcome. If you add support for a new bank or feature, please open a PR with a clear description.

---

## License

MIT