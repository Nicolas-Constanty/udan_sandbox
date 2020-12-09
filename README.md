[![CodeFactor](https://www.codefactor.io/repository/github/nicolas-constanty/udan/badge/main?s=e2f838de4b416755ed4564948b81e7e1312c30b1)](https://www.codefactor.io/repository/github/nicolas-constanty/udan/overview/main)
# UDAN SANDBOX (Windows 10 - x64 Only)


### BUILD
```
git clone --recursive https://github.com/Nicolas-Constanty/udan_sandbox.git
cd udan_sandbox
.\build.bat
```
Then Open the .sln in Visual Studio 2019, it shoud be ready to build.

### PREMAKE CONFIG
Open **premake5.lua**, modify what you need inside, save it and run **build.bat** into a cmd.
* **defines { "PRINT_LINE" }** *Uncomment this to print log with file and line*
