# GTK Youtube Downloader

## A simple GTK4 Front-End for yt-dlp

Supports mp3, aac, mp4 and mkv file formats
mp4 and mkv are limited to 720p resolution because the Operating System doesn't like it when the app takes a while to download something

___

### Installation

#### Dependencies:

- yt-dlp
- ffmpeg

___

#### Windows

First, make sure you have all the dependencies installed, preferably through `winget`
```
winget install ffmpeg yt-dlp
```
or [scoop](https://scoop.sh)
```
scoop install ffmpeg yt-dlp
```

##### Portable zip (Recommended)

To install on Windows, download the portable .zip file from the [releases](https://github.com/Blawal0/yt-downloader-gtk/releases/latest/) page, extract it, and run the `ytdl.exe`

##### Installation from Source

Alternatively, you can install from source, which requires extra dependencies:

- [MSYS2](https://www.msys2.org)
    - mingw-w64-ucrt-x86_64-gtk4
    - mingw-w64-ucrt-x86_64-toolchain
    - base-devel
    - git

Install these dependencies through the MSYS2 shell
```
pacman -S mingw-w64-ucrt-x86_64-gtk4 mingw-w64-ucrt-x86_64-toolchain base-devel git
```

To install from source, first clone the repository through the MSYS2 shell
```
git clone https://github.com/Blawal0/yt-downloader-gtk.git
cd yt-downloader-gtk
```
Then, compile the C file and run it
```
gcc $(pkg-config -cflags gtk4) -o ytdl.exe ytdl.c $(pkg-config -libs gtk4)
./ytdl.exe
```
After the program fully loads, close it

Then, create a temporary folder for the libraries, it can be anywhere within your user folder, and copy all the files from your MSYS2 installation's `/bin` folder to it
After you copy all the files, add that folder to your PATH through Windows' environment variable config tool, and run the file by double-clicking the `ytdl.exe` file you just compiled
While the program is running, try to delete all the files in your temporary folder, and skip all the files that can't be deleted because the program is running, this should leave you with only the required libraries.
After that's done, close the program.

Create a folder called `YTDL` anywhere within your user folder, copy all the libraries from the temporary folder as well as the `ytdl.exe` you compiled previously, then remove your temporary folder from your PATH and delete it.
After that's done, run `ytdl.exe`

#### Linux

Linux users have to install from source, which requires extra dependencies:

- git
- base-devel
- gcc
- gtk4

On debian, Ubuntu and their derivatives, these can be installed with
```
apt install git base-devel gcc libgtk-4-1
```
On Fedora and its derivatives, these can be installed with
```
dnf install git base-devel gcc gtk4
```
On Arch and its derivatives, install them with
```
pacman -S git base-devel gcc gtk4
```
For other linux distributions, check the package list for the GTK4 package, `git`, `gcc` and `base-devel` should have identical package names across distributions


No other methods of installation are available at the moment, but support for them is planned.

To install from source, first clone the repository through your Terminal
```
git clone https://github.com/Blawal0/yt-downloader-gtk.git
cd yt-downloader-gtk
```
Then, compile the C file
```gcc $(pkg-config -cflags gtk4) -o ytdl ytdl.c $(pkg-config -libs gtk4)```
and run it
```./ytdl```

##### (Optional) Adding the file to your graphical application launcher

If you're using a graphical application launcher, you might want to add the app to its application list.
To do that, create a file in your `~/.local/share/applications/` folder called `ytdl.desktop`, and paste the following into it:
```
[Desktop Entry]
Name=Youtube Downloader
Comment=A GTK4 Front-End for yt-dlp
Exec=/path/to/file/ytdl
Terminal=false
Type=Application
```
And replace `/path/to/file/ytdl` with the full path to your `ytdl` executable file

___

### macOS Support

While the program should work on macOS, I do not have a mac, so I cannot test if it runs or how to compile it, if I ever get a mac, this section will be updated.
