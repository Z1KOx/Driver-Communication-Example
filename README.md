# Driver Communication Example

# Overview
This project demonstrates a simple kernel-mode driver and a user-mode application that communicate using IOCTL calls. The driver provides the address of a specific executable, and the application requests this address.

# Prerequisites
- Windows operating system (Windows 10 or later recommended)
- Visual Studio with Windows Driver Kit (WDK) installed
- Administrative privileges
- <a href="https://learn.microsoft.com/en-us/sysinternals/downloads/debugview">DebugView</a> (for viewing debug output)

# Setup Instructions
## 1. Build the Projects
### Kernel-Mode Driver
1. Open the Driver Project in Visual Studio.
2. Build the Driver
   - Select Release configuration.
   - Build the project to generate kernel-mode.sys in the x64\Release folder.

### User-Mode Application
1. Open the Application Project in Visual Studio.
2. Build the Application
   - Select Release configuration.
   - Build the project to create user-mode.exe.

# 2. Install the Driver
### 1. Download and Run DebugView
   - Download DebugView from the <a href="https://learn.microsoft.com/en-us/sysinternals/downloads/debugview">Sysinternals website</a>.
   - Launch DebugView to see debug messages from the driver.
### 2. Open Command Prompt as Administrator
   - Press Win + X and choose Command Prompt (Admin) or Windows PowerShell (Admin).
### 3. Create the Driver Service
   - Execute
```batch
sc create Z1KODriver type= kernel binpath= "C:\Path\To\Your\Driver\x64\Release\kernel-mode.sys"
```
   - Replace C:\Path\To\Your\Driver\x64\Release\kernel-mode.sys with the correct path to your driver file.
### 4. Start the Driver Service
   - Execute
```batch
sc start Z1KODriver
```

# 3. Run AssaultCube
### 1. Start AssaultCube
   - Launch the game AssaultCube before running the user-mode application. The driver is designed to work with this specific game.

# 4. Run the User-Mode Application
### 1. Execute the Application
   - Run
```
C:\Path\To\Your\Application\user-mode.exe
```
### 2. Check DebugView for Output
   - You should see lines like
```
Load Driver
ac_client.exe found
ProcessID: 31548
CREATE I/O Requests
[user-mode] Executable Assaultcube address requested
[user-mode] ProcessID requested
[user-mode] Read requested
[user-mode] Write requested
CLOSE I/O Requests
Unload Driver
```

# Uninstall the Driver
### 1. Stop the Driver Service
   - Execute
```batch
sc stop Z1KODriver
```
### 2. Delete the Driver Service
   - Execute
```batch
sc delete Z1KODriver
```

# Troubleshooting
- Administrative Rights: Ensure you are running commands with administrative privileges.
- File Paths: Verify that the paths to your driver and application are correct.
- DebugView: Use DebugView to see debug messages and verify that the driver is functioning properly.
