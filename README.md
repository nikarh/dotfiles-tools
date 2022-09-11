# What is this

This repository contains various tools written in compiled languages which are used in my dotfiles for both system and user setup.


## nvidia-uvm-reload

Nvidia CUDA doesn't survive system suspends. This leaves things such as [Sunshine](https://github.com/LizardByte/Sunshine) or [Stable Diffusion](https://github.com/AbdBarho/stable-diffusion-webui-docker) broken after resume.
My current solution to this problem consists of the following:

- A systemd daemon which sends a dbus signal before suspend and after resume
- A shell script which monitors resume signal, stops sunshine, docker containers which require a GPU, calls a dbus method consumed by nvidia-uvm-reload, waits for it to complete and restarts sunshine and docker containers
- A dbus system call handler (nvidia-uvm-reload), which restarts nvidia_uvm kernel module

### Why two codebases?
Everything is better in Rust. But C version has no external dependencies, instantly compiles, and the resulting binary is 10x smaller.

## udev-monitor

When a new USB keyboard is connected, xorg resets repeat rate. Because it's a new keyboard. I want my keyboard settings to be always applied, even to new hardware. In order to do so a user process subscribes to udev USB events, and on any change reexecutes input device configuration.