# What is this

This repository contains various tools written in compiled languages which are used in my dotfiles for both system and user setup.


## nvidia-uvm-reload

### DEPRECATED

It seems that [Nvidia systemd sleep hook](http://download.nvidia.com/XFree86/Linux-x86_64/530.41.03/README/powermanagement.html) is finally working.

<details>
Nvidia CUDA doesn't survive system suspends. This leaves things such as [Sunshine](https://github.com/LizardByte/Sunshine) or [Stable Diffusion](https://github.com/AbdBarho/stable-diffusion-webui-docker) broken after resuming.
My current solution to this problem consists of the following:

- A systemd daemon that sends a dbus signal before suspend and after resume
- A shell script which monitors resume signal, stops sunshine, docker containers which require a GPU, calls a dbus method consumed by nvidia-uvm-reload, waits for it to complete and restarts sunshine and docker containers
- A dbus system call handler (nvidia-uvm-reload), which restarts the nvidia_uvm kernel module

### Why so complicated?

I could have slammed all this logic in a single shell script. But it would be either:

- Running as systemd service hooked to suspend, and it would have to~~ run stuff as a user.
- Running this script as a user, and sudo'ing rmmod and modprobe.~~

It's a better idea to run privileged stuff via daemon and RPC call it when needed (using d bus since why not), and run user stuff as a user.

</details>

## udev-monitor

When a new USB keyboard is connected, xorg resets the repeat rate. Because it's a new keyboard. I want my keyboard settings to be always applied, even to new hardware. To do so a user process subscribes to udev USB events and on any change re-executes input device configuration.

## play.sh

A magical shell script I use to launch games and windows app via wine. This script uses a yaml manifest describing how to launch games.
For windows games apps it also
 1. Downloads/ensures that a specific wine-ge runtime exists
 2. Ensures wine prefix exists
 3. Unlinks symlinks to $HOME
 4. Downloads and installs the following libraries to a prefix:
    - dxvk (or dxvk-async)
    - dxvk-nvapi
    - vkd3d-proton
    - Copies nvngx.dll from nvidia driver
    - Copies pre-built nvcuda.dll

Also for each game, this script can generate
 - A `.desktop` file
 - An entry in sunshine for remote play
 - A shell script for launching

For `.desktop` files and sunshine entries, it also downloads a banner or icon from steamgriddb.