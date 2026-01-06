# Banking System (C/C++ Console)

A simple console-based banking system that stores account records in plain text files. Supports creating accounts, viewing details, depositing, withdrawing, listing all accounts, viewing per-account history, and deleting accounts. Built for learning basic file I/O and structs.

## Features
- Create account with number, name, password, and starting balance
- View account details (password-protected)
- Deposit and withdraw funds with balance updates
- List all accounts (number, owner, balance)
- Per-account history log (`history_<accNo>.txt`) for create/deposit/withdraw
- Delete account (removes account and history files)

## Project Structure
- `main1.cpp`: Program source (stdio + dirent based)
- `account_<accNo>.txt`: One file per account (created at runtime)
- `history_<accNo>.txt`: One file per account with operation log (created at runtime)

## Build
This project uses `<dirent.h>` for directory listing. On Windows, build with a MinGW-w64 toolchain that provides `dirent` (e.g., MSYS2). On Linux/macOS, `dirent` is available by default.

### Windows (MSYS2 MinGW-w64 recommended)
1) Install MSYS2: https://www.msys2.org/
2) In the MSYS2 terminal, install the toolchain (pick UCRT64 or MINGW64):
   ```bash
   pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
   ```
3) Open the corresponding "MSYS2 UCRT64" shell (or MINGW64 shell) and compile:
   ```bash
   g++ main1.cpp -o banking.exe
   ```
   If using a plain Windows terminal with MinGW in PATH, the same command works.

### Linux/macOS
```bash
g++ main1.cpp -o banking
```

## Run
- Windows (PowerShell):
  ```powershell
  .\banking.exe
  ```
- Linux/macOS:
  ```bash
  ./banking
  ```

## Usage (Menu)
1. New Account — create `account_<accNo>.txt` and initial history
2. View — show account info (requires password)
3. Deposit — add funds and log `+`
4. Withdraw — subtract funds (cannot exceed balance) and log `-`
5. List — print all accounts found by scanning `account_*.txt`
6. Delete — remove account and history files (password required)
7. History — print operations from `history_<accNo>.txt`
8. Exit — quit the program

## Data Format
`account_<accNo>.txt` (4 lines):
```
<accNo>
<owner full name>
<password>
<balance as float>
```

`history_<accNo>.txt` (append-only, one entry per line):
```
Created: <amount>
+: <amount>
-: <amount>
```

## Notes & Limitations
- Plaintext passwords and files: not secure; for learning only
- Floating-point balances: can have rounding issues (use integers/cents for real apps)
- No concurrency control; no validation against duplicate concurrent writes
- Minimal input validation; assumes reasonably formatted input

## Roadmap Ideas
- Replace plaintext files with a small database (SQLite)
- Switch to integer cents and stronger validation
- Masked password input and hashed storage
- Unit tests and CI build
- Cross-platform file listing without `dirent` dependency

## Repository Description (for GitHub)
Simple console banking system using text files for storage: create/view accounts, deposit/withdraw, list, history, and delete — built for practicing C/C++ file I/O.

## Suggested Topics (Tags)
`c` · `cpp` · `console-app` · `banking-system` · `file-io` · `learning-project` · `dirent` · `windows` · `msys2`