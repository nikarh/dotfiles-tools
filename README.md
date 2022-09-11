# What is this

This repository contains various tools written in compiled languages which are used in my dotfiles for both system and user setup.


## nvidia-uvm-reload

Nvidia CUDA doesn't survive system suspends. This leaves things such as [Sunshine](https://github.com/LizardByte/Sunshine) or [Stable Diffusion](https://github.com/AbdBarho/stable-diffusion-webui-docker) broken after resume.
My current solution to this problem consists of the following:

- A systemd daemon which sends a dbus signal before suspend and after resume
- A shell script which monitors resume signal, stops sunshine, docker containers which require a GPU, calls a dbus method consumed by nvidia-uvm-reload, waits for it to complete and restarts sunshine and docker containers
- A dbus system call handler (nvidia-uvm-reload), which restarts nvidia_uvm kernel module

### Why so complicated?

I could have slammed all this logic in a single shell script. But it would be either:
- Running as systemd serice hooked to suspend, and it would have to run stuff as a user.
- Running this script as user, and sudo'ing rmmod and modprobe.

It's a better idea to run priveleged stuff via daemon and RPC call it when needed (using d bus since why not), and run user stuff as user.

## udev-monitor

When a new USB keyboard is connected, xorg resets repeat rate. Because it's a new keyboard. I want my keyboard settings to be always applied, even to new hardware. In order to do so a user process subscribes to udev USB events, and on any change reexecutes input device configuration.