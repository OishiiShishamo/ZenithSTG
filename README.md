# ZenithSTG
Ultimate Shmups Game Engine!!!!

## Feature
- VERY VERY AUGMENTABILITY
- VERY VERY FAST
- VERY VERY SAFE
- VERY VERY EASY TO READ SOURCE CODE

## Build Instructions
1. Clone the repo from Github\
`git clone --recursive https://github.com/OishiiShishamo/ZenithSTG.git`

2. Download the VS version of DxLib from [here](https://dxlib.xsrv.jp/DxLib/DxLib_VC3_24d.zip)

3. After unzipping, rename **プロジェクトに追加すべきファイル_VC用** to **DxLib** and place it directly under the repository, as it is configured as follows.

> Approximate folder structure after unzip

```
DxLib_VC3_24d
└─DxLib_VC
    ├─help
    ├─Tool
    ├─サンプルプログラム実行用フォルダ
    ├─プロジェクトに追加すべきファイル_VC用
    └─Other files
```

4. Download Boost 1.84 from [here](https://www.boost.org/users/history/version_1_84_0.html), \
build it with [here](https://www.boost.org/doc/libs/1_87_0/more/getting_started/windows.html) as a reference, and place it directly under the repository.

5. If the folder structure looks like the following, you can open and build the solution to start it.
```
ZenithSTG
├─boost
│  ├─include
│  │  └─boost-1_84
│  └─lib
├─DxLib
├─Src
│  ├─res
│  └─Other files
└─Other files
```

6.
[here](https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/lua-5.4.2_Win64_dll17_lib.zip/download)

[here](https://github.com/ThePhD/sol2/releases/download/v3.3.0/sol.hpp)
[here](https://github.com/ThePhD/sol2/releases/download/v3.3.0/config.hpp)