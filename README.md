[![CircleCI](https://circleci.com/gh/Nicolas-Constanty/udan_sandbox.svg?style=shield&circle-token=8a7f3f2253779be15b661612aecbb31b5b519770)](https://app.circleci.com/pipelines/github/Nicolas-Constanty/udan_sandbox) [![CodeFactor](https://www.codefactor.io/repository/github/nicolas-constanty/udan/badge/main?s=e2f838de4b416755ed4564948b81e7e1312c30b1)](https://www.codefactor.io/repository/github/nicolas-constanty/udan/overview/main)
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
