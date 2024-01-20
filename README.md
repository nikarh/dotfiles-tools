# What is this

This repository contains various tools written in compiled languages which are used in my dotfiles for both system and user setup.

## micro-locker

This tool subscribes systemd DBUS signals and runs arbitrary commands on the following events:
- Lock (indicates that a locker must be started)
- Unlock (indicates that a session is unlocked and the locker can be killed)
- Suspend
- Resume

The commands are set via env variables like this:

```
ON_LOCK="i3lock \
ON_SUSPEND="i3lock" \
ON_UNLOCK="killall i3lock" \
    micro-locker 
```

## udev-monitor

When a new USB keyboard is connected, xorg resets the repeat rate. Because it's a new keyboard. I want my keyboard settings to be always applied, even to new hardware. To do so a user process subscribes to udev USB events and on any change re-executes input device configuration.

## brie-bin

[Brie](https://github.com/nikarh/brie/) is a CLI launcher for wine, which uses a YAML manifest to set up the environment, Wine prefix and launch the given Windows executable with the defined env, preparation command, and winetricks. This repository contains a PKGBUILD which downloads the pre-compiled binary from Github releases.
