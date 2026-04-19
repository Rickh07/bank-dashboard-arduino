# 🏦 Bank Dashboard Arduino

A self-hosted, open-source bank dashboard that runs directly from an SD card on an **Arduino MKR WiFi 1010**. Access your bank accounts from any browser on your local network — no cloud, no servers, no subscriptions.

---

## How it works

The Arduino serves static files (HTML, CSS, JS) from the SD card over your local WiFi network. The browser then connects directly to the [Nordigen (GoCardless)](https://nordigen.com) Open Banking API using your personal credentials stored locally in `CONFIG.JS` — a file that **never leaves your device**.